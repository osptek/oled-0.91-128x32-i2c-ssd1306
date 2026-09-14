#include "ssd1306.h"

#include <string.h>

#include "esp_check.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "ssd1306";

/** Co=0, D/C#=0：后续字节均为命令 */
#define SSD1306_CTRL_CMD  0x00
/** Co=0, D/C#=1：后续字节均为显存数据 */
#define SSD1306_CTRL_DATA 0x40

static esp_err_t ssd1306_write_ctrl(i2c_master_dev_handle_t dev, uint8_t ctrl,
                                    const uint8_t *payload, size_t len)
{
    uint8_t buf[1 + SSD1306_FRAMEBUFFER_SIZE];

    if (len > SSD1306_FRAMEBUFFER_SIZE) {
        return ESP_ERR_INVALID_SIZE;
    }

    buf[0] = ctrl;
    if (len > 0) {
        memcpy(&buf[1], payload, len);
    }

    return i2c_master_transmit(dev, buf, 1 + len, 1000);
}

static esp_err_t ssd1306_write_cmd(i2c_master_dev_handle_t dev, const uint8_t *cmds,
                                   size_t len)
{
    return ssd1306_write_ctrl(dev, SSD1306_CTRL_CMD, cmds, len);
}

static esp_err_t ssd1306_write_cmd_byte(i2c_master_dev_handle_t dev, uint8_t cmd)
{
    return ssd1306_write_cmd(dev, &cmd, 1);
}

static esp_err_t ssd1306_set_address_window(i2c_master_dev_handle_t dev)
{
    static const uint8_t cmds[] = {
        0x21, 0x00, 0x7F,
        0x22, 0x00, 0x03,
    };

    return ssd1306_write_cmd(dev, cmds, sizeof(cmds));
}

esp_err_t ssd1306_init(ssd1306_t *oled)
{
    ESP_RETURN_ON_FALSE(oled != NULL, ESP_ERR_INVALID_ARG, TAG, "oled is NULL");

    memset(oled, 0, sizeof(*oled));

    i2c_master_bus_config_t bus_cfg = {
        .i2c_port = SSD1306_I2C_PORT,
        .sda_io_num = SSD1306_I2C_SDA_GPIO,
        .scl_io_num = SSD1306_I2C_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    ESP_RETURN_ON_ERROR(i2c_new_master_bus(&bus_cfg, &oled->bus), TAG, "i2c bus init failed");

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SSD1306_I2C_ADDR,
        .scl_speed_hz = SSD1306_I2C_FREQ_HZ,
    };

    esp_err_t err = i2c_master_bus_add_device(oled->bus, &dev_cfg, &oled->dev);
    if (err != ESP_OK) {
        i2c_del_master_bus(oled->bus);
        oled->bus = NULL;
        ESP_RETURN_ON_ERROR(err, TAG, "i2c add device failed");
    }

    vTaskDelay(pdMS_TO_TICKS(100));

    static const uint8_t init_seq[] = {
        0xAE,
        0xD5, 0x80,
        0xA8, 0x1F,
        0xD3, 0x00,
        0x40,
        0x8D, 0x14,
        0x20, 0x00,
        0xA1,
        0xC8,
        0xDA, 0x02,
        0x81, 0xCF,
        0xD9, 0xF1,
        0xDB, 0x40,
        0xA4,
        0xA6,
    };

    ESP_RETURN_ON_ERROR(ssd1306_write_cmd(oled->dev, init_seq, sizeof(init_seq)), TAG,
                        "init commands failed");
    ESP_RETURN_ON_ERROR(ssd1306_clear(oled), TAG, "clear failed");
    ESP_RETURN_ON_ERROR(ssd1306_display_on(oled, true), TAG, "display on failed");

    ESP_LOGI(TAG, "SSD1306 %dx%d ready (I2C 0x%02X, SCL=%d, SDA=%d)",
             SSD1306_WIDTH, SSD1306_HEIGHT, SSD1306_I2C_ADDR,
             SSD1306_I2C_SCL_GPIO, SSD1306_I2C_SDA_GPIO);
    return ESP_OK;
}

esp_err_t ssd1306_deinit(ssd1306_t *oled)
{
    if (oled == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (oled->dev != NULL) {
        i2c_master_bus_rm_device(oled->dev);
        oled->dev = NULL;
    }

    if (oled->bus != NULL) {
        i2c_del_master_bus(oled->bus);
        oled->bus = NULL;
    }

    return ESP_OK;
}

esp_err_t ssd1306_display_on(ssd1306_t *oled, bool on)
{
    ESP_RETURN_ON_FALSE(oled != NULL && oled->dev != NULL, ESP_ERR_INVALID_STATE, TAG,
                        "oled not initialized");

    return ssd1306_write_cmd_byte(oled->dev, on ? 0xAF : 0xAE);
}

esp_err_t ssd1306_clear(ssd1306_t *oled)
{
    return ssd1306_fill(oled, 0x00);
}

esp_err_t ssd1306_fill(ssd1306_t *oled, uint8_t pattern)
{
    ESP_RETURN_ON_FALSE(oled != NULL && oled->dev != NULL, ESP_ERR_INVALID_STATE, TAG,
                        "oled not initialized");

    ESP_RETURN_ON_ERROR(ssd1306_set_address_window(oled->dev), TAG, "set window failed");

    uint8_t chunk[1 + 128];
    chunk[0] = SSD1306_CTRL_DATA;
    memset(&chunk[1], pattern, 128);

    for (int page = 0; page < SSD1306_HEIGHT / 8; page++) {
        ESP_RETURN_ON_ERROR(i2c_master_transmit(oled->dev, chunk, sizeof(chunk), 1000),
                            TAG, "fill page %d failed", page);
    }

    return ESP_OK;
}

esp_err_t ssd1306_flush(ssd1306_t *oled, const uint8_t *framebuffer)
{
    ESP_RETURN_ON_FALSE(oled != NULL && oled->dev != NULL && framebuffer != NULL,
                        ESP_ERR_INVALID_STATE, TAG, "invalid flush args");

    ESP_RETURN_ON_ERROR(ssd1306_set_address_window(oled->dev), TAG, "set window failed");

    uint8_t chunk[1 + 128];
    chunk[0] = SSD1306_CTRL_DATA;

    for (int page = 0; page < SSD1306_HEIGHT / 8; page++) {
        memcpy(&chunk[1], &framebuffer[page * SSD1306_WIDTH], SSD1306_WIDTH);
        ESP_RETURN_ON_ERROR(i2c_master_transmit(oled->dev, chunk, sizeof(chunk), 1000),
                            TAG, "flush page %d failed", page);
    }

    return ESP_OK;
}

void ssd1306_fb_clear(uint8_t *fb)
{
    memset(fb, 0x00, SSD1306_FRAMEBUFFER_SIZE);
}

void ssd1306_fb_pixel(uint8_t *fb, int x, int y, bool on)
{
    if (x < 0 || x >= SSD1306_WIDTH || y < 0 || y >= SSD1306_HEIGHT) {
        return;
    }

    int idx = (y / 8) * SSD1306_WIDTH + x;
    uint8_t mask = (uint8_t)(1U << (y % 8));

    if (on) {
        fb[idx] |= mask;
    } else {
        fb[idx] &= (uint8_t)~mask;
    }
}

void ssd1306_fb_fill_rect(uint8_t *fb, int x, int y, int w, int h, bool on)
{
    for (int row = y; row < y + h; row++) {
        for (int col = x; col < x + w; col++) {
            ssd1306_fb_pixel(fb, col, row, on);
        }
    }
}

void ssd1306_fb_frame_rect(uint8_t *fb, int x, int y, int w, int h, int t)
{
    ssd1306_fb_fill_rect(fb, x, y, w, t, true);
    ssd1306_fb_fill_rect(fb, x, y + h - t, w, t, true);
    ssd1306_fb_fill_rect(fb, x, y, t, h, true);
    ssd1306_fb_fill_rect(fb, x + w - t, y, t, h, true);
}

void ssd1306_fb_line(uint8_t *fb, int x0, int y0, int x1, int y1)
{
    int dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
    int sx = (x0 < x1) ? 1 : -1;
    int dy = -((y1 > y0) ? (y1 - y0) : (y0 - y1));
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;

    while (true) {
        ssd1306_fb_pixel(fb, x0, y0, true);
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

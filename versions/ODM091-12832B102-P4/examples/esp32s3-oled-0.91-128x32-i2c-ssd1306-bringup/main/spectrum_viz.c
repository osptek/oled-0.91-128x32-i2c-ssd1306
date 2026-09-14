#include "spectrum_viz.h"

#include <math.h>
#include <string.h>

#include "esp_random.h"

/** 上半区：滚动示波器波形 */
#define WAVE_H          11
#define WAVE_MID_Y      (WAVE_H / 2)

/** 下半区：频谱竖条 */
#define BAR_TOP         12
#define BAR_MAX_H       (SSD1306_HEIGHT - BAR_TOP - 1)
#define BAR_SLOT_W      4
#define BAR_W           3

static void push_wave_sample(spectrum_viz_state_t *state)
{
    const float s =
        0.55f * sinf(state->wave_phase) +
        0.30f * sinf(state->wave_phase * 2.17f) +
        0.15f * sinf(state->wave_phase * 5.03f);

    state->wave_phase += 0.22f;

    int y = WAVE_MID_Y + (int)(s * (WAVE_MID_Y - 1));
    if (y < 0) {
        y = 0;
    } else if (y >= WAVE_H) {
        y = WAVE_H - 1;
    }

    memmove(&state->wave_y[0], &state->wave_y[1], SPECTRUM_WAVE_SAMPLES - 1);
    state->wave_y[SPECTRUM_WAVE_SAMPLES - 1] = (uint8_t)y;
}

static void update_bars(spectrum_viz_state_t *state)
{
    for (int i = 0; i < SPECTRUM_BAR_COUNT; i++) {
        const float f = (float)i / (float)SPECTRUM_BAR_COUNT;
        float target =
            0.40f * sinf(state->phase * 1.05f + f * 12.566f) +
            0.35f * sinf(state->phase * 2.31f + f * 18.84f) +
            0.25f * sinf(state->phase * 0.68f + f * 7.54f);

        target = (target + 1.0f) * 0.5f;

        if ((esp_random() & 0xFF) < 10) {
            target = 0.65f + (float)(esp_random() % 35) / 100.0f;
        }

        state->bar_level[i] = state->bar_level[i] * 0.70f + target * 0.30f;

        if (state->bar_level[i] > state->bar_peak[i]) {
            state->bar_peak[i] = state->bar_level[i];
            state->peak_hold[i] = 14;
        } else if (state->peak_hold[i] > 0) {
            state->peak_hold[i]--;
        } else {
            state->bar_peak[i] *= 0.90f;
        }
    }

    state->phase += 0.11f;
}

static void draw_waveform(uint8_t *fb, const spectrum_viz_state_t *state)
{
    for (int x = 0; x < SPECTRUM_WAVE_SAMPLES - 1; x++) {
        ssd1306_fb_line(fb, x, state->wave_y[x], x + 1, state->wave_y[x + 1]);
    }
}

static void draw_spectrum(uint8_t *fb, const spectrum_viz_state_t *state)
{
    ssd1306_fb_fill_rect(fb, 0, BAR_TOP - 1, SSD1306_WIDTH, 1, true);

    for (int i = 0; i < SPECTRUM_BAR_COUNT; i++) {
        const int x = i * BAR_SLOT_W;

        int h = (int)(state->bar_level[i] * (float)BAR_MAX_H);
        if (h < 0) {
            h = 0;
        } else if (h > BAR_MAX_H) {
            h = BAR_MAX_H;
        }

        if (h > 0) {
            const int y = SSD1306_HEIGHT - 1 - h;
            ssd1306_fb_fill_rect(fb, x, y, BAR_W, h, true);
        }

        int ph = (int)(state->bar_peak[i] * (float)BAR_MAX_H);
        if (ph < 0) {
            ph = 0;
        } else if (ph > BAR_MAX_H) {
            ph = BAR_MAX_H;
        }

        if (ph > 0) {
            const int py = SSD1306_HEIGHT - 1 - ph;
            ssd1306_fb_fill_rect(fb, x, py, BAR_W, 1, true);
        }
    }
}

void spectrum_viz_state_init(spectrum_viz_state_t *state)
{
    memset(state, 0, sizeof(*state));

    for (int i = 0; i < SPECTRUM_WAVE_SAMPLES; i++) {
        state->wave_y[i] = WAVE_MID_Y;
    }
}

esp_err_t spectrum_viz_update(ssd1306_t *oled, spectrum_viz_state_t *state)
{
    static uint8_t fb[SSD1306_FRAMEBUFFER_SIZE];

    state->frame++;
    push_wave_sample(state);
    update_bars(state);

    ssd1306_fb_clear(fb);
    draw_waveform(fb, state);
    draw_spectrum(fb, state);

    return ssd1306_flush(oled, fb);
}

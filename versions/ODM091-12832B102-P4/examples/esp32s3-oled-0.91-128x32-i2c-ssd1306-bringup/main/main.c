/*
 * SPDX-FileCopyrightText: Copyright 2026 OSPTEK
 * SPDX-License-Identifier: CC-BY-4.0
 *
 * https://github.com/osptek
 */

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "spectrum_viz.h"
#include "ssd1306.h"

static const char *TAG = "main";

void app_main(void)
{
    ssd1306_t oled = {0};
    spectrum_viz_state_t viz = {0};

    ESP_LOGI(TAG, "spectrum / waveform viz start");
    ESP_ERROR_CHECK(ssd1306_init(&oled));
    spectrum_viz_state_init(&viz);

    while (true) {
        ESP_ERROR_CHECK(spectrum_viz_update(&oled, &viz));
        vTaskDelay(pdMS_TO_TICKS(33));
    }
}

#pragma once

#include <stdint.h>

#include "esp_err.h"
#include "ssd1306.h"

#define SPECTRUM_BAR_COUNT      32
#define SPECTRUM_WAVE_SAMPLES   SSD1306_WIDTH

typedef struct {
    uint32_t frame;
    float phase;
    float wave_phase;
    float bar_level[SPECTRUM_BAR_COUNT];
    float bar_peak[SPECTRUM_BAR_COUNT];
    uint8_t peak_hold[SPECTRUM_BAR_COUNT];
    uint8_t wave_y[SPECTRUM_WAVE_SAMPLES];
} spectrum_viz_state_t;

void spectrum_viz_state_init(spectrum_viz_state_t *state);
esp_err_t spectrum_viz_update(ssd1306_t *oled, spectrum_viz_state_t *state);

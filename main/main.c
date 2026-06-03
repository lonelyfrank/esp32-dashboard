#include "esp_log.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "bsp_board_extra.h"

static const char *TAG = "dashboard";

static void create_clock_screen(void)
{
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x1a1a2e), 0);

    lv_obj_t *label_time = lv_label_create(scr);
    lv_label_set_text(label_time, "12:00");
    lv_obj_set_style_text_font(label_time, &lv_font_montserrat_18, 0);
    lv_obj_set_style_text_color(label_time, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(label_time, LV_ALIGN_CENTER, 0, -40);

    lv_obj_t *label_date = lv_label_create(scr);
    lv_label_set_text(label_date, "Mercoledi 4 Giugno 2026");
    lv_obj_set_style_text_color(label_date, lv_color_hex(0xAAAAAA), 0);
    lv_obj_align(label_date, LV_ALIGN_CENTER, 0, 20);
}

void app_main(void)
{
    ESP_LOGI(TAG, "Dashboard ESP32-P4 starting...");

    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {
            .buff_dma = true,
            .buff_spiram = true,
            .sw_rotate = false,
        }
    };
    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();

    bsp_display_lock(0);
    create_clock_screen();
    bsp_display_unlock();

    ESP_LOGI(TAG, "Dashboard ready.");
}
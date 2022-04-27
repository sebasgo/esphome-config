#include "kitchen-shutter-ui.h"

#include <lvgl.h>

void KitchenShutterUI::setup() {
    setup_styles();
    setup_header();
}

void KitchenShutterUI::set_temp(float temp) {
    if (isnan(temp)) {
        lv_label_set_text(temp_label_, "-- °C");
    }
    else {
        lv_label_set_text_fmt(temp_label_, "%.1f °C", temp);
    }
}

void KitchenShutterUI::setup_styles() {
    lv_style_init(&header_style_);
    lv_style_set_radius(&header_style_, 0);
    lv_style_set_bg_opa(&header_style_, LV_OPA_COVER);
    lv_style_set_bg_color(&header_style_, lv_palette_darken(LV_PALETTE_BLUE, 1));
    lv_style_set_border_width(&header_style_, 0);
    lv_style_set_text_color(&header_style_, lv_color_white());
    lv_style_set_pad_all(&header_style_, 8);
}

void KitchenShutterUI::setup_header() {
    lv_obj_t *header = lv_obj_create(lv_scr_act());
    lv_obj_set_size(header, 240, 24);
    lv_obj_add_style(header, &header_style_, 0);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t *time_label = lv_label_create(header);
    lv_label_set_text(time_label, "12:34");
    lv_obj_align(time_label, LV_ALIGN_LEFT_MID, 0, 0);

    temp_label_ = lv_label_create(header);
    lv_obj_align(temp_label_, LV_ALIGN_RIGHT_MID, 0, 0);
    set_temp(NAN);
}


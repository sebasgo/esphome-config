#include "kitchen-shutter-ui.h"

#include <lvgl.h>

#include "awesome_extra_16.h"

KitchenShutterUI::KitchenShutterUI() {
    setup_styles();
    setup_header();
    setup_tabs();
    setup_shutter_tab();
    setup_screensaver();
}

void KitchenShutterUI::setup() {
    lv_disp_trig_activity(NULL);
}

void KitchenShutterUI::loop() {
    bool idle = lv_disp_get_inactive_time(NULL) > 15 * 1000;
    if (idle_ != idle) {
        if (idle) {
            lv_obj_clear_flag(screensaver_, LV_OBJ_FLAG_HIDDEN);
        }
        idle_ = idle;
    }
}

void KitchenShutterUI::set_time(esphome::time::ESPTime time) {
    if (time.is_valid()) {
        char time_str[6];
        time.strftime(&time_str[0], 6, "%H:%M");
        lv_label_set_text(time_label_, &time_str[0]);
    }
    else {
        lv_label_set_text(time_label_, "--:--");
    }
}

void KitchenShutterUI::set_temp(float temp) {
    if (isnan(temp)) {
        lv_label_set_text(temp_label_, "-- °C");
    }
    else {
        lv_label_set_text_fmt(temp_label_, "%.1f °C", temp);
    }
}

LvglSwitch * KitchenShutterUI::create_shutter_up_switch() {
    return new LvglSwitch(shutter_up_btn_);
}

LvglSwitch * KitchenShutterUI::create_shutter_down_switch() {
    return new LvglSwitch(shutter_down_btn_);
}

LvglSwitch * KitchenShutterUI::create_shutter_stop_switch() {
    return new LvglSwitch(shutter_stop_btn_);
}

LvglSwitch * KitchenShutterUI::create_shutter_auto_switch() {
    return new LvglSwitch(shutter_auto_switch_, LVGL_SWITCH_RESTORE_DEFAULT_OFF);
}

void KitchenShutterUI::setup_styles() {
    lv_style_init(&tab_style_);
    lv_style_set_pad_top(&tab_style_, 8);
    lv_style_set_pad_bottom(&tab_style_, 8);
    lv_style_set_pad_left(&tab_style_, 4);
    lv_style_set_pad_right(&tab_style_, 4);

    lv_style_init(&header_style_);
    lv_style_set_radius(&header_style_, 0);
    lv_style_set_bg_opa(&header_style_, LV_OPA_COVER);
    lv_style_set_bg_color(&header_style_, lv_palette_darken(LV_PALETTE_BLUE, 1));
    lv_style_set_border_width(&header_style_, 0);
    lv_style_set_text_color(&header_style_, lv_color_white());
    lv_style_set_pad_all(&header_style_, 4);

    lv_style_init(&btn_style_);
    lv_style_set_bg_opa(&btn_style_, LV_OPA_COVER);
    lv_style_set_bg_color(&btn_style_, lv_color_white());
    lv_style_set_text_color(&btn_style_, lv_color_black());
    lv_style_set_border_width(&btn_style_, 1);
    lv_style_set_border_color(&btn_style_, lv_palette_darken(LV_PALETTE_BLUE, 1));

    lv_style_init(&screensaver_style_);
    lv_style_set_radius(&screensaver_style_, 0);
    lv_style_set_border_width(&screensaver_style_, 0);
}

void KitchenShutterUI::setup_header() {
    lv_obj_t *header = lv_obj_create(lv_scr_act());
    lv_obj_set_size(header, 240, 24);
    lv_obj_add_style(header, &header_style_, 0);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);

    time_label_ = lv_label_create(header);
    lv_label_set_text(time_label_, "--:--");
    lv_obj_align(time_label_, LV_ALIGN_LEFT_MID, 0, 0);

    temp_label_ = lv_label_create(header);
    lv_obj_align(temp_label_, LV_ALIGN_RIGHT_MID, 0, 0);
    set_temp(NAN);
}

void KitchenShutterUI::setup_tabs() {
    lv_obj_t *tabview = lv_tabview_create(lv_scr_act(), LV_DIR_BOTTOM, 36);
    lv_obj_set_size(tabview, 240, 296);
    lv_obj_align(tabview, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t *tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_text_font(tab_btns, &awesome_extra_16, 0);

    lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);

    shutter_tab_ = lv_tabview_add_tab(tabview, LV_SYMBOL_BLINDS);
    coffee_tab_ = lv_tabview_add_tab(tabview, LV_SYMBOL_MUG);
    settings_tab_ = lv_tabview_add_tab(tabview, LV_SYMBOL_SETTINGS);

    lv_obj_add_style(shutter_tab_, &tab_style_, 0);
    lv_obj_add_style(coffee_tab_, &tab_style_, 0);
    lv_obj_add_style(settings_tab_, &tab_style_, 0);
}


void KitchenShutterUI::setup_shutter_tab() {
    shutter_up_btn_ = lv_btn_create(shutter_tab_);
    lv_obj_add_style(shutter_up_btn_, &btn_style_, 0);
    lv_obj_set_size(shutter_up_btn_, 232, 62);
    lv_obj_add_flag(shutter_up_btn_, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_align(shutter_up_btn_, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_t *up_btn_label = lv_label_create(shutter_up_btn_);
    lv_label_set_text(up_btn_label, LV_SYMBOL_UP);
    lv_obj_center(up_btn_label);

    shutter_stop_btn_ = lv_btn_create(shutter_tab_);
    lv_obj_add_style(shutter_stop_btn_, &btn_style_, 0);
    lv_obj_set_size(shutter_stop_btn_, 232, 62);
    lv_obj_add_flag(shutter_stop_btn_, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_align(shutter_stop_btn_, LV_ALIGN_TOP_MID, 0, 62 + 8);
    lv_obj_t *stop_btn_label = lv_label_create(shutter_stop_btn_);
    lv_label_set_text(stop_btn_label, LV_SYMBOL_STOP);
    lv_obj_center(stop_btn_label);

    shutter_down_btn_ = lv_btn_create(shutter_tab_);
    lv_obj_add_style(shutter_down_btn_, &btn_style_, 0);
    lv_obj_set_size(shutter_down_btn_, 232, 62);
    lv_obj_add_flag(shutter_down_btn_, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_align(shutter_down_btn_, LV_ALIGN_TOP_MID, 0, 2 * (62 + 8));
    lv_obj_t *down_btn_label = lv_label_create(shutter_down_btn_);
    lv_label_set_text(down_btn_label, LV_SYMBOL_DOWN);
    lv_obj_center(down_btn_label);

    shutter_auto_switch_ = lv_switch_create(shutter_tab_);
    lv_obj_align(shutter_auto_switch_, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t *manual_label = lv_label_create(shutter_tab_);
    lv_obj_set_style_text_font(manual_label, &awesome_extra_16, 0);
    lv_label_set_text(manual_label, LV_SYMBOL_HAND);
    lv_obj_align_to(manual_label, shutter_auto_switch_, LV_ALIGN_OUT_LEFT_MID, -20, 0);
    lv_obj_add_flag(manual_label, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(manual_label, shutter_auto_off_label_clicked_cb, LV_EVENT_CLICKED, (void *)this);

    lv_obj_t *auto_label = lv_label_create(shutter_tab_);
    lv_obj_set_style_text_font(auto_label, &awesome_extra_16, 0);
    lv_label_set_text(auto_label, LV_SYMBOL_CLOUDS_SUN);
    lv_obj_align_to(auto_label, shutter_auto_switch_, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    lv_obj_add_flag(auto_label, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(auto_label, shutter_auto_on_label_clicked_cb, LV_EVENT_CLICKED, (void *)this);
}

void KitchenShutterUI::setup_screensaver() {
    screensaver_ = lv_obj_create(lv_scr_act());
    lv_obj_add_style(screensaver_, &screensaver_style_, 0);
    lv_obj_set_size(screensaver_, 240, 320);
    lv_obj_add_flag(screensaver_, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(screensaver_, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(screensaver_, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_add_event_cb(screensaver_, screensaver_pressed_cb, LV_EVENT_PRESSED,
                        static_cast<void *>(this));
    lv_obj_add_flag(screensaver_, LV_OBJ_FLAG_HIDDEN);
}


void KitchenShutterUI::shutter_auto_off_label_clicked_cb(lv_event_t *event) {
    auto ui = static_cast<KitchenShutterUI *>(event->user_data);
    lv_obj_clear_state(ui->shutter_auto_switch_, LV_STATE_CHECKED);
}

void KitchenShutterUI::shutter_auto_on_label_clicked_cb(lv_event_t *event) {
    auto ui = static_cast<KitchenShutterUI *>(event->user_data);
    lv_obj_add_state(ui->shutter_auto_switch_, LV_STATE_CHECKED);
}

void KitchenShutterUI::screensaver_pressed_cb(lv_event_t *event) {
    auto ui = static_cast<KitchenShutterUI *>(event->user_data);
    lv_obj_add_flag(ui->screensaver_, LV_OBJ_FLAG_HIDDEN);
}

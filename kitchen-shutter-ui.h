#pragma once

#include <esphome.h>
#include <lvgl.h>

#include "lvgl_components.h"

class KitchenShutterUI : public esphome::Component {

public:
    KitchenShutterUI();
    void setup() override;
    void set_time(esphome::time::ESPTime time);
    void set_temp(float temp);

    LvglSwitch * create_shutter_up_switch();
    LvglSwitch * create_shutter_down_switch();
    LvglSwitch * create_shutter_stop_switch();

private:
    void setup_styles();
    void setup_header();
    void setup_tabs();
    void setup_shutter_tab();

    lv_style_t header_style_;
    lv_style_t btn_style_;

    lv_obj_t *time_label_{nullptr};
    lv_obj_t *temp_label_{nullptr};

    lv_obj_t *shutter_tab_{nullptr};
    lv_obj_t *coffee_tab_{nullptr};
    lv_obj_t *settings_tab_{nullptr};

    lv_obj_t *shutter_up_btn_{nullptr};
    lv_obj_t *shutter_stop_btn_{nullptr};
    lv_obj_t *shutter_down_btn_{nullptr};
    lv_obj_t *shutter_auto_switch_{nullptr};
};

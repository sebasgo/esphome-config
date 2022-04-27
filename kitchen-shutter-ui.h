#pragma once

#include <esphome.h>
#include <lvgl.h>

class KitchenShutterUI : public esphome::Component {

public:
    void setup() override;
    void set_time(esphome::time::ESPTime time);
    void set_temp(float temp);

private:
    void setup_styles();
    void setup_header();

    lv_style_t header_style_;

    lv_obj_t *time_label_{nullptr};
    lv_obj_t *temp_label_{nullptr};
};

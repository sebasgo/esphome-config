#pragma once

#include <esphome.h>
#include <lvgl.h>

class KitchenShutterUI : public esphome::Component {

public:
    void setup() override;

private:
    void setup_styles();
    void setup_header();

    lv_style_t header_style_;
};

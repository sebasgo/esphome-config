#pragma once

#include <esphome.h>
#include <lvgl.h>

#include "lvgl_components.h"

class KitchenShutterUI : public esphome::Component {

public:
    KitchenShutterUI();
    void setup() override;
    void loop() override;
    void set_time(esphome::time::ESPTime time);
    void set_temp(float temp);

    LvglSwitch * create_shutter_up_switch();
    LvglSwitch * create_shutter_down_switch();
    LvglSwitch * create_shutter_stop_switch();
    LvglSwitch * create_shutter_auto_switch();


    bool idle() {
        return idle_;
    }

private:
    void setup_styles();
    void setup_header();
    void setup_tabs();
    void setup_shutter_tab();
    void setup_screensaver();

    static void shutter_auto_off_label_clicked_cb(lv_event_t *event);
    static void shutter_auto_on_label_clicked_cb(lv_event_t *event);
    static void screensaver_pressed_cb(lv_event_t *event);

    lv_style_t tab_style_;
    lv_style_t header_style_;
    lv_style_t btn_style_;
    lv_style_t screensaver_style_;

    lv_obj_t *time_label_{nullptr};
    lv_obj_t *temp_label_{nullptr};

    lv_obj_t *shutter_tab_{nullptr};
    lv_obj_t *coffee_tab_{nullptr};
    lv_obj_t *settings_tab_{nullptr};

    lv_obj_t *shutter_up_btn_{nullptr};
    lv_obj_t *shutter_stop_btn_{nullptr};
    lv_obj_t *shutter_down_btn_{nullptr};
    lv_obj_t *shutter_auto_switch_{nullptr};

    lv_obj_t *screensaver_{nullptr};
    bool idle_{false};
};


class LvglIdleSensor : public esphome::PollingComponent, public esphome::binary_sensor::BinarySensor {

public:
    LvglIdleSensor(KitchenShutterUI *ui) :
        PollingComponent(66),
        ui_(ui)
        {}

    void setup() override {
    }

    void update() override {
        publish_state(ui_->idle());
    }

private:
    KitchenShutterUI *ui_{nullptr};

};

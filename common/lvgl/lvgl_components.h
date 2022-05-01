#pragma once

#include <esphome.h>
#include <esphome/core/component.h>

class LvglSwitch : public esphome::Component, public esphome::switch_::Switch
{
private:
  lv_obj_t *obj_{nullptr};

public:
  LvglSwitch(lv_obj_t *obj)
    : obj_{obj}
  {}

  void setup() override {
    lv_obj_add_event_cb(obj_, lvgl_event_cb, LV_EVENT_VALUE_CHANGED, (void *)this);
  }

  void write_state(bool state) override
  {
    if (state) {
      lv_obj_add_state(obj_, LV_STATE_CHECKED);
    }
    else {
      lv_obj_clear_state(obj_, LV_STATE_CHECKED);
    }

    // Acknowledge new state by publishing it
    publish_state(state);
  }

  static void lvgl_event_cb(lv_event_t *event)
  {
    lv_obj_t *target = lv_event_get_target(event);
    LvglSwitch *sw = (LvglSwitch *)event->user_data;

    bool state = (lv_obj_get_state(target) & LV_STATE_CHECKED);

    sw->publish_state(state);
  }
};

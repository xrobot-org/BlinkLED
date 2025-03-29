#pragma once

// clang-format off
/* === MODULE MANIFEST ===
module_name: BlinkLED
module_description: 控制 LED 闪烁的简单模块 / A simple module to control LED blinking
constructor_args:
  blink_cycle: 250
required_hardware: led/LED/led1/LED1
repository: https://github.com/xrobot-org/BlinkLED
=== END MANIFEST === */
// clang-format on

#include "app_framework.hpp"
#include "gpio.hpp"
#include "libxr_def.hpp"
#include "timer.hpp"

template <typename HardwareContainer>
class BlinkLED : public LibXR::Application {
public:
  BlinkLED(HardwareContainer &hw, LibXR::ApplicationManager &app,
           uint32_t blink_cycle) {
    UNUSED(app);

    led_ = hw.template FindOrExit<LibXR::GPIO>({"led", "LED", "led1", "LED1"});
    timer_handle_ = LibXR::Timer::CreateTask(BlinkTaskFun, this, blink_cycle);
    LibXR::Timer::Add(timer_handle_);
    LibXR::Timer::Start(timer_handle_);
  }

  static void BlinkTaskFun(BlinkLED<HardwareContainer> *blink) {
    blink->flag_ = !blink->flag_;
    blink->led_->Write(blink->flag_);
  }

  void OnMonitor() override {}

private:
  bool flag_ = false;
  LibXR::GPIO *led_;
  LibXR::Timer::TimerHandle timer_handle_;
};

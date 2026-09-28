# BlinkLED

控制 LED 闪烁的简单模块。
A simple module that blinks an LED.

构造后，模块用一个 LibXR 定时器任务按 `blink_cycle` 毫秒翻转 LED。它同时注册
LibXR 致命错误回调：发生致命错误时停止定时器，并以 125 ms / 125 ms / 500 ms / 500 ms
的特殊节奏闪烁 LED 指示故障（在中断上下文中触发时不进入闪烁循环）。

After construction a LibXR timer task toggles the LED every `blink_cycle`
milliseconds. The module also registers a LibXR fatal-error callback: on a fatal
error it stops the timer and blinks the LED in a 125 ms / 125 ms / 500 ms / 500 ms
pattern (not when the error is raised from an interrupt).

## 依赖 / Dependencies

无其他模块依赖，仅使用 LibXR。
No other Modules; LibXR only.

## 构造接口 / Constructor

```cpp
BlinkLED(LibXR::GPIO& led, uint32_t blink_cycle = 250);
```

依赖 / Dependencies:

- `led`：驱动 LED 的 GPIO。/ The GPIO that drives the LED.

配置 / Configuration:

- `blink_cycle`：翻转周期，单位 ms，默认 250。/ Toggle period in ms, default 250.

## 使用 / Use

```sh
xrobot module add xrobot-org/BlinkLED
xrobot setup
xrobot instance add xrobot-org/BlinkLED
```

`xrobot instance add` 在 `User/xrobot.yaml` 中写入一个实例，依赖项留空，默认值按源码写出；
把 `led` 填为 BSP 中用 `XR_REGISTER` 注册的 GPIO 对象名：
`xrobot instance add` writes an instance to `User/xrobot.yaml` with empty
dependencies and the source defaults; set `led` to the name of a GPIO object the
BSP registers with `XR_REGISTER`:

```yaml
modules:
  - module: xrobot-org/BlinkLED
    id: blinkled_0
    args:
      - led: led_b
      - blink_cycle: '250'
```

BSP 侧 / BSP side:

```cpp
XR_REGISTER(led_b, LibXR::GPIO);
```

填好后再次运行 `xrobot setup`，生成 `User/xrobot_main.hpp`。
Run `xrobot setup` again to generate `User/xrobot_main.hpp`.

`xrobot module show .`（在本仓库中）或 `xrobot module show Modules/xrobot-org/BlinkLED`
（在 BSP 中）打印当前的构造函数。
`xrobot module show .` in this repository, or
`xrobot module show Modules/xrobot-org/BlinkLED` in a BSP, prints the current
constructor.

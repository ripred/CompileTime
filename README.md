[![Arduino CI](https://img.shields.io/static/v1?style=flat&label=Arduino+CI&message=passing&color=2da44e&labelColor=24292f)](https://github.com/ripred/CompileTime/actions/workflows/arduino_test_runner.yml)
[![Arduino-lint](https://img.shields.io/static/v1?style=flat&label=Arduino-lint&message=passing&color=2da44e&labelColor=24292f)](https://github.com/ripred/CompileTime/actions/workflows/arduino-lint.yml)
[![JSON check](https://img.shields.io/static/v1?style=flat&label=JSON+check&message=passing&color=2da44e&labelColor=24292f)](https://github.com/ripred/CompileTime/actions/workflows/jsoncheck.yml)
[![Arduino Library Manager](https://img.shields.io/static/v1?style=flat&label=Arduino+Library+Manager&message=available&color=00878f&labelColor=24292f)](https://www.ardu-badge.com/CompileTime)
[![Release](https://img.shields.io/static/v1?style=flat&label=Release&message=v1.6&color=8250df&labelColor=24292f)](https://github.com/ripred/CompileTime/releases/latest)
[![License](https://img.shields.io/static/v1?style=flat&label=License&message=MIT&color=0969da&labelColor=24292f)](https://github.com/ripred/CompileTime/blob/main/LICENSE)
[![Stars](https://img.shields.io/static/v1?style=flat&label=Stars&message=7&color=bf8700&labelColor=24292f)](https://github.com/ripred/CompileTime/stargazers)
[![Forks](https://img.shields.io/static/v1?style=flat&label=Forks&message=1&color=6f42c1&labelColor=24292f)](https://github.com/ripred/CompileTime/network/members)

![code size](https://flat.badgen.net/badge/code%20size/7.9%20KiB/blue)


****CompileTime Library****

Include the library in your code, call two functions, and from then on when you next compile and upload your project to your microcontroller it will automatically make the current live, wallclock time of the pc, mac, or linux host that compiled it available as the variables: `hour`, `minute`, and `second` and they will be kept up-to-date as long as the board has power. 

Requires calling just two functions and the current time for your Arduino project will be identical to the current time of your pc, mac, or linux machine **down to the second**.

Uses a `CompileTime` namespace so there won't be collisions for those common symbol names. Works with any C/C++ compiler and any embedded platform.
example use:

```cpp
/*
 * CompileTime.ino
 * 
 * example Arduino IDE sketch for the CompileTime library
 * 
 * version 1.0 written June 2023 - Trent M. Wyatt
 * 
 */
#include "CompileTime.h"

using namespace CompileTime;

void setup() {
    CompileTime::setCompileTime(6); // pass the number of seconds it takes to upload
    Serial.begin(115200);
}

void loop() {
    static int16_t lasth = hour, lastm = minute, lasts = second;
    updateTime(micros());

    if (lasts != second || lastm != minute || lasth != hour) {
        lasts  = second;   lastm  = minute;   lasth  = hour;

        char buff[16];
        sprintf(buff, "%s%d %d - %2d:%02d:%02d", month, day, year, hour, minute, second);
        Serial.println(buff);
    }
}
```

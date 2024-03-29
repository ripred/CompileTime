[![Arduino CI](https://github.com/ripred/CompileTime/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/ripred/CompileTime/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/ripred/CompileTime/actions/workflows/arduino-lint.yml)
![code size:](https://img.shields.io/github/languages/code-size/ripred/CompileTime)
[![GitHub release](https://img.shields.io/github/release/ripred/CompileTime.svg?maxAge=3600)](https://github.com/ripred/CompileTime/releases)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/ripred/CompileTime/blob/master/LICENSE)

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


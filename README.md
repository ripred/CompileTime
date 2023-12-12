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
#include <Arduino.h>
#include <CompileTime.h>
using namespace CompileTime;

void setup() {
    setCompileTime(4);  // pass the number of seconds it takes to upload

    Serial.begin(115200);
}

void loop() {
    static uint16_t lasth = hour, lastm = minute, lasts = second;

    updateTime(micros());

    if (lasts != second || lastm != minute || lasth != hour) {
        lasts  = second;   lastm  = minute;   lasth  = hour;

        char buff[16];
        sprintf(buff, "%2d:%02d:%02d", hour, minute, second);
        Serial.println(buff);
    }
}
```

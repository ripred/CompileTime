CompileTime Library

This library allows you to use the hours, minutes, and seconds
from your computer's compile time as 3 initialized variables
into your project that keep themselves up to date.

Works with or without the Arduino environment.

example use:

```
/*
 * CompileTime.ino
 * 
 * example Arduino IDE sketch for the CompileTime library
 * 
 * version 1.0 written July 2023 - Trent m. Wyatt
 * 
 */
#include <Arduino.h>
#include <CompileTime.h>

using namespace CompileTime;

void setup() {
    setCompileTime();
    Serial.begin(115200);

    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:

    static uint16_t lasth = hour, lastm = minute, lasts = second;
    updateTime(micros());

    if (lasts != second || lastm != minute || lasth != hour) {
        lasts = second;
        lastm = minute;
        lasth = hour;

        char buff[16];
        sprintf(buff, "%02d:%02d:%02d", hour, minute, second);
        Serial.println(buff);
    }
}
```

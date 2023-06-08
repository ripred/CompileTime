CompileTime Library

Include the library in your code, call two functions, and from then on when you next compile and upload your project to your microcontroller it will automatically make the current live, wallclock time of the pc, mac, or linux host that compiled it available as the variables: hour, minute, and second and they will be kept up-to-date as long as the board has power. 

Requires calling just two functions and the current time for your Arduino project will be identical to the current time of your pc, mac, or linux machine down to the second. 

Uses a compileTime namespace so there won't be collisions for those common symbol names. Works with any C/C++ compiler or embedded platform.
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

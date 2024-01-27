/*
 * CompileTime.ino
 * 
 * example Arduino IDE sketch for the CompileTime library
 * 
 * version 1.0 written June 2023 - Trent M. Wyatt
 * version 1.5 written December 2023 - Trent M. Wyatt
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

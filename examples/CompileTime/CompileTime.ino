/*
 * CompileTime.ino
 * 
 * example Arduino IDE sketch for the CompileTime library
 * 
 * version 1.0 written June 2023 - Trent m. Wyatt
 * 
 */
#include "CompileTime.h"

using namespace CompileTime;

void setup() {
    CompileTime::setCompileTime();
    Serial.begin(115200);

    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:

    static uint16_t lasth = hour, lastm = minute, lasts = second;
    updateTime();

    if (lasts != second || lastm != minute || lasth != hour) {
        lasts = second;
        lastm = minute;
        lasth = hour;

        char buff[16];
        sprintf(buff, "%02d:%02d:%02d", hour, minute, second);
        Serial.println(buff);
    }

}

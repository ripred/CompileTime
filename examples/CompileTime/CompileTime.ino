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

// names of months
const char* months[12] {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void setup() {
    CompileTime::setCompileTime(6); // pass the number of seconds it takes to upload
    Serial.begin(115200);
    if (!isEepromValid()) {
        Serial.println(F("Note that calibration has not been done on this microcontroller"));
        Serial.println(F("You should exit the IDE and reload it and then load the Calibrate.ino"));
        Serial.println(F("sketch and let i finish and then enter the hour:minute:second displayed"));
        Serial.println(F("when you have the timestamps turned on in the serial monitor. After that"));
        Serial.println(F("the calibration will be stored in EEPROM and the CompileTime library will"));
        Serial.println(F("stay accurate with 32 milliseconds, and this message will not be displayed."));
    }
}

void loop() {
    static int16_t lasth = hour, lastm = minute, lasts = second;
    updateTime(micros());

    if (lasts != second || lastm != minute || lasth != hour) {
        lasts  = second;   lastm  = minute;   lasth  = hour;

        char buff[16];
        sprintf(buff, "%s, %d, %d - %2d:%02d:%02d", months[month], day, year, hour, minute, second);
        Serial.println(buff);
    }
}

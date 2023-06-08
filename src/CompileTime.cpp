/*
 * CompileTime.cpp
 * 
 * implementation file for the CompileTime library
 * 
 * version 1.0 written June 2023 - Trent m. Wyatt
 * 
 */
#include "CompileTime.h"

using namespace CompileTime;

#if !defined(ARDUINO) && not ARDUINO_ARCH_RENESAS

#include <stdio.h>
#include <sys/time.h>

uint32_t micros() {
    unsigned long long start_time_us;
    unsigned long long current_time_us;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    start_time_us = (unsigned long long)(tv.tv_sec) * 1000000 + (unsigned long long)(tv.tv_usec);

    gettimeofday(&tv, NULL);
    current_time_us = (unsigned long long)(tv.tv_sec) * 1000000 + (unsigned long long)(tv.tv_usec);
    unsigned long long microseconds_since_boot = current_time_us - start_time_us;

    return microseconds_since_boot;

} // micros()

uint32_t millis() {
    return micros() / 1000UL;

} // millis()

void noInterrupts() { }
void interrupts() { }

#endif

enum MagicNumbers : uint32_t {
    secsPerMin    =   60UL,
    minsPerHour   =   60UL,
    secsPerHour   = 3600UL,

    // The number of microseconds to calibrate the internal PLL
    // generated clock source to (if in use and adjusted):
    uSecAdjust    = 1000000,
};

// Global values used at runtime
uint32_t CompileTime::startTime;
volatile int16_t CompileTime::second;
volatile int16_t CompileTime::hour;
volatile int16_t CompileTime::minute;

void CompileTime::updateTime(uint32_t const now) {
    uint32_t now_secs = (now / uSecAdjust) + CompileTime::startTime;
    uint16_t curHour = now_secs / secsPerHour;
    now_secs -= curHour * secsPerHour;
    uint16_t curMinute = now_secs / secsPerMin;
    now_secs -= curMinute * secsPerMin;

    CompileTime::hour = curHour;
    CompileTime::minute = curMinute;
    CompileTime::second = now_secs;
}

void CompileTime::setCompileTime() {
    // convert the digits from the ascii __TIME__ string into binary values:
    char const tm[9] = __TIME__;
    uint16_t curHour   = ((uint32_t)(tm[0] - '0') * 10UL) + (uint32_t)(tm[1] - '0');
    uint16_t curMinute = ((uint32_t)(tm[3] - '0') * 10UL) + (uint32_t)(tm[4] - '0');
    uint16_t curSecond = ((uint32_t)(tm[6] - '0') * 10UL) + (uint32_t)(tm[7] - '0');

    // Adjust for the time it took to upload: (change time as needed)
    uint32_t upload_time_seconds = 4UL;
    curSecond += upload_time_seconds;
    while (curSecond >= secsPerMin) {
        curSecond -= secsPerMin;
        if (++curMinute >= minsPerHour) {
            curMinute -= minsPerHour;
            if (++curHour >= 24UL) {
                curHour -= 24UL;
            }
        }
    }

    CompileTime::hour   = curHour;
    CompileTime::minute = curMinute;
    CompileTime::second = curSecond;

    // Set the starting time in seconds since midnight:
    CompileTime::startTime = curHour * secsPerHour + curMinute * secsPerMin + curSecond;
}

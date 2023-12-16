/*
 * CompileTime.cpp
 *
 * implementation file for the CompileTime library
 *
 * version 1.0 written June 2023 - Trent M. Wyatt
 *
 */
#include "CompileTime.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "EEPROM.h"

char const * const tmstr = __TIME__;
char const * const dtstr = __DATE__;

// Function to check if a year is a leap year
static bool isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;  // Leap year
    } else {
        return false; // Not a leap year
    }
}

// Array of days in each month
static int16_t daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

enum MagicNumbers : uint32_t {
    secsPerMin    =   60UL,
    minsPerHour   =   60UL,
    secsPerHour   = 3600UL,
};

static uint16_t const monthhash[12] = {
// ascii added together
    281,    // J+a+n = 74+97+110
    269,    // F+e+b = 70+101+98
    288,    // M+a+r = 77+97+114
    291,    // A+p+r = 65+112+114
    295,    // M+a+y = 77+97+121
    301,    // J+u+n = 74+117+110
    299,    // J+u+l = 74+117+108
    285,    // A+u+g = 65+117+103
    296,    // S+e+p = 83+101+112
    294,    // O+c+t = 79+99+116
    307,    // N+o+v = 78+111+118
    268,    // D+e+c = 68+101+99
};

namespace CompileTime {

// Global values used at runtime
uint32_t startTime;
volatile int16_t hour;
volatile int16_t minute;
volatile int16_t second;
volatile int16_t year;
volatile int16_t month;
volatile int16_t day;

// The number of microseconds to calibrate the internal PLL
// generated clock source to (if in use and adjusted):
uint32_t uSecAdjust = 1000000UL;

void writeUInt32ToEEPROM(uint32_t value, int address) {
    for (int i = 0; i < 4; ++i) {
        EEPROM.write(address + i, (value >> (i * 8)) & 0xFF);
    }
}

uint32_t readUInt32FromEEPROM(int address) {
    uint32_t value = 0;

    for (int i = 0; i < 4; ++i) {
        value |= (uint32_t)(EEPROM.read(address + i)) << (i * 8);
    }

    return value;
}

uint32_t const eeprom_signature = 0xDEADBEEF;

int isEepromValid() {
    return readUInt32FromEEPROM(0) == eeprom_signature;
}

void writeEepromCalibrate(uint32_t cal_us) {
    writeUInt32ToEEPROM(eeprom_signature, 0);
    writeUInt32ToEEPROM(cal_us, sizeof(eeprom_signature));
}

void setCompileTime(double const upload) {
    // convert the digits from the ascii __TIME__ string into binary values:
    char tm[9] {0};
    strcpy(tm, tmstr);
    uint16_t curHour   = ((uint32_t)(tm[0] - '0') * 10UL) + (uint32_t)(tm[1] - '0');
    uint16_t curMinute = ((uint32_t)(tm[3] - '0') * 10UL) + (uint32_t)(tm[4] - '0');
    uint16_t curSecond = ((uint32_t)(tm[6] - '0') * 10UL) + (uint32_t)(tm[7] - '0');

    char dt[12] {0};
    strcpy(dt, dtstr);
    uint16_t curYear = atoi(dt + 7);
    uint16_t monthHash = dt[0] + dt[1] + dt[2];
    uint8_t curMonth = -1;
    for (uint8_t m = 0; m < 12; m++) {
        if (monthHash == monthhash[m]) {
            curMonth = m;
            break;
        }
    }
    char const * dayPtr = dt + 4;
    volatile uint8_t curDay = atoi(dayPtr);

    // Adjust for the time it took to upload: (change time as needed)
    curSecond = ((curSecond * 1000) + uint32_t(upload * 1000.0)) / 1000;
    while (curSecond >= secsPerMin) {
        curSecond -= secsPerMin;
        if (++curMinute >= minsPerHour) {
            curMinute -= minsPerHour;
            if (++curHour >= 24UL) {
                curHour -= 24UL;
            }
        }
    }

    hour   = curHour;
    minute = curMinute;
    second = curSecond;
    year   = curYear;
    month  = curMonth;
    day    = curDay;

    // Set the starting time in seconds since midnight:
    startTime = curHour * secsPerHour + curMinute * secsPerMin + curSecond;

    uint32_t const eeprom_signature = 0xDEADBEEF;
    uint32_t const existing_signature = readUInt32FromEEPROM(0);
    if (existing_signature == eeprom_signature) {
        uSecAdjust = readUInt32FromEEPROM(sizeof(eeprom_signature));
    }
}

static int16_t last_hour = hour;

void updateTime(uint32_t const now) {
    uint32_t now_secs = (now / uSecAdjust) + startTime;
    int16_t curHour = now_secs / secsPerHour;
    now_secs -= curHour * secsPerHour;
    int16_t curMinute = now_secs / secsPerMin;
    now_secs -= curMinute * secsPerMin;

    if (isLeapYear(year)) {
        daysInMonth[1] = 29; // February
    } else {
        daysInMonth[1] = 28; // February
    }

    hour = curHour;
    minute = curMinute;
    second = now_secs;
    if (last_hour != hour) {
        if (last_hour == 23 && hour >= 24) {
            hour -= 24;
            day++;
            if (daysInMonth[month] == day) {
                day = 1;
                month++;
                if (month >= 13) {
                    month -= 12;
                    year++;
                }
            }
        }
        hour %= 24;
        minute %= 60;
        second %= 60;
        last_hour = hour;
    }

}

} // namespace CompileTime

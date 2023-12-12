/*
 * CompileTime.h
 * 
 * header file for the CompileTime library
 * 
 * version 1.0 written June 2023 - Trent M. Wyatt
 * 
 */
#ifndef COMPILETIME_H_INCL
#define COMPILETIME_H_INCL

#include <inttypes.h>

namespace CompileTime {

// Global values used at runtime
extern uint32_t startTime;
extern volatile int16_t second, hour, minute;
extern volatile int16_t year, month, day;
extern uint32_t uSecAdjust;

void setCompileTime(double const upload);
void updateTime(uint32_t const now);

int isEepromValid();
void writeEepromCalibrate(uint32_t cal_us);

}
#endif // COMPILETIME_H_INCL

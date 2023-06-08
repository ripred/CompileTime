/*
 * CompileTime.h
 * 
 * header file for the CompileTime library
 * 
 * version 1.0 written June 2023 - Trent m. Wyatt
 * 
 */
#ifndef COMPILETIME_H_INCL
#define COMPILETIME_H_INCL

#include <inttypes.h>

namespace CompileTime {

// Global values used at runtime
extern uint32_t startTime;
extern volatile int16_t second, hour, minute;

void updateTime(uint32_t const now);
void setCompileTime(int const upload);

}
#endif // COMPILETIME_H_INCL

#ifndef GOLCONSTANTS_H
#define GOLCONSTANTS_H

#include "types.h"

class FloatConstant {
public:
	FloatConstant(LegoFloat p_value) { m_value = p_value; }

	LegoFloat m_value;
};

// GLOBAL: LEGORACERS 0x004c706c
// GLOBAL: GOLDP 0x10065b54
const FloatConstant g_floatConst4096(4096.0f);

// GLOBAL: LEGORACERS 0x004c7074
// GLOBAL: GOLDP 0x10065b5c
const FloatConstant g_floatConst32(32.0f);

extern const LegoFloat g_floatConst127;
extern const LegoFloat g_floatConst256;
extern const LegoFloat g_floatConst1000;

#endif // GOLCONSTANTS_H

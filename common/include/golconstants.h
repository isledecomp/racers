#ifndef GOLCONSTANTS_H
#define GOLCONSTANTS_H

#include "types.h"

class FloatConstant {
public:
	FloatConstant(LegoFloat p_value) { m_value = p_value; }

	LegoFloat m_value;
};

extern const FloatConstant g_floatConst4096;
extern const FloatConstant g_floatConst32;
extern const LegoFloat g_floatConst127;

#endif // GOLCONSTANTS_H

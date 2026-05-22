#ifndef GOLCONSTANTS_H
#define GOLCONSTANTS_H

#include "types.h"

class FloatConstant {
public:
	FloatConstant(LegoFloat p_value) { m_value = p_value; }

	LegoFloat m_value;
};

extern const FloatConstant g_4096f;
extern const FloatConstant g_32f;
extern const LegoFloat g_127f;

#endif // GOLCONSTANTS_H

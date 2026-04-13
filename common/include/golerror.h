#ifndef GOLERROR_H
#define GOLERROR_H

#include "types.h"

enum GolErrorCode {
	c_golErrorAssertion = -7,
	c_golErrorCriticalResource = -5,
	c_golErrorOutOfMemory = -4,
	c_golErrorInvalidValue = -3,
	c_golErrorInvalidParameter = -2,
	c_golErrorGeneral = -1,
	c_golErrorInvalidCondition = 0
};

void GolFatalError(LegoS32, LegoS32, LegoS32);

#endif // GOLERROR_H

#ifndef GOLERROR_H
#define GOLERROR_H

#include "types.h"

#define GOL_FATALERROR_MESSAGE(MESSAGE) GolFatalErrorMessage(MESSAGE, NULL, 0)

#ifdef BUILDING_GOL
#include "gol.h"

extern FatalErrorMessageCBFN* g_fatalErrorMessage;
#endif

enum GolErrorCode {
	c_golErrorAssertion = -7,
	c_golErrorCriticalResource = -5,
	c_golErrorOutOfMemory = -4,
	c_golErrorInvalidValue = -3,
	c_golErrorInvalidParameter = -2,
	c_golErrorGeneral = -1,
	c_golErrorInvalidCondition = 0
};

extern void GolFatalErrorMessage(const char* p_message, const char* p_file, int p_line);

extern void GolFatalError(GolErrorCode p_code, const char* p_file, int p_line);

#endif // GOLERROR_H

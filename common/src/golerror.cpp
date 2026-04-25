#include "golerror.h"

#include "decomp.h"

#ifdef BUILDING_LEGORACERS
#include "main.h"
#endif

#if defined(BUILDING_GOL)
#include "gol.h"

// GLOBAL: GOLDP 0x1006314c
FatalErrorMessageCBFN* g_fatalErrorMessage;
#endif

// FUNCTION: GOLDP 0x100070d0
// FUNCTION: LEGORACERS 0x0042f8b0
void GolFatalErrorMessage(const LegoChar* p_message, const LegoChar* p_file, LegoS32 p_line)
{
#ifdef BUILDING_LEGORACERS
	g_racers.Shutdown();
	MessageBox(NULL, p_message, "Fatal Error", MB_TOPMOST | MB_SETFOREGROUND | MB_ICONWARNING);
	g_racers.Destroy();
	exit(1);
#elif defined(BUILDING_GOL)
	g_fatalErrorMessage(p_message, p_file, p_line);
#endif
}

// FUNCTION: GOLDP 0x100070f0
// STUB: LEGORACERS 0x0042f8f0
void GolFatalError(GolErrorCode p_code, const LegoChar* p_file, LegoS32 p_line)
{
#ifdef BUILDING_LEGORACERS
	STUB(0x42f8f0);
#elif defined(BUILDING_GOL)
	const LegoChar* message;

	switch (p_code) {
	case c_golErrorInvalidCondition:
		message = "Invalid error condition";
		break;
	case c_golErrorGeneral:
		message = "General error occurred";
		break;
	case c_golErrorInvalidParameter:
		message = "Invalid parameter detected";
		break;
	case c_golErrorInvalidValue:
		message = "Invalid value detected";
		break;
	case c_golErrorOutOfMemory:
		message = "Out of memory error occured";
		break;
	case c_golErrorCriticalResource:
		message = "Critical resource busy";
		break;
	default:
		message = "Unknown error condition occured";
		break;
	}

	g_fatalErrorMessage(message, p_file, p_line);
#endif
}

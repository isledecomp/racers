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
	g_unk0x4c4a38.FUN_0042be90();
	MessageBox(NULL, p_message, "Fatal Error", MB_TOPMOST | MB_SETFOREGROUND | MB_ICONWARNING);
	g_unk0x4c4a38.FUN_0042bc20();
	exit(1);
#elif defined(BUILDING_GOL)
	g_fatalErrorMessage(p_message, p_file, p_line);
#endif
}

// STUB: GOLDP 0x100070f0
// STUB: LEGORACERS 0x0042f8f0
void GolFatalError(GolErrorCode p_code, const LegoChar* p_file, LegoS32 p_line)
{
	// TODO
	STUB(0x42f8f0);
}

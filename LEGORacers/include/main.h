#ifndef MAIN_H
#define MAIN_H

#include "neoncactus0x1d6c.h"
#include "types.h"

// SIZE 0x84
struct CommandLineArgs {
	LegoS32 m_argc;       // 0x00
	LegoChar* m_argv[32]; // 0x04
};

extern NeonCactus0x1d6c g_unk0x4c4a38;

#endif // MAIN_H

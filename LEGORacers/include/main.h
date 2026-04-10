#ifndef MAIN_H
#define MAIN_H

#include "types.h"

// SIZE 0x84
struct CommandLineArgs {
	LegoS32 m_argc;       // 0x00
	LegoChar* m_argv[32]; // 0x04
};

#endif // MAIN_H

#include "main.h"

// FUNCTION: LEGORACERS 0x0042f870
LegoS32 GameMain(LegoS32 p_argc, LegoChar** p_argv)
{
	if (!g_racers.Initialize(p_argc, p_argv)) {
		return 1;
	}

	g_racers.Run();
	g_racers.Destroy();
	return 0;
}

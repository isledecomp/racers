#include "menu/screens/racemodesetupscreen.h"

// FUNCTION: LEGORACERS 0x004246d0
LegoU32 RaceModeSetupScreen::FUN_004246d0(LegoChar* p_buffer, LegoU32 p_time)
{
	LegoU32 millisecondsPerHour = 3600000;
	LegoS32 divisor = 10;
	LegoU32 time = p_time % millisecondsPerHour;
	LegoS32 digitOffset;

	p_buffer[8] = '\0';
	if (time >= 600000) {
		digitOffset = 7;
		p_buffer[5] = ':';
		p_buffer[2] = ':';
	}
	else {
		digitOffset = 6;
		p_buffer[4] = ':';
		p_buffer[1] = ':';
		p_buffer[7] = '\0';
	}

	LegoU32 centiseconds = time / 10;
	p_buffer[digitOffset] = static_cast<LegoChar>(centiseconds % 10 + '0');
	centiseconds /= 10;
	p_buffer[digitOffset - 1] = static_cast<LegoChar>(centiseconds % 10 + '0');

	LegoU32 seconds = centiseconds / divisor;
	LegoS32 secondsWithinMinute = static_cast<LegoS32>(seconds % 60);
	LegoU32 minutes = seconds / 60;
	p_buffer[digitOffset - 3] = static_cast<LegoChar>(secondsWithinMinute % divisor + '0');
	p_buffer[digitOffset - 4] = static_cast<LegoChar>((secondsWithinMinute / divisor) % divisor + '0');

	p_buffer[digitOffset - 6] = static_cast<LegoChar>(minutes % divisor + '0');
	LegoU32 extraMinutes = minutes / divisor;
	if (extraMinutes) {
		p_buffer[digitOffset - 7] = static_cast<LegoChar>(extraMinutes % divisor + '0');
		extraMinutes /= divisor;
	}

	return extraMinutes;
}

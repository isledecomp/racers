#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "ironflame0x944.h"
#include "types.h"

#include <windows.h>

class VideoPlayer {
public:
	static int FUN_004a60c0(IronFlame0x944* p_unk0x04, DWORD p_width, DWORD p_height);
	static int FUN_004a61c0(IronFlame0x944* p_unk0x04, LPCSTR p_filename, int p_unk0x08, int p_unk0x0c);
	static int FUN_004a61e0(IronFlame0x944* p_unk0x04);
};

#endif // VIDEOPLAYER_H

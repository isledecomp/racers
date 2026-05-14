#ifndef CHROMESPIKE0X4_H
#define CHROMESPIKE0X4_H

#include "decomp.h"
#include "imaginarytool0x368.h"
#include "types.h"

// SIZE 0x4
class ChromeSpike0x4 {
public:
	ChromeSpike0x4();
	~ChromeSpike0x4();
	LegoBool32 Shutdown();
	LegoBool32 Initialize();
	ImaginaryTool0x368* FUN_0047f4e0(LegoU16 p_menuId);

private:
	undefined m_unk0x00[0x4 - 0x00]; // 0x00
};

#endif // CHROMESPIKE0X4_H

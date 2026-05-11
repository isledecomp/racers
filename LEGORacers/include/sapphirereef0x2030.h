#ifndef SAPPHIREREEF0X2030_H
#define SAPPHIREREEF0X2030_H

#include "decomp.h"
#include "types.h"

// SIZE 0x2030
class SapphireReef0x2030 {
public:
	SapphireReef0x2030();
	~SapphireReef0x2030();
	LegoBool32 FUN_0049a0e0();
	void Destroy();

private:
	undefined4 m_unk0x00;               // 0x0000
	undefined m_unk0x04[0x2030 - 0x04]; // 0x0004
};

#endif // SAPPHIREREEF0X2030_H

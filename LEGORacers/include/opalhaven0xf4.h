#ifndef OPALHAVEN0XF4_H
#define OPALHAVEN0XF4_H

#include "decomp.h"
#include "silverhollow0xb8.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af5ec
// SIZE 0xf4
class OpalHaven0xf4 : public SilverHollow0xb8 {
public:
	OpalHaven0xf4();

private:
	void Reset();

	undefined4 m_unk0xb8;             // 0xb8
	undefined2 m_unk0xbc;             // 0xbc
	undefined m_unk0xbe[0xd0 - 0xbe]; // 0xbe
	undefined4 m_unk0xd0;             // 0xd0
	undefined4 m_unk0xd4;             // 0xd4
	undefined2 m_unk0xd8;             // 0xd8
	undefined m_unk0xda[0xec - 0xda]; // 0xda
	undefined4 m_unk0xec;             // 0xec
	undefined4 m_unk0xf0;             // 0xf0
};

#endif // OPALHAVEN0XF4_H

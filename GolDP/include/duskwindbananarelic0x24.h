#ifndef DUSKWINDBANANARELIC0x24_H
#define DUSKWINDBANANARELIC0x24_H

#include "decomp.h"
#include "types.h"

// SIZE 0x08
struct DuskwindBananaRelicColor {
	DuskwindBananaRelicColor(undefined4 p_arg0, undefined4 p_arg1, undefined4 p_arg2, undefined4 p_arg3)
	{
		m_unk0x0 = p_arg0;
		m_unk0x1 = p_arg1;
		m_unk0x2 = p_arg2;
		m_unk0x3 = p_arg3;
	}
	undefined m_unk0x0; // 0x0
	undefined m_unk0x1; // 0x1
	undefined m_unk0x2; // 0x2
	undefined m_unk0x3; // 0x3
};

// VTABLE: GOLDP 0x10057030
// SIZE 0x24
class DuskwindBananaRelic0x24 {
public:
	DuskwindBananaRelic0x24();
	virtual ~DuskwindBananaRelic0x24(); // vtable+0x00

	// SYNTHETIC: GOLDP 0x100257b0
	// DuskwindBananaRelic0x24::`scalar deleting destructor'

protected:
	enum {
		c_flagBit0 = 1 << 0,
	};

	undefined4 m_unk0x04;
	LegoU32 m_unk0x08;
	DuskwindBananaRelicColor m_unk0x0c;
	DuskwindBananaRelicColor m_unk0x10;
	undefined4 m_unk0x14;
	undefined m_unk0x18[0x20 - 0x18];
	undefined m_unk0x20;
	undefined m_unk0x21;
	undefined m_unk0x22;
	undefined m_unk0x23;
};

#endif // DUSKWINDBANANARELIC0x24_H

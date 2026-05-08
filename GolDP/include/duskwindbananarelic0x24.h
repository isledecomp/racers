#ifndef DUSKWINDBANANARELIC0x24_H
#define DUSKWINDBANANARELIC0x24_H

#include "decomp.h"
#include "types.h"

class WhiteFalcon0x140;
class GoldDune0x38;

// SIZE 0x04
struct DuskwindBananaRelicColor {
	DuskwindBananaRelicColor() {}
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

// SIZE 0x14
struct DuskWindBananaRelicParams {
	DuskWindBananaRelicParams() {}
	DuskWindBananaRelicParams(LegoU8 p_fullIntensity);

	LegoU32 m_unk0x00;
	GoldDune0x38* m_unk0x04;
	DuskwindBananaRelicColor m_unk0x08;
	DuskwindBananaRelicColor m_unk0x0c;
	undefined m_unk0x10;
	undefined m_unk0x11;
	undefined m_unk0x12;
	undefined m_unk0x13;
};

// SIZE 0x8
struct DuskWindName0x8 {
	LegoChar m_unk0x0[8];
};

// VTABLE: GOLDP 0x10057030
// SIZE 0x24
class DuskwindBananaRelic0x24 {
public:
	enum {
		c_flagBit0 = 1 << 0,
		c_flagBit7 = 1 << 7,
		c_flagBit8 = 1 << 8,
		c_flagBit9 = 1 << 9,
		c_flagBit11 = 1 << 11,
		c_flagBit12 = 1 << 12,
		c_flagBit14 = 1 << 14,
	};

	enum {
		c_flag0x08Bit1 = 1 << 1,
		c_flag0x08Bit2 = 1 << 2,
		c_flag0x08Bit3 = 1 << 3,
		c_flag0x08Bit4 = 1 << 4,
		c_flag0x08Bit5 = 1 << 5,
		c_flag0x08Bit6 = 1 << 6,
		c_flag0x08Bit7 = 1 << 7,
		c_flag0x08Bit8 = 1 << 8,
		c_flag0x08Bit9 = 1 << 9,
		c_flag0x08Bit10 = 1 << 10,
		c_flag0x08Bit11 = 1 << 11,
		c_flag0x08Bit12 = 1 << 12,
		c_flag0x08Bit13 = 1 << 13,
		c_flag0x08Bit14 = 1 << 14,
		c_flag0x08Bit15 = 1 << 15,
		c_flag0x08Bit16 = 1 << 16,
		c_flag0x08Bit17 = 1 << 17,
		c_flag0x08Bit19 = 1 << 19,
		c_flag0x08Bit20 = 1 << 20,
		c_flag0x08Bit21 = 1 << 21,
		c_flag0x08Bit22 = 1 << 22,
	};

	DuskwindBananaRelic0x24();
	virtual ~DuskwindBananaRelic0x24(); // vtable+0x00

	GoldDune0x38* GetUnk0x04() const { return m_unk0x04; }
	LegoU32 GetUnk0x08() const { return m_unk0x08; }
	const DuskwindBananaRelicColor& GetColor0x0c() const { return m_unk0x0c; }
	const DuskwindBananaRelicColor& GetColor0x10() const { return m_unk0x10; }
	undefined GetAlphaFunc() const { return m_unk0x20; }
	undefined GetAlphaRef() const { return m_unk0x21; }
	undefined GetSrcBlend() const { return m_unk0x22; }
	undefined GetDestBlend() const { return m_unk0x23; }
	// SYNTHETIC: GOLDP 0x100257b0
	// DuskwindBananaRelic0x24::`scalar deleting destructor'

	void FUN_100257e0(WhiteFalcon0x140*, const DuskWindBananaRelicParams&);

	friend class AmberHaze0x1c;

protected:
	GoldDune0x38* m_unk0x04;
	LegoU32 m_unk0x08;
	DuskwindBananaRelicColor m_unk0x0c;
	DuskwindBananaRelicColor m_unk0x10;
	undefined4 m_unk0x14;
	DuskWindName0x8 m_unk0x18;
	undefined m_unk0x20;
	undefined m_unk0x21;
	undefined m_unk0x22;
	undefined m_unk0x23;
};

inline DuskWindBananaRelicParams::DuskWindBananaRelicParams(LegoU8 p_fullIntensity)
{
	m_unk0x0c.m_unk0x0 = p_fullIntensity;
	m_unk0x0c.m_unk0x1 = p_fullIntensity;
	m_unk0x0c.m_unk0x2 = p_fullIntensity;
	m_unk0x0c.m_unk0x3 = p_fullIntensity;
	m_unk0x08.m_unk0x0 = p_fullIntensity;
	m_unk0x08.m_unk0x1 = p_fullIntensity;
	m_unk0x08.m_unk0x2 = p_fullIntensity;
	m_unk0x08.m_unk0x3 = p_fullIntensity;
	m_unk0x00 = DuskwindBananaRelic0x24::c_flag0x08Bit2 | DuskwindBananaRelic0x24::c_flag0x08Bit4 |
				DuskwindBananaRelic0x24::c_flag0x08Bit7 | DuskwindBananaRelic0x24::c_flag0x08Bit9 |
				DuskwindBananaRelic0x24::c_flag0x08Bit10 | DuskwindBananaRelic0x24::c_flag0x08Bit13 |
				DuskwindBananaRelic0x24::c_flag0x08Bit15 | DuskwindBananaRelic0x24::c_flag0x08Bit20 |
				DuskwindBananaRelic0x24::c_flag0x08Bit22;
	m_unk0x04 = NULL;
	m_unk0x10 = 2;
	m_unk0x11 = 0;
	m_unk0x12 = 1;
	m_unk0x13 = 0;
}

#endif // DUSKWINDBANANARELIC0x24_H

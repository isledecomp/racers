#include "golfontbase0x40.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GolFontBase0x40, 0x40)

// FUNCTION: GOLDP 0x1001dea0
GolFontBase0x40::GolFontBase0x40()
{
	m_unk0x04 = 0;
	m_unk0x1c = 0;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_unk0x18 = 0;
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
	m_unk0x30 = 0;
	m_unk0x2c = 0;
	m_unk0x20 = 0;
}

// FUNCTION: GOLDP 0x1001df40
GolFontBase0x40::~GolFontBase0x40()
{
	Clear();
}

// FUNCTION: GOLDP 0x1001e030
void GolFontBase0x40::Clear()
{
	if (m_unk0x28 != NULL) {
		delete m_unk0x28;
		m_unk0x28 = NULL;
	}

	m_unk0x04 = 0;
	m_unk0x1c = 0;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_unk0x18 = 0;
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
}

// STUB: GOLDP 0x1001e070
void GolFontBase0x40::VTable0x00(undefined4, undefined4)
{
	// TODO
	STUB(0x1001e070);
}

// STUB: GOLDP 0x1001eaa0
undefined4 GolFontBase0x40::FUN_1001eaa0(
	undefined4,
	WhiteFalcon0x140*,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4
)
{
	// TODO
	STUB(0x1001eaa0);
	return 0;
}

// STUB: GOLDP 0x1001eb70
undefined4 GolFontBase0x40::FUN_1001eb70(
	undefined4,
	WhiteFalcon0x140*,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4
)
{
	// TODO
	STUB(0x1001eb70);
	return 0;
}

// STUB: GOLDP 0x1001eca0
undefined4 GolFontBase0x40::FUN_1001eca0(
	undefined4,
	WhiteFalcon0x140*,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4
)
{
	// TODO
	STUB(0x1001eca0);
	return 0;
}

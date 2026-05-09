#include "utopianpan0xa4.h"

#include "duskwindbananarelic0x30.h"
#include "rectangle.h"

DECOMP_SIZE_ASSERT(UtopianPan0xa4, 0xa4)

// FUNCTION: GOLDP 0x10004fd0
UtopianPan0xa4::UtopianPan0xa4()
{
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x50 = 0;
}

// FUNCTION: GOLDP 0x10005040
UtopianPan0xa4::~UtopianPan0xa4()
{
	FUN_100051c0();
	m_unk0x58.VTable0x38();
	WhiteBaffoon0x50::Reset();
}

// STUB: GOLDP 0x100050b0
void UtopianPan0xa4::VTable0x10()
{
	// TODO
	STUB(0x100050b0);
}

// STUB: GOLDP 0x100051c0
void UtopianPan0xa4::FUN_100051c0()
{
	// TODO
	STUB(0x100051c0);
}

// STUB: GOLDP 0x10005210
void UtopianPan0xa4::FUN_10005210()
{
	// TODO
	STUB(0x10005210);
}

// STUB: GOLDP 0x10005260
void UtopianPan0xa4::Reset()
{
	// TODO
	STUB(0x10005260);
}

// STUB: GOLDP 0x10005280
void UtopianPan0xa4::VTable0x00()
{
	// TODO
	STUB(0x10005280);
}

// STUB: GOLDP 0x100052b0
void UtopianPan0xa4::VTable0x04()
{
	// TODO
	STUB(0x100052b0);
}

// STUB: GOLDP 0x100052e0
void UtopianPan0xa4::VTable0x08()
{
	undefined4 count = m_unk0x30 * m_unk0x2c;
	// ...
	m_unk0x54 = new DuskwindBananaRelic0x30[count];
	// TODO
	STUB(0x100052e0);
}

// STUB: GOLDP 0x100053d0
void UtopianPan0xa4::VTable0x0c(undefined4, undefined4, undefined4*)
{
	// TODO
	STUB(0x100053d0);
}

// STUB: GOLDP 0x10005440
void UtopianPan0xa4::FUN_10005440(undefined4*, undefined4*, undefined4*)
{
	// TODO
	STUB(0x10005440);
}

// FUNCTION: GOLDP 0x100054d0
void UtopianPan0xa4::FUN_100054d0(
	BronzeFalcon0xc8770* p_renderer,
	undefined4 p_unk0x08,
	Rect* p_destRect,
	undefined4 p_unk0x14
)
{
	Rect sourceRect;
	sourceRect.m_left = 0;
	sourceRect.m_top = 0;
	sourceRect.m_right = m_unk0x34;
	sourceRect.m_bottom = m_unk0x38;

	FUN_10005510(p_renderer, p_unk0x08, p_destRect, &sourceRect, p_unk0x14);
}

// STUB: GOLDP 0x10005510
undefined4 UtopianPan0xa4::FUN_10005510(BronzeFalcon0xc8770*, undefined4, Rect*, Rect*, undefined4)
{
	// TODO
	STUB(0x10005510);
	return 0;
}

// STUB: GOLDP 0x10005ae0
undefined4 UtopianPan0xa4::VTable0x1c(undefined4, undefined4)
{
	// TODO
	STUB(0x10005ae0);
	return 0;
}

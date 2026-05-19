#include "obscuresigil0xdc.h"

#include "amberlens0x344.h"
#include "bronzefalcon0xc8770.h"
#include "gol.h"
#include "golerror.h"
#include "zoweeblubberworth0xf0.h"

DECOMP_SIZE_ASSERT(ObscureSigil0xdc, 0xdc)
DECOMP_SIZE_ASSERT(ObscureSigil0xdc::CreateParams0x84, 0x84)

// FUNCTION: LEGORACERS 0x004656e0
ObscureSigil0xdc::ObscureSigil0xdc()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00465750
ObscureSigil0xdc::~ObscureSigil0xdc()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x004657a0
void ObscureSigil0xdc::Reset()
{
	m_unk0x88 = 5;
	m_unk0x5c = 0;
	m_unk0x64 = 0;
	m_unk0x60 = 0;
	m_unk0x68 = 0;
	m_unk0x58 = NULL;
	m_unk0x6c = 0;
	m_unk0xb4 = 0;
	m_unk0xb8 = 0;
	m_unk0xbc = 0;
	m_unk0xc0 = 0;
	m_unk0xc4 = 0;
	m_unk0xc8 = 0;
	m_unk0xcc = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xd8 = 0;
	m_unk0x94 = 0;
	m_unk0x90 = 0;
	m_unk0x98 = -1;

	ObscureVantage0x58::Reset();
}

// FUNCTION: LEGORACERS 0x00465820
LegoBool32 ObscureSigil0xdc::FUN_00465820(CreateParams0x84* p_createParams, undefined4 p_unk0x08)
{
	VTable0x08();
	m_unk0x88 = p_createParams->m_unk0x78;

	if (p_createParams->m_parent) {
		if (!p_createParams->m_rect.m_right) {
			p_createParams->m_rect.m_right =
				p_createParams->m_parent->GetRect()->m_right - p_createParams->m_parent->GetRect()->m_left;
		}

		if (!p_createParams->m_rect.m_bottom) {
			p_createParams->m_rect.m_bottom =
				p_createParams->m_parent->GetRect()->m_bottom - p_createParams->m_parent->GetRect()->m_top;
		}
	}

	if (FUN_00472a60(p_createParams)) {
		FUN_00465900(p_createParams, p_unk0x08);
		FUN_004659b0(p_createParams);
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00465890
LegoBool32 ObscureSigil0xdc::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		if (m_unk0x64 && m_unk0x5c && !m_unk0x5c->GetUnk0x7c()) {
			m_golExport->VTable0x54(m_unk0x64);
		}

		if (m_unk0x5c) {
			m_unk0x5c->VTable0x18();
			m_golExport->VTable0x3c(m_unk0x5c);
		}

		if (m_unk0x60) {
			m_unk0x60->VTable0x18();
			m_golExport->VTable0x3c(m_unk0x60);
		}

		result = ObscureVantage0x58::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00465900
void ObscureSigil0xdc::FUN_00465900(CreateParams0x84* p_createParams, undefined4 p_binary)
{
	m_unk0x6c = p_createParams->m_unk0x70;
	m_unk0x8c = p_createParams->m_unk0x5c;

	m_unk0x5c = m_golExport->VTable0x08();
	if (!m_unk0x5c) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x5c->VTable0x14(m_renderer, p_createParams->m_unk0x60, p_binary, m_unk0x8c);

	if (p_createParams->m_unk0x74) {
		m_unk0x60 = m_golExport->VTable0x08();
		if (!m_unk0x60) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_unk0x60->VTable0x14(m_renderer, "blended", p_binary, m_unk0x8c);
	}

	ColorRGBA color = {0, 0, 0, 0};
	m_renderer->VTable0x1c(color);
}

// STUB: LEGORACERS 0x004659b0
void ObscureSigil0xdc::FUN_004659b0(CreateParams0x84*)
{
	STUB(0x004659b0);
}

// FUNCTION: LEGORACERS 0x00465b40
ObscureLink0x1c* ObscureSigil0xdc::FUN_00465b40(ObscureLink0x1c* p_unk0x04)
{
	if (!m_unk0x58) {
		m_unk0x58 = p_unk0x04;
		return p_unk0x04;
	}

	return p_unk0x04->FUN_0046b350(m_unk0x58);
}

// STUB: LEGORACERS 0x00465f20
undefined4 ObscureSigil0xdc::VTable0x38(Rect*, Rect*)
{
	STUB(0x00465f20);
	return 0;
}

// FUNCTION: LEGORACERS 0x00465fe0
ObscureVantage0x58* ObscureSigil0xdc::VTable0x30(OnyxCircularBuffer0x1c::Item* p_item, undefined4 p_x, undefined4 p_y)
{
	if (m_unk0x28 && m_unk0x28->VTable0x18(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00466010
ObscureVantage0x58* ObscureSigil0xdc::VTable0x34(OnyxCircularBuffer0x1c::Item* p_item, undefined4 p_x, undefined4 p_y)
{
	if (m_unk0x28 && m_unk0x28->VTable0x1c(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}

// STUB: LEGORACERS 0x00466040
undefined4 ObscureSigil0xdc::VTable0x3c(undefined4)
{
	STUB(0x00466040);
	return 0;
}

// Keep this fold pair out of the unrelated ObscureVantage0x58 null-return fold group.
#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
ObscureVantage0x58* ObscureSigil0xdc::VTable0x2c(void*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()

#include "obscuresigil0xdc.h"

#include "amberlens0x344.h"
#include "amberlensbase0x120.h"
#include "bronzefalcon0xc8770.h"
#include "gol.h"
#include "golerror.h"
#include "slatepeak0x58.h"
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

// FUNCTION: LEGORACERS 0x004659b0
void ObscureSigil0xdc::FUN_004659b0(CreateParams0x84* p_createParams)
{
	if (m_unk0x5c->GetUnk0x7c()) {
		m_unk0x64 = static_cast<AmberLens0x344*>(m_unk0x5c->VTable0x50(0));
	}
	else {
		GolVec3* cameraVectors = &p_createParams->m_unk0x38;
		m_unk0x64 = m_golExport->VTable0x20();
		if (!m_unk0x64) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		LegoU32 dirtyFlag = AmberLens0x344::c_flagBit1;
		AmberLens0x344* lens = m_unk0x64;
		LegoFloat value = cameraVectors[2].m_x;
		lens->m_unk0x08 = value;
		lens->m_flags |= dirtyFlag;
		lens = m_unk0x64;
		value = cameraVectors[2].m_y;
		lens->m_unk0x10 = value;
		lens->m_flags |= dirtyFlag;
		lens = m_unk0x64;
		value = cameraVectors[2].m_z;
		lens->m_unk0x14 = value;
		lens->m_flags |= dirtyFlag;

		FUN_00465ab0(cameraVectors, cameraVectors + 1);
	}

	Rect rect = *GetGlobalRect();
	FUN_00465e40(&rect);

	LegoS32 width = rect.m_right;
	width -= rect.m_left;
	LegoS32 height = rect.m_bottom;
	height -= rect.m_top;

	LegoFloat aspect = static_cast<LegoFloat>(width);
	LegoFloat divisor = static_cast<LegoFloat>(height);
	aspect /= divisor;
	aspect *= p_createParams->m_unk0x80;
	m_unk0x64->FUN_00404740(aspect);
}

// FUNCTION: LEGORACERS 0x00465ab0
void ObscureSigil0xdc::FUN_00465ab0(GolVec3* p_unk0x04, GolVec3* p_unk0x08)
{
	GolVec3 up;
	up.m_y = 0.0f;
	up.m_x = 0.0f;
	up.m_z = 1.0f;

	if (p_unk0x04) {
		LegoFloat scale = m_unk0x8c;
		m_unk0x70.m_x = scale * p_unk0x04->m_x;
		LegoFloat y = p_unk0x04->m_y;
		m_unk0x70.m_y = y * scale;
		LegoFloat z = p_unk0x04->m_z;
		m_unk0x70.m_z = z * scale;
	}

	if (p_unk0x08) {
		LegoFloat scale = m_unk0x8c;
		m_unk0x7c.m_x = scale * p_unk0x08->m_x;
		LegoFloat y = p_unk0x08->m_y;
		m_unk0x7c.m_y = y * scale;
		LegoFloat z = p_unk0x08->m_z;
		m_unk0x7c.m_z = z * scale;
	}

	m_unk0x64->FUN_004046a0(&m_unk0x70, &m_unk0x7c, &up);
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

// FUNCTION: LEGORACERS 0x00465e40
void ObscureSigil0xdc::FUN_00465e40(Rect* p_rect)
{
	const SlatePeak0x58* renderTarget = m_renderer->GetRenderTargetInfo();

	if (p_rect->m_left < 0) {
		p_rect->m_left = 0;
	}

	LegoS32 width = renderTarget->GetWidth();
	if (p_rect->m_right > width) {
		p_rect->m_right = width;
	}

	if (p_rect->m_top < 0) {
		p_rect->m_top = 0;
	}

	LegoS32 height = renderTarget->GetHeight();
	if (p_rect->m_bottom > height) {
		p_rect->m_bottom = height;
	}

	m_unk0x64->VTable0x0c(p_rect);
}

// FUNCTION: LEGORACERS 0x00465ea0
void ObscureSigil0xdc::FUN_00465ea0()
{
	if (m_unk0x5c->GetUnk0x84() || m_unk0x5c->GetUnk0x8c()) {
		m_renderer->VTable0x28();

		if (m_unk0x5c->GetUnk0x84()) {
			m_renderer->VTable0x2c(m_unk0x5c->GetUnk0xac());
		}

		for (LegoU32 i = 0; i < m_unk0x5c->GetUnk0x8c(); i++) {
			m_renderer->VTable0x30(&m_unk0x5c->GetUnk0xb0()[i]);
		}

		m_renderer->VTable0x60();
	}
}

// FUNCTION: LEGORACERS 0x00465f20
undefined4 ObscureSigil0xdc::VTable0x38(Rect*, Rect*)
{
	m_renderer->VTable0xe4();
	m_unk0x68 = m_renderer->GetUnk0x0c();
	m_renderer->VTable0x20(m_unk0x64);
	m_renderer->VTable0x5c();
	m_renderer->VTable0xec(m_unk0x88);
	FUN_00465ea0();

	if (m_unk0x6c || !m_unk0x58) {
		m_unk0x5c->FUN_00416040();
	}

	for (ObscureLink0x1c* link = m_unk0x58; link; link = link->GetNext()) {
		link->VTable0x0c();
	}

	if (m_unk0x6c && m_unk0x60) {
		m_unk0x60->FUN_00416040();
	}

	m_renderer->VTable0x20(m_unk0x68);
	m_renderer->VTable0x5c();
	m_renderer->VTable0xec(6);
	m_renderer->VTable0xe8(FALSE);

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

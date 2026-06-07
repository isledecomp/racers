#include "core/gol.h"
#include "decomp.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/screens/imaginaryshape0x2b20.h"

DECOMP_SIZE_ASSERT(ImaginaryShape0x2b20::FieldAt0x2308, 0x2d0)
DECOMP_SIZE_ASSERT(ImaginaryShape0x2b20::FieldAt0x2308::CreateParams0x30, 0x30)

// GLOBAL: LEGORACERS 0x004c7668
LegoFloat g_fieldAt0x2308AngleStep = 0.0f;

// FUNCTION: LEGORACERS 0x004778f0
ImaginaryShape0x2b20::FieldAt0x2308::FieldAt0x2308()
{
	LegoFloat angle = 1.57f;

	for (LegoS32 i = 0; i < 8; i++) {
		m_unk0x2a8[i] = angle;
		angle += g_fieldAt0x2308AngleStep;
		if (angle >= g_siennaCircuitTwoPi) {
			angle -= g_siennaCircuitTwoPi;
		}
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x004779d0
ImaginaryShape0x2b20::FieldAt0x2308::~FieldAt0x2308()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00477a40
void ImaginaryShape0x2b20::FieldAt0x2308::Reset()
{
	m_unk0x244 = 1;
	m_unk0x250.m_z = 0.0f;
	m_unk0x250.m_y = 0.0f;
	m_unk0x250.m_x = 0.0f;
	m_unk0x24 = NULL;
	m_unk0x238 = NULL;
	m_unk0x19c = NULL;
	m_unk0x1c = NULL;
	m_unk0x240 = 0;
	m_unk0x248 = 0;
	m_unk0x298 = 0;
	m_unk0x264 = 0;
	m_unk0x268 = 0;
	m_unk0x278 = FALSE;
	m_unk0x26c = 0;
	m_unk0x270 = 0;
	m_unk0x274 = 0;
	m_unk0x290 = FALSE;
	m_unk0x28c = 0;
	m_unk0x29c = 0;
	m_unk0x2a0 = 0;
	m_unk0x2a4 = 0;
	m_unk0x288 = 0;
	m_unk0x2c8 = 0;
	m_unk0x294 = 0;
	m_unk0x2cc = 0;
}

// FUNCTION: LEGORACERS 0x00477ae0
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_00477ae0(CreateParams0x30* p_createParams)
{
	VTable0x08();

	m_unk0x1c = p_createParams->m_screen;
	m_unk0x20 = p_createParams->m_soundGroupBinding;
	m_unk0x24 = p_createParams->m_context;
	m_unk0x250.m_x = p_createParams->m_unk0x1c.m_x;
	m_unk0x250.m_y = p_createParams->m_unk0x1c.m_y;
	m_unk0x250.m_z = p_createParams->m_unk0x1c.m_z;

	if (ObscureLink0x1c::FUN_0046b300(p_createParams)) {
		FUN_00477cc0(p_createParams->m_unk0x2c);
		FUN_00477dc0();
		FUN_00477bf0();
		FUN_00477c50();
		m_unk0x28.FUN_004513d0(&m_unk0x24->m_unk0x21f4);
		FUN_00477f00(TRUE);
		FUN_004784d0(FALSE);
	}

	return m_unk0x18;
}

// FUNCTION: LEGORACERS 0x00477b80
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::VTable0x08()
{
	if (!m_unk0x18) {
		return TRUE;
	}

	if (m_unk0x1a4.HasModel()) {
		m_unk0x0c->VTable0x48(m_unk0x234);
	}

	m_unk0xa8.VTable0x54();

	if (m_unk0x19c) {
		m_unk0x0c->VTable0x4c(m_unk0x19c);
	}

	if (m_unk0x238) {
		m_unk0x0c->VTable0x48(m_unk0x238);
	}

	return ObscureLink0x1c::VTable0x08();
}

// STUB: LEGORACERS 0x00477bf0
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00477bf0()
{
	STUB(0x00477bf0);
}

// STUB: LEGORACERS 0x00477c50
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00477c50()
{
	STUB(0x00477c50);
}

// STUB: LEGORACERS 0x00477cc0
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00477cc0(undefined4)
{
	STUB(0x00477cc0);
}

// STUB: LEGORACERS 0x00477dc0
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00477dc0()
{
	STUB(0x00477dc0);
}

// FUNCTION: LEGORACERS 0x00477e40
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00477e40(LegoS32 p_unk0x04)
{
	TopazBurst0x14::Entry* entry = m_unk0x24->m_unk0x21a4.GetUnk0x10();
	LegoS32 colorRecordIndex;
	m_unk0x25c = p_unk0x04;
	entry->GetChoice(p_unk0x04, &p_unk0x04, &colorRecordIndex);

	LegoPieceLibrary::PieceRecord* pieceRecord = m_unk0x24->m_pieceLibrary.FindPieceRecord(p_unk0x04, TRUE);
	m_unk0x28.FUN_00499890(pieceRecord, colorRecordIndex, entry->GetUnk0x08());

	LegoS32 x;
	LegoS32 y;
	LegoS32 rotation;
	m_unk0x28.FUN_00499ca0(&x, &y, &rotation);

	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
	m_unk0x240 = 1;
}

// FUNCTION: LEGORACERS 0x00477f00
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00477f00(LegoS32 p_unk0x04)
{
	m_unk0x298 = static_cast<LegoS8>(p_unk0x04);
	m_unk0x2c8 = static_cast<LegoFloat>(p_unk0x04);
	FUN_00477f30(m_unk0x2a8[m_unk0x298]);
}

// STUB: LEGORACERS 0x00477f30
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00477f30(LegoFloat)
{
	STUB(0x00477f30);
}

// STUB: LEGORACERS 0x00477fc0
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_00477fc0(LegoFloat)
{
	STUB(0x00477fc0);
	return FALSE;
}

// STUB: LEGORACERS 0x00478080
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_00478080(LegoS32, LegoBool32)
{
	STUB(0x00478080);
	return FALSE;
}

// STUB: LEGORACERS 0x00478120
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00478120()
{
	STUB(0x00478120);
}

// STUB: LEGORACERS 0x00478180
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_00478180(LegoFloat)
{
	STUB(0x00478180);
	return FALSE;
}

// STUB: LEGORACERS 0x004782f0
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_004782f0(LegoS32, LegoBool32)
{
	STUB(0x004782f0);
	return FALSE;
}

// STUB: LEGORACERS 0x004783d0
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_004783d0()
{
	STUB(0x004783d0);
}

// STUB: LEGORACERS 0x004784d0
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_004784d0(LegoBool32)
{
	STUB(0x004784d0);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x00478560
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00478560()
{
	m_unk0x28.FUN_00499b00();
	m_unk0x24->m_unk0x21f4.FUN_0049b740(TRUE);
	m_unk0x24->m_unk0x21f4.FUN_0049c230(&m_unk0x28, &m_unk0x1a4);
	m_unk0x1a4.VTable0x08(m_unk0x250);
}

// STUB: LEGORACERS 0x004785b0
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_004785b0(LegoS32)
{
	STUB(0x004785b0);
	return FALSE;
}

// STUB: LEGORACERS 0x00478670
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_00478670(LegoS32)
{
	STUB(0x00478670);
	return FALSE;
}

// STUB: LEGORACERS 0x00478730
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_00478730()
{
	STUB(0x00478730);
	return FALSE;
}

// STUB: LEGORACERS 0x004787e0
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::FUN_004787e0(LegoS32*, LegoS32*, LegoS32*)
{
	STUB(0x004787e0);
	return FALSE;
}

// STUB: LEGORACERS 0x004788f0
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::VTable0x0c()
{
	STUB(0x004788f0);
	return FALSE;
}

// STUB: LEGORACERS 0x00478be0
LegoBool32 ImaginaryShape0x2b20::FieldAt0x2308::VTable0x10(undefined4)
{
	STUB(0x00478be0);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004792d0
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_004792d0()
{
	m_unk0x24c = 2000;
	m_unk0x244 = 0;
	m_unk0x248 |= 8;
	m_unk0x274 = m_unk0x270;
}

// FUNCTION: LEGORACERS 0x00479300
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00479300()
{
	m_unk0x294 = 2;
}

// FUNCTION: LEGORACERS 0x00479310
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00479310()
{
	m_unk0x294 = 1;
}

// FUNCTION: LEGORACERS 0x00479320
void ImaginaryShape0x2b20::FieldAt0x2308::FUN_00479320()
{
	m_unk0x294 = 0;
}

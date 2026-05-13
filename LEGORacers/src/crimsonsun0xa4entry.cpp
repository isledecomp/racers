#include "crimsonsun0xa4.h"
#include "porcelainveil0x50.h"

DECOMP_SIZE_ASSERT(CrimsonSun0xa4::Entry0x74c, 0x74c)
DECOMP_SIZE_ASSERT(CrimsonSun0xa4::Entry0x74c::CreateParams0x18, 0x18)

// GLOBAL: LEGORACERS 0x004b2160
const LegoFloat g_unk0x4b2160 = 0.0033333334f;

// FUNCTION: LEGORACERS 0x00468140
CrimsonSun0xa4::Entry0x74c::Entry0x74c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004681b0
CrimsonSun0xa4::Entry0x74c::~Entry0x74c()
{
	Destroy();
}

// STUB: LEGORACERS 0x00468220
void CrimsonSun0xa4::Entry0x74c::Reset()
{
	m_unk0x290 = NULL;
	m_unk0x294 = NULL;
	m_unk0x298 = NULL;
	m_unk0x6c8.SetUnk0x7c(NULL);
	m_unk0x6c8.SetUnk0x80(NULL);
	m_unk0x6c8.SetUnk0x78(NULL);
	m_unk0x2bc = 0;
	m_unk0x2c0 = 0;
	m_unk0x29c = 0;
	m_unk0x2a0 = 0;
	m_unk0x2ac = 0;
	m_unk0x2b0 = 0;
	m_unk0x2b4 = 0;
	m_unk0x2a4 = 0.0f;
	m_unk0x2a8 = 0.0f;
	m_unk0x2c4 = 0;
	m_unk0x2c8 = 0;
	m_unk0x2b8 = 1;
	m_unk0x2cc.VTable0x08();
	m_unk0x6c8.VTable0x08();
	ImaginaryNotion0x290::Reset();
}

// FUNCTION: LEGORACERS 0x004682c0
void CrimsonSun0xa4::Entry0x74c::VTable0x4c()
{
	FUN_0046c050((undefined4*) &m_unk0x2cc, 0x11f, 0x47);
	FUN_0046bf80(&m_unk0x6c8, 0x120, 0x37, m_unk0x2ac);
}

// FUNCTION: LEGORACERS 0x00468300
LegoBool32 CrimsonSun0xa4::Entry0x74c::FUN_00468300(CreateParams0x18* p_createParams)
{
	Destroy();

	m_unk0x290 = p_createParams->m_owner;
	m_unk0x294 = p_createParams->m_createParams->m_menuStyles;
	m_unk0x298 = p_createParams->m_eventHandler;
	p_createParams->m_createParams->m_unk0x20 = NULL;
	m_unk0x2b8 = p_createParams->m_unk0x0c;
	m_unk0x2ac = p_createParams->m_unk0x10;
	m_unk0x2c8 = p_createParams->m_unk0x14;
	m_unk0x2c4 = 0;

	if (!ImaginaryNotion0x290::Initialize(p_createParams->m_createParams)) {
		return FALSE;
	}

	m_unk0x2c0 = 0;
	m_unk0x2bc = 1;
	return TRUE;
}

// STUB: LEGORACERS 0x00468390
void CrimsonSun0xa4::Entry0x74c::FUN_00468390()
{
	Rect rect;
	ObscureIcon0x1a8* icon = m_unk0x6c8.GetUnk0x78();

	icon->VTable0x40(this);

	LegoS32 bottom = icon->GetRect()->m_bottom + 0x14;
	m_unk0x2a8 += bottom * 0.5f;

	rect.m_left = 0x19;
	rect.m_top = m_unk0x6c8.GetRect()->m_bottom + 0x14;
	rect.m_right = bottom + rect.m_top;
	rect.m_bottom = icon->GetRect()->m_right + 0x19;

	icon->VTable0x10(&rect);
	icon->SetParent(&m_unk0x2cc);
	icon->FUN_00471ec0(GetUnk0xd8());
	icon->VTable0x4c(5);
}

// STUB: LEGORACERS 0x00468430
void CrimsonSun0xa4::Entry0x74c::FUN_00468430()
{
	Rect rect;
	ObscureIcon0x1a8* icon = m_unk0x6c8.GetUnk0x7c();

	icon->VTable0x40(this);

	LegoS32 bottom = icon->GetRect()->m_bottom + 0x14;
	m_unk0x2a8 += bottom * 0.5f;

	rect.m_left = 0x19;
	rect.m_top = m_unk0x6c8.GetRect()->m_bottom + 0x14;
	rect.m_right = bottom + rect.m_top;
	rect.m_bottom = icon->GetRect()->m_right + 0x19;

	icon->VTable0x10(&rect);
	icon->SetParent(&m_unk0x2cc);
	icon->FUN_00471ec0(GetUnk0xd8());

	if (m_unk0x2c8) {
		icon->VTable0x4c(5);
	}
}

// STUB: LEGORACERS 0x004684e0
void CrimsonSun0xa4::Entry0x74c::FUN_004684e0()
{
	Rect rect;
	ObscureIcon0x1a8* icon = m_unk0x6c8.GetUnk0x80();

	icon->VTable0x40(this);

	LegoS32 bottom = icon->GetRect()->m_bottom + 0x14;
	m_unk0x2a8 += bottom * 0.5f;

	rect.m_left = 0x19;
	rect.m_top = m_unk0x6c8.GetUnk0x7c()->GetRect()->m_bottom + 0x14;
	rect.m_right = bottom + rect.m_top;
	rect.m_bottom = icon->GetRect()->m_right + 0x19;

	icon->VTable0x10(&rect);
	icon->SetParent(&m_unk0x2cc);
	icon->FUN_00471ec0(GetUnk0xd8());

	if (!m_unk0x2c8) {
		icon->VTable0x4c(5);
	}
}

// STUB: LEGORACERS 0x00468590
void CrimsonSun0xa4::Entry0x74c::FUN_00468590()
{
	Rect rect;

	m_unk0x2a4 = (m_unk0x6c8.GetRect()->m_right + 0x28) * 0.5f;
	m_unk0x2a8 = (m_unk0x6c8.GetRect()->m_bottom + 0x28) * 0.5f;

	rect.m_left = m_unk0x6c8.GetRect()->m_left + 0x14;
	rect.m_top = m_unk0x6c8.GetRect()->m_top + 0x14;
	rect.m_right = m_unk0x6c8.GetRect()->m_right + 0x14;
	rect.m_bottom = m_unk0x6c8.GetRect()->m_bottom + 0x14;
	m_unk0x6c8.VTable0x10(&rect);

	m_unk0x29c = m_unk0xd8.GetRect()->m_right / 2;
	m_unk0x2a0 = m_unk0xd8.GetRect()->m_bottom / 2;

	if (m_unk0x2b8 == 1) {
		FUN_00468390();
	}
	else if (m_unk0x2b8 == 2) {
		FUN_00468430();
		FUN_004684e0();
	}

	FUN_00468740();
}

// FUNCTION: LEGORACERS 0x00468670
void CrimsonSun0xa4::Entry0x74c::VTable0x38(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == m_unk0x6c8.GetUnk0x78()) {
		m_unk0x2c0 = 2;
	}
	else if (p_unk0x04 == m_unk0x6c8.GetUnk0x7c()) {
		m_unk0x2c0 = 3;
	}
	else if (p_unk0x04 == m_unk0x6c8.GetUnk0x80()) {
		m_unk0x2c0 = 4;
	}

	if (m_unk0x298) {
		m_unk0x298->VTable0x38(p_unk0x04);
	}
	else {
		FUN_004687a0();
	}
}

// FUNCTION: LEGORACERS 0x004686d0
CeruleanEmperor0x4c* CrimsonSun0xa4::Entry0x74c::GetMenuStyles()
{
	return m_unk0x294;
}

// FUNCTION: LEGORACERS 0x004686e0
CeruleanQueen0x58* CrimsonSun0xa4::Entry0x74c::GetMenuInputBindings()
{
	return (CeruleanQueen0x58*) m_unk0x290;
}

// STUB: LEGORACERS 0x004686f0
void CrimsonSun0xa4::Entry0x74c::FUN_004686f0()
{
	m_unk0x6c8.SetFlags(2);

	ObscureIcon0x1a8* icon = m_unk0x6c8.GetUnk0x78();
	if (icon && (icon->GetFlags() & 1)) {
		icon->SetFlags(2);
	}

	icon = m_unk0x6c8.GetUnk0x7c();
	if (icon && (icon->GetFlags() & 1)) {
		icon->SetFlags(2);
	}

	icon = m_unk0x6c8.GetUnk0x80();
	if (icon && (icon->GetFlags() & 1)) {
		icon->SetFlags(2);
	}
}

// STUB: LEGORACERS 0x00468740
void CrimsonSun0xa4::Entry0x74c::FUN_00468740()
{
	m_unk0x6c8.ClearFlags(2);

	ObscureIcon0x1a8* icon = m_unk0x6c8.GetUnk0x78();
	if (icon && (icon->GetFlags() & 1)) {
		icon->ClearFlags(2);
	}

	icon = m_unk0x6c8.GetUnk0x7c();
	if (icon && (icon->GetFlags() & 1)) {
		icon->ClearFlags(2);
	}

	icon = m_unk0x6c8.GetUnk0x80();
	if (icon && (icon->GetFlags() & 1)) {
		icon->ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x00468790
undefined4 CrimsonSun0xa4::Entry0x74c::GetUnk0x2c0() const
{
	return m_unk0x2c0;
}

// FUNCTION: LEGORACERS 0x004687a0
void CrimsonSun0xa4::Entry0x74c::FUN_004687a0()
{
	FUN_00468740();

	if (m_unk0x6c8.GetUnk0x78() && (m_unk0x6c8.GetUnk0x78()->GetFlags() & 1)) {
		m_unk0x6c8.GetUnk0x78()->FUN_00471f00();
		m_unk0x6c8.GetUnk0x78()->RemoveFromParent();
	}

	if (m_unk0x6c8.GetUnk0x7c() && (m_unk0x6c8.GetUnk0x7c()->GetFlags() & 1)) {
		m_unk0x6c8.GetUnk0x7c()->FUN_00471f00();
		m_unk0x6c8.GetUnk0x7c()->RemoveFromParent();
	}

	if (m_unk0x6c8.GetUnk0x80() && (m_unk0x6c8.GetUnk0x80()->GetFlags() & 1)) {
		m_unk0x6c8.GetUnk0x80()->FUN_00471f00();
		m_unk0x6c8.GetUnk0x80()->RemoveFromParent();
	}

	m_unk0x2bc = 3;
}

// FUNCTION: LEGORACERS 0x00468820 FOLDED
undefined4 CrimsonSun0xa4::Entry0x74c::VTable0x18(
	ObscureIcon0x1a8*,
	OnyxCircularBuffer0x1c::Item*,
	undefined4,
	undefined4
)
{
	return m_unk0x2bc != 2;
}

// FUNCTION: LEGORACERS 0x00468820 FOLDED
undefined4 CrimsonSun0xa4::Entry0x74c::VTable0x1c(
	ObscureIcon0x1a8*,
	OnyxCircularBuffer0x1c::Item*,
	undefined4,
	undefined4
)
{
	return m_unk0x2bc != 2;
}

// FUNCTION: LEGORACERS 0x00468840
LegoBool32 CrimsonSun0xa4::Entry0x74c::VTable0x7c(Rect* p_arg1, Rect* p_arg2)
{
	return ImaginaryNotion0x290::VTable0x7c(p_arg1, p_arg2);
}

// STUB: LEGORACERS 0x00468860
LegoBool32 CrimsonSun0xa4::Entry0x74c::VTable0x78(undefined4 p_elapsedMs)
{
	LegoFloat scale = 1.0f;
	m_unk0x2b0 += p_elapsedMs;

	if (!m_unk0x2b8 && m_unk0x2b0 > 5000) {
		m_unk0x2c0 = 1;
		FUN_004687a0();
	}

	if (m_unk0x2bc == 1 || m_unk0x2bc == 3) {
		m_unk0x2b4 += p_elapsedMs;
		scale = m_unk0x2b4 * g_unk0x4b2160;

		if (m_unk0x2b4 > 300) {
			if (m_unk0x2bc == 1) {
				FUN_004686f0();
				m_unk0x2b4 = 0;
				m_unk0x2bc = 2;
			}
			else {
				m_unk0x2b4 = 0;
				m_unk0x2bc = 0;
				m_unk0x2c4 = 1;
			}
		}

		if (m_unk0x2bc == 3) {
			scale = 1.0f - scale;
		}

		if (scale > 1.0f) {
			scale = 1.0f;
		}
		else if (scale < 0.0f) {
			scale = 0.0f;
		}
	}

	LegoS32 x = (LegoS32) (m_unk0x2a4 * scale);
	LegoS32 y = (LegoS32) (m_unk0x2a8 * scale);

	Rect rect;
	rect.m_right = m_unk0x29c + x;
	rect.m_left = m_unk0x29c - x;
	rect.m_bottom = m_unk0x2a0 + y;
	rect.m_top = m_unk0x2a0 - y;
	m_unk0x2cc.VTable0x10(&rect);

	return m_unk0x2c4 == 0;
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
undefined4 CrimsonSun0xa4::Entry0x74c::VTable0x50()
{
	return 0;
}

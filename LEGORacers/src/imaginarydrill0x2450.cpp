#include "imaginarydrill0x2450.h"

#include "audio/soundgroupbinding.h"
#include "crimsonsun0xa4.h"
#include "input/inputmanager.h"
#include "menutoolcontext0x4bc8.h"
#include "menutoolcreateparams0x30.h"
#include "sapphirereef0x2030.h"
#include "turquoiseglow0x80.h"

DECOMP_SIZE_ASSERT(ImaginaryDrill0x2450, 0x2450)

// GLOBAL: LEGORACERS 0x004c214c
static LegoU8 g_unk0x004c214c[] = {0x13, 0x12, 0x16, 0x15, 0x14, 0x17, 0, 0};

// STUB: LEGORACERS 0x0047ff50
void ImaginaryDrill0x2450::FUN_0047ff50(MenuToolContext0x4bc8*, undefined4)
{
	STUB(0x0047ff50);
}

// STUB: LEGORACERS 0x00480210
void ImaginaryDrill0x2450::FUN_00480210(MenuToolContext0x4bc8*, undefined4)
{
	STUB(0x00480210);
}

// STUB: LEGORACERS 0x00480310
void ImaginaryDrill0x2450::FUN_00480310()
{
	STUB(0x00480310);
}

// STUB: LEGORACERS 0x004803a0
void ImaginaryDrill0x2450::FUN_004803a0()
{
	STUB(0x004803a0);
}

// FUNCTION: LEGORACERS 0x00480b70
ImaginaryDrill0x2450::ImaginaryDrill0x2450()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00480cd0
ImaginaryDrill0x2450::~ImaginaryDrill0x2450()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00480e10
void ImaginaryDrill0x2450::Reset()
{
	m_unk0x2444 = 60000;
	m_unk0x2448 = 30000;
	m_unk0x244c = 0;
	m_unk0x2438 = NULL;
	ImaginaryTool0x368::Reset();
}

// STUB: LEGORACERS 0x00480e40
void ImaginaryDrill0x2450::FUN_00480e40()
{
	ImaginaryDrillFieldAt0x22dc::CreateParams params;
	LegoFloat vector0[3];
	LegoFloat vector1[3];

	FUN_0046c480(&m_unk0x21f8, 0, 0xd0);

	params.m_renderer = m_renderer;
	params.m_golExport = m_golExport;
	params.m_unk0x08 = &m_unk0x21f8;
	params.m_unk0x0c = &m_context->m_unk0x4b40;
	params.m_unk0x10 = 18.18122864f;
	params.m_unk0x14 = -10.62275887f;
	params.m_unk0x18 = 0.025708f;
	m_unk0x22dc.FUN_0047e0a0(&params);
	m_unk0x21f8.FUN_00465b40(&m_unk0x22dc);

	vector1[0] = 0.97237003f;
	vector1[1] = -0.233445f;
	vector1[2] = 0.0f;
	vector0[0] = 0.0f;
	vector0[1] = 0.0f;
	vector0[2] = 1.0f;

	m_unk0x2438 = m_unk0x22dc.GetUnk0x1c();
	m_unk0x2438->VTable0x40(vector1, vector0);
}

// FUNCTION: LEGORACERS 0x00480f20
void ImaginaryDrill0x2450::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x368, 0x49, 0x49);
	FUN_0046bef0(&m_unk0x3c4, 0x52, 0x52);
	FUN_00480e40();
	FUN_0047fdc0(&m_unk0x1058, 3, 0x42, 0x25);
	FUN_0047fdc0(&m_unk0x788, 0x55, 0x42, 0x21);
	FUN_0047fdc0(&m_unk0x498, 0x56, 0x42, 0x22);
	FUN_0047fdc0(&m_unk0xa78, 0x57, 0x42, 0x23);
	FUN_0047fdc0(&m_unk0xd68, 0x58, 0x42, 0x24);
	FUN_0047fdc0(&m_unk0x1348, 8, 0x42, 0x26);
	FUN_0047fdc0(&m_unk0x1638, 0x59, 0x42, 0x27);

	if (!m_inputManager->GetJoystickCount()) {
		m_unk0xa78.VTable0x48(5);
	}
}

// FUNCTION: LEGORACERS 0x00481000
LegoBool32 ImaginaryDrill0x2450::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (!p_context->m_unk0x4b40.HasMenuResources()) {
		FUN_00480210(p_context, 0);
	}

	if (!p_context->m_unk0x21f4.FUN_0049a0e0()) {
		FUN_0047ff50(p_context, TRUE);
	}

	if (!ImaginaryTool0x368::FUN_00480440(p_context)) {
		FUN_00480470(p_context, 0, TRUE);
	}

	if (!ImaginaryTool0x368::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	FUN_00480310();
	LegoU32 index = p_context->m_unk0x258.FUN_00443760();
	TurquoiseGlowColor color;
	p_context->m_unk0x425c.FUN_00421050(g_unk0x004c214c[index], &color);
	m_unk0x22dc.FUN_0047e210(&color);
	m_unk0x22dc.GetUnk0x118()->VTable0x14("legoman", p_context->m_context->m_unk0x18);
	m_unk0x2438->FUN_0040dad0(0);
	m_unk0x2438->SetUnk0x5c(m_unk0x2438->GetUnk0x5c() | 0x10000);
	m_unk0x2438->SetUnk0x5c(m_unk0x2438->GetUnk0x5c() & ~0x40000);
	p_context->m_unk0x258.GetUnk0x1cfc().Reset();
	m_unk0x1058.VTable0x4c(5);
	m_unk0xc4->SetUnk0x41(TRUE);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00481120
LegoBool32 ImaginaryDrill0x2450::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	FUN_004803a0();
	return ImaginaryTool0x368::Destroy();
}

// FUNCTION: LEGORACERS 0x00481150
void ImaginaryDrill0x2450::VTable0x38(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x788) {
		m_unk0x360 = 5;
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() & ~2);
	}
	else if (p_unk0x04 == &m_unk0x498) {
		m_unk0x360 = 6;
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() & ~2);
	}
	else if (p_unk0x04 == &m_unk0xa78) {
		m_unk0x360 = 6;
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() | 2);
	}
	else if (p_unk0x04 == &m_unk0xd68) {
		m_unk0x360 = 0x1d;
	}
	else if (p_unk0x04 == &m_unk0x1058) {
		m_unk0x360 = 3;
		ImaginaryTool0x368::FUN_004804c0(m_context);
	}
	else if (p_unk0x04 == &m_unk0x1348) {
		m_unk0x360 = 8;
	}
	else if (p_unk0x04 == &m_unk0x1638) {
		FUN_0047fdc0(&m_unk0x1928, 0x99, 0x46, 0x73);
		FUN_0047fdc0(&m_unk0x1c18, 0x99, 0x45, 0x74);
		FUN_0046c6f0(&m_unk0x1928, &m_unk0x1c18, 0x75);
	}
	else if (p_unk0x04 == &m_unk0x1928) {
		m_unk0x284->FUN_00468cf0();
		m_unk0x360 = 0;
	}
	else if (p_unk0x04 == &m_unk0x1c18 || p_unk0x04 == &m_unk0x1f08) {
		m_unk0x284->FUN_00468cf0();
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x35c = p_unk0x04;
		m_unk0x364 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x004812c0
void ImaginaryDrill0x2450::VTable0x84()
{
	if (m_unk0x360 && m_unk0x360 != 0xffff) {
		m_context->m_menuStack.Push(m_unk0x360);
		return;
	}

	m_context->m_menuStack.ResetSize();
}

// STUB: LEGORACERS 0x004812f0
undefined4 ImaginaryDrill0x2450::VTable0x18(ObscureVantage0x58*, OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return m_unk0x364 ? TRUE : FALSE;
}

// FUNCTION: LEGORACERS 0x00481310
undefined4 ImaginaryDrill0x2450::VTable0x1c(
	ObscureVantage0x58* p_icon,
	OnyxCircularBuffer0x1c::Item* p_item,
	undefined4,
	undefined4
)
{
	if (m_unk0x364) {
		return TRUE;
	}

	if (p_icon == &m_unk0xd8) {
		switch (p_item->m_keyCode) {
		case 0x1000001d:
		case 0x1000009d:
			m_unk0x244c &= ~1;
			return FALSE;
		case 0x1000002a:
		case 0x10000036:
			m_unk0x244c &= ~2;
			return FALSE;
		case 0x10000014:
			m_unk0x244c &= ~4;
			return FALSE;
		case 0x1000002e:
			m_unk0x244c &= ~8;
			return FALSE;
		case 0x1000002f:
			m_unk0x244c &= ~0x10;
			return FALSE;
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00481450
LegoBool32 ImaginaryDrill0x2450::VTable0x78(undefined4 p_elapsed)
{
	if (p_elapsed > m_unk0x2448) {
		m_unk0x2448 = 0;
	}
	else {
		m_unk0x2448 -= p_elapsed;
	}

	if (p_elapsed > m_unk0x2444) {
		m_unk0x2444 = 0;
	}
	else {
		m_unk0x2444 -= p_elapsed;
	}

	LegoU16 state = m_unk0x2438->GetActiveState();
	if (state == 2) {
		if (m_unk0x2438->GetActiveValue() < 208.0f) {
			m_unk0x243c = FALSE;
		}
		else {
			if (!m_unk0x243c) {
				m_soundGroupBinding->FUN_0046e970(0x1d);
				m_unk0x243c = TRUE;
			}
		}
	}

	if (m_context->m_unk0x4b40.GetUnk0x78() & 4) {
		FUN_0047fdc0(&m_unk0x1f08, 0x99, 0x46, 0x72);
		FUN_0046c730(&m_unk0x1f08, 0x7c);
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() & ~4);
	}

	if (!m_unk0x2448) {
		m_unk0x2438->FUN_0040db80(2, 200, 0.0f, 0, 0, 0);
		m_unk0x2438->SetUnk0x5c(m_unk0x2438->GetUnk0x5c() | 0x10000);
		m_unk0x2448 = 30000;
	}
	else if (m_unk0x2438->FUN_0040e360()) {
		m_unk0x2438->FUN_0040db80(1, 200, 0.0f, 0, 0, 1);
		m_unk0x2438->SetUnk0x5c(m_unk0x2438->GetUnk0x5c() | 0x10000);
	}

	if (!m_unk0x2444) {
		m_unk0x364 = TRUE;
	}

	LegoBool32 result = ImaginaryTool0x368::VTable0x78(p_elapsed);
	if (!m_unk0x360) {
		return TRUE;
	}

	return result;
}

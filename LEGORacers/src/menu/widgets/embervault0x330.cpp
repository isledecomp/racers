#include "menu/widgets/embervault0x330.h"

#include "font/golfontbase0x40.h"

#include <string.h>

DECOMP_SIZE_ASSERT(EmberVault0x330, 0x330)

// FUNCTION: LEGORACERS 0x00471850
EmberVault0x330::EmberVault0x330()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004718d0
EmberVault0x330::~EmberVault0x330()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00471930
void EmberVault0x330::FUN_00471930(CreateParams0xa0*)
{
	GolString localStr;
	undefined2 buf[2];
	LegoU32 maxWidth = 0;

	buf[0] = *m_unk0x1fc.FromCursor(0);
	buf[1] = 0;
	localStr.CopyFromBufSelection(buf, 2);
	localStr.ResetCursors();

	for (LegoS32 i = 0; i < m_unk0x1fc.SelectionLength(); i++) {
		LegoS32 width;
		LegoS32 height;
		buf[0] = *m_unk0x1fc.FromCursor(i);
		m_unk0x214->FUN_00408be0(&localStr, &width, &height);
		if (width > maxWidth) {
			maxWidth = width;
		}
	}

	m_unk0x23c.FUN_00468000(maxWidth);
	m_unk0x23c.FUN_00468040(4);
}

// FUNCTION: LEGORACERS 0x00471a30
void EmberVault0x330::FUN_00471a30()
{
	if (m_unk0x1f8 == 4) {
		m_unk0x208.SetCursorEnd(m_unk0x208.SelectionLength() - 1);
	}

	LegoS32 width;
	LegoS32 height;
	m_unk0x214->FUN_00408be0(&m_unk0x208, &width, &height);

	m_unk0x208.FirstLine();
	m_unk0x23c.FUN_00467fc0(m_unk0x34.m_left + width, m_unk0x34.m_bottom - 6);
}

// FUNCTION: LEGORACERS 0x00471aa0
LegoBool32 EmberVault0x330::FUN_00471aa0(CreateParams0xa0* p_createParams)
{
	SableCrest0xc0::CreateParams0x44 createParams;
	memset(&createParams, 0, sizeof(createParams));
	memcpy(&createParams, p_createParams, sizeof(ObscureVantage0x58::CreateParams0x38));

	createParams.m_parent = ObscureVantage0x58::m_parent;
	createParams.m_unk0x20 = 0x400;
	createParams.m_unk0x38 = 1;
	createParams.m_flags |= 1;
	createParams.m_unk0x3c = 1000;
	createParams.m_unk0x40 = 1000;
	createParams.m_unk0x22.m_unk0x00 = -1;

	return m_unk0x23c.FUN_00467f70(&createParams);
}

// FUNCTION: LEGORACERS 0x00471b20
LegoBool32 EmberVault0x330::VTable0x70(
	CreateParams0xa0* p_createParams,
	const ObscureIcon0x1a8::CreateState0x90* p_createState
)
{
	VTable0x08();

	if (IvoryTalon0x23c::VTable0x70(p_createParams, p_createState)) {
		if (FUN_00471aa0(p_createParams)) {
			FUN_00471930(p_createParams);
		}
		else {
			VTable0x08();
		}
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00471b70
ObscureVantage0x58* EmberVault0x330::VTable0x38(Rect* p_param1, Rect* p_param2)
{
	ObscureVantage0x58* result = IvoryTalon0x23c::VTable0x38(p_param1, p_param2);
	FUN_00471a30();

	if (m_stateFlags & 2) {
		if (m_unk0x23c.GetParent() != ObscureVantage0x58::m_parent) {
			m_unk0x23c.SetParent(ObscureVantage0x58::m_parent);
		}

		if (m_unk0x23a == m_unk0x238) {
			m_unk0x23c.ClearFlags(2);
		}
		else {
			m_unk0x23c.SetFlags(2);
		}
	}
	else {
		m_unk0x23c.RemoveFromParent();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00471c00
ObscureVantage0x58* EmberVault0x330::VTable0x30(
	InputEventQueue::Event* p_param1,
	undefined4 p_param2,
	undefined4 p_param3
)
{
	ObscureVantage0x58* result = IvoryTalon0x23c::VTable0x30(p_param1, p_param2, p_param3);
	FUN_00471a30();

	return result;
}

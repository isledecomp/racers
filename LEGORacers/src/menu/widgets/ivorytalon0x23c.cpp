#include "menu/widgets/ivorytalon0x23c.h"

#include "golstringtable.h"

#include <string.h>

DECOMP_SIZE_ASSERT(IvoryTalon0x23c, 0x23c)
DECOMP_SIZE_ASSERT(IvoryTalon0x23c::CreateParams0xa0, 0xa0)

// FUNCTION: LEGORACERS 0x00470eb0
IvoryTalon0x23c::IvoryTalon0x23c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00470f40
IvoryTalon0x23c::~IvoryTalon0x23c()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00470fb0
void IvoryTalon0x23c::Reset()
{
	m_unk0x208.Reset();
	m_unk0x1fc.Reset();
	memset(m_unk0x1b4, 0, sizeof(m_unk0x1b4));
	memset(m_unk0x1a8, 0, sizeof(m_unk0x1a8));
	m_unk0x214 = 0;
	m_unk0x1f8 = 3;
	m_unk0x238 = 0x1f;
	m_unk0x23a = 0;
	m_unk0x1f4 = 0;
	ObscureIcon0x1a8::Reset();
}

// FUNCTION: LEGORACERS 0x00471040
LegoBool32 IvoryTalon0x23c::VTable0x70(
	CreateParams0xa0* p_createParams,
	const ObscureIcon0x1a8::CreateState0x90* p_createState
)
{
	VTable0x08();

	m_unk0x1a8[0] = p_createParams->m_unk0x96;
	m_unk0x1a8[1] = p_createParams->m_unk0x9a;
	m_unk0x214 = p_createParams->m_unk0x8c;
	m_unk0x1b0 = p_createParams->m_unk0x84;
	m_unk0x238 = p_createParams->m_unk0x94;

	m_unk0x208.CopyFromBufSelection(m_unk0x1b4, m_unk0x238 + 1);
	m_unk0x1fc.CopyFromBufSelection(m_unk0x1b0->GetStringBuffer(p_createParams->m_unk0x88), 0);

	if (p_createParams->m_unk0x90) {
		m_unk0x208.GolStrcpy(p_createParams->m_unk0x90);
		m_unk0x23a = m_unk0x208.SelectionLength();
	}

	return FUN_00471e30(p_createParams, p_createState);
}

// FUNCTION: LEGORACERS 0x00471220
void IvoryTalon0x23c::VTable0x4c(undefined4 p_flags)
{
	FUN_00472bc0();
	ObscureIcon0x1a8::VTable0x4c(p_flags);
}

// FUNCTION: LEGORACERS 0x00471240
void IvoryTalon0x23c::VTable0x50(undefined4 p_flags)
{
	FUN_00472c10();
	ObscureIcon0x1a8::VTable0x50(p_flags);
}

// FUNCTION: LEGORACERS 0x00471260
ObscureVantage0x58* IvoryTalon0x23c::VTable0x2c(void* p_item, undefined4 p_x, undefined4 p_y)
{
	LegoU8 flag = 8;

	if (!m_parent) {
		if (!(flag & m_flags)) {
			return NULL;
		}
	}

	if (!FUN_00472c40(p_x, p_y)) {
		return NULL;
	}

	if (flag & m_flags) {
		if (m_unk0x28) {
			m_unk0x28->VTable0x28(this, p_item, p_x, p_y);
		}

		return this;
	}

	if (!VTable0x5c()) {
		return NULL;
	}

	VTable0x4c(0);

	if (m_activeChild || m_firstChild) {
		return NULL;
	}

	if (m_unk0x28) {
		m_unk0x28->VTable0x14(this, p_item, p_x, p_y);
	}

	return this;
}

// STUB: LEGORACERS 0x00471300
ObscureVantage0x58* IvoryTalon0x23c::VTable0x38(Rect*, Rect*)
{
	STUB(0x00471300);
	return NULL;
}

// STUB: LEGORACERS 0x00471810
ObscureVantage0x58* IvoryTalon0x23c::VTable0x30(InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x00471810);
	return NULL;
}

#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
ObscureVantage0x58* IvoryTalon0x23c::VTable0x34(InputEventQueue::Event*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()

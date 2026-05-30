#include "menu/widgets/ivorytalon0x23c.h"

#include <string.h>

DECOMP_SIZE_ASSERT(IvoryTalon0x23c, 0x23c)

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

// STUB: LEGORACERS 0x00471040
void IvoryTalon0x23c::VTable0x70()
{
	STUB(0x00471040);
}

// STUB: LEGORACERS 0x00471220
void IvoryTalon0x23c::VTable0x4c(undefined4)
{
	STUB(0x00471220);
}

// STUB: LEGORACERS 0x00471240
void IvoryTalon0x23c::VTable0x50(undefined4)
{
	STUB(0x00471240);
}

// STUB: LEGORACERS 0x00471260
ObscureVantage0x58* IvoryTalon0x23c::VTable0x2c(void*, undefined4, undefined4)
{
	STUB(0x00471260);
	return NULL;
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

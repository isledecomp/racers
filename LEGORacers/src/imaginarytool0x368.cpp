#include "imaginarytool0x368.h"

#include "golstring.h"

DECOMP_SIZE_ASSERT(ImaginaryTool0x368, 0x368)

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void ImaginaryTool0x368::VTable0x80()
{
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
undefined4 ImaginaryTool0x368::VTable0x18(ObscureIcon0x1a8*, OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return m_unk0x364;
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
undefined4 ImaginaryTool0x368::VTable0x1c(ObscureIcon0x1a8*, OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return m_unk0x364;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void ImaginaryTool0x368::VTable0x90(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void ImaginaryTool0x368::VTable0x94(undefined4)
{
}

// FUNCTION: LEGORACERS 0x00474bf0 FOLDED
CeruleanEmperor0x4c* ImaginaryTool0x368::VTable0x5c()
{
	return &m_unk0x290;
}

// FUNCTION: LEGORACERS 0x00474c00
CeruleanQueen0x58* ImaginaryTool0x368::VTable0x64()
{
	return &m_unk0x2e0;
}

// STUB: LEGORACERS 0x0047fae0
ImaginaryTool0x368::ImaginaryTool0x368()
{
	// TODO
}

// STUB: LEGORACERS 0x0047fb80
ImaginaryTool0x368::~ImaginaryTool0x368()
{
	// TODO
}

// FUNCTION: LEGORACERS 0x0047fbf0
void ImaginaryTool0x368::VTable0x54()
{
	m_unk0x360 = 0xffff;
	m_unk0x362 = 0;
	m_unk0x354 = NULL;
	m_unk0x35c = NULL;
	m_unk0x358 = 0;
	m_unk0x364 = FALSE;
	ImaginaryNotion0x290::VTable0x54();
}

// FUNCTION: LEGORACERS 0x0047fc20
LegoBool32 ImaginaryTool0x368::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	GolString string;

	m_unk0x354 = p_context;
	LegoBool32 result = ImaginaryNotion0x290::VTable0x70(p_createParams);
	VTable0x80();

	return result;
}

// STUB: LEGORACERS 0x0047fca0
void ImaginaryTool0x368::VTable0x74()
{
	// TODO
	STUB(0x0047fca0);
}

// STUB: LEGORACERS 0x004803c0
void ImaginaryTool0x368::VTable0x6c()
{
	// TODO
	STUB(0x004803c0);
}

// FUNCTION: LEGORACERS 0x00480420 FOLDED
LegoBool32 ImaginaryTool0x368::VTable0x88()
{
	if (m_unk0x35c) {
		return !(m_unk0x35c->GetUnk0x54() & TRUE);
	}

	return TRUE;
}

// STUB: LEGORACERS 0x00480470
void ImaginaryTool0x368::FUN_00480470(MenuToolContext0x4bc8*, undefined4, undefined4)
{
	STUB(0x00480470);
}

// FUNCTION: LEGORACERS 0x00480500 FOLDED
void ImaginaryTool0x368::VTable0x34(undefined4)
{
	m_unk0x364 = FALSE;
}

// FUNCTION: LEGORACERS 0x00480510 FOLDED
void ImaginaryTool0x368::VTable0x3c(undefined4 p_unk0x04)
{
	m_unk0x358 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00480520
LegoBool32 ImaginaryTool0x368::VTable0x78(undefined4)
{
	if (m_unk0x364 && VTable0x88()) {
		VTable0x84();
	}

	return FALSE;
}

// STUB: LEGORACERS 0x00487d30 FOLDED
void ImaginaryTool0x368::VTable0x40(undefined4)
{
	// TODO
	STUB(0x00487d30);
}

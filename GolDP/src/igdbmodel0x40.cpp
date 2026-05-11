#include "igdbmodel0x40.h"

#include <float.h>

// FUNCTION: GOLDP 0x10027020
IGdbModel0x40::IGdbModel0x40()
{
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28.m_x = 0.0f;
	m_unk0x28.m_y = 0.0f;
	m_unk0x28.m_z = 0.0f;
	m_unk0x3c = FALSE;
	m_unk0x34 = FLT_MAX / 2.0f;
	m_unk0x38 = 1.0f;
}

// FUNCTION: GOLDP 0x10027090
IGdbModel0x40::~IGdbModel0x40()
{
	VTable0x24();
}

// STUB: GOLDP 0x100270e0
void IGdbModel0x40::VTable0x1c(undefined4 p_arg1, const LegoChar* p_name, LegoBool32 p_binary)
{
	// TODO
	STUB(0x100270e0);
}

// STUB: GOLDP 0x100272e0
void IGdbModel0x40::FUN_100272e0(undefined4, undefined4)
{
	// TODO
	STUB(0x100272e0);
}

// STUB: GOLDP 0x100273b0
void IGdbModel0x40::VTable0x24()
{
	// TODO
	STUB(0x100273b0);
}

// STUB: GOLDP 0x10027430
void IGdbModel0x40::VTable0x00(GolFileParser& p_parser)
{
	// TODO
	STUB(0x10027430);
}

// STUB: GOLDP 0x10027740
void IGdbModel0x40::VTable0x04(undefined4*)
{
	// TODO
	STUB(0x10027740);
}

// STUB: GOLDP 0x100277d0
void IGdbModel0x40::VTable0x28(undefined4*)
{
	// TODO
	STUB(0x100277d0);
}

// STUB: GOLDP 0x100277e0
void IGdbModel0x40::VTable0x2c(undefined4, undefined4)
{
	// TODO
	STUB(0x100277e0);
}

// STUB: GOLDP 0x10027810
void IGdbModel0x40::VTable0x30(undefined4*)
{
	// TODO
	STUB(0x10027810);
}

// STUB: GOLDP 0x10027820
void IGdbModel0x40::VTable0x34(undefined4)
{
	// TODO
	STUB(0x10027820);
}

// STUB: GOLDP 0x10027830
void IGdbModel0x40::VTable0x08(undefined4*)
{
	// TODO
	STUB(0x10027830);
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void IGdbModel0x40::VTable0x14(GolFileParser& p_parser)
{
	// empty
}

// STUB: GOLDP 0x100278c0
void IGdbModel0x40::VTable0x38(GolVec3*, LegoFloat*, LegoFloat)
{
	// TODO
	STUB(0x100278c0);
}

// STUB: GOLDP 0x10027b30
void IGdbModel0x40::VTable0x3c(undefined4)
{
	// TODO
	STUB(0x10027b30);
}

// STUB: GOLDP 0x10027b40
void IGdbModel0x40::VTable0x40(undefined4)
{
	// TODO
	STUB(0x10027b40);
}

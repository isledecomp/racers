#include "imaginaryruler0x2e60.h"

#include "menutoolcreateparams0x30.h"

DECOMP_SIZE_ASSERT(ImaginaryRuler0x2e60, 0x2e60)

// STUB: LEGORACERS 0x00487850
ImaginaryRuler0x2e60::ImaginaryRuler0x2e60()
{
	STUB(0x00487850);
}

// STUB: LEGORACERS 0x004879b0
ImaginaryRuler0x2e60::~ImaginaryRuler0x2e60()
{
	STUB(0x004879b0);
}

// STUB: LEGORACERS 0x00487ae0
void ImaginaryRuler0x2e60::Reset()
{
	STUB(0x00487ae0);
}

// STUB: LEGORACERS 0x00487b50
void ImaginaryRuler0x2e60::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x1908, 0x49, 0x49);
	ImaginaryGizmo0x1908::VTable0x4c();

	STUB(0x00487b50);
}

// STUB: LEGORACERS 0x00487ca0
LegoBool32 ImaginaryRuler0x2e60::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	m_menuId = p_createParams->m_menuId;
	p_createParams->m_menuId = 6;

	LegoBool32 result = ImaginaryGizmo0x1908::VTable0x8c(p_context, p_createParams);

	STUB(0x00487ca0);
	return result;
}

// STUB: LEGORACERS 0x00487d10
void ImaginaryRuler0x2e60::VTable0x3c(ObscureIcon0x1a8*)
{
	STUB(0x00487d10);
}

// STUB: LEGORACERS 0x00487d40
void ImaginaryRuler0x2e60::VTable0x38(ObscureVantage0x58*)
{
	STUB(0x00487d40);
}

// STUB: LEGORACERS 0x00487e10
void ImaginaryRuler0x2e60::VTable0x44(undefined4)
{
	STUB(0x00487e10);
}

// STUB: LEGORACERS 0x00487f90
void ImaginaryRuler0x2e60::VTable0x84()
{
	STUB(0x00487f90);
}

// STUB: LEGORACERS 0x00488150
LegoBool32 ImaginaryRuler0x2e60::VTable0x78(undefined4)
{
	STUB(0x00488150);
	return FALSE;
}

#include "menu/screens/imaginaryshape0x2b20.h"

#include "decomp.h"
#include "menu/crimsonsun0xa4.h"
#include "menu/menutoolcontext0x4bc8.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryShape0x2b20, 0x2b20)

// FUNCTION: LEGORACERS 0x00476d50
ImaginaryShape0x2b20::ImaginaryShape0x2b20()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00476ef0
ImaginaryShape0x2b20::~ImaginaryShape0x2b20()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00476ff0
void ImaginaryShape0x2b20::Reset()
{
	m_unk0x2ae0 = 1;
	m_unk0x2ae4 = 1;

	m_unk0x2adc = 0;
	m_unk0x2ad8 = 0;
	m_unk0x28d0 = 0;
	m_unk0x28cc = 0;
	m_unk0x28c8 = 0;
	m_unk0x2b1c = 0;
	m_unk0x2ae8 = 0;

	memset(m_unk0x2aec, 0, sizeof(m_unk0x2aec));

	ObsidianMantle0x3b4::Reset();
}

// STUB: LEGORACERS 0x00477050
void ImaginaryShape0x2b20::FUN_00477050()
{
	STUB(0x00477050);
}

// STUB: LEGORACERS 0x00477130
void ImaginaryShape0x2b20::FUN_00477130()
{
	STUB(0x00477130);
}

// STUB: LEGORACERS 0x00477190
void ImaginaryShape0x2b20::VTable0x4c()
{
	STUB(0x00477190);
}

// STUB: LEGORACERS 0x00477210
void ImaginaryShape0x2b20::VTable0x80()
{
	STUB(0x00477210);
}

// FUNCTION: LEGORACERS 0x00477250
LegoBool32 ImaginaryShape0x2b20::VTable0x8c(MenuToolContext0x4bc8* p_unk0x04, MenuToolCreateParams0x30* p_unk0x08)
{
	if (!ImaginaryTool0x368::VTable0x8c(p_unk0x04, p_unk0x08)) {
		return FALSE;
	}

	FUN_00477290();
	VTable0x44(&m_unk0xfec);

	return TRUE;
}

// STUB: LEGORACERS 0x00477290
void ImaginaryShape0x2b20::FUN_00477290()
{
	STUB(0x00477290);
}

// FUNCTION: LEGORACERS 0x00477380
void ImaginaryShape0x2b20::VTable0x84()
{
	FUN_004773a0();
	m_context->m_menuStack.Pop();
}

// STUB: LEGORACERS 0x004773a0
void ImaginaryShape0x2b20::FUN_004773a0()
{
	STUB(0x004773a0);
}

// FUNCTION: LEGORACERS 0x00477630
void ImaginaryShape0x2b20::VTable0x38(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x25d8) {
		m_unk0x284->FUN_00468cf0();
	}
}

// STUB: LEGORACERS 0x00477650
void ImaginaryShape0x2b20::VTable0x44(ObscureVantage0x58*)
{
	STUB(0x00477650);
}

// STUB: LEGORACERS 0x00477700
void ImaginaryShape0x2b20::VTable0x10(ObscureVantage0x58*)
{
	STUB(0x00477700);
}

// STUB: LEGORACERS 0x00477770
void ImaginaryShape0x2b20::FUN_00477770()
{
	STUB(0x00477770);
}

// FUNCTION: LEGORACERS 0x00477880
LegoBool32 ImaginaryShape0x2b20::VTable0x78(undefined4 p_unk0x04)
{
	if (m_unk0x2ae0 != m_unk0x2ae4) {
		if (m_unk0x35c == NULL || !(m_unk0x35c->GetUnk0x54() & 1)) {
			FUN_00477770();
		}
	}

	return ObsidianMantle0x3b4::VTable0x78(p_unk0x04);
}

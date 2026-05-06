#include "obscurezebra0xa4.h"

DECOMP_SIZE_ASSERT(ObscureZebra0xa4, 0xa4)

// FUNCTION: LEGORACERS 0x004734a0
ObscureZebra0xa4::ObscureZebra0xa4()
{
	VTable0x00();
}

// STUB: LEGORACERS 0x00473510
ObscureZebra0xa4::~ObscureZebra0xa4()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00473560
void ObscureZebra0xa4::VTable0x00()
{
	m_unk0x90 = 0;
	m_unk0x78 = 0;
	m_unk0x60 = 0;
	m_unk0x94 = 0;
	m_unk0x7c = 0;
	m_unk0x64 = 0;
	m_unk0x98 = 0;
	m_unk0x80 = 0;
	m_unk0x68 = 0;
	m_unk0xa0 = 0;

	ObscureVantage0x58::VTable0x00();
}

// FUNCTION: LEGORACERS 0x004735c0
void ObscureZebra0xa4::VTable0x14(undefined4* p_param)
{
	m_unk0x6c = *p_param;
	m_unk0x84 = *p_param;
	m_unk0x9c = *p_param;

	ObscureVantage0x58::VTable0x14(p_param);
}

// STUB: LEGORACERS 0x004735f0
undefined4 ObscureZebra0xa4::VTable0x38(undefined4, undefined4)
{
	STUB(0x004735f0);
	return 0;
}

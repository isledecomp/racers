#include "obscurelink0x1c.h"

DECOMP_SIZE_ASSERT(ObscureLink0x1c, 0x1c)

// FUNCTION: LEGORACERS 0x0046b290
ObscureLink0x1c::ObscureLink0x1c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046b2d0
ObscureLink0x1c::~ObscureLink0x1c()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046b2e0
void ObscureLink0x1c::Reset()
{
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x08 = 0;
	m_unk0x04 = 0;
	m_unk0x18 = 0;
}

// FUNCTION: LEGORACERS 0x0046b330
LegoBool32 ObscureLink0x1c::VTable0x08()
{
	if (m_unk0x18) {
		Reset();
	}

	return !m_unk0x18;
}

// FUNCTION: LEGORACERS 0x0046b350
ObscureLink0x1c* ObscureLink0x1c::FUN_0046b350(ObscureLink0x1c* p_parent)
{
	ObscureLink0x1c* result = p_parent;

	if (p_parent) {
		m_unk0x04 = p_parent;
		m_unk0x08 = p_parent->m_unk0x08;
		p_parent->m_unk0x08 = this;
		result = m_unk0x08;

		if (result) {
			result->m_unk0x04 = this;
		}
	}

	return result;
}

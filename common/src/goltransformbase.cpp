#include "goltransformbase.h"

DECOMP_SIZE_ASSERT(GolTransformBase, 0x10)

// FUNCTION: GOLDP 0x1001ce90
GolTransformBase::GolTransformBase()
{
	m_unk0x04 = NULL;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
}

// FUNCTION: GOLDP 0x1001ceb0
void GolTransformBase::FUN_1001ceb0(GolTransformBase* p_unk0x04)
{
	if (p_unk0x04->m_unk0x04 != this) {
		p_unk0x04->m_unk0x04 = this;
		p_unk0x04->m_unk0x08 = m_unk0x0c;
		m_unk0x0c = p_unk0x04;
	}
}

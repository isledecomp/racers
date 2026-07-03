#include "goltransformbase.h"

DECOMP_SIZE_ASSERT(GolTransformBase, 0x10)

// FUNCTION: GOLDP 0x1001ce90
GolTransformBase::GolTransformBase()
{
	m_parent = NULL;
	m_nextSibling = 0;
	m_firstChild = 0;
}

// FUNCTION: GOLDP 0x1001ceb0
void GolTransformBase::AttachChild(GolTransformBase* p_child)
{
	if (p_child->m_parent != this) {
		p_child->m_parent = this;
		p_child->m_nextSibling = m_firstChild;
		m_firstChild = p_child;
	}
}

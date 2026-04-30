#include "awakekite0x20.h"

#include "bronzefalcon0xc8770.h"
#include "golerror.h"

DECOMP_SIZE_ASSERT(AwakeKite0x20, 0x20)

// FUNCTION: GOLDP 0x10005d10
AwakeKite0x20::AwakeKite0x20()
{
	m_items = NULL;
}

// FUNCTION: GOLDP 0x10005d50
AwakeKite0x20::~AwakeKite0x20()
{
	if (m_items) {
		delete[] m_items;
		m_items = NULL;
	}

	HypnoticNoise0x1c::Clear();
}

// FUNCTION: GOLDP 0x10005dc0
void AwakeKite0x20::VTable0x0c()
{
	m_items = new UtopianPan0xa4[m_numItems];
	if (m_items == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x10005ec0
void AwakeKite0x20::Clear()
{
	if (m_items) {
		delete[] m_items;
		m_items = NULL;
	}

	HypnoticNoise0x1c::Clear();
}

// FUNCTION: GOLDP 0x10005ef0
UtopianPan0xa4* AwakeKite0x20::GetItem(undefined4 p_index)
{
	return &m_items[p_index];
}

// FUNCTION: GOLDP 0x10005f10
void AwakeKite0x20::VTable0x10()
{
	if (m_numItems > 0) {
		for (LegoS32 i = 0; i < m_numItems; i++) {
			if (m_items[i].m_unk0x3c & 1) {
				m_items[i].FUN_100051c0();
			}
		}
	}
}

// FUNCTION: GOLDP 0x10005f50
void AwakeKite0x20::VTable0x14()
{
	if (m_numItems > 0) {
		for (LegoS32 i = 0; i < m_numItems; i++) {
			if (m_items[i].m_unk0x3c & 1) {
				m_items[i].FUN_10005210();
			}
		}
	}
}

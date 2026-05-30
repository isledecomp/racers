#include "util/sordidwatch0x140.h"

#include "cmbmodelpart0x34.h"
#include "core/goldpexport.h"
#include "golerror.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "mesh/golmodelbase.h"

DECOMP_SIZE_ASSERT(SordidWatch0x140, 0x140)
DECOMP_SIZE_ASSERT(SordidWatch0x140::SordidWatchInner0x38, 0x38)

// GLOBAL: LEGORACERS 0x004af86c
const LegoFloat g_maxFloat = FLT_MAX;

// FUNCTION: LEGORACERS 0x00412360
SordidWatch0x140::SordidWatch0x140()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00412390
void SordidWatch0x140::Reset()
{
	m_unk0x000 = 0;
	m_unk0x004 = 0;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_unk0x0a0 = 0;
	m_unk0x0a4 = 0;
	m_unk0x0a8 = 0;
	m_unk0x0ac = NULL;
	m_unk0x0b8 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0c4 = 0;
	m_unk0x0c8 = 0;
	m_unk0x0cc = 0;
	m_unk0x0d0 = 0;
	m_unk0x0d4 = 0;
	m_unk0x0d8 = 0;
	m_unk0x0dc = 0;
	m_unk0x0e0 = 0;
	m_unk0x0e4 = 0;
	m_unk0x120 = 0;
	m_unk0x124 = 0;
	m_unk0x128 = 0;
	m_unk0x12c = 0;
	m_unk0x130 = 0;
	m_unk0x134 = 0;
	m_unk0x138 = 0;
	m_unk0x13c = 0;
}

// STUB: LEGORACERS 0x00412430
void SordidWatch0x140::FUN_00412430(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	undefined4 p_param3,
	undefined4 p_param4
)
{
	STUB(0x00412430);
}

// FUNCTION: LEGORACERS 0x00412560
void SordidWatch0x140::Destroy()
{
	if (m_unk0x0ac) {
		delete[] m_unk0x0ac;
		m_unk0x0ac = NULL;
	}
	m_unk0x010.VTable0x54();
	if (m_unk0x000) {
		if (m_unk0x004) {
			m_unk0x000->VTable0x48(m_unk0x004);
			m_unk0x004 = 0;
		}
		m_unk0x000 = 0;
	}
	Reset();
}

// FUNCTION: LEGORACERS 0x00412760
SordidWatch0x140::SordidWatchInner0x38* SordidWatch0x140::FUN_00412760(
	GolVec3* p_param1,
	GolVec3* p_param2,
	undefined4 p_param3
)
{
	SordidWatch0x140::SordidWatchInner0x38* entity = FUN_00412a00();

	GolVec3 center, position;

	if (!m_unk0x0e8) {
		m_unk0x010.VTable0x08(*p_param1);
		center.m_x = 0.0f;
		center.m_y = 0.0f;
		center.m_z = 0.0f;
	}
	else {
		m_unk0x010.VTable0x04(&position);
		center.m_x = p_param1->m_x - position.m_x;
		center.m_y = p_param1->m_y - position.m_y;
		center.m_z = p_param1->m_z - position.m_z;
	}

	entity->SetCenter(center);
	entity->SetVelocity(*p_param2);

	entity->m_unk0x28 = 0;
	entity->m_unk0x2c = p_param3;
	entity->m_unk0x30 = 0;

	m_unk0x0e8++;

	return entity;
}

// FUNCTION: LEGORACERS 0x00412840
void SordidWatch0x140::FUN_00412840()
{
	if (m_unk0x0b8 & 2) {
		FUN_00412970();
		m_unk0x0d0 = 0;
		m_unk0x0d4 = 0;
		m_unk0x0d8 = 0;
		m_unk0x0dc = 0;
		m_unk0x0e0 = 0;
		m_unk0x0e4 = 0;
		m_unk0x0b8 = m_unk0x0b8 & ~0x1e;
	}
}

// FUNCTION: LEGORACERS 0x00412970
void SordidWatch0x140::FUN_00412970()
{
	m_unk0x0b4 = NULL;
	m_unk0x0b0 = m_unk0x0ac;
	for (LegoU32 i = 0; i < m_unk0x0a8 - 1; i++) {
		m_unk0x0ac[i].m_next = &m_unk0x0ac[i + 1];
		m_unk0x0ac[i].m_unk0x30 = NULL;
	}
	m_unk0x0ac[m_unk0x0a8 - 1].m_next = NULL;
	m_unk0x0ac[m_unk0x0a8 - 1].m_unk0x30 = 0;
}

// FUNCTION: LEGORACERS 0x00412a00
SordidWatch0x140::SordidWatchInner0x38* SordidWatch0x140::FUN_00412a00()
{
	SordidWatchInner0x38* maxEntry = m_unk0x0b0;
	SordidWatchInner0x38* current;

	if (maxEntry) {
		m_unk0x0b0 = maxEntry->m_next;
		maxEntry->m_next = m_unk0x0b4;
		m_unk0x0b4 = maxEntry;
		return maxEntry;
	}
	else {
		maxEntry = m_unk0x0b4;
		LegoU32 maxValue = maxEntry->m_unk0x28;
		for (current = maxEntry->m_next; current != NULL; current = current->m_next) {
			if (current->m_unk0x28 > maxValue) {
				maxEntry = current;
				maxValue = current->m_unk0x28;
			}
		}
		return maxEntry;
	}
}

// FUNCTION: LEGORACERS 0x004145e0
SordidWatch0x140::SordidWatchInner0x38::SordidWatchInner0x38()
{
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_next = NULL;
}

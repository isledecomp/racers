#include "util/sordidwatch0x140.h"

#include "cmbmodelpart0x34.h"
#include "menu/widgets/obscurebanner0x5ec.h"

DECOMP_SIZE_ASSERT(SordidWatch0x140, 0x140)
DECOMP_SIZE_ASSERT(SordidWatch0x140::SordidWatchInner0x38, 0x38)

// FUNCTION: LEGORACERS 0x00412360
SordidWatch0x140::SordidWatch0x140()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00412560
SordidWatch0x140::~SordidWatch0x140()
{
	if (m_unk0xac) {
		delete[] m_unk0xac;
		m_unk0xac = 0;
	}
	m_unk0x010.VTable0x54();
	if (m_unk0x000) {
		if (m_unk0x004) {
			// FIXME: hack to get a match, most likely not the correct class
			((ObscureBanner0x5ec*) m_unk0x000)->VTable0x48(m_unk0x004);
			m_unk0x004 = 0;
		}
		m_unk0x000 = 0;
	}
	Reset();
}

// FUNCTION: LEGORACERS 0x00412390
void SordidWatch0x140::Reset()
{
	m_unk0x000 = 0;
	m_unk0x004 = 0;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_unk0xa0 = 0;
	m_unk0xa4 = 0;
	m_unk0xa8 = 0;
	m_unk0xac = 0;
	m_unk0xb8 = 0;
	m_unk0xbc = 0;
	m_unk0xc0 = 0;
	m_unk0xc4 = 0;
	m_unk0xc8 = 0;
	m_unk0xcc = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xd8 = 0;
	m_unk0xdc = 0;
	m_unk0xe0 = 0;
	m_unk0xe4 = 0;
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

// FUNCTION: LEGORACERS 0x00412760
undefined4 SordidWatch0x140::FUN_00412760(GolVec3* p_param1, GolVec3* p_param2, undefined4 p_param3)
{
	SordidWatch0x140::SordidWatchInner0x38* entity = FUN_00412a00();

	GolVec3 gstack18, localc;

	if (!m_unk0xe8) {
		m_unk0x010.VTable0x08(*p_param1);
		gstack18.m_x = 0.0f;
		gstack18.m_y = 0.0f;
		gstack18.m_z = 0.0f;
	}
	else {
		m_unk0x010.VTable0x04(&localc);
		gstack18.m_x = p_param1->m_x - localc.m_x;
		gstack18.m_y = p_param1->m_y - localc.m_y;
		gstack18.m_z = p_param1->m_z - localc.m_z;
	}

	entity->SetCenter(gstack18);
	entity->SetVelocity(*p_param2);

	entity->m_unk0x28 = 0;
	entity->m_unk0x2c = p_param3;
	entity->m_unk0x30 = 0;

	m_unk0xe8++;

	return (undefined4) entity;
}

// FUNCTION: LEGORACERS 0x00412840
void SordidWatch0x140::FUN_00412840()
{
	if (m_unk0xb8 & 2) {
		FUN_00412970();
		m_unk0xd0 = 0;
		m_unk0xd4 = 0;
		m_unk0xd8 = 0;
		m_unk0xdc = 0;
		m_unk0xe0 = 0;
		m_unk0xe4 = 0;
		m_unk0xb8 = m_unk0xb8 & ~0x1e;
	}
}

// FUNCTION: LEGORACERS 0x00412970
void SordidWatch0x140::FUN_00412970()
{
	m_unk0xb4 = 0;
	m_unk0xb0 = m_unk0xac;
	for (LegoU32 i = 0; i < m_unk0xa8 - 1; i++) {
		m_unk0xac[i].m_next = &m_unk0xac[i + 1];
		m_unk0xac[i].m_unk0x30 = 0;
	}
	m_unk0xac[m_unk0xa8 - 1].m_next = NULL;
	m_unk0xac[m_unk0xa8 - 1].m_unk0x30 = 0;
}

// FUNCTION: LEGORACERS 0x00412a00
SordidWatch0x140::SordidWatchInner0x38* SordidWatch0x140::FUN_00412a00()
{
	SordidWatchInner0x38* maxEntry = m_unk0xb0;
	SordidWatchInner0x38* current;

	if (maxEntry) {
		m_unk0xb0 = maxEntry->m_next;
		maxEntry->m_next = m_unk0xb4;
		m_unk0xb4 = maxEntry;
		return maxEntry;
	}
	else {
		maxEntry = m_unk0xb4;
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

#include "util/sordidwatch0x140.h"

#include "cmbmodelpart0x34.h"
#include "menu/widgets/obscurebanner0x5ec.h"

// TODO: Add when the size is known
// DECOMP_SIZE_ASSERT(sordidwatch0x140, 0xTODO)

// FUNCTION: LEGORACERS 0x00412360
SordidWatch0x140::SordidWatch0x140()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00412560
SordidWatch0x140::~SordidWatch0x140()
{
  if (m_unk0x010.m_partIndices[0]) {
	// TODO: What is the actual type of m_partIndices?
	// It cannot be a pointer to something that has a destructor
	delete ((undefined4*)m_unk0x010.m_partIndices[0]); // wrong, in to compile
	m_unk0x010.m_partIndices[0] = 0;
  }
  m_unk0x010.VTable0x54();
  if (m_unk0x000) {
    if (m_unk0x004) {
		// proves m_unk0x000 is a pointer to a class, still unknown
		// FIXME: hack to get a match, most likely not semantically correct
		((ObscureBanner0x5ec*)m_unk0x000)->VTable0x48(m_unk0x004);
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
	m_unk0x010.m_nodes[0] = NULL;
	m_unk0x010.m_nodes[1] = NULL;
	m_unk0x010.m_nodes[2] = NULL;
	m_unk0x010.m_partIndices[0] = 0;
	m_unk0x010.m_modelParts[0] = NULL;
	m_unk0x010.m_modelParts[1] = NULL;
	m_unk0x010.m_modelParts[2] = NULL;
	m_unk0x010.m_unk0xb4 = 0.0;
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

// FUNCTION: LEGORACERS 0x00412760
undefined4 SordidWatch0x140::FUN_00412760(GolVec3* p_param1, GolVec3* p_param2, LegoFloat p_param3)
{
	// type is guessed and may be wrong
	GolOrientedEntity* entity = (GolOrientedEntity*) FUN_00412a00();

	GolVec3 gstack18, localc;

	if (!m_unk0xe8) {
		m_unk0x010.VTable0x08(*p_param1);
		gstack18.m_x = 0.0f;
		gstack18.m_y = 0.0f;
		gstack18.m_z = 0.0f;
	} else {
		// These vtable calls strongly suggest that the SilverHollow is at 0x10

		m_unk0x010.VTable0x04(&localc);
		gstack18.m_x = p_param1->m_x - localc.m_x;
		gstack18.m_y = p_param1->m_y - localc.m_y;
		gstack18.m_z = p_param1->m_z - localc.m_z;
	}

	entity->SetCenter(gstack18);
	entity->m_velocity.m_x = p_param2->m_x;
	entity->m_velocity.m_y = p_param2->m_y;
	entity->m_velocity.m_z = p_param2->m_z;

	entity->m_orientation.m_m[0][0] = 0.0f;
	entity->m_orientation.m_m[0][1] = p_param3;
	entity->m_orientation.m_m[0][2] = 0.0f;

	m_unk0xe8++;

	return (undefined4)entity;
}

// FUNCTION: LEGORACERS 0x00412840
void SordidWatch0x140::FUN_00412840()
{
	// FIXME: wrong offsets now

	if (m_unk0x010.GetFlags0xb4() & 2) {
		FUN_00412970();
		m_unk0xd0 = 0;
		m_unk0xd4 = 0;
		m_unk0xd8 = 0;
		m_unk0xdc = 0;
		m_unk0xe0 = 0;
		m_unk0xe4 = 0;
		m_unk0x010.SetFlags0xb4U32(m_unk0x010.GetFlags0xb4U32() & ~0x1e);
	}
}

// FUNCTION: LEGORACERS 0x00412970
void SordidWatch0x140::FUN_00412970()
{
	// TODO: This matches, but it is a semantic mess

	m_unk0x010.m_partIndices[2] = 0;
	m_unk0x010.m_partIndices[1] = m_unk0x010.m_partIndices[0];

	for (LegoU32 i = 0; i < (undefined4) m_unk0x010.m_nodes[2] - 1; i++) {
		((CmbModelWithLinkPart0x38*) m_unk0x010.m_partIndices[0])[i].m_unk0x34 =
			&((CmbModelWithLinkPart0x38*) m_unk0x010.m_partIndices[0])[i + 1];
		((CmbModelWithLinkPart0x38*) m_unk0x010.m_partIndices[0])[i].m_unk0x30 = 0;
	}

	((CmbModelWithLinkPart0x38*) m_unk0x010.m_partIndices[0])[(undefined4) m_unk0x010.m_nodes[2] - 1].m_unk0x34 = 0;
	((CmbModelWithLinkPart0x38*) m_unk0x010.m_partIndices[0])[(undefined4) m_unk0x010.m_nodes[2] - 1].m_unk0x30 = 0;

// STUB: LEGORACERS 0x00412a00
GolWorldEntity* SordidWatch0x140::FUN_00412a00()
{
	STUB(0x00412a00);
	return NULL;
}

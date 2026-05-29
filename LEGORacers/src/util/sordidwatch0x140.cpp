#include "util/sordidwatch0x140.h"

#include "cmbmodelpart0x34.h"

// TODO: Add when the size is known
// DECOMP_SIZE_ASSERT(sordidwatch0x140, 0xTODO)

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
}

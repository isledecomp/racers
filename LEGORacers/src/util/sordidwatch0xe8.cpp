#include "util/sordidwatch0xe8.h"
#include "cmbmodelpart0x34.h"

// TODO: Add when the size is known
// DECOMP_SIZE_ASSERT(SordidWatch0xe8, 0xTODO)

SordidWatch0xe8::SordidWatch0xe8() {

}

// FUNCTION: LEGORACERS 0x00412840
void SordidWatch0xe8::FUN_00412840()
{
	if (m_unk0x04.GetFlags0xb4() & 2) {
		FUN_00412970();
		m_unk0xd0 = 0;
		m_unk0xd4 = 0;
		m_unk0xd8 = 0;
		m_unk0xdc = 0;
		m_unk0xe0 = 0;
		m_unk0xe4 = 0;
		m_unk0x04.SetFlags0xb4U32(m_unk0x04.GetFlags0xb4U32() & ~0x1e);
	}
}

// FUNCTION: LEGORACERS 0x00412970
void SordidWatch0xe8::FUN_00412970()
{
	m_unk0x04.m_modelParts[2] = NULL;
	m_unk0x04.m_modelParts[1] = m_unk0x04.m_modelParts[0];
	for (LegoU32 i = 0; i < m_unk0x04.m_partIndices[2] - 1; i++) {
		((CmbModelWithLinkPart0x38*)m_unk0x04.m_modelParts[0])[i].m_unk0x34 = &((CmbModelWithLinkPart0x38*)m_unk0x04.m_modelParts[0])[i + 1];
		((CmbModelWithLinkPart0x38*)m_unk0x04.m_modelParts[0])[i].m_unk0x30 = 0;
	}

	((CmbModelWithLinkPart0x38*)m_unk0x04.m_modelParts[0])[m_unk0x04.m_partIndices[2] - 1].m_unk0x34 = 0;
	((CmbModelWithLinkPart0x38*)m_unk0x04.m_modelParts[0])[m_unk0x04.m_partIndices[2] - 1].m_unk0x30 = 0;
}

#include "core/gol.h"
#include "decomp.h"
#include "duskwindbananarelic0x24.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "material/materialtable0x0c.h"
#include "race/racesession.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x170, 0x170)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x98, 0x98)

// FUNCTION: LEGORACERS 0x00493ae0
RaceSession::Field0x6dc::Field0x170::Field0x170()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00493b30
RaceSession::Field0x6dc::Field0x170::~Field0x170()
{
	FUN_00493e60();
}

// FUNCTION: LEGORACERS 0x00493b80
void RaceSession::Field0x6dc::Field0x170::Reset()
{
	m_unk0x000 = NULL;
	m_unk0x004 = NULL;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_unk0x010 = NULL;
	m_unk0x014 = 0;
	m_unk0x0b0 = 0;
	m_unk0x0b4 = 0;
	m_unk0x0b8 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0c4 = 0;
	m_unk0x0c8 = 0;
	m_unk0x0cc = 0;
	m_unk0x0d0 = 0;
	m_unk0x0d4 = 0;
	m_unk0x0dc = 0;
	m_unk0x0e0 = 0;
	m_unk0x0e4 = 0;
	m_unk0x0e8 = 0;
	::memset(m_unk0x0ec, 0, sizeof(m_unk0x0ec));
	::memset(m_unk0x128, 0, sizeof(m_unk0x128));
	m_unk0x13c = 0;
	m_unk0x140 = 0;
	m_unk0x144 = 0;
	m_unk0x148 = 0;
	m_unk0x14c = 0;
	m_unk0x150 = 0;
	m_unk0x160.m_red = 0;
	m_unk0x160.m_grn = 0;
	m_unk0x160.m_blu = 0;
	m_unk0x164.m_red = 0;
	m_unk0x164.m_grn = 0;
	m_unk0x164.m_blu = 0;
	m_unk0x168.m_red = 0;
	m_unk0x168.m_grn = 0;
	m_unk0x168.m_blu = 0;
	m_unk0x16c = 0;
	m_unk0x160.m_alp = 0xff;
	m_unk0x164.m_alp = 0xff;
	m_unk0x168.m_alp = 0xff;
}

// STUB: LEGORACERS 0x00493c90
void RaceSession::Field0x6dc::Field0x170::FUN_00493c90(const SetupParams* p_params)
{
	if (m_unk0x004 != NULL) {
		FUN_00493e60();
	}

	const SetupParams* params = p_params;

	m_unk0x000 = params->m_unk0x00;
	m_unk0x014 = params->m_material;
	m_unk0x0dc = params->m_unk0x0c;
	m_unk0x0e0 = params->m_unk0x10;
	m_unk0x0e4 = params->m_unk0x14;
	m_unk0x0e8 = m_unk0x0e4 + 1;
	m_unk0x0d8 = 1.0f / (LegoS32) m_unk0x0e0;

	LegoU32 i;
	for (i = 0; i < m_unk0x0e8; i++) {
		m_unk0x0ec[i] = params->m_unk0x18[i];
		m_unk0x128[i] = (&params->m_unk0x54)[i];
	}

	LegoU32 modelIndexCount = m_unk0x0e4 * m_unk0x0dc * m_unk0x0e0;
	LegoU32 doubledIndexCount = 2 * modelIndexCount;
	LegoU32 segmentCount = m_unk0x0e0;
	m_unk0x13c = params->m_unk0x68;

	LegoU32 generatedPointCount;
	if (m_unk0x014->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
		generatedPointCount = 0;
		if (m_unk0x13c <= segmentCount) {
			generatedPointCount = segmentCount - m_unk0x13c;
		}
		generatedPointCount += segmentCount + 1;
	}
	else {
		generatedPointCount = segmentCount + 1;
	}

	m_unk0x16c = generatedPointCount * m_unk0x0dc * m_unk0x0e8;
	if (segmentCount >= m_unk0x13c) {
		segmentCount = 2 * segmentCount - m_unk0x13c + 1;
	}

	LegoU32 stride = segmentCount * m_unk0x0e8;
	LegoU32 vertexCount = m_unk0x0dc * (2 * (0x40 / stride) + 5) + 2;
	m_unk0x004 = m_unk0x000->VTable0x14();
	m_unk0x004->VTable0x18(params->m_renderer, 1, m_unk0x16c, doubledIndexCount, vertexCount, 1);

	m_unk0x010 = m_unk0x000->VTable0x18();
	m_unk0x010->Allocate(m_unk0x0dc);
	m_unk0x018.FUN_00494c50(m_unk0x004, m_unk0x010, params->m_unk0x70, params->m_modelDistance);
	m_unk0x004->GetMaterialTable()->SetPosition(0, params->m_material);
}

// FUNCTION: LEGORACERS 0x00493e60
void RaceSession::Field0x6dc::Field0x170::FUN_00493e60()
{
	m_unk0x018.VTable0x54();

	if (m_unk0x000 != NULL) {
		if (m_unk0x010 != NULL) {
			m_unk0x000->VTable0x4c(m_unk0x010);
		}

		if (m_unk0x004 != NULL) {
			m_unk0x000->VTable0x48(m_unk0x004);
		}
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00494820
void RaceSession::Field0x6dc::Field0x170::FUN_00494820(
	const ColorRGBA* p_unk0x04,
	const ColorRGBA* p_unk0x08,
	const ColorRGBA* p_unk0x0c
)
{
	m_unk0x160 = *p_unk0x04;
	m_unk0x164 = *p_unk0x08;
	m_unk0x168 = *p_unk0x0c;
}

// FUNCTION: LEGORACERS 0x00494c00
RaceSession::Field0x6dc::Field0x98::Field0x98()
{
	m_unk0x90 = 0;
	m_unk0x94 = 0;
}

// STUB: LEGORACERS 0x00494c40
RaceSession::Field0x6dc::Field0x98::~Field0x98()
{
	VTable0x54();
}

// STUB: LEGORACERS 0x00494c50
void RaceSession::Field0x6dc::Field0x98::FUN_00494c50(
	GolModelBase* p_model,
	GolSceneNode* p_sceneNode,
	undefined4 p_unk0x0c,
	LegoFloat p_modelDistance
)
{
	VTable0x50(p_model, p_modelDistance);
	m_unk0x90 = p_sceneNode;
	m_unk0x94 = p_unk0x0c;
}

// FUNCTION: LEGORACERS 0x00494c80
void RaceSession::Field0x6dc::Field0x98::VTable0x54()
{
	m_unk0x90 = 0;
}

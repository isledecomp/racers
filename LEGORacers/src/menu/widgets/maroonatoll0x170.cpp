#include "menu/widgets/maroonatoll0x170.h"

#include "audio/soundgroupbinding.h"
#include "golerror.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "mesh/golmodelbase.h"
#include "mesh/golmodelmaterialtable.h"
#include "racer/lavendervault0x764.h"
#include "racer/turquoiseglowcolor.h"
#include "save/savesystem.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(MaroonAtoll0x170, 0x170)
DECOMP_SIZE_ASSERT(MaroonAtoll0x170::CreateParams0x80, 0x80)

// GLOBAL: LEGORACERS 0x004b39d0
LegoFloat g_maroonAtollMaxFloat = FLT_MAX;

// FUNCTION: LEGORACERS 0x00483970
MaroonAtoll0x170::MaroonAtoll0x170()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004839e0
MaroonAtoll0x170::~MaroonAtoll0x170()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00483a30
void MaroonAtoll0x170::Reset()
{
	m_unk0xcc = 0;
	m_materialTables = NULL;
	memset(&m_unk0xd0, 0, sizeof(m_unk0xd0));
	VioletShoal0xc0::Reset();
}

// FUNCTION: LEGORACERS 0x00483a60
LegoBool32 MaroonAtoll0x170::FUN_00483a60(
	CreateParams0x80* p_createParams,
	CeruleanEmperor0x4c::Entry0x18* p_styleEntry
)
{
	m_unk0xc8 = p_createParams->m_context;
	m_unk0xc4 = p_createParams->m_unk0x78;
	m_unk0xcc = p_createParams->m_unk0x7c;
	FUN_00483ee0();

	if (VioletShoal0xc0::FUN_0046cb10(p_createParams, p_styleEntry)) {
		for (LegoS32 i = 0; i < m_unk0x60; i++) {
			m_golExport->VTable0x48(m_unk0x7c[i].m_model);
			m_unk0x7c[i].m_model = NULL;
		}

		FUN_00483b60(m_unk0x60);
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00483af0
LegoBool32 MaroonAtoll0x170::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		for (LegoS32 i = 0; i < m_unk0x60; i++) {
			m_unk0x7c[i].m_model = NULL;
		}

		if (m_materialTables) {
			delete[] m_materialTables;
		}

		result = VioletShoal0xc0::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00483b60
void MaroonAtoll0x170::FUN_00483b60(LegoS32)
{
	m_materialTables = new GolBillboard::Field0x2c[m_unk0x68];
	if (m_materialTables == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoS32 i = 0; i < m_unk0x68; i++) {
		m_materialTables[i].Initialize(m_renderer, 2);
	}
}

// FUNCTION: LEGORACERS 0x00483c20
void MaroonAtoll0x170::CopyModelMaterialTable(GolModelBase* p_model, GolBillboard::Field0x2c* p_materialTable)
{
	GolModelMaterialTable* source = p_model->GetMaterialTable();
	LegoS32 count = source->GetCount();
	for (LegoS32 i = 0; i < count; i++) {
		void* material = source->GetPosition(i);
		if (material) {
			p_materialTable->SetPosition(i, material);
		}
	}
}

// FUNCTION: LEGORACERS 0x00483c60
void MaroonAtoll0x170::FUN_00483c60(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_config->GetHatCount(); i++) {
		TurquoiseGlowColor color;
		m_unk0xc8->m_unk0x258.GetUnk0x1cfc().GetUnk0x248()->FUN_0042b330(&color);

		if (color.m_unk0x00 != i) {
			LegoS32 unlockFlag = p_config->GetHatUnlockFlag(i);
			if (unlockFlag == 0x80) {
				if (!p_saveSystem->GetUnk0x18c4().FUN_0042f280()) {
					continue;
				}
			}
			else if (unlockFlag > 2 && !(p_unlockFlags & (1 << (unlockFlag - 3)))) {
				continue;
			}
		}

		m_unk0xd0[m_unk0x68++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483d00
void MaroonAtoll0x170::FUN_00483d00(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_config->GetFaceCount(); i++) {
		TurquoiseGlowColor color;
		m_unk0xc8->m_unk0x258.GetUnk0x1cfc().GetUnk0x248()->FUN_0042b330(&color);

		if (color.m_unk0x01 != i) {
			LegoS32 unlockFlag = p_config->GetFaceUnlockFlag(i);
			if (unlockFlag == 0x80) {
				if (!p_saveSystem->GetUnk0x18c4().FUN_0042f280()) {
					continue;
				}
			}
			else if (unlockFlag > 2 && !(p_unlockFlags & (1 << (unlockFlag - 3)))) {
				continue;
			}
		}

		m_unk0xd0[m_unk0x68++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483da0
void MaroonAtoll0x170::FUN_00483da0(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_config->GetTorsoCount(); i++) {
		TurquoiseGlowColor color;
		m_unk0xc8->m_unk0x258.GetUnk0x1cfc().GetUnk0x248()->FUN_0042b330(&color);

		if (color.m_unk0x02 != i) {
			LegoS32 unlockFlag = p_config->GetTorsoUnlockFlag(i);
			if (unlockFlag == 0x80) {
				if (!p_saveSystem->GetUnk0x18c4().FUN_0042f280()) {
					continue;
				}
			}
			else if (unlockFlag > 2 && !(p_unlockFlags & (1 << (unlockFlag - 3)))) {
				continue;
			}
		}

		m_unk0xd0[m_unk0x68++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483e40
void MaroonAtoll0x170::FUN_00483e40(LavenderVault0x764* p_config, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_config->GetLegCount(); i++) {
		TurquoiseGlowColor color;
		m_unk0xc8->m_unk0x258.GetUnk0x1cfc().GetUnk0x248()->FUN_0042b330(&color);

		if (color.m_unk0x03 != i) {
			LegoS32 unlockFlag = p_config->GetLegUnlockFlag(i);
			if (unlockFlag == 0x80) {
				if (!p_saveSystem->GetUnk0x18c4().FUN_0042f280()) {
					continue;
				}
			}
			else if (unlockFlag > 2 && !(p_unlockFlags & (1 << (unlockFlag - 3)))) {
				continue;
			}
		}

		m_unk0xd0[m_unk0x68++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483ee0
void MaroonAtoll0x170::FUN_00483ee0()
{
	SaveSystem* saveSystem = &m_unk0xc8->m_unk0x258;
	LavenderVault0x764* config = &m_unk0xc8->m_unk0x437c;
	LegoU32 unlockFlags = saveSystem->GetUnk0x18c4().FUN_0042f1e0();

	switch (m_unk0xcc) {
	case 0:
		FUN_00483c60(config, saveSystem, unlockFlags);
		break;
	case 1:
		FUN_00483d00(config, saveSystem, unlockFlags);
		break;
	case 2:
		FUN_00483da0(config, saveSystem, unlockFlags);
		break;
	case 3:
		FUN_00483e40(config, saveSystem, unlockFlags);
		break;
	}
}

// FUNCTION: LEGORACERS 0x00483f70
void MaroonAtoll0x170::VTable0x60(LegoS32 p_index)
{
	GolModelEntity* entity = GetItemEntity(p_index);
	LegoS32 modelIndex = m_unk0xd0[FUN_0046c9a0(m_unk0xb8 + p_index)];
	GolModelBase* model;
	void* material;
	LegoChar materialName[8];

	switch (m_unk0xcc) {
	case 0:
		model = m_unk0xc4->FUN_00499320(modelIndex);
		material = model->GetMaterialTable()->GetPosition(0);
		m_unk0xc4->FUN_004992f0(model);
		materialName[0] = '\0';
		break;
	case 1:
		model = m_unk0xc4->FUN_00499380(0);
		material = m_unk0xc4->FUN_00499470(modelIndex);
		::strncpy(materialName, "face", sizeof(materialName));
		break;
	case 2:
		model = m_unk0xc4->FUN_004993d0(modelIndex);
		material = m_unk0xc4->FUN_004994b0(modelIndex);
		::strncpy(materialName, "torso", sizeof(materialName));
		break;
	case 3:
		model = m_unk0xc4->FUN_00499420(modelIndex);
		material = m_unk0xc4->FUN_004994f0(modelIndex);
		::strncpy(materialName, "legs", sizeof(materialName));
		break;
	default:
		model = NULL;
		material = NULL;
		break;
	}

	entity->VTable0x50(model, g_maroonAtollMaxFloat);

	GolBillboard::Field0x2c* materialTable = &m_materialTables[FUN_0046c9a0(m_unk0xb8 + p_index)];
	CopyModelMaterialTable(model, materialTable);

	LegoS32 materialIndex = model->GetMaterialTable()->FindEntryIndexByName(materialName);
	if (materialIndex != -1) {
		materialTable->SetPosition(materialIndex, material);
		entity->SetPrimaryMaterialTable(materialTable);
	}

	VioletShoal0xc0::VTable0x60(p_index);
}

// FUNCTION: LEGORACERS 0x00484100
void MaroonAtoll0x170::VTable0x50(undefined4 p_index)
{
	if (m_unk0x68) {
		m_unk0x6c = p_index;
		m_unk0xb8 = FUN_0046c9a0(p_index - m_unk0x64);

		if (!m_unk0x70) {
			if (!m_unk0xcc) {
				::memset(m_unk0xc4->GetUnk0x30(), 0, 7 * sizeof(LegoBool32));
			}

			for (LegoS32 i = 0; i < m_unk0x60; i++) {
				VTable0x60(i);
			}

			VTable0x40();
		}
	}
}

// FUNCTION: LEGORACERS 0x00484170
void MaroonAtoll0x170::FUN_00484170(LegoS32 p_index)
{
	for (LegoS32 i = 0; i < m_unk0x68; i++) {
		if (m_unk0xd0[i] == p_index) {
			VTable0x50(i);
		}
	}
}

// FUNCTION: LEGORACERS 0x004841b0
LegoS32 MaroonAtoll0x170::VTable0x54()
{
	if (!m_unk0x68) {
		return 0;
	}

	if (m_unk0x70) {
		return m_unk0x6c;
	}

	if (m_unk0x6c >= m_unk0x68 - 1 && m_unk0x68 < m_unk0x60 - 1) {
		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[2]);
	}
	else {
		VioletShoal0xc0::VTable0x54();
		VTable0x50(FUN_0046c9a0(m_unk0x6c + 1));

		LegoS32 firstVisibleIndex = static_cast<LegoS32>(m_unk0x64);
		if (m_unk0x68 >= m_unk0x60 - 1 || m_unk0x68 - m_unk0x6c > m_unk0x60 - firstVisibleIndex - 1) {
			VTable0x60(m_unk0x60 - 1);
		}

		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[0]);
	}

	if (!m_unk0xcc) {
		::memset(m_unk0xc4->GetUnk0x30(), 0, 7 * sizeof(LegoBool32));

		for (LegoS32 i = 0; i < m_unk0x60; i++) {
			m_unk0xc4->FUN_004992f0(m_unk0x7c[i].m_model);
		}
	}

	return m_unk0x6c;
}

// FUNCTION: LEGORACERS 0x00484290
LegoS32 MaroonAtoll0x170::VTable0x58()
{
	if (!m_unk0x68) {
		return 0;
	}

	if (m_unk0x70) {
		return m_unk0x6c;
	}

	if (!m_unk0x6c && m_unk0x68 < m_unk0x60 - 1) {
		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[2]);
	}
	else {
		VioletShoal0xc0::VTable0x58();
		VTable0x50(FUN_0046c9a0(m_unk0x6c - 1));

		LegoS32 firstVisibleIndex = static_cast<LegoS32>(m_unk0x64);
		if (m_unk0x68 >= m_unk0x60 - 1 || m_unk0x6c > firstVisibleIndex - 1) {
			VTable0x60(0);
		}

		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[1]);
	}

	if (!m_unk0xcc) {
		::memset(m_unk0xc4->GetUnk0x30(), 0, 7 * sizeof(LegoBool32));

		for (LegoS32 i = 0; i < m_unk0x60; i++) {
			m_unk0xc4->FUN_004992f0(m_unk0x7c[i].m_model);
		}
	}

	return m_unk0x6c;
}

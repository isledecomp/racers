#include "menu/widgets/maroonatoll0x170.h"

#include "audio/soundgroupbinding.h"
#include "mesh/golmodelbase.h"
#include "mesh/golmodelmaterialtable.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(MaroonAtoll0x170, 0x170)

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

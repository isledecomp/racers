#include "menu/widgets/menuracercarousel.h"

#include "audio/soundgroupbinding.h"
#include "golerror.h"
#include "golmodelbase.h"
#include "golmodelmaterialtable.h"
#include "menu/menugamecontext.h"
#include "racer/drivercosmetics.h"
#include "racer/driverpartcatalog.h"
#include "save/savesystem.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(MenuRacerCarousel, 0x170)
DECOMP_SIZE_ASSERT(MenuRacerCarousel::CreateParams, 0x80)

// GLOBAL: LEGORACERS 0x004b39d0
LegoFloat g_maroonAtollMaxFloat = FLT_MAX;

// FUNCTION: LEGORACERS 0x00483970
MenuRacerCarousel::MenuRacerCarousel()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004839e0
MenuRacerCarousel::~MenuRacerCarousel()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00483a30
void MenuRacerCarousel::Reset()
{
	m_unk0xcc = 0;
	m_materialTables = NULL;
	memset(&m_unk0xd0, 0, sizeof(m_unk0xd0));
	MenuModelCarousel::Reset();
}

// FUNCTION: LEGORACERS 0x00483a60
LegoBool32 MenuRacerCarousel::FUN_00483a60(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry)
{
	m_unk0xc8 = p_createParams->m_context;
	m_headBuilder = p_createParams->m_headBuilder;
	m_unk0xcc = p_createParams->m_unk0x7c;
	FUN_00483ee0();

	if (MenuModelCarousel::Create(p_createParams, p_styleEntry)) {
		for (LegoS32 i = 0; i < m_slotCount; i++) {
			m_golExport->VTable0x48(m_items[i].m_model);
			m_items[i].m_model = NULL;
		}

		FUN_00483b60(m_slotCount);
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00483af0
LegoBool32 MenuRacerCarousel::Destroy()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		for (LegoS32 i = 0; i < m_slotCount; i++) {
			m_items[i].m_model = NULL;
		}

		if (m_materialTables) {
			delete[] m_materialTables;
		}

		result = MenuModelCarousel::Destroy();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00483b60
void MenuRacerCarousel::FUN_00483b60(LegoS32)
{
	m_materialTables = new GolBillboard::Field0x2c[m_itemCount];
	if (m_materialTables == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoS32 i = 0; i < m_itemCount; i++) {
		m_materialTables[i].Initialize(m_renderer, 2);
	}
}

// FUNCTION: LEGORACERS 0x00483c20
void MenuRacerCarousel::CopyModelMaterialTable(GolModelBase* p_model, GolBillboard::Field0x2c* p_materialTable)
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
void MenuRacerCarousel::FUN_00483c60(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_partCatalog->GetHatCount(); i++) {
		DriverCosmetics cosmetics;
		m_unk0xc8->m_saveSystem.GetActiveRecord().GetSelectedRecord()->GetCosmetics(&cosmetics);

		if (cosmetics.m_hatIndex != i) {
			LegoS32 unlockFlag = p_partCatalog->GetHatUnlockFlag(i);
			if (unlockFlag == 0x80) {
				if (!p_saveSystem->GetGameState().AreAllRacesUnlocked()) {
					continue;
				}
			}
			else if (unlockFlag > 2 && !(p_unlockFlags & (1 << (unlockFlag - 3)))) {
				continue;
			}
		}

		m_unk0xd0[m_itemCount++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483d00
void MenuRacerCarousel::FUN_00483d00(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_partCatalog->GetFaceCount(); i++) {
		DriverCosmetics cosmetics;
		m_unk0xc8->m_saveSystem.GetActiveRecord().GetSelectedRecord()->GetCosmetics(&cosmetics);

		if (cosmetics.m_faceIndex != i) {
			LegoS32 unlockFlag = p_partCatalog->GetFaceUnlockFlag(i);
			if (unlockFlag == 0x80) {
				if (!p_saveSystem->GetGameState().AreAllRacesUnlocked()) {
					continue;
				}
			}
			else if (unlockFlag > 2 && !(p_unlockFlags & (1 << (unlockFlag - 3)))) {
				continue;
			}
		}

		m_unk0xd0[m_itemCount++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483da0
void MenuRacerCarousel::FUN_00483da0(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_partCatalog->GetTorsoCount(); i++) {
		DriverCosmetics cosmetics;
		m_unk0xc8->m_saveSystem.GetActiveRecord().GetSelectedRecord()->GetCosmetics(&cosmetics);

		if (cosmetics.m_torsoIndex != i) {
			LegoS32 unlockFlag = p_partCatalog->GetTorsoUnlockFlag(i);
			if (unlockFlag == 0x80) {
				if (!p_saveSystem->GetGameState().AreAllRacesUnlocked()) {
					continue;
				}
			}
			else if (unlockFlag > 2 && !(p_unlockFlags & (1 << (unlockFlag - 3)))) {
				continue;
			}
		}

		m_unk0xd0[m_itemCount++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483e40
void MenuRacerCarousel::FUN_00483e40(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_partCatalog->GetLegCount(); i++) {
		DriverCosmetics cosmetics;
		m_unk0xc8->m_saveSystem.GetActiveRecord().GetSelectedRecord()->GetCosmetics(&cosmetics);

		if (cosmetics.m_legIndex != i) {
			LegoS32 unlockFlag = p_partCatalog->GetLegUnlockFlag(i);
			if (unlockFlag == 0x80) {
				if (!p_saveSystem->GetGameState().AreAllRacesUnlocked()) {
					continue;
				}
			}
			else if (unlockFlag > 2 && !(p_unlockFlags & (1 << (unlockFlag - 3)))) {
				continue;
			}
		}

		m_unk0xd0[m_itemCount++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483ee0
void MenuRacerCarousel::FUN_00483ee0()
{
	SaveSystem* saveSystem = &m_unk0xc8->m_saveSystem;
	DriverPartCatalog* partCatalog = &m_unk0xc8->m_partCatalog;
	LegoU32 unlockFlags = saveSystem->GetGameState().GetPartUnlockFlags();

	switch (m_unk0xcc) {
	case 0:
		FUN_00483c60(partCatalog, saveSystem, unlockFlags);
		break;
	case 1:
		FUN_00483d00(partCatalog, saveSystem, unlockFlags);
		break;
	case 2:
		FUN_00483da0(partCatalog, saveSystem, unlockFlags);
		break;
	case 3:
		FUN_00483e40(partCatalog, saveSystem, unlockFlags);
		break;
	}
}

// FUNCTION: LEGORACERS 0x00483f70
void MenuRacerCarousel::VTable0x60(LegoS32 p_index)
{
	GolModelEntity* entity = GetItemEntity(p_index);
	LegoS32 modelIndex = m_unk0xd0[WrapIndex(m_unk0xb8 + p_index)];
	GolModelBase* model;
	void* material;
	LegoChar materialName[8];

	switch (m_unk0xcc) {
	case 0:
		model = m_headBuilder->LoadHatModel(modelIndex);
		material = model->GetMaterialTable()->GetPosition(0);
		m_headBuilder->MarkHatModelUsed(model);
		materialName[0] = '\0';
		break;
	case 1:
		model = m_headBuilder->GetFaceModel(0);
		material = m_headBuilder->FindFaceMaterial(modelIndex);
		::strncpy(materialName, "face", sizeof(materialName));
		break;
	case 2:
		model = m_headBuilder->GetTorsoModel(modelIndex);
		material = m_headBuilder->FindTorsoMaterial(modelIndex);
		::strncpy(materialName, "torso", sizeof(materialName));
		break;
	case 3:
		model = m_headBuilder->GetLegModel(modelIndex);
		material = m_headBuilder->FindLegMaterial(modelIndex);
		::strncpy(materialName, "legs", sizeof(materialName));
		break;
	default:
		model = NULL;
		material = NULL;
		break;
	}

	entity->VTable0x50(model, g_maroonAtollMaxFloat);

	GolBillboard::Field0x2c* materialTable = &m_materialTables[WrapIndex(m_unk0xb8 + p_index)];
	CopyModelMaterialTable(model, materialTable);

	LegoS32 materialIndex = model->GetMaterialTable()->FindEntryIndexByName(materialName);
	if (materialIndex != -1) {
		materialTable->SetPosition(materialIndex, material);
		entity->SetPrimaryMaterialTable(materialTable);
	}

	MenuModelCarousel::VTable0x60(p_index);
}

// FUNCTION: LEGORACERS 0x00484100
void MenuRacerCarousel::SetSelection(undefined4 p_index)
{
	if (m_itemCount) {
		m_selectedIndex = p_index;
		m_unk0xb8 = WrapIndex(p_index - m_focusedSlot);

		if (!m_scrolling) {
			if (!m_unk0xcc) {
				::memset(m_headBuilder->GetHatModelUsedFlags(), 0, 7 * sizeof(LegoBool32));
			}

			for (LegoS32 i = 0; i < m_slotCount; i++) {
				VTable0x60(i);
			}

			SnapToSelection();
		}
	}
}

// FUNCTION: LEGORACERS 0x00484170
void MenuRacerCarousel::FUN_00484170(LegoS32 p_index)
{
	for (LegoS32 i = 0; i < m_itemCount; i++) {
		if (m_unk0xd0[i] == p_index) {
			SetSelection(i);
		}
	}
}

// FUNCTION: LEGORACERS 0x004841b0
LegoS32 MenuRacerCarousel::ScrollNext()
{
	if (!m_itemCount) {
		return 0;
	}

	if (m_scrolling) {
		return m_selectedIndex;
	}

	if (m_selectedIndex >= m_itemCount - 1 && m_itemCount < m_slotCount - 1) {
		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[2]);
	}
	else {
		MenuModelCarousel::ScrollNext();
		SetSelection(WrapIndex(m_selectedIndex + 1));

		LegoS32 firstVisibleIndex = static_cast<LegoS32>(m_focusedSlot);
		if (m_itemCount >= m_slotCount - 1 || m_itemCount - m_selectedIndex > m_slotCount - firstVisibleIndex - 1) {
			VTable0x60(m_slotCount - 1);
		}

		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[0]);
	}

	if (!m_unk0xcc) {
		::memset(m_headBuilder->GetHatModelUsedFlags(), 0, 7 * sizeof(LegoBool32));

		for (LegoS32 i = 0; i < m_slotCount; i++) {
			m_headBuilder->MarkHatModelUsed(m_items[i].m_model);
		}
	}

	return m_selectedIndex;
}

// FUNCTION: LEGORACERS 0x00484290
LegoS32 MenuRacerCarousel::ScrollPrevious()
{
	if (!m_itemCount) {
		return 0;
	}

	if (m_scrolling) {
		return m_selectedIndex;
	}

	if (!m_selectedIndex && m_itemCount < m_slotCount - 1) {
		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[2]);
	}
	else {
		MenuModelCarousel::ScrollPrevious();
		SetSelection(WrapIndex(m_selectedIndex - 1));

		LegoS32 firstVisibleIndex = static_cast<LegoS32>(m_focusedSlot);
		if (m_itemCount >= m_slotCount - 1 || m_selectedIndex > firstVisibleIndex - 1) {
			VTable0x60(0);
		}

		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[1]);
	}

	if (!m_unk0xcc) {
		::memset(m_headBuilder->GetHatModelUsedFlags(), 0, 7 * sizeof(LegoBool32));

		for (LegoS32 i = 0; i < m_slotCount; i++) {
			m_headBuilder->MarkHatModelUsed(m_items[i].m_model);
		}
	}

	return m_selectedIndex;
}

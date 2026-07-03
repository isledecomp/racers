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
	m_partType = 0;
	m_materialTables = NULL;
	memset(&m_itemValues, 0, sizeof(m_itemValues));
	MenuModelCarousel::Reset();
}

// FUNCTION: LEGORACERS 0x00483a60
LegoBool32 MenuRacerCarousel::Create(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry)
{
	m_context = p_createParams->m_context;
	m_headBuilder = p_createParams->m_headBuilder;
	m_partType = p_createParams->m_partType;
	CollectItems();

	if (MenuModelCarousel::Create(p_createParams, p_styleEntry)) {
		for (LegoS32 i = 0; i < m_slotCount; i++) {
			m_golExport->DestroyModel(m_items[i].m_model);
			m_items[i].m_model = NULL;
		}

		CreateMaterialTables(m_slotCount);
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
void MenuRacerCarousel::CreateMaterialTables(LegoS32)
{
	m_materialTables = new GolBillboard::ManagedMaterialTable[m_itemCount];
	if (m_materialTables == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoS32 i = 0; i < m_itemCount; i++) {
		m_materialTables[i].Initialize(m_renderer, 2);
	}
}

// FUNCTION: LEGORACERS 0x00483c20
void MenuRacerCarousel::CopyModelMaterialTable(
	GolModelBase* p_model,
	GolBillboard::ManagedMaterialTable* p_materialTable
)
{
	GolModelMaterialTable* source = p_model->GetMaterialTable();
	LegoS32 count = source->GetCount();
	for (LegoS32 i = 0; i < count; i++) {
		void* material = source->GetEntry(i);
		if (material) {
			p_materialTable->SetEntry(i, material);
		}
	}
}

// FUNCTION: LEGORACERS 0x00483c60
void MenuRacerCarousel::CollectHats(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_partCatalog->GetHatCount(); i++) {
		DriverCosmetics cosmetics;
		m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord()->GetCosmetics(&cosmetics);

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

		m_itemValues[m_itemCount++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483d00
void MenuRacerCarousel::CollectFaces(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_partCatalog->GetFaceCount(); i++) {
		DriverCosmetics cosmetics;
		m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord()->GetCosmetics(&cosmetics);

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

		m_itemValues[m_itemCount++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483da0
void MenuRacerCarousel::CollectTorsos(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_partCatalog->GetTorsoCount(); i++) {
		DriverCosmetics cosmetics;
		m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord()->GetCosmetics(&cosmetics);

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

		m_itemValues[m_itemCount++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483e40
void MenuRacerCarousel::CollectLegs(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags)
{
	for (LegoS32 i = 0; i < p_partCatalog->GetLegCount(); i++) {
		DriverCosmetics cosmetics;
		m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord()->GetCosmetics(&cosmetics);

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

		m_itemValues[m_itemCount++] = i;
	}
}

// FUNCTION: LEGORACERS 0x00483ee0
void MenuRacerCarousel::CollectItems()
{
	SaveSystem* saveSystem = &m_context->m_saveSystem;
	DriverPartCatalog* partCatalog = &m_context->m_partCatalog;
	LegoU32 unlockFlags = saveSystem->GetGameState().GetPartUnlockFlags();

	switch (m_partType) {
	case 0:
		CollectHats(partCatalog, saveSystem, unlockFlags);
		break;
	case 1:
		CollectFaces(partCatalog, saveSystem, unlockFlags);
		break;
	case 2:
		CollectTorsos(partCatalog, saveSystem, unlockFlags);
		break;
	case 3:
		CollectLegs(partCatalog, saveSystem, unlockFlags);
		break;
	}
}

// FUNCTION: LEGORACERS 0x00483f70
void MenuRacerCarousel::RefreshItemModel(LegoS32 p_index)
{
	GolModelEntity* entity = GetItemEntity(p_index);
	LegoS32 modelIndex = m_itemValues[WrapIndex(m_ringBaseIndex + p_index)];
	GolModelBase* model;
	void* material;
	LegoChar materialName[8];

	switch (m_partType) {
	case 0:
		model = m_headBuilder->LoadHatModel(modelIndex);
		material = model->GetMaterialTable()->GetEntry(0);
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

	entity->SetPrimaryModel(model, g_maroonAtollMaxFloat);

	GolBillboard::ManagedMaterialTable* materialTable = &m_materialTables[WrapIndex(m_ringBaseIndex + p_index)];
	CopyModelMaterialTable(model, materialTable);

	LegoS32 materialIndex = model->GetMaterialTable()->FindEntryIndexByName(materialName);
	if (materialIndex != -1) {
		materialTable->SetEntry(materialIndex, material);
		entity->SetPrimaryMaterialTable(materialTable);
	}

	MenuModelCarousel::RefreshItemModel(p_index);
}

// FUNCTION: LEGORACERS 0x00484100
void MenuRacerCarousel::SetSelection(undefined4 p_index)
{
	if (m_itemCount) {
		m_selectedIndex = p_index;
		m_ringBaseIndex = WrapIndex(p_index - m_focusedSlot);

		if (!m_scrolling) {
			if (!m_partType) {
				::memset(m_headBuilder->GetHatModelUsedFlags(), 0, 7 * sizeof(LegoBool32));
			}

			for (LegoS32 i = 0; i < m_slotCount; i++) {
				RefreshItemModel(i);
			}

			SnapToSelection();
		}
	}
}

// FUNCTION: LEGORACERS 0x00484170
void MenuRacerCarousel::SelectValue(LegoS32 p_index)
{
	for (LegoS32 i = 0; i < m_itemCount; i++) {
		if (m_itemValues[i] == p_index) {
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
			RefreshItemModel(m_slotCount - 1);
		}

		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[0]);
	}

	if (!m_partType) {
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
			RefreshItemModel(0);
		}

		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[1]);
	}

	if (!m_partType) {
		::memset(m_headBuilder->GetHatModelUsedFlags(), 0, 7 * sizeof(LegoBool32));

		for (LegoS32 i = 0; i < m_slotCount; i++) {
			m_headBuilder->MarkHatModelUsed(m_items[i].m_model);
		}
	}

	return m_selectedIndex;
}

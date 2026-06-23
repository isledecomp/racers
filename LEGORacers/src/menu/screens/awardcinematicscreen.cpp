#include "menu/screens/awardcinematicscreen.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "core/gol.h"
#include "duskwindbananarelic0x24.h"
#include "golhashtable.h"
#include "golmodelbase.h"
#include "golstring.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "mabmaterialanimationitem0x8.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "model/carbuildmodel.h"
#include "world/golworlddatabase.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(AwardCinematicScreen, 0x7b0)

// FUNCTION: LEGORACERS 0x00475c30
AwardCinematicScreen::AwardCinematicScreen() : m_unk0x79c(NULL), m_unk0x7a4(0), m_unk0x7a8(0), m_unk0x7ac(0)
{
	m_unk0x7a0 = -1;
}

// FUNCTION: LEGORACERS 0x00475cd0
AwardCinematicScreen::~AwardCinematicScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00475d30
LegoBool32 AwardCinematicScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_unk0x7ac = 0;
	m_unk0x7a8 = 0;
	m_unk0x7a4 = 0;

	if (p_createParams->m_menuId == c_menuWinRrCar && p_context->m_unk0x21f4.IsInitialized()) {
		p_context->m_unk0x21f4.FUN_00499f00();
	}

	if (!MenuSceneScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	undefined4 musicId = 1;

	switch (m_unk0x28c) {
	case c_menuChampAward1:
		musicId = 2;
		break;
	case c_menuChampAward2:
		musicId = 3;
		break;
	case c_menuChampAward3:
		musicId = 4;
		break;
	case c_menuChampAward4:
		musicId = 0x0b;
		break;
	case c_menuWinCar:
		musicId = 0x0d;
		break;
	case c_menuWinRrCar:
		musicId = 0x0e;
		break;
	case c_menuWinVvCar:
		musicId = 0x0f;
		break;
	case c_menuCircuit7:
		musicId = 0x0c;
		break;
	}

	FUN_00480470(p_context, musicId, FALSE);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00475e50
LegoBool32 AwardCinematicScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	FUN_004801e0();
	FUN_004800c0(m_context);
	m_unk0x658.FUN_00479590();
	m_unk0x6a8.VTable0x54();

	if (m_unk0x79c) {
		m_golExport->VTable0x48(m_unk0x79c);
		m_unk0x79c = NULL;
	}

	m_unk0x7a0 = -1;

	if (m_context) {
		if (m_context->m_modelBuilder.GetMusicGroup() && m_context->m_modelBuilder.GetMusicInstance()) {
			m_context->m_modelBuilder.GetMusicInstance()->Stop();
			m_context->m_modelBuilder.GetMusicGroup()->DestroyMusicInstance(
				m_context->m_modelBuilder.GetMusicInstance()
			);
			m_context->m_modelBuilder.SetMusicInstance(NULL);
		}
	}

	LegoBool32 result = MenuSceneScreen::Destroy();
	if (m_unk0x28c == c_menuWinRrCar) {
		MenuGameContext* context = m_context;
		if (context->m_unk0x21f4.IsInitialized()) {
			m_context->m_unk0x21f4.FUN_00499ee0();
		}
	}

	return result;
}

// STUB: LEGORACERS 0x00475f40
void AwardCinematicScreen::VTable0x4c()
{
	struct ResourcePathLocals {
		LegoChar m_name[12];
		GolString m_string;
		LegoChar m_path[20];
	} locals;

	if (m_unk0x28c != c_menuWinVvCar) {
		if (!m_context->m_modelBuilder.HasMenuResources()) {
			FUN_00480210(m_context, FALSE);
		}

		if (!m_context->m_cosmeticTable.HasEntries()) {
			FUN_00480310();
		}
	}

	if (m_unk0x28c == c_menuWinCar) {
		if (!m_context->m_chassisModels.HasItems() || !m_context->m_championDefinitions.HasDefinitions()) {
			FUN_00480110(1);
		}
	}

	m_menuNameStrings->CopyStringByIndex(&locals.m_string, m_unk0x28c);
	locals.m_string.CopyToString(locals.m_name);
	::sprintf(locals.m_path, "MENUDATA\\%s", locals.m_name);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(locals.m_path);
	}

	CreateRegion(&m_unk0x368, m_unk0x28c);
	m_unk0x368.m_unk0x2cc = FALSE;

	if (m_unk0x28c == c_menuCircuit7) {
		SaveRecordList::Record* record = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord();
		if (record) {
			m_context->m_context->m_playerSetupSlots[0].m_unk0x10 = 0;
			record->GetCosmetics(&m_context->m_context->m_playerSetupSlots[0].m_cosmetics);
			m_context->m_context->m_playerSetupSlots[0].m_driverName[0] = '\0';
		}
	}

	GolAnimatedEntity* sourceDriverEntity = NULL;
	GolModelEntity* carBodyEntity = NULL;
	GolAnimatedEntity* swapEntity = NULL;
	GolAnimatedEntity* pLegEntity = NULL;
	for (LegoU32 i = 0; i < m_unk0x368.m_unk0x58.GetWorldDatabaseCount(); i++) {
		GolWorldDatabase* worldDatabase = m_unk0x368.m_unk0x58.GetWorldDatabase(i);
		if (!sourceDriverEntity) {
			sourceDriverEntity = worldDatabase->FindUnk0xc0("guy1");
		}

		if (!carBodyEntity) {
			carBodyEntity = worldDatabase->FindUnk0xb4("carbody");
			if (!carBodyEntity) {
				carBodyEntity = worldDatabase->FindUnk0xc0("carbody");
			}
		}

		if (!swapEntity) {
			swapEntity = worldDatabase->FindUnk0xc0("swap");
		}

		if (!pLegEntity) {
			pLegEntity = worldDatabase->FindUnk0xc0("pleg");
		}
	}

	if (m_unk0x28c != c_menuWinVvCar) {
		LegoRacers::Context* racersContext = m_context->m_context;
		LegoU32 slotIndex = 0;
		LegoRacers::Context::PlayerSetupSlot* slot = racersContext->m_playerSetupSlots;

		if (slot->m_unk0x10) {
			while (slotIndex < racersContext->m_playerCount) {
				slot++;
				slotIndex++;
				if (!slot->m_unk0x10) {
					break;
				}
			}
		}

		if (m_unk0x28c == c_menuWinCar) {
			slotIndex = 1;
			slot = &racersContext->m_playerSetupSlots[slotIndex];
		}

		DriverCosmetics cosmetics;
		if (slot->m_driverName[0]) {
			m_context->m_cosmeticTable.CopyCosmetics(slot->m_driverName, &cosmetics);
		}
		else {
			cosmetics = slot->m_cosmetics;
		}

		m_context->m_modelBuilder.SetExpressionMask(0xffff);
		m_unk0x79c = m_context->m_modelBuilder.BuildDriverModel(&cosmetics, NULL, 0);
		m_unk0x6a8.FUN_0040d550(
			m_unk0x79c,
			sourceDriverEntity->VTable0x58(0),
			sourceDriverEntity->GetModelPart(0),
			sourceDriverEntity->GetModelDistance(0)
		);

		LegoBool32 carCreated = FALSE;
		if (carBodyEntity) {
			if (!m_context->m_unk0x21f4.IsInitialized()) {
				GolHashTable::Entry* currentEntry;
				if (g_hashTable) {
					currentEntry = g_hashTable->GetCurrentEntry();
				}
				else {
					currentEntry = NULL;
				}

				FUN_0047ff50(m_context, TRUE);

				if (g_hashTable) {
					g_hashTable->SetCurrentEntry(currentEntry);
				}
			}

			carCreated = FUN_00476b00(slotIndex);
			FUN_004803a0();
			m_context->m_chassisModels.FUN_0041dae0();
			m_context->m_championDefinitions.ClearDefinitions();
		}

		if (carBodyEntity && (swapEntity || pLegEntity)) {
			MaterialTable0x0c* carBodyMaterials = carBodyEntity->GetPrimaryMaterialTable();
			if (!carBodyMaterials) {
				carBodyMaterials = carBodyEntity->GetModel(0)->GetMaterialTable();
			}

			if (swapEntity) {
				MaterialTable0x0c* swapMaterials = swapEntity->GetPrimaryMaterialTable();
				if (!swapMaterials) {
					swapMaterials = swapEntity->GetModel(0)->GetMaterialTable();
				}
				swapMaterials->SetPosition(0, carBodyMaterials->GetPosition(1));
			}

			if (pLegEntity) {
				MaterialTable0x0c* pLegMaterials = pLegEntity->GetPrimaryMaterialTable();
				if (!pLegMaterials) {
					pLegMaterials = pLegEntity->GetModel(0)->GetMaterialTable();
				}
				pLegMaterials->SetPosition(0, carBodyMaterials->GetPosition(1));
			}
		}

		CutsceneDefinition::Frame* frame = m_unk0x368.m_unk0x2b0;
		if (frame) {
			for (LegoU32 i = 0; i < frame->GetModelCount(); i++) {
				CutsceneDefinition::Frame::ModelEvent* model = frame->GetModel(i);
				GolWorldEntity* entity = model->GetEntity();
				if (entity == sourceDriverEntity) {
					model->SetEntity(&m_unk0x6a8);

					for (LegoU32 j = 0; j < model->GetAnimationCount(); j++) {
						CutsceneDefinition::Frame::ModelEvent::Animation* animation = model->GetAnimation(j);
						MabMaterialAnimationItem0x8* animationItems = animation->m_unk0x00->GetUnk0x04();
						MabMaterialAnimationItem0x18* animationItem = animation->m_unk0x04;
						LegoS32 firstFrame = animationItem->GetFirstFrame();
						LegoS32 endFrame = firstFrame + animationItem->GetFrameCount();

						for (LegoS32 frameIndex = firstFrame; frameIndex < endFrame; frameIndex++) {
							DuskwindBananaRelic0x24* material = animationItems[frameIndex].GetMaterial();
							GolName expressionName;
							::memcpy(expressionName, material->GetName(), sizeof(GolName));
							LegoS32 expressionIndex = 0;

							if (::strncmp(expressionName, "face", sizeof(GolName)) != 0) {
								if (::strncmp(expressionName, "angry", sizeof(GolName)) == 0) {
									expressionIndex = 1;
								}
								else if (::strncmp(expressionName, "blink", sizeof(GolName)) == 0) {
									expressionIndex = 2;
								}
								else if (::strncmp(expressionName, "happy", sizeof(GolName)) == 0) {
									expressionIndex = 3;
								}
								else if (::strncmp(expressionName, "sad", sizeof(GolName)) == 0) {
									expressionIndex = 4;
								}
								else if (::strncmp(expressionName, "suprz", sizeof(GolName)) == 0) {
									expressionIndex = 5;
								}
							}

							m_context->m_partCatalog
								.BuildFaceExpressionName(cosmetics.m_faceIndex, expressionIndex, expressionName);
							animationItems[frameIndex].SetMaterial(m_renderer->FindMaterialByName(expressionName));
						}
					}
				}
				else if (entity == carBodyEntity) {
					if (carCreated) {
						model->SetEntity(&m_unk0x658);
					}
				}
				else if (entity == swapEntity || entity == pLegEntity) {
					if (cosmetics.m_legIndex != 10) {
						model->SetEntity(NULL);
					}
				}
			}
		}
	}

	if (m_unk0x28c == c_menuWinCar) {
		GolNameTable* textVisuals = m_unk0x368.m_unk0x84.GetTextVisuals();
		const LegoChar* driverName = m_context->m_context->m_playerSetupSlots[1].m_driverName;
		GolName textName;

		textName[0] = 't';
		textName[1] = 'e';
		textName[2] = 'x';
		textName[3] = 't';
		textName[4] = 'C';
		textName[5] = 'R';
		textName[6] = '\0';

		CutsceneTextVisual* textVisual = static_cast<CutsceneTextVisual*>(textVisuals->GetName(textName));
		if (driverName[0] != textName[4] || driverName[1] != textName[5]) {
			textVisual->SetDisabled(TRUE);
		}

		textName[4] = 'K';
		textName[5] = 'K';
		textVisual = static_cast<CutsceneTextVisual*>(textVisuals->GetName(textName));
		if (driverName[0] != textName[4] || driverName[1] != textName[5]) {
			textVisual->SetDisabled(TRUE);
		}

		textName[4] = 'B';
		textName[5] = 'B';
		textVisual = static_cast<CutsceneTextVisual*>(textVisuals->GetName(textName));
		if (driverName[0] != textName[4] || driverName[1] != textName[5]) {
			textVisual->SetDisabled(TRUE);
		}

		textName[4] = 'J';
		textName[5] = 'T';
		textVisual = static_cast<CutsceneTextVisual*>(textVisuals->GetName(textName));
		if (driverName[0] != textName[4] || driverName[1] != textName[5]) {
			textVisual->SetDisabled(TRUE);
		}

		textName[4] = 'G';
		textName[5] = 'M';
		textVisual = static_cast<CutsceneTextVisual*>(textVisuals->GetName(textName));
		if (driverName[0] != textName[4] || driverName[1] != textName[5]) {
			textVisual->SetDisabled(TRUE);
		}

		textName[4] = 'B';
		textName[5] = 'V';
		textName[6] = 'B';
		textName[7] = '\0';
		textVisual = static_cast<CutsceneTextVisual*>(textVisuals->GetName(textName));
		if (driverName[0] != textName[4] || driverName[1] != textName[5] || driverName[2] != textName[6]) {
			textVisual->SetDisabled(TRUE);
		}
	}

	FUN_004767b0();
}

// FUNCTION: LEGORACERS 0x004767b0
LegoBool32 AwardCinematicScreen::FUN_004767b0()
{
	GameState* gameState = &m_context->m_saveSystem.GetGameState();
	LegoU16 menuId = m_unk0x28c;

	if (menuId != c_menuChampAward1 && menuId != c_menuChampAward2 && menuId != c_menuChampAward3) {
		return FALSE;
	}

	LegoRacers::Context* context = m_context->m_context;

	if (context->m_playerRecordStates[0].m_recordSource == 0) {
		return FALSE;
	}

	SaveRecordList* records = NULL;

	switch (context->m_playerRecordStates[0].m_recordSource) {
	case 1:
	case 3:
		records = &m_context->m_saveSystem.GetSessionSave();
		break;
	case 2:
		records = &m_context->m_saveSystem.GetMemoryCardSaves()[context->m_playerRecordStates[0].m_saveIndex];
		break;
	default:
		return FALSE;
	}

	if (records == NULL) {
		return FALSE;
	}

	CircuitDefinitionList::CircuitDefinition* circuitDefinition =
		static_cast<CircuitDefinitionList::CircuitDefinition*>(
			m_context->m_circuitList.GetName(context->m_circuitName)
		);
	m_unk0x7a4 = FUN_00476890(records, circuitDefinition);

	if (m_unk0x28c != c_menuChampAward1 && m_unk0x28c != c_menuChampAward2) {
		return FALSE;
	}

	m_unk0x7a8 = FUN_00476990(gameState, circuitDefinition);
	m_unk0x7ac = FUN_004768f0(gameState, circuitDefinition);
	return m_unk0x7ac;
}

// FUNCTION: LEGORACERS 0x00476890
LegoBool32 AwardCinematicScreen::FUN_00476890(
	SaveRecordList* p_records,
	CircuitDefinitionList::CircuitDefinition* p_circuitDefinition
)
{
	SaveRecordList::Record* record =
		p_records->FindRecordById(m_context->m_context->m_playerRecordStates[0].m_recordId);
	if (record == NULL) {
		return FALSE;
	}

	return record->SetTrophy(m_context->m_circuitList.GetEntryIndex(p_circuitDefinition), m_unk0x28c - 0x15);
}

// FUNCTION: LEGORACERS 0x004768f0
LegoBool32 AwardCinematicScreen::FUN_004768f0(
	GameState* p_gameState,
	CircuitDefinitionList::CircuitDefinition* p_circuitDefinition
)
{
	GolName menuName;
	::memcpy(menuName, p_circuitDefinition->GetMenuName(), sizeof(menuName));

	if (menuName[0] != '\0') {
		CircuitDefinitionList* circuitList = &m_context->m_circuitList;
		CircuitDefinitionList::CircuitDefinition* menuCircuitDefinition =
			static_cast<CircuitDefinitionList::CircuitDefinition*>(circuitList->GetName(menuName));
		LegoU8 mask = static_cast<LegoU8>(1 << m_context->m_circuitList.GetEntryIndex(menuCircuitDefinition));

		if (!(p_gameState->GetUnlockedCircuits() & mask)) {
			p_gameState->UnlockCircuits(mask);
			m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() | 4);
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00476990
LegoBool32 AwardCinematicScreen::FUN_00476990(
	GameState* p_gameState,
	CircuitDefinitionList::CircuitDefinition* p_circuitDefinition
)
{
	if (m_unk0x28c != c_menuChampAward1) {
		return FALSE;
	}

	m_unk0x7a0 = p_circuitDefinition->GetStringIndex();
	if (m_unk0x7a0 == -1) {
		return FALSE;
	}

	LegoU8 mask = static_cast<LegoU8>(1 << m_unk0x7a0);
	if (p_gameState->GetPartUnlockFlags() & mask) {
		m_unk0x7a0 = -1;
		return FALSE;
	}

	p_gameState->UnlockParts(mask);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00476a00
void AwardCinematicScreen::VTable0x84()
{
	m_context->m_menuStack.Pop();

	if (m_context->m_menuStack.GetSize()) {
		if (m_context->m_menuStack.Peek() == c_menuMainMenu) {
			m_context->m_menuStack.ResetSize();
			m_context->m_menuStack.Push(c_menuMainMenu);
		}
		else {
			m_context->m_menuStack.ResetSize();
		}
	}
	else {
		m_context->m_menuStack.ResetSize();
		if (m_unk0x7a0 != -1) {
			if (m_unk0x7a0 == 6) {
				m_context->m_menuStack.Push(c_menuWinRrCar);
			}
			else {
				m_context->m_menuStack.Push(c_menuWinCar);
			}
		}
		else {
			if (m_unk0x28c == c_menuWinRrCar) {
				m_context->m_menuStack.Push(c_menuCredits);
			}
			else {
				m_context->m_menuStack.Push(c_menuMainMenu);
			}
		}
	}

	if (m_unk0x7a4 || m_unk0x7a8 || m_unk0x7ac) {
		m_context->m_menuStack.Push(c_menuSaveAll);
		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() | 0x10);
	}
}

// FUNCTION: LEGORACERS 0x00476ad0
LegoBool32 AwardCinematicScreen::VTable0x78(undefined4 p_unk0x04)
{
	if (m_unk0x28c == c_menuCircuit7) {
		m_unk0x368.m_unk0x2cc = TRUE;
	}

	return MenuSceneScreen::VTable0x78(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00476b00
LegoBool32 AwardCinematicScreen::FUN_00476b00(undefined4)
{
	SaveRecordList::Record* record = NULL;
	LegoBool32 found = FALSE;
	GolName name;

	do {
		if (m_unk0x28c == c_menuWinCar) {
			LegoRacers::Context* racersContext = m_context->m_context;
			const LegoChar* driverName = racersContext->m_playerSetupSlots[1].m_driverName;
			LegoChar firstChar = driverName[0];

			if (firstChar) {
				DriverCosmeticTable::Entry* driverEntry =
					static_cast<DriverCosmeticTable::Entry*>(m_context->m_cosmeticTable.GetName(driverName));
				ChampionDefinitionList::ChampionDefinition* championDefinition =
					static_cast<ChampionDefinitionList::ChampionDefinition*>(
						m_context->m_championDefinitions.GetName(driverEntry->m_unk0x1a)
					);

				SaveGame* quickBuildSave = &m_context->m_saveSystem.GetQuickBuildSave();
				for (LegoU32 i = 0; i < quickBuildSave->GetRecordCount() && !found; i++) {
					record = quickBuildSave->GetRecord(i);

					record->GetChassisName(name);
					if (::strncmp(name, championDefinition->m_unk0x18, sizeof(GolName)) == 0) {
						record->GetName(name);
						if (::strncmp(name, "CHAMP", sizeof(name)) == 0) {
							found = TRUE;
						}
					}
				}

				if (!found) {
					break;
				}
			}
			else {
				record = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord();
			}
		}
		else {
			record = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord();
		}

		if (record == NULL) {
			break;
		}

		LegoU8 carData[sizeof(SaveRecordData) - 0x2b];
		record->CopyCarData(carData);

		m_context->m_unk0x21f4.FUN_0049c7f0(carData);
		if (m_context->m_unk0x21f4.GetPlacedPieceCount()) {
			m_context->m_unk0x21f4.FUN_0049b740(FALSE);
			m_context->m_unk0x21f4.FUN_0049b920(1, 0x7f);

			SceneEntityGroup::CreateParams createParams;
			createParams.m_unk0x0c = NULL;
			createParams.m_chassisModels = &m_context->m_chassisModels;
			createParams.m_unk0x04 = &m_context->m_unk0x21f4;
			createParams.m_unk0x08 = m_context->m_unk0x21f4.GetUnk0x0c();

			record->GetChassisName(name);
			::strncpy(createParams.m_chassisName, name, sizeof(GolName));

			if (!m_context->m_chassisModels.GetPrimaryModel(name)) {
				GolHashTable::Entry* currentEntry;

				if (g_hashTable) {
					currentEntry = g_hashTable->GetCurrentEntry();
					g_hashTable->SetCurrentEntryFromString("MENUDATA\\PIECEDB");
				}
				else {
					currentEntry = NULL;
				}

				GolAnimatedEntity* primary;
				GolAnimatedEntity* secondary;
				m_context->m_chassisModels.InstantiateModels(name, &primary, &secondary);

				if (g_hashTable) {
					g_hashTable->SetCurrentEntry(currentEntry);
				}
			}

			m_unk0x658.FUN_00479510(&createParams);

			GolAnimatedEntity* entity = m_unk0x658.GetPrimaryChassisEntity();
			entity->SetFlags(entity->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);

			return TRUE;
		}
	} while (FALSE);

	return FALSE;
}

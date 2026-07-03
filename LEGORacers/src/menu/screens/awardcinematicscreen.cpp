#include "menu/screens/awardcinematicscreen.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "core/gol.h"
#include "golhashtable.h"
#include "golmaterial.h"
#include "golmodelbase.h"
#include "golstring.h"
#include "mabmaterialanimation.h"
#include "mabmaterialframe.h"
#include "mabmaterialtrack.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "model/carbuildmodel.h"
#include "world/golworlddatabase.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(AwardCinematicScreen, 0x7b0)

// FUNCTION: LEGORACERS 0x00475c30
AwardCinematicScreen::AwardCinematicScreen()
	: m_driverModel(NULL), m_trophyAwarded(0), m_partsUnlocked(0), m_circuitUnlocked(0)
{
	m_unlockedPartIndex = -1;
}

// FUNCTION: LEGORACERS 0x00475cd0
AwardCinematicScreen::~AwardCinematicScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00475d30
LegoBool32 AwardCinematicScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_circuitUnlocked = 0;
	m_partsUnlocked = 0;
	m_trophyAwarded = 0;

	if (p_createParams->m_menuId == c_menuWinRrCar && p_context->m_carBuildModel.IsInitialized()) {
		p_context->m_carBuildModel.ReleaseBuffers();
	}

	if (!MenuSceneScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	undefined4 musicId = 1;

	switch (m_resourceMenuId) {
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

	StartMenuMusic(p_context, musicId, FALSE);

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

	DestroyChampionResources();
	DestroyPieceResources(m_context);
	m_carGroup.Destroy();
	m_driverEntity.ResetModelState();

	if (m_driverModel) {
		m_golExport->DestroyModel(m_driverModel);
		m_driverModel = NULL;
	}

	m_unlockedPartIndex = -1;

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
	if (m_resourceMenuId == c_menuWinRrCar) {
		MenuGameContext* context = m_context;
		if (context->m_carBuildModel.IsInitialized()) {
			m_context->m_carBuildModel.AcquireBuffers();
		}
	}

	return result;
}

// STUB: LEGORACERS 0x00475f40
void AwardCinematicScreen::CreateWidgets()
{
	struct ResourcePathLocals {
		LegoChar m_name[12];
		GolString m_string;
		LegoChar m_path[20];
	} locals;

	GolAnimatedEntity* sourceDriverEntity = NULL;
	GolModelEntity* carBodyEntity = NULL;
	GolAnimatedEntity* swapEntity = NULL;
	GolAnimatedEntity* pLegEntity = NULL;
	LegoBool32 carCreated = FALSE;
	DriverCosmetics cosmetics;

	if (m_resourceMenuId != c_menuWinVvCar) {
		if (!m_context->m_modelBuilder.HasMenuResources()) {
			LoadPartResources(m_context, FALSE);
		}

		if (!m_context->m_cosmeticTable.HasEntries()) {
			LoadCosmeticTable();
		}
	}

	if (m_resourceMenuId == c_menuWinCar) {
		if (!m_context->m_chassisModels.HasItems() || !m_context->m_championDefinitions.HasDefinitions()) {
			LoadChampionResources(1);
		}
	}

	m_menuNameStrings->CopyStringByIndex(&locals.m_string, m_resourceMenuId);
	locals.m_string.CopyToString(locals.m_name);
	::sprintf(locals.m_path, "MENUDATA\\%s", locals.m_name);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(locals.m_path);
	}

	CreateRegion(&m_sceneWidget, m_resourceMenuId);
	m_sceneWidget.m_skippable = FALSE;
	CutsceneDefinition::Frame* frame = m_sceneWidget.m_frame;

	if (m_resourceMenuId == c_menuCircuit7) {
		SaveRecordList::Record* record = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord();
		if (record) {
			m_context->m_context->m_playerSetupSlots[0].m_slotState = 0;
			record->GetCosmetics(&m_context->m_context->m_playerSetupSlots[0].m_cosmetics);
			m_context->m_context->m_playerSetupSlots[0].m_driverName[0] = '\0';
		}
	}

	for (LegoU32 i = 0; i < m_sceneWidget.m_definition.GetWorldDatabaseCount(); i++) {
		GolWorldDatabase* worldDatabase = m_sceneWidget.m_definition.GetWorldDatabase(i);
		if (!sourceDriverEntity) {
			sourceDriverEntity = worldDatabase->FindAnimatedEntity("guy1");
		}

		if (!carBodyEntity) {
			carBodyEntity = worldDatabase->FindModelEntity("carbody");
			if (!carBodyEntity) {
				carBodyEntity = worldDatabase->FindAnimatedEntity("carbody");
			}
		}

		if (!swapEntity) {
			swapEntity = worldDatabase->FindAnimatedEntity("swap");
		}

		if (!pLegEntity) {
			pLegEntity = worldDatabase->FindAnimatedEntity("pleg");
		}
	}

	if (m_resourceMenuId != c_menuWinVvCar) {
		LegoRacers::Context* racersContext = m_context->m_context;
		LegoU32 slotIndex = 0;
		undefined4 slotState = racersContext->m_playerSetupSlots[slotIndex].m_slotState;

		if (slotState) {
			while (slotState && slotIndex < racersContext->m_playerCount) {
				slotIndex++;
				slotState = racersContext->m_playerSetupSlots[slotIndex].m_slotState;
			}
		}

		if (m_resourceMenuId == c_menuWinCar) {
			slotIndex = 1;
		}

		if (racersContext->m_playerSetupSlots[slotIndex].m_driverName[0]) {
			m_context->m_cosmeticTable.CopyCosmetics(
				racersContext->m_playerSetupSlots[slotIndex].m_driverName,
				&cosmetics
			);
		}
		else {
			cosmetics = racersContext->m_playerSetupSlots[slotIndex].m_cosmetics;
		}

		m_context->m_modelBuilder.SetExpressionMask(0xffff);
		m_driverModel = m_context->m_modelBuilder.BuildDriverModel(&cosmetics, NULL, 0);
		m_driverEntity.SetModel(
			m_driverModel,
			sourceDriverEntity->GetSceneNode(0),
			sourceDriverEntity->GetModelPart(0),
			sourceDriverEntity->GetModelDistance(0)
		);

		if (carBodyEntity) {
			if (!m_context->m_carBuildModel.IsInitialized()) {
				GolHashTable::Entry* currentEntry;
				if (g_hashTable) {
					currentEntry = g_hashTable->GetCurrentEntry();
				}
				else {
					currentEntry = NULL;
				}

				LoadPieceResources(m_context, TRUE);

				if (g_hashTable) {
					g_hashTable->SetCurrentEntry(currentEntry);
				}
			}

			carCreated = CreateWinnerCar(slotIndex);
			ClearCosmeticTable();
			m_context->m_chassisModels.ReleaseInstances();
			m_context->m_championDefinitions.ClearDefinitions();
		}

		if (carBodyEntity && (swapEntity || pLegEntity)) {
			MaterialTable* carBodyMaterials = carBodyEntity->GetPrimaryMaterialTable();
			if (!carBodyMaterials) {
				carBodyMaterials = carBodyEntity->GetModel(0)->GetMaterialTable();
			}

			if (swapEntity) {
				MaterialTable* swapMaterials = swapEntity->GetPrimaryMaterialTable();
				if (!swapMaterials) {
					swapMaterials = swapEntity->GetModel(0)->GetMaterialTable();
				}
				swapMaterials->SetEntry(0, carBodyMaterials->GetEntry(1));
			}

			if (pLegEntity) {
				MaterialTable* pLegMaterials = pLegEntity->GetPrimaryMaterialTable();
				if (!pLegMaterials) {
					pLegMaterials = pLegEntity->GetModel(0)->GetMaterialTable();
				}
				pLegMaterials->SetEntry(0, carBodyMaterials->GetEntry(1));
			}
		}

		if (frame) {
			for (LegoU32 i = 0; i < frame->GetModelEventCount(); i++) {
				CutsceneDefinition::Frame::ModelEvent* model = frame->GetModel(i);
				GolWorldEntity* entity = model->GetEntity();
				if (entity == sourceDriverEntity) {
					model->SetEntity(&m_driverEntity);

					for (LegoU32 j = 0; j < model->GetAnimationCount(); j++) {
						CutsceneDefinition::Frame::ModelEvent::Animation* animation = model->GetAnimation(j);
						MabMaterialFrame* animationItems = animation->m_materialAnimation->GetFrames();
						MabMaterialTrack* animationItem = animation->m_item;
						LegoS32 firstFrame = animationItem->GetFirstFrame();
						LegoS32 endFrame = firstFrame + animationItem->GetFrameCount();

						for (LegoS32 frameIndex = firstFrame; frameIndex < endFrame; frameIndex++) {
							GolMaterial* material = animationItems[frameIndex].GetMaterial();
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
						model->SetEntity(&m_carGroup);
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

	if (m_resourceMenuId == c_menuWinCar) {
		GolNameTable* textVisuals = m_sceneWidget.m_player.GetTextVisuals();
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

	GrantAwards();
}

// FUNCTION: LEGORACERS 0x004767b0
LegoBool32 AwardCinematicScreen::GrantAwards()
{
	GameState* gameState = &m_context->m_saveSystem.GetGameState();
	LegoU16 menuId = m_resourceMenuId;

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
	m_trophyAwarded = GrantTrophy(records, circuitDefinition);

	if (m_resourceMenuId != c_menuChampAward1 && m_resourceMenuId != c_menuChampAward2) {
		return FALSE;
	}

	m_partsUnlocked = UnlockPartSet(gameState, circuitDefinition);
	m_circuitUnlocked = UnlockNextCircuit(gameState, circuitDefinition);
	return m_circuitUnlocked;
}

// FUNCTION: LEGORACERS 0x00476890
LegoBool32 AwardCinematicScreen::GrantTrophy(
	SaveRecordList* p_records,
	CircuitDefinitionList::CircuitDefinition* p_circuitDefinition
)
{
	SaveRecordList::Record* record =
		p_records->FindRecordById(m_context->m_context->m_playerRecordStates[0].m_recordId);
	if (record == NULL) {
		return FALSE;
	}

	return record->SetTrophy(m_context->m_circuitList.GetEntryIndex(p_circuitDefinition), m_resourceMenuId - 0x15);
}

// FUNCTION: LEGORACERS 0x004768f0
LegoBool32 AwardCinematicScreen::UnlockNextCircuit(
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
			m_context->m_modelBuilder.SetMenuFlowFlags(
				m_context->m_modelBuilder.GetMenuFlowFlags() | DriverModelBuilder::c_menuFlowUnlockNotice
			);
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00476990
LegoBool32 AwardCinematicScreen::UnlockPartSet(
	GameState* p_gameState,
	CircuitDefinitionList::CircuitDefinition* p_circuitDefinition
)
{
	if (m_resourceMenuId != c_menuChampAward1) {
		return FALSE;
	}

	m_unlockedPartIndex = p_circuitDefinition->GetStringIndex();
	if (m_unlockedPartIndex == -1) {
		return FALSE;
	}

	LegoU8 mask = static_cast<LegoU8>(1 << m_unlockedPartIndex);
	if (p_gameState->GetPartUnlockFlags() & mask) {
		m_unlockedPartIndex = -1;
		return FALSE;
	}

	p_gameState->UnlockParts(mask);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00476a00
void AwardCinematicScreen::Navigate()
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
		if (m_unlockedPartIndex != -1) {
			if (m_unlockedPartIndex == 6) {
				m_context->m_menuStack.Push(c_menuWinRrCar);
			}
			else {
				m_context->m_menuStack.Push(c_menuWinCar);
			}
		}
		else {
			if (m_resourceMenuId == c_menuWinRrCar) {
				m_context->m_menuStack.Push(c_menuCredits);
			}
			else {
				m_context->m_menuStack.Push(c_menuMainMenu);
			}
		}
	}

	if (m_trophyAwarded || m_partsUnlocked || m_circuitUnlocked) {
		m_context->m_menuStack.Push(c_menuSaveAll);
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() | DriverModelBuilder::c_menuFlowSaveReminder
		);
	}
}

// FUNCTION: LEGORACERS 0x00476ad0
LegoBool32 AwardCinematicScreen::Update(undefined4 p_elapsedMs)
{
	if (m_resourceMenuId == c_menuCircuit7) {
		m_sceneWidget.m_skippable = TRUE;
	}

	return MenuSceneScreen::Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00476b00
LegoBool32 AwardCinematicScreen::CreateWinnerCar(undefined4)
{
	SaveRecordList::Record* record = NULL;
	LegoBool32 found = FALSE;
	GolName name;

	do {
		if (m_resourceMenuId == c_menuWinCar) {
			LegoRacers::Context* racersContext = m_context->m_context;
			const LegoChar* driverName = racersContext->m_playerSetupSlots[1].m_driverName;
			LegoChar firstChar = driverName[0];

			if (firstChar) {
				DriverCosmeticTable::Entry* driverEntry =
					static_cast<DriverCosmeticTable::Entry*>(m_context->m_cosmeticTable.GetName(driverName));
				ChampionDefinitionList::ChampionDefinition* championDefinition =
					static_cast<ChampionDefinitionList::ChampionDefinition*>(
						m_context->m_championDefinitions.GetName(driverEntry->m_championName)
					);

				SaveGame* quickBuildSave = &m_context->m_saveSystem.GetQuickBuildSave();
				for (LegoU32 i = 0; i < quickBuildSave->GetRecordCount() && !found; i++) {
					record = quickBuildSave->GetRecord(i);

					record->GetChassisName(name);
					if (::strncmp(name, championDefinition->m_chassisName, sizeof(GolName)) == 0) {
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

		m_context->m_carBuildModel.Deserialize(carData);
		if (m_context->m_carBuildModel.GetPlacedPieceCount()) {
			m_context->m_carBuildModel.UpdateOffset(FALSE);
			m_context->m_carBuildModel.RebuildModel(1, 0x7f);

			SceneEntityGroup::CreateParams createParams;
			createParams.m_driverEntity = NULL;
			createParams.m_chassisModels = &m_context->m_chassisModels;
			createParams.m_buildModel = &m_context->m_carBuildModel;
			createParams.m_carEntity = m_context->m_carBuildModel.GetModelEntity();

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

			m_carGroup.Create(&createParams);

			GolAnimatedEntity* entity = m_carGroup.GetPrimaryChassisEntity();
			entity->SetFlags(entity->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);

			return TRUE;
		}
	} while (FALSE);

	return FALSE;
}

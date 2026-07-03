#include "menu/screens/racermodelscreenbase.h"

#include "core/gol.h"
#include "golanimatedentity.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "golstream.h"
#include "golstring.h"
#include "golstringtable.h"
#include "menu/menugamecontext.h"
#include "racer/drivercosmetics.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(RacerModelScreenBase, 0x270c)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// GLOBAL: LEGORACERS 0x004c21bc
LegoU16 g_racerIdleAnimTextIds[8] = {116, 117, 119, 120, 121, 122, 123, 0};

// GLOBAL: LEGORACERS 0x004c21cc
LegoU16 g_racerSelectAnimTextIds[3] = {124, 126, 127};

// GLOBAL: LEGORACERS 0x004b3c74
LegoFloat g_racerPickMaxFloat = FLT_MAX;

// FUNCTION: LEGORACERS 0x00485890
RacerModelScreenBase::RacerModelScreenBase()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00485a00
RacerModelScreenBase::~RacerModelScreenBase()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00485af0
void RacerModelScreenBase::Reset()
{
	m_modelSlotCount = 0;
	m_slotCount = 0;

	::memset(m_recordCounts, 0, sizeof(m_recordCounts));
	::memset(m_slotDirty, 0, sizeof(m_slotDirty));
	::memset(m_slotSettled, 0, sizeof(m_slotSettled));
	::memset(m_driverModels, 0, sizeof(m_driverModels));
	::memset(m_bodySceneNodes, 0, sizeof(m_bodySceneNodes));
	::memset(m_carModels, 0, sizeof(m_carModels));
	::memset(m_slotModelToggle, 0, sizeof(m_slotModelToggle));

	m_carUpAxis.m_z = 1.0f;
	m_carDirAxis.m_x = 1.0f;
	m_carUpAxis.m_y = 0.0f;
	m_carUpAxis.m_x = 0.0f;
	m_carDirAxis.m_z = 0.0f;
	m_carDirAxis.m_y = 0.0f;

	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00485bb0
void RacerModelScreenBase::CreateCarModels()
{
	CreateDriverModels();

	m_carModels[0] = m_context->m_carBuildModel.GetModel();

	for (LegoS32 i = 0; i < m_slotCount; i++) {
		if (m_carModels[i] == NULL) {
			m_carModels[i] = m_golExport->CreateModel();
			if (m_carModels[i] == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			m_context->m_carBuildModel.InitializeModel(m_carModels[i]);
		}

		m_carModelEntities[i].SetPrimaryModel(m_carModels[i], g_racerPickMaxFloat);
		m_carModelEntities[i].SetPrimaryMaterialTable(m_context->m_colorTable.GetMaterialTable());
	}

	m_modelParts.Load("rsanim", m_context->m_context->m_useBinaryFiles);
}

// STUB: LEGORACERS 0x00485c80
void RacerModelScreenBase::OpenRecordCursors(MenuGameContext* p_context, LegoU32 p_mask)
{
	SaveSystem* saveSystem = &p_context->m_saveSystem;

	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		SaveRecordCursor* modelState = &m_recordCursors[i];

		modelState->SetSaveSystem(saveSystem);
		modelState->Begin(p_mask);
		m_recordCounts[i] = modelState->CountRecords(p_mask);

		if (m_recordCounts[i]) {
			SaveRecordList::Record* firstRecord = modelState->GetSelectedRecord();
			InputBindingState::PlayerState* player =
				&saveSystem->GetGameState().GetState().m_inputBindings.m_players[i];
			LegoU32 selectedRecordId = player->m_selectedRecordId;
			LegoU32 selectedRecordSource = player->m_selectedRecordSource;
			LegoU32 selectedSaveIndex = player->m_selectedSaveIndex;

			while (TRUE) {
				SaveRecordList::Record* record = modelState->SelectNext();

				if (record->m_recordSource == selectedRecordSource && record->m_saveIndex == selectedSaveIndex &&
					record->m_recordId == selectedRecordId) {
					if (firstRecord != record) {
						break;
					}
				}
				else if (firstRecord != record) {
					continue;
				}

				record = modelState->SelectNext();
				while (record->m_recordSource == 3 && firstRecord != record) {
					record = modelState->SelectNext();
				}

				break;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00485da0
void RacerModelScreenBase::CreateDriverModels()
{
	undefined4 modelParams[5];

	m_context->m_modelBuilder.GetMaxMergedCounts(modelParams);

	for (LegoS32 i = 0; i < m_slotCount; i++) {
		m_driverModels[i] = m_golExport->CreateModel();
		if (m_driverModels[i] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_bodySceneNodes[i] = m_golExport->CreateSceneNode();
		if (m_bodySceneNodes[i] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_driverModels[i]->Allocate(m_renderer, 2, modelParams[0], modelParams[1], modelParams[2], modelParams[3]);
	}
}

// FUNCTION: LEGORACERS 0x00485e50
void RacerModelScreenBase::CreateModelSlots()
{
	LegoS32 i;
	GolVec3 slotPosition0;
	GolVec3 slotPosition1;
	RacerModelSlot::CreateParams createParams;

	slotPosition1.m_x = -0.938000023f;
	slotPosition1.m_y = -0.898000002f;
	LegoS32 count = m_modelSlotCount;
	slotPosition1.m_z = 1.486999989f;
	slotPosition0.m_x = -11.520000457f;
	slotPosition0.m_y = -6.767000198f;
	slotPosition0.m_z = 0.0f;
	i = 0;

	if (count > 0) {
		do {
			::memset(&createParams, 0, sizeof(createParams));

			createParams.m_golExport = m_golExport;
			createParams.m_renderer = m_renderer;
			createParams.m_sceneView = &m_sceneViews[i];
			createParams.m_position = slotPosition0;
			m_carSlots[i].Create(&createParams);

			createParams.m_position = slotPosition1;
			createParams.m_animate = TRUE;
			m_driverSlots[i].Create(&createParams);

			m_sceneViews[i].AddElement(&m_carSlots[i]);
			m_sceneViews[i].AddElement(&m_driverSlots[i]);

			i++;
		} while (i < m_modelSlotCount);
	}
}

// FUNCTION: LEGORACERS 0x00485f70
void RacerModelScreenBase::CreateWidgets()
{
	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\RS_SET");
	}

	LegoS32 i;

	for (i = 0; i < m_modelSlotCount; i++) {
		CreateFramedSceneView(&m_sceneViews[i], 0, i + 0x6e);
	}

	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	for (i = 0; i < m_modelSlotCount; i++) {
		CreateTextLabel(&m_sourceLabels[i], i + 0x72, 0x37, 0x37);
	}

	CreateModelSlots();
}

// FUNCTION: LEGORACERS 0x00486020
void RacerModelScreenBase::SetupLighting()
{
	ColorRGBA materialColor;
	ColorRGBA lightColor;

	materialColor.m_blu = 0x78;
	materialColor.m_grn = 0x78;
	materialColor.m_red = 0x78;
	lightColor.m_blu = 0xff;
	lightColor.m_grn = 0xff;
	lightColor.m_red = 0xff;

	SetLighting(&materialColor, &lightColor);
}

// FUNCTION: LEGORACERS 0x00486060
LegoBool32 RacerModelScreenBase::Initialize(
	MenuGameContext* p_context,
	MenuScreenCreateParams* p_createParams,
	undefined4* p_params
)
{
	m_modelSlotCount = p_params[0];
	m_modelsPerSlot = p_params[1];
	m_slotCount = m_modelsPerSlot * m_modelSlotCount;

	if (!p_context->m_carBuildModel.IsInitialized()) {
		LoadPieceResources(p_context, TRUE);
	}

	if (!p_context->m_modelBuilder.HasMenuResources()) {
		LoadPartResources(p_context, FALSE);
	}

	OpenRecordCursors(p_context, p_params[2]);

	if (!MenuGameScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	CreateCarModels();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004860f0
LegoBool32 RacerModelScreenBase::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	for (LegoS32 i = 0; i < m_slotCount; i++) {
		m_driverEntities[i].ResetModelState();
		m_carModelEntities[i].ResetModelState();
		m_golExport->DestroyModel(m_driverModels[i]);
		m_golExport->DestroySceneNode(m_bodySceneNodes[i]);

		if (i != 0) {
			m_golExport->DestroyModel(m_carModels[i]);
		}
	}

	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x004861b0
void RacerModelScreenBase::CommitRecordSelections()
{
	GameState& state = m_context->m_saveSystem.GetGameState();

	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		SaveRecordList::Record* record = m_recordCursors[i].GetSelectedRecord();

		if (record != NULL) {
			LegoU32 recordSource = record->m_recordSource;
			state.GetState().m_inputBindings.m_players[i].m_selectedRecordSource = static_cast<LegoU8>(recordSource);
			state.SetDirty(1);

			LegoU32 saveIndex = record->m_saveIndex;
			state.GetState().m_inputBindings.m_players[i].m_selectedSaveIndex = static_cast<LegoU8>(saveIndex);
			state.SetDirty(1);

			LegoU32 recordId = record->m_recordId;
			state.GetState().m_inputBindings.m_players[i].m_selectedRecordId = static_cast<LegoU8>(recordId);
			state.SetDirty(1);
		}
	}

	if (m_context->m_menuStack.Peek() != 0x30) {
		m_context->m_menuStack.Push(0x30);
	}
}

// FUNCTION: LEGORACERS 0x00486250
void RacerModelScreenBase::RefreshSlotModel(LegoS32 p_index)
{
	SaveRecordList::Record* record = m_recordCursors[p_index].GetSelectedRecord();
	LegoS32 modelIndex = m_slotModelToggle[p_index] + (m_modelsPerSlot * p_index);

	DriverCosmetics cosmetics;
	record->GetCosmetics(&cosmetics);

	if (m_slotCount == 1) {
		m_context->m_modelBuilder.RefreshMenuResources();
	}

	m_context->m_modelBuilder.SetExpressionMask(0xffff);
	GolModelBase* model = m_context->m_modelBuilder.BuildDriverModel(&cosmetics, m_driverModels[modelIndex], 0);
	m_context->m_modelBuilder.ApplyFaceExpression(model, &cosmetics);

	m_bodySceneNodes[modelIndex]->CopyFrom(m_context->m_modelBuilder.GetBodySceneNode(&cosmetics));
	m_driverEntities[modelIndex]
		.SetModel(m_driverModels[modelIndex], m_bodySceneNodes[modelIndex], &m_modelParts, g_racerPickMaxFloat);

	record->CopyCarData(m_carData);
	m_context->m_carBuildModel.Deserialize(m_carData);
	m_context->m_carBuildModel.UpdateOffset(0);
	m_context->m_carBuildModel.BuildIntoModel(m_carModels[modelIndex], 1, 0x7f);

	AwardCinematicScreen::SceneEntityGroup::CreateParams createParams;
	createParams.m_driverEntity = NULL;
	createParams.m_chassisModels = &m_context->m_chassisModels;
	createParams.m_buildModel = &m_context->m_carBuildModel;
	createParams.m_carEntity = &m_carModelEntities[modelIndex];
	record->GetChassisName(createParams.m_chassisName);

	m_carGroups[modelIndex].Create(&createParams);
}

// FUNCTION: LEGORACERS 0x00486400
void RacerModelScreenBase::SwapSlotModel(LegoS32 p_index)
{
	m_slotModelToggle[p_index] = (m_slotModelToggle[p_index] + 1) % m_modelsPerSlot;
	DetachSlotWidgets(p_index);
	RefreshSlotModel(p_index);
	m_slotDirty[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x00486440
void RacerModelScreenBase::UpdateSourceLabel(LegoS32 p_index)
{
	SaveRecordList::Record* record = m_recordCursors[p_index].GetSelectedRecord();
	LegoS32 textId = 0x2e;

	switch (record->m_recordSource) {
	case 1:
		textId = 0x36;
		break;
	case 2:
		break;
	default:
		textId = 0x37;
		break;
	}

	if (m_sourceLabels[p_index].GetFlags() & 1) {
		m_sourceLabels[p_index].SetStringByIndex(static_cast<undefined2>(textId), 0);
	}
}

// FUNCTION: LEGORACERS 0x004864a0
void RacerModelScreenBase::SelectNextRecord(LegoS32 p_index)
{
	m_recordCursors[p_index].SelectNext();
	m_slotModelToggle[p_index] = (m_slotModelToggle[p_index] + 1) % m_modelsPerSlot;
	DetachSlotWidgets(p_index);
	RefreshSlotModel(p_index);
	m_slotDirty[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x004864f0
void RacerModelScreenBase::SelectPreviousRecord(LegoS32 p_index)
{
	m_recordCursors[p_index].SelectPrevious();
	m_slotModelToggle[p_index] = (m_slotModelToggle[p_index] + 1) % m_modelsPerSlot;
	DetachSlotWidgets(p_index);
	RefreshSlotModel(p_index);
	m_slotDirty[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x00486540
void RacerModelScreenBase::AlignDriverSlots()
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		GolWorldEntity* entity = m_driverSlots[i].GetEntity();

		GolVec3 direction;
		direction.m_x = 0.963630974f;
		direction.m_y = -0.267237991f;
		direction.m_z = 0.0f;

		GolVec3 up;
		up.m_y = 0.0f;
		up.m_x = 0.0f;
		up.m_z = 1.0f;

		if (entity != NULL) {
			entity->SetDirectionUp(direction, up);
		}
	}
}

// FUNCTION: LEGORACERS 0x004865c0
void RacerModelScreenBase::AlignCarSlots()
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		GolWorldEntity* target = m_carSlots[i].GetEntity();
		if (target != NULL) {
			GolWorldDatabase* database = m_sceneViews[i].GetBlendedWorld();
			GolAnimatedEntity* source;
			if (database->GetAnimatedEntityEntries() == NULL) {
				source = NULL;
			}
			else {
				source = database->GetAnimatedEntityByName("crsdow");
			}

			source->ApplyPartAnimation(0);
			GolSceneNode* node = source->GetSceneNode(0);

			GolVec3 localVector;
			GolVec3 direction;
			node->TransformVectorToWorld(0, &m_carDirAxis, &localVector);
			source->RotateToWorld(localVector, &direction);

			GolVec3 up;
			node->TransformVectorToWorld(0, &m_carUpAxis, &localVector);
			source->RotateToWorld(localVector, &up);

			target->SetDirectionUp(direction, up);
		}
	}
}

// FUNCTION: LEGORACERS 0x004866e0
void RacerModelScreenBase::DetachSlotWidgets(LegoS32 p_index)
{
	m_carSlots[p_index].SetEntity(NULL);
	m_driverSlots[p_index].SetEntity(NULL);
	m_slotDirty[p_index] = FALSE;
	m_slotSettled[p_index] = FALSE;
}

// FUNCTION: LEGORACERS 0x00486730
LegoS32 RacerModelScreenBase::PickRandomAnimation()
{
	GolString string;
	LegoChar modelName[8];

	LegoS32 divisor = 7;
	g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
	LegoU16 random = g_randomTable[g_randomTableIndex];
	LegoU16 textIdIndex = static_cast<LegoU16>(static_cast<LegoS32>(random) % divisor);
	m_menuNameStrings->CopyStringByIndex(&string, g_racerIdleAnimTextIds[textIdIndex]);
	string.CopyToBuf8(modelName);
	return m_modelParts.GetPartIndex(modelName);
}

// FUNCTION: LEGORACERS 0x00486810
void RacerModelScreenBase::PlayRandomAnimation(LegoS32 p_index)
{
	LegoS32 modelIndex = m_slotModelToggle[p_index] + (m_modelsPerSlot * p_index);
	GolAnimatedEntity* entity = &m_driverEntities[modelIndex];
	LegoS32 partIndex;

	do {
		partIndex = PickRandomAnimation();
	} while (partIndex == entity->GetActiveState());

	entity->PlayPart(partIndex);
	entity->SetFlags((entity->GetFlags() & ~0x40000) | 0x10000);
}

// FUNCTION: LEGORACERS 0x00486890
void RacerModelScreenBase::PlayRandomNamedAnimation(LegoS32 p_index)
{
	GolString string;
	LegoChar modelName[8];

	LegoS32 modelIndex = m_slotModelToggle[p_index] + (m_modelsPerSlot * p_index);
	g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
	LegoU16 random = g_randomTable[g_randomTableIndex];
	LegoS32 textIdIndex = static_cast<LegoS32>(random) % 3;
	m_menuNameStrings->CopyStringByIndex(&string, g_racerSelectAnimTextIds[textIdIndex]);
	string.CopyToBuf8(modelName);

	LegoS32 partIndex = m_modelParts.GetPartIndex(modelName);
	GolAnimatedEntity* entity = &m_driverEntities[modelIndex];
	entity->TransitionToPart(partIndex, 0xc8, 0.0f, FALSE, FALSE, FALSE);

	LegoU32 flags = entity->GetFlags();
	flags &= ~0x40000;
	flags |= 0x10000;
	entity->SetFlags(flags);
}

// FUNCTION: LEGORACERS 0x004869b0
LegoBool32 RacerModelScreenBase::CanNavigate()
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		if (!(m_driverEntities[i].GetFlags() & 0x10000)) {
			break;
		}

		if (!m_driverEntities[i].IsPartAnimationDone()) {
			return FALSE;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00486a00
LegoBool32 RacerModelScreenBase::Update(undefined4 p_elapsed)
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		LegoS32 modelIndex = m_slotModelToggle[i] + (m_modelsPerSlot * i);

		switch (m_slotDirty[i]) {
		default: {
			if (m_driverEntities[modelIndex].GetFlags() & 1) {
				GolAnimatedEntity* entity = &m_driverEntities[modelIndex];
				if (entity->IsPartAnimationDone() &&
					m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord(i) == NULL && !m_navPending) {
					PlayRandomAnimation(i);
				}
			}
			break;
		}
		case TRUE:
			m_carSlots[i].SetEntity(&m_carGroups[modelIndex]);
			m_driverSlots[i].SetEntity(&m_driverEntities[modelIndex]);
			AlignDriverSlots();
			UpdateSourceLabel(i);
			m_slotDirty[i] = FALSE;

			if (!m_navPending) {
				PlayRandomAnimation(i);
			}
			break;
		}
	}

	AlignCarSlots();
	return MenuGameScreen::Update(p_elapsed);
}

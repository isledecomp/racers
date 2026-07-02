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
LegoU16 g_unk0x004c21bc[8] = {116, 117, 119, 120, 121, 122, 123, 0};

// GLOBAL: LEGORACERS 0x004c21cc
LegoU16 g_unk0x004c21cc[3] = {124, 126, 127};

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

	::memset(m_unk0x2704, 0, sizeof(m_unk0x2704));
	::memset(m_slotDirty, 0, sizeof(m_slotDirty));
	::memset(m_unk0x76c, 0, sizeof(m_unk0x76c));
	::memset(m_driverModels, 0, sizeof(m_driverModels));
	::memset(m_bodySceneNodes, 0, sizeof(m_bodySceneNodes));
	::memset(m_carModels, 0, sizeof(m_carModels));
	::memset(m_slotModelToggle, 0, sizeof(m_slotModelToggle));

	m_unk0x758.m_z = 1.0f;
	m_unk0x74c.m_x = 1.0f;
	m_unk0x758.m_y = 0.0f;
	m_unk0x758.m_x = 0.0f;
	m_unk0x74c.m_z = 0.0f;
	m_unk0x74c.m_y = 0.0f;

	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00485bb0
void RacerModelScreenBase::CreateCarModels()
{
	CreateDriverModels();

	m_carModels[0] = m_context->m_carBuildModel.GetUnk0x84();

	for (LegoS32 i = 0; i < m_slotCount; i++) {
		if (m_carModels[i] == NULL) {
			m_carModels[i] = m_golExport->VTable0x14();
			if (m_carModels[i] == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			m_context->m_carBuildModel.FUN_00499eb0(m_carModels[i]);
		}

		m_carModelEntities[i].VTable0x50(m_carModels[i], g_racerPickMaxFloat);
		m_carModelEntities[i].SetPrimaryMaterialTable(m_context->m_colorTable.GetMaterialTable());
	}

	m_modelParts.VTable0x14("rsanim", m_context->m_context->m_useBinaryFiles);
}

// STUB: LEGORACERS 0x00485c80
void RacerModelScreenBase::FUN_00485c80(MenuGameContext* p_context, LegoU32 p_mask)
{
	SaveSystem* saveSystem = &p_context->m_saveSystem;

	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		SaveRecordCursor* modelState = &m_recordCyclers[i];

		modelState->SetSaveSystem(saveSystem);
		modelState->Begin(p_mask);
		m_unk0x2704[i] = modelState->CountRecords(p_mask);

		if (m_unk0x2704[i]) {
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
		m_driverModels[i] = m_golExport->VTable0x14();
		if (m_driverModels[i] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_bodySceneNodes[i] = m_golExport->VTable0x18();
		if (m_bodySceneNodes[i] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_driverModels[i]->VTable0x18(m_renderer, 2, modelParams[0], modelParams[1], modelParams[2], modelParams[3]);
	}
}

// FUNCTION: LEGORACERS 0x00485e50
void RacerModelScreenBase::VTable0x98()
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
			createParams.m_sceneView = &m_unk0x98c[i];
			createParams.m_position = slotPosition0;
			m_unk0x1ddc[i].Create(&createParams);

			createParams.m_position = slotPosition1;
			createParams.m_animate = TRUE;
			m_modelSlots[i].Create(&createParams);

			m_unk0x98c[i].AddElement(&m_unk0x1ddc[i]);
			m_unk0x98c[i].AddElement(&m_modelSlots[i]);

			i++;
		} while (i < m_modelSlotCount);
	}
}

// FUNCTION: LEGORACERS 0x00485f70
void RacerModelScreenBase::VTable0x4c()
{
	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\RS_SET");
	}

	LegoS32 i;

	for (i = 0; i < m_modelSlotCount; i++) {
		CreateFramedSceneView(&m_unk0x98c[i], 0, i + 0x6e);
	}

	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	for (i = 0; i < m_modelSlotCount; i++) {
		CreateTextLabel(&m_sourceLabels[i], i + 0x72, 0x37, 0x37);
	}

	VTable0x98();
}

// FUNCTION: LEGORACERS 0x00486020
void RacerModelScreenBase::VTable0x80()
{
	ColorRGBA materialColor;
	ColorRGBA lightColor;

	materialColor.m_blu = 0x78;
	materialColor.m_grn = 0x78;
	materialColor.m_red = 0x78;
	lightColor.m_blu = 0xff;
	lightColor.m_grn = 0xff;
	lightColor.m_red = 0xff;

	FUN_0047fec0(&materialColor, &lightColor);
}

// FUNCTION: LEGORACERS 0x00486060
LegoBool32 RacerModelScreenBase::VTable0xa0(
	MenuGameContext* p_context,
	MenuScreenCreateParams* p_createParams,
	undefined4* p_params
)
{
	m_modelSlotCount = p_params[0];
	m_modelsPerSlot = p_params[1];
	m_slotCount = m_modelsPerSlot * m_modelSlotCount;

	if (!p_context->m_carBuildModel.IsInitialized()) {
		FUN_0047ff50(p_context, TRUE);
	}

	if (!p_context->m_modelBuilder.HasMenuResources()) {
		FUN_00480210(p_context, FALSE);
	}

	FUN_00485c80(p_context, p_params[2]);

	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
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
		m_driverEntities[i].VTable0x54();
		m_carModelEntities[i].VTable0x54();
		m_golExport->VTable0x48(m_driverModels[i]);
		m_golExport->VTable0x4c(m_bodySceneNodes[i]);

		if (i != 0) {
			m_golExport->VTable0x48(m_carModels[i]);
		}
	}

	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x004861b0
void RacerModelScreenBase::CommitRecordSelections()
{
	GameState& state = m_context->m_saveSystem.GetGameState();

	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		SaveRecordList::Record* record = m_recordCyclers[i].GetSelectedRecord();

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
	SaveRecordList::Record* record = m_recordCyclers[p_index].GetSelectedRecord();
	LegoS32 modelIndex = m_slotModelToggle[p_index] + (m_modelsPerSlot * p_index);

	DriverCosmetics cosmetics;
	record->GetCosmetics(&cosmetics);

	if (m_slotCount == 1) {
		m_context->m_modelBuilder.RefreshMenuResources();
	}

	m_context->m_modelBuilder.SetExpressionMask(0xffff);
	GolModelBase* model = m_context->m_modelBuilder.BuildDriverModel(&cosmetics, m_driverModels[modelIndex], 0);
	m_context->m_modelBuilder.ApplyFaceExpression(model, &cosmetics);

	m_bodySceneNodes[modelIndex]->VTable0x10(m_context->m_modelBuilder.GetBodySceneNode(&cosmetics));
	m_driverEntities[modelIndex]
		.FUN_0040d550(m_driverModels[modelIndex], m_bodySceneNodes[modelIndex], &m_modelParts, g_racerPickMaxFloat);

	record->CopyCarData(m_carData);
	m_context->m_carBuildModel.FUN_0049c7f0(m_carData);
	m_context->m_carBuildModel.FUN_0049b740(0);
	m_context->m_carBuildModel.FUN_0049bc60(m_carModels[modelIndex], 1, 0x7f);

	AwardCinematicScreen::SceneEntityGroup::CreateParams createParams;
	createParams.m_unk0x0c = NULL;
	createParams.m_chassisModels = &m_context->m_chassisModels;
	createParams.m_unk0x04 = &m_context->m_carBuildModel;
	createParams.m_unk0x08 = &m_carModelEntities[modelIndex];
	record->GetChassisName(createParams.m_chassisName);

	m_carGroups[modelIndex].FUN_00479510(&createParams);
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
	SaveRecordList::Record* record = m_recordCyclers[p_index].GetSelectedRecord();
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
	m_recordCyclers[p_index].SelectNext();
	m_slotModelToggle[p_index] = (m_slotModelToggle[p_index] + 1) % m_modelsPerSlot;
	DetachSlotWidgets(p_index);
	RefreshSlotModel(p_index);
	m_slotDirty[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x004864f0
void RacerModelScreenBase::SelectPreviousRecord(LegoS32 p_index)
{
	m_recordCyclers[p_index].SelectPrevious();
	m_slotModelToggle[p_index] = (m_slotModelToggle[p_index] + 1) % m_modelsPerSlot;
	DetachSlotWidgets(p_index);
	RefreshSlotModel(p_index);
	m_slotDirty[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x00486540
void RacerModelScreenBase::FUN_00486540()
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		GolWorldEntity* entity = m_modelSlots[i].GetEntity();

		GolVec3 direction;
		direction.m_x = 0.963630974f;
		direction.m_y = -0.267237991f;
		direction.m_z = 0.0f;

		GolVec3 up;
		up.m_y = 0.0f;
		up.m_x = 0.0f;
		up.m_z = 1.0f;

		if (entity != NULL) {
			entity->VTable0x40(direction, up);
		}
	}
}

// FUNCTION: LEGORACERS 0x004865c0
void RacerModelScreenBase::FUN_004865c0()
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		GolWorldEntity* target = m_unk0x1ddc[i].GetEntity();
		if (target != NULL) {
			GolWorldDatabase* database = m_unk0x98c[i].GetBlendedWorld();
			GolAnimatedEntity* source;
			if (database->GetUnk0xc0NameEntries() == NULL) {
				source = NULL;
			}
			else {
				source = database->GetUnk0xc0Name("crsdow");
			}

			source->VTable0x5c(0);
			GolSceneNode* node = source->VTable0x58(0);

			GolVec3 localVector;
			GolVec3 direction;
			node->FUN_004132a0(0, &m_unk0x74c, &localVector);
			source->VTable0x34(localVector, &direction);

			GolVec3 up;
			node->FUN_004132a0(0, &m_unk0x758, &localVector);
			source->VTable0x34(localVector, &up);

			target->VTable0x40(direction, up);
		}
	}
}

// FUNCTION: LEGORACERS 0x004866e0
void RacerModelScreenBase::DetachSlotWidgets(LegoS32 p_index)
{
	m_unk0x1ddc[p_index].SetEntity(NULL);
	m_modelSlots[p_index].SetEntity(NULL);
	m_slotDirty[p_index] = FALSE;
	m_unk0x76c[p_index] = FALSE;
}

// FUNCTION: LEGORACERS 0x00486730
LegoS32 RacerModelScreenBase::VTable0x9c()
{
	GolString string;
	LegoChar modelName[8];

	LegoS32 divisor = 7;
	g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
	LegoU16 random = g_randomTable[g_randomTableIndex];
	LegoU16 textIdIndex = static_cast<LegoU16>(static_cast<LegoS32>(random) % divisor);
	m_menuNameStrings->CopyStringByIndex(&string, g_unk0x004c21bc[textIdIndex]);
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
		partIndex = VTable0x9c();
	} while (partIndex == entity->GetActiveState());

	entity->FUN_0040dad0(partIndex);
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
	m_menuNameStrings->CopyStringByIndex(&string, g_unk0x004c21cc[textIdIndex]);
	string.CopyToBuf8(modelName);

	LegoS32 partIndex = m_modelParts.GetPartIndex(modelName);
	GolAnimatedEntity* entity = &m_driverEntities[modelIndex];
	entity->FUN_0040db80(partIndex, 0xc8, 0.0f, FALSE, FALSE, FALSE);

	LegoU32 flags = entity->GetFlags();
	flags &= ~0x40000;
	flags |= 0x10000;
	entity->SetFlags(flags);
}

// FUNCTION: LEGORACERS 0x004869b0
LegoBool32 RacerModelScreenBase::VTable0x88()
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		if (!(m_driverEntities[i].GetFlags() & 0x10000)) {
			break;
		}

		if (!m_driverEntities[i].FUN_0040e360()) {
			return FALSE;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00486a00
LegoBool32 RacerModelScreenBase::VTable0x78(undefined4 p_elapsed)
{
	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		LegoS32 modelIndex = m_slotModelToggle[i] + (m_modelsPerSlot * i);

		switch (m_slotDirty[i]) {
		default: {
			if (m_driverEntities[modelIndex].GetFlags() & 1) {
				GolAnimatedEntity* entity = &m_driverEntities[modelIndex];
				if (entity->FUN_0040e360() && m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord(i) == NULL &&
					!m_unk0x364) {
					PlayRandomAnimation(i);
				}
			}
			break;
		}
		case TRUE:
			m_unk0x1ddc[i].SetEntity(&m_carGroups[modelIndex]);
			m_modelSlots[i].SetEntity(&m_driverEntities[modelIndex]);
			FUN_00486540();
			UpdateSourceLabel(i);
			m_slotDirty[i] = FALSE;

			if (!m_unk0x364) {
				PlayRandomAnimation(i);
			}
			break;
		}
	}

	FUN_004865c0();
	return MenuGameScreen::VTable0x78(p_elapsed);
}

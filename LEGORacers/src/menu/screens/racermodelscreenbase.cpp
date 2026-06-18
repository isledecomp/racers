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

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

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
	m_unk0x26fc = 0;
	m_unk0x77c = 0;

	::memset(m_unk0x2704, 0, sizeof(m_unk0x2704));
	::memset(m_unk0x774, 0, sizeof(m_unk0x774));
	::memset(m_unk0x76c, 0, sizeof(m_unk0x76c));
	::memset(m_unk0x4ec, 0, sizeof(m_unk0x4ec));
	::memset(m_unk0x4dc, 0, sizeof(m_unk0x4dc));
	::memset(m_unk0x73c, 0, sizeof(m_unk0x73c));
	::memset(m_unk0x780, 0, sizeof(m_unk0x780));

	m_unk0x758.m_z = 1.0f;
	m_unk0x74c.m_x = 1.0f;
	m_unk0x758.m_y = 0.0f;
	m_unk0x758.m_x = 0.0f;
	m_unk0x74c.m_z = 0.0f;
	m_unk0x74c.m_y = 0.0f;

	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00485bb0
void RacerModelScreenBase::FUN_00485bb0()
{
	FUN_00485da0();

	m_unk0x73c[0] = m_context->m_unk0x21f4.GetUnk0x84();

	for (LegoS32 i = 0; i < m_unk0x77c; i++) {
		if (m_unk0x73c[i] == NULL) {
			m_unk0x73c[i] = m_golExport->VTable0x14();
			if (m_unk0x73c[i] == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			m_context->m_unk0x21f4.FUN_00499eb0(m_unk0x73c[i]);
		}

		m_unk0x4fc[i].VTable0x50(m_unk0x73c[i], g_racerPickMaxFloat);
		m_unk0x4fc[i].SetPrimaryMaterialTable(m_context->m_unk0x4224.GetMaterialTable());
	}

	m_modelParts.VTable0x14("rsanim", m_context->m_context->m_unk0x18);
}

// STUB: LEGORACERS 0x00485c80
void RacerModelScreenBase::FUN_00485c80(MenuGameContext* p_context, LegoU32 p_mask)
{
	STUB(0x00485c80);

	SaveSystem* saveSystem = &p_context->m_saveSystem;

	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		RacerUnlockState* modelState = &m_unk0x22dc[i];

		modelState->FUN_00442e60(saveSystem);
		modelState->FUN_00442ef0(p_mask);
		m_unk0x2704[i] = modelState->FUN_00442e80(p_mask);

		if (m_unk0x2704[i]) {
			SaveRecordList::Record* firstRecord = modelState->FUN_004430b0();
			InputBindingPlayerState* player = &saveSystem->GetGameState().GetState().m_inputBindings.m_players[i];
			LegoU32 selectedRecordId = player->m_selectedRecordId;
			LegoU32 selectedRecordSource = player->m_selectedRecordSource;
			LegoU32 selectedSaveIndex = player->m_selectedSaveIndex;

			while (TRUE) {
				SaveRecordList::Record* record = modelState->FUN_00442fe0();

				if (record->m_recordSource == selectedRecordSource && record->m_saveIndex == selectedSaveIndex &&
					record->m_recordId == selectedRecordId) {
					if (firstRecord != record) {
						break;
					}
				}
				else if (firstRecord != record) {
					continue;
				}

				do {
					record = modelState->FUN_00442fe0();
				} while (record->m_recordSource == 3 && firstRecord != record);

				break;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00485da0
void RacerModelScreenBase::FUN_00485da0()
{
	undefined4 modelParams[5];

	m_context->m_modelBuilder.GetMaxMergedCounts(modelParams);

	for (LegoS32 i = 0; i < m_unk0x77c; i++) {
		m_unk0x4ec[i] = m_golExport->VTable0x14();
		if (m_unk0x4ec[i] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_unk0x4dc[i] = m_golExport->VTable0x18();
		if (m_unk0x4dc[i] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_unk0x4ec[i]->VTable0x18(m_renderer, 2, modelParams[0], modelParams[1], modelParams[2], modelParams[3]);
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
	LegoS32 count = m_unk0x26fc;
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
			createParams.m_unk0x08 = &m_unk0x98c[i];
			createParams.m_unk0x2c = slotPosition0;
			m_unk0x1ddc[i].FUN_004875d0(&createParams);

			createParams.m_unk0x2c = slotPosition1;
			createParams.m_unk0x44 = TRUE;
			m_unk0x205c[i].FUN_004875d0(&createParams);

			m_unk0x98c[i].FUN_00465b40(&m_unk0x1ddc[i]);
			m_unk0x98c[i].FUN_00465b40(&m_unk0x205c[i]);

			i++;
		} while (i < m_unk0x26fc);
	}
}

// FUNCTION: LEGORACERS 0x00485f70
void RacerModelScreenBase::VTable0x4c()
{
	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\RS_SET");
	}

	LegoS32 i;

	for (i = 0; i < m_unk0x26fc; i++) {
		CreateFramedSceneView(&m_unk0x98c[i], 0, i + 0x6e);
	}

	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	for (i = 0; i < m_unk0x26fc; i++) {
		CreateTextLabel(&m_unk0x1cec[i], i + 0x72, 0x37, 0x37);
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
	m_unk0x26fc = p_params[0];
	m_unk0x2700 = p_params[1];
	m_unk0x77c = m_unk0x2700 * m_unk0x26fc;

	if (!p_context->m_unk0x21f4.IsInitialized()) {
		FUN_0047ff50(p_context, TRUE);
	}

	if (!p_context->m_modelBuilder.HasMenuResources()) {
		FUN_00480210(p_context, FALSE);
	}

	FUN_00485c80(p_context, p_params[2]);

	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	FUN_00485bb0();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004860f0
LegoBool32 RacerModelScreenBase::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	for (LegoS32 i = 0; i < m_unk0x77c; i++) {
		m_unk0x232c[i].VTable0x54();
		m_unk0x4fc[i].VTable0x54();
		m_golExport->VTable0x48(m_unk0x4ec[i]);
		m_golExport->VTable0x4c(m_unk0x4dc[i]);

		if (i != 0) {
			m_golExport->VTable0x48(m_unk0x73c[i]);
		}
	}

	return MenuGameScreen::Destroy();
}

// STUB: LEGORACERS 0x004861b0
void RacerModelScreenBase::FUN_004861b0()
{
	STUB(0x004861b0);

	GameState& state = m_context->m_saveSystem.GetGameState();

	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		SaveRecordList::Record* record = m_unk0x22dc[i].FUN_004430b0();

		if (record != NULL) {
			InputBindingPlayerState& player = state.GetState().m_inputBindings.m_players[i];

			player.m_selectedRecordSource = record->m_recordSource;
			state.SetDirty(1);
			player.m_selectedSaveIndex = record->m_saveIndex;
			state.SetDirty(1);
			player.m_selectedRecordId = record->m_recordId;
			state.SetDirty(1);
		}
	}

	if (m_context->m_menuStack.Peek() != 0x30) {
		m_context->m_menuStack.Push(0x30);
	}
}

// FUNCTION: LEGORACERS 0x00486250
void RacerModelScreenBase::FUN_00486250(LegoS32 p_index)
{
	SaveRecordList::Record* record = m_unk0x22dc[p_index].FUN_004430b0();
	LegoS32 modelIndex = m_unk0x780[p_index] + (m_unk0x2700 * p_index);

	DriverCosmetics cosmetics;
	record->GetCosmetics(&cosmetics);

	if (m_unk0x77c == 1) {
		m_context->m_modelBuilder.RefreshMenuResources();
	}

	m_context->m_modelBuilder.SetExpressionMask(0xffff);
	GolModelBase* model = m_context->m_modelBuilder.BuildDriverModel(&cosmetics, m_unk0x4ec[modelIndex], 0);
	m_context->m_modelBuilder.ApplyFaceExpression(model, &cosmetics);

	m_unk0x4dc[modelIndex]->VTable0x10(m_context->m_modelBuilder.GetBodySceneNode(&cosmetics));
	m_unk0x232c[modelIndex]
		.FUN_0040d550(m_unk0x4ec[modelIndex], m_unk0x4dc[modelIndex], &m_modelParts, g_racerPickMaxFloat);

	record->CopyCarData(m_unk0x788);
	m_context->m_unk0x21f4.FUN_0049c7f0(m_unk0x788);
	m_context->m_unk0x21f4.FUN_0049b740(0);
	m_context->m_unk0x21f4.FUN_0049bc60(m_unk0x73c[modelIndex], 1, 0x7f);

	AwardCinematicScreen::SceneEntityGroup::CreateParams createParams;
	createParams.m_unk0x0c = NULL;
	createParams.m_chassisModels = &m_context->m_chassisModels;
	createParams.m_unk0x04 = &m_context->m_unk0x21f4;
	createParams.m_unk0x08 = &m_unk0x4fc[modelIndex];
	record->GetChassisName(createParams.m_chassisName);

	m_unk0x39c[modelIndex].FUN_00479510(&createParams);
}

// FUNCTION: LEGORACERS 0x00486400
void RacerModelScreenBase::FUN_00486400(LegoS32 p_index)
{
	m_unk0x780[p_index] = (m_unk0x780[p_index] + 1) % m_unk0x2700;
	FUN_004866e0(p_index);
	FUN_00486250(p_index);
	m_unk0x774[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x00486440
void RacerModelScreenBase::FUN_00486440(LegoS32 p_index)
{
	SaveRecordList::Record* record = m_unk0x22dc[p_index].FUN_004430b0();
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

	if (m_unk0x1cec[p_index].GetFlags() & 1) {
		m_unk0x1cec[p_index].VTable0x44(static_cast<undefined2>(textId), 0);
	}
}

// FUNCTION: LEGORACERS 0x004864a0
void RacerModelScreenBase::FUN_004864a0(LegoS32 p_index)
{
	m_unk0x22dc[p_index].FUN_00442fe0();
	m_unk0x780[p_index] = (m_unk0x780[p_index] + 1) % m_unk0x2700;
	FUN_004866e0(p_index);
	FUN_00486250(p_index);
	m_unk0x774[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x004864f0
void RacerModelScreenBase::FUN_004864f0(LegoS32 p_index)
{
	m_unk0x22dc[p_index].FUN_00443050();
	m_unk0x780[p_index] = (m_unk0x780[p_index] + 1) % m_unk0x2700;
	FUN_004866e0(p_index);
	FUN_00486250(p_index);
	m_unk0x774[p_index] = TRUE;
}

// FUNCTION: LEGORACERS 0x00486540
void RacerModelScreenBase::FUN_00486540()
{
	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		GolWorldEntity* entity = m_unk0x205c[i].GetUnk0x68();

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
	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		GolWorldEntity* target = m_unk0x1ddc[i].GetUnk0x68();
		if (target != NULL) {
			GolWorldDatabase* database = m_unk0x98c[i].GetUnk0x60();
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
void RacerModelScreenBase::FUN_004866e0(LegoS32 p_index)
{
	m_unk0x1ddc[p_index].FUN_00487600(NULL);
	m_unk0x205c[p_index].FUN_00487600(NULL);
	m_unk0x774[p_index] = FALSE;
	m_unk0x76c[p_index] = FALSE;
}

// FUNCTION: LEGORACERS 0x00486730
LegoS32 RacerModelScreenBase::VTable0x9c()
{
	GolString string;
	LegoChar modelName[8];

	LegoS32 divisor = 7;
	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
	LegoU16 random = g_unk0x004befec[g_unk0x004c6ee4];
	LegoU16 textIdIndex = static_cast<LegoU16>(static_cast<LegoS32>(random) % divisor);
	m_menuNameStrings->CopyStringByIndex(&string, g_unk0x004c21bc[textIdIndex]);
	string.CopyToBuf8(modelName);
	return m_modelParts.GetPartIndex(modelName);
}

// FUNCTION: LEGORACERS 0x00486810
void RacerModelScreenBase::FUN_00486810(LegoS32 p_index)
{
	LegoS32 modelIndex = m_unk0x780[p_index] + (m_unk0x2700 * p_index);
	GolAnimatedEntity* entity = &m_unk0x232c[modelIndex];
	LegoS32 partIndex;

	do {
		partIndex = VTable0x9c();
	} while (partIndex == entity->GetActiveState());

	entity->FUN_0040dad0(partIndex);
	entity->SetFlags((entity->GetFlags() & ~0x40000) | 0x10000);
}

// FUNCTION: LEGORACERS 0x00486890
void RacerModelScreenBase::FUN_00486890(LegoS32 p_index)
{
	GolString string;
	LegoChar modelName[8];

	LegoS32 modelIndex = m_unk0x780[p_index] + (m_unk0x2700 * p_index);
	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
	LegoU16 random = g_unk0x004befec[g_unk0x004c6ee4];
	LegoS32 textIdIndex = static_cast<LegoS32>(random) % 3;
	m_menuNameStrings->CopyStringByIndex(&string, g_unk0x004c21cc[textIdIndex]);
	string.CopyToBuf8(modelName);

	LegoS32 partIndex = m_modelParts.GetPartIndex(modelName);
	GolAnimatedEntity* entity = &m_unk0x232c[modelIndex];
	entity->FUN_0040db80(partIndex, 0xc8, 0.0f, FALSE, FALSE, FALSE);

	LegoU32 flags = entity->GetFlags();
	flags &= ~0x40000;
	flags |= 0x10000;
	entity->SetFlags(flags);
}

// FUNCTION: LEGORACERS 0x004869b0
LegoBool32 RacerModelScreenBase::VTable0x88()
{
	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		if (!(m_unk0x232c[i].GetFlags() & 0x10000)) {
			break;
		}

		if (!m_unk0x232c[i].FUN_0040e360()) {
			return FALSE;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00486a00
LegoBool32 RacerModelScreenBase::VTable0x78(undefined4 p_elapsed)
{
	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		LegoS32 modelIndex = m_unk0x780[i] + (m_unk0x2700 * i);

		switch (m_unk0x774[i]) {
		default: {
			if (m_unk0x232c[modelIndex].GetFlags() & 1) {
				GolAnimatedEntity* entity = &m_unk0x232c[modelIndex];
				if (entity->FUN_0040e360() && m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord(i) == NULL &&
					!m_unk0x364) {
					FUN_00486810(i);
				}
			}
			break;
		}
		case TRUE:
			m_unk0x1ddc[i].FUN_00487600(&m_unk0x39c[modelIndex]);
			m_unk0x205c[i].FUN_00487600(&m_unk0x232c[modelIndex]);
			FUN_00486540();
			FUN_00486440(i);
			m_unk0x774[i] = FALSE;

			if (!m_unk0x364) {
				FUN_00486810(i);
			}
			break;
		}
	}

	FUN_004865c0();
	return MenuGameScreen::VTable0x78(p_elapsed);
}

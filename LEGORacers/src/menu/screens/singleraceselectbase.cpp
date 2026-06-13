#include "menu/screens/singleraceselectbase.h"

#include "core/gol.h"
#include "golanimatedentity.h"
#include "golhashtable.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/widgets/visualstatecolor.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(SingleRaceSelectBase, 0x1908)

// GLOBAL: LEGORACERS 0x004c2278
static VisualStateColor g_singleRaceVisualStates[] = {
	{{0xffadadad}},
	{{0xff00dfff}},
	{{0xffb4dce6}},
	{{0xffdf3d25}},
};

// GLOBAL: LEGORACERS 0x004c228c
static LegoU8 g_singleRaceVisualStateMap[] = {
	1, 0, 3, 2, 1, 0, 3, 2, 0, 1, 2, 3, 2, 0, 3, 1, 2, 0, 3, 1, 3, 1, 2, 0,
};

// FUNCTION: LEGORACERS 0x00488750
SingleRaceSelectBase::SingleRaceSelectBase()
{
	MenuGameScreen::Reset();
	m_unk0x1904 = 0;
	m_unk0x754 = 0;
	m_unk0x658[0] = '\0';
}

// FUNCTION: LEGORACERS 0x00488840
SingleRaceSelectBase::~SingleRaceSelectBase()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004888f0
LegoBool32 SingleRaceSelectBase::Destroy()
{
	MenuGameContext* context = m_context;

	if (!m_initialized) {
		return TRUE;
	}

	m_unk0x660.VTable0x54();
	if (m_unk0x754) {
		m_golExport->VTable0x48(m_unk0x754);
		m_unk0x754 = NULL;
	}

	FUN_004803a0();
	m_unk0x658[0] = '\0';
	m_unk0x1904 = NULL;

	LegoBool32 result = MenuSceneScreen::Destroy();
	context->m_unk0x21f4.FUN_00499ee0();

	return result;
}

// FUNCTION: LEGORACERS 0x00488970
void SingleRaceSelectBase::VTable0x4c()
{
	LegoS32 optionCount = 3 + ((m_menuId != 0x1d) ? 4 : 0);

	CreateFrame(&m_unk0x758, 0x47, 0x47);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\SINGRACE");
	}

	CreateRegion(&m_unk0x368, 6);
	m_unk0x368.m_unk0x2b0->SetFlags(CutsceneDefinition::Frame::c_flagLoop);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	CreateTriangle(&m_unk0x1860, 0x5e);

	Rect rect;
	rect.m_left = 0;
	rect.m_top = 0;
	rect.m_right = m_unk0x368.GetRect()->m_right - m_unk0x368.GetRect()->m_left;
	rect.m_bottom = m_unk0x368.GetRect()->m_bottom - m_unk0x368.GetRect()->m_top;
	m_unk0x1860.VTable0x10(&rect);
	m_unk0x1860.SetAlphaOverride(200);
	m_unk0x1860.ClearFlags(2);

	CreateCarousel(&m_unk0xb54, 0x3e, 0x3b);
	CreateSelector(&m_unk0xbe8, &m_unk0xb54, 0x95, 0x4d);

	for (LegoS32 i = 0; i < optionCount; i++) {
		CreateImage(&m_unk0x15dc[i], static_cast<undefined2>(i + 0x61), 0x9d);
		m_unk0xb54.FUN_0046d9c0(&m_unk0x15dc[i]);
	}

	m_unk0xb54.VTable0x50(0);
}

// FUNCTION: LEGORACERS 0x00488ac0
LegoBool32 SingleRaceSelectBase::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	m_unk0x1904 = NULL;

	p_context->m_unk0x21f4.FUN_00499f00();
	LegoBool32 result = MenuSceneScreen::VTable0x8c(p_context, p_createParams);
	if (!result) {
		return result;
	}

	m_cursor->SetCursorEnabled(TRUE);

	if (!p_context->m_modelBuilder.HasMenuResources()) {
		FUN_00480210(m_context, 0);
	}

	FUN_00480310();
	m_unk0x368.m_unk0x2cc = FALSE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00488b40
void SingleRaceSelectBase::FUN_00488b40(const LegoChar* p_name)
{
	GolAnimatedEntity* modelEntity = NULL;
	LegoU32 i = 0;
	CutsceneDefinition::Frame* frame = m_unk0x368.m_unk0x2b0;

	while (!modelEntity) {
		if (i >= m_unk0x368.m_unk0x58.GetWorldDatabaseCount()) {
			break;
		}

		GolWorldDatabase* worldDatabase = m_unk0x368.m_unk0x58.GetWorldDatabase(i);
		if (!modelEntity && worldDatabase->GetUnk0xc0NameEntries()) {
			modelEntity = worldDatabase->GetUnk0xc0Name("guy1");
		}

		i++;
	}

	LegoChar* name = m_unk0x658;
	if (::strncmp(name, p_name, sizeof(m_unk0x658)) != 0) {
		::strncpy(name, p_name, sizeof(m_unk0x658));

		if (m_unk0x660.HasModel()) {
			m_unk0x660.VTable0x54();
			m_context->m_modelBuilder.RefreshMenuResources();
		}

		if (m_unk0x754) {
			m_golExport->VTable0x48(m_unk0x754);
			m_unk0x754 = NULL;
		}

		DriverCosmetics cosmetics;
		m_context->m_cosmeticTable.CopyCosmetics(name, &cosmetics);
		m_unk0x754 = m_context->m_modelBuilder.BuildDriverModel(&cosmetics, NULL, 0);
		m_unk0x660.FUN_0040d550(
			m_unk0x754,
			modelEntity->VTable0x58(0),
			modelEntity->GetModelPart(),
			modelEntity->GetModelDistance(0)
		);
	}

	if (m_unk0x660.HasModel()) {
		for (LegoU32 i = 0; i < frame->GetModelCount(); i++) {
			CutsceneDefinition::Frame::ModelEvent* model = frame->GetModel(i);
			if (model->GetEntity() == modelEntity) {
				model->SetEntity(&m_unk0x660);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00488cb0
void SingleRaceSelectBase::FUN_00488cb0(LegoS32 p_index)
{
	m_unk0x758.FUN_0046f050(&g_singleRaceVisualStates[g_singleRaceVisualStateMap[p_index]]);
}

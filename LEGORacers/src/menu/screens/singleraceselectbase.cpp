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
	m_circuitEntry = 0;
	m_driverModel = 0;
	m_driverName[0] = '\0';
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

	m_driverEntity.ResetModelState();
	if (m_driverModel) {
		m_golExport->DestroyModel(m_driverModel);
		m_driverModel = NULL;
	}

	ClearCosmeticTable();
	m_driverName[0] = '\0';
	m_circuitEntry = NULL;

	LegoBool32 result = MenuSceneScreen::Destroy();
	context->m_carBuildModel.AcquireBuffers();

	return result;
}

// FUNCTION: LEGORACERS 0x00488970
void SingleRaceSelectBase::CreateWidgets()
{
	LegoS32 optionCount = 3 + ((m_menuId != 0x1d) ? 4 : 0);

	CreateFrame(&m_borderFrame, 0x47, 0x47);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\SINGRACE");
	}

	CreateRegion(&m_sceneWidget, 6);
	m_sceneWidget.m_frame->SetFlags(CutsceneDefinition::Frame::c_flagLoop);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	CreateTriangle(&m_sceneOverlay, 0x5e);

	Rect rect;
	rect.m_left = 0;
	rect.m_top = 0;
	rect.m_right = m_sceneWidget.GetRect()->m_right - m_sceneWidget.GetRect()->m_left;
	rect.m_bottom = m_sceneWidget.GetRect()->m_bottom - m_sceneWidget.GetRect()->m_top;
	m_sceneOverlay.SetRect(&rect);
	m_sceneOverlay.SetAlphaOverride(200);
	m_sceneOverlay.ClearFlags(2);

	CreateCarousel(&m_trackCarousel, 0x3e, 0x3b);
	CreateSelector(&m_trackSelector, &m_trackCarousel, 0x95, 0x4d);

	for (LegoS32 i = 0; i < optionCount; i++) {
		CreateImage(&m_trackIcons[i], static_cast<undefined2>(i + 0x61), 0x9d);
		m_trackCarousel.AddItem(&m_trackIcons[i]);
	}

	m_trackCarousel.SetSelection(0);
}

// FUNCTION: LEGORACERS 0x00488ac0
LegoBool32 SingleRaceSelectBase::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	m_circuitEntry = NULL;

	p_context->m_carBuildModel.ReleaseBuffers();
	LegoBool32 result = MenuSceneScreen::Initialize(p_context, p_createParams);
	if (!result) {
		return result;
	}

	m_cursor->SetCursorEnabled(TRUE);

	if (!p_context->m_modelBuilder.HasMenuResources()) {
		LoadPartResources(m_context, 0);
	}

	LoadCosmeticTable();
	m_sceneWidget.m_skippable = FALSE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00488b40
void SingleRaceSelectBase::SetPreviewDriver(const LegoChar* p_name)
{
	GolAnimatedEntity* modelEntity = NULL;
	LegoU32 i = 0;
	CutsceneDefinition::Frame* frame = m_sceneWidget.m_frame;

	while (!modelEntity) {
		if (i >= m_sceneWidget.m_definition.GetWorldDatabaseCount()) {
			break;
		}

		GolWorldDatabase* worldDatabase = m_sceneWidget.m_definition.GetWorldDatabase(i);
		if (!modelEntity && worldDatabase->GetAnimatedEntityEntries()) {
			modelEntity = worldDatabase->GetAnimatedEntityByName("guy1");
		}

		i++;
	}

	LegoChar* name = m_driverName;
	if (::strncmp(name, p_name, sizeof(m_driverName)) != 0) {
		::strncpy(name, p_name, sizeof(m_driverName));

		if (m_driverEntity.HasModel()) {
			m_driverEntity.ResetModelState();
			m_context->m_modelBuilder.RefreshMenuResources();
		}

		if (m_driverModel) {
			m_golExport->DestroyModel(m_driverModel);
			m_driverModel = NULL;
		}

		DriverCosmetics cosmetics;
		m_context->m_cosmeticTable.CopyCosmetics(name, &cosmetics);
		m_driverModel = m_context->m_modelBuilder.BuildDriverModel(&cosmetics, NULL, 0);
		m_driverEntity.SetModel(
			m_driverModel,
			modelEntity->GetSceneNode(0),
			modelEntity->GetModelPart(),
			modelEntity->GetModelDistance(0)
		);
	}

	if (m_driverEntity.HasModel()) {
		for (LegoU32 i = 0; i < frame->GetModelEventCount(); i++) {
			CutsceneDefinition::Frame::ModelEvent* model = frame->GetModel(i);
			if (model->GetEntity() == modelEntity) {
				model->SetEntity(&m_driverEntity);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00488cb0
void SingleRaceSelectBase::ApplyThemeColor(LegoS32 p_index)
{
	m_borderFrame.SetBorderColors(&g_singleRaceVisualStates[g_singleRaceVisualStateMap[p_index]]);
}

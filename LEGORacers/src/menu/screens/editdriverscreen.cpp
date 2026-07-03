#include "menu/screens/editdriverscreen.h"

#include "golhashtable.h"
#include "golname.h"
#include "golstream.h"
#include "golstring.h"
#include "golstringtable.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "racer/drivercosmetics.h"
#include "save/memorycardsavegame.h"
#include "save/saverecordlist.h"
#include "surface/color.h"

#include <string.h>

DECOMP_SIZE_ASSERT(EditDriverScreen, 0x4774)
DECOMP_SIZE_ASSERT(MenuRacerCarousel, 0x170)
DECOMP_SIZE_ASSERT(DriverHeadBuilder, 0x50)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// GLOBAL: LEGORACERS 0x004c20b8
LegoU16 g_idleAnimTextIds[8] = {0x74, 0x75, 0x76, 0xd3, 0x81, 0x82, 0x78, 0x79};

// GLOBAL: LEGORACERS 0x004c20c8
LegoU16 g_exitAnimTextIds[2] = {0x7c, 0x80};

// FUNCTION: LEGORACERS 0x0047ce30
EditDriverScreen::EditDriverScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047cf90
EditDriverScreen::~EditDriverScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047d0d0
void EditDriverScreen::Reset()
{
	m_nextViewportIndex = 1;
	m_cosmeticsDirty = 0;
	m_pendingAnimTextId = 0;
	m_savePending = 0;

	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047d100
void EditDriverScreen::LoadHeadBuilder(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	DriverHeadBuilder::LoadParams params;
	::memset(&params, 0, sizeof(params));

	params.m_renderer = p_createParams->m_renderer;
	params.m_golExport = p_createParams->m_golExport;
	params.m_partCatalog = &p_context->m_partCatalog;
	params.m_binary = p_context->m_context->m_useBinaryFiles;
	params.m_partLibrary = p_context->m_partResources.GetPartLibrary();
	m_headBuilder.Load(&params, 2);
}

// FUNCTION: LEGORACERS 0x0047d170
LegoBool32 EditDriverScreen::CreateRacerCarousel(
	MenuRacerCarousel* p_widget,
	undefined2 p_createParamId,
	undefined2 p_styleId,
	LegoU32 p_category
)
{
	MenuRacerCarousel::CreateParams* sourceParams =
		static_cast<MenuRacerCarousel::CreateParams*>(GetBindingEntry(p_createParamId));
	MenuStyleTable::CarouselStyle* styleEntry = static_cast<MenuStyleTable::CarouselStyle*>(GetStyleEntry(p_styleId));

	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuRacerCarousel::CreateParams createParams;
	::memcpy(&createParams, sourceParams, sizeof(createParams));
	ApplyWidgetDefaults(&createParams);

	createParams.m_context = m_context;
	createParams.m_viewportIndex = m_nextViewportIndex++;
	createParams.m_headBuilder = &m_headBuilder;
	createParams.m_partType = p_category;
	createParams.m_aspectScale = GetAspectScale();
	return p_widget->Create(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0047d230
void EditDriverScreen::CreateDriverScene()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\CB_SET");
	}

	CreateFramedSceneView(&m_sceneView, 0, 0xd0);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	MainMenuModelSlot::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	createParams.m_golExport = m_golExport;
	createParams.m_renderer = m_renderer;
	createParams.m_sceneView = &m_sceneView;
	createParams.m_modelBuilder = &m_context->m_modelBuilder;
	createParams.m_position.m_x = -5.3590002f;
	createParams.m_position.m_y = -3.1500001f;
	createParams.m_position.m_z = 0.026000001f;

	m_modelSlot.Create(&createParams);
	m_sceneView.AddElement(&m_modelSlot);
}

// FUNCTION: LEGORACERS 0x0047d2f0
void EditDriverScreen::CreateWidgets()
{
	CreateImage(&m_photoImage, 0x49, 0x49);
	CreateRacerCarousel(&m_cosmeticCarousels[0], 0xcd, 0x3b, 0);
	CreateRacerCarousel(&m_cosmeticCarousels[1], 0xce, 0x3b, 1);
	CreateRacerCarousel(&m_cosmeticCarousels[2], 0xcd, 0x3b, 2);
	CreateRacerCarousel(&m_cosmeticCarousels[3], 0xcd, 0x3b, 3);
	CreateSelector(&m_cosmeticSelectors[0], &m_cosmeticCarousels[0], 0xc8, 0xcc);
	CreateSelector(&m_cosmeticSelectors[1], &m_cosmeticCarousels[1], 0xc9, 0xcc);
	CreateSelector(&m_cosmeticSelectors[2], &m_cosmeticCarousels[2], 0xca, 0xcc);
	CreateSelector(&m_cosmeticSelectors[3], &m_cosmeticCarousels[3], 0xcb, 0xcc);
	CreateDriverScene();
	CreateTextLabel(&m_infoLabel, 0x3a, 0x3a, 9);
	m_infoLabel.WrapText(0x14);
	CreateTextButton(&m_randomButton, 0xd2, 0x42, 0x38);

	if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
		CreateTextButton(&m_doneButton, 0x40, 0x44, 0x0a);
	}
	else {
		CreateTextButton(&m_doneButton, 0x40, 0x46, 0x72);
	}

	CreateTextButton(&m_backButton, 0x3f, 0x45, 0x1f);
}

// FUNCTION: LEGORACERS 0x0047d460
LegoBool32 EditDriverScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!p_context->m_modelBuilder.HasMenuResources()) {
		LoadPartResources(p_context, FALSE);
	}

	if (!MenuGameScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	ColorRGBA materialColor;
	ColorRGBA lightColor;
	materialColor.m_blu = 0x80;
	materialColor.m_grn = 0x80;
	materialColor.m_red = 0x80;
	lightColor.m_alp = 0xff;
	lightColor.m_blu = 0xff;
	lightColor.m_grn = 0xff;
	lightColor.m_red = 0xff;
	materialColor.m_alp = 0xff;
	SetLighting(&materialColor, &lightColor);

	m_modelSlot.GetBodyModelPart()->Load("cbanim", p_context->m_context->m_useBinaryFiles);
	p_context->m_carBuildModel.ReleaseBuffers();
	LoadHeadBuilder(p_context, p_createParams);
	LoadCosmetics();
	PlayNextAnimation();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047d520
LegoBool32 EditDriverScreen::Destroy()
{
	MenuGameContext* context = m_context;

	if (!m_initialized) {
		return TRUE;
	}

	m_headBuilder.ReleaseResources();
	context->m_carBuildModel.AcquireBuffers();

	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x0047d560
LegoBool32 EditDriverScreen::HasUnsavedChanges()
{
	if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
		return FALSE;
	}

	DriverCosmetics cosmetics;
	m_context->m_saveSystem.GetActiveRecord().GetCosmetics(&cosmetics);

	if (cosmetics.m_hatIndex == m_driverCosmetics.m_components[0] &&
		cosmetics.m_faceIndex == m_driverCosmetics.m_components[1] &&
		cosmetics.m_torsoIndex == m_driverCosmetics.m_components[2]) {
		return cosmetics.m_legIndex != m_driverCosmetics.m_components[3];
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047d5d0
LegoS32 EditDriverScreen::PickNextAnimation()
{
	GolString string;
	m_menuNameStrings->CopyStringByIndex(&string, 0x83);

	if (m_pendingAnimTextId) {
		m_menuNameStrings->CopyStringByIndex(&string, m_pendingAnimTextId);
		m_pendingAnimTextId = 0;
	}
	else {
		g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
		LegoU16 random = g_randomTable[g_randomTableIndex];
		LegoU16 textIdIndex = static_cast<LegoU16>(static_cast<LegoS32>(random) % 8);
		m_menuNameStrings->CopyStringByIndex(&string, g_idleAnimTextIds[textIdIndex]);
	}

	GolName name;
	string.CopyToBuf8(name);
	return m_modelSlot.GetBodyModelPart()->GetPartIndex(name);
}

// FUNCTION: LEGORACERS 0x0047d6f0
void EditDriverScreen::PlayNextAnimation()
{
	GolAnimatedEntity* entity = m_modelSlot.GetDriverEntity();
	LegoS32 partIndex;

	do {
		partIndex = PickNextAnimation();
	} while (partIndex == entity->GetActiveState());

	entity->PlayPart(partIndex);
	entity->SetFlags((entity->GetFlags() & ~0x40000) | 0x10000);
}

// FUNCTION: LEGORACERS 0x0047d740
void EditDriverScreen::PlayExitAnimation()
{
	GolString string;
	GolName name;

	g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
	LegoU16 random = g_randomTable[g_randomTableIndex];
	LegoS32 textIdIndex = static_cast<LegoS32>(random) % 2;
	m_menuNameStrings->CopyStringByIndex(&string, g_exitAnimTextIds[textIdIndex]);
	string.CopyToBuf8(name);

	GolAnimatedEntity* entity = m_modelSlot.GetDriverEntity();
	LegoS32 partIndex = m_modelSlot.GetBodyModelPart()->GetPartIndex(name);
	entity->TransitionToPart(partIndex, 0xc8, 0.0f, FALSE, FALSE, FALSE);
	entity->SetFlags((entity->GetFlags() & ~0x40000) | 0x10000);
}

// FUNCTION: LEGORACERS 0x0047d840
void EditDriverScreen::LoadCosmetics()
{
	m_context->m_saveSystem.GetActiveRecord().GetCosmetics(&m_driverCosmetics);

	m_cosmeticCarousels[0].SelectValue(m_driverCosmetics.m_components[0]);
	m_cosmeticCarousels[1].SelectValue(m_driverCosmetics.m_components[1]);
	m_cosmeticCarousels[2].SelectValue(m_driverCosmetics.m_components[2]);
	m_cosmeticCarousels[3].SelectValue(m_driverCosmetics.m_components[3]);

	m_modelSlot.SetCosmetics(&m_driverCosmetics);
	m_cosmeticSelectors[0].Select(4);
	m_cosmeticsDirty = 0;
}

// FUNCTION: LEGORACERS 0x0047d8e0
void EditDriverScreen::SaveCosmetics()
{
	m_context->m_saveSystem.GetActiveRecord().SetCosmetics(&m_driverCosmetics);

	if ((m_context->m_modelBuilder.GetMenuFlowFlags() == 0) & TRUE) {
		m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord()->CopyFrom(
			&m_context->m_saveSystem.GetActiveRecord()
		);
		m_savePending = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0047d940
void EditDriverScreen::RemoveSelectedRecord()
{
	SaveRecordList::Record* record = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord();
	SaveRecordList* records = NULL;

	switch (record->m_recordSource) {
	case 1:
		records = &m_context->m_saveSystem.GetSessionSave();
		break;
	case 2:
		records = &m_context->m_saveSystem.GetMemoryCardSaves()[record->m_saveIndex];
		break;
	}

	records->RemoveRecord(record);
	m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(NULL);
}

// FUNCTION: LEGORACERS 0x0047d9a0
LegoBool32 EditDriverScreen::CanNavigate()
{
	GolAnimatedEntity* entity = m_modelSlot.GetDriverEntity();

	return entity->IsPartAnimationDone() || !(entity->GetFlags() & 0x10000);
}

// FUNCTION: LEGORACERS 0x0047d9d0
void EditDriverScreen::Navigate()
{
	switch (m_nextMenuId) {
	case 0x10:
		m_context->m_menuStack.Pop();
		m_context->m_menuStack.Push(0x10);
		break;

	case 3:
		m_context->m_menuStack.Pop();

		if (m_savePending) {
			m_context->m_menuStack.Push(0x30);
		}

		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() & ~DriverModelBuilder::c_menuFlowNewRacer
		);
		break;
	}
}

// FUNCTION: LEGORACERS 0x0047da50
LegoBool32 EditDriverScreen::HandleKeyDown(MenuWidget* p_source, InputEventQueue::Event*, undefined4, undefined4)
{
	if (m_navPending) {
		return TRUE;
	}

	for (LegoS32 i = 0; i < 4; i++) {
		if (p_source == &m_cosmeticCarousels[i]) {
			OnWidgetValueChanged(&m_cosmeticSelectors[i]);
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0047dab0
void EditDriverScreen::OnWidgetValueChanged(MenuWidget* p_source)
{
	m_cosmeticsDirty = TRUE;

	if (p_source == &m_cosmeticSelectors[0]) {
		LegoU32 index = m_cosmeticCarousels[0].GetSelectedValue();
		m_driverCosmetics.m_components[0] = static_cast<LegoU8>(index);
		index &= 0xff;
		m_modelSlot.SetHat(index);
		m_pendingAnimTextId = 0x83;
		return;
	}
	else if (p_source == &m_cosmeticSelectors[1]) {
		LegoU32 index = m_cosmeticCarousels[1].GetSelectedValue();
		m_driverCosmetics.m_components[1] = static_cast<LegoU8>(index);
		index &= 0xff;
		m_modelSlot.SetFace(index, 0);
		m_pendingAnimTextId = 0x83;
		return;
	}
	else if (p_source == &m_cosmeticSelectors[2]) {
		LegoU32 index = m_cosmeticCarousels[2].GetSelectedValue();
		m_driverCosmetics.m_components[2] = static_cast<LegoU8>(index);
		index &= 0xff;
		m_modelSlot.SetTorso(index);
		m_pendingAnimTextId = 0x84;
		return;
	}
	else if (p_source == &m_cosmeticSelectors[3]) {
		LegoU32 index = m_cosmeticCarousels[3].GetSelectedValue();
		m_driverCosmetics.m_components[3] = static_cast<LegoU8>(index);
		index &= 0xff;
		m_modelSlot.SetLegs(index);

		g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
		LegoU16 random = g_randomTable[g_randomTableIndex];
		m_pendingAnimTextId = (static_cast<LegoS32>(random) % 2) ? 0xd4 : 0x85;
		return;
	}
	else {
		m_cosmeticsDirty = FALSE;
	}
}

// FUNCTION: LEGORACERS 0x0047dbf0
void EditDriverScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_randomButton) {
		LegoS32 i;
		for (i = 0; i < 4; i++) {
			g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
			LegoU16 random = g_randomTable[g_randomTableIndex];
			m_cosmeticCarousels[i].SetSelection(static_cast<LegoS32>(random) % m_cosmeticCarousels[i].GetItemCount());
		}

		m_driverCosmetics.m_components[0] = static_cast<LegoU8>(m_cosmeticCarousels[0].GetSelectedValue());
		m_driverCosmetics.m_components[1] = static_cast<LegoU8>(m_cosmeticCarousels[1].GetSelectedValue());
		m_driverCosmetics.m_components[2] = static_cast<LegoU8>(m_cosmeticCarousels[2].GetSelectedValue());
		m_driverCosmetics.m_components[3] = static_cast<LegoU8>(m_cosmeticCarousels[3].GetSelectedValue());

		m_modelSlot.SetCosmetics(&m_driverCosmetics);
	}
	else if (p_source == &m_backButton) {
		if (HasUnsavedChanges()) {
			CreateTextButton(&m_confirmYesButton, 0x99, 0x46, 0x20);
			CreateTextButton(&m_confirmNoButton, 0x99, 0x45, 0x1f);
			ShowConfirmDialog(&m_confirmYesButton, &m_confirmNoButton, 0x7b);
		}
		else if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
			CreateTextButton(&m_confirmYesButton, 0x99, 0x46, 0x73);
			CreateTextButton(&m_confirmNoButton, 0x99, 0x45, 0x74);
			ShowConfirmDialog(&m_confirmYesButton, &m_confirmNoButton, 0x77);
		}
		else {
			OnIconUnfocused(&m_confirmYesButton);
		}
	}
	else if (p_source == &m_doneButton) {
		SaveCosmetics();
		PlayExitAnimation();

		if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
			m_nextMenuId = 0x10;
		}
		else {
			m_nextMenuId = 3;
		}
	}
	else if (p_source == &m_confirmYesButton) {
		if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
			RemoveSelectedRecord();
		}

		GolAnimatedEntity* entity = m_modelSlot.GetDriverEntity();
		entity->SetFlags(entity->GetFlags() & ~0x10000);

		if (m_dialog->GetOpenCount() > 0) {
			m_dialog->DismissTop();
		}

		m_nextMenuId = 3;
	}
	else if (p_source == &m_confirmNoButton) {
		m_dialog->DismissTop();
	}

	if (m_nextMenuId != 0xffff) {
		m_navPending = TRUE;
		m_clickedWidget = p_source;
	}
}

// FUNCTION: LEGORACERS 0x0047de30
LegoBool32 EditDriverScreen::Update(undefined4 p_source)
{
	if (!m_navPending && m_modelSlot.GetDriverEntity()->IsPartAnimationDone()) {
		PlayNextAnimation();
	}

	return MenuGameScreen::Update(p_source);
}

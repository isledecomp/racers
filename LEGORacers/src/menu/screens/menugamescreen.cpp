#include "menu/screens/menugamescreen.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golstring.h"
#include "input/inputmanager.h"
#include "menu/menugamecontext.h"
#include "menu/widgets/menutextbutton.h"
#include "racer/carpartcarousel.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuGameScreen, 0x368)
DECOMP_SIZE_ASSERT(MenuGameScreen::ButtonBindingTable::ButtonBinding, 0xe0)
DECOMP_SIZE_ASSERT(CarPartCarousel, 0x154)
DECOMP_SIZE_ASSERT(CarPartCarousel::CreateParams, 0x84)

// GLOBAL: LEGORACERS 0x004b2a34
static const LegoFloat g_twoPiGame = 6.2831855f;

// GLOBAL: LEGORACERS 0x004c7660
LegoFloat g_viewStepAngle = g_twoPiGame * 0.125f;

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void MenuGameScreen::SetupLighting()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void MenuGameScreen::OnChar(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void MenuGameScreen::VTable0x94(undefined4)
{
}

// FUNCTION: LEGORACERS 0x00474bf0 FOLDED
MenuStyleTable* MenuGameScreen::GetMenuStyles()
{
	return &m_sharedStyles;
}

// FUNCTION: LEGORACERS 0x00474c00
MenuInputBindingTable* MenuGameScreen::GetMenuInputBindings()
{
	return &m_buttonBindings;
}

// FUNCTION: LEGORACERS 0x0047fae0
MenuGameScreen::MenuGameScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047fb80
MenuGameScreen::~MenuGameScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047fbf0
void MenuGameScreen::Reset()
{
	m_nextMenuId = 0xffff;
	m_menuId = 0;
	m_context = NULL;
	m_clickedWidget = NULL;
	m_selectedIcon = NULL;
	m_navPending = FALSE;
	MenuScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047fc20
LegoBool32 MenuGameScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	GolString string;

	m_context = p_context;
	LegoBool32 result = MenuScreen::Initialize(p_createParams);
	SetupLighting();

	return result;
}

// FUNCTION: LEGORACERS 0x0047fca0
LegoBool32 MenuGameScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	if (m_context->m_modelBuilder.HasMenuResources()) {
		m_context->m_modelBuilder.RefreshMenuResources();
	}

	m_renderer->ClearLights();
	m_renderer->ApplyLights();
	return MenuScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x0047fcf0
undefined4 MenuGameScreen::CreatePartCarousel(CarPartCarousel* p_source, undefined2 p_event, undefined2 p_styleId)
{
	MenuInputBindingTable::IconBinding* inputBindingEntry = GetIconBinding(p_event);
	MenuStyleTable::CarouselStyle* styleEntry = static_cast<MenuStyleTable::CarouselStyle*>(GetStyleEntry(p_styleId));
	if (!inputBindingEntry || !styleEntry) {
		return 0;
	}

	CarPartCarousel::CreateParams createParams;
	::memcpy(&createParams, inputBindingEntry, sizeof(createParams));
	ApplyWidgetDefaults(&createParams);

	MenuGameContext* context = m_context;
	createParams.m_partSet = &context->m_partSet;
	createParams.m_pieceLibrary = &context->m_pieceLibrary;
	createParams.m_buildModel = &context->m_carBuildModel;
	createParams.m_colorTable = &context->m_colorTable;
	createParams.m_aspectScale = GetAspectScale();
	createParams.m_viewportIndex = 5;

	return p_source->Create(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0047fdc0
undefined4 MenuGameScreen::CreateTextButton(
	MenuTextButton* p_source,
	undefined2 p_event,
	undefined2 p_styleId,
	undefined2 p_stringId
)
{
	ButtonBindingTable::ButtonBinding* sourceParams = GetButtonBinding(p_event);
	MenuStyleTable::TextButtonStyle* styleEntry = GetTextButtonStyle(p_styleId);
	if (!sourceParams || !styleEntry) {
		return 0;
	}

	MenuTextButton::CreateParams createParams;
	::memcpy(&createParams, sourceParams, sizeof(createParams));
	ApplyIconDefaults(&createParams);

	for (LegoS32 i = 0; i < 6; i++) {
		if (!createParams.m_stateImages[i]) {
			createParams.m_stateImages[i] = styleEntry->m_stateImages[i];
		}

		if (!createParams.m_stateFonts[i]) {
			createParams.m_stateFonts[i] = styleEntry->m_stateFonts[i];
		}
	}

	if (!createParams.m_hasStateColors && styleEntry->m_hasStateColors) {
		::memcpy(createParams.m_stateColors, styleEntry->m_stateColors, sizeof(createParams.m_stateColors));
	}

	createParams.m_stringTable = m_menuTextStrings;
	createParams.m_stringId = p_stringId;
	return p_source->Create(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0047fec0
void MenuGameScreen::SetLighting(const ColorRGBA* p_materialColor, const ColorRGBA* p_lightColor)
{
	GolVec3 lightDirection;
	lightDirection.m_x = -1.0f;
	lightDirection.m_y = -1.0f;
	lightDirection.m_z = -1.0f;

	m_materialColor.SetColor(*p_materialColor);
	m_light.SetColor(*p_lightColor);
	m_light.SetDirection(lightDirection);

	m_renderer->ClearLights();
	m_renderer->SetAmbient(&m_materialColor);
	m_renderer->AddLight(&m_light);
	m_renderer->ApplyLights();
}

// FUNCTION: LEGORACERS 0x0047ff50
void MenuGameScreen::LoadPieceResources(MenuGameContext* p_context, undefined4 p_binary)
{
	if (!p_context) {
		p_context = m_context;
	}

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PIECEDB");
	}

	LegoPieceLibrary* pieceLibrary = &p_context->m_pieceLibrary;
	GolExport* golExport = p_context->m_context->m_golApp->GetGolExport();
	GolD3DRenderDevice* renderer = p_context->m_context->m_golApp->GetRenderer();
	LegoColorTable* pieceResource;

	if (p_binary) {
		pieceLibrary->Load("LPieceHi.leg", p_context->m_context->m_useBinaryFiles);
		pieceResource = &p_context->m_colorTable;
		pieceResource->Initialize(golExport, renderer);
		pieceResource->LoadMaterials("LPieceHi.WDF", p_context->m_context->m_useBinaryFiles, TRUE);
	}
	else {
		pieceLibrary->Load("LPieceLo.leg", p_context->m_context->m_useBinaryFiles);
		pieceResource = &p_context->m_colorTable;
		pieceResource->Initialize(golExport, renderer);
		pieceResource->LoadMaterials("LPieceLo.WDF", p_context->m_context->m_useBinaryFiles, TRUE);
	}

	pieceResource->LoadColors("L_Colors.LEG", p_context->m_context->m_useBinaryFiles);
	p_context->m_carBuildModel.Initialize(golExport, renderer, pieceLibrary, pieceResource);
	p_context->m_carBuildModel.FindHighBasePiece();
	p_context->m_partSet.Load("crstmgr.leg", pieceLibrary, pieceResource, p_context->m_context->m_useBinaryFiles);

	ChassisModelTable::Params params;
	params.m_golExport = golExport;
	params.m_renderer = renderer;
	params.m_instantiateCount = -1;
	params.m_filename = "chassis.cmf";
	params.m_binary = p_context->m_context->m_useBinaryFiles;

	p_context->m_chassisModels.Load(&params);
	p_context->m_chassisModels.InstantiateAllModels();

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x004800c0
void MenuGameScreen::DestroyPieceResources(MenuGameContext* p_context)
{
	if (!p_context) {
		p_context = m_context;
	}

	p_context->m_partSet.Clear();
	p_context->m_carBuildModel.Destroy();
	p_context->m_colorTable.Destroy();
	p_context->m_pieceLibrary.Destroy();

	GolNameTable* chassisModels = &p_context->m_chassisModels;
	chassisModels->Clear();
}

// FUNCTION: LEGORACERS 0x00480110
void MenuGameScreen::LoadChampionResources(LegoS32 p_entryCapacity)
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PIECEDB");
	}

	Win32GolApp* golApp = m_context->m_context->m_golApp;
	GolExport* golExport = golApp->GetGolExport();
	GolD3DRenderDevice* renderer = golApp->GetRenderer();

	ChassisModelTable::Params chassisParams;
	chassisParams.m_golExport = golExport;
	chassisParams.m_renderer = renderer;
	chassisParams.m_instantiateCount = p_entryCapacity;
	chassisParams.m_filename = "chassis.cmf";
	chassisParams.m_binary = m_context->m_context->m_useBinaryFiles;
	m_context->m_chassisModels.Load(&chassisParams);

	ChampionDefinitionList::LoadParams championParams;
	championParams.m_golExport = golExport;
	championParams.m_renderer = renderer;
	championParams.m_entryCapacity = p_entryCapacity;
	championParams.m_fileName = "champs.ccf";
	championParams.m_binary = m_context->m_context->m_useBinaryFiles;
	m_context->m_championDefinitions.Load(&championParams);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x004801e0
void MenuGameScreen::DestroyChampionResources()
{
	m_context->m_championDefinitions.Clear();
	m_context->m_chassisModels.Clear();
}

// FUNCTION: LEGORACERS 0x00480210
void MenuGameScreen::LoadPartResources(MenuGameContext* p_context, undefined4 p_event)
{
	if (!p_context) {
		p_context = m_context;
	}

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PARTDB");
	}

	DriverModelBuilder::LoadParams menuResourceParams;
	DriverPartResources::LoadParams resourceParams;
	memset(&resourceParams, 0, sizeof(resourceParams));
	memset(&menuResourceParams, 0, sizeof(menuResourceParams));

	p_context->m_partCatalog.Load("bodypart.pcf", p_context->m_context->m_useBinaryFiles);
	resourceParams.m_golExport = p_context->m_context->m_golApp->GetGolExport();
	resourceParams.m_renderer = p_context->m_context->m_golApp->GetRenderer();
	resourceParams.m_partCatalog = &p_context->m_partCatalog;
	resourceParams.m_binary = p_context->m_context->m_useBinaryFiles;
	resourceParams.m_textureBinaryMode = TRUE;
	p_context->m_partResources.Load(&resourceParams, p_event);

	menuResourceParams.m_golExport = resourceParams.m_golExport;
	menuResourceParams.m_renderer = resourceParams.m_renderer;
	menuResourceParams.m_partResources = &p_context->m_partResources;
	menuResourceParams.m_menuId = 12;
	p_context->m_modelBuilder.Load(&menuResourceParams);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x00480310
void MenuGameScreen::LoadCosmeticTable()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PARTDB");
	}

	DriverCosmeticTable::LoadParams params;
	params.m_golExport = m_context->m_context->m_golApp->GetGolExport();
	params.m_renderer = m_context->m_context->m_golApp->GetRenderer();
	params.m_entryCapacity = 0;
	params.m_filename = "drivers.ddf";
	params.m_binary = m_context->m_context->m_useBinaryFiles;
	m_context->m_cosmeticTable.Load(&params);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x004803a0
void MenuGameScreen::ClearCosmeticTable()
{
	DriverCosmeticTable* cosmeticTable = &m_context->m_cosmeticTable;
	cosmeticTable->Clear();
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg prevents this trivial body from folding with identical functions elsewhere.

// FUNCTION: LEGORACERS 0x004803c0
#pragma code_seg(".text$menugamescreen_vt6c")
LegoFloat MenuGameScreen::GetAspectScale()
{
	return 1.0f;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x004803d0
void MenuGameScreen::ReinitializeInputBindings()
{
	m_context->m_inputBindings.Shutdown();
	m_inputManager->Initialize();
	m_context->m_inputBindings.Initialize(m_inputManager);
	m_context->m_saveSystem.ReinitializeInputBindings(m_inputManager);
}

// FUNCTION: LEGORACERS 0x00480420 FOLDED
LegoBool32 MenuGameScreen::CanNavigate()
{
	if (m_clickedWidget) {
		return !(m_clickedWidget->GetAnimFlags() & TRUE);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
LegoBool32 MenuGameScreen::HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_navPending;
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
LegoBool32 MenuGameScreen::HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_navPending;
}

// FUNCTION: LEGORACERS 0x00480440
LegoBool32 MenuGameScreen::IsMenuMusicPlaying(MenuGameContext* p_context)
{
	MusicInstance* musicInstance = p_context->m_modelBuilder.GetMusicInstance();
	return musicInstance && musicInstance->IsPlaying();
}

// FUNCTION: LEGORACERS 0x00480470
void MenuGameScreen::StartMenuMusic(MenuGameContext* p_context, undefined4 p_musicId, undefined4 p_looping)
{
	StopMenuMusic(p_context);

	MusicInstance* musicInstance = p_context->m_modelBuilder.GetMusicGroup()->CreateMusicInstance(p_musicId);
	p_context->m_modelBuilder.SetMusicInstance(musicInstance);

	if (!musicInstance) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	p_context->m_modelBuilder.GetMusicInstance()->Play(p_looping);
}

// FUNCTION: LEGORACERS 0x004804c0
void MenuGameScreen::StopMenuMusic(MenuGameContext* p_context)
{
	if (IsMenuMusicPlaying(p_context)) {
		p_context->m_modelBuilder.GetMusicGroup()->DestroyMusicInstance(p_context->m_modelBuilder.GetMusicInstance());
		p_context->m_modelBuilder.SetMusicInstance(NULL);
	}
}

// FUNCTION: LEGORACERS 0x00480500 FOLDED
void MenuGameScreen::OnIconFocused(MenuIcon*)
{
	m_navPending = FALSE;
}

// FUNCTION: LEGORACERS 0x00480510 FOLDED
void MenuGameScreen::OnIconSelected(MenuIcon* p_icon)
{
	m_selectedIcon = p_icon;
}

// FUNCTION: LEGORACERS 0x00480520
LegoBool32 MenuGameScreen::Update(undefined4)
{
	if (m_navPending && CanNavigate()) {
		Navigate();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00487d30
void MenuGameScreen::OnIconDeselected(MenuIcon*)
{
	m_selectedIcon = NULL;
}

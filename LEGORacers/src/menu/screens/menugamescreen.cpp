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

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void MenuGameScreen::VTable0x80()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void MenuGameScreen::VTable0x90(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void MenuGameScreen::VTable0x94(undefined4)
{
}

// FUNCTION: LEGORACERS 0x00474bf0 FOLDED
MenuStyleTable* MenuGameScreen::GetMenuStyles()
{
	return &m_unk0x290;
}

// FUNCTION: LEGORACERS 0x00474c00
MenuInputBindingTable* MenuGameScreen::GetMenuInputBindings()
{
	return &m_unk0x2e0;
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
	m_unk0x360 = 0xffff;
	m_menuId = 0;
	m_context = NULL;
	m_unk0x35c = NULL;
	m_unk0x358 = NULL;
	m_unk0x364 = FALSE;
	MenuScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047fc20
LegoBool32 MenuGameScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	GolString string;

	m_context = p_context;
	LegoBool32 result = MenuScreen::Initialize(p_createParams);
	VTable0x80();

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

	m_renderer->VTable0x28();
	m_renderer->VTable0x60();
	return MenuScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x0047fcf0
undefined4 MenuGameScreen::FUN_0047fcf0(CarPartCarousel* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuInputBindingTable::IconBinding* inputBindingEntry = GetIconBinding(p_unk0x08);
	MenuStyleTable::CarouselStyle* styleEntry = static_cast<MenuStyleTable::CarouselStyle*>(GetStyleEntry(p_unk0x0c));
	if (!inputBindingEntry || !styleEntry) {
		return 0;
	}

	CarPartCarousel::CreateParams createParams;
	::memcpy(&createParams, inputBindingEntry, sizeof(createParams));
	ApplyWidgetDefaults(&createParams);

	MenuGameContext* context = m_context;
	createParams.m_partSet = &context->m_unk0x21a4;
	createParams.m_pieceLibrary = &context->m_pieceLibrary;
	createParams.m_buildModel = &context->m_unk0x21f4;
	createParams.m_colorTable = &context->m_unk0x4224;
	createParams.m_unk0x70 = VTable0x6c();
	createParams.m_unk0x6c = 5;

	return p_unk0x04->Create(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0047fdc0
undefined4 MenuGameScreen::FUN_0047fdc0(
	MenuTextButton* p_unk0x04,
	undefined2 p_unk0x08,
	undefined2 p_unk0x0c,
	undefined2 p_unk0x10
)
{
	ButtonBindingTable::ButtonBinding* sourceParams = GetButtonBinding(p_unk0x08);
	MenuStyleTable::TextButtonStyle* styleEntry = GetTextButtonStyle(p_unk0x0c);
	if (!sourceParams || !styleEntry) {
		return 0;
	}

	MenuTextButton::CreateParams createParams;
	::memcpy(&createParams, sourceParams, sizeof(createParams));
	ApplyIconDefaults(&createParams);

	for (LegoS32 i = 0; i < 6; i++) {
		if (!createParams.m_unk0x9c[i]) {
			createParams.m_unk0x9c[i] = styleEntry->m_unk0xa8[i];
		}

		if (!createParams.m_unk0x84[i]) {
			createParams.m_unk0x84[i] = styleEntry->m_unk0x90[i];
		}
	}

	if (!createParams.m_unk0x78 && styleEntry->m_unk0x88) {
		::memcpy(createParams.m_unk0xb4, styleEntry->m_unk0xc0, sizeof(createParams.m_unk0xb4));
	}

	createParams.m_unk0xcc = m_menuTextStrings;
	createParams.m_unk0xd4 = p_unk0x10;
	return p_unk0x04->FUN_004826c0(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0047fec0
void MenuGameScreen::FUN_0047fec0(const ColorRGBA* p_materialColor, const ColorRGBA* p_lightColor)
{
	GolVec3 lightDirection;
	lightDirection.m_x = -1.0f;
	lightDirection.m_y = -1.0f;
	lightDirection.m_z = -1.0f;

	m_unk0x350.SetColor(*p_materialColor);
	m_unk0x340.SetColor(*p_lightColor);
	m_unk0x340.SetDirection(lightDirection);

	m_renderer->VTable0x28();
	m_renderer->VTable0x2c(&m_unk0x350);
	m_renderer->VTable0x30(&m_unk0x340);
	m_renderer->VTable0x60();
}

// FUNCTION: LEGORACERS 0x0047ff50
void MenuGameScreen::FUN_0047ff50(MenuGameContext* p_context, undefined4 p_binary)
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
		pieceLibrary->FUN_0049ee30("LPieceHi.leg", p_context->m_context->m_unk0x18);
		pieceResource = &p_context->m_unk0x4224;
		pieceResource->Initialize(golExport, renderer);
		pieceResource->LoadMaterials("LPieceHi.WDF", p_context->m_context->m_unk0x18, TRUE);
	}
	else {
		pieceLibrary->FUN_0049ee30("LPieceLo.leg", p_context->m_context->m_unk0x18);
		pieceResource = &p_context->m_unk0x4224;
		pieceResource->Initialize(golExport, renderer);
		pieceResource->LoadMaterials("LPieceLo.WDF", p_context->m_context->m_unk0x18, TRUE);
	}

	pieceResource->LoadColors("L_Colors.LEG", p_context->m_context->m_unk0x18);
	p_context->m_unk0x21f4.Initialize(golExport, renderer, pieceLibrary, pieceResource);
	p_context->m_unk0x21f4.FindHighBasePiece();
	p_context->m_unk0x21a4.Load("crstmgr.leg", pieceLibrary, pieceResource, p_context->m_context->m_unk0x18);

	ChassisModelTable::Params params;
	params.m_golExport = golExport;
	params.m_renderer = renderer;
	params.m_instantiateCount = -1;
	params.m_filename = "chassis.cmf";
	params.m_binary = p_context->m_context->m_unk0x18;

	p_context->m_chassisModels.FUN_0041db10(&params);
	p_context->m_chassisModels.InstantiateAllModels();

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x004800c0
void MenuGameScreen::FUN_004800c0(MenuGameContext* p_context)
{
	if (!p_context) {
		p_context = m_context;
	}

	p_context->m_unk0x21a4.Clear();
	p_context->m_unk0x21f4.Destroy();
	p_context->m_unk0x4224.Destroy();
	p_context->m_pieceLibrary.Destroy();

	GolNameTable* chassisModels = &p_context->m_chassisModels;
	chassisModels->Clear();
}

// FUNCTION: LEGORACERS 0x00480110
void MenuGameScreen::FUN_00480110(LegoS32 p_entryCapacity)
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
	chassisParams.m_binary = m_context->m_context->m_unk0x18;
	m_context->m_chassisModels.FUN_0041db10(&chassisParams);

	ChampionDefinitionList::LoadParams championParams;
	championParams.m_golExport = golExport;
	championParams.m_renderer = renderer;
	championParams.m_entryCapacity = p_entryCapacity;
	championParams.m_fileName = "champs.ccf";
	championParams.m_binary = m_context->m_context->m_unk0x18;
	m_context->m_championDefinitions.FUN_0041d370(&championParams);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x004801e0
void MenuGameScreen::FUN_004801e0()
{
	m_context->m_championDefinitions.Clear();
	m_context->m_chassisModels.Clear();
}

// FUNCTION: LEGORACERS 0x00480210
void MenuGameScreen::FUN_00480210(MenuGameContext* p_context, undefined4 p_unk0x08)
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

	p_context->m_partCatalog.Load("bodypart.pcf", p_context->m_context->m_unk0x18);
	resourceParams.m_golExport = p_context->m_context->m_golApp->GetGolExport();
	resourceParams.m_renderer = p_context->m_context->m_golApp->GetRenderer();
	resourceParams.m_partCatalog = &p_context->m_partCatalog;
	resourceParams.m_binary = p_context->m_context->m_unk0x18;
	resourceParams.m_textureBinaryMode = TRUE;
	p_context->m_partResources.Load(&resourceParams, p_unk0x08);

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
void MenuGameScreen::FUN_00480310()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PARTDB");
	}

	DriverCosmeticTable::LoadParams params;
	params.m_golExport = m_context->m_context->m_golApp->GetGolExport();
	params.m_renderer = m_context->m_context->m_golApp->GetRenderer();
	params.m_entryCapacity = 0;
	params.m_filename = "drivers.ddf";
	params.m_binary = m_context->m_context->m_unk0x18;
	m_context->m_cosmeticTable.Load(&params);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x004803a0
void MenuGameScreen::FUN_004803a0()
{
	DriverCosmeticTable* cosmeticTable = &m_context->m_cosmeticTable;
	cosmeticTable->Clear();
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg prevents this trivial body from folding with identical functions elsewhere.

// FUNCTION: LEGORACERS 0x004803c0
#pragma code_seg(".text$imaginarytool_vt6c")
LegoFloat MenuGameScreen::VTable0x6c()
{
	return 1.0f;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x004803d0
void MenuGameScreen::FUN_004803d0()
{
	m_context->m_inputBindings.Shutdown();
	m_inputManager->Initialize();
	m_context->m_inputBindings.Initialize(m_inputManager);
	m_context->m_saveSystem.ReinitializeInputBindings(m_inputManager);
}

// FUNCTION: LEGORACERS 0x00480420 FOLDED
LegoBool32 MenuGameScreen::VTable0x88()
{
	if (m_unk0x35c) {
		return !(m_unk0x35c->GetUnk0x54() & TRUE);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
LegoBool32 MenuGameScreen::VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_unk0x364;
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
LegoBool32 MenuGameScreen::VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_unk0x364;
}

// FUNCTION: LEGORACERS 0x00480440
LegoBool32 MenuGameScreen::FUN_00480440(MenuGameContext* p_context)
{
	MusicInstance* musicInstance = p_context->m_modelBuilder.GetMusicInstance();
	return musicInstance && musicInstance->IsPlaying();
}

// FUNCTION: LEGORACERS 0x00480470
void MenuGameScreen::FUN_00480470(MenuGameContext* p_context, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	FUN_004804c0(p_context);

	MusicInstance* musicInstance = p_context->m_modelBuilder.GetMusicGroup()->CreateMusicInstance(p_unk0x08);
	p_context->m_modelBuilder.SetMusicInstance(musicInstance);

	if (!musicInstance) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	p_context->m_modelBuilder.GetMusicInstance()->Play(p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x004804c0
void MenuGameScreen::FUN_004804c0(MenuGameContext* p_context)
{
	if (FUN_00480440(p_context)) {
		p_context->m_modelBuilder.GetMusicGroup()->DestroyMusicInstance(p_context->m_modelBuilder.GetMusicInstance());
		p_context->m_modelBuilder.SetMusicInstance(NULL);
	}
}

// FUNCTION: LEGORACERS 0x00480500 FOLDED
void MenuGameScreen::VTable0x34(MenuIcon*)
{
	m_unk0x364 = FALSE;
}

// FUNCTION: LEGORACERS 0x00480510 FOLDED
void MenuGameScreen::VTable0x3c(MenuIcon* p_unk0x04)
{
	m_unk0x358 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00480520
LegoBool32 MenuGameScreen::VTable0x78(undefined4)
{
	if (m_unk0x364 && VTable0x88()) {
		VTable0x84();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00487d30
void MenuGameScreen::VTable0x40(MenuIcon*)
{
	m_unk0x358 = NULL;
}

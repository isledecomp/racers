#include "menu/screens/imaginarytool0x368.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golstring.h"
#include "input/inputmanager.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "racer/siennacircuit0x154.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryTool0x368, 0x368)
DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x2e0::Entry0xe0, 0xe0)
DECOMP_SIZE_ASSERT(SiennaCircuit0x154, 0x154)
DECOMP_SIZE_ASSERT(SiennaCircuit0x154::CreateParams0x84, 0x84)

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void ImaginaryTool0x368::VTable0x80()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void ImaginaryTool0x368::VTable0x90(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void ImaginaryTool0x368::VTable0x94(undefined4)
{
}

// FUNCTION: LEGORACERS 0x00474bf0 FOLDED
CeruleanEmperor0x4c* ImaginaryTool0x368::GetMenuStyles()
{
	return &m_unk0x290;
}

// FUNCTION: LEGORACERS 0x00474c00
MenuInputBindingTable* ImaginaryTool0x368::GetMenuInputBindings()
{
	return &m_unk0x2e0;
}

// FUNCTION: LEGORACERS 0x0047fae0
ImaginaryTool0x368::ImaginaryTool0x368()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047fb80
ImaginaryTool0x368::~ImaginaryTool0x368()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047fbf0
void ImaginaryTool0x368::Reset()
{
	m_unk0x360 = 0xffff;
	m_menuId = 0;
	m_context = NULL;
	m_unk0x35c = NULL;
	m_unk0x358 = NULL;
	m_unk0x364 = FALSE;
	ImaginaryNotion0x290::Reset();
}

// FUNCTION: LEGORACERS 0x0047fc20
LegoBool32 ImaginaryTool0x368::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	GolString string;

	m_context = p_context;
	LegoBool32 result = ImaginaryNotion0x290::Initialize(p_createParams);
	VTable0x80();

	return result;
}

// FUNCTION: LEGORACERS 0x0047fca0
LegoBool32 ImaginaryTool0x368::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	if (m_context->m_unk0x4b40.HasMenuResources()) {
		m_context->m_unk0x4b40.RefreshMenuResources();
	}

	m_renderer->VTable0x28();
	m_renderer->VTable0x60();
	return ImaginaryNotion0x290::Destroy();
}

// FUNCTION: LEGORACERS 0x0047fcf0
undefined4 ImaginaryTool0x368::FUN_0047fcf0(SiennaCircuit0x154* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuInputBindingTable::Entry0x84* inputBindingEntry = GetInputBindingEntry0x84(p_unk0x08);
	CeruleanEmperor0x4c::Entry0x18* styleEntry = static_cast<CeruleanEmperor0x4c::Entry0x18*>(FUN_0046bd80(p_unk0x0c));
	if (!inputBindingEntry || !styleEntry) {
		return 0;
	}

	SiennaCircuit0x154::CreateParams0x84 createParams;
	::memcpy(&createParams, inputBindingEntry, sizeof(createParams));
	FUN_0046ba60(&createParams);

	MenuToolContext0x4bc8* context = m_context;
	createParams.m_unk0x74 = &context->m_unk0x21a4;
	createParams.m_pieceLibrary = &context->m_pieceLibrary;
	createParams.m_unk0x7c = &context->m_unk0x21f4;
	createParams.m_unk0x80 = &context->m_unk0x4224;
	createParams.m_unk0x70 = VTable0x6c();
	createParams.m_unk0x6c = 5;

	return p_unk0x04->FUN_00485300(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0047fdc0
undefined4 ImaginaryTool0x368::FUN_0047fdc0(
	MainMenuScreenFieldAt0x498* p_unk0x04,
	undefined2 p_unk0x08,
	undefined2 p_unk0x0c,
	undefined2 p_unk0x10
)
{
	FieldAt0x2e0::Entry0xe0* sourceParams = GetToolInputBindingEntry0xe0(p_unk0x08);
	CeruleanEmperor0x4c::Entry0x104* styleEntry = GetStyleEntry0x104(p_unk0x0c);
	if (!sourceParams || !styleEntry) {
		return 0;
	}

	MainMenuScreenFieldAt0x498::CreateParams0xe0 createParams;
	::memcpy(&createParams, sourceParams, sizeof(createParams));
	FUN_0046bb10(&createParams);

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
void ImaginaryTool0x368::FUN_0047fec0(
	GolRenderDevice::MaterialColor* p_materialColor,
	GolRenderDevice::Light* p_lightColor
)
{
	GolVec3 lightDirection;
	lightDirection.m_x = -1.0f;
	lightDirection.m_y = -1.0f;
	lightDirection.m_z = -1.0f;

	m_unk0x350.SetColor(p_materialColor->GetColor());
	m_unk0x340.SetColor(p_lightColor->GetColor());
	m_unk0x340.SetDirection(lightDirection);

	m_renderer->VTable0x28();
	m_renderer->VTable0x2c(&m_unk0x350);
	m_renderer->VTable0x30(&m_unk0x340);
	m_renderer->VTable0x60();
}

// FUNCTION: LEGORACERS 0x0047ff50
void ImaginaryTool0x368::FUN_0047ff50(MenuToolContext0x4bc8* p_context, undefined4 p_binary)
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
	VerdantTide0x38* pieceResource;

	if (p_binary) {
		pieceLibrary->FUN_0049ee30("LPieceHi.leg", p_context->m_context->m_unk0x18);
		pieceResource = &p_context->m_unk0x4224;
		pieceResource->FUN_004978f0(golExport, renderer);
		pieceResource->FUN_00497c30("LPieceHi.WDF", p_context->m_context->m_unk0x18, TRUE);
	}
	else {
		pieceLibrary->FUN_0049ee30("LPieceLo.leg", p_context->m_context->m_unk0x18);
		pieceResource = &p_context->m_unk0x4224;
		pieceResource->FUN_004978f0(golExport, renderer);
		pieceResource->FUN_00497c30("LPieceLo.WDF", p_context->m_context->m_unk0x18, TRUE);
	}

	pieceResource->FUN_00497a10("L_Colors.LEG", p_context->m_context->m_unk0x18);
	p_context->m_unk0x21f4.FUN_00499fc0(golExport, renderer, pieceLibrary, pieceResource);
	p_context->m_unk0x21f4.FUN_0049ad00();
	p_context->m_unk0x21a4.FUN_0049ce80("crstmgr.leg", pieceLibrary, pieceResource, p_context->m_context->m_unk0x18);

	AquamarineSpirit0x3c::Params params;
	params.m_unk0x00 = golExport;
	params.m_unk0x04 = renderer;
	params.m_unk0x08 = -1;
	params.m_filename = "chassis.cmf";
	params.m_unk0x10 = p_context->m_context->m_unk0x18;

	p_context->m_unk0x42dc.FUN_0041db10(&params);
	p_context->m_unk0x42dc.FUN_0041e570();

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x00480210
void ImaginaryTool0x368::FUN_00480210(MenuToolContext0x4bc8* p_context, undefined4 p_unk0x08)
{
	if (!p_context) {
		p_context = m_context;
	}

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PARTDB");
	}

	TanzaniteWisp0x88::LoadParams menuResourceParams;
	GarnetFlare0x60::LoadParams resourceParams;
	memset(&resourceParams, 0, sizeof(resourceParams));
	memset(&menuResourceParams, 0, sizeof(menuResourceParams));

	p_context->m_unk0x437c.Load("bodypart.pcf", p_context->m_context->m_unk0x18);
	resourceParams.m_golExport = p_context->m_context->m_golApp->GetGolExport();
	resourceParams.m_renderer = p_context->m_context->m_golApp->GetRenderer();
	resourceParams.m_unk0x0c = &p_context->m_unk0x437c;
	resourceParams.m_binary = p_context->m_context->m_unk0x18;
	resourceParams.m_unk0x14 = TRUE;
	p_context->m_unk0x4ae0.FUN_00497f10(&resourceParams, p_unk0x08);

	menuResourceParams.m_golExport = resourceParams.m_golExport;
	menuResourceParams.m_renderer = resourceParams.m_renderer;
	menuResourceParams.m_unk0x0c = &p_context->m_unk0x4ae0;
	menuResourceParams.m_menuId = 12;
	p_context->m_unk0x4b40.FUN_0049d1d0(&menuResourceParams);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x00480310
void ImaginaryTool0x368::FUN_00480310()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PARTDB");
	}

	DriverCosmeticTable::LoadParams params;
	params.m_golExport = m_context->m_context->m_golApp->GetGolExport();
	params.m_renderer = m_context->m_context->m_golApp->GetRenderer();
	params.m_unk0x08 = 0;
	params.m_filename = "drivers.ddf";
	params.m_unk0x10 = m_context->m_context->m_unk0x18;
	m_context->m_unk0x425c.Load(&params);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x004803a0
void ImaginaryTool0x368::FUN_004803a0()
{
	DriverCosmeticTable* drivers = &m_context->m_unk0x425c;
	drivers->Clear();
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg prevents this trivial body from folding with identical functions elsewhere.

// FUNCTION: LEGORACERS 0x004803c0
#pragma code_seg(".text$imaginarytool_vt6c")
LegoFloat ImaginaryTool0x368::VTable0x6c()
{
	return 1.0f;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x004803d0
void ImaginaryTool0x368::FUN_004803d0()
{
	m_context->m_inputBindings.Shutdown();
	m_inputManager->Initialize();
	m_context->m_inputBindings.Initialize(m_inputManager);
	m_context->m_unk0x258.FUN_004437a0(m_inputManager);
}

// FUNCTION: LEGORACERS 0x00480420 FOLDED
LegoBool32 ImaginaryTool0x368::VTable0x88()
{
	if (m_unk0x35c) {
		return !(m_unk0x35c->GetUnk0x54() & TRUE);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
undefined4 ImaginaryTool0x368::VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_unk0x364;
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
undefined4 ImaginaryTool0x368::VTable0x1c(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_unk0x364;
}

// FUNCTION: LEGORACERS 0x00480440
LegoBool32 ImaginaryTool0x368::FUN_00480440(MenuToolContext0x4bc8* p_context)
{
	MusicInstance* musicInstance = p_context->m_unk0x4b40.GetMusicInstance();
	return musicInstance && musicInstance->IsPlaying();
}

// FUNCTION: LEGORACERS 0x00480470
void ImaginaryTool0x368::FUN_00480470(MenuToolContext0x4bc8* p_context, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	FUN_004804c0(p_context);

	MusicInstance* musicInstance = p_context->m_unk0x4b40.GetMusicGroup()->CreateMusicInstance(p_unk0x08);
	p_context->m_unk0x4b40.SetMusicInstance(musicInstance);

	if (!musicInstance) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	p_context->m_unk0x4b40.GetMusicInstance()->Play(p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x004804c0
void ImaginaryTool0x368::FUN_004804c0(MenuToolContext0x4bc8* p_context)
{
	if (FUN_00480440(p_context)) {
		p_context->m_unk0x4b40.GetMusicGroup()->DestroyMusicInstance(p_context->m_unk0x4b40.GetMusicInstance());
		p_context->m_unk0x4b40.SetMusicInstance(NULL);
	}
}

// FUNCTION: LEGORACERS 0x00480500 FOLDED
void ImaginaryTool0x368::VTable0x34(ObscureIcon0x1a8*)
{
	m_unk0x364 = FALSE;
}

// FUNCTION: LEGORACERS 0x00480510 FOLDED
void ImaginaryTool0x368::VTable0x3c(ObscureIcon0x1a8* p_unk0x04)
{
	m_unk0x358 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00480520
LegoBool32 ImaginaryTool0x368::VTable0x78(undefined4)
{
	if (m_unk0x364 && VTable0x88()) {
		VTable0x84();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00487d30
void ImaginaryTool0x368::VTable0x40(ObscureIcon0x1a8*)
{
	m_unk0x358 = NULL;
}

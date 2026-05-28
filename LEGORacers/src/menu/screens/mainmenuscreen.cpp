#include "menu/screens/mainmenuscreen.h"

#include "audio/soundgroupbinding.h"
#include "golhashtable.h"
#include "golstream.h"
#include "input/inputmanager.h"
#include "menu/crimsonsun0xa4.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"
#include "model/sapphirereef0x2030.h"
#include "racer/drivercosmetictable.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MainMenuScreen, 0x2450)

// GLOBAL: LEGORACERS 0x004c214c
static LegoU8 g_unk0x004c214c[] = {0x13, 0x12, 0x16, 0x15, 0x14, 0x17, 0, 0};

// FUNCTION: LEGORACERS 0x0047ff50
void MainMenuScreen::FUN_0047ff50(MenuToolContext0x4bc8* p_context, undefined4 p_binary)
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
void MainMenuScreen::FUN_00480210(MenuToolContext0x4bc8* p_context, undefined4 p_unk0x08)
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
void MainMenuScreen::FUN_00480310()
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
void MainMenuScreen::FUN_004803a0()
{
	DriverCosmeticTable* drivers = &m_context->m_unk0x425c;
	drivers->Clear();
}

// FUNCTION: LEGORACERS 0x00480b70
MainMenuScreen::MainMenuScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00480cd0
MainMenuScreen::~MainMenuScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00480e10
void MainMenuScreen::Reset()
{
	m_unk0x2444 = 60000;
	m_unk0x2448 = 30000;
	m_unk0x244c = 0;
	m_unk0x2438 = NULL;
	ImaginaryTool0x368::Reset();
}

// FUNCTION: LEGORACERS 0x00480e40
void MainMenuScreen::FUN_00480e40()
{
	MainMenuScreenFieldAt0x22dc::CreateParams params;
	GolVec3 vector0;
	GolVec3 vector1;
	GolD3DRenderDevice* renderer;

	FUN_0046c480(&m_unk0x21f8, 0, 0xd0);

	renderer = m_renderer;
	::memset(&params, 0, sizeof(params));
	params.m_golExport = m_golExport;
	params.m_unk0x0c = &m_context->m_unk0x4b40;
	params.m_unk0x08 = &m_unk0x21f8;
	params.m_renderer = renderer;
	params.m_position.m_x = 18.18122864f;
	params.m_position.m_y = -10.62275887f;
	params.m_position.m_z = 0.025708f;
	m_unk0x22dc.FUN_0047e0a0(&params);
	m_unk0x21f8.FUN_00465b40(&m_unk0x22dc);

	vector1.m_x = 0.97237003f;
	vector1.m_y = -0.233445f;
	vector1.m_z = 0.0f;
	vector0.m_x = 0.0f;
	vector0.m_y = 0.0f;
	vector0.m_z = 1.0f;

	m_unk0x2438 = m_unk0x22dc.GetUnk0x1c();
	m_unk0x2438->VTable0x40(vector1, vector0);
}

// FUNCTION: LEGORACERS 0x00480f20
void MainMenuScreen::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x368, 0x49, 0x49);
	FUN_0046bef0(&m_unk0x3c4, 0x52, 0x52);
	FUN_00480e40();
	FUN_0047fdc0(&m_unk0x1058, 3, 0x42, 0x25);
	FUN_0047fdc0(&m_unk0x788, 0x55, 0x42, 0x21);
	FUN_0047fdc0(&m_unk0x498, 0x56, 0x42, 0x22);
	FUN_0047fdc0(&m_unk0xa78, 0x57, 0x42, 0x23);
	FUN_0047fdc0(&m_unk0xd68, 0x58, 0x42, 0x24);
	FUN_0047fdc0(&m_unk0x1348, 8, 0x42, 0x26);
	FUN_0047fdc0(&m_unk0x1638, 0x59, 0x42, 0x27);

	if (!m_inputManager->GetJoystickCount()) {
		m_unk0xa78.VTable0x48(5);
	}
}

// FUNCTION: LEGORACERS 0x00481000
LegoBool32 MainMenuScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (!p_context->m_unk0x4b40.HasMenuResources()) {
		FUN_00480210(p_context, 0);
	}

	if (!p_context->m_unk0x21f4.FUN_0049a0e0()) {
		FUN_0047ff50(p_context, TRUE);
	}

	if (!ImaginaryTool0x368::FUN_00480440(p_context)) {
		FUN_00480470(p_context, 0, TRUE);
	}

	if (!ImaginaryTool0x368::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	FUN_00480310();
	LegoU32 index = p_context->m_unk0x258.FUN_00443760();
	TurquoiseGlowColor color;
	p_context->m_unk0x425c.FUN_00421050(g_unk0x004c214c[index], &color);
	m_unk0x22dc.FUN_0047e210(&color);
	m_unk0x22dc.GetUnk0x118()->VTable0x14("legoman", p_context->m_context->m_unk0x18);
	m_unk0x2438->FUN_0040dad0(0);
	m_unk0x2438->SetFlags(m_unk0x2438->GetFlags() | 0x10000);
	m_unk0x2438->SetFlags(m_unk0x2438->GetFlags() & ~0x40000);
	p_context->m_unk0x258.GetUnk0x1cfc().Reset();
	m_unk0x1058.VTable0x4c(5);
	m_cursorHelper->SetCursorEnabled(TRUE);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00481120
LegoBool32 MainMenuScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	FUN_004803a0();
	return ImaginaryTool0x368::Destroy();
}

// FUNCTION: LEGORACERS 0x00481150
void MainMenuScreen::VTable0x38(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x788) {
		m_unk0x360 = 5;
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() & ~2);
	}
	else if (p_unk0x04 == &m_unk0x498) {
		m_unk0x360 = 6;
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() & ~2);
	}
	else if (p_unk0x04 == &m_unk0xa78) {
		m_unk0x360 = 6;
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() | 2);
	}
	else if (p_unk0x04 == &m_unk0xd68) {
		m_unk0x360 = 0x1d;
	}
	else if (p_unk0x04 == &m_unk0x1058) {
		m_unk0x360 = 3;
		ImaginaryTool0x368::FUN_004804c0(m_context);
	}
	else if (p_unk0x04 == &m_unk0x1348) {
		m_unk0x360 = 8;
	}
	else if (p_unk0x04 == &m_unk0x1638) {
		FUN_0047fdc0(&m_unk0x1928, 0x99, 0x46, 0x73);
		FUN_0047fdc0(&m_unk0x1c18, 0x99, 0x45, 0x74);
		FUN_0046c6f0(&m_unk0x1928, &m_unk0x1c18, 0x75);
	}
	else if (p_unk0x04 == &m_unk0x1928) {
		m_unk0x284->FUN_00468cf0();
		m_unk0x360 = 0;
	}
	else if (p_unk0x04 == &m_unk0x1c18 || p_unk0x04 == &m_unk0x1f08) {
		m_unk0x284->FUN_00468cf0();
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x35c = p_unk0x04;
		m_unk0x364 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x004812c0
void MainMenuScreen::VTable0x84()
{
	if (m_unk0x360 && m_unk0x360 != 0xffff) {
		m_context->m_menuStack.Push(m_unk0x360);
		return;
	}

	m_context->m_menuStack.ResetSize();
}

// STUB: LEGORACERS 0x004812f0
undefined4 MainMenuScreen::VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	undefined4 result = TRUE;

	if (!m_unk0x364) {
		result = FALSE;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00481310
undefined4 MainMenuScreen::VTable0x1c(
	ObscureVantage0x58* p_icon,
	InputEventQueue::Event* p_item,
	undefined4,
	undefined4
)
{
	if (m_unk0x364) {
		return TRUE;
	}

	if (p_icon == &m_unk0xd8) {
		switch (p_item->m_keyCode) {
		case 0x1000001d:
		case 0x1000009d:
			m_unk0x244c &= ~1;
			return FALSE;
		case 0x1000002a:
		case 0x10000036:
			m_unk0x244c &= ~2;
			return FALSE;
		case 0x10000014:
			m_unk0x244c &= ~4;
			return FALSE;
		case 0x1000002e:
			m_unk0x244c &= ~8;
			return FALSE;
		case 0x1000002f:
			m_unk0x244c &= ~0x10;
			return FALSE;
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00481450
LegoBool32 MainMenuScreen::VTable0x78(undefined4 p_elapsed)
{
	if (p_elapsed > m_unk0x2448) {
		m_unk0x2448 = 0;
	}
	else {
		m_unk0x2448 -= p_elapsed;
	}

	if (p_elapsed > m_unk0x2444) {
		m_unk0x2444 = 0;
	}
	else {
		m_unk0x2444 -= p_elapsed;
	}

	LegoU16 state = m_unk0x2438->GetActiveState();
	if (state == 2) {
		if (m_unk0x2438->GetActiveValue() < 208.0f) {
			m_unk0x243c = FALSE;
		}
		else {
			if (!m_unk0x243c) {
				m_soundGroupBinding->FUN_0046e970(0x1d);
				m_unk0x243c = TRUE;
			}
		}
	}

	if (m_context->m_unk0x4b40.GetUnk0x78() & 4) {
		FUN_0047fdc0(&m_unk0x1f08, 0x99, 0x46, 0x72);
		FUN_0046c730(&m_unk0x1f08, 0x7c);
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() & ~4);
	}

	if (!m_unk0x2448) {
		m_unk0x2438->FUN_0040db80(2, 200, 0.0f, 0, 0, 0);
		m_unk0x2438->SetFlags(m_unk0x2438->GetFlags() | 0x10000);
		m_unk0x2448 = 30000;
	}
	else if (m_unk0x2438->FUN_0040e360()) {
		m_unk0x2438->FUN_0040db80(1, 200, 0.0f, 0, 0, 1);
		m_unk0x2438->SetFlags(m_unk0x2438->GetFlags() | 0x10000);
	}

	if (!m_unk0x2444) {
		m_unk0x364 = TRUE;
	}

	LegoBool32 result = ImaginaryTool0x368::VTable0x78(p_elapsed);
	if (!m_unk0x360) {
		return TRUE;
	}

	return result;
}

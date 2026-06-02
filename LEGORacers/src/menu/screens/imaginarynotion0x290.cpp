#include "menu/screens/imaginarynotion0x290.h"

#include "core/gol.h"
#include "font/golfonttable.h"
#include "golerror.h"
#include "golname.h"
#include "golstream.h"
#include "golstring.h"
#include "golstringtable.h"
#include "input/inputmanager.h"
#include "material/awakekite0x20.h"
#include "menu/crimsonsun0xa4.h"
#include "menu/menutoolcreateparams0x30.h"
#include "menu/screens/imaginarychisel0x658.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/widgets/ivorytalon0x23c.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"
#include "menu/widgets/obscureglyph0x21c.h"
#include "menu/widgets/obscurelattice0x228.h"
#include "menu/widgets/obscurerune0x4d8.h"
#include "menu/widgets/obscuresigil0xdc.h"
#include "menu/widgets/obscuretome0x3fc.h"
#include "menu/widgets/obscurevantage0x58.h"
#include "menu/widgets/obscurezebra0xa4.h"
#include "menu/widgets/optionsscreenfieldat0x4178.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "render/goldrawstate.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryNotion0x290, 0x290)
DECOMP_SIZE_ASSERT(ImaginaryNotion0x290::FieldAt0x54, 0x54)

// GLOBAL: LEGORACERS 0x004b2240
const undefined4 g_unk0x4b2240[14] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};

// GLOBAL: LEGORACERS 0x004b2278
const ObscureIcon0x1a8::CreateState0x90 g_unk0x4b2278 = {{0}};

// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
undefined4 ImaginaryNotion0x290::VTable0x50()
{
	return 1;
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x00(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x04(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x08(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x0c(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x10(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x20(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x24(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x2c(ObscureIcon0x1a8*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x30(ObscureIcon0x1a8*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x34(ObscureIcon0x1a8*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x38(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x3c(ObscureIcon0x1a8*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x40(ObscureIcon0x1a8*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x44(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x48(ObscureVantage0x58*)
{
	// TODO
	STUB(0x0044f590);
}

// FUNCTION: LEGORACERS 0x0046b380
ImaginaryNotion0x290::ImaginaryNotion0x290()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046b410
ImaginaryNotion0x290::~ImaginaryNotion0x290()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046b480
void ImaginaryNotion0x290::Reset()
{
	m_menuTextStrings = NULL;
	m_menuNameStrings = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_unk0xbc = NULL;
	m_fontTable = NULL;
	m_soundGroupBinding = NULL;
	m_inputManager = NULL;
	m_unk0x284 = NULL;
	m_cursorHelper = NULL;
	m_menuStyles = NULL;
	m_unk0x28c = 0;
	m_unk0x08.Clear();
	m_unk0x58.Clear();
	m_unk0xd8.VTable0x08();
	m_initialized = FALSE;
}

// FUNCTION: LEGORACERS 0x0046b500
LegoBool32 ImaginaryNotion0x290::Initialize(MenuToolCreateParams0x30* p_createParams)
{
	m_golExport = p_createParams->m_golExport;
	m_renderer = p_createParams->m_renderer;
	m_soundGroupBinding = p_createParams->m_soundGroupBinding;
	m_inputManager = p_createParams->m_inputManager;
	m_unk0x288 = p_createParams->m_unk0x2c;
	m_unk0x284 = p_createParams->m_unk0x20;
	m_cursorHelper = p_createParams->m_cursorHelper;
	m_unk0x28c = p_createParams->m_menuId;
	m_menuStyles = p_createParams->m_menuStyles;
	m_inputEvents = p_createParams->m_inputEvents;
	m_menuTextStrings = p_createParams->m_menuTextStrings;
	m_menuNameStrings = p_createParams->m_menuNameStrings;

	if (FUN_0046b630() && FUN_0046b6e0(p_createParams) && VTable0x58(p_createParams)) {
		VTable0x4c();
		m_inputManager->PollDevices(0);
		m_inputEvents->ClearQueue();
		m_initialized = TRUE;
	}

	return m_initialized;
}

// FUNCTION: LEGORACERS 0x0046b5d0
LegoBool32 ImaginaryNotion0x290::Destroy()
{
	if (m_initialized) {
		if (m_unk0xbc) {
			m_unk0xbc->Clear();
			m_golExport->VTable0x68(m_unk0xbc);
		}

		if (m_fontTable) {
			m_fontTable->Clear();
			m_golExport->DestroyFontTable(m_fontTable);
		}

		Reset();
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046b630
LegoBool32 ImaginaryNotion0x290::FUN_0046b630()
{
	GolCommonDrawState* drawState = m_renderer->GetDrawState();
	ObscureIcon0x1a8::CreateParams0x84 createParams;

	memset(&createParams, 0, sizeof(createParams));
	memcpy(&createParams, g_unk0x4b2240, sizeof(g_unk0x4b2240));

	createParams.m_golExport = m_golExport;
	createParams.m_renderer = m_renderer;
	createParams.m_unk0x38 = TRUE;
	createParams.m_soundGroupBinding = m_soundGroupBinding;
	createParams.m_rect.m_right = drawState->m_width;
	createParams.m_rect.m_bottom = drawState->m_height;
	createParams.m_eventHandler = this;

	if (m_unk0xd8.FUN_00471e30(&createParams, &g_unk0x4b2278)) {
		m_unk0xd8.VTable0x4c(0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046b6e0
LegoBool32 ImaginaryNotion0x290::FUN_0046b6e0(MenuToolCreateParams0x30* p_createParams)
{
	GolString string;

	if (!VTable0x50()) {
		return TRUE;
	}

	m_menuNameStrings->CopyStringByIndex(&string, m_unk0x28c);

	LegoChar fileName[16];
	string.CopyToString(fileName);

	const LegoChar* idSuffix = ".idb";
	if (!p_createParams->m_unk0x2c) {
		idSuffix = ".idf";
	}
	strcat(fileName, idSuffix);

	if (!GolStream::FindFile(fileName)) {
		m_unk0xbc = m_golExport->VTable0x34();
		m_unk0xbc->LoadImageDefinitions(m_renderer, fileName, p_createParams->m_unk0x2c);
	}

	string.CopyToString(fileName);

	const LegoChar* fontSuffix = ".fdb";
	if (!p_createParams->m_unk0x2c) {
		fontSuffix = ".fdf";
	}
	strcat(fileName, fontSuffix);

	if (!GolStream::FindFile(fileName)) {
		m_fontTable = m_golExport->CreateFontTable();
		m_fontTable->VTable0x20(m_renderer, fileName, p_createParams->m_unk0x2c);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046b890
LegoBool32 ImaginaryNotion0x290::VTable0x58(MenuToolCreateParams0x30* p_createParams)
{
	GolString string;

	if (!VTable0x50()) {
		return TRUE;
	}

	m_menuNameStrings->CopyStringByIndex(&string, m_unk0x28c);

	LegoChar fileName[16];
	string.CopyToString(fileName);

	const LegoChar* styleSuffix = ".msb";
	if (!p_createParams->m_unk0x2c) {
		styleSuffix = ".msd";
	}
	strcat(fileName, styleSuffix);

	if (!GolStream::FindFile(fileName)) {
		CeruleanEmperor0x4c::ResourceLoadParams params;
		params.m_renderer = m_renderer;
		params.m_unk0x04 = p_createParams->m_menuStyles;
		params.m_fileName = fileName;
		params.m_binary = p_createParams->m_unk0x2c;

		if (!GetMenuStyles()->Load(&params)) {
			return FALSE;
		}
	}

	string.CopyToString(fileName);

	const LegoChar* inputSuffix = ".mib";
	if (!p_createParams->m_unk0x2c) {
		inputSuffix = ".mid";
	}
	strcat(fileName, inputSuffix);

	if (!GolStream::FindFile(fileName)) {
		MenuInputBindingTable::ResourceLoadParams params;
		params.m_renderer = m_renderer;
		params.m_fileName = fileName;
		params.m_binary = p_createParams->m_unk0x2c;

		if (!GetMenuInputBindings()->Load(&params)) {
			return FALSE;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046ba60
void ImaginaryNotion0x290::FUN_0046ba60(ObscureVantage0x58::CreateParams0x38* p_createParams)
{
	if (!p_createParams->m_golExport) {
		p_createParams->m_golExport = m_golExport;
	}

	if (!p_createParams->m_renderer) {
		p_createParams->m_renderer = m_renderer;
	}

	if (!p_createParams->m_soundGroupBinding) {
		p_createParams->m_soundGroupBinding = m_soundGroupBinding;
	}

	if (!p_createParams->m_eventHandler) {
		p_createParams->m_eventHandler = this;
	}

	if (!(p_createParams->m_flags & 2)) {
		::memset(&p_createParams->m_unk0x22, 0xff, sizeof(p_createParams->m_unk0x22));
	}

	if (!p_createParams->m_parent && (p_createParams->m_flags & 1)) {
		if (p_createParams->m_name[0]) {
			MenuInputBindingTable::Entry0x84* entry =
				(MenuInputBindingTable::Entry0x84*) GetMenuInputBindings()->FUN_0046aff0(p_createParams->m_name);

			if (entry) {
				p_createParams->m_unk0x26 = entry->m_unk0x20;
			}
		}

		if (!p_createParams->m_unk0x26) {
			p_createParams->m_unk0x26 = 1;
		}

		p_createParams->m_parent = m_unk0xd8.FUN_00472f10(p_createParams->m_unk0x26);
	}
}

// FUNCTION: LEGORACERS 0x0046bb10
void ImaginaryNotion0x290::FUN_0046bb10(ObscureIcon0x1a8::CreateParams0x84* p_createParams)
{
	if (!p_createParams->m_parent && p_createParams->m_unk0x74) {
		if (p_createParams->m_unk0x4a) {
			MenuInputBindingTable::Entry0x84* entry =
				(MenuInputBindingTable::Entry0x84*) GetMenuInputBindings()->FUN_0046aff0(p_createParams->m_name);
			p_createParams->m_unk0x48 = entry->m_unk0x20;
		}

		if (!p_createParams->m_unk0x48) {
			p_createParams->m_unk0x48 = 1;
		}

		p_createParams->m_parent = static_cast<ObscureIcon0x1a8*>(m_unk0xd8.FUN_00472f10(p_createParams->m_unk0x48));
	}

	if (!p_createParams->m_unk0x80) {
		p_createParams->m_unk0x80 = this;
	}

	FUN_0046ba60(p_createParams);
}

// STUB: LEGORACERS 0x0046bb90
void ImaginaryNotion0x290::FUN_0046bb90(
	ObscureBanner0x5ec::CreateParams0x90* p_createParams,
	CeruleanEmperor0x4c::Entry0xbc* p_styleEntry
)
{
	LegoS32 i;

	FUN_0046bb10(p_createParams);
	FUN_0046bb10(p_createParams->m_unk0x84);
	FUN_0046bb10(p_createParams->m_unk0x88);
	FUN_0046ba60(p_createParams->m_unk0x8c);

	p_createParams->m_unk0x84->m_unk0x38 = p_createParams->m_unk0x38;
	p_createParams->m_unk0x88->m_unk0x38 = p_createParams->m_unk0x38;
	p_createParams->m_unk0x84->m_unk0x80 = NULL;
	p_createParams->m_unk0x88->m_unk0x80 = NULL;

	for (i = 0; i < 6; i++) {
		if (!p_createParams->m_unk0x84->m_images[i]) {
			p_createParams->m_unk0x84->m_images[i] = p_styleEntry->GetUnk0x90()->m_unk0x90[i];
		}

		if (!p_createParams->m_unk0x88->m_images[i]) {
			p_createParams->m_unk0x88->m_images[i] = p_styleEntry->GetUnk0x94()->m_unk0x90[i];
		}
	}

	for (i = 0; i < 8; i++) {
		if (!p_createParams->m_unk0x8c->m_images[6]) {
			p_createParams->m_unk0x8c->m_images[6] = p_styleEntry->m_unk0x98->m_unk0x00[6];
		}
	}

	if (!(p_createParams->m_unk0x8c->m_flags & 2) && p_styleEntry->m_unk0x98->m_unk0x28) {
		p_createParams->m_unk0x8c->m_unk0x58 = p_styleEntry->m_unk0x98->m_unk0x24;
	}
}

// FUNCTION: LEGORACERS 0x0046bc90
void ImaginaryNotion0x290::FUN_0046bc90(
	MenuInputBindingTable::Entry0xb8* p_createParams,
	CeruleanEmperor0x4c::Entry0xbcWithImages* p_styleEntry
)
{
	FUN_0046bb10(p_createParams);
	FUN_0046bb10(p_createParams->m_unk0x84);
	FUN_0046bb10(p_createParams->m_unk0x88);
	FUN_0046ba60(p_createParams->m_unk0x90);
	FUN_0046ba60(p_createParams->m_unk0x8c);

	p_createParams->m_unk0x84->m_unk0x38 = p_createParams->m_unk0x38;
	p_createParams->m_unk0x84->m_unk0x80 = NULL;
	p_createParams->m_unk0x88->m_unk0x38 = p_createParams->m_unk0x38;
	p_createParams->m_unk0x88->m_unk0x80 = NULL;

	for (LegoS32 i = 0; i < 6; i++) {
		if (!p_createParams->m_unk0x84->m_images[i]) {
			p_createParams->m_unk0x84->m_images[i] = p_styleEntry->GetUnk0x90()->m_unk0x90[i];
		}

		if (!p_createParams->m_unk0x88->m_images[i]) {
			p_createParams->m_unk0x88->m_images[i] = p_styleEntry->GetUnk0x94()->m_unk0x90[i];
		}
	}

	if (!p_createParams->m_unk0x90->m_unk0x38) {
		p_createParams->m_unk0x90->m_unk0x38 = p_styleEntry->m_unk0x9c->m_unk0x00;
	}

	if (!p_createParams->m_unk0x8c->m_unk0x38) {
		p_createParams->m_unk0x8c->m_unk0x38 = p_styleEntry->m_unk0x98->m_unk0x00;
	}
}

// FUNCTION: LEGORACERS 0x0046bd80
void* ImaginaryNotion0x290::FUN_0046bd80(undefined2 p_unk0x04)
{
	GolString string;
	GolName name;

	m_menuNameStrings->CopyStringByIndex(&string, p_unk0x04);
	string.CopyToBuf8(name);
	return VTable0x60()->FUN_00470e60(name);
}

// FUNCTION: LEGORACERS 0x0046be10
void* ImaginaryNotion0x290::FUN_0046be10(undefined2 p_unk0x04)
{
	GolString string;
	GolName name;

	m_menuNameStrings->CopyStringByIndex(&string, p_unk0x04);
	string.CopyToBuf8(name);
	return GetMenuInputBindings()->FUN_0046aff0(name);
}

// FUNCTION: LEGORACERS 0x0046bea0
void ImaginaryNotion0x290::FUN_0046bea0(ObscureZebra0xa4* p_unk0x04, undefined2 p_unk0x08)
{
	MenuInputBindingTable::Entry0x38* sourceParams =
		static_cast<MenuInputBindingTable::Entry0x38*>(FUN_0046be10(p_unk0x08));
	if (sourceParams == NULL) {
		return;
	}

	MenuInputBindingTable::Entry0x38 createParams = *sourceParams;
	FUN_0046ba60(&createParams);

	p_unk0x04->FUN_004735a0(&createParams);
}

// FUNCTION: LEGORACERS 0x0046bef0
LegoBool32 ImaginaryNotion0x290::FUN_0046bef0(ObscureAnchor0x5c* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuInputBindingTable::Entry0x3c* sourceParams = GetInputBindingEntry0x3c(p_unk0x08);
	CeruleanEmperor0x4c::Entry0x0c* styleEntry = GetStyleEntry0x0c(p_unk0x0c);
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	ObscureAnchor0x5c::CreateParams0x3c createParams = *sourceParams;
	FUN_0046ba60(&createParams);

	if (!createParams.m_unk0x38) {
		createParams.m_unk0x38 = styleEntry->m_unk0x00;
	}

	if (!(createParams.m_flags & 2) && styleEntry->m_unk0x08) {
		createParams.m_unk0x38 = styleEntry->m_unk0x00;
	}

	return p_unk0x04->FUN_0046f150(&createParams);
}

// FUNCTION: LEGORACERS 0x0046bf80
LegoBool32 ImaginaryNotion0x290::FUN_0046bf80(
	MainMenuScreenFieldAt0x420* p_unk0x04,
	undefined2 p_unk0x08,
	undefined2 p_unk0x0c,
	undefined2 p_unk0x10
)
{
	MainMenuScreenFieldAt0x420::CreateParams0x48* sourceParams =
		static_cast<MainMenuScreenFieldAt0x420::CreateParams0x48*>(FUN_0046be10(p_unk0x08));
	CeruleanEmperor0x4c::Entry0x14* styleEntry = static_cast<CeruleanEmperor0x4c::Entry0x14*>(FUN_0046bd80(p_unk0x0c));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MainMenuScreenFieldAt0x420::CreateParams0x48 createParams = *sourceParams;
	FUN_0046ba60(&createParams);
	createParams.m_unk0x40 = p_unk0x10;

	if (!createParams.m_unk0x38) {
		createParams.m_unk0x38 = m_menuTextStrings;
	}

	if (!createParams.m_unk0x44 && styleEntry->m_unk0x08) {
		createParams.m_unk0x44 = styleEntry->m_unk0x08;
	}

	if (!createParams.m_unk0x3c) {
		createParams.m_unk0x3c = styleEntry->m_unk0x00;
	}

	if (styleEntry->m_unk0x0c && !(createParams.m_flags & 2)) {
		createParams.m_unk0x22 = styleEntry->m_unk0x04;
	}

	return p_unk0x04->FUN_0046f520(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c050
LegoBool32 ImaginaryNotion0x290::FUN_0046c050(ObscureTome0x3fc* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuInputBindingTable::Entry0x60* sourceParams =
		static_cast<MenuInputBindingTable::Entry0x60*>(FUN_0046be10(p_unk0x08));
	CeruleanEmperor0x4c::Entry0x2c* styleEntry = static_cast<CeruleanEmperor0x4c::Entry0x2c*>(FUN_0046bd80(p_unk0x0c));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	ObscureTome0x3fc::CreateParams0x60 createParams = *sourceParams;
	FUN_0046ba60(&createParams);

	for (LegoS32 i = 0; i < 8; i++) {
		if (!createParams.m_images[i]) {
			createParams.m_images[i] = styleEntry->m_unk0x00[i];
		}
	}

	if (!(sourceParams->m_flags & 2) && styleEntry->m_unk0x28) {
		createParams.m_unk0x22 = styleEntry->m_unk0x20;
		createParams.m_unk0x58 = styleEntry->m_unk0x24;
	}

	return p_unk0x04->FUN_0046ecd0(&createParams);
}

// FUNCTION: LEGORACERS 0x0046c110
LegoBool32 ImaginaryNotion0x290::FUN_0046c110(ObscureGlyph0x21c* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	ObscureGlyph0x21c::CreateParams0x9c* sourceParams =
		static_cast<ObscureGlyph0x21c::CreateParams0x9c*>(FUN_0046be10(p_unk0x08));
	CeruleanEmperor0x4c::Entry0xa8* styleEntry = static_cast<CeruleanEmperor0x4c::Entry0xa8*>(FUN_0046bd80(p_unk0x0c));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	ObscureGlyph0x21c::CreateParams0x9c createParams = *sourceParams;
	FUN_0046bb10(&createParams);

	for (LegoS32 i = 0; i < 6; i++) {
		if (!createParams.m_images[i]) {
			createParams.m_images[i] = styleEntry->m_unk0x90[i];
		}
	}

	return p_unk0x04->FUN_004663d0(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c1b0
LegoBool32 ImaginaryNotion0x290::FUN_0046c1b0(
	ObscureLattice0x228* p_unk0x04,
	undefined2 p_unk0x08,
	undefined2 p_unk0x0c
)
{
	ObscureLattice0x228::CreateParams0xa0* sourceParams =
		static_cast<ObscureLattice0x228::CreateParams0xa0*>(FUN_0046be10(p_unk0x08));
	CeruleanEmperor0x4c::Entry0x150* styleEntry = GetStyleEntry0x150(p_unk0x0c);
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	ObscureLattice0x228::CreateParams0xa0 createParams = *sourceParams;
	FUN_0046bb10(&createParams);

	if (!createParams.m_unk0x9c) {
		createParams.m_unk0x9c = styleEntry->m_unk0xa8;
	}

	return p_unk0x04->FUN_004665f0(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c240
LegoBool32 ImaginaryNotion0x290::FUN_0046c240(
	ObscureCarousel0x78* p_unk0x04,
	undefined2 p_unk0x08,
	undefined2 p_unk0x0c
)
{
	ObscureCarousel0x78::CreateParams0x38* sourceParams =
		static_cast<ObscureCarousel0x78::CreateParams0x38*>(FUN_0046be10(p_unk0x08));
	CeruleanEmperor0x4c::Entry0x18* styleEntry = static_cast<CeruleanEmperor0x4c::Entry0x18*>(FUN_0046bd80(p_unk0x0c));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	ObscureCarousel0x78::CreateParams0x38 createParams = *sourceParams;
	FUN_0046ba60(&createParams);

	return p_unk0x04->FUN_0046c970(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c2b0
LegoBool32 ImaginaryNotion0x290::FUN_0046c2b0(
	ObscureBanner0x9f4* p_widget,
	ObscureCarousel0x94* p_carousel,
	undefined2 p_cpId,
	undefined2 p_styleId
)
{
	ObscureBanner0x9f4::CreateParams0x98* sourceParams =
		static_cast<ObscureBanner0x9f4::CreateParams0x98*>(FUN_0046be10(p_cpId));
	CeruleanEmperor0x4c::Entry0xbc* styleEntry = static_cast<CeruleanEmperor0x4c::Entry0xbc*>(FUN_0046bd80(p_styleId));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	ObscureBanner0x9f4::CreateParams0x98* bannerParams = new ObscureBanner0x9f4::CreateParams0x98;
	ObscureGlyph0x21c::CreateParams0x9c* glyph1Params = new ObscureGlyph0x21c::CreateParams0x9c;
	ObscureGlyph0x21c::CreateParams0x9c* glyph2Params = new ObscureGlyph0x21c::CreateParams0x9c;
	ObscureTome0x3fc::CreateParams0x60* tomeParams = new ObscureTome0x3fc::CreateParams0x60;
	if (!bannerParams || !glyph1Params || !glyph2Params || !tomeParams) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	*bannerParams = *sourceParams;
	*glyph1Params = *sourceParams->m_unk0x84;
	*glyph2Params = *sourceParams->m_unk0x88;
	*tomeParams = *sourceParams->m_unk0x8c;

	bannerParams->m_unk0x88 = glyph2Params;
	bannerParams->m_unk0x84 = glyph1Params;
	bannerParams->m_unk0x8c = tomeParams;
	bannerParams->m_unk0x90 = p_carousel;

	FUN_0046bb90(bannerParams, styleEntry);

	LegoBool32 result = p_widget->FUN_00467800(bannerParams, styleEntry);

	delete bannerParams;
	delete glyph1Params;
	delete glyph2Params;
	delete tomeParams;

	return result;
}

// FUNCTION: LEGORACERS 0x0046c400
LegoBool32 ImaginaryNotion0x290::FUN_0046c400(
	OptionsScreenFieldAt0x4178Base0x6e4* p_widget,
	undefined2 p_cpId,
	undefined2 p_styleId
)
{
	MenuInputBindingTable::Entry0xb8* sourceParams =
		static_cast<MenuInputBindingTable::Entry0xb8*>(FUN_0046be10(p_cpId));
	CeruleanEmperor0x4c::Entry0xbcWithImages* styleEntry =
		static_cast<CeruleanEmperor0x4c::Entry0xbcWithImages*>(FUN_0046bd80(p_styleId));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuInputBindingTable::Entry0xb8 createParams = *sourceParams;
	FUN_0046bc90(&createParams, styleEntry);

	return p_widget->FUN_0046dfb0(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c480
LegoBool32 ImaginaryNotion0x290::FUN_0046c480(ObscureSigil0xdc* p_unk0x04, undefined4 p_unk0x08, undefined2 p_unk0x0c)
{
	ObscureSigil0xdc::CreateParams0x84* sourceParams =
		static_cast<ObscureSigil0xdc::CreateParams0x84*>(FUN_0046be10(p_unk0x0c));
	if (!sourceParams) {
		return FALSE;
	}

	ObscureSigil0xdc::CreateParams0x84 createParams = *sourceParams;
	FUN_0046ba60(&createParams);
	createParams.m_unk0x7c = p_unk0x08;
	createParams.m_unk0x5c = 1.0f;
	createParams.m_unk0x80 = VTable0x6c();
	return p_unk0x04->FUN_00465820(&createParams, m_unk0x288);
}

// FUNCTION: LEGORACERS 0x0046c510
LegoBool32 ImaginaryNotion0x290::FUN_0046c510(ObscureRune0x4d8* p_unk0x04, undefined4 p_unk0x08, undefined2 p_unk0x0c)
{
	ObscureRune0x4d8::CreateParams0x88* sourceParams =
		static_cast<ObscureRune0x4d8::CreateParams0x88*>(FUN_0046be10(p_unk0x0c));
	if (!sourceParams) {
		return FALSE;
	}

	ObscureRune0x4d8::CreateParams0x88 createParams = *sourceParams;
	FUN_0046ba60(&createParams);

	if (createParams.m_unk0x84) {
		FUN_0046ba60(createParams.m_unk0x84);
	}

	createParams.m_unk0x7c = p_unk0x08;
	createParams.m_unk0x5c = 1.0f;
	createParams.m_unk0x80 = VTable0x6c();
	return p_unk0x04->FUN_004661f0(&createParams, m_unk0x288);
}

// FUNCTION: LEGORACERS 0x0046c5b0
undefined4 ImaginaryNotion0x290::FUN_0046c5b0(ObscureVantage0x58* p_unk0x04, undefined2 p_unk0x08)
{
	FieldAt0x54* params = GetInputBindingEntry0x54(p_unk0x08);
	if (!params) {
		return 0;
	}

	FieldAt0x54 createParams = *params;
	FUN_0046ba60(&createParams);
	createParams.m_unk0x50 = VTable0x6c();

	return static_cast<ImaginaryChisel0x658::HelperAt0x368*>(p_unk0x04)->FUN_00466b50(&createParams, m_unk0x288);
}

// FUNCTION: LEGORACERS 0x0046c610
LegoBool32 ImaginaryNotion0x290::FUN_0046c610(
	IvoryTalon0x23c* p_unk0x04,
	undefined2 p_unk0x08,
	undefined2 p_unk0x0c,
	undefined2 p_unk0x10,
	GolString* p_unk0x14
)
{
	IvoryTalon0x23c::CreateParams0xa0* sourceParams =
		static_cast<IvoryTalon0x23c::CreateParams0xa0*>(FUN_0046be10(p_unk0x08));
	ObscureIcon0x1a8::CreateState0x90* styleEntry =
		static_cast<ObscureIcon0x1a8::CreateState0x90*>(FUN_0046bd80(p_unk0x0c));
	if (!sourceParams || !styleEntry || !p_unk0x10) {
		return FALSE;
	}

	IvoryTalon0x23c::CreateParams0xa0 createParams = *sourceParams;
	FUN_0046bb10(&createParams);

	if (!createParams.m_unk0x84) {
		createParams.m_unk0x84 = m_menuTextStrings;
	}

	createParams.m_unk0x88 = p_unk0x10;
	createParams.m_unk0x90 = p_unk0x14;
	createParams.m_unk0x8c = sourceParams->m_unk0x8c;

	return p_unk0x04->VTable0x70(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c6f0
undefined4 ImaginaryNotion0x290::FUN_0046c6f0(
	ObscureIcon0x1a8* p_unk0x04,
	ObscureIcon0x1a8* p_unk0x08,
	undefined2 p_unk0x0c
)
{
	CrimsonSun0xa4::Entry0x74c* entry = m_unk0x284->FUN_00468c50(2, p_unk0x0c, this, 0);
	entry->SetUnk0x744(p_unk0x04);
	entry->SetUnk0x748(p_unk0x08);
	entry->FUN_00468590();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c730
undefined4 ImaginaryNotion0x290::FUN_0046c730(ObscureIcon0x1a8* p_unk0x04, undefined2 p_unk0x08)
{
	CrimsonSun0xa4::Entry0x74c* entry = m_unk0x284->FUN_00468c50(1, p_unk0x08, this, 0);
	entry->SetUnk0x740(p_unk0x04);
	entry->FUN_00468590();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c760
void ImaginaryNotion0x290::FUN_0046c760()
{
	ObscureIcon0x1a8* icon;
	ObscureVantage0x58* node;

	while (m_unk0xd8.GetFirstChild()) {
		icon = &m_unk0xd8;

		while (icon->GetFirstChild()) {
			icon = icon->GetFirstChild();
		}

		icon->DetachFromParent();
	}

	while (static_cast<ObscureVantage0x58*>(&m_unk0xd8)->GetFirstChild()) {
		node = &m_unk0xd8;

		while (node->GetFirstChild()) {
			node = node->GetFirstChild();
		}

		node->RemoveFromParent();
	}
}

// FUNCTION: LEGORACERS 0x0046c7d0
LegoBool32 ImaginaryNotion0x290::VTable0x78(undefined4)
{
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c7e0 FOLDED
LegoBool32 ImaginaryNotion0x290::VTable0x7c(Rect* p_arg1, Rect* p_arg2)
{
	m_unk0xd8.VTable0x1c(p_arg1, p_arg2);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c810
CeruleanEmperor0x4c* ImaginaryNotion0x290::GetMenuStyles()
{
	return &m_unk0x08;
}

// FUNCTION: LEGORACERS 0x0046c820 FOLDED
CeruleanEmperor0x4c* ImaginaryNotion0x290::VTable0x60()
{
	CeruleanEmperor0x4c* styles = GetMenuStyles();
	if (!styles->GetNameEntries()) {
		return m_menuStyles;
	}

	return styles;
}

// FUNCTION: LEGORACERS 0x0046c840
MenuInputBindingTable* ImaginaryNotion0x290::GetMenuInputBindings()
{
	return &m_unk0x58;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg prevents this trivial body from folding with identical functions elsewhere.

// FUNCTION: LEGORACERS 0x0046c850
#pragma code_seg(".text$imaginarynotion_vt6c")
LegoFloat ImaginaryNotion0x290::VTable0x6c()
{
	return 1.0f;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 ImaginaryNotion0x290::VTable0x14(ObscureVantage0x58*, void*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 ImaginaryNotion0x290::VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 ImaginaryNotion0x290::VTable0x1c(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 ImaginaryNotion0x290::VTable0x28(ObscureVantage0x58*, void*, undefined4, undefined4)
{
	return 0;
}

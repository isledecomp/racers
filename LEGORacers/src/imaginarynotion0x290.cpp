#include "imaginarynotion0x290.h"

#include "awakekite0x20.h"
#include "bronzefalcon0xc8770.h"
#include "crimsonsun0xa4.h"
#include "gol.h"
#include "golcommondrawstate.h"
#include "goldrawstate.h"
#include "golfonttable.h"
#include "golname.h"
#include "golstream.h"
#include "golstring.h"
#include "golstringtable.h"
#include "imaginarychisel0x658.h"
#include "imaginarydrillfieldat0x420.h"
#include "input/inputmanager.h"
#include "menutoolcreateparams0x30.h"
#include "obscureanchor0x5c.h"
#include "obscurevantage0x58.h"

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
void ImaginaryNotion0x290::VTable0x10(undefined4)
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
void ImaginaryNotion0x290::VTable0x44(undefined4)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x48(undefined4)
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
	m_unk0xc4 = NULL;
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
	m_unk0xc4 = (FieldAt0xc4*) p_createParams->m_unk0x24;
	m_unk0x28c = p_createParams->m_menuId;
	m_menuStyles = p_createParams->m_menuStyles;
	m_inputBindingContainer = p_createParams->m_inputBindingContainer;
	m_menuTextStrings = p_createParams->m_menuTextStrings;
	m_menuNameStrings = p_createParams->m_menuNameStrings;

	if (FUN_0046b630() && FUN_0046b6e0(p_createParams) && VTable0x58(p_createParams)) {
		VTable0x4c();
		m_inputManager->PollDevices(0);
		m_inputBindingContainer->ClearQueue();
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
		CeruleanQueen0x58::ResourceLoadParams params;
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
void ImaginaryNotion0x290::FUN_0046ba60(ObscureVantage0x58::CreateParams0x30* p_createParams)
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
		if (p_createParams->m_flagsAndName.m_unk0x2d[0]) {
			CeruleanQueen0x58::Entry0x84* entry = (CeruleanQueen0x58::Entry0x84*) GetMenuInputBindings()->FUN_0046aff0(
				p_createParams->m_flagsAndName.m_unk0x2d
			);

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
			CeruleanQueen0x58::Entry0x84* entry = (CeruleanQueen0x58::Entry0x84*) GetMenuInputBindings()->FUN_0046aff0(
				p_createParams->m_flagsAndName.m_unk0x2d
			);
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
void ImaginaryNotion0x290::FUN_0046bb90(undefined4*, undefined4)
{
	// TODO
	STUB(0x0046bb90);
}

// STUB: LEGORACERS 0x0046bc90
void ImaginaryNotion0x290::FUN_0046bc90(undefined4*, undefined4)
{
	// TODO
	STUB(0x0046bc90);
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

// STUB: LEGORACERS 0x0046bea0
void ImaginaryNotion0x290::FUN_0046bea0(undefined4*, undefined2)
{
	// TODO
	STUB(0x0046bea0);
}

// FUNCTION: LEGORACERS 0x0046bef0
LegoBool32 ImaginaryNotion0x290::FUN_0046bef0(ObscureAnchor0x5c* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	CeruleanQueen0x58::Entry0x3c* sourceParams = GetInputBindingEntry0x3c(p_unk0x08);
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
	ImaginaryDrillFieldAt0x420* p_unk0x04,
	undefined2 p_unk0x08,
	undefined2 p_unk0x0c,
	undefined2 p_unk0x10
)
{
	ImaginaryDrillFieldAt0x420::CreateParams0x48* sourceParams =
		static_cast<ImaginaryDrillFieldAt0x420::CreateParams0x48*>(FUN_0046be10(p_unk0x08));
	CeruleanEmperor0x4c::Entry0x14* styleEntry = static_cast<CeruleanEmperor0x4c::Entry0x14*>(FUN_0046bd80(p_unk0x0c));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	ImaginaryDrillFieldAt0x420::CreateParams0x48 createParams = *sourceParams;
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

// STUB: LEGORACERS 0x0046c050
undefined4 ImaginaryNotion0x290::FUN_0046c050(undefined4*, undefined2, undefined2)
{
	// TODO
	STUB(0x0046c050);
	return 0;
}

// STUB: LEGORACERS 0x0046c110
undefined4 ImaginaryNotion0x290::FUN_0046c110(undefined4*, undefined2, undefined2)
{
	// TODO
	STUB(0x0046c110);
	return 0;
}

// STUB: LEGORACERS 0x0046c1b0
undefined4 ImaginaryNotion0x290::FUN_0046c1b0(undefined4*, undefined2, undefined2)
{
	// TODO
	STUB(0x0046c1b0);
	return 0;
}

// STUB: LEGORACERS 0x0046c240
undefined4 ImaginaryNotion0x290::FUN_0046c240(undefined4*, undefined2, undefined2)
{
	// TODO
	STUB(0x0046c240);
	return 0;
}

// STUB: LEGORACERS 0x0046c2b0
void ImaginaryNotion0x290::FUN_0046c2b0(undefined4*, undefined4, undefined2, undefined2)
{
	// TODO
	STUB(0x0046c2b0);
}

// STUB: LEGORACERS 0x0046c400
undefined4 ImaginaryNotion0x290::FUN_0046c400(undefined4*, undefined2, undefined2)
{
	// TODO
	STUB(0x0046c400);
	return 0;
}

// STUB: LEGORACERS 0x0046c480
void ImaginaryNotion0x290::FUN_0046c480(ObscureVantage0x58*, undefined4, undefined2)
{
	// TODO
	STUB(0x0046c480);
}

// STUB: LEGORACERS 0x0046c510
void ImaginaryNotion0x290::FUN_0046c510(undefined4*, undefined4, undefined2)
{
	// TODO
	STUB(0x0046c510);
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

// STUB: LEGORACERS 0x0046c610
undefined4 ImaginaryNotion0x290::FUN_0046c610(undefined4*, undefined2, undefined2, undefined2, undefined4)
{
	// TODO
	STUB(0x0046c610);
	return 0;
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
CeruleanQueen0x58* ImaginaryNotion0x290::GetMenuInputBindings()
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
undefined4 ImaginaryNotion0x290::VTable0x14(ObscureIcon0x1a8*, void*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 ImaginaryNotion0x290::VTable0x18(ObscureIcon0x1a8*, OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 ImaginaryNotion0x290::VTable0x1c(ObscureIcon0x1a8*, OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 ImaginaryNotion0x290::VTable0x28(ObscureIcon0x1a8*, void*, undefined4, undefined4)
{
	return 0;
}

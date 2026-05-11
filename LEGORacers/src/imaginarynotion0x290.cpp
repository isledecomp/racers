#include "imaginarynotion0x290.h"

#include "awakekite0x20.h"
#include "bronzefalcon0xc8770.h"
#include "gol.h"
#include "golcommondrawstate.h"
#include "goldrawstate.h"
#include "golfonttable.h"
#include "golstream.h"
#include "golstring.h"
#include "golstringtable.h"
#include "input/inputmanager.h"
#include "menutoolcreateparams0x30.h"
#include "obscurevantage0x58.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryNotion0x290, 0x290)

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
void ImaginaryNotion0x290::VTable0x00(undefined4)
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
void ImaginaryNotion0x290::VTable0x20(undefined4)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x24(undefined4)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x2c(undefined4)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x30(undefined4)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x34(undefined4)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x38(undefined4)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x3c(undefined4)
{
	// TODO
	STUB(0x0044f590);
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void ImaginaryNotion0x290::VTable0x40(undefined4)
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
	m_menuTextStrings = 0;
	m_menuNameStrings = NULL;
	m_golExport = 0;
	m_renderer = 0;
	m_unk0xbc = NULL;
	m_fontTable = 0;
	m_soundGroupBinding = 0;
	m_inputManager = NULL;
	m_unk0x284 = 0;
	m_unk0xc4 = NULL;
	m_menuStyles = 0;
	m_unk0x28c = 0;
	m_unk0x08.Clear();
	m_unk0x58.Clear();
	m_unk0xd8.VTable0x08();
	m_unk0x04 = 0;
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
		m_unk0x04 = TRUE;
	}

	return m_unk0x04;
}

// FUNCTION: LEGORACERS 0x0046b5d0
LegoBool32 ImaginaryNotion0x290::Destroy()
{
	if (m_unk0x04) {
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
	createParams.m_width = drawState->m_width;
	createParams.m_height = drawState->m_height;
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

// STUB: LEGORACERS 0x0046ba60
void ImaginaryNotion0x290::FUN_0046ba60(undefined4*)
{
	// TODO
	STUB(0x0046ba60);
}

// STUB: LEGORACERS 0x0046bb10
void ImaginaryNotion0x290::FUN_0046bb10(undefined4*)
{
	// TODO
	STUB(0x0046bb10);
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

// STUB: LEGORACERS 0x0046bd80
void ImaginaryNotion0x290::FUN_0046bd80(undefined4*, undefined4)
{
	// TODO
	STUB(0x0046bd80);
}

// STUB: LEGORACERS 0x0046be10
void ImaginaryNotion0x290::FUN_0046be10(undefined4*, undefined2)
{
	// TODO
	STUB(0x0046be10);
}

// STUB: LEGORACERS 0x0046bea0
void ImaginaryNotion0x290::FUN_0046bea0(undefined4*, undefined2)
{
	// TODO
	STUB(0x0046bea0);
}

// STUB: LEGORACERS 0x0046bef0
undefined4 ImaginaryNotion0x290::FUN_0046bef0(undefined4*, undefined2, undefined2)
{
	// TODO
	STUB(0x0046bef0);
	return 0;
}

// STUB: LEGORACERS 0x0046bf80
undefined4 ImaginaryNotion0x290::FUN_0046bf80(undefined4*, undefined2, undefined2, undefined2)
{
	// TODO
	STUB(0x0046bf80);
	return 0;
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
void ImaginaryNotion0x290::FUN_0046c480(undefined4*, undefined4, undefined2)
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

// STUB: LEGORACERS 0x0046c5b0
void ImaginaryNotion0x290::FUN_0046c5b0(ObscureVantage0x58*, undefined2)
{
	// TODO
	STUB(0x0046c5b0);
}

// STUB: LEGORACERS 0x0046c610
undefined4 ImaginaryNotion0x290::FUN_0046c610(undefined4*, undefined2, undefined2, undefined2, undefined4)
{
	// TODO
	STUB(0x0046c610);
	return 0;
}

// STUB: LEGORACERS 0x0046c6f0
undefined4 ImaginaryNotion0x290::FUN_0046c6f0(undefined4, undefined4, undefined2)
{
	// TODO
	STUB(0x0046c6f0);
	return 1;
}

// STUB: LEGORACERS 0x0046c730
undefined4 ImaginaryNotion0x290::FUN_0046c730(undefined4, undefined2)
{
	// TODO
	STUB(0x0046c730);
	return 1;
}

// STUB: LEGORACERS 0x0046c760
void ImaginaryNotion0x290::FUN_0046c760()
{
	// TODO
	STUB(0x0046c760);
}

// STUB: LEGORACERS 0x0046c7d0
LegoBool32 ImaginaryNotion0x290::VTable0x78(undefined4)
{
	// TODO
	STUB(0x0046c7d0);
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

// STUB: LEGORACERS 0x0046c820 FOLDED
void ImaginaryNotion0x290::VTable0x60()
{
	// TODO
	STUB(0x0046c820);
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

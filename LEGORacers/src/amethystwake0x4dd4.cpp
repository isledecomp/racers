#include "amethystwake0x4dd4.h"

#include "golhashtable.h"
#include "golstream.h"
#include "imaginarytool0x368.h"
#include "input/inputmanager.h"
#include "input/keyboarddevice.h"

#include <golerror.h>
#include <stddef.h>

DECOMP_SIZE_ASSERT(AmethystWake0x4dd4, 0x4dd4)

// GLOBAL: LEGORACERS 0x004c4918
AmethystWake0x4dd4* g_unk0x4c4918 = NULL;

// GLOBAL: LEGORACERS 0x004beb78
LegoFloat g_unk0x4beb78[7] = {0.04f, 0.04f, 0.04f, 0.04f, 0.39f, 0.4f, 0.04f};

// FUNCTION: LEGORACERS 0x0042b1e0
void AmethystWake0x4dd4::FUN_0042b1e0(LegoRacers::Context* p_context)
{
	g_unk0x4c4918 = new AmethystWake0x4dd4();
	if (!g_unk0x4c4918) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_unk0x4c4918->FUN_0042cb90(p_context);
	g_unk0x4c4918->FUN_0042d510();
	g_unk0x4c4918->Shutdown();

	if (g_unk0x4c4918) {
		delete g_unk0x4c4918;
	}
}

// FUNCTION: LEGORACERS 0x0042c5d0
AmethystWake0x4dd4::AmethystWake0x4dd4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0042c910
AmethystWake0x4dd4::~AmethystWake0x4dd4()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0042cb00
void AmethystWake0x4dd4::Reset()
{
	m_unk0x04.m_context = NULL;
	m_unk0x04.m_unk0x258.GetUnk0x1cfc().Reset();
	m_unk0x04.m_unk0x4b40.Reset();
	m_unk0x4cd4 = NULL;
	m_unk0x4cd8 = NULL;
	m_unk0x4d20 = 0;
	m_unk0x4dc8 = NULL;
	m_unk0x4cdc = NULL;
	m_unk0x4ce0 = NULL;
	m_unk0x4dd0 = FALSE;
	m_unk0x4d24.Reset();
	m_unk0x4d30.Reset();
	m_unk0x4d48.VTable0x08();
}

// FUNCTION: LEGORACERS 0x0042cb90
LegoS32 AmethystWake0x4dd4::FUN_0042cb90(LegoRacers::Context* p_context)
{
	LegoBool32 flag = FALSE;
	m_unk0x04.m_context = p_context;
	m_unk0x4cd4 = p_context->m_golApp->GetGolExport();
	m_unk0x4cd8 = p_context->m_golApp->GetRenderer();

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	FUN_0042d020();
	FUN_0042d0e0();
	FUN_0042d300(m_unk0x04.m_unk0x258.GetUnk0x18e6(), TRUE);
	FUN_0042d1e0();
	FUN_0042e1f0();
	FUN_0042cde0();
	InitializeInputBindings();
	FUN_0042cf00();
	FUN_0042cd60();

	if (FUN_0042e490()) {
		flag = TRUE;
	}
	if (FUN_0042e680()) {
		flag = TRUE;
	}

	m_unk0x4cd8->VTable0x34(7, g_unk0x4beb78);

	m_unk0x04.m_unk0x04.Allocate(10);
	m_unk0x04.m_unk0x04.Push(m_unk0x04.m_context->m_unk0x1c);

	if (flag && FUN_0042e450()) {
		m_unk0x04.m_unk0x04.Push(48);
	}

	LegoU16 top = m_unk0x04.m_unk0x04.Peek();
	FUN_0042d3e0(top);

	m_unk0x4bd0.FUN_00468af0(m_unk0x4d98, 2, &m_unk0x4c74);
	return 1;
}

// FUNCTION: LEGORACERS 0x0042ccc0
LegoS32 AmethystWake0x4dd4::Shutdown()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(NULL);
	}

	if (m_unk0x04.m_context) {
		if (m_unk0x4dc8) {
			m_unk0x4dc8->VTable0x74();

			if (m_unk0x4dc8) {
				delete m_unk0x4dc8;
			}
		}

		m_unk0x4c74.VTable0x0c();
		m_unk0x4bd0.FUN_00468ab0();
		FUN_0042d260();
		ReleaseRendererObject();
		ShutdownInputBindings();
		FUN_0042cf90();
		FUN_0042d080();
		m_unk0x4cd8->VTable0x38();
		Reset();
	}

	return m_unk0x04.m_context == NULL;
}

// FUNCTION: LEGORACERS 0x0042cd60
void AmethystWake0x4dd4::FUN_0042cd60()
{
	LegoChar name[8];
	CopperCrest0x40::InitStruct initStruct;

	m_unk0x4ce4.FUN_0044e500(&m_unk0x4d24, c_menuTextRendererObjectName);
	m_unk0x4d24.CopyToBuf8(name);

	initStruct.m_golExport = m_unk0x4cd4;
	initStruct.m_renderer = m_unk0x4cd8;
	initStruct.m_rendererObject = m_unk0x4cd8->FUN_004131a0(name);
	initStruct.m_inputManager = m_unk0x04.m_context->m_golApp->GetInputManager();
	initStruct.m_inputBindingContainer = m_unk0x04.m_inputBindings.GetUnk0x208();

	m_unk0x4c74.FUN_00469040(&initStruct);
}

// STUB: LEGORACERS 0x0042cde0
void AmethystWake0x4dd4::FUN_0042cde0()
{
	// TODO
	STUB(0x42cde0);
}

// FUNCTION: LEGORACERS 0x0042ceb0
void AmethystWake0x4dd4::ReleaseRendererObject()
{
	undefined4* object = m_unk0x4cd8->GetUnk0x0c();
	if (object) {
		m_unk0x4cd4->VTable0x54(object);
	}
}

// FUNCTION: LEGORACERS 0x0042ced0
void AmethystWake0x4dd4::InitializeInputBindings()
{
	m_unk0x04.m_inputBindings.Initialize(m_unk0x04.m_context->m_golApp->GetInputManager());
}

// FUNCTION: LEGORACERS 0x0042cef0
void AmethystWake0x4dd4::ShutdownInputBindings()
{
	m_unk0x04.m_inputBindings.Shutdown();
}

// STUB: LEGORACERS 0x0042cf00
void AmethystWake0x4dd4::FUN_0042cf00()
{
	// TODO
	STUB(0x42cf00);
}

// STUB: LEGORACERS 0x0042cf90
void AmethystWake0x4dd4::FUN_0042cf90()
{
	// TODO
	STUB(0x42cf90);
}

// FUNCTION: LEGORACERS 0x0042d020
void AmethystWake0x4dd4::FUN_0042d020()
{
	if (!m_unk0x4cdc) {
		m_unk0x4cdc = m_unk0x4cd4->VTable0x34();
	}

	if (!m_unk0x4ce0) {
		m_unk0x4ce0 = m_unk0x4cd4->VTable0x38();
	}

	m_unk0x4cdc->LoadMaterialDefinitions(m_unk0x4cd8, "GImages", m_unk0x04.m_context->m_unk0x18);
}

// STUB: LEGORACERS 0x0042d080
void AmethystWake0x4dd4::FUN_0042d080()
{
	// TODO
	STUB(0x42d080);
}

// STUB: LEGORACERS 0x0042d0e0
void AmethystWake0x4dd4::FUN_0042d0e0()
{
	// TODO
	STUB(0x42d0e0);
}

// STUB: LEGORACERS 0x0042d1e0
void AmethystWake0x4dd4::FUN_0042d1e0()
{
	// TODO
	STUB(0x42d1e0);
}

// STUB: LEGORACERS 0x0042d260
void AmethystWake0x4dd4::FUN_0042d260()
{
	// TODO
	STUB(0x42d260);
}

// STUB: LEGORACERS 0x0042d300
LegoBool AmethystWake0x4dd4::FUN_0042d300(LegoU32, LegoBool)
{
	// TODO
	STUB(0x42d300);
	return FALSE;
}

// STUB: LEGORACERS 0x0042d3e0
void AmethystWake0x4dd4::FUN_0042d3e0(LegoU16)
{
	// TODO
	STUB(0x42d3e0);
}

// FUNCTION: LEGORACERS 0x0042d510
void AmethystWake0x4dd4::FUN_0042d510()
{
	BronzeFalcon0xc8770::JasperRipple0x4 rendererState;
	Win32GolApp* golApp = m_unk0x04.m_context->m_golApp;
	StackOfLegoU16* stack;
	MithrilChain0x8* chain;
	LegoU32 frameDeltaMs;
	LegoU16 previousMenu;

	rendererState.m_unk0x00[0] = 0;
	rendererState.m_unk0x00[1] = 0;
	rendererState.m_unk0x00[2] = 0;
	rendererState.m_unk0x00[3] = 0;
	m_unk0x4cd8->VTable0x1c(&rendererState);
	m_unk0x4dd0 = TRUE;

	while (m_unk0x4dd0) {
		if (!golApp->Tick(this) || !m_unk0x4dd0) {
			m_unk0x04.m_context->m_unk0x00 = FALSE;
			break;
		}

		frameDeltaMs = golApp->GetFrameDeltaMs();
		m_unk0x04.m_context->m_unk0x08->VTable0x34(frameDeltaMs);

		if (!golApp->IsDisabled()) {
			stack = &m_unk0x04.m_unk0x04;
			previousMenu = stack->Peek();
			m_unk0x04.m_context->m_unk0x00 = m_unk0x4c74.VTable0x10(frameDeltaMs);

			if (m_unk0x4bd0.GetUnk0x9c() > 0) {
				m_unk0x4bd0.FUN_00468da0(frameDeltaMs);
			}
			else {
				if (m_unk0x4dc8->VTable0x78(frameDeltaMs)) {
					m_unk0x04.m_context->m_unk0x00 = FALSE;
				}
				if (!m_unk0x04.m_context->m_unk0x00 || !m_unk0x04.m_unk0x04.GetSize()) {
					break;
				}

				if (previousMenu != stack->Peek()) {
					FUN_0042d3e0(stack->Peek());
				}
			}

			chain = &m_unk0x04.m_unk0x4374;
			chain->FUN_00494f60(frameDeltaMs);
			m_unk0x4cd8->VTable0x54(TRUE);
			m_unk0x4cd8->VTable0xec(6);
			m_unk0x4cd8->VTable0xe8(TRUE);

			if (m_unk0x4bd0.GetUnk0x9c() > 0) {
				m_unk0x4bd0.FUN_00468e20();
			}
			else {
				m_unk0x4c74.FUN_00469550();
			}

			chain->FUN_00494fa0(m_unk0x4cd8);
			m_unk0x4cd8->VTable0xe4();
			m_unk0x4cd8->VTable0xf0();

			if (golApp->GetInputManager()->GetKeyboard()->GetButtonState(
					InputDevice::MakeEvent(InputDevice::c_sourceKeyboard, 0xb7)
				)) {
				FUN_0042e720();
			}

			golApp->PresentFrame();
		}
	}

	m_unk0x4cd8->VTable0xf4();
	if (m_unk0x4dc8) {
		m_unk0x4dc8->VTable0x74();
		delete m_unk0x4dc8;
		m_unk0x4dc8 = NULL;
	}

	if (m_unk0x04.m_context->m_unk0x00) {
		FUN_0042d730();
	}
}

// STUB: LEGORACERS 0x0042d730
void AmethystWake0x4dd4::FUN_0042d730()
{
	// TODO
	STUB(0x42d730);
}

// STUB: LEGORACERS 0x0042e1f0
void AmethystWake0x4dd4::FUN_0042e1f0()
{
	// TODO
	STUB(0x42e1f0);
}

// FUNCTION: LEGORACERS 0x0042e450
LegoBool32 AmethystWake0x4dd4::FUN_0042e450()
{
	PeridotTrace0x4e0* entry = m_unk0x04.m_unk0x258.GetUnk0xa58();

	for (LegoU32 i = 0; i < m_unk0x04.m_unk0x258.GetUnk0x18c0(); i++, entry++) {
		if (entry->HasUnk0x4b4Flag0x01()) {
			return TRUE;
		}
	}

	return FALSE;
}

// STUB: LEGORACERS 0x0042e490
LegoS32 AmethystWake0x4dd4::FUN_0042e490()
{
	// TODO
	STUB(0x42e490);
	return FALSE;
}

// STUB: LEGORACERS 0x0042e680
LegoS32 AmethystWake0x4dd4::FUN_0042e680()
{
	// TODO
	STUB(0x42e680);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0042e700
void AmethystWake0x4dd4::VTable0x00()
{
	m_unk0x4dd0 = FALSE;
	m_unk0x04.m_context->m_unk0x00 = FALSE;
}

// STUB: LEGORACERS 0x0042e720
void AmethystWake0x4dd4::FUN_0042e720()
{
	// TODO
	STUB(0x42e720);
}

// FUNCTION: LEGORACERS 0x0042e810
void AmethystWake0x4dd4::VTable0x1c(undefined4 p_unk0x04)
{
	if (m_unk0x4dc8) {
		m_unk0x4dc8->VTable0x90(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0042e830
void AmethystWake0x4dd4::VTable0x28()
{
	m_unk0x4cc4 = 1;
}

// FUNCTION: LEGORACERS 0x0042e840
void AmethystWake0x4dd4::VTable0x2c()
{
	m_unk0x4cc4 = 0;
}

// FUNCTION: LEGORACERS 0x0042e850
void AmethystWake0x4dd4::VTable0x24(undefined4 p_arg1, undefined4 p_arg2)
{
	m_unk0x4cb4 = p_arg1 - m_unk0x4cbc;
	m_unk0x4cb8 = p_arg2 - m_unk0x4cc0;
}

#include "menumanager.h"

#include "amberlens0x344.h"
#include "audio/musicinstance.h"
#include "audio/nullmusicgroup.h"
#include "audio/nullsoundgroup.h"
#include "golhashtable.h"
#include "golstream.h"
#include "imaginarytool0x368.h"
#include "input/inputmanager.h"
#include "input/keyboarddevice.h"

#include <golerror.h>
#include <stddef.h>

DECOMP_SIZE_ASSERT(MenuManager, 0x4dd4)
DECOMP_SIZE_ASSERT(AmberLens0x344, 0x344)

// GLOBAL: LEGORACERS 0x004c4918
MenuManager* g_menuManager = NULL;

// GLOBAL: LEGORACERS 0x004beb78
LegoFloat g_unk0x4beb78[7] = {0.04f, 0.04f, 0.04f, 0.04f, 0.39f, 0.4f, 0.04f};

// FUNCTION: LEGORACERS 0x0042b1e0
void MenuManager::Run(LegoRacers::Context* p_context)
{
	g_menuManager = new MenuManager();
	if (!g_menuManager) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_menuManager->Initialize(p_context);
	g_menuManager->Run();
	g_menuManager->Shutdown();

	if (g_menuManager) {
		delete g_menuManager;
	}
}

// FUNCTION: LEGORACERS 0x0042c5d0
MenuManager::MenuManager()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0042c910
MenuManager::~MenuManager()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0042cb00
void MenuManager::Reset()
{
	m_unk0x04.m_context = NULL;
	m_unk0x04.m_unk0x258.GetUnk0x1cfc().Reset();
	m_unk0x04.m_unk0x4b40.Reset();
	m_unk0x4cd4 = NULL;
	m_unk0x4cd8 = NULL;
	m_soundGroup = NULL;
	m_unk0x4dc8 = NULL;
	m_unk0x4cdc = NULL;
	m_unk0x4ce0 = NULL;
	m_unk0x4dd0 = FALSE;
	m_unk0x4d24.Reset();
	m_unk0x4d30.Reset();
	m_unk0x4d48.Clear();
}

// FUNCTION: LEGORACERS 0x0042cb90
LegoS32 MenuManager::Initialize(LegoRacers::Context* p_context)
{
	LegoBool32 flag = FALSE;
	m_unk0x04.m_context = p_context;
	m_unk0x4cd4 = p_context->m_golApp->GetGolExport();
	m_unk0x4cd8 = p_context->m_golApp->GetRenderer();

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	LoadMenuMaterials();
	FUN_0042d0e0();
	FUN_0042d300(m_unk0x04.m_unk0x258.GetUnk0x18e6(), TRUE);
	LoadMenuData();
	FUN_0042e1f0();
	FUN_0042cde0();
	InitializeInputBindings();
	InitializeAudio();
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
LegoS32 MenuManager::Shutdown()
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
		ShutdownAudio();
		FUN_0042d080();
		m_unk0x4cd8->VTable0x38();
		Reset();
	}

	return m_unk0x04.m_context == NULL;
}

// FUNCTION: LEGORACERS 0x0042cd60
void MenuManager::FUN_0042cd60()
{
	LegoChar name[8];
	CopperCrest0x40::InitStruct initStruct;

	m_menuNameStrings.CopyStringByIndex(&m_unk0x4d24, c_menuTextRendererObjectName);
	m_unk0x4d24.CopyToBuf8(name);

	initStruct.m_golExport = m_unk0x4cd4;
	initStruct.m_renderer = m_unk0x4cd8;
	initStruct.m_rendererObject = m_unk0x4cd8->FUN_004131a0(name);
	initStruct.m_inputManager = m_unk0x04.m_context->m_golApp->GetInputManager();
	initStruct.m_inputBindingContainer = m_unk0x04.m_inputBindings.GetUnk0x208();

	m_unk0x4c74.FUN_00469040(&initStruct);
}

// FUNCTION: LEGORACERS 0x0042cde0
void MenuManager::FUN_0042cde0()
{
	FloatyVec0xc position;
	FloatyVec0xc forward;
	FloatyVec0xc right;
	AmberLens0x344* lens = m_unk0x4cd4->VTable0x20();

	lens->m_unk0x08 = m_unk0x04.m_context->GetUnk0x0c();
	lens->m_flags |= AmberLens0x344::c_flagBit1;
	lens->m_unk0x10 = m_unk0x04.m_context->GetUnk0x10();
	lens->m_flags |= AmberLens0x344::c_flagBit1;
	lens->m_unk0x14 = m_unk0x04.m_context->GetUnk0x14();
	lens->m_flags |= AmberLens0x344::c_flagBit1;

	position.m_x = 0.0f;
	position.m_y = 0.0f;
	position.m_z = 0.0f;
	forward.m_x = 0.0f;
	forward.m_y = 0.0f;
	forward.m_z = -1.0f;
	right.m_x = 1.0f;
	right.m_y = 0.0f;
	right.m_z = 0.0f;

	lens->GetUnk0x04()->VTable0x44(&position);
	lens->m_flags |= AmberLens0x344::c_flagBit0;
	lens->GetUnk0x04()->VTable0x24(&right, &forward);
	lens->m_flags |= AmberLens0x344::c_flagBit0;
	m_unk0x4cd8->VTable0x20(lens);
}

// FUNCTION: LEGORACERS 0x0042ceb0
void MenuManager::ReleaseRendererObject()
{
	undefined4* object = m_unk0x4cd8->GetUnk0x0c();
	if (object) {
		m_unk0x4cd4->VTable0x54(object);
	}
}

// FUNCTION: LEGORACERS 0x0042ced0
void MenuManager::InitializeInputBindings()
{
	m_unk0x04.m_inputBindings.Initialize(m_unk0x04.m_context->m_golApp->GetInputManager());
}

// FUNCTION: LEGORACERS 0x0042cef0
void MenuManager::ShutdownInputBindings()
{
	m_unk0x04.m_inputBindings.Shutdown();
}

// FUNCTION: LEGORACERS 0x0042cf00
void MenuManager::InitializeAudio()
{
	m_unk0x04.m_unk0x4b40.m_musicGroup = m_unk0x04.m_context->m_soundManager->CreateMusicGroup();
	if (!m_unk0x04.m_unk0x4b40.m_musicGroup) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	m_unk0x04.m_unk0x4b40.m_musicGroup->Load("legomsc");
	LegoRacers::Context* context = m_unk0x04.m_context;
	m_unk0x04.m_unk0x4b40.m_musicInstance = NULL;
	m_soundGroup = context->GetSoundManager()->CreateSoundGroup();
	if (!m_soundGroup) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	m_soundGroup->Load("genc0r0");
	m_soundGroupBinding.SetSoundGroup(m_unk0x04.m_context->m_soundManager, m_soundGroup, FALSE);
}

// FUNCTION: LEGORACERS 0x0042cf90
void MenuManager::ShutdownAudio()
{
	if (m_unk0x04.m_unk0x4b40.m_musicInstance) {
		m_unk0x04.m_unk0x4b40.m_musicInstance->Stop();
		m_unk0x04.m_unk0x4b40.m_musicGroup->DestroyMusicInstance(m_unk0x04.m_unk0x4b40.m_musicInstance);
	}

	m_soundGroupBinding.ResetSoundGroup();
	m_soundGroup->Unload();

	if (m_unk0x04.m_unk0x4b40.m_musicGroup) {
		m_unk0x04.m_unk0x4b40.m_musicGroup->Unload();
	}

	m_unk0x04.m_context->GetSoundManager()->DestroySoundGroup(m_soundGroup);

	if (m_unk0x04.m_unk0x4b40.m_musicGroup) {
		m_unk0x04.m_context->GetSoundManager()->DestroyMusicGroup(m_unk0x04.m_unk0x4b40.m_musicGroup);
	}

	m_unk0x04.m_unk0x4b40.m_musicGroup = NULL;
	m_unk0x04.m_unk0x4b40.m_musicInstance = NULL;
}

// FUNCTION: LEGORACERS 0x0042d020
void MenuManager::LoadMenuMaterials()
{
	if (!m_unk0x4cdc) {
		m_unk0x4cdc = m_unk0x4cd4->VTable0x34();
	}

	if (!m_unk0x4ce0) {
		m_unk0x4ce0 = m_unk0x4cd4->VTable0x38();
	}

	m_unk0x4cdc->LoadMaterialDefinitions(m_unk0x4cd8, "GImages", m_unk0x04.m_context->m_unk0x18);
}

// FUNCTION: LEGORACERS 0x0042d080
void MenuManager::FUN_0042d080()
{
	if (m_unk0x4cdc) {
		m_unk0x4cdc->Clear();
		m_unk0x4cd4->VTable0x68(m_unk0x4cdc);
		m_unk0x4cdc = NULL;
	}

	if (m_unk0x4ce0) {
		m_unk0x4ce0->Clear();
		m_unk0x4cd4->VTable0x6c(m_unk0x4ce0);
		m_unk0x4ce0 = NULL;
	}
}

// STUB: LEGORACERS 0x0042d0e0
void MenuManager::FUN_0042d0e0()
{
	// TODO
	STUB(0x42d0e0);
}

// FUNCTION: LEGORACERS 0x0042d1e0
void MenuManager::LoadMenuData()
{
	GolStringTable* raceStrings = &m_raceStrings;
	LapisSigil0x14* raceList = &m_unk0x04.m_raceList;

	raceList->Load(raceStrings, "LEGORace", m_unk0x04.m_context->m_unk0x18);
	m_unk0x04.m_raceNames.Load(raceStrings, raceList, "LEGORace", m_unk0x04.m_context->m_unk0x18);
	m_unk0x4bcc.FUN_0047f4d0();
	m_unk0x04.m_menuAnimations.Allocate(2);

	GolStringTable* menuNameStrings = &m_menuNameStrings;
	menuNameStrings->UseOwnedBuffers();
	menuNameStrings->Load("menuname.srf");
}

// STUB: LEGORACERS 0x0042d260
void MenuManager::FUN_0042d260()
{
	// TODO
	STUB(0x42d260);
}

// STUB: LEGORACERS 0x0042d300
LegoBool MenuManager::FUN_0042d300(LegoU32, LegoBool)
{
	// TODO
	STUB(0x42d300);
	return FALSE;
}

// STUB: LEGORACERS 0x0042d3e0
void MenuManager::FUN_0042d3e0(LegoU16)
{
	// TODO
	STUB(0x42d3e0);
}

// FUNCTION: LEGORACERS 0x0042d510
void MenuManager::Run()
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
		m_unk0x04.m_context->GetSoundManager()->Update(frameDeltaMs);

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

			chain = &m_unk0x04.m_menuAnimations;
			chain->Update(frameDeltaMs);
			m_unk0x4cd8->VTable0x54(TRUE);
			m_unk0x4cd8->VTable0xec(6);
			m_unk0x4cd8->VTable0xe8(TRUE);

			if (m_unk0x4bd0.GetUnk0x9c() > 0) {
				m_unk0x4bd0.FUN_00468e20();
			}
			else {
				m_unk0x4c74.FUN_00469550();
			}

			chain->Draw(m_unk0x4cd8);
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
void MenuManager::FUN_0042d730()
{
	// TODO
	STUB(0x42d730);
}

// STUB: LEGORACERS 0x0042e1f0
void MenuManager::FUN_0042e1f0()
{
	// TODO
	STUB(0x42e1f0);
}

// FUNCTION: LEGORACERS 0x0042e450
LegoBool32 MenuManager::FUN_0042e450()
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
LegoS32 MenuManager::FUN_0042e490()
{
	// TODO
	STUB(0x42e490);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0042e680
LegoBool32 MenuManager::FUN_0042e680()
{
	LegoU8 flags = m_unk0x04.m_context->m_unk0x1e;

	if (!(flags & LegoRacers::Context::c_flagBit0)) {
		return FALSE;
	}

	m_unk0x04.m_context->m_unk0x1e = flags & ~LegoRacers::Context::c_flagBit0;

	PeridotTraceState0x438* state = &m_unk0x04.m_unk0x258.GetUnk0x18c4();
	LegoU32 index = m_unk0x04.m_raceNames.GetEntryIndexByName(m_unk0x04.m_context->m_raceSlots[0].m_unk0x08);
	if (index >= 12) {
		return FALSE;
	}

	if (state->FUN_0042f250(1 << index)) {
		if (state->FUN_0042f280()) {
			state->FUN_0042f200(0x80);
			m_unk0x04.m_context->m_unk0x1c = 0x1c;
		}

		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0042e700
void MenuManager::VTable0x00()
{
	m_unk0x4dd0 = FALSE;
	m_unk0x04.m_context->m_unk0x00 = FALSE;
}

// STUB: LEGORACERS 0x0042e720
void MenuManager::FUN_0042e720()
{
	// TODO
	STUB(0x42e720);
}

// FUNCTION: LEGORACERS 0x0042e810
void MenuManager::VTable0x1c(undefined4 p_unk0x04)
{
	if (m_unk0x4dc8) {
		m_unk0x4dc8->VTable0x90(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0042e830
void MenuManager::VTable0x28()
{
	m_unk0x4cc4 = 1;
}

// FUNCTION: LEGORACERS 0x0042e840
void MenuManager::VTable0x2c()
{
	m_unk0x4cc4 = 0;
}

// FUNCTION: LEGORACERS 0x0042e850
void MenuManager::VTable0x24(undefined4 p_arg1, undefined4 p_arg2)
{
	m_unk0x4cb4 = p_arg1 - m_unk0x4cbc;
	m_unk0x4cb8 = p_arg2 - m_unk0x4cc0;
}

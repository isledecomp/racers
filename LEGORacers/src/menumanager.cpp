#include "menumanager.h"

#include "amberlens0x344.h"
#include "audio/musicinstance.h"
#include "audio/nullmusicgroup.h"
#include "audio/nullsoundgroup.h"
#include "goldrawstate.h"
#include "golhashtable.h"
#include "golstream.h"
#include "imaginarytool0x368.h"
#include "input/inputmanager.h"
#include "input/keyboarddevice.h"

#include <golerror.h>
#include <stddef.h>
#include <string.h>

DECOMP_SIZE_ASSERT(MenuManager, 0x4dd4)
DECOMP_SIZE_ASSERT(MenuToolContext0x4bc8, 0x4bc8)
DECOMP_SIZE_ASSERT(MenuToolCreateParams0x30, 0x30)
DECOMP_SIZE_ASSERT(AmberLens0x344, 0x344)

// GLOBAL: LEGORACERS 0x004b05d8
LegoFloat g_unk0x4b05d8 = 1.0f / 255.0f;

// GLOBAL: LEGORACERS 0x004beb78
LegoFloat g_unk0x4beb78[7] = {0.04f, 0.04f, 0.04f, 0.04f, 0.39f, 0.4f, 0.04f};

// GLOBAL: LEGORACERS 0x004c4918
MenuManager* g_menuManager = NULL;

// GLOBAL: LEGORACERS 0x004c4928
DisplayDriverGuid g_displayDriverGuid = {0};

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
	m_imageTable = NULL;
	m_fontTable = NULL;
	m_unk0x4dd0 = FALSE;
	m_unk0x4d24.Reset();
	m_unk0x4d30.Reset();
	m_menuStyles.Clear();
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

	LoadMenuImages();
	FUN_0042d0e0();
	LoadLocalizedMenuResources(m_unk0x04.m_unk0x258.GetLanguageIndex(), TRUE);
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

	m_unk0x4bd0.FUN_00468af0(&m_unk0x4d98, 2, &m_unk0x4c74);
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
		UnloadMenuData();
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
	initStruct.m_rendererObject = m_unk0x4cd8->FindImageByName(name);
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
	AmberLens0x344* object = m_unk0x4cd8->GetUnk0x0c();
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
void MenuManager::LoadMenuImages()
{
	if (!m_imageTable) {
		m_imageTable = m_unk0x4cd4->VTable0x34();
	}

	if (!m_fontTable) {
		m_fontTable = m_unk0x4cd4->VTable0x38();
	}

	m_imageTable->LoadImageDefinitions(m_unk0x4cd8, "GImages", m_unk0x04.m_context->m_unk0x18);
}

// FUNCTION: LEGORACERS 0x0042d080
void MenuManager::FUN_0042d080()
{
	if (m_imageTable) {
		m_imageTable->Clear();
		m_unk0x4cd4->VTable0x68(m_imageTable);
		m_imageTable = NULL;
	}

	if (m_fontTable) {
		m_fontTable->Clear();
		m_unk0x4cd4->VTable0x6c(m_fontTable);
		m_fontTable = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0042d0e0
void MenuManager::FUN_0042d0e0()
{
	const GUID* displayDriverGuid = m_unk0x04.m_context->m_golApp->GetDrawState()->VTable0x38();
	GUID currentDisplayDriverGuid;

	if (!displayDriverGuid) {
		::memset(&currentDisplayDriverGuid, 0, sizeof(currentDisplayDriverGuid));
	}
	else {
		currentDisplayDriverGuid = *displayDriverGuid;
	}
	g_displayDriverGuid.m_guid = currentDisplayDriverGuid;

	m_unk0x04.m_unk0x258.FUN_004432e0(m_unk0x04.m_context->m_golApp->GetInputManager(), FALSE);

	if (m_unk0x04.m_context->m_unk0x1e & LegoRacers::Context::c_flagBit2) {
		PeridotTrace0x4a8* trace = &m_unk0x04.m_unk0x258.GetUnk0x108();
		::memcpy(
			m_unk0x04.m_unk0x258.GetUnk0x108().GetUnk0x24(),
			m_unk0x04.m_context->m_saveState.m_data,
			sizeof(m_unk0x04.m_context->m_saveState.m_data)
		);
		m_unk0x04.m_context->m_unk0x1e &= ~LegoRacers::Context::c_flagBit2;
		m_unk0x04.m_unk0x258.GetUnk0x18c4().FUN_0042eb60(trace, m_unk0x04.m_unk0x258.GetUnk0x18c4().GetUnk0x04());
	}

	LegoRacers::Context::SaveRecord* saveRecord = m_unk0x04.m_context->m_saveRecords;
	for (LegoU32 i = 0; i < m_unk0x04.m_context->m_saveRecordCount; i++, saveRecord++) {
		PeridotTraceBase0x24::Record* record = m_unk0x04.m_unk0x258.GetUnk0x108().FUN_0042b880();
		::memcpy(record->m_data, saveRecord->m_data, sizeof(LegoRacers::Context::SaveRecord));
	}
}

// FUNCTION: LEGORACERS 0x0042d1e0
void MenuManager::LoadMenuData()
{
	GolStringTable* raceStrings = &m_raceStrings;
	RaceDefinitionList* raceList = &m_unk0x04.m_raceList;

	raceList->Load(raceStrings, "LEGORace", m_unk0x04.m_context->m_unk0x18);
	m_unk0x04.m_raceNames.Load(raceStrings, raceList, "LEGORace", m_unk0x04.m_context->m_unk0x18);
	m_unk0x4bcc.Init();
	m_unk0x04.m_menuAnimations.Allocate(2);

	GolStringTable* menuNameStrings = &m_menuNameStrings;
	menuNameStrings->UseOwnedBuffers();
	menuNameStrings->Load("menuname.srf");
}

// FUNCTION: LEGORACERS 0x0042d260
void MenuManager::UnloadMenuData()
{
	m_unk0x04.m_raceNames.Clear();
	m_unk0x04.m_raceList.Clear();
	m_raceStrings.ReleaseOwnedBuffers();
	m_unk0x04.m_unk0x258.FUN_004436e0();
	m_unk0x04.m_pieceLibrary.Destroy();
	m_unk0x04.m_unk0x21f4.Destroy();
	m_unk0x04.m_unk0x4224.Destroy();
	m_unk0x04.m_unk0x4b40.ReleaseMenuResources();
	m_unk0x04.m_unk0x4ae0.ReleaseResources();
	m_unk0x04.m_unk0x437c.Destroy();
	m_unk0x4bcc.Shutdown();
	m_unk0x04.m_menuAnimations.Reset();
}

// FUNCTION: LEGORACERS 0x0042d300
LegoBool32 MenuManager::LoadLocalizedMenuResources(LegoU32 p_languageIndex, LegoBool32 p_forceReload)
{
	if (p_languageIndex != m_unk0x04.m_context->m_languageIndex || p_forceReload) {
		m_unk0x04.m_unk0x258.GetUnk0x18c4().SetLanguageResourcePath();
		m_unk0x04.m_context->m_languageIndex = p_languageIndex;

		GolStringTable* menuTextStrings = &m_menuTextStrings;
		menuTextStrings->UseOwnedBuffers();

		GolStringTable* raceStrings = &m_raceStrings;
		raceStrings->UseOwnedBuffers();

		menuTextStrings->Load("menutext.srf");
		raceStrings->Load("circuit.srf");
		m_fontTable->LoadFontDefinitions(m_unk0x4cd8, "GFonts", m_unk0x04.m_context->m_unk0x18);

		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA");
		}

		CeruleanEmperor0x4c::ResourceLoadParams params;
		params.m_renderer = m_unk0x4cd8;
		params.m_unk0x04 = 0;
		params.m_fileName = "gstyles";
		params.m_binary = m_unk0x04.m_context->m_unk0x18;
		p_forceReload = m_menuStyles.Load(&params);
	}

	return p_forceReload;
}

// FUNCTION: LEGORACERS 0x0042d3e0
void MenuManager::FUN_0042d3e0(LegoU16 p_menuId)
{
	LoadLocalizedMenuResources(m_unk0x04.m_unk0x258.GetLanguageIndex(), FALSE);

	m_menuNameStrings.CopyStringByIndex(&m_unk0x4d30, p_menuId);

	m_unk0x4d98.m_golExport = m_unk0x4cd4;
	m_unk0x4d98.m_renderer = m_unk0x4cd8;
	m_unk0x4d98.m_inputManager = m_unk0x04.m_context->m_golApp->GetInputManager();
	m_unk0x4d98.m_inputBindingContainer = m_unk0x04.m_inputBindings.GetUnk0x208();
	m_unk0x4d98.m_soundGroupBinding = &m_soundGroupBinding;
	m_unk0x4d98.m_menuStyles = &m_menuStyles;
	m_unk0x4d98.m_menuId = p_menuId;
	m_unk0x4d98.m_unk0x2c = m_unk0x04.m_context->m_unk0x18;
	m_unk0x4d98.m_unk0x20 = &m_unk0x4bd0;
	m_unk0x4d98.m_unk0x24 = m_unk0x4c74.GetUnk0x10();
	m_unk0x4d98.m_menuNameStrings = &m_menuNameStrings;
	m_unk0x4d98.m_menuTextStrings = &m_menuTextStrings;

	if (m_unk0x4dc8) {
		m_unk0x4cd8->VTable0xf4();
		m_unk0x4dc8->VTable0x74();

		if (m_unk0x4dc8) {
			delete m_unk0x4dc8;
		}
	}

	m_unk0x4dc8 = m_unk0x4bcc.FUN_0047f4e0(p_menuId);
	m_unk0x4c74.SetUnk0x54(m_unk0x4dc8);
	m_unk0x4dc8->VTable0x8c(&m_unk0x04, &m_unk0x4d98);
}

// FUNCTION: LEGORACERS 0x0042d510
void MenuManager::Run()
{
	ColorRGBA rendererState;
	Win32GolApp* golApp = m_unk0x04.m_context->m_golApp;
	StackOfLegoU16* stack;
	MenuAnimationList* menuAnimations;
	LegoU32 frameDeltaMs;
	LegoU16 previousMenu;

	rendererState.m_red = 0;
	rendererState.m_grn = 0;
	rendererState.m_blu = 0;
	rendererState.m_alp = 0;
	m_unk0x4cd8->VTable0x1c(rendererState);
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

			menuAnimations = &m_unk0x04.m_menuAnimations;
			menuAnimations->Update(frameDeltaMs);
			m_unk0x4cd8->VTable0x54(TRUE);
			m_unk0x4cd8->VTable0xec(6);
			m_unk0x4cd8->VTable0xe8(TRUE);

			if (m_unk0x4bd0.GetUnk0x9c() > 0) {
				m_unk0x4bd0.FUN_00468e20();
			}
			else {
				m_unk0x4c74.FUN_00469550();
			}

			menuAnimations->Draw(m_unk0x4cd8);
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

// FUNCTION: LEGORACERS 0x0042e1f0
void MenuManager::FUN_0042e1f0()
{
	LegoU32 driverIndex = 0;
	LegoFloat musicVolume;
	PeridotTraceState0x438& state = m_unk0x04.m_unk0x258.GetUnk0x18c4();

	m_unk0x04.m_context->m_unk0x100 = state.GetUnk0x0c();
	m_unk0x04.m_context->m_unk0x2c = state.GetUnk0x23();

	if (m_unk0x04.m_context->GetSoundManager() != NULL) {
		musicVolume = state.GetUnk0x1f() * g_unk0x4b05d8;
		m_unk0x04.m_context->GetSoundManager()->SetMusicVolumeScale(1.0f);

		if (m_unk0x04.m_unk0x4b40.m_musicInstance) {
			m_unk0x04.m_unk0x4b40.m_musicInstance->SetVolume(musicVolume);
		}
		m_unk0x04.m_context->GetSoundManager()->SetMusicVolumeScale(musicVolume);
		m_unk0x04.m_context->GetSoundManager()->SetVolumeScale(state.GetUnk0x20() * g_unk0x4b05d8);

		if (state.GetUnk0x21()) {
			m_unk0x04.m_context->GetSoundManager()->ClearUnk0x04Flag0x04();
		}
		else {
			m_unk0x04.m_context->GetSoundManager()->SetUnk0x04Flag0x04();
		}
	}

	GolDrawState* drawState = m_unk0x04.m_context->m_golApp->GetDrawState();
	DisplayDriverGuid savedDisplayDriverGuid;
	DisplayDriverGuid currentDisplayDriverGuid;
	DisplayDriverGuid driverGuid;
	const LegoChar* driverName = NULL;
	LegoU32 deviceIndex = 0;
	LegoU32 selectedDrawFlags = 0;
	state.FUN_0042f060(savedDisplayDriverGuid);

	const GUID* currentGuid = drawState->VTable0x38();
	if (!currentGuid) {
		drawState->VTable0x30(driverIndex, &currentDisplayDriverGuid.m_guid);
	}
	else {
		currentDisplayDriverGuid.m_guid = *currentGuid;
	}

	if (::memcmp(&savedDisplayDriverGuid, &currentDisplayDriverGuid, sizeof(GUID)) != 0) {
		do {
			drawState->VTable0x30(driverIndex, &driverGuid.m_guid);

			if (::memcmp(&driverGuid, &savedDisplayDriverGuid, sizeof(GUID)) == 0) {
				driverName = drawState->VTable0x14(driverIndex);
			}

			driverIndex++;
		} while (driverName == NULL && driverIndex < drawState->VTable0x10());

		if (driverName != NULL) {
			driverIndex--;

			while (deviceIndex < drawState->VTable0x1c(driverIndex) &&
				   !drawState->VTable0x28(driverIndex, deviceIndex)) {
				deviceIndex++;
			}

			if (deviceIndex < drawState->VTable0x1c(driverIndex)) {
				const LegoChar* deviceName = drawState->VTable0x20(driverIndex, deviceIndex);
				drawState->VTable0x0c(driverName, deviceName);
				selectedDrawFlags = GolDrawState::c_flagBit14;
			}
		}
	}

	LegoS32 width = drawState->m_width;
	LegoS32 height = drawState->m_height;

	if (::memcmp(&savedDisplayDriverGuid, &currentDisplayDriverGuid, sizeof(GUID)) != 0) {
		LegoU32 appFlags = m_unk0x04.m_context->m_golApp->GetFlags();

		if (!(appFlags & (GolApp::c_flagPrimaryDriver | GolApp::c_flagSelect3DDevice))) {
			LegoU32 displayFlags = 0;
			if (appFlags & GolApp::c_flagFullscreen) {
				displayFlags = GolApp::c_flagFullscreen;
			}
			if (appFlags & GolApp::c_flagBit4) {
				displayFlags |= GolApp::c_flagBit4;
			}
			if (appFlags & GolApp::c_flagBit8) {
				displayFlags |= GolApp::c_flagBit8;
			}

			drawState->VTable0x50();
			undefined4 bpp = drawState->m_bpp;
			drawState->VTable0x54(
				width,
				height,
				bpp,
				m_unk0x04.m_context->m_golApp->BuildDrawStateFlags(displayFlags) | selectedDrawFlags
			);
		}
	}
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
	m_unk0x4c74.SetCursorInside(1);
}

// FUNCTION: LEGORACERS 0x0042e840
void MenuManager::VTable0x2c()
{
	m_unk0x4c74.SetCursorInside(0);
}

// FUNCTION: LEGORACERS 0x0042e850
void MenuManager::VTable0x24(undefined4 p_arg1, undefined4 p_arg2)
{
	m_unk0x4c74.SetCursorPosition(p_arg1, p_arg2);
}

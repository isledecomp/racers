#include "menu/menumanager.h"

#include "app/cheatflags.h"
#include "app/win32golapp.h"
#include "audio/musicinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart.h"
#include "gdbvertexarray.h"
#include "golanimatedentity.h"
#include "golbmpwriterfile.h"
#include "golhashtable.h"
#include "golmaterial.h"
#include "golmateriallibrary.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golmodelmaterialtable.h"
#include "golmodelrenderstate.h"
#include "golname.h"
#include "golstream.h"
#include "goltexture.h"
#include "input/inputmanager.h"
#include "input/keyboarddevice.h"
#include "material/golimagedefinitionlist.h"
#include "material/goltexturelist.h"
#include "menu/menuscreenid.h"
#include "menu/screens/menugamescreen.h"
#include "race/racemoderunner.h"
#include "render/golcommondrawstate.h"
#include "render/goldrawstate.h"
#include "save/memorycardsavegame.h"
#include "surface/gold3dtexture.h"

#include <float.h>
#include <golerror.h>
#include <golstream.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(MenuManager, 0x4dd4)
DECOMP_SIZE_ASSERT(MenuGameContext, 0x4bc8)
DECOMP_SIZE_ASSERT(MenuScreenCreateParams, 0x30)
DECOMP_SIZE_ASSERT(GolCamera, 0x344)

// GLOBAL: LEGORACERS 0x004b05a0
const LegoFloat g_menuManagerMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b05d8
LegoFloat g_inv255 = 1.0f / 255.0f;

// GLOBAL: LEGORACERS 0x004beb78
LegoFloat g_menuViewportParams[7] = {0.04f, 0.04f, 0.04f, 0.04f, 0.39f, 0.4f, 0.04f};

// GLOBAL: LEGORACERS 0x004c4918
MenuManager* g_menuManager = NULL;

// GLOBAL: LEGORACERS 0x004c4928
DisplayDriverGuid g_displayDriverGuid = {0};

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

DECOMP_SIZE_ASSERT(RaceModeRunner, 0x37b8)

// GLOBAL: LEGORACERS 0x004c4914
RaceModeRunner* g_raceModeRunner = NULL;

// GLOBAL: LEGORACERS 0x004c491c
LegoChar g_raceNameBuffer[9];

// FUNCTION: LEGORACERS 0x0042b130
void RaceModeRunner::Run(LegoRacers::Context* p_context)
{
	g_raceModeRunner = new RaceModeRunner();
	if (!g_raceModeRunner) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_raceModeRunner->Initialize(p_context);
	g_raceModeRunner->Run();
	g_raceModeRunner->Shutdown();

	if (g_raceModeRunner) {
		delete g_raceModeRunner;
	}
}

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

// FUNCTION: LEGORACERS 0x0042c1b0
RaceModeRunner::RaceModeRunner()
{
	m_context = NULL;
}

// FUNCTION: LEGORACERS 0x0042c210
RaceModeRunner::~RaceModeRunner()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0042c280
void RaceModeRunner::Initialize(LegoRacers::Context* p_context)
{
	m_context = p_context;
	m_context->m_flags &= ~LegoRacers::Context::c_flagAbortRace;

	if (p_context->m_raceMode == LegoRacers::Context::c_raceModeTimeRace) {
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("GAMEDATA\\COMMON");
		}
		m_timeRaceManager.Initialize(
			p_context->m_golApp->GetRenderer(),
			p_context->m_golApp->GetGolExport(),
			p_context->m_useBinaryFiles,
			p_context->m_raceSlots[0].m_mirror
		);
	}

	if (p_context->m_flags & LegoRacers::Context::c_flagReturnToGarage) {
		p_context->m_nextMenuId = c_menuGarage;
	}
	else {
		p_context->m_nextMenuId = c_menuMainMenu;
	}

	p_context->m_currentRaceIndex = 0;
	p_context->m_golApp->ClearFileSourceDirectoryCaches();

	if (!p_context->m_raceMode) {
		m_circuitRunner.Initialize(m_context, &m_session);
		return;
	}

	InitializeRaceScene();
}

// FUNCTION: LEGORACERS 0x0042c330
void RaceModeRunner::Run()
{
	if (!m_context->m_raceMode) {
		m_circuitRunner.Run();
		m_context->m_flags &= ~LegoRacers::Context::c_flagBit7;
		return;
	}

	m_session.Run();
	m_timeRaceManager.Shutdown();
	m_context->m_flags &= ~LegoRacers::Context::c_flagBit7;
}

// FUNCTION: LEGORACERS 0x0042c380
void RaceModeRunner::Shutdown()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(NULL);
	}

	m_timeRaceManager.Shutdown();
	m_circuitRunner.Shutdown();
	m_session.Shutdown();
	ReleaseContextAssets();
	m_context = NULL;
}

// FUNCTION: LEGORACERS 0x0042c3d0
void RaceModeRunner::ReleaseContextAssets()
{
	if (!m_context) {
		return;
	}

	GolExport* golExport = m_context->m_golApp->GetGolExport();

	for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
		LegoRacers::Context::PlayerSetupSlot& slot = m_context->m_playerSetupSlots[i];

		if (slot.m_chassisName[0]) {
			if (slot.m_model) {
				golExport->DestroyModel(slot.m_model);
				slot.m_model = NULL;
			}
			if (slot.m_materials) {
				golExport->DestroyMaterialList(slot.m_materials);
				slot.m_materials = NULL;
			}
			if (slot.m_textures) {
				golExport->DestroyTextureList(slot.m_textures);
				slot.m_textures = NULL;
			}
			if (slot.m_altModel) {
				golExport->DestroyModel(slot.m_altModel);
				slot.m_altModel = NULL;
			}
			if (slot.m_altMaterials) {
				golExport->DestroyMaterialList(slot.m_altMaterials);
				slot.m_altMaterials = NULL;
			}
			if (slot.m_altTextures) {
				golExport->DestroyTextureList(slot.m_altTextures);
				slot.m_altTextures = NULL;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0042c4e0
void RaceModeRunner::InitializeRaceScene()
{
	sprintf(m_context->m_commonDataDirectory, "GAMEDATA\\COMMON");
	strcpy(m_context->m_gameDataDirectory, "GAMEDATA\\");
	memcpy(g_raceNameBuffer, m_context->m_raceSlots[0].m_folderName, sizeof(m_context->m_raceSlots[0].m_folderName));
	g_raceNameBuffer[sizeof(m_context->m_raceSlots[0].m_folderName)] = '\0';
	strcat(m_context->m_gameDataDirectory, g_raceNameBuffer);

	LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(gameDataDirectory);
	}

	if (m_timeRaceManager.GetScratchLapTimes()) {
		m_session.Initialize(m_context, g_raceNameBuffer, m_context->m_raceSlots[0].m_mirror, &m_timeRaceManager);
		return;
	}

	m_session.Initialize(m_context, g_raceNameBuffer, m_context->m_raceSlots[0].m_mirror, NULL);
}
// FUNCTION: LEGORACERS 0x0042c5d0
MenuManager::MenuManager()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0042c7e0
inline MenuGameContext::~MenuGameContext()
{
}

// FUNCTION: LEGORACERS 0x0042c910
MenuManager::~MenuManager()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0042cb00
void MenuManager::Reset()
{
	m_gameContext.m_context = NULL;
	m_gameContext.m_saveSystem.GetActiveRecord().Reset();
	m_gameContext.m_modelBuilder.Reset();
	m_golExport = NULL;
	m_renderer = NULL;
	m_soundGroup = NULL;
	m_activeScreen = NULL;
	m_imageTable = NULL;
	m_fontTable = NULL;
	m_running = FALSE;
	m_cursorImageName.Reset();
	m_screenName.Reset();
	m_menuStyles.Clear();
}

// FUNCTION: LEGORACERS 0x0042cb90
LegoS32 MenuManager::Initialize(LegoRacers::Context* p_context)
{
	LegoBool32 flag = FALSE;
	m_gameContext.m_context = p_context;
	m_golExport = p_context->m_golApp->GetGolExport();
	m_renderer = p_context->m_golApp->GetRenderer();

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	LoadMenuImages();
	InitializeSaveSystem();
	LoadLocalizedMenuResources(m_gameContext.m_saveSystem.GetLanguageIndex(), TRUE);
	LoadMenuData();
	ApplySettings();
	SetupCamera();
	InitializeInputBindings();
	InitializeAudio();
	InitializeInputDispatcher();

	if (CommitBestTimes()) {
		flag = TRUE;
	}
	if (ProcessRecordBeaten()) {
		flag = TRUE;
	}

	m_renderer->SetViewportRect(7, g_menuViewportParams);

	m_gameContext.m_menuStack.Allocate(10);
	m_gameContext.m_menuStack.Push(m_gameContext.m_context->m_nextMenuId);

	if (flag && HasPendingMemoryCardSaves()) {
		m_gameContext.m_menuStack.Push(c_menuSaveAll);
	}

	LegoU16 top = m_gameContext.m_menuStack.Peek();
	OpenScreen(top);

	m_dialog.Initialize(&m_screenCreateParams, 2, &m_inputDispatcher);
	return 1;
}

// FUNCTION: LEGORACERS 0x0042ccc0
LegoS32 MenuManager::Shutdown()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(NULL);
	}

	if (m_gameContext.m_context) {
		if (m_activeScreen) {
			m_activeScreen->Destroy();

			if (m_activeScreen) {
				delete m_activeScreen;
			}
		}

		m_inputDispatcher.Shutdown();
		m_dialog.Destroy();
		UnloadMenuData();
		ReleaseRendererObject();
		ShutdownInputBindings();
		ShutdownAudio();
		UnloadMenuImages();
		m_renderer->VTable0x38();
		Reset();
	}

	return m_gameContext.m_context == NULL;
}

// FUNCTION: LEGORACERS 0x0042cd60
void MenuManager::InitializeInputDispatcher()
{
	GolName name;
	MenuInputDispatcher::InitStruct initStruct;

	m_menuNameStrings.CopyStringByIndex(&m_cursorImageName, c_menuCursorImageName);
	m_cursorImageName.CopyToBuf8(name);

	initStruct.m_golExport = m_golExport;
	initStruct.m_renderer = m_renderer;
	initStruct.m_cursorImage = m_renderer->FindImageByName(name);
	initStruct.m_inputManager = m_gameContext.m_context->m_golApp->GetInputManager();
	initStruct.m_inputEvents = m_gameContext.m_inputBindings.GetInputEvents();

	m_inputDispatcher.Initialize(&initStruct);
}

// FUNCTION: LEGORACERS 0x0042cde0
void MenuManager::SetupCamera()
{
	GolVec3 position;
	GolVec3 forward;
	GolVec3 right;
	GolCamera* lens = m_golExport->CreateCamera();

	lens->m_fov = m_gameContext.m_context->GetCameraFov();
	lens->m_flags |= GolCamera::c_flagProjectionDirty;
	lens->m_nearClip = m_gameContext.m_context->GetCameraNearClip();
	lens->m_flags |= GolCamera::c_flagProjectionDirty;
	lens->m_farClip = m_gameContext.m_context->GetCameraFarClip();
	lens->m_flags |= GolCamera::c_flagProjectionDirty;

	position.m_x = 0.0f;
	position.m_y = 0.0f;
	position.m_z = 0.0f;
	forward.m_x = 0.0f;
	forward.m_y = 0.0f;
	forward.m_z = -1.0f;
	right.m_x = 1.0f;
	right.m_y = 0.0f;
	right.m_z = 0.0f;

	lens->GetTransform()->SetPosition(&position);
	lens->m_flags |= GolCamera::c_flagViewDirty;
	lens->GetTransform()->VTable0x24(&right, &forward);
	lens->m_flags |= GolCamera::c_flagViewDirty;
	m_renderer->SetCamera(lens);
}

// FUNCTION: LEGORACERS 0x0042ceb0
void MenuManager::ReleaseRendererObject()
{
	GolCamera* object = m_renderer->GetCurrentCamera();
	if (object) {
		m_golExport->DestroyCamera(object);
	}
}

// FUNCTION: LEGORACERS 0x0042ced0
void MenuManager::InitializeInputBindings()
{
	m_gameContext.m_inputBindings.Initialize(m_gameContext.m_context->m_golApp->GetInputManager());
}

// FUNCTION: LEGORACERS 0x0042cef0
void MenuManager::ShutdownInputBindings()
{
	m_gameContext.m_inputBindings.Shutdown();
}

// FUNCTION: LEGORACERS 0x0042cf00
void MenuManager::InitializeAudio()
{
	m_gameContext.m_modelBuilder.m_musicGroup = m_gameContext.m_context->m_soundManager->CreateMusicGroup();
	if (!m_gameContext.m_modelBuilder.m_musicGroup) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	m_gameContext.m_modelBuilder.m_musicGroup->Load("legomsc");
	LegoRacers::Context* context = m_gameContext.m_context;
	m_gameContext.m_modelBuilder.m_musicInstance = NULL;
	m_soundGroup = context->GetSoundManager()->CreateSoundGroup();
	if (!m_soundGroup) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	m_soundGroup->Load("genc0r0");
	m_soundGroupBinding.SetSoundGroup(m_gameContext.m_context->m_soundManager, m_soundGroup, FALSE);
}

// FUNCTION: LEGORACERS 0x0042cf90
void MenuManager::ShutdownAudio()
{
	if (m_gameContext.m_modelBuilder.m_musicInstance) {
		m_gameContext.m_modelBuilder.m_musicInstance->Stop();
		m_gameContext.m_modelBuilder.m_musicGroup->DestroyMusicInstance(m_gameContext.m_modelBuilder.m_musicInstance);
	}

	m_soundGroupBinding.ResetSoundGroup();
	m_soundGroup->Unload();

	if (m_gameContext.m_modelBuilder.m_musicGroup) {
		m_gameContext.m_modelBuilder.m_musicGroup->Unload();
	}

	m_gameContext.m_context->GetSoundManager()->DestroySoundGroup(m_soundGroup);

	if (m_gameContext.m_modelBuilder.m_musicGroup) {
		m_gameContext.m_context->GetSoundManager()->DestroyMusicGroup(m_gameContext.m_modelBuilder.m_musicGroup);
	}

	m_gameContext.m_modelBuilder.m_musicGroup = NULL;
	m_gameContext.m_modelBuilder.m_musicInstance = NULL;
}

// FUNCTION: LEGORACERS 0x0042d020
void MenuManager::LoadMenuImages()
{
	if (!m_imageTable) {
		m_imageTable = m_golExport->CreateImageList();
	}

	if (!m_fontTable) {
		m_fontTable = m_golExport->CreateFontTable();
	}

	m_imageTable->LoadImageDefinitions(m_renderer, "GImages", m_gameContext.m_context->m_useBinaryFiles);
}

// FUNCTION: LEGORACERS 0x0042d080
void MenuManager::UnloadMenuImages()
{
	if (m_imageTable) {
		m_imageTable->Clear();
		m_golExport->DestroyImageList(m_imageTable);
		m_imageTable = NULL;
	}

	if (m_fontTable) {
		m_fontTable->Clear();
		m_golExport->DestroyFontTable(m_fontTable);
		m_fontTable = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0042d0e0
void MenuManager::InitializeSaveSystem()
{
	const GUID* displayDriverGuid = m_gameContext.m_context->m_golApp->GetDrawState()->GetCurrentDriverGuid();
	GUID currentDisplayDriverGuid;

	if (!displayDriverGuid) {
		::memset(&currentDisplayDriverGuid, 0, sizeof(currentDisplayDriverGuid));
	}
	else {
		currentDisplayDriverGuid = *displayDriverGuid;
	}
	g_displayDriverGuid.m_guid = currentDisplayDriverGuid;

	m_gameContext.m_saveSystem.Initialize(m_gameContext.m_context->m_golApp->GetInputManager(), FALSE);

	if (m_gameContext.m_context->m_flags & LegoRacers::Context::c_flagSaveStateValid) {
		SaveGame* saveGame = &m_gameContext.m_saveSystem.GetSessionSave();
		::memcpy(
			m_gameContext.m_saveSystem.GetSessionSave().GetFileImage(),
			&m_gameContext.m_context->m_saveState,
			sizeof(m_gameContext.m_context->m_saveState)
		);
		m_gameContext.m_context->m_flags &= ~LegoRacers::Context::c_flagSaveStateValid;
		m_gameContext.m_saveSystem.GetGameState().LoadFromSaveGame(
			saveGame,
			m_gameContext.m_saveSystem.GetGameState().GetActiveSaveIndex()
		);
	}

	SaveRecordData* saveRecord = m_gameContext.m_context->m_saveRecords;
	for (LegoU32 i = 0; i < m_gameContext.m_context->m_saveRecordCount; i++, saveRecord++) {
		SaveRecordList::Record* record = m_gameContext.m_saveSystem.GetSessionSave().AllocateRecord();
		::memcpy(record->m_data, *saveRecord, sizeof(*saveRecord));
	}
}

// FUNCTION: LEGORACERS 0x0042d1e0
void MenuManager::LoadMenuData()
{
	GolStringTable* raceStrings = &m_raceStrings;
	CircuitDefinitionList* circuitList = &m_gameContext.m_circuitList;

	circuitList->Load(raceStrings, "LEGORace", m_gameContext.m_context->m_useBinaryFiles);
	m_gameContext.m_raceNames.Load(raceStrings, circuitList, "LEGORace", m_gameContext.m_context->m_useBinaryFiles);
	m_screenFactory.Initialize();
	m_gameContext.m_menuAnimations.Allocate(2);

	GolStringTable* menuNameStrings = &m_menuNameStrings;
	menuNameStrings->UseOwnedBuffers();
	menuNameStrings->Load("menuname.srf");
}

// FUNCTION: LEGORACERS 0x0042d260
void MenuManager::UnloadMenuData()
{
	m_gameContext.m_raceNames.Clear();
	m_gameContext.m_circuitList.Clear();
	m_raceStrings.ReleaseOwnedBuffers();
	m_gameContext.m_saveSystem.Destroy();
	m_gameContext.m_pieceLibrary.Destroy();
	m_gameContext.m_carBuildModel.Destroy();
	m_gameContext.m_colorTable.Destroy();
	m_gameContext.m_modelBuilder.ReleaseMenuResources();
	m_gameContext.m_partResources.ReleaseResources();
	m_gameContext.m_partCatalog.Destroy();
	m_screenFactory.Shutdown();
	m_gameContext.m_menuAnimations.Reset();
}

// FUNCTION: LEGORACERS 0x0042d300
LegoBool32 MenuManager::LoadLocalizedMenuResources(LegoU32 p_languageIndex, LegoBool32 p_forceReload)
{
	if (p_languageIndex != m_gameContext.m_context->m_languageIndex || p_forceReload) {
		m_gameContext.m_saveSystem.GetGameState().SetLanguageResourcePath();
		m_gameContext.m_context->m_languageIndex = p_languageIndex;

		GolStringTable* menuTextStrings = &m_menuTextStrings;
		menuTextStrings->UseOwnedBuffers();

		GolStringTable* raceStrings = &m_raceStrings;
		raceStrings->UseOwnedBuffers();

		menuTextStrings->Load("menutext.srf");
		raceStrings->Load("circuit.srf");
		m_fontTable->LoadFontDefinitions(m_renderer, "GFonts", m_gameContext.m_context->m_useBinaryFiles);

		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA");
		}

		MenuStyleTable::ResourceLoadParams params;
		params.m_renderer = m_renderer;
		params.m_fallback = 0;
		params.m_fileName = "gstyles";
		params.m_binary = m_gameContext.m_context->m_useBinaryFiles;
		p_forceReload = m_menuStyles.Load(&params);
	}

	return p_forceReload;
}

// FUNCTION: LEGORACERS 0x0042d3e0
void MenuManager::OpenScreen(LegoU16 p_menuId)
{
	LoadLocalizedMenuResources(m_gameContext.m_saveSystem.GetLanguageIndex(), FALSE);

	m_menuNameStrings.CopyStringByIndex(&m_screenName, p_menuId);

	m_screenCreateParams.m_golExport = m_golExport;
	m_screenCreateParams.m_renderer = m_renderer;
	m_screenCreateParams.m_inputManager = m_gameContext.m_context->m_golApp->GetInputManager();
	m_screenCreateParams.m_inputEvents = m_gameContext.m_inputBindings.GetInputEvents();
	m_screenCreateParams.m_soundGroupBinding = &m_soundGroupBinding;
	m_screenCreateParams.m_menuStyles = &m_menuStyles;
	m_screenCreateParams.m_menuId = p_menuId;
	m_screenCreateParams.m_useBinaryFiles = m_gameContext.m_context->m_useBinaryFiles;
	m_screenCreateParams.m_dialog = &m_dialog;
	m_screenCreateParams.m_cursor = m_inputDispatcher.GetCursor();
	m_screenCreateParams.m_menuNameStrings = &m_menuNameStrings;
	m_screenCreateParams.m_menuTextStrings = &m_menuTextStrings;

	if (m_activeScreen) {
		m_renderer->VTable0xf4();
		m_activeScreen->Destroy();

		if (m_activeScreen) {
			delete m_activeScreen;
		}
	}

	m_activeScreen = m_screenFactory.CreateScreen(p_menuId);
	m_inputDispatcher.SetActiveScreen(m_activeScreen);
	m_activeScreen->Initialize(&m_gameContext, &m_screenCreateParams);
}

// FUNCTION: LEGORACERS 0x0042d510
void MenuManager::Run()
{
	ColorRGBA rendererState;
	Win32GolApp* golApp = m_gameContext.m_context->m_golApp;
	StackOfLegoU16* stack;
	MenuAnimationList* menuAnimations;
	LegoU32 frameDeltaMs;
	LegoU16 previousMenu;

	rendererState.m_red = 0;
	rendererState.m_grn = 0;
	rendererState.m_blu = 0;
	rendererState.m_alp = 0;
	m_renderer->SetClearColor(rendererState);
	m_running = TRUE;

	while (m_running) {
		if (!golApp->Tick(this) || !m_running) {
			m_gameContext.m_context->m_running = FALSE;
			break;
		}

		frameDeltaMs = golApp->GetFrameDeltaMs();
		m_gameContext.m_context->GetSoundManager()->Update(frameDeltaMs);

		if (!golApp->IsDisabled()) {
			stack = &m_gameContext.m_menuStack;
			previousMenu = stack->Peek();
			m_gameContext.m_context->m_running = m_inputDispatcher.Update(frameDeltaMs);

			if (m_dialog.GetOpenCount() > 0) {
				m_dialog.Update(frameDeltaMs);
			}
			else {
				if (m_activeScreen->Update(frameDeltaMs)) {
					m_gameContext.m_context->m_running = FALSE;
				}
				if (!m_gameContext.m_context->m_running || !m_gameContext.m_menuStack.GetSize()) {
					break;
				}

				if (previousMenu != stack->Peek()) {
					OpenScreen(stack->Peek());
				}
			}

			menuAnimations = &m_gameContext.m_menuAnimations;
			menuAnimations->Update(frameDeltaMs);
			m_renderer->BeginFrame(TRUE);
			m_renderer->SelectViewport(6);
			m_renderer->DisableZBuffer(TRUE);

			if (m_dialog.GetOpenCount() > 0) {
				m_dialog.DrawCursors();
			}
			else {
				m_inputDispatcher.DrawCursor();
			}

			menuAnimations->Draw(m_renderer);
			m_renderer->EnableZBuffer();
			m_renderer->EndFrame();

			if (golApp->GetInputManager()->GetKeyboard()->GetButtonState(
					InputDevice::MakeEvent(InputDevice::c_sourceKeyboard, 0xb7)
				)) {
				TakeScreenshot();
			}

			golApp->PresentFrame();
		}
	}

	m_renderer->VTable0xf4();
	if (m_activeScreen) {
		m_activeScreen->Destroy();
		delete m_activeScreen;
		m_activeScreen = NULL;
	}

	if (m_gameContext.m_context->m_running) {
		PrepareRaceContext();
	}
}

// STUB: LEGORACERS 0x0042d730
void MenuManager::PrepareRaceContext()
{
	GolString string;
	GolRenderDevice::MaterialColor materialColor;
	GolRenderDevice::Light light;
	GolModelRenderState rendererState;
	LegoRacers::Context* context = m_gameContext.m_context;
	ActiveRecordBuffer& selectedRecords = m_gameContext.m_saveSystem.GetActiveRecord();

	if (context->m_raceMode == LegoRacers::Context::c_raceModeCircuit ||
		context->m_raceMode == LegoRacers::Context::c_raceModeTimeRace) {
		context->m_cheatFlags = 0;
	}

	for (LegoU32 saveIndex = 0; saveIndex < m_gameContext.m_saveSystem.GetSessionSave().GetRecordCount(); saveIndex++) {
		SaveRecordList::Record* record = m_gameContext.m_saveSystem.GetSessionSave().GetRecord(saveIndex);
		::memcpy(context->m_saveRecords[saveIndex], record->m_data, sizeof(context->m_saveRecords[saveIndex]));
	}
	context->m_saveRecordCount = m_gameContext.m_saveSystem.GetSessionSave().GetRecordCount();

	m_gameContext.m_saveSystem.GetGameState().WriteToSaveGame(&m_gameContext.m_saveSystem.GetSessionSave());
	::memcpy(
		&context->m_saveState,
		m_gameContext.m_saveSystem.GetSessionSave().GetFileImage(),
		sizeof(context->m_saveState)
	);
	context->m_flags |= LegoRacers::Context::c_flagSaveStateValid;

	if (!selectedRecords.GetSelectedRecordCount()) {
		context->m_racerCount = 6;
		context->m_raceMode = LegoRacers::Context::c_raceModeSingle;

		g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
		RaceNameEntry* raceName =
			m_gameContext.m_circuitList.GetEntries()[0].GetRaceNameEntry(g_randomTable[g_randomTableIndex] % 4);

		if (raceName) {
			::memcpy(
				context->m_raceSlots[0].m_raceName,
				raceName->GetName(),
				sizeof(context->m_raceSlots[0].m_raceName)
			);
			::memcpy(
				context->m_raceSlots[0].m_folderName,
				raceName->GetFolderName(),
				sizeof(context->m_raceSlots[0].m_folderName)
			);
			context->m_raceSlots[0].m_enabled = 1;
			context->m_raceSlots[0].m_mirror = raceName->GetMirror();
		}

		context->m_circuitName[0] = 'c';
		context->m_circuitName[1] = '0';
		context->m_circuitName[2] = '\0';
	}

	if ((context->m_cheatFlags & c_lnfrrrm) && ::strcmp(context->m_circuitName, "c6") == 0) {
		context->m_raceSlots[0].m_mirror = 1;
	}

	LegoRacers::Context::PlayerSetupSlot* slots = context->m_playerSetupSlots;
	if (context->m_racerCount > selectedRecords.GetSelectedRecordCount()) {
		CircuitDefinitionList::CircuitDefinition* circuitDefinition =
			static_cast<CircuitDefinitionList::CircuitDefinition*>(
				m_gameContext.m_circuitList.GetName(context->m_circuitName)
			);
		if (context->m_racerCount > circuitDefinition->GetDriverCount()) {
			context->m_racerCount = circuitDefinition->GetDriverCount();
		}

		LegoRacers::Context::PlayerSetupSlot* defaultSlot = slots;
		for (LegoU32 slotIndex = 0; slotIndex < context->m_racerCount; slotIndex++) {
			::memcpy(
				defaultSlot->m_driverName,
				circuitDefinition->GetDriverName(slotIndex),
				sizeof(defaultSlot->m_driverName)
			);
			defaultSlot->m_chassisName[0] = '\0';
			defaultSlot->m_slotState = 2;
			defaultSlot->m_cosmetics.m_hatIndex = 0;
			defaultSlot->m_cosmetics.m_faceIndex = 0;
			defaultSlot->m_cosmetics.m_torsoIndex = 0;
			defaultSlot->m_cosmetics.m_legIndex = 0;
			defaultSlot->m_cosmetics.m_expressionIndex = 0;
			defaultSlot->m_previewFaceIndex = 0;

			defaultSlot++;
		}
	}

	undefined2 emptyName[15];
	::memset(emptyName, 0, sizeof(emptyName));
	string.CopyFromBufSelection(emptyName, 14);

	slots = context->m_playerSetupSlots;
	context->m_playerCount = selectedRecords.GetSelectedRecordCount();
	if (selectedRecords.GetSelectedRecordCount() > context->m_racerCount) {
		context->m_racerCount = selectedRecords.GetSelectedRecordCount();
	}

	if (m_gameContext.m_carBuildModel.IsInitialized()) {
		m_gameContext.m_partSet.Clear();
		m_gameContext.m_carBuildModel.Destroy();
		m_gameContext.m_colorTable.Destroy();
		m_gameContext.m_pieceLibrary.Destroy();
	}

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PIECEDB");
	}

	m_gameContext.m_pieceLibrary.Load("LPieceLo.leg", context->m_useBinaryFiles);
	m_gameContext.m_colorTable.Initialize(m_golExport, m_renderer);
	m_gameContext.m_colorTable.LoadMaterials("LPieceLo.WDF", context->m_useBinaryFiles, FALSE);
	m_gameContext.m_colorTable.LoadColors("L_Colors.LEG", context->m_useBinaryFiles);
	m_gameContext.m_carBuildModel
		.Initialize(m_golExport, m_renderer, &m_gameContext.m_pieceLibrary, &m_gameContext.m_colorTable);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	ReleasePartResources();
	LoadPartResources(TRUE);

	LegoRacers::Context::PlayerSetupSlot* slot = slots;
	LegoRacers::Context::PlayerRecordState* recordState = context->m_playerRecordStates;
	for (LegoU32 selectedIndex = 0; selectedIndex < selectedRecords.GetSelectedRecordCount(); selectedIndex++) {
		SaveRecordList::Record* record = selectedRecords.GetSelectedRecord(selectedIndex);

		rendererState.ResetLighting();

		ColorRGBA color;
		color.m_alp = 0xff;
		color.m_red = 0x80;
		color.m_grn = 0x80;
		color.m_blu = 0x80;
		materialColor.SetColor(color);
		rendererState.SetAmbientColor(&materialColor);

		color.m_red = 0xff;
		color.m_grn = 0xff;
		color.m_blu = 0xff;
		light.SetColor(color);

		GolVec3 direction;
		direction.m_x = -1.0f;
		direction.m_y = 0.0f;
		direction.m_z = -1.0f;
		light.SetDirection(direction);
		rendererState.AddLight(&light);

		record->GetName(&string);
		string.CopyToString(slot->m_playerName);

		BuildPlayerCarModel(record, slot, &rendererState);
		BuildPlayerDriverModel(record, slot, &rendererState);

		recordState->m_recordSource = record->m_recordSource;
		recordState->m_saveIndex = record->m_saveIndex;
		recordState->m_recordId = record->m_recordId;

		record->GetCosmetics(&slot->m_cosmetics);
		slot->m_slotState = 0;

		slot++;
		recordState++;
	}

	for (LegoU32 clearIndex = 0; clearIndex < 4; clearIndex++) {
		context->m_bestLapTimes[clearIndex] = 0;
		context->m_bestLapHolders[clearIndex] = 0;
		context->m_bestRaceTimes[clearIndex] = 0;
		context->m_bestRaceHolders[clearIndex] = 0;
	}

	if (!selectedRecords.GetSelectedRecordCount()) {
		context->m_playerCount = m_gameContext.m_inputBindings.GetInputManager()->GetJoystickCount();
	}

	for (LegoU32 playerIndex = 0; playerIndex < context->m_playerCount; playerIndex++) {
		LegoU32 entryIndex = m_gameContext.m_saveSystem.GetGameState().GetSelectedInputBindingEntryIndex(playerIndex);
		m_gameContext.m_saveSystem.GetGameState()
			.GetInputBindingEntry(playerIndex, entryIndex, &context->m_inputBindings[playerIndex]);
	}

	if (!selectedRecords.GetSelectedRecordCount()) {
		context->m_playerCount = 0;
	}
}

// FUNCTION: LEGORACERS 0x0042dcb0
void MenuManager::BuildPlayerCarModel(
	SaveRecordList::Record* p_record,
	LegoRacers::Context::PlayerSetupSlot* p_slot,
	GolModelRenderState* p_rendererState
)
{
	GolModelEntity entity;

	p_slot->m_driverName[0] = '\0';
	p_record->GetChassisName(p_slot->m_chassisName);

	GolExport* golExport = m_gameContext.m_context->m_golApp->GetGolExport();
	GolD3DRenderDevice* renderer = golExport->GetDrawState()->m_currentRenderer;
	CarBuildModel& carBuildModel = m_gameContext.m_carBuildModel;

	if (!carBuildModel.Deserialize(p_record->GetCarData())) {
		GOL_FATALERROR_MESSAGE("Unable to load mesh builder with car data");
	}

	carBuildModel.UpdateOffset(0);
	carBuildModel.RebuildModel(0, 0xff);

	undefined4 textureCount;
	undefined4 materialCount;

	materialCount = carBuildModel.GetFinalMaterialCount();
	textureCount = carBuildModel.GetFinalTextureCount();

	GolMaterialLibrary* materials = p_slot->m_materials;
	if (materials) {
		golExport->DestroyMaterialList(materials);
		p_slot->m_materials = NULL;
	}
	p_slot->m_materials = golExport->CreateMaterialList();
	p_slot->m_materials->Initialize(renderer, materialCount);

	if (p_slot->m_textures) {
		golExport->DestroyTextureList(p_slot->m_textures);
		p_slot->m_textures = NULL;
	}
	p_slot->m_textures = golExport->CreateTextureList();
	p_slot->m_textures->Initialize(renderer, textureCount);

	if (p_slot->m_model) {
		golExport->DestroyModel(p_slot->m_model);
		p_slot->m_model = NULL;
	}
	p_slot->m_model = golExport->CreateModel();
	p_slot->m_model->Allocate(
		renderer,
		3,
		carBuildModel.GetFinalVertexCount(),
		carBuildModel.GetFinalTriangleCount(),
		carBuildModel.GetFinalGroupCount(),
		materialCount
	);

	carBuildModel.ExportModel(p_slot->m_model, p_slot->m_materials, p_slot->m_textures);
	p_slot->m_highPieceCount =
		carBuildModel.ComputeHighPieceCentroid(&p_slot->m_centroidX, &p_slot->m_centroidY, &p_slot->m_centroidZ);

	entity.SetPrimaryModel(p_slot->m_model, g_menuManagerMaxFloat);
	renderer->DrawModelEntityWithScopedState(&entity, p_rendererState, 0);
	entity.ResetModelState();

	GdbVertexArray* vertexArray;
	p_slot->m_model->GetVertexArray(&vertexArray);
	vertexArray->DiscardNormals();
	p_slot->m_model->AddFlagsWithBounds(1, FALSE);
}

// FUNCTION: LEGORACERS 0x0042de90
void MenuManager::LoadPartResources(LegoBool32 p_arg)
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PARTDB");
	}

	m_gameContext.m_partCatalog.Load("bodypart.pcf", m_gameContext.m_context->m_useBinaryFiles);

	DriverPartResources::LoadParams partParams;
	partParams.m_golExport = m_gameContext.m_context->m_golApp->GetGolExport();
	partParams.m_renderer = m_gameContext.m_context->m_golApp->GetRenderer();
	partParams.m_partCatalog = &m_gameContext.m_partCatalog;
	partParams.m_binary = m_gameContext.m_context->m_useBinaryFiles;
	partParams.m_textureBinaryMode = p_arg == FALSE;
	m_gameContext.m_partResources.Load(&partParams, p_arg);

	DriverModelBuilder::LoadParams menuParams;
	menuParams.m_golExport = partParams.m_golExport;
	menuParams.m_renderer = partParams.m_renderer;
	menuParams.m_menuId = 6;
	menuParams.m_partResources = &m_gameContext.m_partResources;
	m_gameContext.m_modelBuilder.Load(&menuParams);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x0042df70
void MenuManager::ReleasePartResources()
{
	m_gameContext.m_modelBuilder.ReleaseMenuResources();
	m_gameContext.m_partResources.ReleaseResources();
	m_gameContext.m_partCatalog.Destroy();
}

// STUB: LEGORACERS 0x0042dfa0
void MenuManager::BuildPlayerDriverModel(
	SaveRecordList::Record* p_record,
	LegoRacers::Context::PlayerSetupSlot* p_slot,
	GolModelRenderState* p_rendererState
)
{
	GolAnimatedEntity entity;
	CmbModelPart modelParts;
	LegoU32 textureCount;
	DriverCosmetics cosmetics;
	GolModelMaterialTable* materialTable;
	LegoU32 materialCount;
	GolMaterialParams params;

	p_record->GetCosmetics(&cosmetics);

	DriverModelBuilder* modelBuilder = &m_gameContext.m_modelBuilder;
	p_slot->m_altModel = modelBuilder->BuildDriverModel(&cosmetics, NULL, 3);
	p_slot->m_previewFaceIndex = cosmetics.m_faceIndex;
	materialTable = p_slot->m_altModel->GetMaterialTable();
	textureCount = 0;

	for (materialCount = 0; materialCount < materialTable->GetCount(); materialCount++) {
		GolMaterial* material = materialTable->GetMaterial(materialCount);
		if (material == NULL) {
			break;
		}

		if (material->GetFlags() & GolMaterial::c_flagTextured) {
			textureCount++;
		}
	}

	GolExport* golExport = m_gameContext.m_context->m_golApp->GetGolExport();
	GolD3DRenderDevice* renderer = golExport->GetDrawState()->m_currentRenderer;

	p_slot->m_altMaterials = golExport->CreateMaterialList();
	p_slot->m_altMaterials->Initialize(renderer, materialCount);
	p_slot->m_altTextures = golExport->CreateTextureList();
	p_slot->m_altTextures->Initialize(renderer, textureCount);

	textureCount = 0;
	for (LegoU32 materialIndex = 0; materialIndex < materialCount; materialIndex++) {
		GolMaterial* sourceMaterial = materialTable->GetMaterial(materialIndex);
		sourceMaterial->CopyParamsTo(&params);

		if (sourceMaterial->GetFlags() & GolMaterial::c_flagTextured) {
			GolD3DTexture* texture = p_slot->m_altTextures->GetItem(textureCount++);
			texture->SetName(static_cast<GolD3DTexture*>(params.m_texture)->GetName());
			texture->SetSourceTextureDefinition(
				params.m_texture->GetMipmapCount(),
				params.m_texture->GetTextureFlags(),
				params.m_texture->GetColorKey()
			);
			params.m_texture = texture;
		}
		else {
			params.m_texture = NULL;
		}

		params.m_flags &= ~GolMaterial::c_flagCreated;
		GolMaterial* material = p_slot->m_altMaterials->GetItem(materialIndex);
		material->SetParams(renderer, params);
		materialTable->SetEntry(materialIndex, material);
	}

	entity.SetModel(p_slot->m_altModel, modelBuilder->GetBodySceneNode(&cosmetics), &modelParts, g_menuManagerMaxFloat);
	renderer->DrawModelEntityWithScopedState(&entity, p_rendererState, 0);
	entity.ResetModelState();

	GdbVertexArray* vertexArray;
	p_slot->m_altModel->GetVertexArray(&vertexArray);
	vertexArray->DiscardNormals();
	p_slot->m_altModel->AddFlagsWithBounds(1, FALSE);
}

// FUNCTION: LEGORACERS 0x0042e1f0
void MenuManager::ApplySettings()
{
	LegoU32 driverIndex = 0;
	LegoFloat musicVolume;
	GameState& state = m_gameContext.m_saveSystem.GetGameState();

	m_gameContext.m_context->m_racerCount = state.GetRacerCount();
	m_gameContext.m_context->m_lapCount = state.GetLapCount();

	if (m_gameContext.m_context->GetSoundManager() != NULL) {
		musicVolume = state.GetMusicVolume() * g_inv255;
		m_gameContext.m_context->GetSoundManager()->SetMusicVolumeScale(1.0f);

		if (m_gameContext.m_modelBuilder.m_musicInstance) {
			m_gameContext.m_modelBuilder.m_musicInstance->SetVolume(musicVolume);
		}
		m_gameContext.m_context->GetSoundManager()->SetMusicVolumeScale(musicVolume);
		m_gameContext.m_context->GetSoundManager()->SetVolumeScale(state.GetSoundVolume() * g_inv255);

		if (state.GetStereo()) {
			m_gameContext.m_context->GetSoundManager()->ClearMonoFlag();
		}
		else {
			m_gameContext.m_context->GetSoundManager()->SetMonoFlag();
		}
	}

	GolDrawState* drawState = m_gameContext.m_context->m_golApp->GetDrawState();
	DisplayDriverGuid savedDisplayDriverGuid;
	DisplayDriverGuid currentDisplayDriverGuid;
	DisplayDriverGuid driverGuid;
	const LegoChar* driverName = NULL;
	LegoU32 deviceIndex = 0;
	LegoU32 selectedDrawFlags = 0;

	state.GetDisplayDriverGuid(savedDisplayDriverGuid);

	const GUID* currentGuid = drawState->GetCurrentDriverGuid();
	if (!currentGuid) {
		drawState->GetDriverGuid(driverIndex, &currentDisplayDriverGuid.m_guid);
	}
	else {
		currentDisplayDriverGuid.m_guid = *currentGuid;
	}

	if (::memcmp(&savedDisplayDriverGuid, &currentDisplayDriverGuid, sizeof(GUID)) != 0) {
		do {
			drawState->GetDriverGuid(driverIndex, &driverGuid.m_guid);

			if (::memcmp(&driverGuid, &savedDisplayDriverGuid, sizeof(GUID)) == 0) {
				driverName = drawState->GetDriverDescription(driverIndex);
			}

			driverIndex++;
		} while (driverName == NULL && driverIndex < drawState->GetDriverCount());

		if (driverName != NULL) {
			driverIndex--;

			while (deviceIndex < drawState->GetDeviceCount(driverIndex) &&
				   !drawState->IsDeviceHwAccelerated(driverIndex, deviceIndex)) {
				deviceIndex++;
			}

			if (deviceIndex < drawState->GetDeviceCount(driverIndex)) {
				const LegoChar* deviceName = drawState->GetDeviceName(driverIndex, deviceIndex);
				drawState->SelectDevice(driverName, deviceName);
				selectedDrawFlags = GolDrawState::c_flagBit14;
			}
		}
	}

	LegoS32 width = drawState->m_width;
	LegoS32 height = drawState->m_height;

	if (::memcmp(&savedDisplayDriverGuid, &currentDisplayDriverGuid, sizeof(GUID)) != 0) {
		LegoU32 appFlags = m_gameContext.m_context->m_golApp->GetFlags();

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

			drawState->ReleaseDisplay();
			undefined4 bpp = drawState->m_bpp;
			drawState->CreateDisplay(
				width,
				height,
				bpp,
				m_gameContext.m_context->m_golApp->BuildDrawStateFlags(displayFlags) | selectedDrawFlags
			);
		}
	}
}

// FUNCTION: LEGORACERS 0x0042e450
LegoBool32 MenuManager::HasPendingMemoryCardSaves()
{
	MemoryCardSaveGame* entry = m_gameContext.m_saveSystem.GetMemoryCardSaves();

	for (LegoU32 i = 0; i < m_gameContext.m_saveSystem.GetMemoryCardSaveCount(); i++, entry++) {
		if (entry->IsUsable()) {
			return TRUE;
		}
	}

	return FALSE;
}

// STUB: LEGORACERS 0x0042e490
LegoS32 MenuManager::CommitBestTimes()
{
	LegoU8 flags = m_gameContext.m_context->m_flags;

	if (!(flags & LegoRacers::Context::c_flagBestTimesPending)) {
		return FALSE;
	}

	m_gameContext.m_context->m_flags = flags & ~LegoRacers::Context::c_flagBestTimesPending;
	LegoRacers::Context* context = m_gameContext.m_context;

	GolString string;
	LegoChar name[15];
	undefined2 wideName[15];
	LegoS32 result = FALSE;
	LegoU32 raceIndex = 0;

	for (LegoS32 i = 0; i < 4; i++) {
		LegoBool32 hasRaceIndex = FALSE;

		if (context->m_bestLapTimes[i]) {
			raceIndex = m_gameContext.m_raceNames.GetEntryIndexByName(context->m_raceSlots[i].m_raceName);
			hasRaceIndex = TRUE;

			const LegoChar* sourceName = context->m_playerSetupSlots[context->m_bestLapHolders[i]].m_playerName;
			::strncpy(name, sourceName, sizeof(name) - 1);
			name[sizeof(name) - 1] = '\0';
			GolString::CopyStringToBuf16(sourceName, wideName);
			string.CopyFromBufSelection(wideName, sizeof(name) - 1);

			if (m_gameContext.m_saveSystem.GetGameState()
					.SetBestTime(raceIndex, 0, context->m_bestLapTimes[i], &string)) {
				result = TRUE;
			}
		}

		if (context->m_bestRaceTimes[i]) {
			if (!hasRaceIndex) {
				raceIndex = m_gameContext.m_raceNames.GetEntryIndexByName(context->m_raceSlots[i].m_raceName);
			}

			const LegoChar* sourceName = context->m_playerSetupSlots[context->m_bestRaceHolders[i]].m_playerName;
			::strncpy(name, sourceName, sizeof(name) - 1);
			name[sizeof(name) - 1] = '\0';
			GolString::CopyStringToBuf16(sourceName, wideName);
			string.CopyFromBufSelection(wideName, sizeof(name) - 1);

			if (m_gameContext.m_saveSystem.GetGameState()
					.SetBestTime(raceIndex, 1, context->m_bestRaceTimes[i], &string)) {
				result = TRUE;
			}
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0042e680
LegoBool32 MenuManager::ProcessRecordBeaten()
{
	LegoU8 flags = m_gameContext.m_context->m_flags;

	if (!(flags & LegoRacers::Context::c_flagRecordBeaten)) {
		return FALSE;
	}

	m_gameContext.m_context->m_flags = flags & ~LegoRacers::Context::c_flagRecordBeaten;

	GameState* state = &m_gameContext.m_saveSystem.GetGameState();
	LegoU32 index = m_gameContext.m_raceNames.GetEntryIndexByName(m_gameContext.m_context->m_raceSlots[0].m_raceName);
	if (index >= 12) {
		return FALSE;
	}

	if (state->UnlockRace(1 << index)) {
		if (state->AreAllRacesUnlocked()) {
			state->UnlockParts(0x80);
			m_gameContext.m_context->m_nextMenuId = 0x1c;
		}

		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0042e700
void MenuManager::OnCloseRequested()
{
	m_running = FALSE;
	m_gameContext.m_context->m_running = FALSE;
}

// FUNCTION: LEGORACERS 0x0042e720
void MenuManager::TakeScreenshot()
{
	GolBmpWriterFile bmpWriter;
	GolHashTable::Entry* currentEntry;
	LegoChar fileName[32];
	LegoU32 screenshotIndex;

	if (g_hashTable) {
		currentEntry = g_hashTable->GetCurrentEntry();
		g_hashTable->SetCurrentEntryFromString(NULL);
	}
	else {
		currentEntry = NULL;
	}

	for (screenshotIndex = 0; screenshotIndex <= c_maxScreenshotIndex; screenshotIndex++) {
		sprintf(fileName, "LEGO%d.bmp", screenshotIndex);
		if (GolStream::FindFile(fileName) != GolStream::e_ioSuccess) {
			break;
		}
	}

	if (screenshotIndex <= c_maxScreenshotIndex) {
		bmpWriter.Open(fileName);
		bmpWriter.WriteSurface(m_renderer->GetRenderTargetInfo());
		bmpWriter.Destroy();

		if (g_hashTable) {
			g_hashTable->SetCurrentEntry(currentEntry);
		}
	}
}

// FUNCTION: LEGORACERS 0x0042e810
void MenuManager::OnChar(undefined4 p_char)
{
	if (m_activeScreen) {
		m_activeScreen->OnChar(p_char);
	}
}

// FUNCTION: LEGORACERS 0x0042e830
void MenuManager::OnCursorInside()
{
	m_inputDispatcher.SetCursorInside(1);
}

// FUNCTION: LEGORACERS 0x0042e840
void MenuManager::OnCursorOutside()
{
	m_inputDispatcher.SetCursorInside(0);
}

// FUNCTION: LEGORACERS 0x0042e850
void MenuManager::OnCursorMoved(undefined4 p_x, undefined4 p_y)
{
	m_inputDispatcher.SetCursorPosition(p_x, p_y);
}

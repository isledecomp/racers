#include "menu/menumanager.h"

#include "audio/musicinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart0x34.h"
#include "golanimatedentity.h"
#include "golbmpwriterfile.h"
#include "golhashtable.h"
#include "golmodelentity.h"
#include "golname.h"
#include "golstream.h"
#include "input/inputmanager.h"
#include "input/keyboarddevice.h"
#include "material/awakekite0x20.h"
#include "material/duskwindbananarelic0x24.h"
#include "material/golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "menu/menuscreenid.h"
#include "menu/screens/menugamescreen.h"
#include "mesh/gdbvertexarray0xc.h"
#include "mesh/golmodelbase.h"
#include "mesh/golmodelmaterialtable.h"
#include "render/golcommondrawstate.h"
#include "render/goldrawstate.h"
#include "surface/golddune0x38.h"
#include "surface/purpledune0x7c.h"
#include "util/amethystbreeze0x104.h"

#include <float.h>
#include <golerror.h>
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
LegoFloat g_unk0x4b05d8 = 1.0f / 255.0f;

// GLOBAL: LEGORACERS 0x004beb78
LegoFloat g_unk0x4beb78[7] = {0.04f, 0.04f, 0.04f, 0.04f, 0.39f, 0.4f, 0.04f};

// GLOBAL: LEGORACERS 0x004c4918
MenuManager* g_menuManager = NULL;

// GLOBAL: LEGORACERS 0x004c4928
DisplayDriverGuid g_displayDriverGuid = {0};

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

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
	m_unk0x04.m_saveSystem.GetActiveRecord().Reset();
	m_unk0x04.m_modelBuilder.Reset();
	m_golExport = NULL;
	m_renderer = NULL;
	m_soundGroup = NULL;
	m_unk0x4dc8 = NULL;
	m_imageTable = NULL;
	m_fontTable = NULL;
	m_running = FALSE;
	m_unk0x4d24.Reset();
	m_unk0x4d30.Reset();
	m_menuStyles.Clear();
}

// FUNCTION: LEGORACERS 0x0042cb90
LegoS32 MenuManager::Initialize(LegoRacers::Context* p_context)
{
	LegoBool32 flag = FALSE;
	m_unk0x04.m_context = p_context;
	m_golExport = p_context->m_golApp->GetGolExport();
	m_renderer = p_context->m_golApp->GetRenderer();

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	LoadMenuImages();
	FUN_0042d0e0();
	LoadLocalizedMenuResources(m_unk0x04.m_saveSystem.GetLanguageIndex(), TRUE);
	LoadMenuData();
	FUN_0042e1f0();
	FUN_0042cde0();
	InitializeInputBindings();
	InitializeAudio();
	InitializeTextRenderer();

	if (FUN_0042e490()) {
		flag = TRUE;
	}
	if (FUN_0042e680()) {
		flag = TRUE;
	}

	m_renderer->VTable0x34(7, g_unk0x4beb78);

	m_unk0x04.m_menuStack.Allocate(10);
	m_unk0x04.m_menuStack.Push(m_unk0x04.m_context->m_nextMenuId);

	if (flag && FUN_0042e450()) {
		m_unk0x04.m_menuStack.Push(c_menuSaveAll);
	}

	LegoU16 top = m_unk0x04.m_menuStack.Peek();
	FUN_0042d3e0(top);

	m_unk0x4bd0.FUN_00468af0(&m_unk0x4d98, 2, &m_textRenderer);
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
			m_unk0x4dc8->Destroy();

			if (m_unk0x4dc8) {
				delete m_unk0x4dc8;
			}
		}

		m_textRenderer.VTable0x0c();
		m_unk0x4bd0.FUN_00468ab0();
		UnloadMenuData();
		ReleaseRendererObject();
		ShutdownInputBindings();
		ShutdownAudio();
		UnloadMenuImages();
		m_renderer->VTable0x38();
		Reset();
	}

	return m_unk0x04.m_context == NULL;
}

// FUNCTION: LEGORACERS 0x0042cd60
void MenuManager::InitializeTextRenderer()
{
	GolName name;
	CopperCrest0x40::InitStruct initStruct;

	m_menuNameStrings.CopyStringByIndex(&m_unk0x4d24, c_menuTextRendererObjectName);
	m_unk0x4d24.CopyToBuf8(name);

	initStruct.m_golExport = m_golExport;
	initStruct.m_renderer = m_renderer;
	initStruct.m_rendererObject = m_renderer->FindImageByName(name);
	initStruct.m_inputManager = m_unk0x04.m_context->m_golApp->GetInputManager();
	initStruct.m_inputEvents = m_unk0x04.m_inputBindings.GetUnk0x208();

	m_textRenderer.FUN_00469040(&initStruct);
}

// FUNCTION: LEGORACERS 0x0042cde0
void MenuManager::FUN_0042cde0()
{
	GolVec3 position;
	GolVec3 forward;
	GolVec3 right;
	GolCamera* lens = m_golExport->VTable0x20();

	lens->m_unk0x08 = m_unk0x04.m_context->GetUnk0x0c();
	lens->m_flags |= GolCamera::c_flagBit1;
	lens->m_unk0x10 = m_unk0x04.m_context->GetUnk0x10();
	lens->m_flags |= GolCamera::c_flagBit1;
	lens->m_unk0x14 = m_unk0x04.m_context->GetUnk0x14();
	lens->m_flags |= GolCamera::c_flagBit1;

	position.m_x = 0.0f;
	position.m_y = 0.0f;
	position.m_z = 0.0f;
	forward.m_x = 0.0f;
	forward.m_y = 0.0f;
	forward.m_z = -1.0f;
	right.m_x = 1.0f;
	right.m_y = 0.0f;
	right.m_z = 0.0f;

	lens->GetUnk0x04()->SetPosition(&position);
	lens->m_flags |= GolCamera::c_flagBit0;
	lens->GetUnk0x04()->VTable0x24(&right, &forward);
	lens->m_flags |= GolCamera::c_flagBit0;
	m_renderer->VTable0x20(lens);
}

// FUNCTION: LEGORACERS 0x0042ceb0
void MenuManager::ReleaseRendererObject()
{
	GolCamera* object = m_renderer->GetUnk0x0c();
	if (object) {
		m_golExport->VTable0x54(object);
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
	m_unk0x04.m_modelBuilder.m_musicGroup = m_unk0x04.m_context->m_soundManager->CreateMusicGroup();
	if (!m_unk0x04.m_modelBuilder.m_musicGroup) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	m_unk0x04.m_modelBuilder.m_musicGroup->Load("legomsc");
	LegoRacers::Context* context = m_unk0x04.m_context;
	m_unk0x04.m_modelBuilder.m_musicInstance = NULL;
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
	if (m_unk0x04.m_modelBuilder.m_musicInstance) {
		m_unk0x04.m_modelBuilder.m_musicInstance->Stop();
		m_unk0x04.m_modelBuilder.m_musicGroup->DestroyMusicInstance(m_unk0x04.m_modelBuilder.m_musicInstance);
	}

	m_soundGroupBinding.ResetSoundGroup();
	m_soundGroup->Unload();

	if (m_unk0x04.m_modelBuilder.m_musicGroup) {
		m_unk0x04.m_modelBuilder.m_musicGroup->Unload();
	}

	m_unk0x04.m_context->GetSoundManager()->DestroySoundGroup(m_soundGroup);

	if (m_unk0x04.m_modelBuilder.m_musicGroup) {
		m_unk0x04.m_context->GetSoundManager()->DestroyMusicGroup(m_unk0x04.m_modelBuilder.m_musicGroup);
	}

	m_unk0x04.m_modelBuilder.m_musicGroup = NULL;
	m_unk0x04.m_modelBuilder.m_musicInstance = NULL;
}

// FUNCTION: LEGORACERS 0x0042d020
void MenuManager::LoadMenuImages()
{
	if (!m_imageTable) {
		m_imageTable = m_golExport->VTable0x34();
	}

	if (!m_fontTable) {
		m_fontTable = m_golExport->CreateFontTable();
	}

	m_imageTable->LoadImageDefinitions(m_renderer, "GImages", m_unk0x04.m_context->m_unk0x18);
}

// FUNCTION: LEGORACERS 0x0042d080
void MenuManager::UnloadMenuImages()
{
	if (m_imageTable) {
		m_imageTable->Clear();
		m_golExport->VTable0x68(m_imageTable);
		m_imageTable = NULL;
	}

	if (m_fontTable) {
		m_fontTable->Clear();
		m_golExport->DestroyFontTable(m_fontTable);
		m_fontTable = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0042d0e0
void MenuManager::FUN_0042d0e0()
{
	const GUID* displayDriverGuid = m_unk0x04.m_context->m_golApp->GetDrawState()->GetCurrentDriverGuid();
	GUID currentDisplayDriverGuid;

	if (!displayDriverGuid) {
		::memset(&currentDisplayDriverGuid, 0, sizeof(currentDisplayDriverGuid));
	}
	else {
		currentDisplayDriverGuid = *displayDriverGuid;
	}
	g_displayDriverGuid.m_guid = currentDisplayDriverGuid;

	m_unk0x04.m_saveSystem.Initialize(m_unk0x04.m_context->m_golApp->GetInputManager(), FALSE);

	if (m_unk0x04.m_context->m_unk0x1e & LegoRacers::Context::c_flagBit2) {
		SaveGame* saveGame = &m_unk0x04.m_saveSystem.GetSessionSave();
		::memcpy(
			m_unk0x04.m_saveSystem.GetSessionSave().GetFileImage(),
			&m_unk0x04.m_context->m_saveState,
			sizeof(m_unk0x04.m_context->m_saveState)
		);
		m_unk0x04.m_context->m_unk0x1e &= ~LegoRacers::Context::c_flagBit2;
		m_unk0x04.m_saveSystem.GetGameState().FUN_0042eb60(
			saveGame,
			m_unk0x04.m_saveSystem.GetGameState().GetActiveSaveIndex()
		);
	}

	SaveRecordData* saveRecord = m_unk0x04.m_context->m_saveRecords;
	for (LegoU32 i = 0; i < m_unk0x04.m_context->m_saveRecordCount; i++, saveRecord++) {
		SaveRecordList::Record* record = m_unk0x04.m_saveSystem.GetSessionSave().AllocateRecord();
		::memcpy(record->m_data, *saveRecord, sizeof(*saveRecord));
	}
}

// FUNCTION: LEGORACERS 0x0042d1e0
void MenuManager::LoadMenuData()
{
	GolStringTable* raceStrings = &m_raceStrings;
	CircuitDefinitionList* circuitList = &m_unk0x04.m_circuitList;

	circuitList->Load(raceStrings, "LEGORace", m_unk0x04.m_context->m_unk0x18);
	m_unk0x04.m_raceNames.Load(raceStrings, circuitList, "LEGORace", m_unk0x04.m_context->m_unk0x18);
	m_unk0x4bcc.Initialize();
	m_unk0x04.m_menuAnimations.Allocate(2);

	GolStringTable* menuNameStrings = &m_menuNameStrings;
	menuNameStrings->UseOwnedBuffers();
	menuNameStrings->Load("menuname.srf");
}

// FUNCTION: LEGORACERS 0x0042d260
void MenuManager::UnloadMenuData()
{
	m_unk0x04.m_raceNames.Clear();
	m_unk0x04.m_circuitList.Clear();
	m_raceStrings.ReleaseOwnedBuffers();
	m_unk0x04.m_saveSystem.Destroy();
	m_unk0x04.m_pieceLibrary.Destroy();
	m_unk0x04.m_unk0x21f4.Destroy();
	m_unk0x04.m_unk0x4224.Destroy();
	m_unk0x04.m_modelBuilder.ReleaseMenuResources();
	m_unk0x04.m_partResources.ReleaseResources();
	m_unk0x04.m_partCatalog.Destroy();
	m_unk0x4bcc.Shutdown();
	m_unk0x04.m_menuAnimations.Reset();
}

// FUNCTION: LEGORACERS 0x0042d300
LegoBool32 MenuManager::LoadLocalizedMenuResources(LegoU32 p_languageIndex, LegoBool32 p_forceReload)
{
	if (p_languageIndex != m_unk0x04.m_context->m_languageIndex || p_forceReload) {
		m_unk0x04.m_saveSystem.GetGameState().SetLanguageResourcePath();
		m_unk0x04.m_context->m_languageIndex = p_languageIndex;

		GolStringTable* menuTextStrings = &m_menuTextStrings;
		menuTextStrings->UseOwnedBuffers();

		GolStringTable* raceStrings = &m_raceStrings;
		raceStrings->UseOwnedBuffers();

		menuTextStrings->Load("menutext.srf");
		raceStrings->Load("circuit.srf");
		m_fontTable->LoadFontDefinitions(m_renderer, "GFonts", m_unk0x04.m_context->m_unk0x18);

		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA");
		}

		MenuStyleTable::ResourceLoadParams params;
		params.m_renderer = m_renderer;
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
	LoadLocalizedMenuResources(m_unk0x04.m_saveSystem.GetLanguageIndex(), FALSE);

	m_menuNameStrings.CopyStringByIndex(&m_unk0x4d30, p_menuId);

	m_unk0x4d98.m_golExport = m_golExport;
	m_unk0x4d98.m_renderer = m_renderer;
	m_unk0x4d98.m_inputManager = m_unk0x04.m_context->m_golApp->GetInputManager();
	m_unk0x4d98.m_inputEvents = m_unk0x04.m_inputBindings.GetUnk0x208();
	m_unk0x4d98.m_soundGroupBinding = &m_soundGroupBinding;
	m_unk0x4d98.m_menuStyles = &m_menuStyles;
	m_unk0x4d98.m_menuId = p_menuId;
	m_unk0x4d98.m_unk0x2c = m_unk0x04.m_context->m_unk0x18;
	m_unk0x4d98.m_unk0x20 = &m_unk0x4bd0;
	m_unk0x4d98.m_cursorHelper = m_textRenderer.GetCursorHelper();
	m_unk0x4d98.m_menuNameStrings = &m_menuNameStrings;
	m_unk0x4d98.m_menuTextStrings = &m_menuTextStrings;

	if (m_unk0x4dc8) {
		m_renderer->VTable0xf4();
		m_unk0x4dc8->Destroy();

		if (m_unk0x4dc8) {
			delete m_unk0x4dc8;
		}
	}

	m_unk0x4dc8 = m_unk0x4bcc.CreateScreen(p_menuId);
	m_textRenderer.SetUnk0x54(m_unk0x4dc8);
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
	m_renderer->VTable0x1c(rendererState);
	m_running = TRUE;

	while (m_running) {
		if (!golApp->Tick(this) || !m_running) {
			m_unk0x04.m_context->m_running = FALSE;
			break;
		}

		frameDeltaMs = golApp->GetFrameDeltaMs();
		m_unk0x04.m_context->GetSoundManager()->Update(frameDeltaMs);

		if (!golApp->IsDisabled()) {
			stack = &m_unk0x04.m_menuStack;
			previousMenu = stack->Peek();
			m_unk0x04.m_context->m_running = m_textRenderer.VTable0x10(frameDeltaMs);

			if (m_unk0x4bd0.GetUnk0x9c() > 0) {
				m_unk0x4bd0.FUN_00468da0(frameDeltaMs);
			}
			else {
				if (m_unk0x4dc8->VTable0x78(frameDeltaMs)) {
					m_unk0x04.m_context->m_running = FALSE;
				}
				if (!m_unk0x04.m_context->m_running || !m_unk0x04.m_menuStack.GetSize()) {
					break;
				}

				if (previousMenu != stack->Peek()) {
					FUN_0042d3e0(stack->Peek());
				}
			}

			menuAnimations = &m_unk0x04.m_menuAnimations;
			menuAnimations->Update(frameDeltaMs);
			m_renderer->VTable0x54(TRUE);
			m_renderer->VTable0xec(6);
			m_renderer->VTable0xe8(TRUE);

			if (m_unk0x4bd0.GetUnk0x9c() > 0) {
				m_unk0x4bd0.FUN_00468e20();
			}
			else {
				m_textRenderer.FUN_00469550();
			}

			menuAnimations->Draw(m_renderer);
			m_renderer->VTable0xe4();
			m_renderer->VTable0xf0();

			if (golApp->GetInputManager()->GetKeyboard()->GetButtonState(
					InputDevice::MakeEvent(InputDevice::c_sourceKeyboard, 0xb7)
				)) {
				FUN_0042e720();
			}

			golApp->PresentFrame();
		}
	}

	m_renderer->VTable0xf4();
	if (m_unk0x4dc8) {
		m_unk0x4dc8->Destroy();
		delete m_unk0x4dc8;
		m_unk0x4dc8 = NULL;
	}

	if (m_unk0x04.m_context->m_running) {
		FUN_0042d730();
	}
}

// STUB: LEGORACERS 0x0042d730
void MenuManager::FUN_0042d730()
{
	GolString string;
	GolRenderDevice::MaterialColor materialColor;
	GolRenderDevice::Light light;
	AmethystBreeze0x104 rendererState;
	LegoRacers::Context* context = m_unk0x04.m_context;
	SaveGame& saveGame = m_unk0x04.m_saveSystem.GetSessionSave();
	GameState& state = m_unk0x04.m_saveSystem.GetGameState();
	ActiveRecordBuffer& selectedRecords = m_unk0x04.m_saveSystem.GetActiveRecord();

	if (context->m_raceMode == LegoRacers::Context::c_raceModeCircuit ||
		context->m_raceMode == LegoRacers::Context::c_raceModeTimeRace) {
		context->m_unk0x20 = 0;
	}

	for (LegoU32 saveIndex = 0; saveIndex < saveGame.GetRecordCount(); saveIndex++) {
		SaveRecordList::Record* record = saveGame.GetRecord(saveIndex);
		::memcpy(context->m_saveRecords[saveIndex], record->m_data, sizeof(context->m_saveRecords[saveIndex]));
	}
	context->m_saveRecordCount = saveGame.GetRecordCount();

	state.WriteToSaveGame(&saveGame);
	::memcpy(&context->m_saveState, saveGame.GetFileImage(), sizeof(context->m_saveState));
	context->m_unk0x1e |= LegoRacers::Context::c_flagBit2;

	LegoU32 selectedCount = selectedRecords.GetSelectedRecordCount();
	if (!selectedCount) {
		context->m_racerCount = 6;
		context->m_raceMode = LegoRacers::Context::c_raceModeSingle;

		g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
		RaceNameEntry* raceName =
			m_unk0x04.m_circuitList.GetEntries()[0].GetRaceNameEntry(g_unk0x004befec[g_unk0x004c6ee4] % 4);

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

	if ((context->m_unk0x20 & 0x20) && ::strcmp(context->m_circuitName, "c6") == 0) {
		context->m_raceSlots[0].m_mirror = 1;
	}

	CircuitDefinitionList::CircuitDefinition* circuitDefinition =
		static_cast<CircuitDefinitionList::CircuitDefinition*>(m_unk0x04.m_circuitList.GetName(context->m_circuitName));
	if (circuitDefinition != NULL && context->m_racerCount > circuitDefinition->GetDriverCount()) {
		context->m_racerCount = circuitDefinition->GetDriverCount();
	}

	LegoRacers::Context::PlayerSetupSlot* slots = context->m_playerSetupSlots;
	if (circuitDefinition != NULL) {
		for (LegoU32 slotIndex = 0; slotIndex < context->m_racerCount; slotIndex++) {
			::memcpy(
				slots[slotIndex].m_driverName,
				circuitDefinition->GetDriverName(slotIndex),
				sizeof(slots[slotIndex].m_driverName)
			);
			slots[slotIndex].m_chassisName[0] = '\0';
			slots[slotIndex].m_unk0x10 = 2;
			slots[slotIndex].m_cosmetics.m_hatIndex = 0;
			slots[slotIndex].m_cosmetics.m_faceIndex = 0;
			slots[slotIndex].m_cosmetics.m_torsoIndex = 0;
			slots[slotIndex].m_cosmetics.m_legIndex = 0;
			slots[slotIndex].m_cosmetics.m_expressionIndex = 0;
			slots[slotIndex].m_previewFaceIndex = 0;
		}
	}

	undefined2 emptyName[15];
	::memset(emptyName, 0, sizeof(emptyName));
	string.CopyFromBufSelection(emptyName, 14);

	context->m_playerCount = selectedCount;
	if (selectedCount > context->m_racerCount) {
		context->m_racerCount = selectedCount;
	}

	if (m_unk0x04.m_unk0x21f4.IsInitialized()) {
		m_unk0x04.m_unk0x21a4.Clear();
		m_unk0x04.m_unk0x21f4.Destroy();
		m_unk0x04.m_unk0x4224.Destroy();
		m_unk0x04.m_pieceLibrary.Destroy();
	}

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PIECEDB");
	}

	m_unk0x04.m_pieceLibrary.FUN_0049ee30("LPieceLo.leg", context->m_unk0x18);
	m_unk0x04.m_unk0x4224.Initialize(m_golExport, m_renderer);
	m_unk0x04.m_unk0x4224.LoadMaterials("LPieceLo.WDF", context->m_unk0x18, FALSE);
	m_unk0x04.m_unk0x4224.LoadColors("L_Colors.LEG", context->m_unk0x18);
	m_unk0x04.m_unk0x21f4.Initialize(m_golExport, m_renderer, &m_unk0x04.m_pieceLibrary, &m_unk0x04.m_unk0x4224);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	FUN_0042df70();
	FUN_0042de90(TRUE);

	LegoRacers::Context::PlayerRecordState* recordStates = context->m_playerRecordStates;
	for (LegoU32 selectedIndex = 0; selectedIndex < selectedCount; selectedIndex++) {
		SaveRecordList::Record* record = selectedRecords.GetSelectedRecord(selectedIndex);
		LegoRacers::Context::PlayerSetupSlot* slot = &slots[selectedIndex];

		rendererState.FUN_0040eb60();

		ColorRGBA color;
		color.m_red = 0x80;
		color.m_grn = 0x80;
		color.m_blu = 0x80;
		color.m_alp = 0x80;
		materialColor.SetColor(color);
		rendererState.FUN_0040eb70(&materialColor);

		color.m_red = 0xff;
		color.m_grn = 0xff;
		color.m_blu = 0xff;
		color.m_alp = 0xff;
		light.SetColor(color);

		GolVec3 direction;
		direction.m_x = -1.0f;
		direction.m_y = 0.0f;
		direction.m_z = -1.0f;
		light.SetDirection(direction);
		rendererState.FUN_0040eba0(&light);

		record->GetName(&string);
		string.CopyToString(slot->m_playerName);

		FUN_0042dcb0(record, slot, &rendererState);
		FUN_0042dfa0(record, slot, &rendererState);

		recordStates[selectedIndex].m_unk0x00 = record->m_unk0x08;
		recordStates[selectedIndex].m_unk0x04 = record->m_unk0x0c;
		recordStates[selectedIndex].m_unk0x08 = record->m_recordId;

		record->GetCosmetics(&slot->m_cosmetics);
		slot->m_unk0x10 = 0;
	}

	for (LegoU32 clearIndex = 0; clearIndex < 4; clearIndex++) {
		context->m_bestLapTimes[clearIndex] = 0;
		context->m_bestLapHolders[clearIndex] = 0;
		context->m_bestRaceTimes[clearIndex] = 0;
		context->m_bestRaceHolders[clearIndex] = 0;
	}

	if (!selectedCount) {
		context->m_playerCount = m_unk0x04.m_inputBindings.GetInputManager()->GetJoystickCount();
	}

	for (LegoU32 playerIndex = 0; playerIndex < context->m_playerCount; playerIndex++) {
		LegoU32 entryIndex = state.GetSelectedInputBindingEntryIndex(playerIndex);
		state.GetInputBindingEntry(playerIndex, entryIndex, &context->m_inputBindings[playerIndex]);
	}

	if (!selectedCount) {
		context->m_playerCount = 0;
	}
}

// FUNCTION: LEGORACERS 0x0042dcb0
void MenuManager::FUN_0042dcb0(
	SaveRecordList::Record* p_record,
	LegoRacers::Context::PlayerSetupSlot* p_slot,
	AmethystBreeze0x104* p_rendererState
)
{
	GolModelEntity entity;

	p_slot->m_driverName[0] = '\0';
	p_record->GetChassisName(p_slot->m_chassisName);

	GolExport* golExport = m_unk0x04.m_context->m_golApp->GetGolExport();
	GolD3DRenderDevice* renderer = golExport->GetDrawState()->m_currentRenderer;
	CarBuildModel& carBuildModel = m_unk0x04.m_unk0x21f4;

	if (!carBuildModel.FUN_0049c7f0(p_record->GetCarData())) {
		GOL_FATALERROR_MESSAGE("Unable to load mesh builder with car data");
	}

	carBuildModel.FUN_0049b740(0);
	carBuildModel.FUN_0049b920(0, 0xff);

	undefined4 textureCount;
	undefined4 materialCount;

	materialCount = carBuildModel.GetUnk0x1ee8();
	textureCount = carBuildModel.GetUnk0x1eec();

	GolMaterialLibrary* materials = p_slot->m_materials;
	if (materials) {
		golExport->DestroyMaterialList(materials);
		p_slot->m_materials = NULL;
	}
	p_slot->m_materials = golExport->CreateMaterialList();
	p_slot->m_materials->VTable0x1c(renderer, materialCount);

	if (p_slot->m_textures) {
		golExport->DestroyTextureList(p_slot->m_textures);
		p_slot->m_textures = NULL;
	}
	p_slot->m_textures = golExport->CreateTextureList();
	p_slot->m_textures->VTable0x1c(renderer, textureCount);

	if (p_slot->m_model) {
		golExport->VTable0x48(p_slot->m_model);
		p_slot->m_model = NULL;
	}
	p_slot->m_model = golExport->VTable0x14();
	p_slot->m_model->VTable0x18(
		renderer,
		3,
		carBuildModel.GetUnk0x1ef8(),
		carBuildModel.GetUnk0x1ef4(),
		carBuildModel.GetUnk0x1ef0(),
		materialCount
	);

	carBuildModel.FUN_0049c840(p_slot->m_model, p_slot->m_materials, p_slot->m_textures);
	p_slot->m_unk0x14 = carBuildModel.FUN_0049c6a0(&p_slot->m_unk0x18, &p_slot->m_unk0x1c, &p_slot->m_unk0x20);

	entity.VTable0x50(p_slot->m_model, g_menuManagerMaxFloat);
	renderer->VTable0x9c(&entity, p_rendererState, 0);
	entity.VTable0x54();

	GdbVertexArray0xc* vertexArray;
	p_slot->m_model->VTable0x28(&vertexArray);
	vertexArray->VTable0x10();
	p_slot->m_model->VTable0x2c(1, FALSE);
}

// FUNCTION: LEGORACERS 0x0042de90
void MenuManager::FUN_0042de90(LegoBool32 p_arg)
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PARTDB");
	}

	m_unk0x04.m_partCatalog.Load("bodypart.pcf", m_unk0x04.m_context->m_unk0x18);

	DriverPartResources::LoadParams partParams;
	partParams.m_golExport = m_unk0x04.m_context->m_golApp->GetGolExport();
	partParams.m_renderer = m_unk0x04.m_context->m_golApp->GetRenderer();
	partParams.m_partCatalog = &m_unk0x04.m_partCatalog;
	partParams.m_binary = m_unk0x04.m_context->m_unk0x18;
	partParams.m_textureBinaryMode = p_arg == FALSE;
	m_unk0x04.m_partResources.Load(&partParams, p_arg);

	DriverModelBuilder::LoadParams menuParams;
	menuParams.m_golExport = partParams.m_golExport;
	menuParams.m_renderer = partParams.m_renderer;
	menuParams.m_menuId = 6;
	menuParams.m_partResources = &m_unk0x04.m_partResources;
	m_unk0x04.m_modelBuilder.Load(&menuParams);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x0042df70
void MenuManager::FUN_0042df70()
{
	m_unk0x04.m_modelBuilder.ReleaseMenuResources();
	m_unk0x04.m_partResources.ReleaseResources();
	m_unk0x04.m_partCatalog.Destroy();
}

// STUB: LEGORACERS 0x0042dfa0
void MenuManager::FUN_0042dfa0(
	SaveRecordList::Record* p_record,
	LegoRacers::Context::PlayerSetupSlot* p_slot,
	AmethystBreeze0x104* p_rendererState
)
{
	GolAnimatedEntity entity;
	CmbModelPart0x34 modelParts;
	LegoU32 textureCount;
	DriverCosmetics cosmetics;
	GolModelMaterialTable* materialTable;
	LegoU32 materialCount;
	DuskWindBananaRelicParams params;

	p_record->GetCosmetics(&cosmetics);

	DriverModelBuilder* modelBuilder = &m_unk0x04.m_modelBuilder;
	p_slot->m_altModel = modelBuilder->BuildDriverModel(&cosmetics, NULL, 3);
	p_slot->m_previewFaceIndex = cosmetics.m_faceIndex;
	materialTable = p_slot->m_altModel->GetMaterialTable();
	textureCount = 0;

	for (materialCount = 0; materialCount < materialTable->GetCount(); materialCount++) {
		DuskwindBananaRelic0x24* material = materialTable->GetMaterial(materialCount);
		if (material == NULL) {
			break;
		}

		if (material->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
			textureCount++;
		}
	}

	GolExport* golExport = m_unk0x04.m_context->m_golApp->GetGolExport();
	GolD3DRenderDevice* renderer = golExport->GetDrawState()->m_currentRenderer;

	p_slot->m_altMaterials = golExport->CreateMaterialList();
	p_slot->m_altMaterials->VTable0x1c(renderer, materialCount);
	p_slot->m_altTextures = golExport->CreateTextureList();
	p_slot->m_altTextures->VTable0x1c(renderer, textureCount);

	textureCount = 0;
	for (LegoU32 materialIndex = 0; materialIndex < materialCount; materialIndex++) {
		DuskwindBananaRelic0x24* sourceMaterial = materialTable->GetMaterial(materialIndex);
		sourceMaterial->CopyParamsTo(&params);

		if (sourceMaterial->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
			PurpleDune0x7c* texture = p_slot->m_altTextures->GetItem(textureCount++);
			texture->SetName(static_cast<PurpleDune0x7c*>(params.m_unk0x04)->GetName());
			texture->SetSourceTextureDefinition(
				params.m_unk0x04->GetUnk0x34(),
				params.m_unk0x04->GetUnk0x36(),
				params.m_unk0x04->GetColorKey()
			);
			params.m_unk0x04 = texture;
		}
		else {
			params.m_unk0x04 = NULL;
		}

		params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flagBit0;
		DuskwindBananaRelic0x24* material = p_slot->m_altMaterials->GetItem(materialIndex);
		material->FUN_100257e0(renderer, params);
		materialTable->SetPosition(materialIndex, material);
	}

	entity.FUN_0040d550(
		p_slot->m_altModel,
		modelBuilder->GetBodySceneNode(&cosmetics),
		&modelParts,
		g_menuManagerMaxFloat
	);
	renderer->VTable0x9c(&entity, p_rendererState, 0);
	entity.VTable0x54();

	GdbVertexArray0xc* vertexArray;
	p_slot->m_altModel->VTable0x28(&vertexArray);
	vertexArray->VTable0x10();
	p_slot->m_altModel->VTable0x2c(1, FALSE);
}

// FUNCTION: LEGORACERS 0x0042e1f0
void MenuManager::FUN_0042e1f0()
{
	LegoU32 driverIndex = 0;
	LegoFloat musicVolume;
	GameState& state = m_unk0x04.m_saveSystem.GetGameState();

	m_unk0x04.m_context->m_racerCount = state.GetRacerCount();
	m_unk0x04.m_context->m_unk0x2c = state.GetUnk0x23();

	if (m_unk0x04.m_context->GetSoundManager() != NULL) {
		musicVolume = state.GetMusicVolume() * g_unk0x4b05d8;
		m_unk0x04.m_context->GetSoundManager()->SetMusicVolumeScale(1.0f);

		if (m_unk0x04.m_modelBuilder.m_musicInstance) {
			m_unk0x04.m_modelBuilder.m_musicInstance->SetVolume(musicVolume);
		}
		m_unk0x04.m_context->GetSoundManager()->SetMusicVolumeScale(musicVolume);
		m_unk0x04.m_context->GetSoundManager()->SetVolumeScale(state.GetSoundVolume() * g_unk0x4b05d8);

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
	MemoryCardSaveGame* entry = m_unk0x04.m_saveSystem.GetMemoryCardSaves();

	for (LegoU32 i = 0; i < m_unk0x04.m_saveSystem.GetMemoryCardSaveCount(); i++, entry++) {
		if (entry->HasUnk0x4b4Flag0x01()) {
			return TRUE;
		}
	}

	return FALSE;
}

// STUB: LEGORACERS 0x0042e490
LegoS32 MenuManager::FUN_0042e490()
{
	LegoU8 flags = m_unk0x04.m_context->m_unk0x1e;

	if (!(flags & LegoRacers::Context::c_flagBestTimesPending)) {
		return FALSE;
	}

	m_unk0x04.m_context->m_unk0x1e = flags & ~LegoRacers::Context::c_flagBestTimesPending;
	LegoRacers::Context* context = m_unk0x04.m_context;

	GolString string;
	LegoChar name[15];
	undefined2 wideName[15];
	LegoS32 result = FALSE;
	LegoU32 raceIndex = 0;

	for (LegoS32 i = 0; i < 4; i++) {
		LegoBool32 hasRaceIndex = FALSE;

		if (context->m_bestLapTimes[i]) {
			raceIndex = m_unk0x04.m_raceNames.GetEntryIndexByName(context->m_raceSlots[i].m_raceName);
			hasRaceIndex = TRUE;

			const LegoChar* sourceName = context->m_playerSetupSlots[context->m_bestLapHolders[i]].m_playerName;
			::strncpy(name, sourceName, sizeof(name) - 1);
			name[sizeof(name) - 1] = '\0';
			GolString::CopyStringToBuf16(sourceName, wideName);
			string.CopyFromBufSelection(wideName, sizeof(name) - 1);

			if (m_unk0x04.m_saveSystem.GetGameState().SetBestTime(raceIndex, 0, context->m_bestLapTimes[i], &string)) {
				result = TRUE;
			}
		}

		if (context->m_bestRaceTimes[i]) {
			if (!hasRaceIndex) {
				raceIndex = m_unk0x04.m_raceNames.GetEntryIndexByName(context->m_raceSlots[i].m_raceName);
			}

			const LegoChar* sourceName = context->m_playerSetupSlots[context->m_bestRaceHolders[i]].m_playerName;
			::strncpy(name, sourceName, sizeof(name) - 1);
			name[sizeof(name) - 1] = '\0';
			GolString::CopyStringToBuf16(sourceName, wideName);
			string.CopyFromBufSelection(wideName, sizeof(name) - 1);

			if (m_unk0x04.m_saveSystem.GetGameState().SetBestTime(raceIndex, 1, context->m_bestRaceTimes[i], &string)) {
				result = TRUE;
			}
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0042e680
LegoBool32 MenuManager::FUN_0042e680()
{
	LegoU8 flags = m_unk0x04.m_context->m_unk0x1e;

	if (!(flags & LegoRacers::Context::c_flagRecordBeaten)) {
		return FALSE;
	}

	m_unk0x04.m_context->m_unk0x1e = flags & ~LegoRacers::Context::c_flagRecordBeaten;

	GameState* state = &m_unk0x04.m_saveSystem.GetGameState();
	LegoU32 index = m_unk0x04.m_raceNames.GetEntryIndexByName(m_unk0x04.m_context->m_raceSlots[0].m_raceName);
	if (index >= 12) {
		return FALSE;
	}

	if (state->UnlockRace(1 << index)) {
		if (state->AreAllRacesUnlocked()) {
			state->UnlockParts(0x80);
			m_unk0x04.m_context->m_nextMenuId = 0x1c;
		}

		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0042e700
void MenuManager::VTable0x00()
{
	m_running = FALSE;
	m_unk0x04.m_context->m_running = FALSE;
}

// FUNCTION: LEGORACERS 0x0042e720
void MenuManager::FUN_0042e720()
{
	enum {
		c_maxScreenshotIndex = 9999
	};

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
		bmpWriter.VTable0x08(fileName);
		bmpWriter.WriteSurface(m_renderer->GetRenderTargetInfo());
		bmpWriter.Destroy();

		if (g_hashTable) {
			g_hashTable->SetCurrentEntry(currentEntry);
		}
	}
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
	m_textRenderer.SetCursorInside(1);
}

// FUNCTION: LEGORACERS 0x0042e840
void MenuManager::VTable0x2c()
{
	m_textRenderer.SetCursorInside(0);
}

// FUNCTION: LEGORACERS 0x0042e850
void MenuManager::VTable0x24(undefined4 p_arg1, undefined4 p_arg2)
{
	m_textRenderer.SetCursorPosition(p_arg1, p_arg2);
}

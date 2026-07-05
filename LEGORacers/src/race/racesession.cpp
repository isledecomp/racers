#include "race/racesession.h"

#include "app/golapp.h"
#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "audio/soundmanager.h"
#include "audio/soundnode.h"
#include "camera/golcamera.h"
#include "camera/goltransform.h"
#include "core/gol.h"
#include "font/golfonttable.h"
#include "golbinparser.h"
#include "golbmpwriterfile.h"
#include "golboundedentity.h"
#include "golboundingvolume.h"
#include "golerror.h"
#include "golfontbase.h"
#include "golhashtable.h"
#include "golmaterial.h"
#include "golmateriallibrary.h"
#include "golmodelmaterialtable.h"
#include "golstream.h"
#include "input/directinputdevice.h"
#include "input/inputdevice.h"
#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "input/mousedevice.h"
#include "material/golimagedefinitionlist.h"
#include "race/circuitstandings.h"
#include "race/hazards/hazardcontext.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/golrendertarget.h"
#include "world/golworlddatabase.h"

#include <memory.h>
#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_raceLapCount;
extern LegoU32 g_randomTableIndex;

DECOMP_SIZE_ASSERT(RaceSession, 0x3368)

// GLOBAL: LEGORACERS 0x004b08c0
extern const LegoFloat g_unk0x004b08c0 = 1.75f;
DECOMP_SIZE_ASSERT(InputEventSink, 0x04)
DECOMP_SIZE_ASSERT(RaceSession::RabTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(RacerContext, 0x40)

// GLOBAL: LEGORACERS 0x004b07ec
LegoFloat g_defaultMusicVolume = 1.2f;

// GLOBAL: LEGORACERS 0x004b07f0
extern const LegoFloat g_mirroredRaceStateRouteScale = 0.05f;

// GLOBAL: LEGORACERS 0x004b08bc
extern const LegoFloat g_splitScreenFovDelta = 25.0f;

// GLOBAL: LEGORACERS 0x004bee30
const LegoChar* g_sideWinderForceFeedName = "Microsoft SideWinder Force Feed";

// GLOBAL: LEGORACERS 0x004bee64
const LegoFloat g_viewportRects[4] = {0.5f, 0.01f, 0.49f, 0.49f};

// GLOBAL: LEGORACERS 0x004bee74
const LegoU16 g_pauseMenuStringIds[16] =
	{0x0e, 0x0f, 0x11, 0x14, 0x0e, 0x10, 0x11, 0x00, 0x12, 0x13, 0x15, 0x16, 0x17, 0x18, 0x2c, 0x00};

// FUNCTION: LEGORACERS 0x004316e0
RaceSession::RaceSession()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00431990
RaceSession::~RaceSession()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00431bd0
void RaceSession::Reset()
{
	m_context = NULL;
	m_golApp = NULL;
	m_soundManager = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_inputManager = NULL;
	m_standings = NULL;
	m_displayName[0] = '\0';
	m_trackModelName[0] = '\0';
	m_worldName[0] = '\0';
	m_sharedModelName[0] = '\0';
	m_effectsModelName[0] = '\0';
	m_materialAnimationModelName[0] = '\0';
	m_triggerModelName[0] = '\0';
	m_collisionWorldName[0] = '\0';
	m_triggerWorldName[0] = '\0';
	m_powerupFileName[0] = '\0';
	m_turboDatabaseName[0] = '\0';
	m_powerupDatabaseName[0] = '\0';
	m_unusedFileName[0] = '\0';
	m_racerTriggerFileName[0] = '\0';
	m_eventFileName[0] = '\0';
	m_triggerFileName[0] = '\0';
	m_timerFileName[0] = '\0';
	m_particleAnimationName[0] = '\0';
	m_soundFileName[0] = '\0';
	m_voiceFileName[0] = '\0';
	m_soundBankName[0] = '\0';
	m_musicFileName[0] = '\0';
	m_fontFileName[0] = '\0';
	m_imageFileName[0] = '\0';
	m_startPositionsFileName[0] = '\0';
	m_skyName[0] = '\0';
	m_surfaceFileName[0] = '\0';
	m_hazardFileName[0] = '\0';
	m_checkpointFileName[0] = '\0';
	m_extraTriggerWorldName[0] = '\0';
	m_cameraName[0] = '\0';
	m_targetFileName[0] = '\0';
	m_trackCamera = NULL;
	m_cameraStartPosition.m_x = 0.0f;
	m_cameraStartPosition.m_y = 0.0f;
	m_cameraStartPosition.m_z = 0.0f;
	m_cameraStartDirection.m_x = 1.0f;
	m_cameraStartDirection.m_y = 0.0f;
	m_cameraStartDirection.m_z = 0.0f;
	m_cameraStartUp.m_x = 0.0f;
	m_cameraStartUp.m_y = 0.0f;
	m_cameraStartUp.m_z = -1.0f;
	m_mapMinX = 1023.0f;
	m_mapMaxX = -1023.0f;
	m_mapMaxY = 1023.0f;
	m_mapMinY = -1023.0f;
	m_trackDatabase = NULL;
	m_trackCollidable = NULL;
	m_effectsDatabase = NULL;
	m_sharedDatabase = NULL;
	m_triggerDatabase = NULL;
	m_collisionWorld = NULL;
	m_triggerWorldEntity = NULL;
	m_extraTriggerWorldEntity = NULL;
	m_fontTable = 0;
	m_hudFont = 0;
	m_loadingFont = 0;
	m_hudImages = 0;
	m_musicGroup = NULL;
	m_music = NULL;
	m_musicVolume = g_defaultMusicVolume;
	m_materialAnimationDatabase = NULL;
	m_powerupTrackDatabase = 0;
	m_finishedCount = 0;
	m_clearMode = 0;

	for (LegoS32 i = 0; i < sizeOfArray(m_cameras); i++) {
		m_listenerNodes[i] = NULL;
		m_cameras[i] = NULL;
		m_raceState.m_playerRacers[i] = NULL;
	}

	m_elapsedMs = 0;
	m_state = 0;
	memset(m_hudScratchBuffer, 0, sizeof(m_hudScratchBuffer));
	m_demoTextMs = 0;
	m_running = 0;
	m_abortKeyMask = 0;
	m_demoMode = 0;
	m_splitScreen = 0;
	m_pauseState = 0;
	m_returnToGarage = 0;
	m_pendingAction = 0;
	m_lapCount = 0;
	m_timeRaceManager = NULL;
}

// FUNCTION: LEGORACERS 0x00431e00
void RaceSession::Initialize(
	LegoRacers::Context* p_context,
	const LegoChar* p_raceName,
	undefined4 p_mirror,
	TimeRaceManager* p_timeRaceManager
)
{
	GolFileParser* parser;
	if (p_context->m_useBinaryFiles) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".rab");
	}
	else {
		parser = new RabTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_raceName);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(e_race));
	strcpy(m_displayName, parser->ReadStringWithMaxLength(0x3f));
	parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case e_world:
			strcpy(m_worldName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_sky:
			strcpy(m_skyName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_sharedModel:
			strcpy(m_sharedModelName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_cameraDirection:
			m_cameraStartDirection.m_x = parser->ReadFloat();
			m_cameraStartDirection.m_y = parser->ReadFloat();
			m_cameraStartDirection.m_z = parser->ReadFloat();
			m_cameraStartUp.m_x = parser->ReadFloat();
			m_cameraStartUp.m_y = parser->ReadFloat();
			m_cameraStartUp.m_z = parser->ReadFloat();
			break;
		case e_cameraPosition:
			m_cameraStartPosition.m_x = parser->ReadFloat();
			m_cameraStartPosition.m_y = parser->ReadFloat();
			m_cameraStartPosition.m_z = parser->ReadFloat();
			break;
		case e_camera:
			strncpy(m_cameraName, parser->ReadStringWithMaxLength(8), 8);
			break;
		case e_effectsModel:
			strcpy(m_effectsModelName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_collision:
			strcpy(m_triggerModelName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(m_collisionWorldName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(m_triggerWorldName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_events:
			strcpy(m_eventFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_fonts:
			strcpy(m_fontFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_trackModel:
			strcpy(m_trackModelName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_images:
			strcpy(m_imageFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_music:
			strcpy(m_musicFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_unused0x31:
		case e_unused0x32:
			parser->ReadStringWithMaxLength(0x0c);
			break;
		case e_powerups:
			strcpy(m_powerupFileName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(m_turboDatabaseName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(m_powerupDatabaseName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_unusedFile:
			strcpy(m_unusedFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_startPositions:
			strcpy(m_startPositionsFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_sounds:
			strcpy(m_soundFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_voices:
			strcpy(m_voiceFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_soundBank:
			strcpy(m_soundBankName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_triggers:
			strcpy(m_triggerFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_timers:
			strcpy(m_timerFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_materialAnimationModel:
			strcpy(m_materialAnimationModelName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_particleAnimations:
			strcpy(m_particleAnimationName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(m_sharedParticleAnimationName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_racerTriggers:
			strcpy(m_racerTriggerFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_surfaces:
			strcpy(m_surfaceFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_hazards:
			strcpy(m_hazardFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_checkpoints:
			strcpy(m_checkpointFileName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(m_extraTriggerWorldName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case e_mapBounds:
			m_mapMinX = parser->ReadFloat();
			m_mapMaxY = parser->ReadFloat();
			m_mapMaxX = parser->ReadFloat();
			m_mapMinY = parser->ReadFloat();
			break;
		case e_targets:
			strcpy(m_targetFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = parser->GetNextToken();
	}

	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}

	AttachContext(p_context);

	if (p_mirror) {
		m_cameraStartDirection.m_y = -m_cameraStartDirection.m_y;
		m_cameraStartUp.m_y = -m_cameraStartUp.m_y;
		m_cameraStartPosition.m_y = -m_cameraStartPosition.m_y;
	}

	CreateCameras();
	LoadStringsAndFonts();

	GolHashTable* hashTable = g_hashTable;
	LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(gameDataDirectory));
	}

	m_loadingScreen.Initialize(m_golExport, m_renderer, &m_stringTable, m_loadingFont, p_context->m_useBinaryFiles);
	m_golApp->ClearFlags(GolApp::c_flagBit14);
	DrawLoadProgress(0.0f);

	m_timeRaceManager = p_timeRaceManager;
	if (p_timeRaceManager) {
		p_timeRaceManager->PrepareRun();
	}

	m_elapsedMs = 0;
	m_state = 1;
	InitializeSound();
	DrawLoadProgress(0.05f);
	LoadHudImages();
	LoadDatabases(p_mirror);
	LoadRaceContent(p_mirror);
	DrawLoadProgress(1.0f);
	InitializeInput();
	StartIntroCamera();
	m_renderer->DisableMipmaps();
}

// FUNCTION: LEGORACERS 0x00432520
void RaceSession::OnCloseRequested()
{
	m_running = 0;
	m_context->m_running = FALSE;
}

// FUNCTION: LEGORACERS 0x00432540
void RaceSession::Run()
{
	m_running = 1;
	m_frameCount = 0;
	m_totalRunMs = 0;

	LegoS32 previousTime = timeGetTime();

	m_fps = 0.0f;
	m_elapsedMs = 0;

	LegoU32 frameSampleCount = 0;
	LegoU32 frameSampleElapsedMs = 0;

	m_state = 1;
	m_renderer->VTable0x44();

	while (m_running) {
		if (!m_golApp->Tick(this)) {
			break;
		}

		if (m_golApp->GetFlags() & GolApp::c_flagBit14) {
			m_pauseState = 1;
			OpenPauseDialog();
			m_golApp->ClearFlags(GolApp::c_flagBit14);
		}

		while (m_inputEvents.GetSize()) {
			InputEventQueue::Event* event = m_inputEvents.Dequeue();
			if (event->m_isPressed) {
				OnKeyDown(event->m_keyCode);
			}
			else {
				OnKeyUp(event->m_keyCode);
			}
		}

		if (!m_golApp->IsDisabled()) {
			if (!m_pauseState) {
				m_elapsedMs += m_golApp->GetFrameDeltaMs();
			}

			switch (m_state) {
			case 1:
				UpdateIntroState();
				break;
			case 2:
				UpdateCountdownState();
				break;
			case 3:
				UpdateRacingState();
				break;
			case 4:
				UpdateFinishedState();
				break;
			case 5:
				UpdateResultsState();
				break;
			}

			Update();
			Draw();
			m_golApp->PresentFrame();

			if (m_frameCount) {
				LegoS32 currentTime = timeGetTime();
				m_totalRunMs += currentTime - previousTime;
				frameSampleElapsedMs += currentTime - previousTime;
				frameSampleCount++;
				previousTime = currentTime;

				if (frameSampleCount >= 64) {
					frameSampleElapsedMs >>= 6;
					m_fps = 1.0f / (static_cast<LegoFloat>((LegoS32) frameSampleElapsedMs) * 0.001f);
					frameSampleCount = 0;
					frameSampleElapsedMs = 0;
				}
			}

			m_frameCount++;
		}
	}

	m_renderer->VTable0xf4();
	m_renderer->VTable0x38();
	m_renderer->VTable0x48();
	m_raceState.RecordBestTimes(m_context);

	Racer* field = m_raceState.GetPlayerRacer();
	if (field) {
		m_context->m_cameraViewIndex = field->m_cameraViewIndex;
	}

	if (m_context->m_running && m_timeRaceManager) {
		m_context->m_flags |= LegoRacers::Context::c_flagBestTimesPending;

		if (m_timeRaceManager->HasBeatenRecord()) {
			m_context->m_flags |= LegoRacers::Context::c_flagRecordBeaten;
		}
	}
}

// FUNCTION: LEGORACERS 0x00432790
void RaceSession::Shutdown()
{
	DestroyRouteRecords();
	DestroyInput();
	DestroyRaceContent();
	DestroyDatabases();
	DestroyHudImages();
	DestroyStringsAndFonts();
	m_loadingScreen.Destroy();
	DestroyCameras();
	DestroySound();
	DetachContext();
	Reset();
}

// FUNCTION: LEGORACERS 0x004327f0
void RaceSession::AttachContext(LegoRacers::Context* p_context)
{
	m_context = p_context;
	m_context->m_flags &= ~LegoRacers::Context::c_flagRecordBeaten;

	m_golApp = m_context->m_golApp;
	m_soundManager = m_context->m_soundManager;
	m_golExport = m_golApp->GetGolExport();
	m_renderer = m_golApp->GetRenderer();
	m_inputManager = m_golApp->GetInputManager();

	LegoU32 one = 1;
	if (m_context->m_playerCount > one) {
		m_splitScreen = one;
	}
	else {
		m_splitScreen = 0;
	}

	if (m_splitScreen) {
		m_renderer->SetViewportRect(3, &g_viewportRects[1]);
		m_lapCount = m_context->m_lapCount;
	}
	else {
		m_renderer->SetViewportRect(1, g_viewportRects);
		m_lapCount = 3;
	}

	if (!m_context->m_playerCount) {
		m_context->m_playerCount = one;
		m_context->m_playerSetupSlots[0].m_slotState = 0;
		m_demoMode = one;
	}
	else {
		m_demoMode = 0;
	}

	if (m_context->m_flags & LegoRacers::Context::c_flagReturnToGarage) {
		m_returnToGarage = one;
	}
}

// FUNCTION: LEGORACERS 0x004328d0
void RaceSession::DetachContext()
{
	m_context = NULL;
	m_golApp = NULL;
	m_soundManager = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_inputManager = NULL;
}

// FUNCTION: LEGORACERS 0x004328f0
void RaceSession::InitializeSound()
{
	LegoChar firstVoice[16];
	LegoChar secondVoice[16];

	firstVoice[0] = '\0';
	secondVoice[0] = '\0';

	m_musicGroup = m_soundManager->CreateMusicGroup();
	m_musicGroup->Load(m_musicFileName);

	m_soundSource.Initialize(m_soundManager);
	m_soundSource.LoadAmbientBank(m_soundBankName);

	LegoU32 index = GetPlayerVoiceName(0, firstVoice);
	if (m_timeRaceManager) {
		strcpy(secondVoice, "voice29");
	}
	else if (m_context->m_playerCount > 1) {
		GetPlayerVoiceName(index + 1, secondVoice);
	}
	else {
		strcpy(secondVoice, m_voiceFileName);
	}

	GolHashTable* hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString("GAMEDATA\\VOICES"));
	}

	m_soundSource.LoadVoiceBanks(firstVoice, secondVoice);

	const LegoChar* commonDataDirectory = m_context->m_commonDataDirectory;
	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(commonDataDirectory));
	}

	m_soundSource.LoadSfxBank(m_soundFileName);

	for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
		m_listenerNodes[i] = m_soundManager->CreateSoundNode();
		m_soundManager->AddActiveSoundNode(m_listenerNodes[i]);
		m_cameraControllers[i].m_listenerNode = m_listenerNodes[i];
	}
}

// FUNCTION: LEGORACERS 0x00432a50
LegoU32 RaceSession::GetPlayerVoiceName(LegoU32 p_index, LegoChar* p_buffer)
{
	undefined4 slotState = m_context->m_playerSetupSlots[p_index].m_slotState;

	if (slotState && p_index < m_context->m_racerCount) {
		do {
			p_index++;
			slotState = m_context->m_playerSetupSlots[p_index].m_slotState;
		} while (slotState);
	}

	if (m_demoMode) {
		p_index = 0;
	}

	strcpy(p_buffer, "voice");

	LegoU8 tens = m_context->m_playerSetupSlots[p_index].m_previewFaceIndex;
	if (tens < 10) {
		tens = 0;
	}
	else {
		tens /= 10;
	}

	p_buffer[5] = tens + '0';
	p_buffer[6] = m_context->m_playerSetupSlots[p_index].m_previewFaceIndex - (tens * 10) + '0';
	p_buffer[7] = '\0';

	return p_index;
}

// FUNCTION: LEGORACERS 0x00432b30
void RaceSession::DestroySound()
{
	if (m_soundManager) {
		for (LegoS32 i = 0; i < sizeOfArray(m_listenerNodes); i++) {
			if (m_listenerNodes[i]) {
				m_soundManager->DestroySoundNode(m_listenerNodes[i]);
				m_listenerNodes[i] = NULL;
			}
		}

		m_soundSource.DestroyGroups();

		if (m_music) {
			m_music->Stop();
			m_musicGroup->DestroyMusicInstance(m_music);
			m_music = NULL;
		}

		MusicGroup* musicGroup = m_musicGroup;
		if (musicGroup) {
			m_soundManager->DestroyMusicGroup(musicGroup);
			m_musicGroup = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00432bc0
void RaceSession::LoadStringsAndFonts()
{
	LegoChar commonDataPath[28];
	strcpy(commonDataPath, "GAMEDATA\\COMMON\\");

	switch (m_context->m_languageIndex) {
	case 0:
		strcat(commonDataPath, "english");
		break;
	case 1:
		strcat(commonDataPath, "spanish");
		break;
	case 2:
		strcat(commonDataPath, "french");
		break;
	case 3:
		strcat(commonDataPath, "german");
		break;
	case 4:
		strcat(commonDataPath, "italian");
		break;
	case 5:
		strcat(commonDataPath, "danish");
		break;
	case 6:
		strcat(commonDataPath, "swedish");
		break;
	case 7:
		strcat(commonDataPath, "norwegi");
		break;
	case 8:
		strcat(commonDataPath, "dutch");
		break;
	case 10:
		strcat(commonDataPath, "finnish");
		break;
	}

	GolHashTable* hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(commonDataPath));
	}

	m_stringTable.UseOwnedBuffers();
	m_stringTable.Load("game.srf");

	m_raceState.m_driverTable.LoadStrings();
	m_hudScratchString.CopyFromBufSelection(m_hudScratchBuffer, 0x100);

	m_fontTable = m_golExport->CreateFontTable();
	m_fontTable->LoadFontDefinitions(m_renderer, m_fontFileName, m_context->m_useBinaryFiles);
	m_hudFont = m_fontTable->GetItem(0);
	m_loadingFont = m_fontTable->GetItem(0);
}

// FUNCTION: LEGORACERS 0x00432d70
void RaceSession::DestroyStringsAndFonts()
{
	if (m_golExport && m_fontTable) {
		m_golExport->DestroyFontTable(m_fontTable);
		m_fontTable = NULL;
	}

	m_hudScratchString.Reset();

	GolStringTable* stringTable = &m_stringTable;
	stringTable->ReleaseOwnedBuffers();
}

// FUNCTION: LEGORACERS 0x00432dc0
void RaceSession::LoadHudImages()
{
	m_hudImages = m_golExport->CreateImageList();
	m_hudImages->LoadImageDefinitions(m_renderer, m_imageFileName, m_context->m_useBinaryFiles);
}

// FUNCTION: LEGORACERS 0x00432df0
void RaceSession::DestroyHudImages()
{
	if (m_golExport) {
		if (m_hudImages) {
			m_golExport->DestroyImageList(m_hudImages);
			m_hudImages = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00432e20
void RaceSession::LoadDatabases(LegoBool32 p_mirror)
{
	m_effectsDatabase = m_golExport->CreateWorldDatabase();
	m_effectsDatabase->Load(m_renderer, m_effectsModelName, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_effectsDatabase->ResetEntities();
	}
	DrawLoadProgress(0.1f);

	GolHashTable* hashTable = g_hashTable;
	LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(gameDataDirectory));
	}

	m_trackDatabase = m_golExport->CreateWorldDatabase();
	m_trackDatabase->Load(m_renderer, m_trackModelName, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_trackDatabase->ResetEntities();
	}
	DrawLoadProgress(0.24f);

	m_trackCollidable = m_trackDatabase->GetCollidableEntities();
	if (m_cameraName[0]) {
		m_trackCamera = m_trackDatabase->FindCamera(m_cameraName);
	}
	DrawLoadProgress(0.26f);

	m_triggerDatabase = m_golExport->CreateWorldDatabase();
	m_triggerDatabase->Load(m_renderer, m_triggerModelName, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_triggerDatabase->ResetEntities();
	}
	BindSurfaceMaterials(p_mirror);
	DrawLoadProgress(0.34f);

	LegoChar name[sizeof(GolName)];
	::strncpy(name, m_collisionWorldName, sizeof(name));
	m_collisionWorld = m_triggerDatabase->FindBoundedEntity(name);
	DrawLoadProgress(0.36f);

	::strncpy(name, m_triggerWorldName, sizeof(name));
	m_triggerWorldEntity = m_triggerDatabase->FindBoundedEntity(name);

	if (m_extraTriggerWorldName[0]) {
		::strncpy(name, m_extraTriggerWorldName, sizeof(name));
		m_extraTriggerWorldEntity = m_triggerDatabase->FindBoundedEntity(name);
	}
	DrawLoadProgress(0.38f);

	m_sharedDatabase = m_golExport->CreateWorldDatabase();
	m_sharedDatabase->Load(m_renderer, m_sharedModelName, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_sharedDatabase->ResetEntities();
	}
	DrawLoadProgress(0.4f);

	m_materialAnimationDatabase = m_golExport->CreateWorldDatabase();
	m_materialAnimationDatabase->Load(m_renderer, m_materialAnimationModelName, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_materialAnimationDatabase->ResetEntities();
	}
	DrawLoadProgress(0.42f);
}

// FUNCTION: LEGORACERS 0x004330e0
void RaceSession::DestroyDatabases()
{
	if (m_golExport) {
		if (m_triggerDatabase) {
			m_golExport->DestroyWorldDatabase(m_triggerDatabase);
		}
		if (m_materialAnimationDatabase) {
			m_golExport->DestroyWorldDatabase(m_materialAnimationDatabase);
		}
		if (m_sharedDatabase) {
			m_golExport->DestroyWorldDatabase(m_sharedDatabase);
		}
		if (m_trackDatabase) {
			m_golExport->DestroyWorldDatabase(m_trackDatabase);
		}
		if (m_effectsDatabase) {
			m_golExport->DestroyWorldDatabase(m_effectsDatabase);
		}
	}

	GolNameTable* surfaceTable = &m_surfaceTable;
	surfaceTable->Clear();

	m_effectsDatabase = NULL;
	m_sharedDatabase = NULL;
	m_triggerDatabase = NULL;
	m_trackDatabase = NULL;
	m_collisionWorld = NULL;
	m_triggerWorldEntity = NULL;
	m_extraTriggerWorldEntity = NULL;
	m_trackCamera = NULL;
}

// FUNCTION: LEGORACERS 0x00433190
void RaceSession::LoadRouteRecords(LegoBool32 p_mirror)
{
	LegoChar fileName[12];
	LegoU32 loaded = FALSE;
	LegoU32 i;
	LegoU32 type;
	RaceRouteRecord* current = m_routeRecords;

	for (i = 0; i < static_cast<LegoU32>(m_context->m_racerCount); i++) {
		if (m_context->m_playerSetupSlots[i].m_slotState == 2 || m_demoMode) {
			fileName[0] = 'r';
			fileName[1] = static_cast<LegoChar>(i + '0');
			fileName[2] = '_';
			fileName[4] = '_';
			fileName[6] = '.';
			fileName[7] = 'r';
			fileName[8] = 'r';
			fileName[9] = m_context->m_useBinaryFiles ? 'b' : 'f';
			fileName[10] = '\0';

			LegoU32 frontCount = 0;
			LegoU32 middleCount = 0;
			LegoU32 sideCount = 0;
			LegoU32* count;

			for (type = 0; type < 3; type++) {
				switch (type) {
				case 0:
					fileName[3] = 'f';
					count = &frontCount;
					break;
				case 1:
					fileName[3] = 'm';
					count = &middleCount;
					break;
				case 2:
					fileName[3] = 's';
					count = &sideCount;
					break;
				default:
					count = NULL;
					break;
				}

				fileName[5] = '0';
				while (GolStream::FindFile(fileName) == GolStream::e_ioSuccess && *count < 10) {
					(*count)++;
					fileName[5] = static_cast<LegoChar>(*count + '0');
				}
			}

			if (frontCount || middleCount || sideCount) {
				g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;

				LegoU32 total = frontCount + middleCount + sideCount;
				LegoU32 index = g_randomTable[g_randomTableIndex] % total;
				if (index < frontCount) {
					fileName[3] = 'f';
				}
				else {
					index -= frontCount;
					if (index < middleCount) {
						fileName[3] = 'm';
					}
					else {
						index -= middleCount;
						fileName[3] = 's';
					}
				}
				fileName[5] = static_cast<LegoChar>(index + '0');

				current->Load(fileName, m_context->m_useBinaryFiles, p_mirror);
			}
		}

		current++;
	}

	for (i = 0; i < sizeOfArray(m_routeRecords); i++) {
		if (m_routeRecords[i].m_pathPoints) {
			loaded = TRUE;
		}
	}

	if (!loaded) {
		::strcpy(fileName, "r1_f_0");
		::strcat(fileName, m_context->m_useBinaryFiles ? ".rrb" : ".rrf");

		LegoBool32 foundFallback = GolStream::FindFile(fileName) == GolStream::e_ioSuccess;
		if (!foundFallback) {
			fileName[3] = 'm';
			foundFallback = GolStream::FindFile(fileName) == GolStream::e_ioSuccess;

			if (!foundFallback) {
				fileName[3] = 's';
				foundFallback = GolStream::FindFile(fileName) == GolStream::e_ioSuccess;
			}
		}

		if (foundFallback) {
			m_routeRecords[0].Load(fileName, m_context->m_useBinaryFiles, p_mirror);
		}
	}
}

// FUNCTION: LEGORACERS 0x00433460
void RaceSession::DestroyRouteRecords()
{
	RaceRouteRecord* current = m_routeRecords;
	LegoS32 remaining = sizeOfArray(m_routeRecords);
	do {
		current->Destroy();
		current++;
	} while (--remaining);
}

// FUNCTION: LEGORACERS 0x00433480
void RaceSession::LoadRaceContent(LegoBool32 p_mirror)
{
	if (m_checkpointFileName[0]) {
		m_checkpointGraph.Load(m_checkpointFileName, m_context->m_useBinaryFiles, p_mirror);
		BindCheckpointMaterials();
	}

	RacePowerupManager::Params powerupParams;
	RaceReset::Params resetParams;
	RaceEventTable::Params params;
	HazardContext dispatcherContext;
	RacerContext racerContext;
	RaceState::CreateRacersParams racerParams;

	DrawLoadProgress(0.45f);

	MabMaterialAnimation* materialAnimation = m_materialAnimationDatabase->GetMaterialAnimation(0);
	m_sharedParticleAnimation.Load(
		4,
		m_golExport,
		m_renderer,
		materialAnimation,
		m_sharedParticleAnimationName,
		m_context->m_useBinaryFiles
	);

	DrawLoadProgress(0.48f);

	m_animationList.Allocate(2);
	m_animationList.Activate(500, TRUE, NULL, NULL);

	m_trailManager.Initialize(m_renderer, m_golExport, 6);

	DrawLoadProgress(0.51f);

	m_decalManager.Initialize(m_renderer, m_golExport, m_trackCollidable, 4);
	LoadRouteRecords(p_mirror);

	DrawLoadProgress(0.54f);

	m_raceState.LoadStartPositions(m_startPositionsFileName, m_context->m_useBinaryFiles, p_mirror);

	DrawLoadProgress(0.56f);

	GolHashTable* hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_commonDataDirectory));
	}

	racerContext.m_renderer = m_renderer;
	racerContext.m_golExport = m_golExport;
	racerContext.m_trackCollidable = m_trackCollidable;
	racerContext.m_trackWorld = m_collisionWorld;
	racerContext.m_triggerWorld = m_extraTriggerWorldEntity;
	racerContext.m_soundSource = &m_soundSource;
	racerContext.m_powerupManager = &m_powerupManager;
	racerContext.m_particleAnimation = &m_particleAnimation;
	racerContext.m_sharedParticleAnimation = &m_sharedParticleAnimation;
	racerContext.m_decalManager = &m_decalManager;
	racerContext.m_eventTable = &m_eventTable;
	racerContext.m_surfaceTable = &m_surfaceTable;
	racerContext.m_shadowsEnabled = TRUE;
	racerContext.m_checkpointGraph = &m_checkpointGraph;
	racerContext.m_cheatFlags = m_context->m_cheatFlags;

	racerParams.m_racerCount = m_context->m_racerCount;
	racerParams.m_routeRecords = m_routeRecords;
	racerParams.m_timeRaceManager = m_timeRaceManager;
	racerParams.m_splitScreen = m_splitScreen;
	racerParams.m_lapCount = m_lapCount;

	LegoU32 racerIndex;
	RaceRouteRecord* routeRecord = m_routeRecords;
	for (racerIndex = 0; racerIndex < m_context->m_racerCount; racerIndex++) {
		LegoRacers::Context::PlayerSetupSlot* slot = &m_context->m_playerSetupSlots[racerIndex];
		racerParams.m_slots[racerIndex] = slot;

		if ((slot->m_slotState == 2 || m_demoMode) && routeRecord->m_pathPoints) {
			racerParams.m_racerRoutes[racerIndex] = routeRecord;
		}
		else {
			racerParams.m_racerRoutes[racerIndex] = NULL;
		}

		routeRecord++;
	}

	if (m_context->m_racerCount < sizeOfArray(racerParams.m_slots)) {
		::memset(
			&racerParams.m_slots[m_context->m_racerCount],
			0,
			(sizeOfArray(racerParams.m_slots) - m_context->m_racerCount) * sizeof(racerParams.m_slots[0])
		);
	}

	m_raceState.CreateRacers(&racerParams, &racerContext, m_context->m_useBinaryFiles);

	if (p_mirror) {
		m_raceState.SetRubberBandBoost(g_mirroredRaceStateRouteScale);
	}

	DrawLoadProgress(0.6f);

	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_gameDataDirectory));
	}

	for (racerIndex = 0; racerIndex < m_context->m_racerCount; racerIndex++) {
		if (m_context->m_playerSetupSlots[racerIndex].m_slotState == 0) {
			Racer* racer = &m_raceState.GetRacers()[racerIndex];
			RaceCameraController* cameraController = &m_cameraControllers[racerIndex];
			m_raceState.m_playerRacers[racerIndex] = racer;

			cameraController->SetRacer(racer);
			racer->InitializeSounds(cameraController, FALSE);
			racer->SetCameraView(m_context->m_cameraViewIndex, m_splitScreen);
			cameraController->Update(1.0f);
			cameraController->SetMode(0);
			cameraController->SnapPosition(&m_cameraStartPosition);
			cameraController->SetOrientation(&m_cameraStartDirection, &m_cameraStartUp);
		}

		g_raceLapCount = m_lapCount;
	}

	if (m_demoMode) {
		Racer* racer = m_raceState.GetRacers();
		racer->SwitchToAiControl();
		racer->m_flags |= Racer::c_flagDemoRacer;
	}

	if (!m_splitScreen) {
		m_raceState.SetCurrentRacer(m_raceState.m_playerRacers[0]);
	}
	else {
		m_raceState.SetCurrentRacer(NULL);
	}

	m_raceState.InitializeRacerVisuals(m_renderer, m_golExport);

	DrawLoadProgress(0.7f);

	m_skyState.Load(m_renderer, m_golExport, m_skyName, m_worldName, m_context->m_useBinaryFiles);

	DrawLoadProgress(0.75f);

	if (m_targetFileName[0]) {
		m_targetPoints.Load(m_targetFileName, m_context->m_useBinaryFiles, p_mirror);
	}

	params.m_trackDatabase = m_trackDatabase;
	params.m_sharedDatabase = m_sharedDatabase;
	params.m_triggerDatabase = m_triggerDatabase;
	params.m_materialAnimationDatabase = m_materialAnimationDatabase;
	params.m_soundSource = &m_soundSource;
	params.m_hazardManager = &m_hazardManager;
	params.m_particleAnimation = &m_particleAnimation;
	params.m_sharedParticleAnimation = &m_sharedParticleAnimation;
	params.m_skyState = &m_skyState;
	params.m_targetPoints = &m_targetPoints;
	params.m_name = m_eventFileName;
	params.m_binary = m_context->m_useBinaryFiles;
	params.m_mirror = p_mirror;
	m_eventTable.Load(&params);

	DrawLoadProgress(0.77f);

	dispatcherContext.m_eventQueue = &m_raceState.m_roster;
	dispatcherContext.m_context = m_context;
	dispatcherContext.m_soundSource = &m_soundSource;
	dispatcherContext.m_eventTable = &m_eventTable;
	dispatcherContext.m_trackDatabase = m_trackDatabase;
	dispatcherContext.m_sharedDatabase = m_sharedDatabase;
	dispatcherContext.m_triggerDatabase = m_triggerDatabase;
	dispatcherContext.m_particleAnimation = &m_sharedParticleAnimation;
	dispatcherContext.m_trackCollidable = m_trackCollidable;
	dispatcherContext.m_golExport = m_golExport;
	dispatcherContext.m_renderer = m_renderer;
	dispatcherContext.m_colliderTable = &m_surfaceTable;
	dispatcherContext.m_raceState = &m_raceState;
	dispatcherContext.m_triggerWorld = &m_triggerWorld;
	dispatcherContext.m_powerupManager = &m_powerupManager;
	dispatcherContext.m_trailManager = &m_trailManager;
	dispatcherContext.m_mirror = p_mirror;
	m_hazardManager.LoadHazards(&dispatcherContext, m_hazardFileName, m_context->m_useBinaryFiles);

	DrawLoadProgress(0.8f);

	m_racerCollisionWorlds.Initialize(m_triggerDatabase, &m_raceState);
	m_triggerWorld.Initialize(m_triggerDatabase, m_collisionWorldName, &m_eventTable, &m_surfaceTable);
	m_racerTriggers.Load(
		&m_raceState,
		&m_eventTable,
		&m_powerupManager,
		m_triggerDatabase,
		&m_racerCollisionWorlds,
		m_racerTriggerFileName,
		m_context->m_useBinaryFiles,
		p_mirror
	);

	DrawLoadProgress(0.84f);

	m_triggers
		.Load(m_raceState.GetEventQueue(), &m_eventTable, m_triggerFileName, m_context->m_useBinaryFiles, p_mirror);

	DrawLoadProgress(0.86f);

	m_timers.Load(m_raceState.GetEventQueue(), &m_eventTable, m_timerFileName, m_context->m_useBinaryFiles);

	DrawLoadProgress(0.88f);

	GolMaterial* material = NULL;
	if (m_materialAnimationDatabase != NULL && m_materialAnimationDatabase->GetMaterialLibraryCount() >= 2) {
		GolMaterialLibrary* materialLibrary = m_materialAnimationDatabase->GetMaterialLibrary(1);
		if (materialLibrary != NULL) {
			material = materialLibrary->GetItem(0);
		}
	}

	for (LegoU32 i = 0; i < sizeOfArray(m_huds); i++) {
		m_huds[i].Initialize(
			m_renderer,
			m_fontTable,
			&m_hudScratchString,
			m_hudImages,
			&m_raceState,
			m_timeRaceManager,
			&m_stringTable,
			&m_soundSource,
			m_timeRaceManager != NULL,
			m_returnToGarage
		);
		m_huds[i].SetMapInfo(material, m_mapMinX, m_mapMaxY, m_mapMaxX, m_mapMinY, p_mirror);
	}

	if (m_splitScreen) {
		m_huds[0].SetRacer(m_raceState.m_playerRacers[0]);
		m_huds[0].ResetDisplay(-1);
		m_huds[0].SetLayout(RaceHud::c_layoutSplitTop);

		m_huds[1].SetRacer(m_raceState.m_playerRacers[1]);
		m_huds[1].ResetDisplay(-1);
		m_huds[1].SetLayout(RaceHud::c_layoutSplitBottom);
	}
	else {
		m_huds[0].SetRacer(m_context->m_playerCount == 1 ? m_raceState.m_playerRacers[0] : m_raceState.GetRacers());
		m_huds[0].ResetDisplay(-1);
		m_huds[0].SetLayout(RaceHud::c_layoutFull);
	}

	DrawLoadProgress(0.9f);

	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_commonDataDirectory));
	}

	if (!m_demoMode) {
		m_dialog.Initialize(m_loadingFont, m_renderer, &m_stringTable, m_context->m_inputBindings[0].m_events[2]);
	}

	resetParams.m_context = m_context;
	resetParams.m_raceState = &m_raceState;
	resetParams.m_powerupManager = &m_powerupManager;
	resetParams.m_hazardManager = &m_hazardManager;
	resetParams.m_particleAnimation = &m_particleAnimation;
	resetParams.m_sharedParticleAnimation = &m_sharedParticleAnimation;
	resetParams.m_timeRaceManager = m_timeRaceManager;
	resetParams.m_racerTriggers = &m_racerTriggers;
	resetParams.m_triggers = &m_triggers;
	resetParams.m_collisionWorlds = &m_racerCollisionWorlds;
	resetParams.m_eventTable = &m_eventTable;
	m_raceReset.Initialize(&resetParams);

	m_particleAnimation.Load(
		10,
		m_golExport,
		m_renderer,
		m_effectsDatabase->GetMaterialAnimation(0),
		m_particleAnimationName,
		m_context->m_useBinaryFiles
	);

	DrawLoadProgress(0.93f);

	powerupParams.m_golExport = m_golExport;
	powerupParams.m_renderer = m_renderer;
	powerupParams.m_raceState = &m_raceState;
	powerupParams.m_collidable = m_trackCollidable;
	powerupParams.m_boundedEntity = m_triggerWorldEntity;
	powerupParams.m_collisionWorld = &m_triggerWorld;
	powerupParams.m_soundSource = &m_soundSource;
	powerupParams.m_cutsceneAnimation = &m_particleAnimation;
	powerupParams.m_trailManager = &m_trailManager;
	powerupParams.m_racerTriggers = &m_racerTriggers;
	powerupParams.m_animationList = &m_animationList;
	powerupParams.m_trackDatabase = m_powerupTrackDatabase;
	powerupParams.m_targetPoints = &m_targetPoints;
	powerupParams.m_cameraFov = m_splitScreen ? m_context->m_cameraFov - g_splitScreenFovDelta : m_context->m_cameraFov;
	powerupParams.m_cheatFlags = m_context->m_cheatFlags;
	m_powerupManager.Initialize(&powerupParams);

	m_powerupManager.LoadDatabases(m_powerupDatabaseName, m_turboDatabaseName, m_context->m_useBinaryFiles);

	DrawLoadProgress(0.97f);

	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_gameDataDirectory));
	}

	if (m_timeRaceManager) {
		LegoU32 nameLength = ::strlen(m_powerupFileName);
		(m_powerupFileName)[nameLength - 4] = '2';
		(m_powerupFileName)[nameLength - 3] = '.';
		(m_powerupFileName)[nameLength - 2] = 'P';
		(m_powerupFileName)[nameLength - 1] = 'W';
		(m_powerupFileName)[nameLength] = 'F';
		(m_powerupFileName)[nameLength + 1] = 0;
	}

	m_powerupManager.LoadPowerupFile(m_powerupFileName, m_context->m_useBinaryFiles, p_mirror);
	m_powerupManager.PreparePools(!m_splitScreen);
	m_powerupManager.CreatePools();
	m_powerupManager.ClearBricksAudible();

	PlayIntroMusic();
}

// FUNCTION: LEGORACERS 0x00434000
void RaceSession::DestroyRaceContent()
{
	if (m_context) {
		LegoU32 playerCount = m_context->m_playerCount;
		LegoU32 i = 0;

		if (playerCount > 0) {
			Racer** racer = m_raceState.m_playerRacers;
			do {
				if (*racer) {
					(*racer)->m_visuals.EndFlash();
					(*racer)->m_visuals.ClearColorTransform();
				}

				i++;
				racer++;
			} while (i < m_context->m_playerCount);
		}
	}

	m_dialog.Destroy();
	m_powerupManager.Destroy();

	if (m_golExport) {
		if (m_powerupTrackDatabase) {
			m_golExport->DestroyWorldDatabase(m_powerupTrackDatabase);
			m_powerupTrackDatabase = NULL;
		}
	}

	m_timers.Destroy();
	m_triggers.Destroy();
	m_racerTriggers.Destroy();
	m_racerCollisionWorlds.Destroy();
	m_hazardManager.Destroy();
	m_eventTable.Destroy();
	m_targetPoints.Reset();
	m_skyState.Clear();
	m_raceState.Destroy();
	m_checkpointGraph.Reset();
	m_decalManager.Destroy();
	m_trailManager.Destroy();
	m_animationList.Reset();
	m_sharedParticleAnimation.Clear();
	m_particleAnimation.Clear();

	RaceCameraController* cameraController = m_cameraControllers;
	Racer** racer = m_raceState.m_playerRacers;
	LegoS32 remaining = sizeOfArray(m_cameraControllers);
	do {
		*racer = NULL;
		cameraController->Reset();
		racer++;
		cameraController++;
	} while (--remaining);
}

// FUNCTION: LEGORACERS 0x00434170
void RaceSession::CreateCameras()
{
	const GolRenderTarget* renderTargetInfo = m_renderer->GetRenderTargetInfo();
	LegoU32 width = renderTargetInfo->GetWidth();
	LegoU32 height = renderTargetInfo->GetHeight();
	LegoU32 i = 0;

	if (m_context->m_playerCount > 0) {
		do {
			GolCamera* camera = m_golExport->CreateCamera();
			m_cameras[i] = camera;

			if (m_splitScreen) {
				camera->SetLens(
					m_context->m_cameraFov - g_splitScreenFovDelta,
					m_context->m_cameraNearClip,
					m_context->m_cameraFarClip,
					2.6666667f
				);
			}
			else {
				camera->SetLens(
					m_context->m_cameraFov,
					m_context->m_cameraNearClip,
					m_context->m_cameraFarClip,
					1.3333334f
				);
			}

			GolCamera* currentCamera = m_cameras[i];
			currentCamera->GetTransform()->SetPosition(&m_cameraStartPosition);
			currentCamera->m_flags |= GolCamera::c_flagViewDirty;

			m_cameras[i]->GetTransform()->SetDirectionUp(&m_cameraStartDirection, &m_cameraStartUp);
			m_cameras[i]->m_flags |= GolCamera::c_flagViewDirty;

			Rect viewport;
			if (!m_splitScreen) {
				viewport.m_left = 0;
				viewport.m_top = 0;
				viewport.m_right = width;
				viewport.m_bottom = height;
			}
			else {
				switch (i) {
				case 0:
					viewport.m_left = 0;
					viewport.m_top = 0;
					viewport.m_right = width;
					viewport.m_bottom = height >> 1;
					break;
				case 1:
					viewport.m_left = 0;
					viewport.m_top = height >> 1;
					viewport.m_right = width;
					viewport.m_bottom = height;
					break;
				}
			}

			m_cameras[i]->SetViewport(&viewport);

			RaceCameraController* cameraController = &m_cameraControllers[i];
			cameraController->Initialize(m_cameras[i], m_renderer);
			cameraController->m_dirty = TRUE;

			i++;
		} while (i < m_context->m_playerCount);
	}

	m_renderer->SetCamera(m_cameras[0]);
}

// FUNCTION: LEGORACERS 0x00434300
void RaceSession::DestroyCameras()
{
	if (m_golExport) {
		for (LegoS32 i = 0; i < sizeOfArray(m_cameras); i++) {
			if (m_cameras[i]) {
				m_golExport->DestroyCamera(m_cameras[i]);
			}
			m_cameras[i] = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00434340
void RaceSession::StartIntroCamera()
{
	if (m_trackCamera) {
		m_trackCamera->m_trackedEntity->PlayPart(0);
		m_trackCamera->m_trackedEntity->SetFlags(
			m_trackCamera->m_trackedEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation
		);

		GolAnimatedEntity* entity = m_trackCamera->m_trackedEntity;
		entity->ResetPartIndices();
		entity->SetActiveValue(0.0f);

		LegoU32 i = 0;
		m_trackCamera->m_trackedEntity->SetFlags(
			m_trackCamera->m_trackedEntity->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart
		);

		LegoU32 playerCount = m_context->m_playerCount;
		if (playerCount > 0) {
			GolCamera** camera = m_cameras;
			do {
				(*camera)->SetTrackedEntity(m_trackCamera->m_trackedEntity, m_trackCamera->m_trackedNodeIndex);
				i++;
				camera++;
			} while (i < m_context->m_playerCount);
		}
	}
}

// FUNCTION: LEGORACERS 0x004343e0
void RaceSession::InitializeInput()
{
	RaceSession* session = this;
	InputEventQueue* inputEvents = &session->m_inputEvents;
	inputEvents->Allocate(32);

	MouseDevice* mouse = session->m_inputManager->GetMouse();
	if (mouse) {
		mouse->SetCallback(inputEvents);
		mouse->SetExclusiveMode();
		mouse->Acquire();
	}

	KeyboardDevice* keyboard = session->m_inputManager->GetKeyboard();
	if (keyboard) {
		session->m_inputRouter.Initialize(keyboard, inputEvents);
		session->m_inputRouter.AcquireDevice();
	}

	LegoU32 playerCount;
	if (session->m_demoMode) {
		playerCount = 2;
	}
	else {
		playerCount = session->m_context->m_playerCount;
	}

	if (playerCount > 0) {
		PlayerControls* controls = session->m_playerControls;
		Racer** racer = session->m_raceState.m_playerRacers;
		LegoU32 playerIndex = 0;

		do {
			LegoBool32 bindingAcquired = FALSE;
			PlayerControls::InputState* inputSink = NULL;

			if (!session->m_demoMode) {
				controls->Initialize(*racer, inputEvents);
				inputSink = &controls->m_input;
			}

			InputBindingState::Entry* binding = &session->m_context->m_inputBindings[playerIndex];
			if (binding->m_deviceType == DIDEVTYPE_JOYSTICK && binding->m_deviceId < 16) {
				JoystickDevice* joystick = session->m_inputManager->FindJoystickByDeviceId(binding->m_deviceId);
				if (joystick && joystick->GetDeviceSubType() == binding->m_deviceSubType) {
					joystick->SetCallback(inputEvents);
					bindingAcquired = TRUE;
					joystick->Acquire();

					if (!session->m_demoMode) {
						if (binding->m_deviceSubType == 4) {
							joystick->SetAxisButtonEventsEnabled(TRUE);
						}

						LegoU32 event = binding->m_events[0];
						DirectInputDevice* source;
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->SetBinding(source, event, 0);

						event = binding->m_events[1];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->SetBinding(source, event, 1);

						event = binding->m_events[2];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->SetBinding(source, event, 2);

						event = binding->m_events[3];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->SetBinding(source, event, 3);

						event = binding->m_events[4];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->SetBinding(source, event, 4);

						event = binding->m_events[5];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->SetBinding(source, event, 5);

						event = binding->m_events[6];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->SetBinding(source, event, 6);

						event = binding->m_events[7];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->SetBinding(source, event, 7);

						event = binding->m_events[8];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->SetBinding(source, event, 8);

						inputSink->AcquireDevices();
					}
				}
			}

			if (!session->m_demoMode) {
				if (binding->m_deviceType == DIDEVTYPE_KEYBOARD && keyboard) {
					inputSink->SetBinding(keyboard, binding->m_events[0], 0);
					inputSink->SetBinding(keyboard, binding->m_events[1], 1);
					inputSink->SetBinding(keyboard, binding->m_events[2], 2);
					inputSink->SetBinding(keyboard, binding->m_events[3], 3);
					inputSink->SetBinding(keyboard, binding->m_events[4], 4);
					inputSink->SetBinding(keyboard, binding->m_events[5], 5);
					inputSink->SetBinding(keyboard, binding->m_events[6], 6);
					inputSink->SetBinding(keyboard, binding->m_events[7], 7);
					inputSink->SetBinding(keyboard, binding->m_events[8], 8);
					bindingAcquired = TRUE;
				}

				m_inputRouter.AddSink(inputSink);

				if (!bindingAcquired) {
					GOL_FATALERROR_MESSAGE("Could not acquire controller for player");
				}

				session->m_forceFeedback[playerIndex].Initialize(inputSink->m_devices[4]);
				(*racer)->m_forceFeedback = &session->m_forceFeedback[playerIndex];
				controls->DetectAnalogDevice();
			}

			racer++;
			playerIndex++;
			controls++;
			playerCount--;
		} while (playerCount);
	}

	session->m_inputManager->PollDevices(0);
	inputEvents->ClearQueue();
}

// FUNCTION: LEGORACERS 0x004348a0
void RaceSession::DestroyInput()
{
	InputManager* inputManager = m_inputManager;
	if (!inputManager) {
		m_inputEvents.Reset();
		return;
	}

	InputDevice* source = inputManager->GetMouse();
	if (source) {
		source->SetCallback(NULL);
		source->Unacquire();
	}

	PlayerControls* controls = m_playerControls;
	RaceForceFeedback* forceFeedback = m_forceFeedback;
	for (LegoS32 i = 0; i < sizeOfArray(m_playerControls); i++) {
		forceFeedback->Destroy();
		controls->Destroy();
		forceFeedback++;
		controls++;
	}

	m_inputEvents.Reset();
	m_inputRouter.UnacquireDevice();
	m_inputRouter.Reset();
}

// FUNCTION: LEGORACERS 0x00434930
void RaceSession::PlayIntroMusic()
{
	if (m_music) {
		m_music->Stop();
		m_musicGroup->DestroyMusicInstance(m_music);
		m_music = NULL;
	}

	m_music = m_musicGroup->CreateMusicInstance(0);

	if (m_music) {
		m_music->SetVolume(m_musicVolume);
		m_music->Play(FALSE);
	}
}

// FUNCTION: LEGORACERS 0x004349a0
void RaceSession::UpdateIntroState()
{
	if (m_trackCamera && m_cameras[0] && m_cameras[0]->m_trackedEntity &&
		m_cameras[0]->m_trackedEntity->IsPartAnimationDone()) {
		GolVec3 position;
		GolVec3 forward;
		GolVec3 right;
		GolCamera** camera = m_cameras;

		GolCamera* currentCamera = *camera;
		GolVec3* positionPtr = &position;
		currentCamera->m_transform->GetPosition(positionPtr);

		currentCamera = *camera;
		GolVec3* rightPtr = &right;
		GolVec3* forwardPtr = &forward;
		currentCamera->m_transform->GetDirectionUp(forwardPtr, rightPtr);

		RaceCameraController* cameraController = m_cameraControllers;
		LegoS32 remaining = sizeOfArray(m_cameraControllers);
		do {
			if (*camera) {
				(*camera)->ClearTrackedEntity();
				positionPtr = &position;
				cameraController->SnapPosition(positionPtr);

				rightPtr = &right;
				forwardPtr = &forward;
				cameraController->SetOrientation(forwardPtr, rightPtr);
			}

			camera++;
			cameraController++;
		} while (--remaining);

		m_elapsedMs = 0;
	}

	if (m_elapsedMs >= 2000) {
		GolCamera* camera = m_cameras[0];
		if (!camera || !camera->m_trackedEntity) {
			m_elapsedMs = 0;
			m_state = 2;

			LegoU32 i = 0;
			if (m_context->m_playerCount > 0) {
				RaceForceFeedback* forceFeedback = m_forceFeedback;
				Racer** racer = m_raceState.m_playerRacers;
				RaceHud* hud = m_huds;
				do {
					(*racer)->ReapplyCameraView();
					if (!m_returnToGarage) {
						hud->StartCountdown();
					}
					(*racer)->StartEngine();
					forceFeedback->StartEngineEffect();

					RaceHud* nextHud = hud + 1;
					i++;
					racer++;
					hud = nextHud;
					forceFeedback++;
				} while (i < m_context->m_playerCount);
			}

			if (m_standings) {
				m_standings->ClearRoundPoints();
			}

			UpdateCountdownState();
		}
	}
}

// FUNCTION: LEGORACERS 0x00434b00
void RaceSession::UpdateCountdownState()
{
	if (m_elapsedMs < 3000 && !m_returnToGarage) {
		return;
	}

	m_elapsedMs = 0;
	m_state = 3;
	m_raceState.StartRace();

	LegoU32 i = 0;
	if (m_context->m_playerCount > 0) {
		PlayerControls* controls = m_playerControls;
		do {
			if (controls->m_racer) {
				controls->TryStartBoost();
			}

			i++;
			controls++;
		} while (i < m_context->m_playerCount);
	}

	m_powerupManager.SetBricksAudible();

	if (m_timeRaceManager) {
		m_timeRaceManager->AttachRacer(m_raceState.m_playerRacers[0]);
	}

	if (m_music) {
		m_music->Stop();
		m_musicGroup->DestroyMusicInstance(m_music);

		LegoU32 musicIndex = 1;
		MusicGroup* musicGroup = m_musicGroup;
		if (musicGroup->GetMusicCount() > 4 && !m_standings) {
			LegoU32 randomValue = 0;
			LegoU32 randomState = g_randomTableIndex;
			g_randomTableIndex = (randomState + 1) & 0x3ff;
			musicGroup = m_musicGroup;
			randomValue = g_randomTable[g_randomTableIndex];
			LegoU32 randomIndex = randomValue % (musicGroup->GetMusicCount() - 3);
			switch (randomIndex) {
			case 0:
				musicIndex = 1;
				break;
			case 1:
				musicIndex = 4;
				break;
			case 2:
				musicIndex = 5;
				break;
			case 3:
				musicIndex = 6;
				break;
			default:
				musicIndex = 1;
				break;
			}
		}

		m_music = m_musicGroup->CreateMusicInstance(musicIndex);
		if (m_music) {
			m_music->SetVolume(m_musicVolume);
			m_music->Play(TRUE);
		}
	}

	m_finishedCount = 0;
	UpdateRacingState();
}

// FUNCTION: LEGORACERS 0x00434c80
void RaceSession::UpdateRacingState()
{
	LegoU32 racerIndex = 0;
	if (m_context->m_racerCount > 0) {
		do {
			Racer* racer = &m_raceState.GetRacers()[racerIndex];
			if (racer->m_lapsCompleted >= m_lapCount && !(racer->m_flags & 0x1000)) {
				racer->m_flags |= 0x1000;

				if (m_standings) {
					m_standings->AwardPoints(racer->m_materialIndex, m_finishedCount);
				}

				m_finishedCount++;
				racer->SetStandingsPosition(m_finishedCount);

				if (racer->m_controlMode != Racer::c_controlAi || (m_demoMode && racerIndex == 0)) {
					LegoU32 playerIndex = 0;
					Racer** playerRacer = m_raceState.m_playerRacers;
					while (*playerRacer != racer && playerIndex < m_context->m_playerCount) {
						playerRacer++;
						playerIndex++;
					}

					m_huds[playerIndex].ShowFinish();
					m_elapsedMs = 0;
					m_state = 4;
					if (m_returnToGarage) {
						m_elapsedMs = 9000;
					}

					if (m_playerControls[playerIndex].m_racer) {
						m_playerControls[playerIndex].EnterAiControl();
					}

					m_powerupManager.CancelWarp(racer);

					if (!(racer->m_flags & Racer::c_flagGhost) && !(racer->m_flags & 0x200000) && !m_returnToGarage) {
						m_cameraControllers[playerIndex].SetView(4, m_splitScreen);
					}

					if (m_timeRaceManager) {
						m_timeRaceManager->UpdateBestRun();
					}

					if (m_music) {
						m_music->Stop();
						m_musicGroup->DestroyMusicInstance(m_music);

						if (racer->m_standingsPosition == 1) {
							m_music = m_musicGroup->CreateMusicInstance(3);
						}
						else {
							m_music = m_musicGroup->CreateMusicInstance(2);
						}

						if (m_music) {
							m_music->SetVolume(m_musicVolume);
							m_music->Play(FALSE);
						}
					}

					if (m_standings) {
						m_standings->m_font = m_loadingFont;
						m_standings->m_raceState = &m_raceState;
						m_standings->m_stringTable = &m_stringTable;
					}

					UpdateFinishedState();
					return;
				}
			}

			racerIndex++;
		} while (racerIndex < m_context->m_racerCount);
	}
}

// FUNCTION: LEGORACERS 0x00434eb0
void RaceSession::UpdateFinishedState()
{
	if (m_elapsedMs > 9000) {
		if (!m_animationList.HasActive() && !m_standings) {
			m_animationList.Activate(1000, FALSE, NULL, NULL);
		}
	}

	if (m_timeRaceManager && m_elapsedMs > 9500) {
		if (m_pauseState != 2) {
			m_pauseState = 2;
			OpenPauseDialog();
		}
		return;
	}

	if (m_elapsedMs >= 10000) {
		m_elapsedMs = 0;
		m_state = 5;

		LegoU32 i = 0;
		if (m_context->m_racerCount > 0) {
			Racer* racer = m_raceState.GetRacers();
			do {
				if (!(racer->m_flags & 0x1000)) {
					if (m_standings) {
						m_standings->AwardPoints(racer->m_materialIndex, m_finishedCount);
					}

					m_finishedCount++;
					racer->SetStandingsPosition(m_finishedCount);
				}

				m_context->m_playerSetupSlots[i].m_finishPosition = (LegoU8) racer->m_standingsPosition;
				i++;
				racer++;
			} while (i < m_context->m_racerCount);
		}

		UpdateResultsState();
		return;
	}

	LegoU32 racerIndex = 0;
	if (m_context->m_racerCount > 0) {
		Racer* racer = m_raceState.GetRacers();
		do {
			if (racer->m_lapsCompleted >= m_lapCount && !(racer->m_flags & 0x1000)) {
				racer->m_flags |= 0x1000;

				if (m_standings) {
					m_standings->AwardPoints(racer->m_materialIndex, m_finishedCount);
				}

				m_finishedCount++;
				racer->SetStandingsPosition(m_finishedCount);

				if (racer->m_controlMode != Racer::c_controlAi) {
					LegoU32 playerIndex = 0;
					Racer** playerRacer = m_raceState.m_playerRacers;
					while (*playerRacer != racer && playerIndex < m_context->m_playerCount) {
						playerRacer++;
						playerIndex++;
					}

					if (m_playerControls[playerIndex].m_racer) {
						m_playerControls[playerIndex].EnterAiControl();
					}

					m_powerupManager.CancelWarp(racer);

					if (!(racer->m_flags & Racer::c_flagGhost) && !(racer->m_flags & 0x200000)) {
						m_cameraControllers[playerIndex].SetView(4, m_splitScreen);
					}
				}
			}

			if ((racer->m_flags & 0x1000) && racer->m_cameraController && !(racer->m_flags & Racer::c_flagGhost) &&
				!(racer->m_flags & 0x200000) && racer->m_cameraViewIndex != 4 && !m_returnToGarage) {
				racer->m_cameraController->SetView(4, m_splitScreen);
			}

			racerIndex++;
			racer++;
		} while (racerIndex < m_context->m_racerCount);
	}

	if (m_standings && m_elapsedMs > 5000) {
		m_standings->Update(m_golApp->GetFrameDeltaMs());
	}
}

// FUNCTION: LEGORACERS 0x00435180
void RaceSession::UpdateResultsState()
{
	if (m_elapsedMs > 4000) {
		if (!m_animationList.HasActive()) {
			m_animationList.Activate(1000, FALSE, NULL, NULL);
		}
	}

	if (m_elapsedMs < 5000 && m_standings) {
		m_standings->Update(m_golApp->GetFrameDeltaMs());
		return;
	}

	m_elapsedMs = 0;
	m_running = 0;
}

// FUNCTION: LEGORACERS 0x004351f0
void RaceSession::UpdateHuds()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_huds); i++) {
		m_huds[i].Update(m_golApp->GetFrameDeltaMs());
	}
}

// FUNCTION: LEGORACERS 0x00435220
void RaceSession::Update()
{
	LegoU32 elapsedMs = m_golApp->GetFrameDeltaMs();
	if (m_context->m_cheatFlags & c_cheatFastForward) {
		elapsedMs = static_cast<LegoU32>(
			static_cast<LegoFloat>(static_cast<LegoS32>(m_golApp->GetFrameDeltaMs())) * g_unk0x004b08c0
		);
	}

	if (!(m_pauseState && ProcessDialogs(elapsedMs))) {
		if (elapsedMs > m_demoTextMs) {
			m_demoTextMs = c_demoTextCycleMs;
		}
		else {
			m_demoTextMs -= elapsedMs;
		}

		m_trackDatabase->Update(elapsedMs);
		m_materialAnimationDatabase->Update(elapsedMs);
		m_sharedDatabase->Update(elapsedMs);
		m_powerupManager.Update(elapsedMs);
		m_racerCollisionWorlds.Update(elapsedMs);
		m_triggers.Update(elapsedMs);
		m_racerTriggers.Update(elapsedMs);
		m_particleAnimation.Update(elapsedMs);
		m_sharedParticleAnimation.Update(elapsedMs);
		m_trailManager.Update(elapsedMs);
		m_eventTable.Update(elapsedMs);
		m_hazardManager.Update(elapsedMs);
		m_timers.Update(elapsedMs);
		m_animationList.Update(elapsedMs);
		m_soundManager->Update(elapsedMs);

		LegoU32 i;
		if (!m_demoMode) {
			for (i = 0; i < m_context->m_playerCount; i++) {
				LegoFloat forwardSpeed = m_raceState.m_playerRacers[i]->m_physics.m_forwardSpeed;
				m_forceFeedback[i].Update(elapsedMs, forwardSpeed);
				m_playerControls[i].Update(elapsedMs);
			}
		}

		LegoU32 remainingMs = elapsedMs;
		while (remainingMs > 0) {
			LegoS32 stepMs;
			LegoU32 remainingAfterStep;

			if (remainingMs > c_updateStepMs) {
				remainingMs -= c_updateStepMs;
				stepMs = c_updateStepMs;
				remainingAfterStep = remainingMs;
			}
			else {
				remainingAfterStep = 0;
				stepMs = static_cast<LegoS32>(remainingMs);
				remainingMs = 0;
			}

			m_raceState.UpdateRacers(stepMs);

			for (i = 0; i < m_context->m_playerCount; i++) {
				m_cameraControllers[i].Update(static_cast<LegoFloat>(stepMs));
			}

			remainingMs = remainingAfterStep;
			if (m_timeRaceManager) {
				m_timeRaceManager->Update(stepMs);
			}
		}

		m_decalManager.Update(elapsedMs);
		m_hazardManager.UpdatePerRacer(m_cameras[0], m_cameraControllers[0].m_racer);
		m_skyState.Update(elapsedMs);

		if (m_state == 2 || m_state == 3 || m_state == 4) {
			UpdateHuds();
		}
	}
}

// FUNCTION: LEGORACERS 0x004354d0
void RaceSession::Draw()
{
	if (m_powerupManager.GetExclusiveDraw()) {
		m_powerupManager.Draw(FALSE);
		return;
	}

	GolAppEventHandler::OnCloseRequested();
	m_renderer->SetCamera(m_cameras[0]);
	ClearViewport();

	if (m_splitScreen) {
		m_raceState.m_playerRacers[0]->m_visuals.UpdateShadow(m_cameras[0]);
		m_raceState.m_playerRacers[1]->m_visuals.UpdateShadow(m_cameras[1]);
	}
	else {
		m_raceState.UpdateShadows(m_cameras[0]);
	}

	LegoU32 viewportIndex = 1;
	if (m_splitScreen) {
		m_renderer->SelectViewport(viewportIndex);
	}
	else {
		m_renderer->SelectViewport(FALSE);
	}

	if (m_raceState.m_playerRacers[0]->m_flags & Racer::c_flagGhost) {
		m_powerupManager.Draw(viewportIndex);
	}
	else {
		GolVec3 cameraPosition;
		GolCamera* camera = m_cameras[0];
		GolVec3* position = &cameraPosition;
		camera->m_transform->GetPosition(position);

		position = &cameraPosition;
		m_skyState.SetPosition(position);

		switch (m_state) {
		case 1:
			DrawRacerViewportForState1(m_raceState.m_playerRacers[0]);
			break;
		case 2:
			DrawRacerViewportForState2(m_raceState.m_playerRacers[0]);
			break;
		case 3:
			DrawRacerViewportForState3(m_raceState.m_playerRacers[0]);
			break;
		case 4:
			DrawRacerViewportForState4(m_raceState.m_playerRacers[0]);
			break;
		case 5:
			DrawRacerViewportForState5(m_raceState.m_playerRacers[0]);
			break;
		}
	}

	while (viewportIndex < m_context->m_playerCount) {
		m_renderer->SetCamera(m_cameras[viewportIndex]);
		m_renderer->ApplyCamera();
		m_renderer->SelectViewport(viewportIndex + 1);

		if (m_raceState.m_playerRacers[viewportIndex]->m_flags & Racer::c_flagGhost) {
			m_powerupManager.Draw(FALSE);
		}
		else {
			GolVec3 cameraPosition;
			GolCamera* camera = m_cameras[viewportIndex];
			GolVec3* position = &cameraPosition;
			camera->m_transform->GetPosition(position);

			position = &cameraPosition;
			m_skyState.SetPosition(position);

			switch (m_state) {
			case 1:
				DrawRacerViewportForState1(m_raceState.m_playerRacers[viewportIndex]);
				break;
			case 2:
				DrawRacerViewportForState2(m_raceState.m_playerRacers[viewportIndex]);
				break;
			case 3:
				DrawRacerViewportForState3(m_raceState.m_playerRacers[viewportIndex]);
				break;
			case 4:
				DrawRacerViewportForState4(m_raceState.m_playerRacers[viewportIndex]);
				break;
			case 5:
				DrawRacerViewportForState5(m_raceState.m_playerRacers[viewportIndex]);
				break;
			}
		}

		viewportIndex++;
	}

	if (m_splitScreen) {
		m_renderer->SelectViewport(FALSE);
	}

	m_renderer->DisableZBuffer(FALSE);

	switch (m_state) {
	case 1:
		DrawOverlaysForState1();
		break;
	case 2:
		DrawOverlaysForState2();
		break;
	case 3:
		DrawOverlaysForState3();
		break;
	case 4:
		DrawOverlaysForState4();
		break;
	case 5:
		DrawOverlaysForState5();
		break;
	}

	m_renderer->EnableZBuffer();
	FlushOverlays();
}

// Separate helpers keep MSVC from merging the identical switch arms in Draw; ICF folds the bodies.

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState1(Racer* p_racer)
{
	m_skyState.Draw(m_renderer);
	DrawScene(p_racer);
	DrawTransparent();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState2(Racer* p_racer)
{
	m_skyState.Draw(m_renderer);
	DrawScene(p_racer);
	DrawTransparent();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState3(Racer* p_racer)
{
	m_skyState.Draw(m_renderer);
	DrawScene(p_racer);
	DrawTransparent();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState4(Racer* p_racer)
{
	m_skyState.Draw(m_renderer);
	DrawScene(p_racer);
	DrawTransparent();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState5(Racer* p_racer)
{
	m_skyState.Draw(m_renderer);
	DrawScene(p_racer);
	DrawTransparent();
}

// FUNCTION: LEGORACERS 0x004357e0
void RaceSession::DrawOverlaysForState1()
{
	DrawDemoText();
	m_animationList.Draw(m_renderer);
	DrawPauseDialog();
}

// FUNCTION: LEGORACERS 0x00435800
void RaceSession::DrawOverlaysForState2()
{
	DrawHuds();
	DrawDemoText();
	m_animationList.Draw(m_renderer);
	DrawPauseDialog();
}

// FUNCTION: LEGORACERS 0x00435830
void RaceSession::DrawOverlaysForState3()
{
	DrawHuds();
	DrawDemoText();
	GolAppEventHandler::OnCloseRequested();
	m_animationList.Draw(m_renderer);
	DrawPauseDialog();
}

// FUNCTION: LEGORACERS 0x00435860
void RaceSession::DrawOverlaysForState4()
{
	DrawHuds();
	if (m_standings && m_running && m_elapsedMs > 5000) {
		for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
			m_huds[i].m_bannerMs = 0;
		}

		m_standings->Draw(FALSE);
	}

	DrawDemoText();
	m_animationList.Draw(m_renderer);
	DrawPauseDialog();
}

// FUNCTION: LEGORACERS 0x004358e0
void RaceSession::DrawOverlaysForState5()
{
	if (m_standings && m_running) {
		m_standings->Draw(TRUE);
	}

	DrawDemoText();
	m_animationList.Draw(m_renderer);
	DrawPauseDialog();
}

// FUNCTION: LEGORACERS 0x00435920
void RaceSession::DrawPauseDialog()
{
	if (m_pauseState) {
		m_dialog.Draw();
	}
}

// FUNCTION: LEGORACERS 0x00435940
void RaceSession::ClearViewport()
{
	if (m_clearMode) {
		m_renderer->BeginFrame(2);
	}
	else {
		m_renderer->BeginFrame(6);
	}
}

// FUNCTION: LEGORACERS 0x00435960
void RaceSession::DrawScene(Racer* p_racer)
{
	m_raceState.DrawRacerEntities(m_renderer, p_racer);
	m_powerupManager.Draw(FALSE);
	m_particleAnimation.Draw(m_renderer);
	m_sharedParticleAnimation.Draw(m_renderer);
	m_trailManager.DrawOpaque(m_renderer);

	m_trackDatabase->DrawAnimatedEntities(m_renderer);
	m_trackDatabase->DrawModelEntities(m_renderer);
	m_trackDatabase->DrawSprites(m_renderer);
	m_trackDatabase->DrawCollidableEntities(m_renderer);

	m_decalManager.DrawOpaque(m_renderer);
}

// FUNCTION: LEGORACERS 0x00435a00
void RaceSession::DrawTransparent()
{
	m_sharedDatabase->DrawWorld();
	m_raceState.DrawRacersTransparent(m_renderer);
	m_hazardManager.Draw(m_renderer);
	m_powerupManager.DrawTransparent();
	m_particleAnimation.DrawTransparent(m_renderer);
	m_sharedParticleAnimation.DrawTransparent(m_renderer);
	m_trailManager.DrawTransparent(m_renderer);
	m_decalManager.DrawTransparent(m_renderer);

	if (m_timeRaceManager) {
		m_timeRaceManager->Draw(m_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00435a90
void RaceSession::DrawHuds()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_huds); i++) {
		m_huds[i].Draw();
	}
}

// FUNCTION: LEGORACERS 0x00435ab0
void RaceSession::DrawDemoText()
{
	if (m_demoMode && m_demoTextMs > c_overlayDrawDelayMs) {
		GolString string;
		const GolRenderTarget* renderTargetInfo = m_renderer->GetRenderTargetInfo();
		string.CopyFromBufSelection(m_stringTable.GetStringBuffer(c_overlayStringId), 0);

		LegoS32 textWidth;
		LegoS32 textHeight;
		m_loadingFont->MeasureString(&string, &textWidth, &textHeight);

		m_renderer->DrawString(
			&string,
			m_loadingFont,
			(renderTargetInfo->GetWidthU32() >> 1) - (static_cast<LegoU32>(textWidth) >> 1),
			renderTargetInfo->GetHeightU32() - textHeight - c_overlayBottomPadding,
			1.0f,
			1.0f,
			NULL,
			0
		);
	}
}

// FUNCTION: LEGORACERS 0x00435ba0
void RaceSession::DrawLoadProgress(LegoFloat p_progress)
{
	m_renderer->BeginFrame(FALSE);
	m_renderer->SelectViewport(FALSE);
	m_loadingScreen.SetProgress(p_progress);
	m_loadingScreen.Draw();
	m_renderer->EndFrame();
	m_golApp->PresentFrame();
}

// FUNCTION: LEGORACERS 0x00435bf0
void RaceSession::FlushOverlays()
{
	m_renderer->EndFrame();
}

// FUNCTION: LEGORACERS 0x00435c00
void RaceSession::OnKeyDown(LegoU32 p_keyCode)
{
	if (m_demoMode && (p_keyCode & c_keySourceAbortMask)) {
		m_running = 0;
		m_context->m_flags |= LegoRacers::Context::c_flagBit7;
		return;
	}

	switch (p_keyCode) {
	case c_keyEscape:
	case c_keyPause:
		if (!m_pauseState) {
			m_pauseState = 1;
			OpenPauseDialog();
		}
		break;
	case c_keyPrintScreen:
		TakeScreenshot();
		break;
	}

	if (m_abortKeyMask == 3) {
		m_running = 0;
	}

	if (m_abortKeyMask == 7) {
		m_running = 0;
		m_context->m_running = FALSE;
	}

	if (m_pauseState) {
		m_dialog.OnKeyDown(p_keyCode);
	}
}

// FUNCTION: LEGORACERS 0x00435cc0
void RaceSession::OnKeyUp(LegoU32 p_keyCode)
{
	switch (p_keyCode) {
	case c_keyQ:
		m_abortKeyMask &= ~c_abortKeyQ;
		break;
	case c_keyLeftControl:
		m_abortKeyMask &= ~c_abortKeyControl;
		break;
	case c_keyLeftShift:
		m_abortKeyMask &= ~c_abortKeyShift;
		break;
	}

	if (m_pauseState) {
		m_dialog.OnKeyUp(p_keyCode);
	}
}

// FUNCTION: LEGORACERS 0x00435d20
void RaceSession::BindSurfaceMaterials(LegoBool32 p_mirror)
{
	RaceSession* raceSession = this;

	if (!raceSession->m_surfaceFileName[0]) {
		LegoU32 zero = 0;
		for (LegoU32 i = zero; i < raceSession->m_triggerDatabase->GetBoundedEntityCount(); i++) {
			GolModelMaterialTable* materials =
				raceSession->m_triggerDatabase->GetBoundedEntities()[i].GetMaterialTable();

			for (LegoU32 j = zero; j < materials->m_count; j++) {
				GolMaterial* material = materials->GetMaterial(j);
				material->EnableFlagBit18();
				material->SetUserData(NULL);
			}
		}
		return;
	}

	SurfaceTable* surfaceTable = &raceSession->m_surfaceTable;
	surfaceTable->Load(raceSession->m_surfaceFileName, raceSession->m_context->m_useBinaryFiles, p_mirror);

	for (LegoU32 i = 0; i < raceSession->m_triggerDatabase->GetBoundedEntityCount(); i++) {
		GolModelMaterialTable* materials = raceSession->m_triggerDatabase->GetBoundedEntities()[i].GetMaterialTable();

		for (LegoU32 j = 0; j < materials->m_count; j++) {
			GolMaterial* material = materials->GetMaterial(j);
			GolMaterial::NameRecord materialName = material->GetNameRecord();

			void* materialPosition;
			if (surfaceTable->GetNameEntries() == NULL) {
				materialPosition = NULL;
			}
			else {
				materialPosition = surfaceTable->GetName(materialName.m_name);
			}
			material->SetUserData(materialPosition);
			material->EnableFlagBit18();
		}
	}
}

// FUNCTION: LEGORACERS 0x00435e70
void RaceSession::BindCheckpointMaterials()
{
	LegoU32 materialIndex;
	LegoU32 checkpointIndex;

	if (m_extraTriggerWorldEntity) {
		GolModelMaterialTable* materials = m_extraTriggerWorldEntity->GetBoundingVolume()->GetMaterialTable();
		materialIndex = 0;
		checkpointIndex = 0;

		if (materials->GetCount() > 0) {
			do {
				GolMaterial* material = materials->GetMaterial(materialIndex);
				GolMaterial::NameRecord materialName = material->GetNameRecord();
				if (materialName.m_name[0] >= '0' && materialName.m_name[0] <= '9') {
					material->SetUserData(m_checkpointGraph.GetCheckpoint(checkpointIndex));
					material->EnableFlagBit18();
					checkpointIndex++;
				}
				else {
					void* materialPosition;
					if (m_surfaceTable.GetNameEntries() == NULL) {
						materialPosition = NULL;
					}
					else {
						materialPosition = m_surfaceTable.GetName(materialName.m_name);
					}

					material->SetUserData(materialPosition);
					material->EnableFlagBit18();
				}

				materialIndex++;
			} while (materialIndex < materials->GetCount());
		}
	}
}

// FUNCTION: LEGORACERS 0x00435f20
void RaceSession::TakeScreenshot()
{
	GolHashTable::Entry* currentEntry;
	GolBmpWriterFile bmpWriter;
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

// FUNCTION: LEGORACERS 0x00436010
void RaceSession::OpenPauseDialog()
{
	LegoU32 playerIndex = 0;
	if (m_context->m_playerCount > 0) {
		PlayerControls* controls = m_playerControls;
		RaceForceFeedback* forceFeedback = m_forceFeedback;

		do {
			controls->m_input.m_enabled = FALSE;
			controls->m_input.ReleaseAllInputs();
			forceFeedback->Pause();

			playerIndex++;
			controls++;
			forceFeedback++;
		} while (playerIndex < m_context->m_playerCount);
	}

	m_inputRouter.m_enabled = FALSE;
	m_inputRouter.ReleaseAllInputs();

	for (LegoU32 i = 0; i < sizeOfArray(m_huds); i++) {
		m_huds[i].m_visible = FALSE;
	}

	if (m_standings) {
		m_standings->m_isVisible = FALSE;
	}

	switch (m_pauseState) {
	case 1:
		if (m_standings) {
			m_dialog.Open(3, &g_pauseMenuStringIds[4], g_pauseMenuStringIds[3], 0xffff, 0);
		}
		else {
			m_dialog.Open(3, &g_pauseMenuStringIds[0], g_pauseMenuStringIds[3], 0xffff, 0);
		}
		break;
	case 2:
		if (m_timeRaceManager->HasBeatenRecord()) {
			m_dialog.Open(2, &g_pauseMenuStringIds[8], g_pauseMenuStringIds[12], g_pauseMenuStringIds[13], 0);
		}
		else {
			m_dialog.Open(2, &g_pauseMenuStringIds[8], g_pauseMenuStringIds[10], g_pauseMenuStringIds[11], 0);
		}
		break;
	case 3:
		m_dialog.Open(2, &g_pauseMenuStringIds[8], g_pauseMenuStringIds[14], 0xffff, 1);
		break;
	}

	MusicInstance* musicInstance = m_music;
	if (musicInstance) {
		musicInstance->Pause();
	}

	m_soundManager->Pause();
}

// FUNCTION: LEGORACERS 0x00436160
void RaceSession::ProcessPauseDialog()
{
	LegoU32 selectionIndex = m_dialog.GetSelectionIndex();
	for (LegoS32 i = 0; i < sizeOfArray(m_huds); i++) {
		m_huds[i].m_visible = TRUE;
	}

	if (m_standings) {
		m_standings->m_isVisible = TRUE;
	}

	switch (m_pauseState) {
	case 3:
		if (!selectionIndex) {
			if (m_pendingAction == 1) {
				if (!m_standings || (m_context->m_flags & LegoRacers::Context::c_flagFirstRace)) {
					if (m_standings) {
						m_standings->ClearPoints();
					}
					RestartRace();
				}
				else {
					m_running = 0;
					m_context->m_flags |= LegoRacers::Context::c_flagRestartCircuit;
				}
			}
			else if (m_pendingAction == 2) {
				m_running = 0;
				m_context->m_flags |= LegoRacers::Context::c_flagAbortRace;
			}
		}

		m_pendingAction = 0;
		break;
	case 2:
		if (!selectionIndex) {
			if (m_timeRaceManager) {
				m_timeRaceManager->PrepareRun();
			}
			RestartRace();
		}
		else {
			m_running = 0;
		}
		break;
	case 1:
		if (selectionIndex == 1) {
			m_pendingAction = 1;
		}
		else if (selectionIndex == 2) {
			m_pendingAction = 2;
		}
		break;
	}

	if (m_pendingAction) {
		m_pauseState = 3;
		OpenPauseDialog();
	}
	else {
		m_pauseState = 0;

		for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
			m_playerControls[i].m_input.m_enabled = TRUE;
			m_forceFeedback[i].Resume();
		}

		m_inputRouter.m_enabled = TRUE;
		m_soundManager->Resume();

		if (m_music) {
			m_music->Resume();
		}
	}
}

// FUNCTION: LEGORACERS 0x004362e0
void RaceSession::RestartRace()
{
	Racer* racer = m_raceState.GetPlayerRacer();
	if (racer) {
		m_context->m_cameraViewIndex = racer->m_cameraViewIndex;
	}

	m_raceReset.FinishRace();
	m_decalManager.StopAll();

	m_elapsedMs = 0;
	m_state = 1;

	LegoU32 playerIndex = 0;
	if (m_context->m_playerCount > 0) {
		do {
			RaceCameraController* cameraController = &m_cameraControllers[playerIndex];

			m_playerControls[playerIndex].Reset();
			m_forceFeedback[playerIndex].StopEngineEffect();
			m_raceState.m_playerRacers[playerIndex]->SetCameraView(m_context->m_cameraViewIndex, m_splitScreen);
			cameraController->Update(1.0f);
			cameraController->SetMode(0);
			cameraController->SnapPosition(&m_cameraStartPosition);
			cameraController->SetOrientation(&m_cameraStartDirection, &m_cameraStartUp);

			LegoFloat fov;
			if (m_splitScreen) {
				GolCamera* currentCamera = m_cameras[playerIndex];
				LegoU32 cameraFlags = currentCamera->m_flags | GolCamera::c_flagProjectionDirty;
				currentCamera->m_fov = m_context->m_cameraFov - g_splitScreenFovDelta;
				currentCamera->m_flags = cameraFlags;
				fov = m_context->m_cameraFov - g_splitScreenFovDelta;
			}
			else {
				GolCamera* currentCamera = m_cameras[playerIndex];
				LegoU32 cameraFlags = currentCamera->m_flags | GolCamera::c_flagProjectionDirty;
				LegoFloat cameraFov = m_context->m_cameraFov;
				currentCamera->m_fov = cameraFov;
				currentCamera->m_flags = cameraFlags;
				fov = m_context->m_cameraFov;
			}

			cameraController->m_targetFov = fov;
			cameraController->m_shakeMs = 0;
			MenuAnimationList* animationList = &m_animationList;
			cameraController->m_dirty = TRUE;

			animationList->DeactivateAll();

			playerIndex++;
		} while (playerIndex < m_context->m_playerCount);
	}

	m_huds[0].ResetDisplay(-1);

	if (m_splitScreen) {
		m_huds[1].ResetDisplay(-1);
	}

	StartIntroCamera();
	PlayIntroMusic();
}

#include "race/racesession.h"

#include "app/golapp.h"
#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "audio/soundmanager.h"
#include "audio/soundnode.h"
#include "camera/golcamera.h"
#include "camera/goltransform.h"
#include "core/gol.h"
#include "duskwindbananarelic0x24.h"
#include "font/golfonttable.h"
#include "golbinparser.h"
#include "golbmpwriterfile.h"
#include "golboundedentity.h"
#include "golboundingvolume.h"
#include "golerror.h"
#include "golfontbase.h"
#include "golhashtable.h"
#include "golmateriallibrary.h"
#include "golmodelmaterialtable.h"
#include "golstream.h"
#include "input/directinputdevice.h"
#include "input/inputdevice.h"
#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "input/mousedevice.h"
#include "material/awakekite0x20.h"
#include "race/circuitstandings.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/slatepeak0x58.h"
#include "world/golworlddatabase.h"

#include <memory.h>
#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_raceLapCount;
extern LegoU32 g_randomTableIndex;

DECOMP_SIZE_ASSERT(RaceSession, 0x3368)
DECOMP_SIZE_ASSERT(RaceSession::InputEventSink, 0x04)
DECOMP_SIZE_ASSERT(RaceSession::RabTxtParser, 0x1fc)

// GLOBAL: LEGORACERS 0x004b07ec
LegoFloat g_unk0x004b07ec = 1.2f;

// GLOBAL: LEGORACERS 0x004b07f0
extern const LegoFloat g_mirroredRaceStateRouteScale = 0.05f;

// GLOBAL: LEGORACERS 0x004b08bc
extern const LegoFloat g_unk0x004b08bc = 25.0f;

// GLOBAL: LEGORACERS 0x004bee30
const LegoChar* g_sideWinderForceFeedName = "Microsoft SideWinder Force Feed";

// GLOBAL: LEGORACERS 0x004bee64
const LegoFloat g_unk0x004bee64[4] = {0.5f, 0.01f, 0.49f, 0.49f};

// GLOBAL: LEGORACERS 0x004bee74
const LegoU16 g_unk0x004bee74[16] =
	{0x0e, 0x0f, 0x11, 0x14, 0x0e, 0x10, 0x11, 0x00, 0x12, 0x13, 0x15, 0x16, 0x17, 0x18, 0x2c, 0x00};

// FUNCTION: LEGORACERS 0x004316e0
RaceSession::RaceSession()
{
	FUN_00431bd0();
}

// FUNCTION: LEGORACERS 0x00431990
RaceSession::~RaceSession()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00431bd0
void RaceSession::FUN_00431bd0()
{
	m_context = NULL;
	m_golApp = NULL;
	m_soundManager = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_inputManager = NULL;
	m_standings = NULL;
	m_displayName = 0;
	m_trackModelName = 0;
	m_worldName = 0;
	m_sharedModelName = 0;
	m_effectsModelName = 0;
	m_unk0x90 = 0;
	m_unk0x9d = 0;
	m_collisionWorldName = 0;
	m_triggerWorldName = 0;
	m_powerupFileName = 0;
	m_turboDatabaseName = 0;
	m_powerupDatabaseName = 0;
	m_unk0xeb = 0;
	m_unk0xf8 = 0;
	m_eventFileName = 0;
	m_unk0x112 = 0;
	m_timerFileName = 0;
	m_particleAnimationName = 0;
	m_soundFileName = 0;
	m_voiceFileName = 0;
	m_soundBankName = 0;
	m_musicFileName = 0;
	m_fontFileName = 0;
	m_imageFileName = 0;
	m_startPositionsFileName = 0;
	m_skyName = 0;
	m_unk0x1ae = 0;
	m_hazardFileName = 0;
	m_checkpointFileName = 0;
	m_extraTriggerWorldName = 0;
	m_cameraName = 0;
	m_targetFileName = 0;
	m_trackCamera = NULL;
	m_unk0x1f8.m_x = 0.0f;
	m_unk0x1f8.m_y = 0.0f;
	m_unk0x1f8.m_z = 0.0f;
	m_unk0x204.m_x = 1.0f;
	m_unk0x204.m_y = 0.0f;
	m_unk0x204.m_z = 0.0f;
	m_unk0x210.m_x = 0.0f;
	m_unk0x210.m_y = 0.0f;
	m_unk0x210.m_z = -1.0f;
	m_unk0x2abc = 1023.0f;
	m_unk0x2ac0 = -1023.0f;
	m_unk0x2ac4 = 1023.0f;
	m_unk0x2ac8 = -1023.0f;
	m_trackDatabase = NULL;
	m_trackCollidable = NULL;
	m_effectsDatabase = NULL;
	m_sharedDatabase = NULL;
	m_triggerDatabase = NULL;
	m_collisionWorld = NULL;
	m_triggerWorldEntity = NULL;
	m_extraTriggerWorldEntity = NULL;
	m_fontTable = 0;
	m_unk0x2d78 = 0;
	m_unk0x2d7c = 0;
	m_hudImages = 0;
	m_musicGroup = NULL;
	m_music = NULL;
	m_unk0x3324 = g_unk0x004b07ec;
	m_unk0x3a4 = NULL;
	m_unk0x3a8 = 0;
	m_unk0x3330 = 0;
	m_unk0x3358 = 0;

	for (LegoS32 i = 0; i < sizeOfArray(m_cameras); i++) {
		m_listenerNodes[i] = NULL;
		m_cameras[i] = NULL;
		m_raceState.m_playerRacers[i] = NULL;
	}

	m_elapsedMs = 0;
	m_state = 0;
	memset(m_unk0x2d8c, 0, sizeof(m_unk0x2d8c));
	m_unk0x334c = 0;
	m_running = 0;
	m_unk0x3338 = 0;
	m_unk0x3350 = 0;
	m_unk0x3354 = 0;
	m_unk0x30c0 = 0;
	m_unk0x335c = 0;
	m_unk0x3360 = 0;
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
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(c_rabToken0x35));
	strcpy(&m_displayName, parser->ReadStringWithMaxLength(0x3f));
	parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case c_rabToken0x27:
			strcpy(&m_worldName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x42:
			strcpy(&m_skyName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3b:
			strcpy(&m_sharedModelName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x28:
			m_unk0x204.m_x = parser->ReadFloat();
			m_unk0x204.m_y = parser->ReadFloat();
			m_unk0x204.m_z = parser->ReadFloat();
			m_unk0x210.m_x = parser->ReadFloat();
			m_unk0x210.m_y = parser->ReadFloat();
			m_unk0x210.m_z = parser->ReadFloat();
			break;
		case c_rabToken0x29:
			m_unk0x1f8.m_x = parser->ReadFloat();
			m_unk0x1f8.m_y = parser->ReadFloat();
			m_unk0x1f8.m_z = parser->ReadFloat();
			break;
		case c_rabToken0x49:
			strncpy(&m_cameraName, parser->ReadStringWithMaxLength(8), 8);
			break;
		case c_rabToken0x40:
			strcpy(&m_effectsModelName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2b:
			strcpy(&m_unk0x9d, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_collisionWorldName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_triggerWorldName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2c:
			strcpy(&m_eventFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2d:
			strcpy(&m_fontFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2e:
			strcpy(&m_trackModelName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2f:
			strcpy(&m_imageFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x30:
			strcpy(&m_musicFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x31:
		case c_rabToken0x32:
			parser->ReadStringWithMaxLength(0x0c);
			break;
		case c_rabToken0x33:
			strcpy(&m_powerupFileName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_turboDatabaseName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_powerupDatabaseName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x34:
			strcpy(&m_unk0xeb, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x41:
			strcpy(&m_startPositionsFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3c:
			strcpy(&m_soundFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3d:
			strcpy(&m_voiceFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3f:
			strcpy(&m_soundBankName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x37:
			strcpy(&m_unk0x112, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x38:
			strcpy(&m_timerFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x45:
			strcpy(&m_unk0x90, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3a:
			strcpy(&m_particleAnimationName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_sharedParticleAnimationName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x39:
			strcpy(&m_unk0xf8, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x43:
			strcpy(&m_unk0x1ae, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x44:
			strcpy(&m_hazardFileName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x48:
			strcpy(&m_checkpointFileName, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_extraTriggerWorldName, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x46:
			m_unk0x2abc = parser->ReadFloat();
			m_unk0x2ac4 = parser->ReadFloat();
			m_unk0x2ac0 = parser->ReadFloat();
			m_unk0x2ac8 = parser->ReadFloat();
			break;
		case c_rabToken0x4a:
			strcpy(&m_targetFileName, parser->ReadStringWithMaxLength(0x0c));
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

	FUN_004327f0(p_context);

	if (p_mirror) {
		m_unk0x204.m_y = -m_unk0x204.m_y;
		m_unk0x210.m_y = -m_unk0x210.m_y;
		m_unk0x1f8.m_y = -m_unk0x1f8.m_y;
	}

	FUN_00434170();
	FUN_00432bc0();

	GolHashTable* hashTable = g_hashTable;
	LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(gameDataDirectory));
	}

	m_unk0x280c.FUN_0042f480(m_golExport, m_renderer, &m_stringTable, m_unk0x2d7c, p_context->m_useBinaryFiles);
	m_golApp->ClearFlags(GolApp::c_flagBit14);
	FUN_00435ba0(0.0f);

	m_timeRaceManager = p_timeRaceManager;
	if (p_timeRaceManager) {
		p_timeRaceManager->FUN_00422de0();
	}

	m_elapsedMs = 0;
	m_state = 1;
	FUN_004328f0();
	FUN_00435ba0(0.05f);
	FUN_00432dc0();
	FUN_00432e20(p_mirror);
	FUN_00433480(p_mirror);
	FUN_00435ba0(1.0f);
	FUN_004343e0();
	FUN_00434340();
	m_renderer->VTable0x40();
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
	m_unk0x3340 = 0;

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
			m_unk0x30c0 = 1;
			FUN_00436010();
			m_golApp->ClearFlags(GolApp::c_flagBit14);
		}

		while (m_inputEvents.GetSize()) {
			InputEventQueue::Event* event = m_inputEvents.Dequeue();
			if (event->m_isPressed) {
				VTable0x44(event->m_keyCode);
			}
			else {
				VTable0x48(event->m_keyCode);
			}
		}

		if (!m_golApp->IsDisabled()) {
			if (!m_unk0x30c0) {
				m_elapsedMs += m_golApp->GetFrameDeltaMs();
			}

			switch (m_state) {
			case 1:
				FUN_004349a0();
				break;
			case 2:
				FUN_00434b00();
				break;
			case 3:
				FUN_00434c80();
				break;
			case 4:
				FUN_00434eb0();
				break;
			case 5:
				FUN_00435180();
				break;
			}

			VTable0x30();
			FUN_004354d0();
			m_golApp->PresentFrame();

			if (m_frameCount) {
				LegoS32 currentTime = timeGetTime();
				m_unk0x3340 += currentTime - previousTime;
				frameSampleElapsedMs += currentTime - previousTime;
				frameSampleCount++;
				previousTime = currentTime;

				if (frameSampleCount >= 64) {
					frameSampleElapsedMs >>= 6;
					frameSampleCount = 0;
					m_fps = 1.0f / (static_cast<LegoFloat>((LegoS32) frameSampleElapsedMs) * 0.001f);
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

	RaceState::Racer* field = m_raceState.GetPlayerRacer();
	if (field) {
		m_context->m_unk0x398 = field->m_cameraViewIndex;
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
	FUN_00433460();
	FUN_004348a0();
	FUN_00434000();
	FUN_004330e0();
	FUN_00432df0();
	FUN_00432d70();
	m_unk0x280c.FUN_0042f430();
	FUN_00434300();
	FUN_00432b30();
	FUN_004328d0();
	FUN_00431bd0();
}

// FUNCTION: LEGORACERS 0x004327f0
void RaceSession::FUN_004327f0(LegoRacers::Context* p_context)
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
		m_unk0x3354 = one;
	}
	else {
		m_unk0x3354 = 0;
	}

	if (m_unk0x3354) {
		m_renderer->VTable0x34(3, &g_unk0x004bee64[1]);
		m_lapCount = m_context->m_lapCount;
	}
	else {
		m_renderer->VTable0x34(1, g_unk0x004bee64);
		m_lapCount = 3;
	}

	if (!m_context->m_playerCount) {
		m_context->m_playerCount = one;
		m_context->m_playerSetupSlots[0].m_unk0x10 = 0;
		m_unk0x3350 = one;
	}
	else {
		m_unk0x3350 = 0;
	}

	if (m_context->m_flags & LegoRacers::Context::c_flagReturnToGarage) {
		m_unk0x335c = one;
	}
}

// FUNCTION: LEGORACERS 0x004328d0
void RaceSession::FUN_004328d0()
{
	m_context = NULL;
	m_golApp = NULL;
	m_soundManager = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_inputManager = NULL;
}

// FUNCTION: LEGORACERS 0x004328f0
void RaceSession::FUN_004328f0()
{
	LegoChar firstVoice[16];
	LegoChar secondVoice[16];

	firstVoice[0] = '\0';
	secondVoice[0] = '\0';

	m_musicGroup = m_soundManager->CreateMusicGroup();
	m_musicGroup->Load(&m_musicFileName);

	m_soundSource.FUN_00443ac0(m_soundManager);
	m_soundSource.FUN_00443b40(&m_soundBankName);

	LegoU32 index = FUN_00432a50(0, firstVoice);
	if (m_timeRaceManager) {
		strcpy(secondVoice, "voice29");
	}
	else if (m_context->m_playerCount > 1) {
		FUN_00432a50(index + 1, secondVoice);
	}
	else {
		strcpy(secondVoice, &m_voiceFileName);
	}

	GolHashTable* hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString("GAMEDATA\\VOICES"));
	}

	m_soundSource.FUN_00443b10(firstVoice, secondVoice);

	const LegoChar* commonDataDirectory = m_context->m_commonDataDirectory;
	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(commonDataDirectory));
	}

	m_soundSource.FUN_00443b00(&m_soundFileName);

	for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
		m_listenerNodes[i] = m_soundManager->CreateSoundNode();
		m_soundManager->AddActiveSoundNode(m_listenerNodes[i]);
		m_cameraControllers[i].m_listenerNode = m_listenerNodes[i];
	}
}

// FUNCTION: LEGORACERS 0x00432a50
LegoU32 RaceSession::FUN_00432a50(LegoU32 p_index, LegoChar* p_buffer)
{
	undefined4 slotState = m_context->m_playerSetupSlots[p_index].m_unk0x10;

	if (slotState && p_index < m_context->m_racerCount) {
		do {
			p_index++;
			slotState = m_context->m_playerSetupSlots[p_index].m_unk0x10;
		} while (slotState);
	}

	if (m_unk0x3350) {
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
void RaceSession::FUN_00432b30()
{
	if (m_soundManager) {
		for (LegoS32 i = 0; i < sizeOfArray(m_listenerNodes); i++) {
			if (m_listenerNodes[i]) {
				m_soundManager->DestroySoundNode(m_listenerNodes[i]);
				m_listenerNodes[i] = NULL;
			}
		}

		m_soundSource.FUN_00443a80();

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
void RaceSession::FUN_00432bc0()
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
	m_unk0x2d80.CopyFromBufSelection(m_unk0x2d8c, 0x100);

	m_fontTable = m_golExport->CreateFontTable();
	m_fontTable->LoadFontDefinitions(m_renderer, &m_fontFileName, m_context->m_useBinaryFiles);
	m_unk0x2d78 = m_fontTable->GetItem(0);
	m_unk0x2d7c = m_fontTable->GetItem(0);
}

// FUNCTION: LEGORACERS 0x00432d70
void RaceSession::FUN_00432d70()
{
	if (m_golExport && m_fontTable) {
		m_golExport->DestroyFontTable(m_fontTable);
		m_fontTable = NULL;
	}

	m_unk0x2d80.Reset();

	GolStringTable* stringTable = &m_stringTable;
	stringTable->ReleaseOwnedBuffers();
}

// FUNCTION: LEGORACERS 0x00432dc0
void RaceSession::FUN_00432dc0()
{
	m_hudImages = m_golExport->VTable0x34();
	m_hudImages->LoadImageDefinitions(m_renderer, &m_imageFileName, m_context->m_useBinaryFiles);
}

// FUNCTION: LEGORACERS 0x00432df0
void RaceSession::FUN_00432df0()
{
	if (m_golExport) {
		if (m_hudImages) {
			m_golExport->VTable0x68(m_hudImages);
			m_hudImages = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00432e20
void RaceSession::FUN_00432e20(LegoBool32 p_mirror)
{
	m_effectsDatabase = m_golExport->VTable0x08();
	m_effectsDatabase->VTable0x14(m_renderer, &m_effectsModelName, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_effectsDatabase->FUN_00416140();
	}
	FUN_00435ba0(0.1f);

	GolHashTable* hashTable = g_hashTable;
	LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(gameDataDirectory));
	}

	m_trackDatabase = m_golExport->VTable0x08();
	m_trackDatabase->VTable0x14(m_renderer, &m_trackModelName, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_trackDatabase->FUN_00416140();
	}
	FUN_00435ba0(0.24f);

	m_trackCollidable = m_trackDatabase->GetUnk0xa4();
	if (m_cameraName) {
		m_trackCamera = m_trackDatabase->FindUnk0xe4(&m_cameraName);
	}
	FUN_00435ba0(0.26f);

	m_triggerDatabase = m_golExport->VTable0x08();
	m_triggerDatabase->VTable0x14(m_renderer, &m_unk0x9d, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_triggerDatabase->FUN_00416140();
	}
	FUN_00435d20(p_mirror);
	FUN_00435ba0(0.34f);

	LegoChar name[sizeof(GolName)];
	::strncpy(name, &m_collisionWorldName, sizeof(name));
	m_collisionWorld = m_triggerDatabase->FindUnk0xd8(name);
	FUN_00435ba0(0.36f);

	::strncpy(name, &m_triggerWorldName, sizeof(name));
	m_triggerWorldEntity = m_triggerDatabase->FindUnk0xd8(name);

	if (m_extraTriggerWorldName) {
		::strncpy(name, &m_extraTriggerWorldName, sizeof(name));
		m_extraTriggerWorldEntity = m_triggerDatabase->FindUnk0xd8(name);
	}
	FUN_00435ba0(0.38f);

	m_sharedDatabase = m_golExport->VTable0x08();
	m_sharedDatabase->VTable0x14(m_renderer, &m_sharedModelName, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_sharedDatabase->FUN_00416140();
	}
	FUN_00435ba0(0.4f);

	m_unk0x3a4 = m_golExport->VTable0x08();
	m_unk0x3a4->VTable0x14(m_renderer, &m_unk0x90, m_context->m_useBinaryFiles, 1.0f);
	if (p_mirror) {
		m_unk0x3a4->FUN_00416140();
	}
	FUN_00435ba0(0.42f);
}

// FUNCTION: LEGORACERS 0x004330e0
void RaceSession::FUN_004330e0()
{
	if (m_golExport) {
		if (m_triggerDatabase) {
			m_golExport->VTable0x3c(m_triggerDatabase);
		}
		if (m_unk0x3a4) {
			m_golExport->VTable0x3c(m_unk0x3a4);
		}
		if (m_sharedDatabase) {
			m_golExport->VTable0x3c(m_sharedDatabase);
		}
		if (m_trackDatabase) {
			m_golExport->VTable0x3c(m_trackDatabase);
		}
		if (m_effectsDatabase) {
			m_golExport->VTable0x3c(m_effectsDatabase);
		}
	}

	GolNameTable* field0x27e0 = &m_unk0x27e0;
	field0x27e0->Clear();

	m_effectsDatabase = NULL;
	m_sharedDatabase = NULL;
	m_triggerDatabase = NULL;
	m_trackDatabase = NULL;
	m_collisionWorld = NULL;
	m_triggerWorldEntity = NULL;
	m_extraTriggerWorldEntity = NULL;
	m_trackCamera = NULL;
}

// STUB: LEGORACERS 0x00433190
void RaceSession::FUN_00433190(LegoBool32 p_mirror)
{
	LegoChar fileName[12];
	LegoU32 loaded = FALSE;
	LegoU32 i;
	LegoU32 type;
	RaceRouteRecord* current = m_routeRecords;

	for (i = 0; i < static_cast<LegoU32>(m_context->m_racerCount); i++) {
		if (m_context->m_playerSetupSlots[i].m_unk0x10 == 2 || m_unk0x3350) {
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
void RaceSession::FUN_00433460()
{
	RaceRouteRecord* current = m_routeRecords;
	LegoS32 remaining = sizeOfArray(m_routeRecords);
	do {
		current->Destroy();
		current++;
	} while (--remaining);
}

// STUB: LEGORACERS 0x00433480
void RaceSession::FUN_00433480(LegoBool32 p_mirror)
{
	if (m_checkpointFileName) {
		m_checkpointGraph.Load(&m_checkpointFileName, m_context->m_useBinaryFiles, p_mirror);
		FUN_00435e70();
	}

	RacePowerupManager::Params powerupParams;
	Field0x30c4::Params field0x30c4Params;
	RaceEventTable::Params params;
	HazardManager::Context dispatcherContext;
	RaceState::RacerContext racerContext;
	RaceState::CreateRacersParams racerParams;

	FUN_00435ba0(0.45f);

	MabMaterialAnimation0x14* materialAnimation = m_unk0x3a4->VTable0x4c(0);
	m_sharedParticleAnimation.FUN_00489af0(
		4,
		m_golExport,
		m_renderer,
		materialAnimation,
		&m_sharedParticleAnimationName,
		m_context->m_useBinaryFiles
	);

	FUN_00435ba0(0.48f);

	m_animationList.Allocate(2);
	m_animationList.Activate(500, TRUE, NULL, NULL);

	m_trailManager.FUN_00493850(m_renderer, m_golExport, 6);

	FUN_00435ba0(0.51f);

	m_decalManager.FUN_00492680(m_renderer, m_golExport, m_trackCollidable, 4);
	FUN_00433190(p_mirror);

	FUN_00435ba0(0.54f);

	m_raceState.LoadStartPositions(&m_startPositionsFileName, m_context->m_useBinaryFiles, p_mirror);

	FUN_00435ba0(0.56f);

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
	racerContext.m_unk0x2c = &m_unk0x27e0;
	racerContext.m_shadowsEnabled = TRUE;
	racerContext.m_checkpointGraph = &m_checkpointGraph;
	racerContext.m_cheatFlags = m_context->m_cheatFlags;

	racerParams.m_racerCount = m_context->m_racerCount;
	racerParams.m_routeRecords = m_routeRecords;
	racerParams.m_timeRaceManager = m_timeRaceManager;
	racerParams.m_unk0x3c = m_unk0x3354;
	racerParams.m_lapCount = m_lapCount;

	LegoU32 racerIndex;
	RaceRouteRecord* routeRecord = m_routeRecords;
	for (racerIndex = 0; racerIndex < m_context->m_racerCount; racerIndex++) {
		LegoRacers::Context::PlayerSetupSlot* slot = &m_context->m_playerSetupSlots[racerIndex];
		racerParams.m_slots[racerIndex] = slot;

		if ((slot->m_unk0x10 == 2 || m_unk0x3350) && routeRecord->m_pathPoints) {
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

	FUN_00435ba0(0.6f);

	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_gameDataDirectory));
	}

	for (racerIndex = 0; racerIndex < m_context->m_racerCount; racerIndex++) {
		if (m_context->m_playerSetupSlots[racerIndex].m_unk0x10 == 0) {
			RaceState::Racer* racer = &m_raceState.GetRacers()[racerIndex];
			RaceCameraController* cameraController = &m_cameraControllers[racerIndex];
			m_raceState.m_playerRacers[racerIndex] = racer;

			cameraController->SetRacer(racer);
			racer->InitializeSounds(cameraController, FALSE);
			racer->SetCameraView(m_context->m_unk0x398, m_unk0x3354);
			cameraController->Update(1.0f);
			cameraController->SetMode(0);
			cameraController->SnapPosition(&m_unk0x1f8);
			cameraController->SetOrientation(&m_unk0x204, &m_unk0x210);
		}

		g_raceLapCount = m_lapCount;
	}

	if (m_unk0x3350) {
		RaceState::Racer* racer = m_raceState.GetRacers();
		racer->SwitchToAiControl();
		racer->m_flags |= c_racerFlags0xd04Bit23;
	}

	if (!m_unk0x3354) {
		m_raceState.SetCurrentRacer(m_raceState.m_playerRacers[0]);
	}
	else {
		m_raceState.SetCurrentRacer(NULL);
	}

	m_raceState.InitializeRacerVisuals(m_renderer, m_golExport);

	FUN_00435ba0(0.7f);

	m_skyState.FUN_0041c550(m_renderer, m_golExport, &m_skyName, &m_worldName, m_context->m_useBinaryFiles);

	FUN_00435ba0(0.75f);

	if (m_targetFileName) {
		m_targetPoints.Load(&m_targetFileName, m_context->m_useBinaryFiles, p_mirror);
	}

	params.m_trackDatabase = m_trackDatabase;
	params.m_sharedDatabase = m_sharedDatabase;
	params.m_unk0x08 = m_triggerDatabase;
	params.m_unk0x0c = m_unk0x3a4;
	params.m_soundSource = &m_soundSource;
	params.m_hazardManager = &m_hazardManager;
	params.m_particleAnimation = &m_particleAnimation;
	params.m_sharedParticleAnimation = &m_sharedParticleAnimation;
	params.m_skyState = &m_skyState;
	params.m_targetPoints = &m_targetPoints;
	params.m_name = &m_eventFileName;
	params.m_binary = m_context->m_useBinaryFiles;
	params.m_mirror = p_mirror;
	m_eventTable.Load(&params);

	FUN_00435ba0(0.77f);

	dispatcherContext.m_eventQueue = &m_raceState.m_roster;
	dispatcherContext.m_unk0x04 = m_context;
	dispatcherContext.m_soundSource = &m_soundSource;
	dispatcherContext.m_eventTable = &m_eventTable;
	dispatcherContext.m_trackDatabase = m_trackDatabase;
	dispatcherContext.m_sharedDatabase = m_sharedDatabase;
	dispatcherContext.m_unk0x18 = m_triggerDatabase;
	dispatcherContext.m_particleAnimation = &m_sharedParticleAnimation;
	dispatcherContext.m_trackCollidable = m_trackCollidable;
	dispatcherContext.m_golExport = m_golExport;
	dispatcherContext.m_renderer = m_renderer;
	dispatcherContext.m_colliderTable = &m_unk0x27e0;
	dispatcherContext.m_raceState = &m_raceState;
	dispatcherContext.m_skyState = &m_triggerWorld;
	dispatcherContext.m_powerupManager = &m_powerupManager;
	dispatcherContext.m_unk0x3c = &m_trailManager;
	dispatcherContext.m_mirror = p_mirror;
	m_hazardManager.LoadHazards(&dispatcherContext, &m_hazardFileName, m_context->m_useBinaryFiles);

	FUN_00435ba0(0.8f);

	m_unk0x32c4.FUN_0045e3f0(m_triggerDatabase, &m_raceState);
	m_triggerWorld.Initialize(m_triggerDatabase, &m_collisionWorldName, &m_eventTable, &m_unk0x27e0);
	m_unk0x2080.FUN_00463dc0(
		&m_raceState,
		&m_eventTable,
		&m_powerupManager,
		m_triggerDatabase,
		&m_unk0x32c4,
		&m_unk0xf8,
		m_context->m_useBinaryFiles,
		p_mirror
	);

	FUN_00435ba0(0.84f);

	m_unk0x2128
		.FUN_00464ff0(m_raceState.GetEventQueue(), &m_eventTable, &m_unk0x112, m_context->m_useBinaryFiles, p_mirror);

	FUN_00435ba0(0.86f);

	m_unk0x213c.FUN_00464aa0(m_raceState.GetEventQueue(), &m_eventTable, &m_timerFileName, m_context->m_useBinaryFiles);

	FUN_00435ba0(0.88f);

	DuskwindBananaRelic0x24* material = NULL;
	if (m_unk0x3a4 != NULL && m_unk0x3a4->GetUnk0x14() >= 2) {
		GolMaterialLibrary* materialLibrary = m_unk0x3a4->VTable0x30(1);
		if (materialLibrary != NULL) {
			material = materialLibrary->GetItem(0);
		}
	}

	for (LegoU32 i = 0; i < sizeOfArray(m_trails); i++) {
		m_trails[i].FUN_00425d80(
			m_renderer,
			m_fontTable,
			&m_unk0x2d80,
			m_hudImages,
			&m_raceState,
			m_timeRaceManager,
			&m_stringTable,
			&m_soundSource,
			m_timeRaceManager != NULL,
			m_unk0x335c
		);
		m_trails[i].FUN_00426280(material, m_unk0x2abc, m_unk0x2ac4, m_unk0x2ac0, m_unk0x2ac8, p_mirror);
	}

	if (m_unk0x3354) {
		m_trails[0].FUN_004262c0(m_raceState.m_playerRacers[0]);
		m_trails[0].FUN_004262d0(-1);
		m_trails[0].FUN_00425e90(2);

		m_trails[1].FUN_004262c0(m_raceState.m_playerRacers[1]);
		m_trails[1].FUN_004262d0(-1);
		m_trails[1].FUN_00425e90(3);
	}
	else {
		m_trails[0].FUN_004262c0(
			m_context->m_playerCount == 1 ? m_raceState.m_playerRacers[0] : m_raceState.GetRacers()
		);
		m_trails[0].FUN_004262d0(-1);
		m_trails[0].FUN_00425e90(1);
	}

	FUN_00435ba0(0.9f);

	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_commonDataDirectory));
	}

	if (!m_unk0x3350) {
		m_unk0x3058.FUN_004272c0(m_unk0x2d7c, m_renderer, &m_stringTable, m_context->m_inputBindings[0].m_events[2]);
	}

	field0x30c4Params.m_context = m_context;
	field0x30c4Params.m_raceState = &m_raceState;
	field0x30c4Params.m_unk0x08 = &m_powerupManager;
	field0x30c4Params.m_unk0x0c = &m_hazardManager;
	field0x30c4Params.m_unk0x10 = &m_particleAnimation;
	field0x30c4Params.m_unk0x14 = &m_sharedParticleAnimation;
	field0x30c4Params.m_timeRaceManager = m_timeRaceManager;
	field0x30c4Params.m_unk0x1c = &m_unk0x2080;
	field0x30c4Params.m_unk0x20 = &m_unk0x2128;
	field0x30c4Params.m_unk0x24 = &m_unk0x32c4;
	field0x30c4Params.m_unk0x28 = &m_eventTable;
	m_unk0x30c4.FUN_0043a690(&field0x30c4Params);

	m_particleAnimation.FUN_00489af0(
		10,
		m_golExport,
		m_renderer,
		m_effectsDatabase->VTable0x4c(0),
		&m_particleAnimationName,
		m_context->m_useBinaryFiles
	);

	FUN_00435ba0(0.93f);

	powerupParams.m_golExport = m_golExport;
	powerupParams.m_renderer = m_renderer;
	powerupParams.m_raceState = &m_raceState;
	powerupParams.m_collidable = m_trackCollidable;
	powerupParams.m_boundedEntity = m_triggerWorldEntity;
	powerupParams.m_collisionWorld = &m_triggerWorld;
	powerupParams.m_soundSource = &m_soundSource;
	powerupParams.m_cutsceneAnimation = &m_particleAnimation;
	powerupParams.m_trailManager = &m_trailManager;
	powerupParams.m_unk0x24 = &m_unk0x2080;
	powerupParams.m_animationList = &m_animationList;
	powerupParams.m_trackDatabase = m_unk0x3a8;
	powerupParams.m_targetPoints = &m_targetPoints;
	powerupParams.m_cameraFov = m_unk0x3354 ? m_context->m_cameraFov - g_unk0x004b08bc : m_context->m_cameraFov;
	powerupParams.m_cheatFlags = m_context->m_cheatFlags;
	m_powerupManager.Initialize(&powerupParams);

	m_powerupManager.LoadDatabases(&m_powerupDatabaseName, &m_turboDatabaseName, m_context->m_useBinaryFiles);

	FUN_00435ba0(0.97f);

	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_gameDataDirectory));
	}

	if (m_timeRaceManager) {
		LegoU32 nameLength = ::strlen(&m_powerupFileName);
		(&m_powerupFileName)[nameLength - 4] = '2';
		(&m_powerupFileName)[nameLength - 3] = '.';
		(&m_powerupFileName)[nameLength - 2] = 'P';
		(&m_powerupFileName)[nameLength - 1] = 'W';
		(&m_powerupFileName)[nameLength] = 'F';
		(&m_powerupFileName)[nameLength + 1] = 0;
	}

	m_powerupManager.LoadPowerupFile(&m_powerupFileName, m_context->m_useBinaryFiles, p_mirror);
	m_powerupManager.PreparePools(!m_unk0x3354);
	m_powerupManager.CreatePools();
	m_powerupManager.ClearBricksAudible();

	FUN_00434930();
}

// FUNCTION: LEGORACERS 0x00434000
void RaceSession::FUN_00434000()
{
	if (m_context) {
		LegoU32 playerCount = m_context->m_playerCount;
		LegoU32 i = 0;

		if (playerCount > 0) {
			RaceState::Racer** racer = m_raceState.m_playerRacers;
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

	m_unk0x3058.Destroy();
	m_powerupManager.Destroy();

	if (m_golExport) {
		if (m_unk0x3a8) {
			m_golExport->VTable0x3c(m_unk0x3a8);
			m_unk0x3a8 = NULL;
		}
	}

	m_unk0x213c.Destroy();
	m_unk0x2128.Destroy();
	m_unk0x2080.Destroy();
	m_unk0x32c4.Destroy();
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

	RaceCameraController* field0x2ad4 = m_cameraControllers;
	RaceState::Racer** racer = m_raceState.m_playerRacers;
	LegoS32 remaining = sizeOfArray(m_cameraControllers);
	do {
		*racer = NULL;
		field0x2ad4->Reset();
		racer++;
		field0x2ad4++;
	} while (--remaining);
}

// FUNCTION: LEGORACERS 0x00434170
void RaceSession::FUN_00434170()
{
	const SlatePeak0x58* renderTargetInfo = m_renderer->GetRenderTargetInfo();
	LegoU32 width = renderTargetInfo->GetWidth();
	LegoU32 height = renderTargetInfo->GetHeight();
	LegoU32 i = 0;

	if (m_context->m_playerCount > 0) {
		do {
			GolCamera* camera = m_golExport->VTable0x20();
			m_cameras[i] = camera;

			if (m_unk0x3354) {
				camera->FUN_00404710(
					m_context->m_cameraFov - g_unk0x004b08bc,
					m_context->m_cameraNearClip,
					m_context->m_cameraFarClip,
					2.6666667f
				);
			}
			else {
				camera->FUN_00404710(
					m_context->m_cameraFov,
					m_context->m_cameraNearClip,
					m_context->m_cameraFarClip,
					1.3333334f
				);
			}

			GolCamera* currentCamera = m_cameras[i];
			currentCamera->GetTransform()->SetPosition(&m_unk0x1f8);
			currentCamera->m_flags |= GolCamera::c_flagBit0;

			m_cameras[i]->GetTransform()->VTable0x24(&m_unk0x204, &m_unk0x210);
			m_cameras[i]->m_flags |= GolCamera::c_flagBit0;

			Rect viewport;
			if (!m_unk0x3354) {
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

			m_cameras[i]->VTable0x0c(&viewport);

			RaceCameraController* field0x2ad4 = &m_cameraControllers[i];
			field0x2ad4->Initialize(m_cameras[i], m_renderer);
			field0x2ad4->m_dirty = TRUE;

			i++;
		} while (i < m_context->m_playerCount);
	}

	m_renderer->VTable0x20(m_cameras[0]);
}

// FUNCTION: LEGORACERS 0x00434300
void RaceSession::FUN_00434300()
{
	if (m_golExport) {
		for (LegoS32 i = 0; i < sizeOfArray(m_cameras); i++) {
			if (m_cameras[i]) {
				m_golExport->VTable0x54(m_cameras[i]);
			}
			m_cameras[i] = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00434340
void RaceSession::FUN_00434340()
{
	if (m_trackCamera) {
		m_trackCamera->m_trackedEntity->FUN_0040dad0(0);
		m_trackCamera->m_trackedEntity->SetFlags(
			m_trackCamera->m_trackedEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation
		);

		GolAnimatedEntity* entity = m_trackCamera->m_trackedEntity;
		entity->FUN_0040d650();
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

// STUB: LEGORACERS 0x004343e0
void RaceSession::FUN_004343e0()
{
	RaceSession* session = this;
	InputEventQueue* inputEvents = &session->m_inputEvents;
	inputEvents->Allocate(32);

	MouseInputDevice* mouse = session->m_inputManager->GetMouse();
	if (mouse) {
		mouse->SetCallback(inputEvents);
		mouse->SetExclusiveMode();
		mouse->Acquire();
	}

	KeyboardInputDevice* keyboard = session->m_inputManager->GetKeyboard();
	if (keyboard) {
		session->m_unk0x23c.FUN_00427980(keyboard, inputEvents);
		session->m_unk0x23c.FUN_004279c0();
	}

	LegoU32 playerCount;
	if (session->m_unk0x3350) {
		playerCount = 2;
	}
	else {
		playerCount = session->m_context->m_playerCount;
	}

	if (playerCount > 0) {
		Field0x258* field0x258 = session->m_playerControls;
		RaceState::Racer** racer = session->m_raceState.m_playerRacers;
		LegoU32 playerIndex = 0;

		do {
			LegoBool32 bindingAcquired = FALSE;
			Field0x258::Field0x04* inputSink = NULL;

			if (!session->m_unk0x3350) {
				field0x258->FUN_004300d0(*racer, inputEvents);
				inputSink = &field0x258->m_unk0x004;
			}

			InputBindingState::Entry* binding = &session->m_context->m_inputBindings[playerIndex];
			if (binding->m_deviceType == DIDEVTYPE_JOYSTICK && binding->m_deviceId < 16) {
				JoystickInputDevice* joystick = session->m_inputManager->FindJoystickByDeviceId(binding->m_deviceId);
				if (joystick && joystick->GetDeviceSubType() == binding->m_deviceSubType) {
					joystick->SetCallback(inputEvents);
					bindingAcquired = TRUE;
					joystick->Acquire();

					if (!session->m_unk0x3350) {
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
						inputSink->FUN_004308f0(source, event, 0);

						event = binding->m_events[1];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->FUN_004308f0(source, event, 1);

						event = binding->m_events[2];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->FUN_004308f0(source, event, 2);

						event = binding->m_events[3];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->FUN_004308f0(source, event, 3);

						event = binding->m_events[4];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->FUN_004308f0(source, event, 4);

						event = binding->m_events[5];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->FUN_004308f0(source, event, 5);

						event = binding->m_events[6];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->FUN_004308f0(source, event, 6);

						event = binding->m_events[7];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->FUN_004308f0(source, event, 7);

						event = binding->m_events[8];
						if ((event & InputDevice::c_sourceCharacter) == InputDevice::c_sourceKeyboard && keyboard) {
							source = keyboard;
						}
						else {
							source = joystick;
						}
						inputSink->FUN_004308f0(source, event, 8);

						inputSink->FUN_00430930();
					}
				}
			}

			if (!session->m_unk0x3350) {
				if (binding->m_deviceType == DIDEVTYPE_KEYBOARD && keyboard) {
					inputSink->FUN_004308f0(keyboard, binding->m_events[0], 0);
					inputSink->FUN_004308f0(keyboard, binding->m_events[1], 1);
					inputSink->FUN_004308f0(keyboard, binding->m_events[2], 2);
					inputSink->FUN_004308f0(keyboard, binding->m_events[3], 3);
					inputSink->FUN_004308f0(keyboard, binding->m_events[4], 4);
					inputSink->FUN_004308f0(keyboard, binding->m_events[5], 5);
					inputSink->FUN_004308f0(keyboard, binding->m_events[6], 6);
					inputSink->FUN_004308f0(keyboard, binding->m_events[7], 7);
					inputSink->FUN_004308f0(keyboard, binding->m_events[8], 8);
					bindingAcquired = TRUE;
				}

				m_unk0x23c.FUN_004279a0(inputSink);

				if (!bindingAcquired) {
					GOL_FATALERROR_MESSAGE("Could not acquire controller for player");
				}

				session->m_forceFeedback[playerIndex].Initialize(inputSink->m_unk0x02c[4]);
				(*racer)->m_forceFeedback = &session->m_forceFeedback[playerIndex];
				field0x258->FUN_004307f0();
			}

			racer++;
			playerIndex++;
			field0x258++;
			playerCount--;
		} while (playerCount);
	}

	session->m_inputManager->PollDevices(0);
	inputEvents->ClearQueue();
}

// FUNCTION: LEGORACERS 0x004348a0
void RaceSession::FUN_004348a0()
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

	Field0x258* field0x258 = m_playerControls;
	RaceForceFeedback* field0x340 = m_forceFeedback;
	for (LegoS32 i = 0; i < sizeOfArray(m_playerControls); i++) {
		field0x340->Destroy();
		field0x258->FUN_004300a0();
		field0x340++;
		field0x258++;
	}

	m_inputEvents.Reset();
	m_unk0x23c.FUN_004279f0();
	m_unk0x23c.FUN_00427960();
}

// FUNCTION: LEGORACERS 0x00434930
void RaceSession::FUN_00434930()
{
	if (m_music) {
		m_music->Stop();
		m_musicGroup->DestroyMusicInstance(m_music);
		m_music = NULL;
	}

	m_music = m_musicGroup->CreateMusicInstance(0);

	if (m_music) {
		m_music->SetVolume(m_unk0x3324);
		m_music->Play(FALSE);
	}
}

// FUNCTION: LEGORACERS 0x004349a0
void RaceSession::FUN_004349a0()
{
	if (m_trackCamera && m_cameras[0] && m_cameras[0]->m_trackedEntity &&
		m_cameras[0]->m_trackedEntity->FUN_0040e360()) {
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
		currentCamera->m_transform->VTable0x1c(forwardPtr, rightPtr);

		RaceCameraController* field0x2ad4 = m_cameraControllers;
		LegoS32 remaining = sizeOfArray(m_cameraControllers);
		do {
			if (*camera) {
				(*camera)->ClearTrackedEntity();
				positionPtr = &position;
				field0x2ad4->SnapPosition(positionPtr);

				rightPtr = &right;
				forwardPtr = &forward;
				field0x2ad4->SetOrientation(forwardPtr, rightPtr);
			}

			camera++;
			field0x2ad4++;
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
				CobaltTrail0x140* cobaltTrail = m_trails;
				RaceForceFeedback* field0x340 = m_forceFeedback;
				RaceState::Racer** racer = m_raceState.m_playerRacers;
				do {
					(*racer)->ReapplyCameraView();
					if (!m_unk0x335c) {
						cobaltTrail->FUN_00426360();
					}
					(*racer)->StartEngine();
					field0x340->StartEngineEffect();

					CobaltTrail0x140* nextCobaltTrail = cobaltTrail + 1;
					i++;
					racer++;
					cobaltTrail = nextCobaltTrail;
					field0x340++;
				} while (i < m_context->m_playerCount);
			}

			if (m_standings) {
				m_standings->FUN_004402b0();
			}

			FUN_00434b00();
		}
	}
}

// FUNCTION: LEGORACERS 0x00434b00
void RaceSession::FUN_00434b00()
{
	if (m_elapsedMs < 3000 && !m_unk0x335c) {
		return;
	}

	m_elapsedMs = 0;
	m_state = 3;
	m_raceState.StartRace();

	LegoU32 i = 0;
	if (m_context->m_playerCount > 0) {
		Field0x258* field0x258 = m_playerControls;
		do {
			if (field0x258->m_unk0x000) {
				field0x258->FUN_00430710();
			}

			i++;
			field0x258++;
		} while (i < m_context->m_playerCount);
	}

	m_powerupManager.SetBricksAudible();

	if (m_timeRaceManager) {
		m_timeRaceManager->FUN_00422eb0(m_raceState.m_playerRacers[0]);
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
			m_music->SetVolume(m_unk0x3324);
			m_music->Play(TRUE);
		}
	}

	m_unk0x3330 = 0;
	FUN_00434c80();
}

// FUNCTION: LEGORACERS 0x00434c80
void RaceSession::FUN_00434c80()
{
	LegoU32 racerIndex = 0;
	if (m_context->m_racerCount > 0) {
		do {
			RaceState::Racer* racer = &m_raceState.GetRacers()[racerIndex];
			if (racer->m_lapsCompleted >= m_lapCount && !(racer->m_flags & 0x1000)) {
				racer->m_flags |= 0x1000;

				if (m_standings) {
					m_standings->FUN_004402c0(racer->m_materialIndex, m_unk0x3330);
				}

				m_unk0x3330++;
				racer->SetStandingsPosition(m_unk0x3330);

				if (racer->m_controlMode != 2 || (m_unk0x3350 && racerIndex == 0)) {
					LegoU32 playerIndex = 0;
					RaceState::Racer** playerRacer = m_raceState.m_playerRacers;
					while (*playerRacer != racer && playerIndex < m_context->m_playerCount) {
						playerRacer++;
						playerIndex++;
					}

					m_trails[playerIndex].FUN_00426370();
					m_elapsedMs = 0;
					m_state = 4;
					if (m_unk0x335c) {
						m_elapsedMs = 9000;
					}

					if (m_playerControls[playerIndex].m_unk0x000) {
						m_playerControls[playerIndex].FUN_00430760();
					}

					m_powerupManager.CancelWarp(racer);

					if (!(racer->m_flags & RaceState::Racer::c_flagGhost) && !(racer->m_flags & 0x200000) &&
						!m_unk0x335c) {
						m_cameraControllers[playerIndex].SetView(4, m_unk0x3354);
					}

					if (m_timeRaceManager) {
						m_timeRaceManager->UpdateBestRun();
					}

					if (m_music) {
						m_music->Stop();
						m_musicGroup->DestroyMusicInstance(m_music);

						if (racer->m_lapTimes[5] == 1) {
							m_music = m_musicGroup->CreateMusicInstance(3);
						}
						else {
							m_music = m_musicGroup->CreateMusicInstance(2);
						}

						if (m_music) {
							m_music->SetVolume(m_unk0x3324);
							m_music->Play(FALSE);
						}
					}

					if (m_standings) {
						m_standings->m_unk0x00 = m_unk0x2d7c;
						m_standings->m_unk0x08 = &m_raceState;
						m_standings->m_unk0x0c = &m_stringTable;
					}

					FUN_00434eb0();
					return;
				}
			}

			racerIndex++;
		} while (racerIndex < m_context->m_racerCount);
	}
}

// FUNCTION: LEGORACERS 0x00434eb0
void RaceSession::FUN_00434eb0()
{
	if (m_elapsedMs > 9000) {
		if (!m_animationList.HasActive() && !m_standings) {
			m_animationList.Activate(1000, FALSE, NULL, NULL);
		}
	}

	if (m_timeRaceManager && m_elapsedMs > 9500) {
		if (m_unk0x30c0 != 2) {
			m_unk0x30c0 = 2;
			FUN_00436010();
		}
		return;
	}

	if (m_elapsedMs >= 10000) {
		m_elapsedMs = 0;
		m_state = 5;

		LegoU32 i = 0;
		if (m_context->m_racerCount > 0) {
			RaceState::Racer* racer = m_raceState.GetRacers();
			do {
				if (!(racer->m_flags & 0x1000)) {
					if (m_standings) {
						m_standings->FUN_004402c0(racer->m_materialIndex, m_unk0x3330);
					}

					m_unk0x3330++;
					racer->SetStandingsPosition(m_unk0x3330);
				}

				m_context->m_playerSetupSlots[i].m_unk0x5a[0] = (LegoU8) racer->m_lapTimes[5];
				i++;
				racer++;
			} while (i < m_context->m_racerCount);
		}

		FUN_00435180();
		return;
	}

	LegoU32 racerIndex = 0;
	if (m_context->m_racerCount > 0) {
		RaceState::Racer* racer = m_raceState.GetRacers();
		do {
			if (racer->m_lapsCompleted >= m_lapCount && !(racer->m_flags & 0x1000)) {
				racer->m_flags |= 0x1000;

				if (m_standings) {
					m_standings->FUN_004402c0(racer->m_materialIndex, m_unk0x3330);
				}

				m_unk0x3330++;
				racer->SetStandingsPosition(m_unk0x3330);

				if (racer->m_controlMode != 2) {
					LegoU32 playerIndex = 0;
					RaceState::Racer** playerRacer = m_raceState.m_playerRacers;
					while (*playerRacer != racer && playerIndex < m_context->m_playerCount) {
						playerRacer++;
						playerIndex++;
					}

					if (m_playerControls[playerIndex].m_unk0x000) {
						m_playerControls[playerIndex].FUN_00430760();
					}

					m_powerupManager.CancelWarp(racer);

					if (!(racer->m_flags & RaceState::Racer::c_flagGhost) && !(racer->m_flags & 0x200000)) {
						m_cameraControllers[playerIndex].SetView(4, m_unk0x3354);
					}
				}
			}

			if ((racer->m_flags & 0x1000) && racer->m_cameraController &&
				!(racer->m_flags & RaceState::Racer::c_flagGhost) && !(racer->m_flags & 0x200000) &&
				racer->m_cameraViewIndex != 4 && !m_unk0x335c) {
				racer->m_cameraController->SetView(4, m_unk0x3354);
			}

			racerIndex++;
			racer++;
		} while (racerIndex < m_context->m_racerCount);
	}

	if (m_standings && m_elapsedMs > 5000) {
		m_standings->FUN_00440330(m_golApp->GetFrameDeltaMs());
	}
}

// FUNCTION: LEGORACERS 0x00435180
void RaceSession::FUN_00435180()
{
	if (m_elapsedMs > 4000) {
		if (!m_animationList.HasActive()) {
			m_animationList.Activate(1000, FALSE, NULL, NULL);
		}
	}

	if (m_elapsedMs < 5000 && m_standings) {
		m_standings->FUN_00440330(m_golApp->GetFrameDeltaMs());
		return;
	}

	m_elapsedMs = 0;
	m_running = 0;
}

// FUNCTION: LEGORACERS 0x004351f0
void RaceSession::FUN_004351f0()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_trails); i++) {
		m_trails[i].FUN_00426390(m_golApp->GetFrameDeltaMs());
	}
}

// FUNCTION: LEGORACERS 0x00435220
void RaceSession::VTable0x30()
{
	LegoU32 elapsedMs = m_golApp->GetFrameDeltaMs();
	if (m_context->m_cheatFlags & c_contextFlag0x20Bit8) {
		elapsedMs =
			static_cast<LegoU32>(static_cast<LegoFloat>(static_cast<LegoS32>(m_golApp->GetFrameDeltaMs())) * 1.75f);
	}

	if (!m_unk0x30c0 ||
		(m_unk0x3058.FUN_00427420(elapsedMs), m_unk0x3058.GetUnk0x48() == 2) && (FUN_00436160(), m_unk0x30c0 != 3)) {
		if (elapsedMs > m_unk0x334c) {
			m_unk0x334c = c_unk0x334cResetMs;
		}
		else {
			m_unk0x334c -= elapsedMs;
		}

		m_trackDatabase->FUN_00416090(elapsedMs);
		m_unk0x3a4->FUN_00416090(elapsedMs);
		m_sharedDatabase->FUN_00416090(elapsedMs);
		m_powerupManager.Update(elapsedMs);
		m_unk0x32c4.FUN_0045e470(elapsedMs);
		m_unk0x2128.VTable0x08(elapsedMs);
		m_unk0x2080.VTable0x08(elapsedMs);
		m_particleAnimation.FUN_00489fa0(elapsedMs);
		m_sharedParticleAnimation.FUN_00489fa0(elapsedMs);
		m_trailManager.FUN_00493a20(elapsedMs);
		m_eventTable.Update(elapsedMs);
		m_hazardManager.Update(elapsedMs);
		m_unk0x213c.FUN_00464dd0(elapsedMs);
		m_animationList.Update(elapsedMs);
		m_soundManager->Update(elapsedMs);

		LegoU32 i;
		if (!m_unk0x3350) {
			for (i = 0; i < m_context->m_playerCount; i++) {
				LegoFloat unk0xa00 = m_raceState.m_playerRacers[i]->m_physics.m_forwardSpeed;
				m_forceFeedback[i].Update(elapsedMs, unk0xa00);
				m_playerControls[i].FUN_00430530(elapsedMs);
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
				m_timeRaceManager->FUN_00422710(stepMs);
			}
		}

		m_decalManager.FUN_00492870(elapsedMs);
		m_hazardManager.UpdatePerRacer(m_cameras[0], m_cameraControllers[0].m_racer);
		m_skyState.FUN_0041ccb0(elapsedMs);

		if (m_state == 2 || m_state == 3 || m_state == 4) {
			FUN_004351f0();
		}
	}
}

// FUNCTION: LEGORACERS 0x004354d0
void RaceSession::FUN_004354d0()
{
	if (m_powerupManager.GetUnk0x19a0()) {
		m_powerupManager.Draw(FALSE);
		return;
	}

	GolAppEventHandler::OnCloseRequested();
	m_renderer->VTable0x20(m_cameras[0]);
	VTable0x34();

	if (m_unk0x3354) {
		m_raceState.m_playerRacers[0]->m_visuals.UpdateShadow(m_cameras[0]);
		m_raceState.m_playerRacers[1]->m_visuals.UpdateShadow(m_cameras[1]);
	}
	else {
		m_raceState.UpdateShadows(m_cameras[0]);
	}

	LegoU32 viewportIndex = 1;
	if (m_unk0x3354) {
		m_renderer->VTable0xec(viewportIndex);
	}
	else {
		m_renderer->VTable0xec(FALSE);
	}

	if (m_raceState.m_playerRacers[0]->m_flags & RaceState::Racer::c_flagGhost) {
		m_powerupManager.Draw(viewportIndex);
	}
	else {
		GolVec3 cameraPosition;
		GolCamera* camera = m_cameras[0];
		GolVec3* position = &cameraPosition;
		camera->m_transform->GetPosition(position);

		position = &cameraPosition;
		m_skyState.FUN_0041d040(position);

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
		m_renderer->VTable0x20(m_cameras[viewportIndex]);
		m_renderer->VTable0x5c();
		m_renderer->VTable0xec(viewportIndex + 1);

		if (m_raceState.m_playerRacers[viewportIndex]->m_flags & RaceState::Racer::c_flagGhost) {
			m_powerupManager.Draw(FALSE);
		}
		else {
			GolVec3 cameraPosition;
			GolCamera* camera = m_cameras[viewportIndex];
			GolVec3* position = &cameraPosition;
			camera->m_transform->GetPosition(position);

			position = &cameraPosition;
			m_skyState.FUN_0041d040(position);

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

	if (m_unk0x3354) {
		m_renderer->VTable0xec(FALSE);
	}

	m_renderer->VTable0xe8(FALSE);

	switch (m_state) {
	case 1:
		FUN_004357e0();
		break;
	case 2:
		FUN_00435800();
		break;
	case 3:
		FUN_00435830();
		break;
	case 4:
		FUN_00435860();
		break;
	case 5:
		FUN_004358e0();
		break;
	}

	m_renderer->VTable0xe4();
	FUN_00435bf0();
}

// Separate helpers keep MSVC from merging the identical switch arms in FUN_004354d0; ICF folds the bodies.
// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState1(RaceState::Racer* p_racer)
{
	m_skyState.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState2(RaceState::Racer* p_racer)
{
	m_skyState.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState3(RaceState::Racer* p_racer)
{
	m_skyState.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState4(RaceState::Racer* p_racer)
{
	m_skyState.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState5(RaceState::Racer* p_racer)
{
	m_skyState.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357e0
void RaceSession::FUN_004357e0()
{
	FUN_00435ab0();
	m_animationList.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435800
void RaceSession::FUN_00435800()
{
	VTable0x40();
	FUN_00435ab0();
	m_animationList.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435830
void RaceSession::FUN_00435830()
{
	VTable0x40();
	FUN_00435ab0();
	GolAppEventHandler::OnCloseRequested();
	m_animationList.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435860
void RaceSession::FUN_00435860()
{
	VTable0x40();
	if (m_standings && m_running && m_elapsedMs > 5000) {
		for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
			m_trails[i].m_unk0x070 = 0;
		}

		m_standings->FUN_00440350(FALSE);
	}

	FUN_00435ab0();
	m_animationList.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x004358e0
void RaceSession::FUN_004358e0()
{
	if (m_standings && m_running) {
		m_standings->FUN_00440350(TRUE);
	}

	FUN_00435ab0();
	m_animationList.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435920
void RaceSession::FUN_00435920()
{
	if (m_unk0x30c0) {
		m_unk0x3058.FUN_00427440();
	}
}

// FUNCTION: LEGORACERS 0x00435940
void RaceSession::VTable0x34()
{
	if (m_unk0x3358) {
		m_renderer->VTable0x54(2);
	}
	else {
		m_renderer->VTable0x54(6);
	}
}

// FUNCTION: LEGORACERS 0x00435960
void RaceSession::VTable0x38(RaceState::Racer* p_racer)
{
	m_raceState.DrawRacerEntities(m_renderer, p_racer);
	m_powerupManager.Draw(FALSE);
	m_particleAnimation.FUN_00489ff0(m_renderer);
	m_sharedParticleAnimation.FUN_00489ff0(m_renderer);
	m_trailManager.FUN_00493a60(m_renderer);

	m_trackDatabase->VTable0x24(m_renderer);
	m_trackDatabase->VTable0x20(m_renderer);
	m_trackDatabase->VTable0x28(m_renderer);
	m_trackDatabase->VTable0x1c(m_renderer);

	m_decalManager.FUN_004928b0(m_renderer);
}

// FUNCTION: LEGORACERS 0x00435a00
void RaceSession::VTable0x3c()
{
	m_sharedDatabase->FUN_00416040();
	m_raceState.DrawRacersTransparent(m_renderer);
	m_hazardManager.Draw(m_renderer);
	m_powerupManager.DrawTransparent();
	m_particleAnimation.FUN_0048a040(m_renderer);
	m_sharedParticleAnimation.FUN_0048a040(m_renderer);
	m_trailManager.FUN_00493aa0(m_renderer);
	m_decalManager.FUN_004928f0(m_renderer);

	if (m_timeRaceManager) {
		m_timeRaceManager->FUN_00422960(m_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00435a90
void RaceSession::VTable0x40()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_trails); i++) {
		m_trails[i].FUN_004263a0();
	}
}

// FUNCTION: LEGORACERS 0x00435ab0
void RaceSession::FUN_00435ab0()
{
	if (m_unk0x3350 && m_unk0x334c > c_overlayDrawDelayMs) {
		GolString string;
		const SlatePeak0x58* renderTargetInfo = m_renderer->GetRenderTargetInfo();
		string.CopyFromBufSelection(m_stringTable.GetStringBuffer(c_overlayStringId), 0);

		LegoS32 textWidth;
		LegoS32 textHeight;
		m_unk0x2d7c->MeasureString(&string, &textWidth, &textHeight);

		m_renderer->VTable0x64(
			&string,
			m_unk0x2d7c,
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
void RaceSession::FUN_00435ba0(LegoFloat p_unk0x04)
{
	m_renderer->VTable0x54(FALSE);
	m_renderer->VTable0xec(FALSE);
	m_unk0x280c.FUN_0042f790(p_unk0x04);
	m_unk0x280c.FUN_0042f7a0();
	m_renderer->VTable0xf0();
	m_golApp->PresentFrame();
}

// FUNCTION: LEGORACERS 0x00435bf0
void RaceSession::FUN_00435bf0()
{
	m_renderer->VTable0xf0();
}

// FUNCTION: LEGORACERS 0x00435c00
void RaceSession::VTable0x44(LegoU32 p_keyCode)
{
	if (m_unk0x3350 && (p_keyCode & c_keySourceAbortMask)) {
		m_running = 0;
		m_context->m_flags |= LegoRacers::Context::c_flagBit7;
		return;
	}

	switch (p_keyCode) {
	case c_keyboardKey0x01:
	case c_keyboardKey0xc5:
		if (!m_unk0x30c0) {
			m_unk0x30c0 = 1;
			FUN_00436010();
		}
		break;
	case c_keyboardKey0xb7:
		FUN_00435f20();
		break;
	}

	if (m_unk0x3338 == 3) {
		m_running = 0;
	}

	if (m_unk0x3338 == 7) {
		m_running = 0;
		m_context->m_running = FALSE;
	}

	if (m_unk0x30c0) {
		m_unk0x3058.FUN_00427810(p_keyCode);
	}
}

// FUNCTION: LEGORACERS 0x00435cc0
void RaceSession::VTable0x48(LegoU32 p_keyCode)
{
	switch (p_keyCode) {
	case c_keyboardKey0x10:
		m_unk0x3338 &= ~c_unk0x3338Bit0;
		break;
	case c_keyboardKey0x1d:
		m_unk0x3338 &= ~c_unk0x3338Bit1;
		break;
	case c_keyboardKey0x2a:
		m_unk0x3338 &= ~c_unk0x3338Bit2;
		break;
	}

	if (m_unk0x30c0) {
		m_unk0x3058.FUN_004278c0(p_keyCode);
	}
}

// FUNCTION: LEGORACERS 0x00435d20
void RaceSession::FUN_00435d20(LegoBool32 p_mirror)
{
	RaceSession* raceSession = this;

	if (!raceSession->m_unk0x1ae) {
		LegoU32 zero = 0;
		for (LegoU32 i = zero; i < raceSession->m_triggerDatabase->GetUnk0x64(); i++) {
			GolModelMaterialTable* materials = raceSession->m_triggerDatabase->GetUnk0xa8()[i].GetMaterialTable();

			for (LegoU32 j = zero; j < materials->m_count; j++) {
				DuskwindBananaRelic0x24* material = materials->GetMaterial(j);
				material->EnableFlag0x08Bit18();
				material->SetUnk0x14(NULL);
			}
		}
		return;
	}

	Field0x27e0* field0x27e0 = &raceSession->m_unk0x27e0;
	field0x27e0->FUN_00444030(&raceSession->m_unk0x1ae, raceSession->m_context->m_useBinaryFiles, p_mirror);

	for (LegoU32 i = 0; i < raceSession->m_triggerDatabase->GetUnk0x64(); i++) {
		GolModelMaterialTable* materials = raceSession->m_triggerDatabase->GetUnk0xa8()[i].GetMaterialTable();

		for (LegoU32 j = 0; j < materials->m_count; j++) {
			DuskwindBananaRelic0x24* material = materials->GetMaterial(j);
			DuskWindName0x8 materialName = material->GetNameRecord();

			void* materialPosition;
			if (field0x27e0->GetNameEntries() == NULL) {
				materialPosition = NULL;
			}
			else {
				materialPosition = field0x27e0->GetName(materialName.m_unk0x0);
			}
			material->SetUnk0x14(materialPosition);
			material->EnableFlag0x08Bit18();
		}
	}
}

// STUB: LEGORACERS 0x00435e70
void RaceSession::FUN_00435e70()
{
	LegoU32 materialIndex;
	LegoU32 checkpointIndex;

	if (m_extraTriggerWorldEntity) {
		GolModelMaterialTable* materials = m_extraTriggerWorldEntity->GetUnk0x58()->GetUnk0x18();
		materialIndex = 0;
		checkpointIndex = 0;

		if (materials->GetCount() > 0) {
			do {
				DuskwindBananaRelic0x24* material = materials->GetMaterial(materialIndex);
				DuskWindName0x8 materialName = material->GetNameRecord();
				if (materialName.m_unk0x0[0] >= '0' && materialName.m_unk0x0[0] <= '9') {
					material->SetUnk0x14(m_checkpointGraph.GetCheckpoint(checkpointIndex));
					material->EnableFlag0x08Bit18();
					checkpointIndex++;
				}
				else {
					void* materialPosition;
					if (m_unk0x27e0.GetNameEntries() == NULL) {
						materialPosition = NULL;
					}
					else {
						materialPosition = m_unk0x27e0.GetName(materialName.m_unk0x0);
					}

					material->SetUnk0x14(materialPosition);
					material->EnableFlag0x08Bit18();
				}

				materialIndex++;
			} while (materialIndex < materials->GetCount());
		}
	}
}

// FUNCTION: LEGORACERS 0x00435f20
void RaceSession::FUN_00435f20()
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
		bmpWriter.VTable0x08(fileName);
		bmpWriter.WriteSurface(m_renderer->GetRenderTargetInfo());
		bmpWriter.Destroy();

		if (g_hashTable) {
			g_hashTable->SetCurrentEntry(currentEntry);
		}
	}
}

// FUNCTION: LEGORACERS 0x00436010
void RaceSession::FUN_00436010()
{
	LegoU32 playerIndex = 0;
	if (m_context->m_playerCount > 0) {
		Field0x258* field0x258 = m_playerControls;
		RaceForceFeedback* field0x340 = m_forceFeedback;

		do {
			field0x258->m_unk0x004.m_unk0x054 = 0;
			field0x258->m_unk0x004.FUN_00430c20();
			field0x340->Pause();

			playerIndex++;
			field0x258++;
			field0x340++;
		} while (playerIndex < m_context->m_playerCount);
	}

	m_unk0x23c.m_unk0x18 = 0;
	m_unk0x23c.FUN_00427b40();

	for (LegoU32 i = 0; i < sizeOfArray(m_trails); i++) {
		m_trails[i].m_unk0x13c = 0;
	}

	if (m_standings) {
		m_standings->m_isVisible = FALSE;
	}

	switch (m_unk0x30c0) {
	case 1:
		if (m_standings) {
			m_unk0x3058.FUN_00427310(3, &g_unk0x004bee74[4], g_unk0x004bee74[3], 0xffff, 0);
		}
		else {
			m_unk0x3058.FUN_00427310(3, &g_unk0x004bee74[0], g_unk0x004bee74[3], 0xffff, 0);
		}
		break;
	case 2:
		if (m_timeRaceManager->HasBeatenRecord()) {
			m_unk0x3058.FUN_00427310(2, &g_unk0x004bee74[8], g_unk0x004bee74[12], g_unk0x004bee74[13], 0);
		}
		else {
			m_unk0x3058.FUN_00427310(2, &g_unk0x004bee74[8], g_unk0x004bee74[10], g_unk0x004bee74[11], 0);
		}
		break;
	case 3:
		m_unk0x3058.FUN_00427310(2, &g_unk0x004bee74[8], g_unk0x004bee74[14], 0xffff, 1);
		break;
	}

	MusicInstance* musicInstance = m_music;
	if (musicInstance) {
		musicInstance->Pause();
	}

	m_soundManager->Pause();
}

// FUNCTION: LEGORACERS 0x00436160
void RaceSession::FUN_00436160()
{
	LegoU32 selectionIndex = m_unk0x3058.GetUnk0x50();
	for (LegoS32 i = 0; i < sizeOfArray(m_trails); i++) {
		m_trails[i].m_unk0x13c = 1;
	}

	if (m_standings) {
		m_standings->m_isVisible = TRUE;
	}

	switch (m_unk0x30c0) {
	case 3:
		if (!selectionIndex) {
			if (m_unk0x3360 == 1) {
				if (!m_standings || (m_context->m_flags & LegoRacers::Context::c_flagFirstRace)) {
					if (m_standings) {
						m_standings->ClearPoints();
					}
					FUN_004362e0();
				}
				else {
					m_running = 0;
					m_context->m_flags |= LegoRacers::Context::c_flagRestartCircuit;
				}
			}
			else if (m_unk0x3360 == 2) {
				m_running = 0;
				m_context->m_flags |= LegoRacers::Context::c_flagAbortRace;
			}
		}

		m_unk0x3360 = 0;
		break;
	case 2:
		if (!selectionIndex) {
			if (m_timeRaceManager) {
				m_timeRaceManager->FUN_00422de0();
			}
			FUN_004362e0();
		}
		else {
			m_running = 0;
		}
		break;
	case 1:
		if (selectionIndex == 1) {
			m_unk0x3360 = 1;
		}
		else if (selectionIndex == 2) {
			m_unk0x3360 = 2;
		}
		break;
	}

	if (m_unk0x3360) {
		m_unk0x30c0 = 3;
		FUN_00436010();
	}
	else {
		m_unk0x30c0 = 0;

		for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
			m_playerControls[i].m_unk0x004.m_unk0x054 = 1;
			m_forceFeedback[i].Resume();
		}

		m_unk0x23c.m_unk0x18 = 1;
		m_soundManager->Resume();

		if (m_music) {
			m_music->Resume();
		}
	}
}

// FUNCTION: LEGORACERS 0x004362e0
void RaceSession::FUN_004362e0()
{
	RaceState::Racer* racer = m_raceState.GetPlayerRacer();
	if (racer) {
		m_context->m_unk0x398 = racer->m_cameraViewIndex;
	}

	m_unk0x30c4.FUN_0043a6e0();
	m_decalManager.FUN_00492840();

	m_elapsedMs = 0;
	m_state = 1;

	LegoU32 playerIndex = 0;
	if (m_context->m_playerCount > 0) {
		do {
			RaceCameraController* field0x2ad4 = &m_cameraControllers[playerIndex];

			m_playerControls[playerIndex].FUN_00430100();
			m_forceFeedback[playerIndex].StopEngineEffect();
			m_raceState.m_playerRacers[playerIndex]->SetCameraView(m_context->m_unk0x398, m_unk0x3354);
			field0x2ad4->Update(1.0f);
			field0x2ad4->SetMode(0);
			field0x2ad4->SnapPosition(&m_unk0x1f8);
			field0x2ad4->SetOrientation(&m_unk0x204, &m_unk0x210);

			LegoFloat fov;
			if (m_unk0x3354) {
				GolCamera* currentCamera = m_cameras[playerIndex];
				LegoU32 cameraFlags = currentCamera->m_flags | GolCamera::c_flagBit1;
				currentCamera->m_fov = m_context->m_cameraFov - g_unk0x004b08bc;
				currentCamera->m_flags = cameraFlags;
				fov = m_context->m_cameraFov - g_unk0x004b08bc;
			}
			else {
				GolCamera* currentCamera = m_cameras[playerIndex];
				LegoU32 cameraFlags = currentCamera->m_flags | GolCamera::c_flagBit1;
				LegoFloat cameraFov = m_context->m_cameraFov;
				currentCamera->m_fov = cameraFov;
				currentCamera->m_flags = cameraFlags;
				fov = m_context->m_cameraFov;
			}

			field0x2ad4->m_targetFov = fov;
			field0x2ad4->m_shakeMs = 0;
			MenuAnimationList* animationList = &m_animationList;
			field0x2ad4->m_dirty = TRUE;

			animationList->FUN_00494fe0();

			playerIndex++;
		} while (playerIndex < m_context->m_playerCount);
	}

	m_trails[0].FUN_004262d0(-1);

	if (m_unk0x3354) {
		m_trails[1].FUN_004262d0(-1);
	}

	FUN_00434340();
	FUN_00434930();
}

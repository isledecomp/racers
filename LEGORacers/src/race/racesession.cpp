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

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004bef70;
extern LegoU32 g_unk0x004c6ee4;

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
extern const LegoChar* g_sideWinderForceFeedName = "Microsoft SideWinder Force Feed";

// GLOBAL: LEGORACERS 0x004bee64
extern const LegoFloat g_unk0x004bee64[4] = {0.5f, 0.01f, 0.49f, 0.49f};

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
	m_unk0x21c = NULL;
	m_standings = NULL;
	m_unk0x1c = 0;
	m_unk0x5c = 0;
	m_unk0x69 = 0;
	m_unk0x76 = 0;
	m_unk0x83 = 0;
	m_unk0x90 = 0;
	m_unk0x9d = 0;
	m_unk0xaa = 0;
	m_unk0xb7 = 0;
	m_unk0xc4 = 0;
	m_unk0xde = 0;
	m_unk0xd1 = 0;
	m_unk0xeb = 0;
	m_unk0xf8 = 0;
	m_unk0x105 = 0;
	m_unk0x112 = 0;
	m_unk0x11f = 0;
	m_unk0x12c = 0;
	m_unk0x146 = 0;
	m_unk0x153 = 0;
	m_unk0x160 = 0;
	m_unk0x16d = 0;
	m_unk0x17a = 0;
	m_unk0x187 = 0;
	m_unk0x194 = 0;
	m_unk0x1a1 = 0;
	m_unk0x1ae = 0;
	m_unk0x1bb = 0;
	m_unk0x1c8 = 0;
	m_unk0x1d5 = 0;
	m_unk0x1ef = 0;
	m_unk0x1e2 = 0;
	m_unk0x3ac = NULL;
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
	m_unk0x390 = NULL;
	m_unk0x394 = NULL;
	m_unk0x39c = NULL;
	m_unk0x398 = NULL;
	m_unk0x3a0 = NULL;
	m_unk0x3b0 = NULL;
	m_unk0x3b4 = NULL;
	m_unk0x3b8 = NULL;
	m_unk0x2d74 = 0;
	m_unk0x2d78 = 0;
	m_unk0x2d7c = 0;
	m_unk0x2f8c = 0;
	m_unk0x3314 = NULL;
	m_unk0x3320 = NULL;
	m_unk0x3324 = g_unk0x004b07ec;
	m_unk0x3a4 = NULL;
	m_unk0x3a8 = 0;
	m_unk0x3330 = 0;
	m_unk0x3358 = 0;

	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x2acc); i++) {
		m_unk0x3318[i] = NULL;
		m_unk0x2acc[i] = NULL;
		m_raceState.m_unk0x318[i] = NULL;
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
	m_unk0x3348 = 0;
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
	if (p_context->m_unk0x18) {
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
	strcpy(&m_unk0x1c, parser->ReadStringWithMaxLength(0x3f));
	parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case c_rabToken0x27:
			strcpy(&m_unk0x69, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x42:
			strcpy(&m_unk0x1a1, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3b:
			strcpy(&m_unk0x76, parser->ReadStringWithMaxLength(0x0c));
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
			strncpy(&m_unk0x1ef, parser->ReadStringWithMaxLength(8), 8);
			break;
		case c_rabToken0x40:
			strcpy(&m_unk0x83, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2b:
			strcpy(&m_unk0x9d, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_unk0xaa, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_unk0xb7, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2c:
			strcpy(&m_unk0x105, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2d:
			strcpy(&m_unk0x17a, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2e:
			strcpy(&m_unk0x5c, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x2f:
			strcpy(&m_unk0x187, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x30:
			strcpy(&m_unk0x16d, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x31:
		case c_rabToken0x32:
			parser->ReadStringWithMaxLength(0x0c);
			break;
		case c_rabToken0x33:
			strcpy(&m_unk0xc4, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_unk0xde, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_unk0xd1, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x34:
			strcpy(&m_unk0xeb, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x41:
			strcpy(&m_unk0x194, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3c:
			strcpy(&m_unk0x146, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3d:
			strcpy(&m_unk0x153, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3f:
			strcpy(&m_unk0x160, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x37:
			strcpy(&m_unk0x112, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x38:
			strcpy(&m_unk0x11f, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x45:
			strcpy(&m_unk0x90, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x3a:
			strcpy(&m_unk0x12c, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_unk0x139, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x39:
			strcpy(&m_unk0xf8, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x43:
			strcpy(&m_unk0x1ae, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x44:
			strcpy(&m_unk0x1bb, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x48:
			strcpy(&m_unk0x1c8, parser->ReadStringWithMaxLength(0x0c));
			strcpy(&m_unk0x1d5, parser->ReadStringWithMaxLength(0x0c));
			break;
		case c_rabToken0x46:
			m_unk0x2abc = parser->ReadFloat();
			m_unk0x2ac4 = parser->ReadFloat();
			m_unk0x2ac0 = parser->ReadFloat();
			m_unk0x2ac8 = parser->ReadFloat();
			break;
		case c_rabToken0x4a:
			strcpy(&m_unk0x1e2, parser->ReadStringWithMaxLength(0x0c));
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

	m_unk0x280c.FUN_0042f480(m_golExport, m_renderer, &m_unk0x30f0, m_unk0x2d7c, p_context->m_unk0x18);
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
void RaceSession::VTable0x00()
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

	RaceState::Racer* field = m_raceState.GetUnk0x318();
	if (field) {
		m_context->m_unk0x398 = field->m_unk0xdb8;
	}

	if (m_context->m_running && m_timeRaceManager) {
		m_context->m_unk0x1e |= LegoRacers::Context::c_flagBestTimesPending;

		if (m_timeRaceManager->HasBeatenRecord()) {
			m_context->m_unk0x1e |= LegoRacers::Context::c_flagRecordBeaten;
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
	m_context->m_unk0x1e &= ~LegoRacers::Context::c_flagRecordBeaten;

	m_golApp = m_context->m_golApp;
	m_soundManager = m_context->m_soundManager;
	m_golExport = m_golApp->GetGolExport();
	m_renderer = m_golApp->GetRenderer();
	m_unk0x21c = m_golApp->GetInputManager();

	LegoU32 one = 1;
	if (m_context->m_playerCount > one) {
		m_unk0x3354 = one;
	}
	else {
		m_unk0x3354 = 0;
	}

	if (m_unk0x3354) {
		m_renderer->VTable0x34(3, &g_unk0x004bee64[1]);
		m_unk0x3348 = m_context->m_unk0x2c;
	}
	else {
		m_renderer->VTable0x34(1, g_unk0x004bee64);
		m_unk0x3348 = 3;
	}

	if (!m_context->m_playerCount) {
		m_context->m_playerCount = one;
		m_context->m_playerSetupSlots[0].m_unk0x10 = 0;
		m_unk0x3350 = one;
	}
	else {
		m_unk0x3350 = 0;
	}

	if (m_context->m_unk0x1e & LegoRacers::Context::c_flagReturnToGarage) {
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
	m_unk0x21c = NULL;
}

// FUNCTION: LEGORACERS 0x004328f0
void RaceSession::FUN_004328f0()
{
	LegoChar firstVoice[16];
	LegoChar secondVoice[16];

	firstVoice[0] = '\0';
	secondVoice[0] = '\0';

	m_unk0x3314 = m_soundManager->CreateMusicGroup();
	m_unk0x3314->Load(&m_unk0x16d);

	m_unk0x3300.FUN_00443ac0(m_soundManager);
	m_unk0x3300.FUN_00443b40(&m_unk0x160);

	LegoU32 index = FUN_00432a50(0, firstVoice);
	if (m_timeRaceManager) {
		strcpy(secondVoice, "voice29");
	}
	else if (m_context->m_playerCount > 1) {
		FUN_00432a50(index + 1, secondVoice);
	}
	else {
		strcpy(secondVoice, &m_unk0x153);
	}

	GolHashTable* hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString("GAMEDATA\\VOICES"));
	}

	m_unk0x3300.FUN_00443b10(firstVoice, secondVoice);

	const LegoChar* commonDataDirectory = m_context->m_commonDataDirectory;
	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(commonDataDirectory));
	}

	m_unk0x3300.FUN_00443b00(&m_unk0x146);

	for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
		m_unk0x3318[i] = m_soundManager->CreateSoundNode();
		m_soundManager->AddActiveSoundNode(m_unk0x3318[i]);
		m_unk0x2ad4[i].m_unk0x14c = m_unk0x3318[i];
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
		for (LegoS32 i = 0; i < sizeOfArray(m_unk0x3318); i++) {
			if (m_unk0x3318[i]) {
				m_soundManager->DestroySoundNode(m_unk0x3318[i]);
				m_unk0x3318[i] = NULL;
			}
		}

		m_unk0x3300.FUN_00443a80();

		if (m_unk0x3320) {
			m_unk0x3320->Stop();
			m_unk0x3314->DestroyMusicInstance(m_unk0x3320);
			m_unk0x3320 = NULL;
		}

		MusicGroup* musicGroup = m_unk0x3314;
		if (musicGroup) {
			m_soundManager->DestroyMusicGroup(musicGroup);
			m_unk0x3314 = NULL;
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

	m_unk0x30f0.UseOwnedBuffers();
	m_unk0x30f0.Load("game.srf");

	m_raceState.m_unk0x000.LoadStrings();
	m_unk0x2d80.CopyFromBufSelection(m_unk0x2d8c, 0x100);

	m_unk0x2d74 = m_golExport->CreateFontTable();
	m_unk0x2d74->LoadFontDefinitions(m_renderer, &m_unk0x17a, m_context->m_unk0x18);
	m_unk0x2d78 = m_unk0x2d74->GetItem(0);
	m_unk0x2d7c = m_unk0x2d74->GetItem(0);
}

// FUNCTION: LEGORACERS 0x00432d70
void RaceSession::FUN_00432d70()
{
	if (m_golExport && m_unk0x2d74) {
		m_golExport->DestroyFontTable(m_unk0x2d74);
		m_unk0x2d74 = NULL;
	}

	m_unk0x2d80.Reset();

	GolStringTable* stringTable = &m_unk0x30f0;
	stringTable->ReleaseOwnedBuffers();
}

// FUNCTION: LEGORACERS 0x00432dc0
void RaceSession::FUN_00432dc0()
{
	m_unk0x2f8c = m_golExport->VTable0x34();
	m_unk0x2f8c->LoadImageDefinitions(m_renderer, &m_unk0x187, m_context->m_unk0x18);
}

// FUNCTION: LEGORACERS 0x00432df0
void RaceSession::FUN_00432df0()
{
	if (m_golExport) {
		if (m_unk0x2f8c) {
			m_golExport->VTable0x68(m_unk0x2f8c);
			m_unk0x2f8c = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00432e20
void RaceSession::FUN_00432e20(LegoBool32 p_mirror)
{
	m_unk0x39c = m_golExport->VTable0x08();
	m_unk0x39c->VTable0x14(m_renderer, &m_unk0x83, m_context->m_unk0x18, 1.0f);
	if (p_mirror) {
		m_unk0x39c->FUN_00416140();
	}
	FUN_00435ba0(0.1f);

	GolHashTable* hashTable = g_hashTable;
	LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(gameDataDirectory));
	}

	m_unk0x390 = m_golExport->VTable0x08();
	m_unk0x390->VTable0x14(m_renderer, &m_unk0x5c, m_context->m_unk0x18, 1.0f);
	if (p_mirror) {
		m_unk0x390->FUN_00416140();
	}
	FUN_00435ba0(0.24f);

	m_unk0x394 = m_unk0x390->GetUnk0xa4();
	if (m_unk0x1ef) {
		m_unk0x3ac = m_unk0x390->FindUnk0xe4(&m_unk0x1ef);
	}
	FUN_00435ba0(0.26f);

	m_unk0x3a0 = m_golExport->VTable0x08();
	m_unk0x3a0->VTable0x14(m_renderer, &m_unk0x9d, m_context->m_unk0x18, 1.0f);
	if (p_mirror) {
		m_unk0x3a0->FUN_00416140();
	}
	FUN_00435d20(p_mirror);
	FUN_00435ba0(0.34f);

	LegoChar name[sizeof(GolName)];
	::strncpy(name, &m_unk0xaa, sizeof(name));
	m_unk0x3b0 = m_unk0x3a0->FindUnk0xd8(name);
	FUN_00435ba0(0.36f);

	::strncpy(name, &m_unk0xb7, sizeof(name));
	m_unk0x3b4 = m_unk0x3a0->FindUnk0xd8(name);

	if (m_unk0x1d5) {
		::strncpy(name, &m_unk0x1d5, sizeof(name));
		m_unk0x3b8 = m_unk0x3a0->FindUnk0xd8(name);
	}
	FUN_00435ba0(0.38f);

	m_unk0x398 = m_golExport->VTable0x08();
	m_unk0x398->VTable0x14(m_renderer, &m_unk0x76, m_context->m_unk0x18, 1.0f);
	if (p_mirror) {
		m_unk0x398->FUN_00416140();
	}
	FUN_00435ba0(0.4f);

	m_unk0x3a4 = m_golExport->VTable0x08();
	m_unk0x3a4->VTable0x14(m_renderer, &m_unk0x90, m_context->m_unk0x18, 1.0f);
	if (p_mirror) {
		m_unk0x3a4->FUN_00416140();
	}
	FUN_00435ba0(0.42f);
}

// FUNCTION: LEGORACERS 0x004330e0
void RaceSession::FUN_004330e0()
{
	if (m_golExport) {
		if (m_unk0x3a0) {
			m_golExport->VTable0x3c(m_unk0x3a0);
		}
		if (m_unk0x3a4) {
			m_golExport->VTable0x3c(m_unk0x3a4);
		}
		if (m_unk0x398) {
			m_golExport->VTable0x3c(m_unk0x398);
		}
		if (m_unk0x390) {
			m_golExport->VTable0x3c(m_unk0x390);
		}
		if (m_unk0x39c) {
			m_golExport->VTable0x3c(m_unk0x39c);
		}
	}

	GolNameTable* field0x27e0 = &m_unk0x27e0;
	field0x27e0->Clear();

	m_unk0x39c = NULL;
	m_unk0x398 = NULL;
	m_unk0x3a0 = NULL;
	m_unk0x390 = NULL;
	m_unk0x3b0 = NULL;
	m_unk0x3b4 = NULL;
	m_unk0x3b8 = NULL;
	m_unk0x3ac = NULL;
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
			fileName[9] = m_context->m_unk0x18 ? 'b' : 'f';
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
				g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;

				LegoU32 total = frontCount + middleCount + sideCount;
				LegoU32 index = g_unk0x004befec[g_unk0x004c6ee4] % total;
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

				current->FUN_004a4e30(fileName, m_context->m_unk0x18, p_mirror);
			}
		}

		current++;
	}

	for (i = 0; i < sizeOfArray(m_routeRecords); i++) {
		if (m_routeRecords[i].m_unk0x004) {
			loaded = TRUE;
		}
	}

	if (!loaded) {
		::strcpy(fileName, "r1_f_0");
		::strcat(fileName, m_context->m_unk0x18 ? ".rrb" : ".rrf");

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
			m_routeRecords[0].FUN_004a4e30(fileName, m_context->m_unk0x18, p_mirror);
		}
	}
}

// FUNCTION: LEGORACERS 0x00433460
void RaceSession::FUN_00433460()
{
	RaceRouteRecord* current = m_routeRecords;
	LegoS32 remaining = sizeOfArray(m_routeRecords);
	do {
		current->FUN_004a50a0();
		current++;
	} while (--remaining);
}

// STUB: LEGORACERS 0x00433480
void RaceSession::FUN_00433480(LegoBool32 p_mirror)
{
	if (m_unk0x1c8) {
		m_unk0x27f4.FUN_0041e770(&m_unk0x1c8, m_context->m_unk0x18, p_mirror);
		FUN_00435e70();
	}

	RacePowerupManager::Params powerupParams;
	Field0x30c4::Params field0x30c4Params;
	Field0x2098::Params params;
	RaceEventDispatcher0x08::Context dispatcherContext;
	RaceState::Field0x3b190Params0x08 racerContext;
	RaceState::Field0x3b190Params0x04 racerParams;

	FUN_00435ba0(0.45f);

	MabMaterialAnimation0x14* materialAnimation = m_unk0x3a4->VTable0x4c(0);
	m_unk0x248c.FUN_00489af0(4, m_golExport, m_renderer, materialAnimation, &m_unk0x139, m_context->m_unk0x18);

	FUN_00435ba0(0.48f);

	m_unk0x27fc.Allocate(2);
	m_unk0x27fc.Activate(500, TRUE, NULL, NULL);

	m_trailManager.FUN_00493850(m_renderer, m_golExport, 6);

	FUN_00435ba0(0.51f);

	m_unk0x27d4.FUN_00492680(m_renderer, m_golExport, m_unk0x394, 4);
	FUN_00433190(p_mirror);

	FUN_00435ba0(0.54f);

	m_raceState.FUN_0043bc10(&m_unk0x194, m_context->m_unk0x18, p_mirror);

	FUN_00435ba0(0.56f);

	GolHashTable* hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_commonDataDirectory));
	}

	racerContext.m_renderer = m_renderer;
	racerContext.m_golExport = m_golExport;
	racerContext.m_unk0x08 = m_unk0x394;
	racerContext.m_unk0x0c = m_unk0x3b0;
	racerContext.m_unk0x10 = m_unk0x3b8;
	racerContext.m_resourceMgr = &m_unk0x3300;
	racerContext.m_unk0x18 = &m_unk0x6dc;
	racerContext.m_unk0x1c = &m_unk0x2150;
	racerContext.m_unk0x20 = &m_unk0x248c;
	racerContext.m_unk0x24 = &m_unk0x27d4;
	racerContext.m_unk0x28 = &m_unk0x2098;
	racerContext.m_unk0x2c = &m_unk0x27e0;
	racerContext.m_unk0x30 = TRUE;
	racerContext.m_racerField0x010 = &m_unk0x27f4;
	racerContext.m_flags0x3c = m_context->m_unk0x20;

	racerParams.m_racerCount = m_context->m_racerCount;
	racerParams.m_routeRecords = m_routeRecords;
	racerParams.m_timeRaceManager = m_timeRaceManager;
	racerParams.m_unk0x3c = m_unk0x3354;
	racerParams.m_lapCount = m_unk0x3348;

	LegoU32 racerIndex;
	RaceRouteRecord* routeRecord = m_routeRecords;
	for (racerIndex = 0; racerIndex < m_context->m_racerCount; racerIndex++) {
		LegoRacers::Context::PlayerSetupSlot* slot = &m_context->m_playerSetupSlots[racerIndex];
		racerParams.m_unk0x04[racerIndex] = slot;

		if ((slot->m_unk0x10 == 2 || m_unk0x3350) && routeRecord->m_unk0x004) {
			racerParams.m_unk0x20[racerIndex] = routeRecord;
		}
		else {
			racerParams.m_unk0x20[racerIndex] = NULL;
		}

		routeRecord++;
	}

	if (m_context->m_racerCount < sizeOfArray(racerParams.m_unk0x04)) {
		::memset(
			&racerParams.m_unk0x04[m_context->m_racerCount],
			0,
			(sizeOfArray(racerParams.m_unk0x04) - m_context->m_racerCount) * sizeof(racerParams.m_unk0x04[0])
		);
	}

	m_raceState.FUN_0043b190(&racerParams, &racerContext, m_context->m_unk0x18);

	if (p_mirror) {
		m_raceState.SetUnk0x284Unk0x0c(g_mirroredRaceStateRouteScale);
	}

	FUN_00435ba0(0.6f);

	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_gameDataDirectory));
	}

	for (racerIndex = 0; racerIndex < m_context->m_racerCount; racerIndex++) {
		if (m_context->m_playerSetupSlots[racerIndex].m_unk0x10 == 0) {
			RaceState::Racer* racer = &m_raceState.GetRacers()[racerIndex];
			RaceCameraController* cameraController = &m_unk0x2ad4[racerIndex];
			m_raceState.m_unk0x318[racerIndex] = racer;

			cameraController->FUN_00428230(racer);
			racer->FUN_00437540(cameraController, FALSE);
			racer->FUN_0043a300(m_context->m_unk0x398, m_unk0x3354);
			cameraController->FUN_00428540(1.0f);
			cameraController->FUN_004283d0(0);
			cameraController->FUN_00428390(&m_unk0x1f8);
			cameraController->FUN_004282a0(&m_unk0x204, &m_unk0x210);
		}

		g_unk0x004bef70 = m_unk0x3348;
	}

	if (m_unk0x3350) {
		RaceState::Racer* racer = m_raceState.GetRacers();
		racer->FUN_0043a0e0();
		racer->m_unk0xd04 |= c_racerFlags0xd04Bit23;
	}

	if (!m_unk0x3354) {
		m_raceState.SetUnk0x080(m_raceState.m_unk0x318[0]);
	}
	else {
		m_raceState.SetUnk0x080(NULL);
	}

	m_raceState.FUN_0043be60(m_renderer, m_golExport);

	FUN_00435ba0(0.7f);

	m_unk0x2f90.FUN_0041c550(m_renderer, m_golExport, &m_unk0x1a1, &m_unk0x69, m_context->m_unk0x18);

	FUN_00435ba0(0.75f);

	if (m_unk0x1e2) {
		m_unk0x2804.FUN_0045c3d0(&m_unk0x1e2, m_context->m_unk0x18, p_mirror);
	}

	params.m_unk0x00 = m_unk0x390;
	params.m_unk0x04 = m_unk0x398;
	params.m_unk0x08 = m_unk0x3a0;
	params.m_unk0x0c = m_unk0x3a4;
	params.m_unk0x10 = &m_unk0x3300;
	params.m_unk0x14 = &m_unk0x2148;
	params.m_unk0x18 = &m_unk0x2150;
	params.m_unk0x1c = &m_unk0x248c;
	params.m_unk0x20 = &m_unk0x2f90;
	params.m_unk0x24 = &m_unk0x2804;
	params.m_name = &m_unk0x105;
	params.m_binary = m_context->m_unk0x18;
	params.m_mirror = p_mirror;
	m_unk0x2098.FUN_0045efa0(&params);

	FUN_00435ba0(0.77f);

	dispatcherContext.m_unk0x00 = &m_raceState.m_unk0x0f0;
	dispatcherContext.m_unk0x04 = m_context;
	dispatcherContext.m_unk0x08 = &m_unk0x3300;
	dispatcherContext.m_unk0x0c = m_unk0x2098.GetEventTable();
	dispatcherContext.m_unk0x10 = m_unk0x390;
	dispatcherContext.m_unk0x14 = m_unk0x398;
	dispatcherContext.m_unk0x18 = m_unk0x3a0;
	dispatcherContext.m_unk0x1c = &m_unk0x248c;
	dispatcherContext.m_unk0x20 = m_unk0x394;
	dispatcherContext.m_unk0x24 = m_golExport;
	dispatcherContext.m_unk0x28 = m_renderer;
	dispatcherContext.m_unk0x2c = &m_unk0x27e0;
	dispatcherContext.m_unk0x30 = &m_raceState;
	dispatcherContext.m_unk0x34 = &m_unk0x32b4;
	dispatcherContext.m_unk0x38 = &m_unk0x6dc;
	dispatcherContext.m_unk0x3c = &m_trailManager;
	dispatcherContext.m_unk0x40 = p_mirror;
	m_unk0x2148.FUN_0048a4d0(&dispatcherContext, &m_unk0x1bb, m_context->m_unk0x18);

	FUN_00435ba0(0.8f);

	m_unk0x32c4.FUN_0045e3f0(m_unk0x3a0, &m_raceState);
	m_unk0x32b4.FUN_0041f440(m_unk0x3a0, &m_unk0xaa, m_unk0x2098.GetEventTable(), &m_unk0x27e0);
	m_unk0x2080.FUN_00463dc0(
		&m_raceState,
		m_unk0x2098.GetEventTable(),
		&m_unk0x6dc,
		m_unk0x3a0,
		&m_unk0x32c4,
		&m_unk0xf8,
		m_context->m_unk0x18,
		p_mirror
	);

	FUN_00435ba0(0.84f);

	m_unk0x2128.FUN_00464ff0(
		m_raceState.GetEventQueue(),
		m_unk0x2098.GetEventTable(),
		&m_unk0x112,
		m_context->m_unk0x18,
		p_mirror
	);

	FUN_00435ba0(0.86f);

	m_unk0x213c
		.FUN_00464aa0(m_raceState.GetEventQueue(), m_unk0x2098.GetEventTable(), &m_unk0x11f, m_context->m_unk0x18);

	FUN_00435ba0(0.88f);

	DuskwindBananaRelic0x24* material = NULL;
	if (m_unk0x3a4 != NULL && m_unk0x3a4->GetUnk0x14() >= 2) {
		GolMaterialLibrary* materialLibrary = m_unk0x3a4->VTable0x30(1);
		if (materialLibrary != NULL) {
			material = materialLibrary->GetItem(0);
		}
	}

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x283c); i++) {
		m_unk0x283c[i].FUN_00425d80(
			m_renderer,
			m_unk0x2d74,
			&m_unk0x2d80,
			m_unk0x2f8c,
			&m_raceState,
			m_timeRaceManager,
			&m_unk0x30f0,
			&m_unk0x3300,
			m_timeRaceManager != NULL,
			m_unk0x335c
		);
		m_unk0x283c[i].FUN_00426280(material, m_unk0x2abc, m_unk0x2ac4, m_unk0x2ac0, m_unk0x2ac8, p_mirror);
	}

	if (m_unk0x3354) {
		m_unk0x283c[0].FUN_004262c0(m_raceState.m_unk0x318[0]);
		m_unk0x283c[0].FUN_004262d0(0xffffffff);
		m_unk0x283c[0].FUN_00425e90(2);

		m_unk0x283c[1].FUN_004262c0(m_raceState.m_unk0x318[1]);
		m_unk0x283c[1].FUN_004262d0(0xffffffff);
		m_unk0x283c[1].FUN_00425e90(3);
	}
	else {
		m_unk0x283c[0].FUN_004262c0(
			m_context->m_playerCount == 1 ? m_raceState.m_unk0x318[0] : m_raceState.GetRacers()
		);
		m_unk0x283c[0].FUN_004262d0(0xffffffff);
		m_unk0x283c[0].FUN_00425e90(1);
	}

	FUN_00435ba0(0.9f);

	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_commonDataDirectory));
	}

	if (!m_unk0x3350) {
		m_unk0x3058.FUN_004272c0(m_unk0x2d7c, m_renderer, &m_unk0x30f0, m_context->m_inputBindings[0].m_events[2]);
	}

	field0x30c4Params.m_context = m_context;
	field0x30c4Params.m_raceState = &m_raceState;
	field0x30c4Params.m_unk0x08 = &m_unk0x6dc;
	field0x30c4Params.m_unk0x0c = &m_unk0x2148;
	field0x30c4Params.m_unk0x10 = &m_unk0x2150;
	field0x30c4Params.m_unk0x14 = &m_unk0x248c;
	field0x30c4Params.m_timeRaceManager = m_timeRaceManager;
	field0x30c4Params.m_unk0x1c = &m_unk0x2080;
	field0x30c4Params.m_unk0x20 = &m_unk0x2128;
	field0x30c4Params.m_unk0x24 = &m_unk0x32c4;
	field0x30c4Params.m_unk0x28 = &m_unk0x2098;
	m_unk0x30c4.FUN_0043a690(&field0x30c4Params);

	m_unk0x2150.FUN_00489af0(10, m_golExport, m_renderer, m_unk0x39c->VTable0x4c(0), &m_unk0x12c, m_context->m_unk0x18);

	FUN_00435ba0(0.93f);

	powerupParams.m_unk0x00 = m_golExport;
	powerupParams.m_renderer = m_renderer;
	powerupParams.m_raceState = &m_raceState;
	powerupParams.m_unk0x0c = m_unk0x394;
	powerupParams.m_unk0x10 = m_unk0x3b4;
	powerupParams.m_unk0x14 = &m_unk0x32b4;
	powerupParams.m_unk0x18 = &m_unk0x3300;
	powerupParams.m_unk0x1c = &m_unk0x2150;
	powerupParams.m_trailManager = &m_trailManager;
	powerupParams.m_unk0x24 = &m_unk0x2080;
	powerupParams.m_unk0x28 = &m_unk0x27fc;
	powerupParams.m_unk0x2c = m_unk0x3a8;
	powerupParams.m_unk0x30 = &m_unk0x2804;
	powerupParams.m_unk0x34 = m_unk0x3354 ? m_context->m_unk0x0c - g_unk0x004b08bc : m_context->m_unk0x0c;
	powerupParams.m_unk0x38 = m_context->m_unk0x20;
	m_unk0x6dc.FUN_00457c20(&powerupParams);

	m_unk0x6dc.FUN_00457c90(&m_unk0xd1, &m_unk0xde, m_context->m_unk0x18);

	FUN_00435ba0(0.97f);

	hashTable = g_hashTable;
	if (hashTable) {
		hashTable->SetCurrentEntry(hashTable->AddString(m_context->m_gameDataDirectory));
	}

	if (m_timeRaceManager) {
		LegoU32 nameLength = ::strlen(&m_unk0xc4);
		(&m_unk0xc4)[nameLength - 4] = '2';
		(&m_unk0xc4)[nameLength - 3] = '.';
		(&m_unk0xc4)[nameLength - 2] = 'P';
		(&m_unk0xc4)[nameLength - 1] = 'W';
		(&m_unk0xc4)[nameLength] = 'F';
		(&m_unk0xc4)[nameLength + 1] = 0;
	}

	m_unk0x6dc.FUN_00458810(&m_unk0xc4, m_context->m_unk0x18, p_mirror);
	m_unk0x6dc.FUN_00457cf0(!m_unk0x3354);
	m_unk0x6dc.FUN_00458940();
	m_unk0x6dc.FUN_0045b950();

	FUN_00434930();
}

// FUNCTION: LEGORACERS 0x00434000
void RaceSession::FUN_00434000()
{
	if (m_context) {
		LegoU32 playerCount = m_context->m_playerCount;
		LegoU32 i = 0;

		if (playerCount > 0) {
			RaceState::Racer** racer = m_raceState.m_unk0x318;
			do {
				if (*racer) {
					(*racer)->m_unk0x018.FUN_00440130();
					(*racer)->m_unk0x018.FUN_004400e0();
				}

				i++;
				racer++;
			} while (i < m_context->m_playerCount);
		}
	}

	m_unk0x3058.Destroy();
	m_unk0x6dc.FUN_00459e20();

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
	m_unk0x2148.Destroy();
	m_unk0x2098.Destroy();
	m_unk0x2804.Reset();
	m_unk0x2f90.Clear();
	m_raceState.Destroy();
	m_unk0x27f4.Reset();
	m_unk0x27d4.Destroy();
	m_trailManager.Destroy();
	m_unk0x27fc.Reset();
	m_unk0x248c.Clear();
	m_unk0x2150.Clear();

	RaceCameraController* field0x2ad4 = m_unk0x2ad4;
	RaceState::Racer** racer = m_raceState.m_unk0x318;
	LegoS32 remaining = sizeOfArray(m_unk0x2ad4);
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
			m_unk0x2acc[i] = camera;

			if (m_unk0x3354) {
				camera->FUN_00404710(
					m_context->m_unk0x0c - g_unk0x004b08bc,
					m_context->m_unk0x10,
					m_context->m_unk0x14,
					2.6666667f
				);
			}
			else {
				camera->FUN_00404710(m_context->m_unk0x0c, m_context->m_unk0x10, m_context->m_unk0x14, 1.3333334f);
			}

			GolCamera* currentCamera = m_unk0x2acc[i];
			currentCamera->GetTransform()->SetPosition(&m_unk0x1f8);
			currentCamera->m_flags |= GolCamera::c_flagBit0;

			m_unk0x2acc[i]->GetTransform()->VTable0x24(&m_unk0x204, &m_unk0x210);
			m_unk0x2acc[i]->m_flags |= GolCamera::c_flagBit0;

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

			m_unk0x2acc[i]->VTable0x0c(&viewport);

			RaceCameraController* field0x2ad4 = &m_unk0x2ad4[i];
			field0x2ad4->FUN_00428210(m_unk0x2acc[i], m_renderer);
			field0x2ad4->m_unk0x000 = TRUE;

			i++;
		} while (i < m_context->m_playerCount);
	}

	m_renderer->VTable0x20(m_unk0x2acc[0]);
}

// FUNCTION: LEGORACERS 0x00434300
void RaceSession::FUN_00434300()
{
	if (m_golExport) {
		for (LegoS32 i = 0; i < sizeOfArray(m_unk0x2acc); i++) {
			if (m_unk0x2acc[i]) {
				m_golExport->VTable0x54(m_unk0x2acc[i]);
			}
			m_unk0x2acc[i] = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00434340
void RaceSession::FUN_00434340()
{
	if (m_unk0x3ac) {
		m_unk0x3ac->m_trackedEntity->FUN_0040dad0(0);
		m_unk0x3ac->m_trackedEntity->SetFlags(
			m_unk0x3ac->m_trackedEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation
		);

		GolAnimatedEntity* entity = m_unk0x3ac->m_trackedEntity;
		entity->FUN_0040d650();
		entity->SetActiveValue(0.0f);

		LegoU32 i = 0;
		m_unk0x3ac->m_trackedEntity->SetFlags(
			m_unk0x3ac->m_trackedEntity->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart
		);

		LegoU32 playerCount = m_context->m_playerCount;
		if (playerCount > 0) {
			GolCamera** camera = m_unk0x2acc;
			do {
				(*camera)->SetTrackedEntity(m_unk0x3ac->m_trackedEntity, m_unk0x3ac->m_trackedNodeIndex);
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

	MouseInputDevice* mouse = session->m_unk0x21c->GetMouse();
	if (mouse) {
		mouse->SetCallback(inputEvents);
		mouse->SetExclusiveMode();
		mouse->Acquire();
	}

	KeyboardInputDevice* keyboard = session->m_unk0x21c->GetKeyboard();
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
		Field0x258* field0x258 = session->m_unk0x258;
		RaceState::Racer** racer = session->m_raceState.m_unk0x318;
		LegoU32 playerIndex = 0;

		do {
			LegoBool32 bindingAcquired = FALSE;
			Field0x258::Field0x04* inputSink = NULL;

			if (!session->m_unk0x3350) {
				field0x258->FUN_004300d0(*racer, inputEvents);
				inputSink = &field0x258->m_unk0x004;
			}

			InputBindingEntry* binding = &session->m_context->m_inputBindings[playerIndex];
			if (binding->m_deviceType == DIDEVTYPE_JOYSTICK && binding->m_deviceId < 16) {
				JoystickInputDevice* joystick = session->m_unk0x21c->FindJoystickByDeviceId(binding->m_deviceId);
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

				session->m_unk0x340[playerIndex].FUN_00421e00(inputSink->m_unk0x02c[4]);
				(*racer)->m_unk0x014 = &session->m_unk0x340[playerIndex];
				field0x258->FUN_004307f0();
			}

			racer++;
			playerIndex++;
			field0x258++;
			playerCount--;
		} while (playerCount);
	}

	session->m_unk0x21c->PollDevices(0);
	inputEvents->ClearQueue();
}

// FUNCTION: LEGORACERS 0x004348a0
void RaceSession::FUN_004348a0()
{
	InputManager* inputManager = m_unk0x21c;
	if (!inputManager) {
		m_inputEvents.Reset();
		return;
	}

	InputDevice* source = inputManager->GetMouse();
	if (source) {
		source->SetCallback(NULL);
		source->Unacquire();
	}

	Field0x258* field0x258 = m_unk0x258;
	RaceForceFeedback* field0x340 = m_unk0x340;
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x258); i++) {
		field0x340->FUN_00421de0();
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
	if (m_unk0x3320) {
		m_unk0x3320->Stop();
		m_unk0x3314->DestroyMusicInstance(m_unk0x3320);
		m_unk0x3320 = NULL;
	}

	m_unk0x3320 = m_unk0x3314->CreateMusicInstance(0);

	if (m_unk0x3320) {
		m_unk0x3320->SetVolume(m_unk0x3324);
		m_unk0x3320->Play(FALSE);
	}
}

// FUNCTION: LEGORACERS 0x004349a0
void RaceSession::FUN_004349a0()
{
	if (m_unk0x3ac && m_unk0x2acc[0] && m_unk0x2acc[0]->m_trackedEntity &&
		m_unk0x2acc[0]->m_trackedEntity->FUN_0040e360()) {
		GolVec3 position;
		GolVec3 forward;
		GolVec3 right;
		GolCamera** camera = m_unk0x2acc;

		GolCamera* currentCamera = *camera;
		GolVec3* positionPtr = &position;
		currentCamera->m_transform->GetPosition(positionPtr);

		currentCamera = *camera;
		GolVec3* rightPtr = &right;
		GolVec3* forwardPtr = &forward;
		currentCamera->m_transform->VTable0x1c(forwardPtr, rightPtr);

		RaceCameraController* field0x2ad4 = m_unk0x2ad4;
		LegoS32 remaining = sizeOfArray(m_unk0x2ad4);
		do {
			if (*camera) {
				(*camera)->ClearTrackedEntity();
				positionPtr = &position;
				field0x2ad4->FUN_00428390(positionPtr);

				rightPtr = &right;
				forwardPtr = &forward;
				field0x2ad4->FUN_004282a0(forwardPtr, rightPtr);
			}

			camera++;
			field0x2ad4++;
		} while (--remaining);

		m_elapsedMs = 0;
	}

	if (m_elapsedMs >= 2000) {
		GolCamera* camera = m_unk0x2acc[0];
		if (!camera || !camera->m_trackedEntity) {
			m_elapsedMs = 0;
			m_state = 2;

			LegoU32 i = 0;
			if (m_context->m_playerCount > 0) {
				CobaltTrail0x140* cobaltTrail = m_unk0x283c;
				RaceForceFeedback* field0x340 = m_unk0x340;
				RaceState::Racer** racer = m_raceState.m_unk0x318;
				do {
					(*racer)->FUN_0043a360();
					if (!m_unk0x335c) {
						cobaltTrail->FUN_00426360();
					}
					(*racer)->FUN_004393d0();
					field0x340->FUN_00422130();

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
	m_raceState.FUN_0043ccb0();

	LegoU32 i = 0;
	if (m_context->m_playerCount > 0) {
		Field0x258* field0x258 = m_unk0x258;
		do {
			if (field0x258->m_unk0x000) {
				field0x258->FUN_00430710();
			}

			i++;
			field0x258++;
		} while (i < m_context->m_playerCount);
	}

	m_unk0x6dc.FUN_0045b900();

	if (m_timeRaceManager) {
		m_timeRaceManager->FUN_00422eb0(m_raceState.m_unk0x318[0]);
	}

	if (m_unk0x3320) {
		m_unk0x3320->Stop();
		m_unk0x3314->DestroyMusicInstance(m_unk0x3320);

		LegoU32 musicIndex = 1;
		MusicGroup* musicGroup = m_unk0x3314;
		if (musicGroup->GetMusicCount() > 4 && !m_standings) {
			LegoU32 randomValue = 0;
			LegoU32 randomState = g_unk0x004c6ee4;
			g_unk0x004c6ee4 = (randomState + 1) & 0x3ff;
			musicGroup = m_unk0x3314;
			randomValue = g_unk0x004befec[g_unk0x004c6ee4];
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

		m_unk0x3320 = m_unk0x3314->CreateMusicInstance(musicIndex);
		if (m_unk0x3320) {
			m_unk0x3320->SetVolume(m_unk0x3324);
			m_unk0x3320->Play(TRUE);
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
		RaceState::Racer* racer = m_raceState.GetRacers();
		do {
			if (racer->m_lapsCompleted >= m_unk0x3348 && !(racer->m_unk0xd04 & 0x1000)) {
				racer->m_unk0xd04 |= 0x1000;

				if (m_standings) {
					m_standings->FUN_004402c0(racer->m_unk0xe04, m_unk0x3330);
				}

				m_unk0x3330++;
				racer->FUN_0043a210(m_unk0x3330);

				if (racer->m_unk0xd08 != 2 || !m_unk0x3350 || racerIndex == 0) {
					LegoU32 playerIndex = 0;
					RaceState::Racer** playerRacer = m_raceState.m_unk0x318;
					while (*playerRacer != racer && playerIndex < m_context->m_playerCount) {
						playerRacer++;
						playerIndex++;
					}

					m_unk0x283c[playerIndex].FUN_00426370();
					m_elapsedMs = 0;
					m_state = 4;
					if (m_unk0x335c) {
						m_elapsedMs = 9000;
					}

					if (m_unk0x258[playerIndex].m_unk0x000) {
						m_unk0x258[playerIndex].FUN_00430760();
					}

					m_unk0x6dc.FUN_0045b740(racer);

					if (!(racer->m_unk0xd04 & c_racerFlags0xd04Bit4) && !(racer->m_unk0xd04 & 0x200000) &&
						!m_unk0x335c) {
						m_unk0x2ad4[playerIndex].FUN_004283f0(4, m_unk0x3354);
					}

					if (m_timeRaceManager) {
						m_timeRaceManager->UpdateBestRun();
					}

					if (m_unk0x3320) {
						m_unk0x3320->Stop();
						m_unk0x3314->DestroyMusicInstance(m_unk0x3320);

						if (racer->m_lapTimes[5] == 1) {
							m_unk0x3320 = m_unk0x3314->CreateMusicInstance(3);
						}
						else {
							m_unk0x3320 = m_unk0x3314->CreateMusicInstance(2);
						}

						if (m_unk0x3320) {
							m_unk0x3320->SetVolume(m_unk0x3324);
							m_unk0x3320->Play(FALSE);
						}
					}

					if (m_standings) {
						m_standings->m_unk0x00 = m_unk0x2d7c;
						m_standings->m_unk0x08 = &m_raceState;
						m_standings->m_unk0x0c = &m_unk0x30f0;
					}

					FUN_00434eb0();
					return;
				}
			}

			racerIndex++;
			racer++;
		} while (racerIndex < m_context->m_racerCount);
	}
}

// FUNCTION: LEGORACERS 0x00434eb0
void RaceSession::FUN_00434eb0()
{
	if (m_elapsedMs > 9000) {
		if (!m_unk0x27fc.HasActive() && !m_standings) {
			m_unk0x27fc.Activate(1000, FALSE, NULL, NULL);
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
				if (!(racer->m_unk0xd04 & 0x1000)) {
					if (m_standings) {
						m_standings->FUN_004402c0(racer->m_unk0xe04, m_unk0x3330);
					}

					m_unk0x3330++;
					racer->FUN_0043a210(m_unk0x3330);
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
			if (racer->m_lapsCompleted >= m_unk0x3348 && !(racer->m_unk0xd04 & 0x1000)) {
				racer->m_unk0xd04 |= 0x1000;

				if (m_standings) {
					m_standings->FUN_004402c0(racer->m_unk0xe04, m_unk0x3330);
				}

				m_unk0x3330++;
				racer->FUN_0043a210(m_unk0x3330);

				if (racer->m_unk0xd08 != 2) {
					LegoU32 playerIndex = 0;
					RaceState::Racer** playerRacer = m_raceState.m_unk0x318;
					while (*playerRacer != racer && playerIndex < m_context->m_playerCount) {
						playerRacer++;
						playerIndex++;
					}

					if (m_unk0x258[playerIndex].m_unk0x000) {
						m_unk0x258[playerIndex].FUN_00430760();
					}

					m_unk0x6dc.FUN_0045b740(racer);

					if (!(racer->m_unk0xd04 & c_racerFlags0xd04Bit4) && !(racer->m_unk0xd04 & 0x200000)) {
						m_unk0x2ad4[playerIndex].FUN_004283f0(4, m_unk0x3354);
					}
				}
			}

			if ((racer->m_unk0xd04 & 0x1000) && racer->m_unk0xdb4 && !(racer->m_unk0xd04 & c_racerFlags0xd04Bit4) &&
				!(racer->m_unk0xd04 & 0x200000) && racer->m_unk0xdb8 != 4 && !m_unk0x335c) {
				racer->m_unk0xdb4->FUN_004283f0(4, m_unk0x3354);
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
		if (!m_unk0x27fc.HasActive()) {
			m_unk0x27fc.Activate(1000, FALSE, NULL, NULL);
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
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x283c); i++) {
		m_unk0x283c[i].FUN_00426390(m_golApp->GetFrameDeltaMs());
	}
}

// FUNCTION: LEGORACERS 0x00435220
void RaceSession::VTable0x30()
{
	LegoU32 elapsedMs = m_golApp->GetFrameDeltaMs();
	if (m_context->m_unk0x20 & c_contextFlag0x20Bit8) {
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

		m_unk0x390->FUN_00416090(elapsedMs);
		m_unk0x3a4->FUN_00416090(elapsedMs);
		m_unk0x398->FUN_00416090(elapsedMs);
		m_unk0x6dc.FUN_0045a490(elapsedMs);
		m_unk0x32c4.FUN_0045e470(elapsedMs);
		m_unk0x2128.VTable0x08(elapsedMs);
		m_unk0x2080.VTable0x08(elapsedMs);
		m_unk0x2150.FUN_00489fa0(elapsedMs);
		m_unk0x248c.FUN_00489fa0(elapsedMs);
		m_trailManager.FUN_00493a20(elapsedMs);
		m_unk0x2098.FUN_00461cc0(elapsedMs);
		m_unk0x2148.FUN_0048add0(elapsedMs);
		m_unk0x213c.FUN_00464dd0(elapsedMs);
		m_unk0x27fc.Update(elapsedMs);
		m_soundManager->Update(elapsedMs);

		LegoU32 i;
		if (!m_unk0x3350) {
			for (i = 0; i < m_context->m_playerCount; i++) {
				LegoFloat unk0xa00 = m_raceState.m_unk0x318[i]->m_unk0x3e8.m_unk0x618;
				m_unk0x340[i].FUN_00421e30(elapsedMs, unk0xa00);
				m_unk0x258[i].FUN_00430530(elapsedMs);
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

			m_raceState.FUN_0043c030(stepMs);

			for (i = 0; i < m_context->m_playerCount; i++) {
				m_unk0x2ad4[i].FUN_00428540(static_cast<LegoFloat>(stepMs));
			}

			remainingMs = remainingAfterStep;
			if (m_timeRaceManager) {
				m_timeRaceManager->FUN_00422710(stepMs);
			}
		}

		m_unk0x27d4.FUN_00492870(elapsedMs);
		m_unk0x2148.FUN_0048ae00(m_unk0x2acc[0], m_unk0x2ad4[0].m_unk0x0d4);
		m_unk0x2f90.FUN_0041ccb0(elapsedMs);

		if (m_state == 2 || m_state == 3 || m_state == 4) {
			FUN_004351f0();
		}
	}
}

// FUNCTION: LEGORACERS 0x004354d0
void RaceSession::FUN_004354d0()
{
	if (m_unk0x6dc.GetUnk0x19a0()) {
		m_unk0x6dc.FUN_0045a7b0(FALSE);
		return;
	}

	GolAppEventHandler::VTable0x00();
	m_renderer->VTable0x20(m_unk0x2acc[0]);
	VTable0x34();

	if (m_unk0x3354) {
		m_raceState.m_unk0x318[0]->m_unk0x018.FUN_0043fa50(m_unk0x2acc[0]);
		m_raceState.m_unk0x318[1]->m_unk0x018.FUN_0043fa50(m_unk0x2acc[1]);
	}
	else {
		m_raceState.FUN_0043c6a0(m_unk0x2acc[0]);
	}

	LegoU32 viewportIndex = 1;
	if (m_unk0x3354) {
		m_renderer->VTable0xec(viewportIndex);
	}
	else {
		m_renderer->VTable0xec(FALSE);
	}

	if (m_raceState.m_unk0x318[0]->m_unk0xd04 & c_racerFlags0xd04Bit4) {
		m_unk0x6dc.FUN_0045a7b0(viewportIndex);
	}
	else {
		GolVec3 cameraPosition;
		GolCamera* camera = m_unk0x2acc[0];
		GolVec3* position = &cameraPosition;
		camera->m_transform->GetPosition(position);

		position = &cameraPosition;
		m_unk0x2f90.FUN_0041d040(position);

		switch (m_state) {
		case 1:
			DrawRacerViewportForState1(m_raceState.m_unk0x318[0]);
			break;
		case 2:
			DrawRacerViewportForState2(m_raceState.m_unk0x318[0]);
			break;
		case 3:
			DrawRacerViewportForState3(m_raceState.m_unk0x318[0]);
			break;
		case 4:
			DrawRacerViewportForState4(m_raceState.m_unk0x318[0]);
			break;
		case 5:
			DrawRacerViewportForState5(m_raceState.m_unk0x318[0]);
			break;
		}
	}

	while (viewportIndex < m_context->m_playerCount) {
		m_renderer->VTable0x20(m_unk0x2acc[viewportIndex]);
		m_renderer->VTable0x5c();
		m_renderer->VTable0xec(viewportIndex + 1);

		if (m_raceState.m_unk0x318[viewportIndex]->m_unk0xd04 & c_racerFlags0xd04Bit4) {
			m_unk0x6dc.FUN_0045a7b0(FALSE);
		}
		else {
			GolVec3 cameraPosition;
			GolCamera* camera = m_unk0x2acc[viewportIndex];
			GolVec3* position = &cameraPosition;
			camera->m_transform->GetPosition(position);

			position = &cameraPosition;
			m_unk0x2f90.FUN_0041d040(position);

			switch (m_state) {
			case 1:
				DrawRacerViewportForState1(m_raceState.m_unk0x318[viewportIndex]);
				break;
			case 2:
				DrawRacerViewportForState2(m_raceState.m_unk0x318[viewportIndex]);
				break;
			case 3:
				DrawRacerViewportForState3(m_raceState.m_unk0x318[viewportIndex]);
				break;
			case 4:
				DrawRacerViewportForState4(m_raceState.m_unk0x318[viewportIndex]);
				break;
			case 5:
				DrawRacerViewportForState5(m_raceState.m_unk0x318[viewportIndex]);
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
	m_unk0x2f90.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState2(RaceState::Racer* p_racer)
{
	m_unk0x2f90.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState3(RaceState::Racer* p_racer)
{
	m_unk0x2f90.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState4(RaceState::Racer* p_racer)
{
	m_unk0x2f90.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357b0 FOLDED
void RaceSession::DrawRacerViewportForState5(RaceState::Racer* p_racer)
{
	m_unk0x2f90.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357e0
void RaceSession::FUN_004357e0()
{
	FUN_00435ab0();
	m_unk0x27fc.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435800
void RaceSession::FUN_00435800()
{
	VTable0x40();
	FUN_00435ab0();
	m_unk0x27fc.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435830
void RaceSession::FUN_00435830()
{
	VTable0x40();
	FUN_00435ab0();
	GolAppEventHandler::VTable0x00();
	m_unk0x27fc.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435860
void RaceSession::FUN_00435860()
{
	VTable0x40();
	if (m_standings && m_running && m_elapsedMs > 5000) {
		for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
			m_unk0x283c[i].m_unk0x070 = 0;
		}

		m_standings->FUN_00440350(FALSE);
	}

	FUN_00435ab0();
	m_unk0x27fc.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x004358e0
void RaceSession::FUN_004358e0()
{
	if (m_standings && m_running) {
		m_standings->FUN_00440350(TRUE);
	}

	FUN_00435ab0();
	m_unk0x27fc.Draw(m_renderer);
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
	m_raceState.FUN_0043cd30(m_renderer, p_racer);
	m_unk0x6dc.FUN_0045a7b0(FALSE);
	m_unk0x2150.FUN_00489ff0(m_renderer);
	m_unk0x248c.FUN_00489ff0(m_renderer);
	m_trailManager.FUN_00493a60(m_renderer);

	m_unk0x390->VTable0x24(m_renderer);
	m_unk0x390->VTable0x20(m_renderer);
	m_unk0x390->VTable0x28(m_renderer);
	m_unk0x390->VTable0x1c(m_renderer);

	m_unk0x27d4.FUN_004928b0(m_renderer);
}

// FUNCTION: LEGORACERS 0x00435a00
void RaceSession::VTable0x3c()
{
	m_unk0x398->FUN_00416040();
	m_raceState.FUN_0043bff0(m_renderer);
	m_unk0x2148.FUN_0048ae30(m_renderer);
	m_unk0x6dc.FUN_0045a8a0();
	m_unk0x2150.FUN_0048a040(m_renderer);
	m_unk0x248c.FUN_0048a040(m_renderer);
	m_trailManager.FUN_00493aa0(m_renderer);
	m_unk0x27d4.FUN_004928f0(m_renderer);

	if (m_timeRaceManager) {
		m_timeRaceManager->FUN_00422960(m_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00435a90
void RaceSession::VTable0x40()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x283c); i++) {
		m_unk0x283c[i].FUN_004263a0();
	}
}

// FUNCTION: LEGORACERS 0x00435ab0
void RaceSession::FUN_00435ab0()
{
	if (m_unk0x3350 && m_unk0x334c > c_overlayDrawDelayMs) {
		GolString string;
		const SlatePeak0x58* renderTargetInfo = m_renderer->GetRenderTargetInfo();
		string.CopyFromBufSelection(m_unk0x30f0.GetStringBuffer(c_overlayStringId), 0);

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
		m_context->m_unk0x1e |= LegoRacers::Context::c_flagBit7;
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
		for (LegoU32 i = zero; i < raceSession->m_unk0x3a0->GetUnk0x64(); i++) {
			GolModelMaterialTable* materials = raceSession->m_unk0x3a0->GetUnk0xa8()[i].GetMaterialTable();

			for (LegoU32 j = zero; j < materials->m_count; j++) {
				DuskwindBananaRelic0x24* material = materials->GetMaterial(j);
				material->EnableFlag0x08Bit18();
				material->SetUnk0x14(NULL);
			}
		}
		return;
	}

	Field0x27e0* field0x27e0 = &raceSession->m_unk0x27e0;
	field0x27e0->FUN_00444030(&raceSession->m_unk0x1ae, raceSession->m_context->m_unk0x18, p_mirror);

	for (LegoU32 i = 0; i < raceSession->m_unk0x3a0->GetUnk0x64(); i++) {
		GolModelMaterialTable* materials = raceSession->m_unk0x3a0->GetUnk0xa8()[i].GetMaterialTable();

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

	if (m_unk0x3b8) {
		GolModelMaterialTable* materials = m_unk0x3b8->GetUnk0x58()->GetUnk0x18();
		materialIndex = 0;
		checkpointIndex = 0;

		if (materials->GetCount() > 0) {
			do {
				DuskwindBananaRelic0x24* material = materials->GetMaterial(materialIndex);
				DuskWindName0x8 materialName = material->GetNameRecord();
				if (materialName.m_unk0x0[0] >= '0' && materialName.m_unk0x0[0] <= '9') {
					material->SetUnk0x14(m_unk0x27f4.FUN_0041e940(checkpointIndex));
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
		Field0x258* field0x258 = m_unk0x258;
		RaceForceFeedback* field0x340 = m_unk0x340;

		do {
			field0x258->m_unk0x004.m_unk0x054 = 0;
			field0x258->m_unk0x004.FUN_00430c20();
			field0x340->FUN_00422170();

			playerIndex++;
			field0x258++;
			field0x340++;
		} while (playerIndex < m_context->m_playerCount);
	}

	m_unk0x23c.m_unk0x18 = 0;
	m_unk0x23c.FUN_00427b40();

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x283c); i++) {
		m_unk0x283c[i].m_unk0x13c = 0;
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

	MusicInstance* musicInstance = m_unk0x3320;
	if (musicInstance) {
		musicInstance->Pause();
	}

	m_soundManager->Pause();
}

// FUNCTION: LEGORACERS 0x00436160
void RaceSession::FUN_00436160()
{
	LegoU32 selectionIndex = m_unk0x3058.GetUnk0x50();
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x283c); i++) {
		m_unk0x283c[i].m_unk0x13c = 1;
	}

	if (m_standings) {
		m_standings->m_isVisible = TRUE;
	}

	switch (m_unk0x30c0) {
	case 3:
		if (!selectionIndex) {
			if (m_unk0x3360 == 1) {
				if (!m_standings || (m_context->m_unk0x1e & LegoRacers::Context::c_flagFirstRace)) {
					if (m_standings) {
						m_standings->ClearPoints();
					}
					FUN_004362e0();
				}
				else {
					m_running = 0;
					m_context->m_unk0x1e |= LegoRacers::Context::c_flagRestartCircuit;
				}
			}
			else if (m_unk0x3360 == 2) {
				m_running = 0;
				m_context->m_unk0x1e |= LegoRacers::Context::c_flagAbortRace;
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
			m_unk0x258[i].m_unk0x004.m_unk0x054 = 1;
			m_unk0x340[i].FUN_004221a0();
		}

		m_unk0x23c.m_unk0x18 = 1;
		m_soundManager->Resume();

		if (m_unk0x3320) {
			m_unk0x3320->Resume();
		}
	}
}

// FUNCTION: LEGORACERS 0x004362e0
void RaceSession::FUN_004362e0()
{
	RaceState::Racer* racer = m_raceState.GetUnk0x318();
	if (racer) {
		m_context->m_unk0x398 = racer->m_unk0xdb8;
	}

	m_unk0x30c4.FUN_0043a6e0();
	m_unk0x27d4.FUN_00492840();

	m_elapsedMs = 0;
	m_state = 1;

	LegoU32 playerIndex = 0;
	if (m_context->m_playerCount > 0) {
		do {
			RaceCameraController* field0x2ad4 = &m_unk0x2ad4[playerIndex];

			m_unk0x258[playerIndex].FUN_00430100();
			m_unk0x340[playerIndex].FUN_00422150();
			m_raceState.m_unk0x318[playerIndex]->FUN_0043a300(m_context->m_unk0x398, m_unk0x3354);
			field0x2ad4->FUN_00428540(1.0f);
			field0x2ad4->FUN_004283d0(0);
			field0x2ad4->FUN_00428390(&m_unk0x1f8);
			field0x2ad4->FUN_004282a0(&m_unk0x204, &m_unk0x210);

			LegoFloat fov;
			if (m_unk0x3354) {
				GolCamera* currentCamera = m_unk0x2acc[playerIndex];
				LegoU32 cameraFlags = currentCamera->m_flags | GolCamera::c_flagBit1;
				currentCamera->m_fov = m_context->m_unk0x0c - g_unk0x004b08bc;
				currentCamera->m_flags = cameraFlags;
				fov = m_context->m_unk0x0c - g_unk0x004b08bc;
			}
			else {
				GolCamera* currentCamera = m_unk0x2acc[playerIndex];
				LegoU32 cameraFlags = currentCamera->m_flags | GolCamera::c_flagBit1;
				LegoFloat cameraFov = m_context->m_unk0x0c;
				currentCamera->m_fov = cameraFov;
				currentCamera->m_flags = cameraFlags;
				fov = m_context->m_unk0x0c;
			}

			field0x2ad4->m_unk0x134 = fov;
			field0x2ad4->m_unk0x140 = 0;
			MenuAnimationList* animationList = &m_unk0x27fc;
			field0x2ad4->m_unk0x000 = TRUE;

			animationList->FUN_00494fe0();

			playerIndex++;
		} while (playerIndex < m_context->m_playerCount);
	}

	m_unk0x283c[0].FUN_004262d0(0xffffffff);

	if (m_unk0x3354) {
		m_unk0x283c[1].FUN_004262d0(0xffffffff);
	}

	FUN_00434340();
	FUN_00434930();
}

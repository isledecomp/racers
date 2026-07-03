#include "race/hazardmanager.h"

#include "camera/golcamera.h"
#include "decomp.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"
#include "race/hazards/cannonballrainhazard.h"
#include "race/hazards/codepuzzlehazard.h"
#include "race/hazards/cursedrophazard.h"
#include "race/hazards/fallingpillarhazard.h"
#include "race/hazards/ghosthazard.h"
#include "race/hazards/grabberhazard.h"
#include "race/hazards/hammerhazard.h"
#include "race/hazards/hazardcontext.h"
#include "race/hazards/launcherhazard.h"
#include "race/hazards/lavageyserhazard.h"
#include "race/hazards/movingobstaclehazard.h"
#include "race/hazards/multilauncherhazard.h"
#include "race/hazards/oscillatorhazard.h"
#include "race/hazards/rockethazard.h"
#include "race/hazards/rollingrockhazard.h"
#include "race/hazards/smokeventhazard.h"
#include "race/hazards/snowfallhazard.h"
#include "race/hazards/sphinxhazard.h"
#include "race/hazards/sweepcannonhazard.h"
#include "race/hazards/triggeredanimationhazard.h"
#include "race/hazards/warppadhazard.h"
#include "race/racer/racer.h"
#include "render/gold3drenderdevice.h"
#include "types.h"

DECOMP_SIZE_ASSERT(HazardManager, 0x08)
DECOMP_SIZE_ASSERT(HazardContext, 0x60)
DECOMP_SIZE_ASSERT(HazardManager::HzbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(ColliderRecord, 0x0c)

// FUNCTION: LEGORACERS 0x0048a4b0
HazardManager::HazardManager()
{
	m_entries = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0048a4c0
HazardManager::~HazardManager()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0048a4d0
void HazardManager::LoadHazards(void* p_context, const LegoChar* p_name, LegoBool32 p_binary)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".hzb");
	}
	else {
		parser = new HzbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(HzbTxtParser::e_hazards));
	m_count = parser->ReadBracketedCountAndLeftCurly();

	if (m_count == 0) {
		parser->Dispose();
		delete parser;
		return;
	}

	m_entries = new Hazard*[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	HazardContext* context = static_cast<HazardContext*>(p_context);
	for (LegoU32 i = 0; i < m_count; i++) {
		m_entries[i] = NULL;

		switch (parser->GetNextToken()) {
		case HzbTxtParser::e_fallingPillar:
			m_entries[i] = new FallingPillarHazard;
			break;
		case HzbTxtParser::e_sphinx:
			m_entries[i] = new SphinxHazard;
			break;
		case HzbTxtParser::e_hammer:
			m_entries[i] = new HammerHazard;
			break;
		case HzbTxtParser::e_ghost:
			m_entries[i] = new GhostHazard;
			break;
		case HzbTxtParser::e_lavaGeyser:
			m_entries[i] = new LavaGeyserHazard;
			break;
		case HzbTxtParser::e_codePuzzle:
			m_entries[i] = new CodePuzzleHazard;
			break;
		case HzbTxtParser::e_rocket:
			m_entries[i] = new RocketHazard;
			break;
		case HzbTxtParser::e_snowfall:
			m_entries[i] = new SnowfallHazard;
			break;
		case HzbTxtParser::e_smokeVent:
			m_entries[i] = new SmokeVentHazard;
			break;
		case HzbTxtParser::e_movingObstacle:
			m_entries[i] = new MovingObstacleHazard;
			break;
		case HzbTxtParser::e_launcher:
			m_entries[i] = new LauncherHazard;
			break;
		case HzbTxtParser::e_triggeredAnimation:
			m_entries[i] = new TriggeredAnimationHazard;
			break;
		case HzbTxtParser::e_oscillator:
			m_entries[i] = new OscillatorHazard;
			break;
		case HzbTxtParser::e_multiLauncher:
			m_entries[i] = new MultiLauncherHazard;
			break;
		case HzbTxtParser::e_rollingRock:
			m_entries[i] = new RollingRockHazard;
			break;
		case HzbTxtParser::e_curseDrop:
			m_entries[i] = new CurseDropHazard;
			break;
		case HzbTxtParser::e_sweepCannon:
			m_entries[i] = new SweepCannonHazard;
			break;
		case HzbTxtParser::e_cannonballRain:
			m_entries[i] = new CannonballRainHazard;
			break;
		case HzbTxtParser::e_grabber:
			m_entries[i] = new GrabberHazard;
			break;
		case HzbTxtParser::e_warpPad:
			m_entries[i] = new WarpPadHazard;
			break;
		default:
			break;
		}

		if (m_entries[i] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_entries[i]->Load(context, parser);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x0048aa70
void HazardManager::Destroy()
{
	LegoU32 i;

	if (m_entries) {
		for (i = 0; i < m_count; i++) {
			m_entries[i]->Reset();
			delete m_entries[i];
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0048aad0
void HazardManager::NotifyEventStart(LegoS32 p_eventId, void* p_context)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_eventId) {
			item->Activate(NULL);
		}

		m_entries[i]->OnEventStart(p_eventId, p_context);
	}
}

// FUNCTION: LEGORACERS 0x0048ab20
void HazardManager::NotifyEventEnd(LegoS32 p_eventId, void* p_context)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_eventId) {
			item->Deactivate(NULL);
		}

		m_entries[i]->OnEventEnd(p_eventId, p_context);
	}
}

// FUNCTION: LEGORACERS 0x0048ab70
void HazardManager::ForceDeactivate(LegoS32 p_eventId)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_eventId) {
			item->m_state = Hazard::c_stateDeactivatePending;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048abb0
void HazardManager::NotifyEventPair(LegoS32 p_startId, LegoS32 p_endId, void* p_context)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_startId) {
			item->Activate(NULL);
		}

		item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_endId) {
			item->Deactivate(NULL);
		}

		m_entries[i]->OnEventStart(p_startId, p_context);
		m_entries[i]->OnEventEnd(p_endId, p_context);
	}
}

// FUNCTION: LEGORACERS 0x0048ac30
void HazardManager::DispatchEventStart(LegoS32 p_eventId, void* p_context)
{
	HazardContext* context = static_cast<HazardContext*>(p_context);
	undefined position[12];
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->CanRetrigger()) {
			item = m_entries[i];
			if (item->m_triggerId == p_eventId) {
				item->Activate(p_context);
			}
		}

		context->m_positionProvider->GetPosition(position);
		m_entries[i]->OnEventStart(p_eventId, position);
	}
}

// FUNCTION: LEGORACERS 0x0048aca0
void HazardManager::DispatchEventEnd(LegoS32 p_eventId, void* p_context)
{
	HazardContext* context = static_cast<HazardContext*>(p_context);
	undefined position[12];
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->CanRetrigger()) {
			item = m_entries[i];
			if (item->m_triggerId == p_eventId) {
				item->Deactivate(p_context);
			}
		}

		context->m_positionProvider->GetPosition(position);
		m_entries[i]->OnEventEnd(p_eventId, position);
	}
}

// FUNCTION: LEGORACERS 0x0048ad10
void HazardManager::DispatchEventPair(LegoS32 p_startId, LegoS32 p_endId, void* p_context)
{
	HazardContext* context = static_cast<HazardContext*>(p_context);
	undefined position[12];
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1) {
			if (item->CanRetrigger()) {
				item = m_entries[i];
				if (item->m_triggerId == p_startId) {
					item->Activate(p_context);
				}
			}
		}

		item = m_entries[i];
		if (item->m_triggerId != -1 && item->CanRetrigger()) {
			item = m_entries[i];
			if (item->m_triggerId == p_endId) {
				item->Deactivate(p_context);
			}
		}

		context->m_positionProvider->GetPosition(position);
		m_entries[i]->OnEventStart(p_startId, position);
		m_entries[i]->OnEventEnd(p_endId, position);
	}
}

// FUNCTION: LEGORACERS 0x0048add0
void HazardManager::Update(undefined4 p_elapsedMs)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->Update(p_elapsedMs);
	}
}

// FUNCTION: LEGORACERS 0x0048ae00
void HazardManager::UpdatePerRacer(GolCamera* p_camera, Racer* p_racer)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->UpdatePerRacer(p_camera, p_racer);
	}
}

// FUNCTION: LEGORACERS 0x0048ae30
void HazardManager::Draw(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->Draw(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x0048ae60
void HazardManager::ResetAll()
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->ResetState();
	}
}

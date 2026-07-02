#include "race/circuitracerunner.h"

#include "golhashtable.h"
#include "golstream.h"
#include "menu/menuscreenid.h"
#include "race/racesession.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(CircuitRaceRunner, 0x94)

// GLOBAL: LEGORACERS 0x004c4804
LegoChar g_circuitRaceNameBuffer[9];

// FUNCTION: LEGORACERS 0x0041ec10
CircuitRaceRunner::CircuitRaceRunner()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041ec90
CircuitRaceRunner::~CircuitRaceRunner()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0041ece0
void CircuitRaceRunner::Reset()
{
	m_context = NULL;
	m_session = NULL;

	for (LegoS32 i = 0; i < 2; i++) {
		for (LegoS32 j = 0; j < 4; j++) {
			m_unk0x54[i][j][0] = 0;
			m_unk0x54[i][j][1] = 0;
		}
	}
}

// FUNCTION: LEGORACERS 0x0041ed10
LegoS32 CircuitRaceRunner::Initialize(LegoRacers::Context* p_context, RaceSession* p_session)
{
	if (m_context) {
		Shutdown();
	}

	m_context = p_context;
	m_session = p_session;
	sprintf(p_context->m_commonDataDirectory, "GAMEDATA\\COMMON");
	return m_standings.SetContext(m_context);
}

// FUNCTION: LEGORACERS 0x0041ed60
void CircuitRaceRunner::Shutdown()
{
	m_standings.Shutdown();
	Reset();
}

// FUNCTION: LEGORACERS 0x0041ed80
void CircuitRaceRunner::Run()
{
	LegoU32 i;

	for (i = 0;; i++) {
		if (i >= sizeOfArray(m_context->m_raceSlots)) {
			if (!(m_context->m_flags & LegoRacers::Context::c_flagRestartCircuit)) {
				break;
			}
		}

		undefined flags = m_context->m_flags;

		if (flags & LegoRacers::Context::c_flagRestartCircuit) {
			flags &= ~LegoRacers::Context::c_flagRestartCircuit;
			i = 0;
			m_context->m_flags = flags;
			m_context->m_currentRaceIndex = 0;
			m_standings.ClearPoints();
			m_context->m_flags |= LegoRacers::Context::c_flagFirstRace;
		}
		else {
			if (i == 0) {
				LegoRacers::Context*& context = m_context;
				context->m_flags |= LegoRacers::Context::c_flagFirstRace;
			}
			else {
				flags &= ~LegoRacers::Context::c_flagFirstRace;
				m_context->m_flags = flags;
			}
		}

		if (m_context->m_raceSlots[i].m_enabled && m_context->m_running) {
			if (m_context->m_flags & LegoRacers::Context::c_flagAbortRace) {
				return;
			}

			if (m_context->m_playerCount == c_singlePlayerCount) {
				if (m_standings.GetPoints(c_firstPointsIndex) < c_pointsThresholdStep * i) {
					m_context->m_nextMenuId = c_menuChampAward4;
					return;
				}
			}

			strcpy(m_context->m_gameDataDirectory, "GAMEDATA\\");
			memcpy(
				g_circuitRaceNameBuffer,
				m_context->m_raceSlots[i].m_folderName,
				sizeof(m_context->m_raceSlots[i].m_folderName)
			);
			g_circuitRaceNameBuffer[sizeof(m_context->m_raceSlots[i].m_folderName)] = '\0';
			strcat(m_context->m_gameDataDirectory, g_circuitRaceNameBuffer);

			LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
			if (g_hashTable) {
				g_hashTable->SetCurrentEntryFromString(gameDataDirectory);
			}

			m_session->Initialize(m_context, g_circuitRaceNameBuffer, m_context->m_raceSlots[i].m_mirror, NULL);
			m_session->SetStandings(&m_standings);
			m_session->Run();
			m_session->Shutdown();
			m_context->m_golApp->ClearFileSourceDirectoryCaches();
		}

		m_context->m_currentRaceIndex++;
	}

	if (!(m_context->m_flags & LegoRacers::Context::c_flagAbortRace) && m_context->m_running) {
		LegoU32 rankIndex = 0;
		LegoRacers::Context::PlayerSetupSlot* slot = m_context->m_playerSetupSlots;
		undefined4 slotValue = slot->m_slotState;

		if (slotValue) {
			LegoU32 slotCount = m_context->m_racerCount;

			while (slotValue && rankIndex < slotCount) {
				slot++;
				rankIndex++;
				slotValue = slot->m_slotState;
			}
		}

		switch (m_standings.GetRank(rankIndex)) {
		case 0:
			m_context->m_nextMenuId = c_menuChampAward1;
			break;
		case 1:
			m_context->m_nextMenuId = c_menuChampAward2;
			break;
		case 2:
			m_context->m_nextMenuId = c_menuChampAward3;
			break;
		default:
			m_context->m_nextMenuId = c_menuChampAward4;
			break;
		}
	}
}

#include "race/circuitstandings.h"

#include "golfontbase.h"
#include "golstring.h"
#include "golstringtable.h"
#include "race/racestate.h"
#include "render/gold3drenderdevice.h"
#include "surface/slatepeak0x58.h"

#include <memory.h>
#include <stdio.h>

DECOMP_SIZE_ASSERT(CircuitStandings, 0x48)

// GLOBAL: LEGORACERS 0x004b0b58
const LegoU32 g_unk0x004b0b58[6] = {30, 20, 10, 3, 2, 1};

// GLOBAL: LEGORACERS 0x004bef74
const LegoChar g_circuitStandingsPlusSign[] = "+";

// GLOBAL: LEGORACERS 0x004bef78
const LegoChar g_circuitStandingsMinusSign[] = "-";

// FUNCTION: LEGORACERS 0x00440220
CircuitStandings::CircuitStandings()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00440230
CircuitStandings::~CircuitStandings()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00440240
void CircuitStandings::Reset()
{
	LegoS32 i;

	m_unk0x00 = 0;
	m_context = NULL;
	m_unk0x08 = 0;
	m_unk0x0c = 0;

	for (i = 0; i < sizeOfArray(m_points); i++) {
		m_points[i] = 0;
		m_roundPoints[i] = 0;
	}

	m_displayTimerMs = 0;
	m_isVisible = TRUE;
}

// FUNCTION: LEGORACERS 0x00440270
undefined4 CircuitStandings::SetContext(LegoRacers::Context* p_context)
{
	LegoRacers::Context* previous = m_context;

	if (previous) {
		Shutdown();
		previous = p_context;
	}

	m_context = p_context;
	return (undefined4) previous;
}

// FUNCTION: LEGORACERS 0x004402a0
void CircuitStandings::Shutdown()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004402b0
void CircuitStandings::FUN_004402b0()
{
	LegoU32* values = m_roundPoints;
	LegoS32 remaining = sizeOfArray(m_roundPoints);
	do {
		*values++ = 0;
	} while (--remaining);
}

// FUNCTION: LEGORACERS 0x004402c0
void CircuitStandings::FUN_004402c0(LegoU32 p_unk0x04, LegoU32 p_unk0x08)
{
	m_roundPoints[p_unk0x04] = g_unk0x004b0b58[p_unk0x08];
	m_points[p_unk0x04] += g_unk0x004b0b58[p_unk0x08];
}

// FUNCTION: LEGORACERS 0x004402f0
LegoU32 CircuitStandings::GetPoints(LegoU32 p_index)
{
	return m_points[p_index];
}

// FUNCTION: LEGORACERS 0x00440300
LegoS32 CircuitStandings::GetRank(LegoU32 p_index)
{
	LegoS32 result = 0;

	for (LegoU32 i = 0; i < sizeOfArray(m_points); i++) {
		if (i != p_index && m_points[i] > m_points[p_index]) {
			result++;
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00440330
void CircuitStandings::FUN_00440330(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs > m_displayTimerMs) {
		m_displayTimerMs = c_displayResetMs;
	}
	else {
		m_displayTimerMs -= p_elapsedMs;
	}
}

// STUB: LEGORACERS 0x00440350
void CircuitStandings::FUN_00440350(LegoBool32 p_showCircuitPoints)
{
	GolString string;
	LegoChar timeBuffer[12];
	LegoChar buffer[64];
	LegoU32 selected[c_racerCount];
	RaceState::Racer::Field0x00c::StandingsDeltaEntry deltaEntries[c_racerCount];
	GolD3DRenderDevice* renderer = m_context->m_golApp->GetRenderer();
	const SlatePeak0x58* renderTargetInfo = renderer->GetRenderTargetInfo();

	if (!m_isVisible) {
		return;
	}

	RaceState::Racer* racers = m_unk0x08->GetRacers();

	if (p_showCircuitPoints) {
		string.CopyFromBufSelection(m_unk0x0c->GetStringBuffer(c_titleStringId), 0);
		LegoS32 textWidth;
		LegoS32 textHeight;
		m_unk0x00->MeasureString(&string, &textWidth, &textHeight);
		renderer->VTable0x64(
			&string,
			m_unk0x00,
			(renderTargetInfo->GetWidth() >> 1) - (static_cast<LegoU32>(textWidth) >> 1),
			c_titleY,
			1.0f,
			1.0f,
			NULL,
			0
		);

		LegoS32 rank = 0;
		::memset(selected, 0, sizeof(selected));
		for (LegoU32 y = c_rowStartY; y < c_rowEndY; y += c_rowStepY) {
			LegoU32 selectedIndex = 0;
			LegoU32 bestScore = 0;

			for (LegoU32 i = 0; i < c_racerCount; i++) {
				if (!selected[i] && m_points[i] > bestScore) {
					bestScore = m_points[i];
					selectedIndex = i;
				}
			}

			if (m_displayTimerMs >= c_hiddenInactiveThresholdMs ||
				m_context->m_playerSetupSlots[selectedIndex].m_unk0x10) {
				::sprintf(buffer, "%ld", rank + 1);
				renderer->VTable0x68(buffer, m_unk0x00, c_rankX, y, 1.0f, 1.0f, NULL, 0);

				RaceState::Racer* selectedRacer = &racers[selectedIndex];
				renderer->VTable0x64(&selectedRacer->m_displayName, m_unk0x00, c_racerNameX, y, 1.0f, 1.0f, NULL, 0);

				::sprintf(buffer, "%ld", m_points[selectedIndex]);
				renderer->VTable0x68(buffer, m_unk0x00, c_pointsX, y, 1.0f, 1.0f, NULL, 0);
			}

			selected[selectedIndex] = TRUE;
			rank++;
		}
	}
	else {
		LegoU32 leaderIndex = 0;
		LegoU32 leaderScore = 0;
		for (LegoU32 i = 0; i < c_racerCount; i++) {
			if (m_roundPoints[i] >= leaderScore) {
				leaderScore = m_roundPoints[i];
				leaderIndex = i;
			}
		}

		RaceState::Racer* leaderRacer = &racers[leaderIndex];
		leaderRacer->FUN_00439c70(deltaEntries);

		LegoS32 sign = 1;
		LegoS32 rank = 0;
		::memset(selected, 0, sizeof(selected));
		for (LegoU32 y = c_rowStartY; y < c_rowEndY; y += c_rowStepY) {
			LegoU32 selectedIndex = leaderIndex;
			LegoU32 bestScore = 0;

			for (LegoU32 i = 0; i < c_racerCount; i++) {
				if (!selected[i] && m_roundPoints[i] >= bestScore) {
					bestScore = m_roundPoints[i];
					selectedIndex = i;
				}
			}

			if (m_displayTimerMs >= c_hiddenInactiveThresholdMs ||
				m_context->m_playerSetupSlots[selectedIndex].m_unk0x10) {
				::sprintf(buffer, "%ld", rank + 1);
				renderer->VTable0x68(buffer, m_unk0x00, c_rankX, y, 1.0f, 1.0f, NULL, 0);

				RaceState::Racer* selectedRacer = &racers[selectedIndex];
				renderer->VTable0x64(&selectedRacer->m_displayName, m_unk0x00, c_racerNameX, y, 1.0f, 1.0f, NULL, 0);

				::sprintf(buffer, "%ld", m_roundPoints[selectedIndex]);
				renderer->VTable0x68(buffer, m_unk0x00, c_pointsX, y, 1.0f, 1.0f, NULL, 0);

				LegoU32 deltaIndex = 0;
				while (deltaIndex < c_racerCount && deltaEntries[deltaIndex].m_racer != selectedRacer) {
					deltaIndex++;
				}

				if (deltaIndex < c_racerCount) {
					RaceState::Racer::Field0x00c::StandingsDeltaEntry* deltaEntry = &deltaEntries[deltaIndex];
					if (deltaEntry->m_racer == leaderRacer) {
						string.CopyFromBufSelection(m_unk0x0c->GetStringBuffer(c_leaderStringId), 0);
						renderer->VTable0x64(&string, m_unk0x00, c_deltaSignX, y, 1.0f, 1.0f, NULL, 0);
					}
					else if (deltaEntry->m_racer->m_unk0xd04 & c_racerFlags0xd04Bit12) {
						LegoS32 delta = deltaEntry->m_delta;
						if (delta <= 0) {
							if (delta < 0) {
								sign = -1;
								delta = -delta;
								deltaEntry->m_delta = delta;
							}
						}
						else {
							sign = 1;
						}

						LegoU32 time = static_cast<LegoU32>(delta) % c_millisecondsPerHour;
						LegoS32 digitOffset;
						timeBuffer[8] = '\0';
						if (time >= c_longTimeThresholdMs) {
							digitOffset = 7;
							timeBuffer[5] = ':';
							timeBuffer[2] = ':';
						}
						else {
							digitOffset = 6;
							timeBuffer[4] = ':';
							timeBuffer[1] = ':';
							timeBuffer[7] = '\0';
						}

						LegoU32 centiseconds = time / c_timeDivisor;
						timeBuffer[digitOffset] = static_cast<LegoChar>(centiseconds % c_timeDivisor + '0');
						centiseconds /= c_timeDivisor;
						timeBuffer[digitOffset - 1] = static_cast<LegoChar>(centiseconds % c_timeDivisor + '0');

						LegoU32 seconds = centiseconds / c_timeDivisor;
						LegoS32 secondsWithinMinute = static_cast<LegoS32>(seconds % 60);
						LegoU32 minutes = seconds / 60;
						timeBuffer[digitOffset - 3] = static_cast<LegoChar>(secondsWithinMinute % c_timeDivisor + '0');
						timeBuffer[digitOffset - 4] =
							static_cast<LegoChar>((secondsWithinMinute / c_timeDivisor) % c_timeDivisor + '0');

						timeBuffer[digitOffset - 6] = static_cast<LegoChar>(minutes % c_timeDivisor + '0');
						LegoU32 extraMinutes = minutes / c_timeDivisor;
						if (extraMinutes) {
							timeBuffer[digitOffset - 7] = static_cast<LegoChar>(extraMinutes % c_timeDivisor + '0');
						}

						renderer->VTable0x68(timeBuffer, m_unk0x00, c_deltaTimeX, y, 1.0f, 1.0f, NULL, 0);
						renderer->VTable0x68(
							sign == 1 ? g_circuitStandingsPlusSign : g_circuitStandingsMinusSign,
							m_unk0x00,
							c_deltaSignX,
							y,
							1.0f,
							1.0f,
							NULL,
							0
						);
					}
					else {
						string.CopyFromBufSelection(m_unk0x0c->GetStringBuffer(c_trailingStringId), 0);
						renderer->VTable0x64(&string, m_unk0x00, c_deltaSignX, y, 1.0f, 1.0f, NULL, 0);
					}
				}
			}

			selected[selectedIndex] = TRUE;
			rank++;
		}
	}
}

// FUNCTION: LEGORACERS 0x00440860
void CircuitStandings::ClearPoints()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_points); i++) {
		m_points[i] = 0;
		m_roundPoints[i] = 0;
	}
}

#include "race/circuitstandings.h"

#include "golfontbase.h"
#include "golstring.h"
#include "golstringtable.h"
#include "race/racestate.h"
#include "render/gold3drenderdevice.h"
#include "surface/golrendertarget.h"

#include <memory.h>
#include <stdio.h>

DECOMP_SIZE_ASSERT(CircuitStandings, 0x48)

// GLOBAL: LEGORACERS 0x004b0b58
const LegoU32 g_circuitPointsByPosition[6] = {30, 20, 10, 3, 2, 1};

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

	m_font = 0;
	m_context = NULL;
	m_raceState = 0;
	m_stringTable = 0;

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
void CircuitStandings::ClearRoundPoints()
{
	LegoU32* values = m_roundPoints;
	LegoS32 remaining = sizeOfArray(m_roundPoints);
	do {
		*values++ = 0;
	} while (--remaining);
}

// FUNCTION: LEGORACERS 0x004402c0
void CircuitStandings::AwardPoints(LegoU32 p_racerIndex, LegoU32 p_position)
{
	m_roundPoints[p_racerIndex] = g_circuitPointsByPosition[p_position];
	m_points[p_racerIndex] += g_circuitPointsByPosition[p_position];
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
void CircuitStandings::Update(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs > m_displayTimerMs) {
		m_displayTimerMs = c_displayResetMs;
	}
	else {
		m_displayTimerMs -= p_elapsedMs;
	}
}

// FUNCTION: LEGORACERS 0x004246d0 FOLDED
LegoU32 CircuitStandings::FormatTime(LegoChar* p_buffer, LegoU32 p_time)
{
	LegoU32 millisecondsPerHour = 3600000;
	LegoS32 divisor = 10;
	LegoU32 time = p_time % millisecondsPerHour;
	LegoS32 digitOffset;

	p_buffer[8] = '\0';
	if (time >= 600000) {
		digitOffset = 7;
		p_buffer[5] = ':';
		p_buffer[2] = ':';
	}
	else {
		digitOffset = 6;
		p_buffer[4] = ':';
		p_buffer[1] = ':';
		p_buffer[7] = '\0';
	}

	LegoU32 centiseconds = time / 10;
	p_buffer[digitOffset] = static_cast<LegoChar>(centiseconds % 10 + '0');
	centiseconds /= 10;
	p_buffer[digitOffset - 1] = static_cast<LegoChar>(centiseconds % 10 + '0');

	LegoU32 seconds = centiseconds / divisor;
	LegoS32 secondsWithinMinute = static_cast<LegoS32>(seconds % 60);
	LegoU32 minutes = seconds / 60;
	p_buffer[digitOffset - 3] = static_cast<LegoChar>(secondsWithinMinute % divisor + '0');
	p_buffer[digitOffset - 4] = static_cast<LegoChar>((secondsWithinMinute / divisor) % divisor + '0');

	p_buffer[digitOffset - 6] = static_cast<LegoChar>(minutes % divisor + '0');
	LegoU32 extraMinutes = minutes / divisor;
	if (extraMinutes) {
		p_buffer[digitOffset - 7] = static_cast<LegoChar>(extraMinutes % divisor + '0');
		extraMinutes /= divisor;
	}

	return extraMinutes;
}

// STUB: LEGORACERS 0x00440350
void CircuitStandings::Draw(LegoBool32 p_showCircuitPoints)
{
	GolString string;
	LegoChar timeBuffer[12];
	LegoChar buffer[64];
	LegoU32 selected[c_racerCount];
	Racer::StandingsDeltaEntry deltaEntries[c_racerCount];
	GolD3DRenderDevice* renderer = m_context->m_golApp->GetRenderer();
	const GolRenderTarget* renderTargetInfo = renderer->GetRenderTargetInfo();

	if (!m_isVisible) {
		return;
	}

	Racer* racers = m_raceState->GetRacers();

	if (p_showCircuitPoints) {
		string.CopyFromBufSelection(m_stringTable->GetStringBuffer(c_titleStringId), 0);
		LegoS32 textWidth;
		LegoS32 textHeight;
		m_font->MeasureString(&string, &textWidth, &textHeight);
		renderer->DrawString(
			&string,
			m_font,
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
				m_context->m_playerSetupSlots[selectedIndex].m_slotState) {
				::sprintf(buffer, "%ld", rank + 1);
				renderer->DrawCString(buffer, m_font, c_rankX, y, 1.0f, 1.0f, NULL, 0);

				Racer* selectedRacer = &racers[selectedIndex];
				renderer->DrawString(&selectedRacer->m_displayName, m_font, c_racerNameX, y, 1.0f, 1.0f, NULL, 0);

				::sprintf(buffer, "%ld", m_points[selectedIndex]);
				renderer->DrawCString(buffer, m_font, c_pointsX, y, 1.0f, 1.0f, NULL, 0);
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

		Racer* leaderRacer = &racers[leaderIndex];
		leaderRacer->ComputeStandingsDeltas(deltaEntries);

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
				m_context->m_playerSetupSlots[selectedIndex].m_slotState) {
				::sprintf(buffer, "%ld", rank + 1);
				renderer->DrawCString(buffer, m_font, c_rankX, y, 1.0f, 1.0f, NULL, 0);

				Racer* selectedRacer = &racers[selectedIndex];
				renderer->DrawString(&selectedRacer->m_displayName, m_font, c_racerNameX, y, 1.0f, 1.0f, NULL, 0);

				::sprintf(buffer, "%ld", m_roundPoints[selectedIndex]);
				renderer->DrawCString(buffer, m_font, c_pointsX, y, 1.0f, 1.0f, NULL, 0);

				LegoU32 deltaIndex = 0;
				while (deltaIndex < c_racerCount && deltaEntries[deltaIndex].m_racer != selectedRacer) {
					deltaIndex++;
				}

				if (deltaIndex < c_racerCount) {
					Racer::StandingsDeltaEntry* deltaEntry = &deltaEntries[deltaIndex];
					if (deltaEntry->m_racer == leaderRacer) {
						string.CopyFromBufSelection(m_stringTable->GetStringBuffer(c_leaderStringId), 0);
						renderer->DrawString(&string, m_font, c_deltaSignX, y, 1.0f, 1.0f, NULL, 0);
					}
					else if (deltaEntry->m_racer->m_flags & Racer::c_flagFinished) {
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

						FormatTime(timeBuffer, delta);
						renderer->DrawCString(timeBuffer, m_font, c_deltaTimeX, y, 1.0f, 1.0f, NULL, 0);

						if (sign == 1) {
							renderer
								->DrawCString(g_circuitStandingsPlusSign, m_font, c_deltaSignX, y, 1.0f, 1.0f, NULL, 0);
						}
						else if (sign == -1) {
							renderer->DrawCString(
								g_circuitStandingsMinusSign,
								m_font,
								c_deltaSignX,
								y,
								1.0f,
								1.0f,
								NULL,
								0
							);
						}
					}
					else {
						string.CopyFromBufSelection(m_stringTable->GetStringBuffer(c_trailingStringId), 0);
						renderer->DrawString(&string, m_font, c_deltaSignX, y, 1.0f, 1.0f, NULL, 0);
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

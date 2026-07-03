#ifndef CIRCUITSTANDINGS_H
#define CIRCUITSTANDINGS_H

#include "app/legoracers.h"
#include "decomp.h"
#include "types.h"

class GolFontBase;
class GolStringTable;
class RaceState;

// SIZE 0x48
class CircuitStandings {
public:
	CircuitStandings();
	~CircuitStandings();

	void Reset();
	undefined4 SetContext(LegoRacers::Context* p_context);
	void Shutdown();
	LegoU32 GetPoints(LegoU32 p_index);
	LegoS32 GetRank(LegoU32 p_index);
	void Update(LegoU32 p_elapsedMs);
	void Draw(LegoBool32 p_showCircuitPoints);
	void ClearPoints();

private:
	friend class RaceSession;

	void ClearRoundPoints();
	void AwardPoints(LegoU32 p_racerIndex, LegoU32 p_position);
	LegoU32 FormatTime(LegoChar* p_buffer, LegoU32 p_time);

	enum {
		c_racerCount = 6,
		c_displayResetMs = 400,
		c_hiddenInactiveThresholdMs = 150,
		c_titleStringId = 0x2d,
		c_leaderStringId = 0x2a,
		c_trailingStringId = 0x2b,
		c_rankX = 20,
		c_racerNameX = 50,
		c_pointsX = 450,
		c_deltaSignX = 500,
		c_deltaTimeX = 520,
		c_titleY = 60,
		c_rowStartY = 132,
		c_rowStepY = 32,
		c_rowEndY = 0x144,
		c_millisecondsPerHour = 3600000,
		c_longTimeThresholdMs = 600000,
		c_timeDivisor = 10,
	};

	GolFontBase* m_font;                 // 0x00
	LegoRacers::Context* m_context;      // 0x04
	RaceState* m_raceState;              // 0x08
	GolStringTable* m_stringTable;       // 0x0c
	LegoU32 m_points[c_racerCount];      // 0x10
	LegoU32 m_roundPoints[c_racerCount]; // 0x28
	LegoU32 m_displayTimerMs;            // 0x40
	LegoBool32 m_isVisible;              // 0x44
};

#endif // CIRCUITSTANDINGS_H

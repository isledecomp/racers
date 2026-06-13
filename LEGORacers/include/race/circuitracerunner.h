#ifndef CIRCUITRACERUNNER_H
#define CIRCUITRACERUNNER_H

#include "app/legoracers.h"
#include "compat.h"
#include "decomp.h"
#include "race/circuitstandings.h"
#include "types.h"
#include "util/cactusinterface0x4.h"

class RaceSession;

// VTABLE: LEGORACERS 0x004aff70
// SIZE 0x94
class CircuitRaceRunner : public CactusInterface0x4 {
public:
	CircuitRaceRunner();
	virtual ~CircuitRaceRunner(); // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0041ec70
	// CircuitRaceRunner::`scalar deleting destructor'

	void Reset();
	LegoS32 Initialize(LegoRacers::Context* p_context, RaceSession* p_session);
	void Shutdown();
	void Run();

private:
	enum {
		c_firstPointsIndex = 0,
		c_singlePlayerCount = 1,
		c_pointsThresholdStep = 10,
	};

	CircuitStandings m_standings;   // 0x04
	LegoRacers::Context* m_context; // 0x4c
	RaceSession* m_session;         // 0x50
	undefined4 m_unk0x54[2][4][2];  // 0x54
};

#endif // CIRCUITRACERUNNER_H

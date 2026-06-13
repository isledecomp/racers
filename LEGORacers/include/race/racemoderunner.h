#ifndef RACEMODERUNNER_H
#define RACEMODERUNNER_H

#include "app/legoracers.h"
#include "decomp.h"
#include "race/circuitracerunner.h"
#include "race/racesession.h"
#include "race/timeracemanager.h"
#include "types.h"

// SIZE 0x37b8
class RaceModeRunner {
public:
	RaceModeRunner();
	~RaceModeRunner();

	static void Run(LegoRacers::Context* p_context);

	LegoS32 Initialize(LegoRacers::Context* p_context);
	void Run();
	void Shutdown();

private:
	void ReleaseContextAssets();
	LegoS32 InitializeRaceScene();

	LegoRacers::Context* m_context;    // 0x00
	CircuitRaceRunner m_circuitRunner; // 0x04
	RaceSession m_session;             // 0x98
	TimeRaceManager m_timeRaceManager; // 0x3400
};

#endif // RACEMODERUNNER_H

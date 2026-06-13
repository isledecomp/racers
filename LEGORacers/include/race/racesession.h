#ifndef RACESESSION_H
#define RACESESSION_H

#include "app/golappeventhandler.h"
#include "app/legoracers.h"
#include "compat.h"
#include "decomp.h"
#include "input/inputeventqueue.h"
#include "race/racestate.h"
#include "types.h"

class GolD3DRenderDevice;
class CircuitStandings;
class TimeRaceManager;
class GolExport;
class SoundManager;
class Win32GolApp;

// VTABLE: LEGORACERS 0x004b07f4
// SIZE 0x3368
class RaceSession : public GolAppEventHandler {
public:
	RaceSession();
	void VTable0x00() override; // vtable+0x00
	LegoS32 Initialize(
		LegoRacers::Context* p_context,
		const LegoChar* p_raceName,
		undefined4 p_mirror,
		TimeRaceManager* p_timeRaceManager
	);
	void Shutdown();
	void Run();
	virtual void VTable0x30();           // vtable+0x30
	virtual void VTable0x34();           // vtable+0x34
	virtual void VTable0x38();           // vtable+0x38
	virtual void VTable0x3c();           // vtable+0x3c
	virtual void VTable0x40();           // vtable+0x40
	virtual void VTable0x44(undefined4); // vtable+0x44
	virtual void VTable0x48(undefined4); // vtable+0x48
	virtual ~RaceSession();              // vtable+0x4c
	void SetStandings(CircuitStandings* p_standings) { m_standings = p_standings; }

	// SYNTHETIC: LEGORACERS 0x00431960
	// RaceSession::`scalar deleting destructor'

private:
	void FUN_004349a0();
	void FUN_00434b00();
	void FUN_00434c80();
	void FUN_00434eb0();
	void FUN_00435180();
	void FUN_004354d0();
	void FUN_00436010();

	LegoRacers::Context* m_context;         // 0x04
	Win32GolApp* m_golApp;                  // 0x08
	SoundManager* m_soundManager;           // 0x0c
	GolExport* m_golExport;                 // 0x10
	GolD3DRenderDevice* m_renderer;         // 0x14
	CircuitStandings* m_standings;          // 0x18
	undefined m_unk0x1c[0x220 - 0x1c];      // 0x1c
	InputEventQueue m_inputEvents;          // 0x220
	undefined m_unk0x23c[0x3bc - 0x23c];    // 0x23c
	RaceState m_raceState;                  // 0x3bc
	undefined m_unk0x6dc[0x30c0 - 0x6dc];   // 0x6dc
	undefined4 m_unk0x30c0;                 // 0x30c0
	undefined m_unk0x30c4[0x3328 - 0x30c4]; // 0x30c4
	undefined4 m_state;                     // 0x3328
	LegoU32 m_elapsedMs;                    // 0x332c
	undefined4 m_unk0x3330;                 // 0x3330
	undefined4 m_running;                   // 0x3334
	LegoBool m_unk0x3338;                   // 0x3338
	undefined m_unk0x3339[0x333c - 0x3339]; // 0x3339
	LegoU32 m_frameCount;                   // 0x333c
	LegoU32 m_unk0x3340;                    // 0x3340
	LegoFloat m_fps;                        // 0x3344
	undefined m_unk0x3348;                  // 0x3348
	undefined m_unk0x3349[0x3350 - 0x3349]; // 0x3349
	undefined4 m_unk0x3350;                 // 0x3350
	undefined4 m_unk0x3354;                 // 0x3354
	undefined4 m_unk0x3358;                 // 0x3358
	undefined4 m_unk0x335c;                 // 0x335c
	undefined4 m_unk0x3360;                 // 0x3360
	TimeRaceManager* m_timeRaceManager;     // 0x3364
};

#endif // RACESESSION_H

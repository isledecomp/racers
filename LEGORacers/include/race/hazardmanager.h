#ifndef HAZARDMANAGER_H
#define HAZARDMANAGER_H

#include "decomp.h"
#include "goltxtparser.h"
#include "types.h"

class GolCamera;
class GolD3DRenderDevice;
class Hazard;
class Racer;

// SIZE 0x08
class HazardManager {
public:
	// VTABLE: LEGORACERS 0x004b40f8
	// SIZE 0x1fc
	class HzbTxtParser : public GolTxtParser {
	public:
		// .hzb tokens: one keyword per hazard type
		enum {
			e_hazards = 0x27,
			e_fallingPillar = 0x28,
			e_sphinx = 0x29,
			e_hammer = 0x2a,
			e_ghost = 0x2b,
			e_lavaGeyser = 0x2c,
			e_codePuzzle = 0x2d,
			e_rocket = 0x2e,
			e_snowfall = 0x2f,
			e_smokeVent = 0x30,
			e_movingObstacle = 0x32,
			e_launcher = 0x33,
			e_triggeredAnimation = 0x34,
			e_oscillator = 0x36,
			e_multiLauncher = 0x3d,
			e_rollingRock = 0x3e,
			e_curseDrop = 0x3f,
			e_sweepCannon = 0x40,
			e_cannonballRain = 0x43,
			e_grabber = 0x48,
			e_warpPad = 0x49,
			e_trigger = 0x3b,
			e_entity = 0x42,
			e_source = 0x37,
			e_target = 0x38,
			e_triggerPosition = 0x39,
			e_triggerRadius = 0x3a,
			e_collider = 0x41,
			e_interval = 0x44,
			e_material = 0x45,
			e_period = 0x46,
			e_sweep = 0x47,
		};
	};

	HazardManager();
	~HazardManager();

	void NotifyEventStart(LegoS32 p_eventId, void* p_context);
	void NotifyEventEnd(LegoS32 p_eventId, void* p_context);
	void ForceDeactivate(LegoS32 p_eventId);
	void NotifyEventPair(LegoS32 p_startId, LegoS32 p_endId, void* p_context);
	void DispatchEventStart(LegoS32 p_eventId, void* p_context);
	void DispatchEventEnd(LegoS32 p_eventId, void* p_context);
	void DispatchEventPair(LegoS32 p_startId, LegoS32 p_endId, void* p_context);
	void Update(undefined4 p_elapsedMs);
	void UpdatePerRacer(GolCamera* p_camera, Racer* p_racer);
	void Draw(GolD3DRenderDevice* p_renderer);
	void ResetAll();

private:
	friend class RaceSession;

	void Destroy();
	void LoadHazards(void* p_context, const LegoChar* p_name, LegoBool32 p_binary);

	LegoU32 m_count;    // 0x00
	Hazard** m_entries; // 0x04
};

#endif // HAZARDMANAGER_H

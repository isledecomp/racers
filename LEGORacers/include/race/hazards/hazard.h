#ifndef HAZARD_H
#define HAZARD_H

#include "util/legoeventqueue.h"

class GolCamera;
class GolD3DRenderDevice;
class GolFileParser;
class HazardContext;
class RaceEventTable;
class Racer;

// VTABLE: LEGORACERS 0x004b40c4
// SIZE 0x10
class Hazard : public LegoEventQueue::Callback {
public:
	Hazard();
	void OnEvent(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
	virtual void OnActivate(void*) = 0;                          // vtable+0x04
	virtual void OnDeactivate(void*) = 0;                        // vtable+0x08
	virtual ~Hazard();                                           // vtable+0x0c
	virtual void Load(HazardContext*, GolFileParser*) = 0;       // vtable+0x10
	virtual void Update(undefined4 p_elapsedMs);                 // vtable+0x14
	virtual void UpdatePerRacer(GolCamera*, Racer*);             // vtable+0x18
	virtual void Draw(GolD3DRenderDevice*);                      // vtable+0x1c
	virtual LegoBool32 CanRetrigger();                           // vtable+0x20
	virtual void ResetState();                                   // vtable+0x24
	virtual void OnEventStart(LegoS32, void*);                   // vtable+0x28
	virtual void OnEventEnd(LegoS32, void*);                     // vtable+0x2c

	enum {
		c_stateUnloaded = 0,
		c_stateLoaded = 1,
		c_stateActive = 2,
		c_stateDeactivatePending = 3,
	};

	LegoS32 Reset();
	void Activate(void* p_context);
	void Deactivate(void* p_context);

	// SYNTHETIC: LEGORACERS 0x0048a420
	// Hazard::`scalar deleting destructor'

protected:
	friend class HazardManager;

	RaceEventTable* m_eventTable; // 0x04
	LegoS32 m_triggerId;          // 0x08
	LegoS32 m_state;              // 0x0c
};

#endif // HAZARD_H

#ifndef PARTANIMATIONRESOURCE_H
#define PARTANIMATIONRESOURCE_H

#include "compat.h"
#include "race/events/raceeventresource.h"
#include "types.h"

class GolAnimatedEntity;
class RaceEventTable;

// VTABLE: LEGORACERS 0x004b1c00
// SIZE 0x34
class PartAnimationResource : public RaceEventResource {
public:
	// SIZE 0x3c
	struct InitParams {
		LegoU32 m_eventId;                   // 0x00
		LegoS32 m_stateEventIds[3];          // 0x04
		RaceEventTable* m_eventTable;        // 0x10
		GolAnimatedEntity* m_animatedEntity; // 0x14
		LegoS32 m_activePart;                // 0x18
		LegoS32 m_idlePart;                  // 0x1c
		LegoS32 m_startPart;                 // 0x20
		LegoS32 m_endPart;                   // 0x24
		LegoBool32 m_looping;                // 0x28
		LegoBool32 m_noEnd;                  // 0x2c
		LegoBool32 m_triggerOnEnd;           // 0x30
		LegoBool32 m_atEventPosition;        // 0x34
		LegoBool32 m_useSharedDatabase;      // 0x38
	};

	PartAnimationResource();
	~PartAnimationResource() override;
	void OnStartAt(GolVec3* p_position) override;
	void OnEnd() override;
	void Update(LegoU32 p_elapsedMs) override;

	// FUNCTION: LEGORACERS 0x00452430 FOLDED
	LegoU32 GetKind() override { return 1; } // vtable+0x18

	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x0045f9d0
	// PartAnimationResource::`vector deleting destructor'

private:
	enum {
		c_flagLooping = 1 << 0,
		c_flagUseSharedDatabase = 1 << 4,
		c_entityFlag0x200000 = 1 << 21,
		c_entityFlags0x4e0000 = 0x4e0000,
		c_entityFlags0x0e0000 = 0x0e0000,
		c_entityFlags0x120000 = 0x120000
	};

	GolAnimatedEntity* m_animatedEntity; // 0x20
	LegoS32 m_activePart;                // 0x24
	LegoS32 m_idlePart;                  // 0x28
	LegoS32 m_startPart;                 // 0x2c
	LegoS32 m_endPart;                   // 0x30
};

#endif // PARTANIMATIONRESOURCE_H

#ifndef LOOKTARGETRESOURCE_H
#define LOOKTARGETRESOURCE_H

#include "race/events/raceeventresource.h"

// VTABLE: LEGORACERS 0x004b1ad4
// SIZE 0x2c
class LookTargetResource : public RaceEventResource {
public:
	// SIZE 0x20
	struct InitParams {
		undefined4 m_unk0x00;         // 0x00
		LegoS32 m_stateEventIds[3];   // 0x04
		RaceEventTable* m_eventTable; // 0x10
		GolVec3 m_unk0x14;            // 0x14
	};

	LookTargetResource();
	~LookTargetResource() override;
	void OnStartForRacer(Racer* p_racer) override;
	void OnEndForRacer(Racer* p_racer) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void FUN_004513d0(undefined4 p_unk0x04);
	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x00461610
	// LookTargetResource::`vector deleting destructor'

private:
	GolVec3 m_lookPosition; // 0x20
};

#endif // LOOKTARGETRESOURCE_H

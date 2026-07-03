#ifndef MODELDISTANCERESOURCE_H
#define MODELDISTANCERESOURCE_H

#include "race/events/raceeventresource.h"

class GolModelEntity;

// VTABLE: LEGORACERS 0x004b1c20
// SIZE 0x34
class ModelDistanceResource : public RaceEventResource {
public:
	// SIZE 0x24
	struct InitParams {
		undefined4 m_unk0x00;         // 0x00
		LegoS32 m_stateEventIds[3];   // 0x04
		RaceEventTable* m_eventTable; // 0x10
		GolModelEntity* m_unk0x14;    // 0x14
		LegoBool32 m_unk0x18;         // 0x18
		LegoBool32 m_unk0x1c;         // 0x1c
		LegoBool32 m_unk0x20;         // 0x20
	};

	ModelDistanceResource();
	~ModelDistanceResource() override;
	void OnStartAt(GolVec3*) override;
	void OnEnd() override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void FUN_004636e0();
	void FUN_00463700(InitParams* p_params);
	void FUN_004637a0();

	// SYNTHETIC: LEGORACERS 0x004613d0
	// ModelDistanceResource::`vector deleting destructor'

private:
	GolModelEntity* m_unk0x20;     // 0x20
	LegoFloat m_modelDistances[3]; // 0x24
	LegoBool32 m_unk0x30;          // 0x30
};

#endif // MODELDISTANCERESOURCE_H

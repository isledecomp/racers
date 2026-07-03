#ifndef NODETRANSFORMRESOURCE_H
#define NODETRANSFORMRESOURCE_H

#include "race/events/raceeventresource.h"

class GolBoundedEntity;
class GolModelEntity;

// VTABLE: LEGORACERS 0x004b1c3c
// SIZE 0x2c
class NodeTransformResource : public RaceEventResource {
public:
	// SIZE 0x24
	struct InitParams {
		undefined4 m_unk0x00;         // 0x00
		LegoS32 m_stateEventIds[3];   // 0x04
		RaceEventTable* m_eventTable; // 0x10
		GolBoundedEntity* m_unk0x14;  // 0x14
		GolModelEntity* m_unk0x18;    // 0x18
		LegoU32 m_unk0x1c;            // 0x1c
		LegoBool32 m_unk0x20;         // 0x20
	};

	NodeTransformResource();
	~NodeTransformResource() override;
	void OnStartAt(GolVec3*) override;
	void OnEnd() override;
	void Update(LegoU32 p_elapsedMs) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void FUN_004638f0();
	void FUN_00463900(InitParams* p_params);
	void FUN_00463970();

	// SYNTHETIC: LEGORACERS 0x00461010
	// NodeTransformResource::`vector deleting destructor'

private:
	GolBoundedEntity* m_unk0x20; // 0x20
	GolModelEntity* m_unk0x24;   // 0x24
	LegoU32 m_unk0x28;           // 0x28
};

#endif // NODETRANSFORMRESOURCE_H

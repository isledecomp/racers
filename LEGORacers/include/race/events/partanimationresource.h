#ifndef PARTANIMATIONRESOURCE_H
#define PARTANIMATIONRESOURCE_H

#include "race/events/raceeventresource.h"

class GolAnimatedEntity;

// VTABLE: LEGORACERS 0x004b1c00
// SIZE 0x34
class PartAnimationResource : public RaceEventResource {
public:
	// SIZE 0x3c
	struct InitParams {
		undefined4 m_unk0x00;         // 0x00
		LegoS32 m_stateEventIds[3];   // 0x04
		RaceEventTable* m_eventTable; // 0x10
		GolAnimatedEntity* m_unk0x14; // 0x14
		LegoS32 m_unk0x18;            // 0x18
		LegoS32 m_unk0x1c;            // 0x1c
		LegoS32 m_unk0x20;            // 0x20
		LegoS32 m_unk0x24;            // 0x24
		LegoBool32 m_unk0x28;         // 0x28
		LegoBool32 m_unk0x2c;         // 0x2c
		LegoBool32 m_unk0x30;         // 0x30
		LegoBool32 m_unk0x34;         // 0x34
		LegoBool32 m_unk0x38;         // 0x38
	};

	PartAnimationResource();
	~PartAnimationResource() override;
	void OnStartAt(GolVec3* p_unk0x04) override;
	void OnEnd() override;
	void Update(LegoU32 p_elapsedMs) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void FUN_00463330(InitParams* p_params);
	void FUN_004633e0();

	// SYNTHETIC: LEGORACERS 0x0045f9d0
	// PartAnimationResource::`vector deleting destructor'

private:
	enum {
		c_flags0x1cBit0 = 1 << 0,
		c_flags0x1cBit4 = 1 << 4,
		c_entityFlag0x200000 = 1 << 21,
		c_entityFlags0x4e0000 = 0x4e0000,
		c_entityFlags0x0e0000 = 0x0e0000,
		c_entityFlags0x120000 = 0x120000
	};

	GolAnimatedEntity* m_unk0x20; // 0x20
	LegoS32 m_unk0x24;            // 0x24
	LegoS32 m_unk0x28;            // 0x28
	LegoS32 m_unk0x2c;            // 0x2c
	LegoS32 m_unk0x30;            // 0x30
};

#endif // PARTANIMATIONRESOURCE_H

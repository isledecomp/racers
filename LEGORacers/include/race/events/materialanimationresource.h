#ifndef MATERIALANIMATIONRESOURCE_H
#define MATERIALANIMATIONRESOURCE_H

#include "race/events/raceeventresource.h"

class MabMaterialAnimation;
class MabMaterialTrack;
struct MaterialTable;

// VTABLE: LEGORACERS 0x004b1be4
// SIZE 0x34
class MaterialAnimationResource : public RaceEventResource {
public:
	// SIZE 0x38
	struct InitParams {
		undefined4 m_unk0x00;             // 0x00
		LegoS32 m_stateEventIds[3];       // 0x04
		RaceEventTable* m_eventTable;     // 0x10
		MabMaterialAnimation* m_unk0x14;  // 0x14
		MaterialTable* m_unk0x18;         // 0x18
		LegoU16 m_unk0x1c;                // 0x1c
		undefined m_unk0x1e[0x20 - 0x1e]; // 0x1e
		LegoU32 m_unk0x20;                // 0x20
		LegoU32 m_unk0x24;                // 0x24
		LegoBool32 m_unk0x28;             // 0x28
		LegoBool32 m_unk0x2c;             // 0x2c
		LegoBool32 m_unk0x30;             // 0x30
		LegoBool32 m_unk0x34;             // 0x34
	};

	MaterialAnimationResource();
	~MaterialAnimationResource() override;
	void OnStartAt(GolVec3* p_unk0x04) override;
	void OnEnd() override;
	void Update(LegoU32 p_elapsedMs) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void FUN_00463120(InitParams* p_params);
	void FUN_004631e0();

	// SYNTHETIC: LEGORACERS 0x0045fe50
	// MaterialAnimationResource::`vector deleting destructor'

private:
	enum {
		c_flags0x1cBit0 = 1 << 0
	};

	MabMaterialAnimation* m_unk0x20;  // 0x20
	MabMaterialTrack* m_unk0x24;      // 0x24
	MabMaterialTrack* m_unk0x28;      // 0x28
	MaterialTable* m_unk0x2c;         // 0x2c
	LegoU16 m_unk0x30;                // 0x30
	undefined m_unk0x32[0x34 - 0x32]; // 0x32
};

#endif // MATERIALANIMATIONRESOURCE_H

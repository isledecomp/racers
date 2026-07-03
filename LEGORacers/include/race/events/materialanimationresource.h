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
		LegoU32 m_eventId;                         // 0x00
		LegoS32 m_stateEventIds[3];                // 0x04
		RaceEventTable* m_eventTable;              // 0x10
		MabMaterialAnimation* m_materialAnimation; // 0x14
		MaterialTable* m_materialTable;            // 0x18
		LegoU16 m_materialIndex;                   // 0x1c
		undefined m_unk0x1e[0x20 - 0x1e];          // 0x1e
		LegoU32 m_activeTrackIndex;                // 0x20
		LegoU32 m_idleTrackIndex;                  // 0x24
		LegoBool32 m_looping;                      // 0x28
		LegoBool32 m_noEnd;                        // 0x2c
		LegoBool32 m_triggerOnEnd;                 // 0x30
		LegoBool32 m_atEventPosition;              // 0x34
	};

	MaterialAnimationResource();
	~MaterialAnimationResource() override;
	void OnStartAt(GolVec3* p_position) override;
	void OnEnd() override;
	void Update(LegoU32 p_elapsedMs) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x0045fe50
	// MaterialAnimationResource::`vector deleting destructor'

private:
	enum {
		c_flagLooping = 1 << 0
	};

	MabMaterialAnimation* m_materialAnimation; // 0x20
	MabMaterialTrack* m_activeTrack;           // 0x24
	MabMaterialTrack* m_idleTrack;             // 0x28
	MaterialTable* m_materialTable;            // 0x2c
	LegoU16 m_materialIndex;                   // 0x30
	undefined m_unk0x32[0x34 - 0x32];          // 0x32
};

#endif // MATERIALANIMATIONRESOURCE_H

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
		undefined4 m_eventId;              // 0x00
		LegoS32 m_stateEventIds[3];        // 0x04
		RaceEventTable* m_eventTable;      // 0x10
		GolBoundedEntity* m_boundedEntity; // 0x14
		GolModelEntity* m_modelEntity;     // 0x18
		LegoU32 m_unk0x1c;                 // 0x1c
		LegoBool32 m_triggerOnEnd;         // 0x20
	};

	NodeTransformResource();
	~NodeTransformResource() override;
	void OnStartAt(GolVec3*) override;
	void OnEnd() override;
	void Update(LegoU32 p_elapsedMs) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void ClearFields();
	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x00461010
	// NodeTransformResource::`vector deleting destructor'

private:
	GolBoundedEntity* m_boundedEntity; // 0x20
	GolModelEntity* m_modelEntity;     // 0x24
	LegoU32 m_nodeIndex;               // 0x28
};

#endif // NODETRANSFORMRESOURCE_H

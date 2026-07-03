#ifndef MODELDISTANCERESOURCE_H
#define MODELDISTANCERESOURCE_H

#include "race/events/raceeventresource.h"

class GolModelEntity;

// VTABLE: LEGORACERS 0x004b1c20
// SIZE 0x34
class ModelDistanceResource : public RaceEventResource {
public:
	// .evb field token scoped to the modelDistances section
	enum {
		e_hideWhenActive = 0x46,
	};

	// SIZE 0x24
	struct InitParams {
		LegoU32 m_eventId;             // 0x00
		LegoS32 m_stateEventIds[3];    // 0x04
		RaceEventTable* m_eventTable;  // 0x10
		GolModelEntity* m_modelEntity; // 0x14
		LegoBool32 m_noEnd;            // 0x18
		LegoBool32 m_triggerOnEnd;     // 0x1c
		LegoBool32 m_hideWhenActive;   // 0x20
	};

	ModelDistanceResource();
	~ModelDistanceResource() override;
	void OnStartAt(GolVec3*) override;
	void OnEnd() override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void ClearFields();
	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x004613d0
	// ModelDistanceResource::`vector deleting destructor'

private:
	GolModelEntity* m_modelEntity; // 0x20
	LegoFloat m_modelDistances[3]; // 0x24
	LegoBool32 m_hideWhenActive;   // 0x30
};

#endif // MODELDISTANCERESOURCE_H

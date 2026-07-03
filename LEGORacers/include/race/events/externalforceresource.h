#ifndef EXTERNALFORCERESOURCE_H
#define EXTERNALFORCERESOURCE_H

#include "race/events/raceeventresource.h"

// VTABLE: LEGORACERS 0x004b1bc8
// SIZE 0x38
class ExternalForceResource : public RaceEventResource {
public:
	// .evb external-force field tokens
	enum {
		e_force = 0x3e,
		e_channel = 0x4c,
		e_armEventId = 0x5a,
	};

	// SIZE 0x30
	struct InitParams {
		LegoU32 m_eventId;            // 0x00
		LegoS32 m_stateEventIds[3];   // 0x04
		RaceEventTable* m_eventTable; // 0x10
		GolVec3 m_force;              // 0x14
		LegoU32 m_channel;            // 0x20
		LegoS32 m_armEventId;         // 0x24
		LegoBool32 m_noEnd;           // 0x28
		LegoBool32 m_triggerOnEnd;    // 0x2c
	};

	ExternalForceResource();
	~ExternalForceResource() override;
	void OnStartForRacer(Racer* p_racer) override;
	void OnEndForRacer(Racer* p_racer) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void ClearFields();
	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x00461930
	// ExternalForceResource::`vector deleting destructor'

public:
	enum {
		c_forceFlagArmed = 1 << 0
	};

	GolVec3 m_force;                  // 0x20
	LegoU32 m_channel;                // 0x2c
	LegoS32 m_armEventId;             // 0x30
	LegoU8 m_forceFlags;              // 0x34
	undefined m_unk0x35[0x38 - 0x35]; // 0x35
};

#endif // EXTERNALFORCERESOURCE_H

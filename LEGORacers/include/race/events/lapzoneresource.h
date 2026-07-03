#ifndef LAPZONERESOURCE_H
#define LAPZONERESOURCE_H

#include "race/events/raceeventresource.h"

// VTABLE: LEGORACERS 0x004b1ca4
// SIZE 0x24
class LapZoneResource : public RaceEventResource {
public:
	// SIZE 0x18
	struct InitParams {
		LegoU32 m_eventId;            // 0x00
		LegoS32 m_stateEventIds[3];   // 0x04
		RaceEventTable* m_eventTable; // 0x10
		undefined4 m_zone;            // 0x14
	};

	LapZoneResource();
	~LapZoneResource() override;
	void OnStartForRacer(Racer* p_racer) override;
	void OnEndForRacer(Racer* p_racer) override;

	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x00461b40
	// LapZoneResource::`vector deleting destructor'

private:
	undefined4 m_zone; // 0x20
};

#endif // LAPZONERESOURCE_H

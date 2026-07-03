#ifndef SKYSTATERESOURCE_H
#define SKYSTATERESOURCE_H

#include "golname.h"
#include "race/events/raceeventresource.h"

class RaceSkyState;

// VTABLE: LEGORACERS 0x004b1aac
// SIZE 0x34
class SkyStateResource : public RaceEventResource {
public:
	// SIZE 0x2c
	struct InitParams {
		undefined4 m_eventId;             // 0x00
		LegoS32 m_stateEventIds[3];       // 0x04
		RaceEventTable* m_eventTable;     // 0x10
		RaceSkyState* m_skyState;         // 0x14
		GolName m_skyName;                // 0x18
		LegoU32 m_unk0x20;                // 0x20
		LegoBool32 m_unk0x24;             // 0x24
		LegoU8 m_skyFlags;                // 0x28
		undefined m_unk0x29[0x2c - 0x29]; // 0x29
	};

	// .evb sky-state field tokens
	enum {
		e_skyName = 0x43,
	};

	SkyStateResource();
	~SkyStateResource() override;
	void OnStartAt(GolVec3* p_unk0x04) override;
	void OnEnd() override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void ClearFields();
	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x004606c0
	// SkyStateResource::`vector deleting destructor'

private:
	enum {
		c_flags0x30Bit0 = 1 << 0,
		c_flags0x30Bit1 = 1 << 1,
		c_flags0x30Bit2 = 1 << 2,
		c_flags0x30Bit3 = 1 << 3
	};

	RaceSkyState* m_skyState; // 0x20
	GolName m_skyName;        // 0x24
	LegoU32 m_unk0x2c;        // 0x2c
	LegoU8 m_skyFlags;        // 0x30
	undefined m_unk0x31[0x34 - 0x31];
};

#endif // SKYSTATERESOURCE_H

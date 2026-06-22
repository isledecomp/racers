#ifndef RACESESSIONFIELD0X6DCFIELD0XA8_H
#define RACESESSIONFIELD0X6DCFIELD0XA8_H

#include "decomp.h"
#include "golmath.h"
#include "race/racestate.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolWorldEntity;
class RaceSessionField0x32b4;

// VTABLE: LEGORACERS 0x004b0778
// SIZE 0xa8
class RaceSessionField0x6dcField0xa8 : public LegoEventQueue::Callback {
public:
	// SIZE 0x28
	class Params {
	public:
		GolWorldEntity* m_unk0x00;         // 0x00
		RaceSessionField0x32b4* m_unk0x04; // 0x04
		LegoFloat m_unk0x08;               // 0x08
		LegoEventQueue* m_unk0x0c;         // 0x0c
		GolVec3 m_unk0x10;                 // 0x10
		LegoFloat m_unk0x1c;               // 0x1c
		LegoU32 m_unk0x20;                 // 0x20
		LegoFloat m_unk0x24;               // 0x24
	};

	RaceSessionField0x6dcField0xa8();
	~RaceSessionField0x6dcField0xa8();
	void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
	virtual void VTable0x04(Params* p_params, GolVec3* p_unk0x08);  // vtable+0x04
	virtual void VTable0x08(                                      // vtable+0x08
		Params* p_params,
		RaceState::Racer* p_racer,
		GolVec3* p_unk0x0c,
		GolVec3* p_unk0x10,
		LegoBool32 p_unk0x14
	);
	virtual void VTable0x0c(                                            // vtable+0x0c
		Params* p_params,
		RaceState::Racer* p_racer,
		RaceState::Racer* p_targetRacer,
		LegoBool32 p_unk0x10,
		LegoBool32 p_unk0x14
	);
	virtual RaceSessionField0x6dcField0xa8* VTable0x10(undefined4); // vtable+0x10
	virtual void VTable0x14();                                      // vtable+0x14
	virtual LegoS32 VTable0x18(LegoU32 p_elapsedMs);                // vtable+0x18
	virtual void VTable0x1c(GolVec3*);                              // vtable+0x1c

	void Reset();
	void FUN_004316d0();
	void FUN_00430d40(Params* p_params);
	void FUN_00431310(RaceState::Racer* p_racer);
	void FUN_00431450(LegoFloat p_durationSeconds);
	void FUN_004314d0(LegoEventQueue* p_eventQueue);
	LegoU32 GetUnk0x004() const { return m_unk0x004; }
	GolWorldEntity* GetUnk0x008() { return m_unk0x008; }
	const GolVec3& GetUnk0x01c() const { return m_unk0x01c; }
	const GolVec3& GetUnk0x028() const { return m_unk0x028; }
	const GolVec3& GetUnk0x05c() const { return m_unk0x05c; }
	RaceState::Racer* GetUnk0x0a4() const { return m_unk0x0a4; }

protected:
	undefined4 m_unk0x004;               // 0x004
	GolWorldEntity* m_unk0x008;          // 0x008
	RaceSessionField0x32b4* m_unk0x00c;  // 0x00c
	GolVec3 m_unk0x010;                  // 0x010
	GolVec3 m_unk0x01c;                  // 0x01c
	GolVec3 m_unk0x028;                  // 0x028
	LegoFloat m_unk0x034;                // 0x034
	LegoFloat m_unk0x038;                // 0x038
	LegoFloat m_unk0x03c;                // 0x03c
	LegoFloat m_unk0x040;                // 0x040
	LegoEventQueue::Event* m_unk0x044;   // 0x044
	LegoFloat m_unk0x048;                // 0x048
	LegoFloat m_unk0x04c;                // 0x04c
	LegoS32 m_unk0x050;                  // 0x050
	undefined4 m_unk0x054;               // 0x054
	LegoU32 m_unk0x058;                  // 0x058
	GolVec3 m_unk0x05c;                  // 0x05c
	undefined m_unk0x068[0x09c - 0x068]; // 0x068
	RaceState::Racer* m_unk0x09c;        // 0x09c
	RaceState::Racer* m_unk0x0a0;        // 0x0a0
	RaceState::Racer* m_unk0x0a4;        // 0x0a4
};

#endif // RACESESSIONFIELD0X6DCFIELD0XA8_H

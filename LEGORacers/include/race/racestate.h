#ifndef RACESTATE_H
#define RACESTATE_H

#include "app/legoracers.h"
#include "decomp.h"
#include "types.h"

// SIZE 0x320
class RaceState {
public:
	// SIZE 0xdbc
	class Field0x318 {
	public:
		undefined m_unk0x000[0xdb8 - 0x000]; // 0x000
		undefined4 m_unk0xdb8;               // 0xdb8
	};

	// SIZE 0xe34
	class Racer {
	public:
		undefined m_unk0x000[0xce4 - 0x000]; // 0x000
		LegoU32 m_lapsCompleted;             // 0xce4
		undefined m_unk0xce8[0xcec - 0xce8]; // 0xce8
		LegoU32 m_lapTimes[0x148 / 4];       // 0xcec
	};

	void RecordBestTimes(LegoRacers::Context* p_context);
	Field0x318* GetUnk0x318() { return m_unk0x318; }

private:
	enum {
		c_invalidTime = 0xffffffff,
	};

	undefined m_unk0x000[0x140 - 0x000]; // 0x000
	Racer* m_racers;                     // 0x140
	LegoU32 m_racerCount;                // 0x144
	undefined m_unk0x148[0x29c - 0x148]; // 0x148
	LegoU8 m_lapCount;                   // 0x29c
	undefined m_unk0x29d[0x318 - 0x29d]; // 0x29d
	Field0x318* m_unk0x318;              // 0x318
	undefined m_unk0x31c[0x320 - 0x31c]; // 0x31c
};

#endif // RACESTATE_H

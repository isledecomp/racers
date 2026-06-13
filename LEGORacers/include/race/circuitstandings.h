#ifndef CIRCUITSTANDINGS_H
#define CIRCUITSTANDINGS_H

#include "app/legoracers.h"
#include "decomp.h"
#include "types.h"

// SIZE 0x48
class CircuitStandings {
public:
	CircuitStandings();
	~CircuitStandings();

	void Reset();
	undefined4 SetContext(LegoRacers::Context* p_context);
	void Shutdown();
	undefined4 GetPoints(LegoU32 p_index);
	LegoS32 GetRank(LegoU32 p_index);
	void ClearPoints();

private:
	undefined4 m_unk0x00;           // 0x00
	LegoRacers::Context* m_context; // 0x04
	undefined4 m_unk0x08;           // 0x08
	undefined4 m_unk0x0c;           // 0x0c
	undefined4 m_points[6];         // 0x10
	undefined4 m_unk0x28[6];        // 0x28
	undefined4 m_unk0x40;           // 0x40
	undefined4 m_unk0x44;           // 0x44
};

#endif // CIRCUITSTANDINGS_H

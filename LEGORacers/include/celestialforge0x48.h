#ifndef CELESTIALFORGE0X48_H
#define CELESTIALFORGE0X48_H

#include "decomp.h"
#include "legoracers.h"
#include "types.h"

// SIZE 0x48
class CelestialForge0x48 {
public:
	CelestialForge0x48();
	~CelestialForge0x48();

	void Reset();
	undefined4 SetContext(LegoRacers::Context* p_context);
	void FUN_004402a0();

private:
	undefined4 m_unk0x00;           // 0x00
	LegoRacers::Context* m_context; // 0x04
	undefined4 m_unk0x08;           // 0x08
	undefined4 m_unk0x0c;           // 0x0c
	undefined4 m_unk0x10[6];        // 0x10
	undefined4 m_unk0x28[6];        // 0x28
	undefined4 m_unk0x40;           // 0x40
	undefined4 m_unk0x44;           // 0x44
};

#endif // CELESTIALFORGE0X48_H

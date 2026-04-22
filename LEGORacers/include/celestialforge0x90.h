#ifndef CELESTIALFORGE0X90_H
#define CELESTIALFORGE0X90_H

#include "decomp.h"
#include "types.h"

// SIZE 0x90
class CelestialForge0x90 {
public:
	CelestialForge0x90();
	~CelestialForge0x90();

	void Reset();
	void FUN_004402a0();

private:
	undefined4 m_unk0x00;             // 0x00
	undefined4 m_unk0x04;             // 0x04
	undefined4 m_unk0x08;             // 0x08
	undefined4 m_unk0x0c;             // 0x0c
	undefined4 m_unk0x10[6];          // 0x10
	undefined4 m_unk0x28[6];          // 0x28
	undefined4 m_unk0x40;             // 0x40
	undefined4 m_unk0x44;             // 0x44
	undefined m_unk0x48[0x90 - 0x48]; // 0x48
};

#endif // CELESTIALFORGE0X90_H

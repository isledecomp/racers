#ifndef NEONCACTUS0X1D6C_H
#define NEONCACTUS0X1D6C_H

#include "amberwolf0x98.h"
#include "cactusinterface0x4.h"
#include "cobaltmist0x30.h"
#include "decomp.h"
#include "ironflame0x944.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b0568
// SIZE 0x1d6c
class NeonCactus0x1d6c : public CactusInterface0x4 {
public:
	virtual ~NeonCactus0x1d6c(); // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0042bb20
	// NeonCactus0x1d6c::`scalar deleting destructor'

	LegoS32 Init(LegoS32 p_argc, LegoChar** p_argv);
	void FUN_0042bc20();
	void FUN_0042bc40();
	void FUN_0042bd00();
	void FUN_0042be90();
	LegoS32 FUN_0042bee0(LegoS32 p_argc, LegoChar** p_argv);

private:
	IronFlame0x944 m_unk0x04;             // 0x04
	AmberWolf0x98 m_unk0x948;             // 0x948
	CobaltMist0x30 m_unk0x9e0;            // 0x9e0
	undefined m_unk0xa10[0xa14 - 0xa10];  // 0xa10
	LegoU32 m_golBackendType;             // 0xa14
	undefined m_unk0xa18[0x1d6c - 0xa18]; // 0xa18
};

#endif // NEONCACTUS0X1D6C_H

#ifndef NEONCACTUS0X1D6C_H
#define NEONCACTUS0X1D6C_H

#include "cactusinterface0x4.h"
#include "cobaltmist0x30.h"
#include "decomp.h"
#include "ironflame0x944.h"
#include "soundmanager.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b0568
// SIZE 0x1d6c
class NeonCactus0x1d6c : public CactusInterface0x4 {
public:
	enum {
		c_videoFullScreen = 0x08,
		c_videoPrimaryDriver = 0x80,
		c_videoSelect3D = 0x200,
		c_videoAlphaTrans = 0x8000,
	};

	virtual ~NeonCactus0x1d6c(); // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0042bb20
	// NeonCactus0x1d6c::`scalar deleting destructor'

	LegoS32 Init(LegoS32 p_argc, LegoChar** p_argv);
	void Shutdown();
	void FUN_0042bc40();
	void FUN_0042bd00();
	void FUN_0042be90();
	LegoS32 ParseArguments(LegoS32 p_argc, LegoChar** p_argv);
	void ShowUsage();

private:
	IronFlame0x944 m_unk0x04;             // 0x04
	SoundManager m_soundManager;          // 0x948
	CobaltMist0x30 m_unk0x9e0;            // 0x9e0
	undefined m_unk0xa10[0xa14 - 0xa10];  // 0xa10
	LegoU32 m_golBackendType;             // 0xa14
	LegoBool32 m_cutscenes;               // 0xa18
	undefined m_unk0xa1c[0xab8 - 0xa1c];  // 0xa1c
	LegoU32 m_videoFlags;                 // 0xab8
	undefined m_unk0xabc[0x1d6c - 0xabc]; // 0xabc
};

#endif // NEONCACTUS0X1D6C_H

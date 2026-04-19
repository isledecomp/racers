#ifndef LEGORACERS_H
#define LEGORACERS_H

#include "cactusinterface0x4.h"
#include "cobaltmist0x30.h"
#include "decomp.h"
#include "ironflame0x944.h"
#include "soundmanager.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b0568
// SIZE 0x1d6c
class LegoRacers : public CactusInterface0x4 {
public:
	enum {
		c_videoFullScreen = 0x08,
		c_videoPrimaryDriver = 0x80,
		c_videoSelect3D = 0x200,
		c_videoAlphaTrans = 0x8000,
	};

	virtual ~LegoRacers(); // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0042bb20
	// LegoRacers::`scalar deleting destructor'

	LegoS32 Init(LegoS32 p_argc, LegoChar** p_argv);
	void Destroy();
	void Run();
	void FUN_0042bd00();
	void FUN_0042bdc0();
	void FUN_0042bde0();
	void FUN_0042be00();
	void Shutdown();
	LegoS32 ParseArguments(LegoS32 p_argc, LegoChar** p_argv);
	void ShowUsage();
	LONG ResetDisplay();

private:
	IronFlame0x944 m_unk0x04;             // 0x04
	SoundManager m_soundManager;          // 0x948
	CobaltMist0x30 m_unk0x9e0;            // 0x9e0
	undefined m_unk0xa10[0xa14 - 0xa10];  // 0xa10
	LegoU32 m_golBackendType;             // 0xa14
	LegoBool32 m_cutscenes;               // 0xa18
	undefined m_unk0xa1c[0xab8 - 0xa1c];  // 0xa1c
	LegoU32 m_videoFlags;                 // 0xab8
	undefined4 m_unk0xabc;                // 0xabc
	undefined m_unk0xac0[0x1d6c - 0xac0]; // 0xac0
};

#endif // LEGORACERS_H

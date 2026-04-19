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

	LegoRacers();
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
	IndigoStar0x18* m_unk0xa10;           // 0xa10
	LegoU32 m_golBackendType;             // 0xa14
	LegoBool32 m_cutscenes;               // 0xa18
	undefined4 m_unk0xa1c;                // 0xa1c
	undefined m_unk0xa20[0xab4 - 0xa20];  // 0xa20
	undefined4 m_bpp;                     // 0xab4
	LegoU32 m_videoFlags;                 // 0xab8
	LegoBool32 m_unk0xabc;                // 0xabc
	IronFlame0x944* m_unk0xac0;           // 0xac0
	IndigoStar0x18* m_unk0xac4;           // 0xac4
	LegoFloat m_unk0xac8;                 // 0xac8
	LegoFloat m_unk0xacc;                 // 0xacc
	LegoFloat m_unk0xad0;                 // 0xad0
	undefined4 m_unk0xad4;                // 0xad4
	LegoU16 m_unk0xad8;                   // 0xad8
	undefined m_unk0xada[0xae0 - 0xada];  // 0xada
	undefined4 m_unk0xae0;                // 0xae0
	undefined m_unk0xae4[0xae9 - 0xae4];  // 0xae4
	LegoChar m_unk0xae9[8];               // 0xae9
	undefined m_unk0xaf1[0xaf4 - 0xaf1];  // 0xaf1
	undefined4 m_unk0xaf4;                // 0xaf4
	undefined m_unk0xaf8[0xafc - 0xaf8];  // 0xaf8
	LegoChar m_unk0xafc[8];               // 0xafc
	LegoChar m_unk0xb04[8];               // 0xb04
	undefined m_unk0xb0c[0xde8 - 0xb0c];  // 0xb0c
	undefined4 m_unk0xde8;                // 0xde8
	undefined m_unk0xdec[0xe54 - 0xdec];  // 0xdec
	undefined4 m_unk0xe54;                // 0xe54
	undefined m_unk0xe58[0x1d6c - 0xe58]; // 0xe58
};

#endif // LEGORACERS_H

#ifndef LEGORACERS_H
#define LEGORACERS_H

#include "audio/directsoundmanager.h"
#include "audio/nullsoundmanager.h"
#include "cactusinterface0x4.h"
#include "decomp.h"
#include "scarletnova0x5c.h"
#include "types.h"
#include "win32golapp.h"

// VTABLE: LEGORACERS 0x004b0568
// SIZE 0x1d6c
class LegoRacers : public CactusInterface0x4 {
public:
	// SIZE 0x12b0
	class Context {
	public:
		enum {
			c_flagBit1 = 1 << 1,
			c_flagBit3 = 1 << 3,
			c_flagBit7 = 1 << 7,
		};

		LegoBool32 m_unk0x00;                 // 0x00
		Win32GolApp* m_golApp;                // 0x04
		SoundManager* m_unk0x08;              // 0x08
		LegoFloat m_unk0x0c;                  // 0x0c
		LegoFloat m_unk0x10;                  // 0x10
		LegoFloat m_unk0x14;                  // 0x14
		undefined4 m_unk0x18;                 // 0x18
		LegoU16 m_unk0x1c;                    // 0x1c
		undefined m_unk0x1e;                  // 0x1e
		undefined m_unk0x1f;                  // 0x1f
		undefined m_unk0x20[0x24 - 0x20];     // 0x20
		undefined4 m_unk0x24;                 // 0x24
		undefined m_unk0x28[0x2d - 0x28];     // 0x28
		LegoChar m_unk0x2d[8];                // 0x2d
		undefined m_unk0x35[0x38 - 0x35];     // 0x35
		undefined4 m_unk0x38;                 // 0x38
		undefined4 m_unk0x3c;                 // 0x3c
		LegoChar m_unk0x40[8];                // 0x40
		LegoChar m_raceName[8];               // 0x48
		undefined m_unk0x50[0xd8 - 0x50];     // 0x50
		undefined4 m_unk0xd8;                 // 0xd8
		LegoChar m_gameDataDirectory[18];     // 0xdc
		LegoChar m_commonDataDirectory[26];   // 0xee
		ScarletNova0x5c m_unk0x108[5];        // 0x108
		undefined m_unk0x2d4[0x32c - 0x2d4];  // 0x2d4
		undefined4 m_unk0x32c;                // 0x32c
		undefined m_unk0x330[0x398 - 0x330];  // 0x330
		undefined4 m_unk0x398;                // 0x398
		undefined m_unk0x39c[0x12b0 - 0x39c]; // 0x39c
	};

	enum {
		c_videoFullScreen = 0x08,
		c_videoBit4 = 0x10,
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
	Win32GolApp m_golApp;                    // 0x04
	DirectSoundManager m_directSoundManager; // 0x948
	NullSoundManager m_nullSoundManager;     // 0x9e0
	SoundManager* m_soundManager;            // 0xa10
	LegoU32 m_golBackendType;                // 0xa14
	LegoBool32 m_cutscenes;                  // 0xa18
	undefined4 m_unk0xa1c;                   // 0xa1c
	undefined m_unk0xa20[0xab4 - 0xa20];     // 0xa20
	undefined4 m_bpp;                        // 0xab4
	LegoU32 m_videoFlags;                    // 0xab8
	Context m_context;                       // 0xabc
};

#endif // LEGORACERS_H

#ifndef LEGORACERS_H
#define LEGORACERS_H

#include "app/win32golapp.h"
#include "audio/directsoundmanager.h"
#include "audio/nullsoundmanager.h"
#include "decomp.h"
#include "golname.h"
#include "racer/drivercosmetics.h"
#include "save/savegame.h"
#include "types.h"
#include "util/cactusinterface0x4.h"

class GolMaterialLibrary;
class GolModelBase;
class GolTextureList;

// VTABLE: LEGORACERS 0x004b0568
// SIZE 0x1d6c
class LegoRacers : public CactusInterface0x4 {
public:
	// SIZE 0x18
	struct RaceSlot {
		undefined4 m_enabled; // 0x00
		undefined4 m_mirror;  // 0x04
		GolName m_raceName;   // 0x08
		GolName m_folderName; // 0x10
	};

#pragma pack(push, 1)
	// SIZE 0x12b0
	class Context {
	public:
		// SIZE 0x5c
		struct PlayerSetupSlot {
			GolName m_driverName;               // 0x00
			GolName m_chassisName;              // 0x08
			undefined4 m_unk0x10;               // 0x10
			LegoFloat m_unk0x14;                // 0x14
			LegoFloat m_unk0x18;                // 0x18
			LegoFloat m_unk0x1c;                // 0x1c
			LegoFloat m_unk0x20;                // 0x20
			GolModelBase* m_model;              // 0x24
			GolMaterialLibrary* m_materials;    // 0x28
			GolTextureList* m_textures;         // 0x2c
			LegoChar m_playerName[14];          // 0x30
			undefined m_unk0x3e[0x48 - 0x3e];   // 0x3e
			GolModelBase* m_altModel;           // 0x48
			GolMaterialLibrary* m_altMaterials; // 0x4c
			GolTextureList* m_altTextures;      // 0x50
			DriverCosmetics m_cosmetics;        // 0x54
			LegoU8 m_previewFaceIndex;          // 0x59
			undefined m_unk0x5a[0x5c - 0x5a];   // 0x5a
		};

		// SIZE 0x0c
		struct PlayerRecordState {
			undefined4 m_unk0x00; // 0x00
			undefined4 m_unk0x04; // 0x04
			undefined4 m_unk0x08; // 0x08
		};

		enum {
			c_flagRecordBeaten = 1 << 0,
			c_flagReturnToGarage = 1 << 1,
			c_flagBit2 = 1 << 2,
			c_flagAbortRace = 1 << 3,
			c_flagBestTimesPending = 1 << 4,
			c_flagRestartCircuit = 1 << 5,
			c_flagFirstRace = 1 << 6,
			c_flagBit7 = 1 << 7,

			c_playerSetupSlotCount = 6,
			c_playerRecordStateCount = 2,
			c_inputBindingEntryCount = 2,
		};

		enum {
			c_raceModeCircuit = 0,
			c_raceModeSingle = 1,
			c_raceModeTimeRace = 2,
		};

		LegoBool32 m_running;                                             // 0x00
		Win32GolApp* m_golApp;                                            // 0x04
		SoundManager* m_soundManager;                                     // 0x08
		LegoFloat m_unk0x0c;                                              // 0x0c
		LegoFloat m_unk0x10;                                              // 0x10
		LegoFloat m_unk0x14;                                              // 0x14
		undefined4 m_unk0x18;                                             // 0x18
		LegoU16 m_nextMenuId;                                             // 0x1c
		LegoU8 m_unk0x1e;                                                 // 0x1e
		undefined m_unk0x1f;                                              // 0x1f
		LegoU32 m_unk0x20;                                                // 0x20
		undefined4 m_raceMode;                                            // 0x24
		LegoU32 m_languageIndex;                                          // 0x28
		undefined m_unk0x2c;                                              // 0x2c
		GolName m_circuitName;                                            // 0x2d
		undefined m_unk0x35[0x38 - 0x35];                                 // 0x35
		RaceSlot m_raceSlots[4];                                          // 0x38
		LegoU32 m_bestLapTimes[4];                                        // 0x98
		LegoU32 m_bestLapHolders[4];                                      // 0xa8
		LegoU32 m_bestRaceTimes[4];                                       // 0xb8
		LegoU32 m_bestRaceHolders[4];                                     // 0xc8
		LegoU32 m_currentRaceIndex;                                       // 0xd8
		LegoChar m_gameDataDirectory[18];                                 // 0xdc
		LegoChar m_commonDataDirectory[18];                               // 0xee
		undefined4 m_racerCount;                                          // 0x100
		PlayerSetupSlot m_playerSetupSlots[c_playerSetupSlotCount];       // 0x104
		undefined4 m_playerCount;                                         // 0x32c
		PlayerRecordState m_playerRecordStates[c_playerRecordStateCount]; // 0x330
		InputBindingEntry m_inputBindings[c_inputBindingEntryCount];      // 0x348
		undefined4 m_unk0x398;                                            // 0x398
		LegoU32 m_saveRecordCount;                                        // 0x39c
		SaveRecordData m_saveRecords[5];                                  // 0x3a0
		PersistentGameState m_saveState;                                  // 0xe81
		undefined m_unk0x12ad[0x12b0 - 0x12ad];                           // 0x12ad

		SoundManager* GetSoundManager() { return m_soundManager; }
		LegoFloat GetUnk0x0c() const { return m_unk0x0c; }
		LegoFloat GetUnk0x10() const { return m_unk0x10; }
		LegoFloat GetUnk0x14() const { return m_unk0x14; }
	};
#pragma pack(pop)

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

	LegoS32 Initialize(LegoS32 p_argc, LegoChar** p_argv);
	void Destroy();
	void Run();
	void ReleaseContextAssets();
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

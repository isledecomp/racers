#ifndef TIMERACEMANAGER_H
#define TIMERACEMANAGER_H

#include "compat.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golmodelentity.h"
#include "race/racestate.h"
#include "render/gold3drenderdevice.h"
#include "types.h"

class GolExport;
class GolWorldDatabase;

// VTABLE: LEGORACERS 0x004b01a0
// SIZE 0x3b8
class TimeRaceManager {
public:
	TimeRaceManager();
	virtual ~TimeRaceManager(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x00422390
	// TimeRaceManager::`scalar deleting destructor'

	void Reset();
	void Initialize(GolD3DRenderDevice* p_renderer, GolExport* p_golExport, undefined4 p_unk0x0c, undefined4 p_mirror);
	void Shutdown();
	void UpdateBestRun();
	LegoBool32 HasBeatenRecord();
	LegoU32* GetScratchLapTimes() { return m_scratchLapTimes; }

private:
	enum {
		c_flag0x3b4Bit0 = 1 << 0,
		c_flag0x3b4Bit3 = 1 << 3,
		c_flag0x3b4Bit4 = 1 << 4,
	};

	GolWorldDatabase* m_worldDatabase;   // 0x04
	GolExport* m_golExport;              // 0x08
	LegoU32* m_recordLapTimes;           // 0x0c
	LegoU32* m_bestLapTimes;             // 0x10
	LegoU32* m_scratchLapTimes;          // 0x14
	RaceState::Racer* m_racer;           // 0x18
	GolAnimatedEntity m_unk0x1c;         // 0x1c
	undefined m_unk0x110[0x114 - 0x110]; // 0x110
	GolAnimatedEntity m_unk0x114;        // 0x114
	undefined m_unk0x208[0x20c - 0x208]; // 0x208
	GolAnimatedEntity m_unk0x20c;        // 0x20c
	GolModelEntity m_unk0x300;           // 0x300
	GolSceneNode* m_nodes[3];            // 0x390
	LegoS32 m_partIndices[3];            // 0x39c
	CmbModelPart0x34* m_modelParts[3];   // 0x3a8
	LegoU8 m_flags0x3b4;                 // 0x3b4
};

#endif // TIMERACEMANAGER_H

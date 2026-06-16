#ifndef TIMERACEMANAGER_H
#define TIMERACEMANAGER_H

#include "compat.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golmodelentity.h"
#include "goltxtparser.h"
#include "race/racestate.h"
#include "render/gold3drenderdevice.h"
#include "types.h"

class GolExport;
class GolWorldDatabase;

// VTABLE: LEGORACERS 0x004b01a0
// SIZE 0x3b8
class TimeRaceManager {
public:
	// VTABLE: LEGORACERS 0x004b01ac
	// SIZE 0x1fc
	class GhbTxtParser : public GolTxtParser {
		// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
		// TimeRaceManager::GhbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
		// TimeRaceManager::GhbTxtParser::~GhbTxtParser
	};

	class GhostRunData;

	TimeRaceManager();
	virtual ~TimeRaceManager(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x00422390
	// TimeRaceManager::`scalar deleting destructor'

	void Reset();
	void Initialize(GolD3DRenderDevice* p_renderer, GolExport* p_golExport, LegoBool32 p_binary, LegoBool32 p_mirror);
	void Shutdown();
	void FUN_00422710(LegoU32 p_elapsedMs);
	void FUN_00422960(GolD3DRenderDevice* p_renderer);
	void FUN_00422de0();
	void FUN_00422eb0(RaceState::Racer* p_racer);
	void UpdateBestRun();
	LegoBool32 HasBeatenRecord();
	GhostRunData* FUN_004234f0();
	LegoU32* GetScratchLapTimes() { return m_scratchRun->m_lapTimes; }

	// SIZE 0x25c0
	class GhostRunData {
	public:
		// SIZE 0x0a
		class Sample {
		public:
			LegoS16 m_positionX; // 0x00
			LegoS16 m_positionY; // 0x02
			LegoS16 m_positionZ; // 0x04
			LegoS8 m_rotationX;  // 0x06
			LegoS8 m_rotationY;  // 0x07
			LegoS8 m_rotationZ;  // 0x08
			LegoS8 m_rotationW;  // 0x09
		};

		enum {
			c_sampleCapacity = 0x3c1,
		};

		LegoU32 m_lapTimes[3];              // 0x0000
		Sample m_samples[c_sampleCapacity]; // 0x000c
		undefined2 m_unk0x2596;             // 0x2596
		LegoU32 m_sampleCount;              // 0x2598
		LegoU32 m_unk0x259c;                // 0x259c
		GolVec3 m_initialPosition;          // 0x25a0
		GolQuat m_initialRotation;          // 0x25ac
		LegoU32 m_finished;                 // 0x25bc
	};

private:
	enum {
		c_flag0x3b4Bit0 = 1 << 0,
		c_flag0x3b4Bit1 = 1 << 1,
		c_flag0x3b4Bit2 = 1 << 2,
		c_flag0x3b4Bit3 = 1 << 3,
		c_flag0x3b4Bit4 = 1 << 4,
		c_flag0x3b4Bit5 = 1 << 5,
		c_lapCount = 3,
		c_ghostSampleIntervalMs = 250,
		c_ghostRaceDurationLimitMs = 240000,
		c_ghostFileNameLimit = 8,
		c_ghostFileSuffixLimit = 4,
		c_ghostFileNameBufferSize = 16,
		c_ghostPathToken = GolFileParser::e_unknown0x2c,
		c_ghostPathNodesToken = GolFileParser::e_unknown0x27,
		c_ghostPathPositionToken = GolFileParser::e_unknown0x28,
		c_ghostPathRotationToken = GolFileParser::e_unknown0x29,
		c_ghostPathLapTimesToken = GolFileParser::e_unknown0x2a,
		c_ghostPathUnknownToken = GolFileParser::e_unknown0x2b,
	};

	void FUN_00423160(GhostRunData* p_ghostRun, const LegoChar* p_name);

	GolWorldDatabase* m_worldDatabase; // 0x04
	GolExport* m_golExport;            // 0x08
	GhostRunData* m_recordRun;         // 0x0c
	GhostRunData* m_bestRun;           // 0x10
	GhostRunData* m_scratchRun;        // 0x14
	RaceState::Racer* m_racer;         // 0x18
	GolAnimatedEntity m_unk0x1c;       // 0x1c
	GolAnimatedEntity* m_unk0x110;     // 0x110
	GolAnimatedEntity m_unk0x114;      // 0x114
	GolAnimatedEntity* m_unk0x208;     // 0x208
	GolAnimatedEntity m_unk0x20c;      // 0x20c
	GolModelEntity m_unk0x300;         // 0x300
	GolModelEntity* m_unk0x390;        // 0x390
	GolVec3 m_unk0x394;                // 0x394
	GolVec3 m_unk0x3a0;                // 0x3a0
	LegoU32 m_unk0x3ac;                // 0x3ac
	LegoU32 m_unk0x3b0;                // 0x3b0
	LegoU8 m_flags0x3b4;               // 0x3b4
};

#endif // TIMERACEMANAGER_H

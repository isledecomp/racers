#ifndef RACECAMERACONTROLLER_H
#define RACECAMERACONTROLLER_H

#include "decomp.h"
#include "golmath.h"
#include "race/racestate.h"
#include "types.h"

class GolCamera;
class GolD3DRenderDevice;
struct SoundNode;

// SIZE 0x150
class RaceCameraController {
public:
	// SIZE 0x18
	struct Profile {
		LegoFloat GetUnk0x0c() const { return m_unk0x0c; }

		LegoU8 m_unk0x00;       // 0x00
		undefined m_unk0x01[3]; // 0x01
		LegoFloat m_unk0x04;    // 0x04
		LegoFloat m_unk0x08;    // 0x08
		LegoFloat m_unk0x0c;    // 0x0c
		LegoFloat m_unk0x10;    // 0x10
		LegoFloat m_unk0x14;    // 0x14
	};

	RaceCameraController();
	void Reset();
	void FUN_00428210(GolCamera* p_camera, GolD3DRenderDevice* p_renderer);
	void FUN_00428230(RaceState::Racer* p_unk0x04);

	void FUN_00427b70(LegoFloat p_unk0x04);
	void FUN_00427b90(LegoFloat p_unk0x04);
	void FUN_00427bb0(LegoFloat p_unk0x04);
	void FUN_00427be0(LegoFloat p_unk0x04);
	void FUN_004282a0(GolVec3* p_unk0x04, GolVec3* p_unk0x08);
	static void FUN_004282d0(GolVec3* p_unk0x04, GolVec3* p_unk0x08, GolMatrix3* p_unk0x0c);
	void FUN_00428390(GolVec3* p_unk0x04);
	void FUN_004283d0(LegoU8 p_unk0x04);
	void FUN_004283f0(LegoS32 p_unk0x04, LegoBool32 p_unk0x08);
	GolVec3* FUN_00428500(GolVec3* p_unk0x04);
	void FUN_00428540(LegoFloat p_unk0x04);

private:
	void FUN_00427c00();
	void FUN_00427d30();
	void FUN_00427e80();
	void FUN_004280a0();
	static LegoFloat FUN_00428f40(LegoFloat p_unk0x04, LegoFloat p_unk0x08);

public:
	LegoU8 m_unk0x000;                   // 0x000
	LegoU8 m_unk0x001;                   // 0x001
	LegoU8 m_unk0x002;                   // 0x002
	undefined m_unk0x003;                // 0x003
	LegoU8 m_unk0x004;                   // 0x004
	LegoU8 m_unk0x005;                   // 0x005
	undefined m_unk0x006[0x008 - 0x006]; // 0x006
	GolMatrix34 m_unk0x008;              // 0x008
	GolQuat m_unk0x038;                  // 0x038
	GolMatrix34 m_unk0x048;              // 0x048
	GolQuat m_unk0x078;                  // 0x078
	GolMatrix34 m_unk0x088;              // 0x088
	GolQuat m_unk0x0b8;                  // 0x0b8
	LegoFloat m_unk0x0c8;                // 0x0c8
	LegoFloat m_unk0x0cc;                // 0x0cc
	LegoS32 m_unk0x0d0;                  // 0x0d0
	RaceState::Racer* m_unk0x0d4;        // 0x0d4
	GolVec3 m_unk0x0d8;                  // 0x0d8
	GolVec3 m_unk0x0e4;                  // 0x0e4
	LegoFloat m_unk0x0f0;                // 0x0f0
	LegoFloat m_unk0x0f4;                // 0x0f4
	LegoFloat m_unk0x0f8;                // 0x0f8
	LegoFloat m_unk0x0fc;                // 0x0fc
	LegoFloat m_unk0x100;                // 0x100
	LegoFloat m_unk0x104;                // 0x104
	LegoFloat m_unk0x108;                // 0x108
	LegoFloat m_unk0x10c;                // 0x10c
	LegoFloat m_unk0x110;                // 0x110
	LegoFloat m_unk0x114;                // 0x114
	LegoFloat m_unk0x118;                // 0x118
	LegoU32 m_unk0x11c;                  // 0x11c
	LegoFloat m_unk0x120;                // 0x120
	LegoFloat m_unk0x124;                // 0x124
	LegoFloat m_unk0x128;                // 0x128
	LegoFloat m_unk0x12c;                // 0x12c
	LegoFloat m_unk0x130;                // 0x130
	LegoFloat m_unk0x134;                // 0x134
	LegoFloat m_unk0x138;                // 0x138
	LegoFloat m_unk0x13c;                // 0x13c
	LegoU32 m_unk0x140;                  // 0x140
	GolD3DRenderDevice* m_renderer;      // 0x144
	GolCamera* m_camera;                 // 0x148
	SoundNode* m_unk0x14c;               // 0x14c
};

#endif // RACECAMERACONTROLLER_H

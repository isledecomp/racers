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
	void Initialize(GolCamera* p_camera, GolD3DRenderDevice* p_renderer);
	void SetRacer(RaceState::Racer* p_unk0x04);

	void SetPositionLag(LegoFloat p_unk0x04);
	void SetRotationLag(LegoFloat p_unk0x04);
	void SetPitchAngle(LegoFloat p_unk0x04);
	void SetHeightAngle(LegoFloat p_unk0x04);
	void SetOrientation(GolVec3* p_unk0x04, GolVec3* p_unk0x08);
	static void BuildOrientation(GolVec3* p_unk0x04, GolVec3* p_unk0x08, GolMatrix3* p_unk0x0c);
	void SnapPosition(GolVec3* p_unk0x04);
	void SetMode(LegoU8 p_unk0x04);
	void SetView(LegoS32 p_unk0x04, LegoBool32 p_unk0x08);
	GolVec3* GetViewDirection(GolVec3* p_unk0x04);
	void Update(LegoFloat p_unk0x04);

private:
	void UpdateListener();
	void UpdateFollow();
	void UpdateShake();
	void ApplySmoothing();
	static LegoFloat LerpAngle(LegoFloat p_unk0x04, LegoFloat p_unk0x08);

public:
	LegoU8 m_dirty;                      // 0x000
	LegoU8 m_unk0x001;                   // 0x001
	LegoU8 m_mode;                       // 0x002
	undefined m_unk0x003;                // 0x003
	LegoU8 m_lookBack;                   // 0x004
	LegoU8 m_alternate;                  // 0x005
	undefined m_unk0x006[0x008 - 0x006]; // 0x006
	GolMatrix34 m_rawTransform;          // 0x008
	GolQuat m_rawRotation;               // 0x038
	GolMatrix34 m_smoothedTransform;     // 0x048
	GolQuat m_smoothedRotation;          // 0x078
	GolMatrix34 m_previousTransform;     // 0x088
	GolQuat m_previousRotation;          // 0x0b8
	LegoFloat m_unk0x0c8;                // 0x0c8
	LegoFloat m_elapsed;                 // 0x0cc
	LegoS32 m_elapsedMs;                 // 0x0d0
	RaceState::Racer* m_racer;           // 0x0d4
	GolVec3 m_unk0x0d8;                  // 0x0d8
	GolVec3 m_lastRacerPosition;         // 0x0e4
	LegoFloat m_unk0x0f0;                // 0x0f0
	LegoFloat m_unk0x0f4;                // 0x0f4
	LegoFloat m_positionLag;             // 0x0f8
	LegoFloat m_rotationLag;             // 0x0fc
	LegoFloat m_unk0x100;                // 0x100
	LegoFloat m_unk0x104;                // 0x104
	LegoFloat m_unk0x108;                // 0x108
	LegoFloat m_heightSine;              // 0x10c
	LegoFloat m_pitchSine;               // 0x110
	LegoFloat m_pitchCosine;             // 0x114
	LegoFloat m_followDistance;          // 0x118
	LegoU32 m_unk0x11c;                  // 0x11c
	LegoFloat m_unk0x120;                // 0x120
	LegoFloat m_blendHeightSine;         // 0x124
	LegoFloat m_blendPitchSine;          // 0x128
	LegoFloat m_blendPitchCosine;        // 0x12c
	LegoFloat m_blendFollowDistance;     // 0x130
	LegoFloat m_targetFov;               // 0x134
	LegoFloat m_unk0x138;                // 0x138
	LegoFloat m_shakeAmount;             // 0x13c
	LegoU32 m_shakeMs;                   // 0x140
	GolD3DRenderDevice* m_renderer;      // 0x144
	GolCamera* m_camera;                 // 0x148
	SoundNode* m_listenerNode;           // 0x14c
};

#endif // RACECAMERACONTROLLER_H

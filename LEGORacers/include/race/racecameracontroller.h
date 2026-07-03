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
	enum {
		c_modeChase = 1,
		c_modeCockpit = 2,
		c_modeFinish = 3,
	};

	// SIZE 0x18
	struct Profile {
		LegoFloat GetFollowDistance() const { return m_followDistance; }

		LegoU8 m_mode;              // 0x00
		LegoFloat m_pitchAngle;     // 0x04
		LegoFloat m_heightAngle;    // 0x08
		LegoFloat m_followDistance; // 0x0c
		LegoFloat m_positionLag;    // 0x10
		LegoFloat m_rotationLag;    // 0x14
	};

	RaceCameraController();
	void Reset();
	void Initialize(GolCamera* p_camera, GolD3DRenderDevice* p_renderer);
	void SetRacer(Racer* p_racer);

	void SetPositionLag(LegoFloat p_amount);
	void SetRotationLag(LegoFloat p_amount);
	void SetPitchAngle(LegoFloat p_degrees);
	void SetHeightAngle(LegoFloat p_degrees);
	void SetOrientation(GolVec3* p_direction, GolVec3* p_up);
	static void BuildOrientation(GolVec3* p_direction, GolVec3* p_up, GolMatrix3* p_dest);
	void SnapPosition(GolVec3* p_position);
	void SetMode(LegoU8 p_mode);
	void SetView(LegoS32 p_viewIndex, LegoBool32 p_alternate);
	GolVec3* GetViewDirection(GolVec3* p_dest);
	void Update(LegoFloat p_elapsedMs);

private:
	void UpdateListener();
	void UpdateFollow();
	void UpdateShake();
	void ApplySmoothing();
	static LegoFloat VectorToAngle(LegoFloat p_x, LegoFloat p_y);

public:
	LegoU8 m_dirty;                      // 0x000
	LegoU8 m_frameDirty;                 // 0x001
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
	LegoFloat m_transitionMs;            // 0x0c8
	LegoFloat m_elapsed;                 // 0x0cc
	LegoS32 m_elapsedMs;                 // 0x0d0
	Racer* m_racer;                      // 0x0d4
	GolVec3 m_viewDirection;             // 0x0d8
	GolVec3 m_lastRacerPosition;         // 0x0e4
	LegoFloat m_unk0x0f0;                // 0x0f0
	LegoFloat m_turnLeadAngle;           // 0x0f4
	LegoFloat m_positionLag;             // 0x0f8
	LegoFloat m_rotationLag;             // 0x0fc
	LegoFloat m_targetPositionRate;      // 0x100
	LegoFloat m_turnLeadRate;            // 0x104
	LegoFloat m_viewAngleRate;           // 0x108
	LegoFloat m_heightSine;              // 0x10c
	LegoFloat m_pitchSine;               // 0x110
	LegoFloat m_pitchCosine;             // 0x114
	LegoFloat m_followDistance;          // 0x118
	LegoU32 m_turboActive;               // 0x11c
	LegoFloat m_followDistanceScale;     // 0x120
	LegoFloat m_blendHeightSine;         // 0x124
	LegoFloat m_blendPitchSine;          // 0x128
	LegoFloat m_blendPitchCosine;        // 0x12c
	LegoFloat m_blendFollowDistance;     // 0x130
	LegoFloat m_targetFov;               // 0x134
	LegoFloat m_baseFov;                 // 0x138
	LegoFloat m_shakeAmount;             // 0x13c
	LegoU32 m_shakeMs;                   // 0x140
	GolD3DRenderDevice* m_renderer;      // 0x144
	GolCamera* m_camera;                 // 0x148
	SoundNode* m_listenerNode;           // 0x14c
};

#endif // RACECAMERACONTROLLER_H

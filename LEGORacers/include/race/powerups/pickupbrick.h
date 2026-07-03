#ifndef PICKUPBRICK_H
#define PICKUPBRICK_H

#include "golmath.h"
#include "golmodelentity.h"
#include "util/legoeventqueue.h"

class GolBoundedEntity;
class GolCollidableEntity;
class GolD3DRenderDevice;
class GolExport;
class RacePowerupManager;
class Racer;
class RacerSoundSource;
class RaceState;
class TriggerWorld;

// VTABLE: LEGORACERS 0x004b14b0
// SIZE 0x54
class PickupBrick : public LegoEventQueue::Callback {
public:
	void OnEvent(LegoEventQueue::CallbackData* p_data) override;  // vtable+0x00
	virtual void OnTouched(Racer* p_racer) = 0;                   // vtable+0x04
	virtual ~PickupBrick();                                       // vtable+0x08
	virtual void Respawn();                                       // vtable+0x0c
	virtual void Draw(GolD3DRenderDevice* p_renderer);            // vtable+0x10
	virtual void DrawTransparent(GolD3DRenderDevice* p_renderer); // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x00453940
	// PickupBrick::`scalar deleting destructor'

	PickupBrick();
	void Initialize(
		RacePowerupManager* p_owner,
		RacerSoundSource* p_soundResource,
		GolVec3* p_position,
		GolModelEntity* p_model0,
		GolModelEntity* p_model1
	);
	void Destroy();
	LegoS32 Reset();

	void SetAudible() { m_flags |= c_flagAudible; }
	void ClearAudible() { m_flags &= ~c_flagAudible; }
	void ClearVelocityX() { m_worldEntity.ClearVelocityX(); }
	GolWorldEntity* GetWorldEntity() { return &m_worldEntity; }

protected:
	enum {
		c_stateIdle = 0,
		c_stateWait = 1,
		c_stateActive = 2,
		c_stateTransition = 3,
		c_stateInactive = 4,

		c_flagAudible = 1 << 0,
		c_flagTouched = 1 << 1,
		c_flagWasTouched = 1 << 2,
		c_flagDropped = 1 << 0,
		c_flagReturnHome = 1 << 1,
		c_flagGhost = 1 << 4,
	};

	void Update(LegoU32 p_elapsedMs);
	void SetTouchable(LegoBool32 p_touchable);

	RacePowerupManager* m_manager;    // 0x04
	GolWorldEntity m_worldEntity;     // 0x08
	LegoFloat m_scale;                // 0x30
	GolModelEntity* m_model;          // 0x34
	GolModelEntity* m_blendModel;     // 0x38
	LegoU32 m_state;                  // 0x3c
	LegoU32 m_nextState;              // 0x40
	RacerSoundSource* m_soundSource;  // 0x44
	LegoU32 m_respawnMs;              // 0x48
	LegoU32 m_stateTimerMs;           // 0x4c
	LegoU8 m_flags;                   // 0x50
	undefined m_unk0x51[0x54 - 0x51]; // 0x51
};

#endif // PICKUPBRICK_H

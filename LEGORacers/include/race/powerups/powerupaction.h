#ifndef POWERUPACTION_H
#define POWERUPACTION_H

#include "compat.h"
#include "race/powerups/actionsetup.h"
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

// VTABLE: LEGORACERS 0x004b132c
// SIZE 0x18
class PowerupAction : public LegoEventQueue::Callback {
public:
	// Brick color codes (PWB color tokens map to these; GetBrickColor returns them)
	enum {
		c_brickColorRed = 1,
		c_brickColorBlue = 2,
		c_brickColorGreen = 3,
		c_brickColorYellow = 4,
	};

	PowerupAction();
	void OnEvent(LegoEventQueue::CallbackData* p_param) override; // vtable+0x00
	virtual ~PowerupAction();                                     // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00451370
	// PowerupAction::`scalar deleting destructor'

	virtual void Update(LegoU32 p_elapsedMs);          // vtable+0x08
	virtual void Draw(GolD3DRenderDevice*);            // vtable+0x0c
	virtual void DrawTransparent(GolD3DRenderDevice*); // vtable+0x10
	virtual void AdvanceState() = 0;                   // vtable+0x14
	virtual LegoS32 GetBrickColor() = 0;               // vtable+0x18
	virtual void Deactivate();                         // vtable+0x1c

	PowerupAction* GetNext() { return m_next; }
	LegoS32 GetState() const { return m_state; }
	LegoU32 GetStateTimerMs() const { return m_stateTimerMs; }
	LegoU32 GetLevel() const { return m_level; }
	void SetState(LegoS32 p_state) { m_state = p_state; }
	void SetSoundSource(RacerSoundSource* p_soundSource) { m_soundSource = p_soundSource; }
	void SetNext(PowerupAction* p_next) { m_next = p_next; }
	void SetLevel(LegoU32 p_level) { m_level = p_level; }

protected:
	friend class RacePowerupManager;

	LegoS32 m_state;                 // 0x004
	LegoU32 m_stateTimerMs;          // 0x008
	PowerupAction* m_next;           // 0x00c
	RacerSoundSource* m_soundSource; // 0x010
	LegoU32 m_level;                 // 0x014
};

#endif // POWERUPACTION_H

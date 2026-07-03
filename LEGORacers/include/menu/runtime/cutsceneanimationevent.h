#ifndef CUTSCENEANIMATIONEVENT_H
#define CUTSCENEANIMATIONEVENT_H

#include "golname.h"
#include "menu/runtime/cutsceneevent.h"
#include "menu/runtime/cutsceneparticleref.h"

class CutsceneAnimation;

// VTABLE: LEGORACERS 0x004b4a94
// SIZE 0x50
class CutsceneAnimationEvent : public CutsceneEvent {
public:
	// .ceb animation-event field tokens
	enum {
		e_position = 0x39,
		e_attached = 0x3a,
		e_joint = 0x3b,
		e_animationIndex = 0x3d,
		e_direction = 0x3e,
	};

	CutsceneAnimationEvent();

	void StartOnJointed(GolWorldEntity* p_arg) override;                               // vtable+0x04
	void StartOnBsp(GolWorldEntity* p_arg) override;                                   // vtable+0x0c
	void StartAt(const GolVec3* p_a, const GolVec3* p_b, const GolVec3* p_c) override; // vtable+0x10
	void Start() override;                                                             // vtable+0x14
	void Stop() override;                                                              // vtable+0x18

	void Reset();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner);
	void Spawn();
	void Update(LegoU32 p_elapsedMs);

	// SYNTHETIC: LEGORACERS 0x004a20e0 FOLDED
	// CutsceneAnimationEvent::~CutsceneAnimationEvent

	// SYNTHETIC: LEGORACERS 0x004a1f20
	// CutsceneAnimationEvent::`vector deleting destructor'

private:
	CutsceneAnimation* m_animation;     // 0x14
	CutsceneParticleRef* m_particleRef; // 0x18
	GolName m_emitterName;              // 0x1c
	GolVec3 m_position;                 // 0x24
	GolVec3 m_direction;                // 0x30
	GolVec3 m_up;                       // 0x3c
	LegoU32 m_flags;                    // 0x48
	LegoU32 m_jointIndex;               // 0x4c
};

#endif // CUTSCENEANIMATIONEVENT_H

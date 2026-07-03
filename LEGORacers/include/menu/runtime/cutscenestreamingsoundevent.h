#ifndef CUTSCENESTREAMINGSOUNDEVENT_H
#define CUTSCENESTREAMINGSOUNDEVENT_H

#include "menu/runtime/cutscenesoundevent.h"

class StreamingSoundInstance;

// VTABLE: LEGORACERS 0x004b4ad8
// SIZE 0x50
class CutsceneStreamingSoundEvent : public CutsceneSoundEvent {
public:
	enum Flags {
		c_flagHasPosition = 1 << 0,
		c_flagTrackEntity = 1 << 1,
		c_flagTrackJoint = 1 << 2,
		c_flagWasPlaying = 1 << 3,
	};

	// .ceb streaming-sound field tokens
	enum {
		e_minDistance = 0x37,
		e_maxDistance = 0x38,
		e_position = 0x39,
		e_positional = 0x3a,
		e_joint = 0x3b,
	};

	CutsceneStreamingSoundEvent();

	void StartOnJointed(GolWorldEntity* p_arg) override;                               // vtable+0x04
	void StartOnBsp(GolWorldEntity* p_arg) override;                                   // vtable+0x0c
	void StartAt(const GolVec3* p_a, const GolVec3* p_b, const GolVec3* p_c) override; // vtable+0x10
	void Start() override;                                                             // vtable+0x14
	void Stop() override;                                                              // vtable+0x18

	void Reset();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner);
	void Clear();
	void CreateInstance(const GolVec3* p_position);
	void Update();

private:
	StreamingSoundInstance* m_streamInstance; // 0x30
	LegoFloat m_minDistance;                  // 0x34
	LegoFloat m_maxDistance;                  // 0x38
	GolVec3 m_position;                       // 0x3c
	LegoU32 m_flags;                          // 0x48
	LegoU32 m_jointIndex;                     // 0x4c
};

#endif // CUTSCENESTREAMINGSOUNDEVENT_H

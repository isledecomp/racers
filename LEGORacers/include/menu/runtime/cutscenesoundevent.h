#ifndef CUTSCENESOUNDEVENT_H
#define CUTSCENESOUNDEVENT_H

#include "menu/runtime/cutsceneevent.h"

class SoundGroup;
class SoundInstance;

// VTABLE: LEGORACERS 0x004b4abc
// SIZE 0x30
class CutsceneSoundEvent : public CutsceneEvent {
public:
	// .ceb sound-event field tokens
	enum {
		e_soundIndex = 0x30,
		e_priority = 0x31,
		e_volume = 0x32,
		e_frequencyScale = 0x33,
		e_pan = 0x34,
		e_looping = 0x35,
	};

	CutsceneSoundEvent();

	void Start() override; // vtable+0x14
	void Stop() override;  // vtable+0x18

	void Reset();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner);
	LegoBool32 ParseToken(GolFileParser* p_parser, CutscenePlayer* p_owner, GolFileParser::ParserTokenType p_token);
	void Clear();
	void Update();

	// SYNTHETIC: LEGORACERS 0x004a1d60
	// CutsceneSoundEvent::`vector deleting destructor'

protected:
	SoundGroup* m_soundGroup;   // 0x14
	SoundInstance* m_instance;  // 0x18
	LegoFloat m_volume;         // 0x1c
	LegoU32 m_priority;         // 0x20
	LegoFloat m_frequencyScale; // 0x24
	LegoFloat m_pan;            // 0x28
	LegoU16 m_looping;          // 0x2c
	LegoU16 m_soundIndex;       // 0x2e
};

#endif // CUTSCENESOUNDEVENT_H

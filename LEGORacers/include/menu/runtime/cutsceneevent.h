#ifndef CUTSCENEEVENT_H
#define CUTSCENEEVENT_H

#include "golfileparser.h"
#include "golmath.h"
#include "types.h"

class CutscenePlayer;
class GolAnimatedEntity;
class GolWorldEntity;

// VTABLE: LEGORACERS 0x004b4954
// SIZE 0x14
class CutsceneEvent {
public:
	CutsceneEvent();
	virtual ~CutsceneEvent();                                             // vtable+0x00
	virtual void StartOnJointed(GolWorldEntity* p_arg);                   // vtable+0x04
	virtual void StartOnModel(GolWorldEntity* p_arg);                     // vtable+0x08
	virtual void StartOnBsp(GolWorldEntity* p_arg);                       // vtable+0x0c
	virtual void StartAt(const GolVec3*, const GolVec3*, const GolVec3*); // vtable+0x10
	virtual void Start();                                                 // vtable+0x14
	virtual void Stop();                                                  // vtable+0x18

	void Reset();
	void GetJointPosition(undefined4 p_param1, GolVec3* p_param2);
	void GetJointAxes(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3);
	void ParseCommonToken(GolFileParser* p_parser, CutscenePlayer* p_owner, GolFileParser::ParserTokenType p_token);
	void SetDisabled(LegoBool32 p_disabled) { m_disabled = p_disabled; }

	// SYNTHETIC: LEGORACERS 0x0049fd90
	// CutsceneEvent::`scalar deleting destructor'

protected:
	GolWorldEntity* m_parsedEntity;      // 0x04
	GolWorldEntity* m_entity;            // 0x08
	GolAnimatedEntity* m_animatedEntity; // 0x0c
	LegoBool32 m_disabled;               // 0x10
};

#endif // CUTSCENEEVENT_H

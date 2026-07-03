#ifndef CUTSCENECOLOREVENT_H
#define CUTSCENECOLOREVENT_H

#include "menu/runtime/cutsceneevent.h"

// VTABLE: LEGORACERS 0x004b4b34
// SIZE 0x48
class CutsceneColorEvent : public CutsceneEvent {
public:
	// .ceb color-event field tokens
	enum {
		e_shifts = 0x2c,
		e_offsets = 0x2d,
		e_offsetRates = 0x2e,
	};

	CutsceneColorEvent();

	void Start() override;                             // vtable+0x14
	void Stop() override;                              // vtable+0x18
	void StartOnModel(GolWorldEntity* p_arg) override; // vtable+0x08

	void Reset();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner);
	void Update(LegoFloat p_elapsedSeconds);
	void ApplyColorTransform();

	// SYNTHETIC: LEGORACERS 0x004a1ba0
	// CutsceneColorEvent::`vector deleting destructor'

private:
	LegoBool32 m_active;       // 0x14
	LegoS32 m_shiftRed;        // 0x18
	LegoS32 m_shiftGrn;        // 0x1c
	LegoS32 m_shiftBlu;        // 0x20
	LegoS32 m_offsetStartRed;  // 0x24
	LegoS32 m_offsetStartGrn;  // 0x28
	LegoS32 m_offsetStartBlu;  // 0x2c
	LegoFloat m_offsetRed;     // 0x30
	LegoFloat m_offsetGrn;     // 0x34
	LegoFloat m_offsetBlu;     // 0x38
	LegoFloat m_offsetRateRed; // 0x3c
	LegoFloat m_offsetRateGrn; // 0x40
	LegoFloat m_offsetRateBlu; // 0x44
};

#endif // CUTSCENECOLOREVENT_H

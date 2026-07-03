#ifndef CUTSCENEMENUANIMATIONEVENT_H
#define CUTSCENEMENUANIMATIONEVENT_H

#include "menu/menuanimationlist.h"
#include "menu/runtime/cutsceneevent.h"
#include "surface/color.h"

class GolD3DRenderDevice;
class GolMaterial;

// VTABLE: LEGORACERS 0x004b4b18
// SIZE 0x2c
class CutsceneMenuAnimationEvent : public CutsceneEvent {
public:
	// .ceb menu-animation field tokens
	enum {
		e_durationMs = 0x61,
		e_mode = 0x62,
		e_modeOn = 0x63,
		e_modeOff = 0x64,
		e_material = 0x65,
		e_color = 0x66,
	};

	CutsceneMenuAnimationEvent();

	void Start() override; // vtable+0x14
	void Stop() override;  // vtable+0x18

	void Reset();
	void Parse(
		GolFileParser* p_parser,
		CutscenePlayer* p_owner,
		MenuAnimationList* p_animationList,
		GolD3DRenderDevice* p_renderer
	);

	// SYNTHETIC: LEGORACERS 0x004a22b0
	// CutsceneMenuAnimationEvent::`vector deleting destructor'

private:
	MenuAnimationList* m_animationList;      // 0x14
	GolMaterial* m_material;                 // 0x18
	MenuAnimationList::Entry* m_activeEntry; // 0x1c
	union {
		ColorRGBA m_color;     // 0x20
		LegoU32 m_colorPacked; // 0x20
	};
	LegoU32 m_durationMs;             // 0x24
	LegoU8 m_mode;                    // 0x28
	undefined m_unk0x29[0x2c - 0x29]; // 0x29
};

#endif // CUTSCENEMENUANIMATIONEVENT_H

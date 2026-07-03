#ifndef CUTSCENETEXTVISUAL_H
#define CUTSCENETEXTVISUAL_H

#include "golstring.h"
#include "menu/runtime/cutscenevisual.h"

class GolFont;

// VTABLE: LEGORACERS 0x004b4af4
// SIZE 0x70
class CutsceneTextVisual : public CutsceneVisual {
public:
	CutsceneTextVisual();
	~CutsceneTextVisual() override; // vtable+0x00

	void GetContentSize(LegoS32* p_width, LegoS32* p_height) override; // vtable+0x1c
	void DrawContent(
		GolRenderDevice* p_renderer,
		LegoS32 p_x,
		LegoS32 p_y,
		undefined4,
		undefined4,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY
	) override; // vtable+0x20

	void Reset();
	void Clear();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner, GolRenderDevice* p_renderer);
	void RefreshString(CutscenePlayer* p_owner, GolRenderDevice* p_renderer);

	// SYNTHETIC: LEGORACERS 0x004a2480
	// CutsceneTextVisual::`vector deleting destructor'

private:
	GolString m_string;    // 0x58
	LegoChar* m_rawString; // 0x64
	GolFont* m_font;       // 0x68
	LegoU32 m_stringIndex; // 0x6c
};

#endif // CUTSCENETEXTVISUAL_H

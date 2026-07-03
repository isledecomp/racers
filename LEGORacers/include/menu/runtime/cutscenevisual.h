#ifndef CUTSCENEVISUAL_H
#define CUTSCENEVISUAL_H

#include "golname.h"
#include "menu/runtime/cutsceneevent.h"
#include "surface/color.h"

class GolD3DRenderDevice;
class GolRenderDevice;

// VTABLE: LEGORACERS 0x004b4a4c
// SIZE 0x58
class CutsceneVisual : public CutsceneEvent {
public:
	CutsceneVisual();
	~CutsceneVisual() override; // vtable+0x00

	void Start() override;                                                // vtable+0x14
	void Stop() override;                                                 // vtable+0x18
	virtual void GetContentSize(LegoS32* p_width, LegoS32* p_height) = 0; // vtable+0x1c
	virtual void DrawContent(
		GolRenderDevice* p_renderer,
		LegoS32 p_x,
		LegoS32 p_y,
		undefined4,
		undefined4,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY
	) = 0; // vtable+0x20

	void Reset();
	void Clear();
	void Update(LegoFloat p_elapsedSeconds);
	void Draw(GolD3DRenderDevice* p_renderer);
	void ComputeLayout(GolD3DRenderDevice* p_renderer, LegoFloat p_width, LegoFloat p_height);
	void ParseVisualToken(
		GolFileParser* p_parser,
		GolFileParser::ParserTokenType p_token,
		CutscenePlayer* p_owner,
		GolRenderDevice* p_renderer
	);

	// SYNTHETIC: LEGORACERS 0x004a32d0
	// CutsceneVisual::`scalar deleting destructor'

protected:
	enum Flags {
		c_flagCenterX = 1 << 0,
		c_flagCenterY = 1 << 1,
		c_flagPositionX = 1 << 2,
		c_flagPositionY = 1 << 3,
		c_flagWidth = 1 << 4,
		c_flagHeight = 1 << 5,
		c_flagActive = 1 << 6,
		c_flagLayoutPending = 1 << 7,
		c_flagHasColor = 1 << 8
	};

	LegoFloat m_startX;         // 0x14
	LegoFloat m_startY;         // 0x18
	LegoFloat m_x;              // 0x1c
	LegoFloat m_y;              // 0x20
	LegoFloat m_startWidth;     // 0x24
	LegoFloat m_startHeight;    // 0x28
	LegoFloat m_width;          // 0x2c
	LegoFloat m_height;         // 0x30
	LegoFloat m_rateX;          // 0x34
	LegoFloat m_rateY;          // 0x38
	LegoFloat m_rateWidth;      // 0x3c
	LegoFloat m_rateHeight;     // 0x40
	LegoU32 m_flags;            // 0x44
	GolName m_fontName;         // 0x48
	LegoU32 m_stringTableIndex; // 0x50
	union {
		ColorRGBA m_color;     // 0x54
		LegoU32 m_colorPacked; // 0x54
	};
};

#endif // CUTSCENEVISUAL_H

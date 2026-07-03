#ifndef CUTSCENEIMAGEVISUAL_H
#define CUTSCENEIMAGEVISUAL_H

#include "menu/runtime/cutscenevisual.h"

class GolImage;

// VTABLE: LEGORACERS 0x004b4a70
// SIZE 0x64
class CutsceneImageVisual : public CutsceneVisual {
public:
	CutsceneImageVisual();
	~CutsceneImageVisual() override; // vtable+0x00

	void GetContentSize(LegoS32* p_width, LegoS32* p_height) override; // vtable+0x1c
	void DrawContent(
		GolRenderDevice* p_renderer,
		LegoS32 p_x,
		LegoS32 p_y,
		undefined4 p_width,
		undefined4 p_height,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY
	) override; // vtable+0x20

	void Reset();
	void Clear();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner, GolRenderDevice* p_renderer);
	void ResolveImage(GolD3DRenderDevice* p_renderer);

	// SYNTHETIC: LEGORACERS 0x004a2690
	// CutsceneImageVisual::`vector deleting destructor'

private:
	GolImage* m_image;   // 0x58
	GolName m_imageName; // 0x5c
};

#endif // CUTSCENEIMAGEVISUAL_H

#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "golstring.h"
#include "golstringtable.h"
#include "goltxtparser.h"
#include "types.h"

class GolD3DRenderDevice;
class GolFontBase;
class GolImage;
class RaceSession;

// SIZE 0x30
class LoadingScreen {
public:
	// VTABLE: LEGORACERS 0x004b0698
	// SIZE 0x1fc
	class LsbTxtParser : public GolTxtParser {
	public:
		enum {
			e_loadingScreen = 0x27,
			e_image = 0x28,
			e_dots = 0x29,
			e_string = 0x2a,
		};
	};

	LoadingScreen();
	~LoadingScreen();
	void Destroy();
	void Initialize(
		GolExport* p_golExport,
		GolD3DRenderDevice* p_renderer,
		GolStringTable* p_stringTable,
		GolFontBase* p_font,
		LegoBool32 p_binary
	);
	void SetProgress(LegoFloat p_progress);
	void Draw();

private:
	GolD3DRenderDevice* m_renderer;   // 0x00
	GolExport* m_golExport;           // 0x04
	GolImageDefinitionList* m_images; // 0x08
	GolImage* m_tickImage;            // 0x0c
	LegoFloat m_progress;             // 0x10
	LegoS32 m_dotCount;               // 0x14
	LegoS32* m_dotPositions;          // 0x18
	GolString m_text;                 // 0x1c
	GolFontBase* m_font;              // 0x28
	LegoS32 m_textX;                  // 0x2c
};

#endif // LOADINGSCREEN_H

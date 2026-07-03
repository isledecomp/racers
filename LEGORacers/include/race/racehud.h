#ifndef RACEHUD_H
#define RACEHUD_H

#include "decomp.h"
#include "golstring.h"
#include "race/racestate.h"
#include "render/golrenderdevice.h"
#include "render/rectangle.h"
#include "types.h"

class GolMaterial;
class GolImageDefinitionList;
class GolD3DRenderDevice;
class GolFontBase;
class GolNameTable;
class GolStringTable;
class RaceSession;
class TimeRaceManager;
class GolImage;

// SIZE 0x140
class RaceHud {
public:
	enum {
		c_soundCountdown = 0x0f,
	};

	enum {
		c_layoutNone = 0,
		c_layoutFull = 1,
		c_layoutSplitTop = 2,
		c_layoutSplitBottom = 3,
	};

	// SIZE 0x09
	struct TimeText {
		LegoChar m_text[9]; // 0x00
	};

	RaceHud();

	// FUNCTION: LEGORACERS 0x00431980
	~RaceHud() {}

	LegoS32 SetResolution(LegoS32 p_width, LegoS32 p_height);
	void SetMapInfo(
		GolMaterial* p_material,
		LegoFloat p_minX,
		LegoFloat p_maxY,
		LegoFloat p_maxX,
		LegoFloat p_minY,
		LegoBool p_mirror
	);
	Racer* SetRacer(Racer* p_v0);
	void ResetDisplay(LegoS32 p_lapCount);
	void StartCountdown();
	void ShowFinish();
	void Update(LegoU32 p_elapsedMs);

private:
	friend class RaceSession;
	friend class Racer;

	void DrawFixedMap();
	void DrawRotatingMap();
	void ClipTriangleTop(
		const GolRenderDevice::TexturedVertex* p_v0,
		const GolRenderDevice::TexturedVertex* p_v1,
		const GolRenderDevice::TexturedVertex* p_v2
	);
	void ClipTriangleLeft(
		const GolRenderDevice::TexturedVertex* p_v0,
		const GolRenderDevice::TexturedVertex* p_v1,
		const GolRenderDevice::TexturedVertex* p_v2
	);
	void ClipTriangleRight(
		const GolRenderDevice::TexturedVertex* p_v0,
		const GolRenderDevice::TexturedVertex* p_v1,
		const GolRenderDevice::TexturedVertex* p_v2
	);
	void ClipTriangleBottom(
		const GolRenderDevice::TexturedVertex* p_v0,
		const GolRenderDevice::TexturedVertex* p_v1,
		const GolRenderDevice::TexturedVertex* p_v2
	);
	void DrawMapArrow(LegoS32 p_x, LegoS32 p_y, LegoFloat p_directionX, LegoFloat p_directionY);
	LegoU32 FormatTime(LegoChar* p_buffer, LegoU32 p_time);
	void DrawSpeedometer();
	void Draw();
	LegoS32 DrawTime(const LegoChar* p_text, LegoS32 p_x, LegoS32 p_y);
	LegoS32 Initialize(
		GolD3DRenderDevice* p_renderer,
		GolNameTable* p_nameTable,
		GolString* p_string,
		GolImageDefinitionList* p_resourceTable,
		RaceState* p_raceState,
		TimeRaceManager* p_timeRaceManager,
		GolStringTable* p_stringTable,
		RacerSoundSource* p_soundSource,
		LegoBool p_isTimeRace,
		undefined4 p_hideRaceInfo
	);
	LegoS32 SetLayout(LegoS32 p_v0);
	void Reset();

	static undefined4 CopyToGolString(const LegoChar* p_text, GolString* p_string);

	GolD3DRenderDevice* m_renderer;     // 0x000
	RacerSoundSource* m_soundSource;    // 0x004
	GolImageDefinitionList* m_images;   // 0x008
	GolStringTable* m_stringTable;      // 0x00c
	GolString* m_scratchString;         // 0x010
	GolString m_labelString;            // 0x014
	GolFontBase* m_font;                // 0x020
	GolFontBase* m_numberFont;          // 0x024
	RaceState* m_raceState;             // 0x028
	Racer* m_racer;                     // 0x02c
	TimeRaceManager* m_timeRaceManager; // 0x030
	LegoU32 m_elapsedMs;                // 0x034
	LegoU8 m_layout;                    // 0x038
	LegoBool m_hideRaceInfo;            // 0x039
	LegoBool m_isTimeRace;              // 0x03a
	LegoBool m_mirror;                  // 0x03b
	LegoU8 m_gadgetMode;                // 0x03c
	TimeText m_lapTimeText;             // 0x03d
	TimeText m_bestLapText;             // 0x046
	TimeText m_timeBehindText;          // 0x04f
	TimeText m_totalTimeText;           // 0x058
	LegoChar m_lapText[0x070 - 0x061];  // 0x061
	LegoS32 m_bannerMs;                 // 0x070
	LegoU32 m_positionPulseMs;          // 0x074
	LegoFloat m_speedValue;             // 0x078
	LegoS32 m_lastLapIndex;             // 0x07c
	LegoS32 m_displayLapCount;          // 0x080
	LegoU32 m_lapTimeMs;                // 0x084
	LegoU32 m_bestLapMs;                // 0x088
	LegoS32 m_finalPosition;            // 0x08c
	LegoS32 m_position;                 // 0x090
	Rect m_viewport;                    // 0x094
	LegoS32 m_centerX;                  // 0x0a4
	LegoS32 m_positionX;                // 0x0a8
	LegoS32 m_lapTimeX;                 // 0x0ac
	LegoS32 m_bestLapX;                 // 0x0b0
	LegoS32 m_timeBehindX;              // 0x0b4
	LegoS32 m_wrongWayX;                // 0x0b8
	LegoS32 m_totalTimeX;               // 0x0bc
	LegoS32 m_powerupX;                 // 0x0c0
	LegoS32 m_bannerY;                  // 0x0c4
	LegoS32 m_positionY;                // 0x0c8
	LegoS32 m_lapTimeY;                 // 0x0cc
	LegoS32 m_bestLapY;                 // 0x0d0
	LegoS32 m_timeBehindY;              // 0x0d4
	LegoS32 m_wrongWayY;                // 0x0d8
	LegoS32 m_totalTimeY;               // 0x0dc
	LegoS32 m_powerupY;                 // 0x0e0
	LegoS32 m_shortTimeWidth;           // 0x0e4
	LegoS32 m_longTimeWidth;            // 0x0e8
	LegoFloat m_textScale;              // 0x0ec
	LegoFloat m_imageScale;             // 0x0f0
	LegoFloat m_mapScale;               // 0x0f4
	LegoFloat m_bannerScale;            // 0x0f8
	LegoS32 m_screenWidth;              // 0x0fc
	LegoS32 m_screenHeight;             // 0x100
	LegoFloat m_scaleX;                 // 0x104
	LegoFloat m_aspectScale;            // 0x108
	LegoFloat m_textScaleX;             // 0x10c
	LegoFloat m_aspectRatio;            // 0x110
	LegoFloat m_scaleY;                 // 0x114
	GolMaterial* m_mapMaterial;         // 0x118
	LegoFloat m_mapMaxY;                // 0x11c
	LegoFloat m_mapMinX;                // 0x120
	LegoFloat m_mapMinY;                // 0x124
	LegoFloat m_mapMaxX;                // 0x128
	LegoFloat m_clipTop;                // 0x12c
	LegoFloat m_clipLeft;               // 0x130
	LegoFloat m_clipBottom;             // 0x134
	LegoFloat m_clipRight;              // 0x138
	LegoBool32 m_visible;               // 0x13c
};

#endif // RACEHUD_H

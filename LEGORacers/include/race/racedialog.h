#ifndef RACEDIALOG_H
#define RACEDIALOG_H

#include "decomp.h"
#include "golstring.h"
#include "types.h"

class GolD3DRenderDevice;
class GolFontBase;
class GolStringTable;
class RaceSession;

// SIZE 0x68
class RaceDialog {
public:
	RaceDialog();
	~RaceDialog();

	void Open(
		LegoU32 p_optionCount,
		const LegoU16* p_optionStringIds,
		LegoU16 p_promptStringId,
		LegoU16 p_extraStringId,
		LegoU32 p_selectionIndex
	);
	void Update(LegoU32 p_elapsedMs);
	void Draw();
	void OnKeyDown(LegoU32 p_keyCode);
	void OnKeyUp(LegoU32 p_keyCode);
	undefined4 GetState() const { return m_state; }
	LegoU32 GetSelectionIndex() const { return m_selectionIndex; }

private:
	friend class RaceSession;

	enum {
		c_keyboardEnter = 0x1000001c,
		c_keyboardSpace = 0x10000039,
		c_keyboardPrevious = 0x100000c8,
		c_keyboardNext = 0x100000d0,
		c_joystickButton4 = 0x30000004,
		c_joystickButton6 = 0x30000006,
		c_joystickButton10 = 0x3000000a,
		c_joystickButton11 = 0x3000000b,
		c_joystickButton13 = 0x3000000d,
		c_joystickButton14 = 0x3000000e,
		c_joystickButton15 = 0x3000000f,
		c_joystickAxisPositive = 0x40000002,
		c_joystickAxisNegative = 0x40000003,
		c_promptColor = 0xffffffff,
		c_selectedColor = 0xff24ffff,
		c_optionColor = 0xff127f7f,
		c_selectedAlpha = 0xff,
		c_selectedAlphaFlag = 1,
		c_selectedBlinkThresholdMs = 250,
		c_selectedPulseAlphaCenter = 0xbf,
		c_selectedPulseAlphaAmplitude = 64,
		c_cosineTableMask = 0x3ff,
		c_backdropAlpha = 64,
		c_backdropAlphaFlag = 2
	};

	void Destroy();
	void Reset();
	void Initialize(
		GolFontBase* p_font,
		GolD3DRenderDevice* p_renderer,
		GolStringTable* p_stringTable,
		LegoU32 p_keyCode
	);
	void DrawBackdrop();

	GolFontBase* m_font;            // 0x00
	GolD3DRenderDevice* m_renderer; // 0x04
	GolStringTable* m_stringTable;  // 0x08
	GolString m_options[3];         // 0x0c
	GolString m_prompt;             // 0x30
	GolString m_extra;              // 0x3c
	undefined4 m_state;             // 0x48
	LegoU32 m_optionCount;          // 0x4c
	LegoU32 m_selectionIndex;       // 0x50
	LegoU32 m_blinkMs;              // 0x54
	undefined4 m_selecting;         // 0x58
	LegoS32 m_optionsTop;           // 0x5c
	LegoS32 m_lineHeight;           // 0x60
	LegoU32 m_acceptKey;            // 0x64
};

#endif // RACEDIALOG_H

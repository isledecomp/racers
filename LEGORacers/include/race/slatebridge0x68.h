#ifndef SLATEBRIDGE0X68_H
#define SLATEBRIDGE0X68_H

#include "decomp.h"
#include "golstring.h"
#include "types.h"

class GolD3DRenderDevice;
class GolFontBase;
class GolStringTable;
class RaceSession;

// SIZE 0x68
class SlateBridge0x68 {
public:
	SlateBridge0x68();
	~SlateBridge0x68();

	void FUN_00427310(
		LegoU32 p_optionCount,
		const LegoU16* p_optionStringIds,
		LegoU16 p_promptStringId,
		LegoU16 p_extraStringId,
		LegoU32 p_selectionIndex
	);
	void FUN_00427420(LegoU32 p_elapsedMs);
	void FUN_00427440();
	void FUN_00427810(LegoU32 p_keyCode);
	void FUN_004278c0(LegoU32 p_keyCode);
	undefined4 GetUnk0x48() const { return m_unk0x48; }
	LegoU32 GetUnk0x50() const { return m_unk0x50; }

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
	void FUN_004276c0();

	GolFontBase* m_font;            // 0x00
	GolD3DRenderDevice* m_renderer; // 0x04
	GolStringTable* m_stringTable;  // 0x08
	GolString m_options[3];         // 0x0c
	GolString m_prompt;             // 0x30
	GolString m_extra;              // 0x3c
	undefined4 m_unk0x48;           // 0x48
	LegoU32 m_unk0x4c;              // 0x4c
	LegoU32 m_unk0x50;              // 0x50
	LegoU32 m_unk0x54;              // 0x54
	undefined4 m_unk0x58;           // 0x58
	LegoS32 m_unk0x5c;              // 0x5c
	LegoS32 m_unk0x60;              // 0x60
	LegoU32 m_unk0x64;              // 0x64
};

#endif // SLATEBRIDGE0X68_H

#ifndef GOLDDUNE0x38_H
#define GOLDDUNE0x38_H

#include "silverdune0x30.h"

class WhiteFalcon0x140;
class GolImgFile;

// VTABLE: GOLDP 0x1005766c
// SIZE 0x38
class GoldDune0x38 : public SilverDune0x30 {
public:
	enum {
		c_unk0x36Bit2 = 0x04,
		c_unk0x36Bit5 = 0x20,
		c_unk0x36Bit6 = 0x40,
		c_unk0x36Bit7 = 0x80,
		c_unk0x36Bit10 = 0x400,
		c_unk0x36Bit11 = 0x800,
	};
	GoldDune0x38();

	virtual void VTable0x30(WhiteFalcon0x140& p_renderer, GolImgFile* p_source); // vtable+0x30
	virtual void VTable0x34(
		WhiteFalcon0x140& p_renderer,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) = 0;                         // vtable+0x34
	virtual void VTable0x38() = 0; // vtable+0x38

	LegoU16 GetUnk0x34() const { return m_unk0x34; }
	LegoU16 GetUnk0x36() const { return m_unk0x36; }

	// SYNTHETIC: GOLDP 0x10004470 FOLDED
	// GoldDune0x38::~GoldDune0x38

	// SYNTHETIC: GOLDP 0x1002f380 FOLDED
	// GoldDune0x38::`scalar deleting destructor'

protected:
	ColorRGBA m_unk0x30;  // 0x30
	undefined2 m_unk0x34; // 0x34
	LegoU16 m_unk0x36;    // 0x36
};

#endif //  GOLDDUNE0x38_H

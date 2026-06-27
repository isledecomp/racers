#ifndef GOLDDUNE0X38_H
#define GOLDDUNE0X38_H

#include "silverdune0x30.h"

class GolRenderDevice;
class GolImgFile;
class GolTextureList;
class WhiteBaffoon0x50;

// VTABLE: GOLDP 0x1005766c
// VTABLE: LEGORACERS 0x004af928
// SIZE 0x38
class GoldDune0x38 : public SilverDune0x30 {
public:
	enum {
		c_unk0x36Bit0 = 0x01,
		c_unk0x36Bit1 = 0x02,
		c_unk0x36Bit2 = 0x04,
		c_unk0x36Bit3 = 0x08,
		c_unk0x36Bit4 = 0x10,
		c_unk0x36Bit5 = 0x20,
		c_unk0x36Bit6 = 0x40,
		c_unk0x36Bit7 = 0x80,
		c_unk0x36Bit8 = 0x100,
		c_unk0x36Bit9 = 0x200,
		c_unk0x36Bit10 = 0x400,
		c_unk0x36Bit11 = 0x800,
	};
	GoldDune0x38();

	virtual void VTable0x30(GolRenderDevice& p_renderer, GolImgFile* p_source); // vtable+0x30
	virtual void VTable0x34(
		GolRenderDevice& p_renderer,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) = 0;                         // vtable+0x34
	virtual void VTable0x38() = 0; // vtable+0x38

	LegoU16 GetUnk0x34() const { return m_unk0x34; }
	LegoU16 GetUnk0x36() const { return m_unk0x36; }
	const ColorRGBA& GetColorKey() const { return m_colorKey; }
	void SetTextureFlags(LegoU16 p_flags) { m_unk0x36 = p_flags; }
	void SetTextureDefinition(LegoU16 p_unk0x34, LegoU16 p_unk0x36, const ColorRGBA& p_colorKey)
	{
		m_unk0x34 = p_unk0x34;
		p_unk0x36 |= c_unk0x36Bit11;
		m_colorKey = p_colorKey;
		m_colorKey.m_alp = 0;
		m_unk0x36 = p_unk0x36;
	}
	void SetSourceTextureDefinition(LegoU16 p_unk0x34, LegoU16 p_unk0x36, const ColorRGBA& p_colorKey)
	{
		m_unk0x36 = p_unk0x36;
		m_unk0x34 = p_unk0x34;
		p_unk0x36 |= c_unk0x36Bit11;
		m_unk0x36 = p_unk0x36;
		m_colorKey = p_colorKey;
		m_colorKey.m_alp = 0;
	}
	void SetColorKey(const ColorRGBA& p_colorKey)
	{
		m_colorKey = p_colorKey;
		m_colorKey.m_alp = 0;
		m_unk0x36 = c_unk0x36Bit5;
		m_unk0x36 |= c_unk0x36Bit11;
	}

	// SYNTHETIC: GOLDP 0x10004470 FOLDED
	// SYNTHETIC: LEGORACERS 0x00408bd0 FOLDED
	// GoldDune0x38::~GoldDune0x38

	// SYNTHETIC: GOLDP 0x1002f380 FOLDED
	// SYNTHETIC: LEGORACERS 0x00415c40
	// GoldDune0x38::`scalar deleting destructor'

protected:
	friend class GolTextureList;
	friend class WhiteBaffoon0x50;

	ColorRGBA m_colorKey; // 0x30
	undefined2 m_unk0x34; // 0x34
	LegoU16 m_unk0x36;    // 0x36
};

#endif // GOLDDUNE0X38_H

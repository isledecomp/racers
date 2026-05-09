#ifndef MOONLITCANVAS0X5B0_H
#define MOONLITCANVAS0X5B0_H

#include "compat.h"
#include "decomp.h"
#include "falcontextureformat.h"
#include "golfile.h"
#include "types.h"

class GoldDune0x38;

// VTABLE: GOLDP 0x10056f04
// SIZE 0x5b0
class MoonlitCanvas0x5b0 {
public:
	MoonlitCanvas0x5b0();
	virtual void VTable0x00();                                                            // vtable+0x00
	virtual ~MoonlitCanvas0x5b0();                                                        // vtable+0x04
	virtual void VTable0x08(const LegoChar* p_fileName);                                  // vtable+0x08
	virtual void VTable0x0c();                                                            // vtable+0x0c
	virtual const LegoChar* VTable0x10();                                                 // vtable+0x10
	virtual void VTable0x14(undefined4, undefined4, undefined4, undefined4);              // vtable+0x14
	virtual void VTable0x18(undefined4* p_arg1);                                          // vtable+0x18
	virtual void VTable0x1c(GoldDune0x38* p_texture, LegoU32 p_flags, undefined4 p_arg3); // vtable+0x1c
	virtual void VTable0x20(GoldDune0x38* p_texture, LegoU32 p_flags, undefined4 p_arg3); // vtable+0x20

	void FUN_100226c0(
		const FalconTextureFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_pitch,
		const ColorRGBA* p_palette,
		LegoU32 p_paletteCount
	);

	const FalconTextureFormat& GetTextureFormat() const { return m_textureFormat; }
	LegoU32 GetWidth() const { return m_width; }
	LegoU32 GetHeight() const { return m_height; }
	void SetUnk0x5a8(undefined4 p_unk0x5a8) { m_unk0x5a8 = p_unk0x5a8; }
	void SetUnk0x5ac(undefined4 p_unk0x5ac) { m_unk0x5ac = p_unk0x5ac; }

	// SYNTHETIC: GOLDP 0x1001ff30
	// MoonlitCanvas0x5b0::`scalar deleting destructor'

private:
	undefined4 m_unk0x04;                // 0x04
	undefined4 m_unk0x08;                // 0x08
	undefined4 m_unk0x0c;                // 0x0c
	LegoU8* m_unk0x10;                   // 0x10
	GolFile m_file;                      // 0x14
	LegoU32 m_width;                     // 0x44
	LegoU32 m_height;                    // 0x48
	undefined4 m_unk0x4c;                // 0x4c
	FalconTextureFormat m_textureFormat; // 0x50
	undefined4 m_unk0x68;                // 0x68
	undefined4 m_unk0x6c;                // 0x6c
	undefined m_unk0x70[0x74 - 0x70];    // 0x70
	undefined4 m_unk0x74;                // 0x74
	undefined m_unk0x78[0x98 - 0x78];    // 0x78
	undefined4 m_unk0x98;                // 0x98
	ColorRGBA m_unk0x9c;                 // 0x9c
	ColorRGBA m_unk0xa0;                 // 0xa0
	undefined4 m_unk0xa4;                // 0xa4
	undefined m_unk0xa8[0x5a8 - 0xa8];   // 0xa8
	undefined4 m_unk0x5a8;               // 0x5a8
	undefined4 m_unk0x5ac;               // 0x5ac
};

#endif // MOONLITCANVAS0X5B0_H

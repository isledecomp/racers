#ifndef GOLDP_SILVERDUNE0X30_H
#define GOLDP_SILVERDUNE0X30_H

#include "decomp.h"
#include "falcontextureformat.h"
#include "types.h"

class PearlDew0x0c;
class IPalette0x4;
class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x10056d3c
// SIZE 0x30
class SilverDune0x30 {
public:
	struct Rect {
		LegoS32 m_left;   // 0x00
		LegoS32 m_top;    // 0x04
		LegoS32 m_right;  // 0x08
		LegoS32 m_bottom; // 0x0c
	};

	enum {
		c_lockRequestRead = 0x01,
		c_lockRequestWrite = 0x02,
		c_lockFlagLocked = 0x02,
		c_lockFlagUnknown0x04 = 0x04,
		c_lockFlagRead = 0x08,
		c_lockFlagWrite = 0x10,
		c_lockStateMask = c_lockFlagLocked | c_lockFlagRead | c_lockFlagWrite
	};

	SilverDune0x30();

	virtual ~SilverDune0x30();                                                                 // vtable+0x00
	virtual void LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags);             // vtable+0x04
	virtual void UnlockPixels();                                                               // vtable+0x08
	virtual void LockAuxPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags);          // vtable+0x0c
	virtual void UnlockAuxPixels();                                                            // vtable+0x10
	virtual void VTable0x14(undefined4*);                                                      // vtable+0x14
	virtual void VTable0x18();                                                                 // vtable+0x18
	virtual IPalette0x4* GetPalette();                                                         // vtable+0x1c
	virtual void Fill(LegoU32 p_color);                                                        // vtable+0x20
	virtual void Blit(LegoU32 p_x, LegoU32 p_y, SilverDune0x30* p_source, Rect* p_sourceRect); // vtable+0x24
	virtual void VTable0x28(undefined4, undefined4, undefined4*);                              // vtable+0x28
	virtual void VTable0x2c();                                                                 // vtable+0x2c

	// SYNTHETIC: GOLDP 0x1001cf40
	// SilverDune0x30::`scalar deleting destructor'

	LegoU16 GetPixelFlags() const { return m_pixelFlags; }
	LegoU16 GetWidth() const { return m_width; }
	LegoU16 GetHeight() const { return m_height; }
	FalconTextureFormat& GetTextureFormat() { return m_textureFormat; }

protected:
	friend class BronzeFalcon0xc8770;

	FalconTextureFormat m_textureFormat; // 0x04
	LegoU8* m_pixels;                    // 0x1c
	LegoU8* m_auxPixels;                 // 0x20
	LegoU16 m_pitch;                     // 0x24
	LegoU16 m_pixelFlags;                // 0x26
	LegoU16 m_auxFlags;                  // 0x28
	LegoU16 m_width;                     // 0x2a
	LegoU16 m_height;                    // 0x2c
};

#endif // GOLDP_SILVERDUNE0X30_H

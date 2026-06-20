#ifndef FALCONDUNEBAG0X10_H
#define FALCONDUNEBAG0X10_H

#include "bronzedunebag0xc.h"
#include "decomp.h"
#include "golsurfaceformat.h"

#include <windows.h>

// VTABLE: GOLDP 0x10056708
// SIZE 0x10
class FalconDuneBag0x10 : public BronzeDuneBag0xc {
public:
	FalconDuneBag0x10();
	~FalconDuneBag0x10() override; // vtable+0x20

	void CopyEntriesFrom(GolPaletteBase* p_source) override;                          // vtable+0x04
	void SetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count) override; // vtable+0x08

	void Initialize(const GolSurfaceFormat& p_textureFormat);
	void Destroy();

	LegoU16* GetMappedEntries() const { return m_unk0x0c; }

	static void SetTextureFormat(const GolSurfaceFormat& p_format);
	// SYNTHETIC: GOLDP 0x100146e0
	// FalconDuneBag0x10::`scalar deleting destructor'

private:
	LegoU16* m_unk0x0c; // 0x0c

	static GolSurfaceFormat g_textureFormat;

	friend class PurpleDune0x7c;
};

#endif // FALCONDUNEBAG0X10_H

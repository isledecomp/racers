#ifndef GOLDP_GOLFONTTABLE_H
#define GOLDP_GOLFONTTABLE_H

#include "font/golfontlibrary.h"
#include "types.h"

class GolD3DRenderDevice;
class GolFont;

// VTABLE: GOLDP 0x100562b4
// SIZE 0x2c
class GolFontTable : public GolFontLibrary {
public:
	GolFontTable();
	~GolFontTable() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	// SYNTHETIC: GOLDP 0x10003fd0
	// GolFontTable::`scalar deleting destructor'

	void AllocateItems() override;                              // vtable+0x0c
	void AllocateDefinitionBuffer(undefined4 p_index) override; // vtable+0x10
	void ReleaseDefinitionBuffers() override;                   // vtable+0x14
	void ReleaseFontSurfaces() override;                        // vtable+0x18
	void RefreshFontSurfaces() override;                        // vtable+0x1c
	GolFontBase* GetItem(LegoU32 p_index) override;             // vtable+0x24

private:
	GolFont* m_fonts; // 0x28
};

#endif // GOLDP_GOLFONTTABLE_H

#ifndef GOLDP_GOL_H
#define GOLDP_GOL_H

#include "awakekite0x20.h"
#include "decomp.h"
#include "floatyboat0x28.h"
#include "goldrawstate.h"
#include "golnametable.h"
#include "types.h"
#include "zoweeblubberworth0xf0.h"

#include <windows.h>

typedef void FatalErrorMessageCBFN(const LegoChar* p_message, const LegoChar* p_file, LegoS32 p_line);
typedef void GolExitCBFN();

class AmberHaze0x1c;
class BoundingShape0x2c;
class GolFontBase0x40;
class GolHashTable;
class GolFileSource;
class AmberLens0x344;
class GolFontTable;
class MagentaRibbon0x20;
class WhiteBaffoon0x50;
class AmberHaze0x1c;
class WhiteFalconNode0x18;

struct GolImport {
	GolFileSource* m_fileSources;               // 0x00
	LegoU32 m_fileSourceCount;                  // 0x04
	LegoChar* m_searchPaths[4];                 // 0x08
	LegoU32 m_searchPathCount;                  // 0x18
	GolHashTable* m_hashTable;                  // 0x1c
	HANDLE m_mutex;                             // 0x20
	undefined m_unk0x24[0x28 - 0x24];           // 0x24
	FatalErrorMessageCBFN* m_fatalErrorMessage; // 0x28
};

// VTABLE: GOLDP 0x100564b0
// SIZE 0x4
class GolExport {
	// SYNTHETIC: GOLDP 0x10007170
	// GolExport::`scalar deleting destructor'

protected:
	virtual ~GolExport() {} // vtable+0x00

public:
	virtual GolDrawState* GetDrawState() = 0;                  // vtable+0x04
	virtual ZoweeBlubberworth0xf0* VTable0x08() = 0;           // vtable+0x08
	virtual MagentaRibbon0x20* CreateTextureList() = 0;        // vtable+0x0c
	virtual AmberHaze0x1c* CreateMaterialList() = 0;           // vtable+0x10
	virtual undefined4* VTable0x14() = 0;                      // vtable+0x14
	virtual undefined4* VTable0x18() = 0;                      // vtable+0x18
	virtual BoundingShape0x2c* CreateBoundingShape() = 0;      // vtable+0x1c
	virtual AmberLens0x344* VTable0x20() = 0;                  // vtable+0x20
	virtual undefined4 VTable0x24() = 0;                       // vtable+0x24
	virtual WhiteBaffoon0x50* VTable0x28() = 0;                // vtable+0x28
	virtual GolFontBase0x40* CreateFont() = 0;                 // vtable+0x2c
	virtual FloatyBoat0x28* VTable0x30() = 0;                  // vtable+0x30
	virtual AwakeKite0x20* VTable0x34() = 0;                   // vtable+0x34
	virtual GolFontTable* CreateFontTable() = 0;               // vtable+0x38
	virtual void VTable0x3c(ZoweeBlubberworth0xf0*) = 0;       // vtable+0x3c
	virtual void DestroyTextureList(MagentaRibbon0x20*) = 0;   // vtable+0x40
	virtual void DestroyMaterialList(AmberHaze0x1c*) = 0;      // vtable+0x44
	virtual void VTable0x48(undefined4*) = 0;                  // vtable+0x48
	virtual void VTable0x4c(WhiteFalconNode0x18*) = 0;         // vtable+0x4c
	virtual void DestroyBoundingShape(BoundingShape0x2c*) = 0; // vtable+0x50
	virtual void VTable0x54(AmberLens0x344*) = 0;              // vtable+0x54
	virtual void VTable0x58(undefined4*) = 0;                  // vtable+0x58
	virtual void VTable0x5c(WhiteBaffoon0x50*) = 0;            // vtable+0x5c
	virtual void DestroyFont(GolFontBase0x40*) = 0;            // vtable+0x60
	virtual void VTable0x64(undefined4*) = 0;                  // vtable+0x64
	virtual void VTable0x68(AwakeKite0x20*) = 0;               // vtable+0x68
	virtual void DestroyFontTable(GolNameTable*) = 0;          // vtable+0x6c
};

typedef GolExport* GolEntryCBFN(GolImport*);
typedef void GolExitCBFN();

#ifdef __cplusplus
extern "C"
{
#endif

	extern GolExport* GolEntry(GolImport* p_import);

	extern void GolExit();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GOLDP_GOL_H

#ifndef GOLDP_GOL_H
#define GOLDP_GOL_H

#include "decomp.h"
#include "types.h"

#include <windows.h>

typedef void FatalErrorMessageCBFN(const LegoChar* p_message, const LegoChar* p_file, LegoS32 p_line);
typedef void GolExitCBFN();

class GolMaterialLibrary;
class GolCamera;
class GolImageDefinitionList;
class GolBoundingShape;
class GolWorldEntity;
class GolDrawState;
class GolCommonDrawState;
class GolFontBase;
class GolHashTable;
class GolFileSource;
class GolFontTable;
class GolNameTable;
class GolModelBase;
class GolTextureList;
class GolTiledTexture;
class GolSceneNode;
class GolWorldDatabase;

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
	// FUNCTION: GOLDP 0x10007160
	virtual ~GolExport() {} // vtable+0x00

public:
	virtual GolCommonDrawState* GetDrawState() = 0;             // vtable+0x04
	virtual GolWorldDatabase* CreateWorldDatabase() = 0;        // vtable+0x08
	virtual GolTextureList* CreateTextureList() = 0;            // vtable+0x0c
	virtual GolMaterialLibrary* CreateMaterialList() = 0;       // vtable+0x10
	virtual GolModelBase* CreateModel() = 0;                    // vtable+0x14
	virtual GolSceneNode* CreateSceneNode() = 0;                // vtable+0x18
	virtual GolBoundingShape* CreateBoundingShape() = 0;        // vtable+0x1c
	virtual GolCamera* CreateCamera() = 0;                      // vtable+0x20
	virtual undefined4 VTable0x24() = 0;                        // vtable+0x24
	virtual GolTiledTexture* CreateTiledTexture() = 0;          // vtable+0x28
	virtual GolFontBase* CreateFont() = 0;                      // vtable+0x2c
	virtual GolWorldEntity* CreateBillboard() = 0;              // vtable+0x30
	virtual GolImageDefinitionList* CreateImageList() = 0;      // vtable+0x34
	virtual GolFontTable* CreateFontTable() = 0;                // vtable+0x38
	virtual void DestroyWorldDatabase(GolWorldDatabase*) = 0;   // vtable+0x3c
	virtual void DestroyTextureList(GolTextureList*) = 0;       // vtable+0x40
	virtual void DestroyMaterialList(GolMaterialLibrary*) = 0;  // vtable+0x44
	virtual void DestroyModel(GolModelBase*) = 0;               // vtable+0x48
	virtual void DestroySceneNode(GolSceneNode*) = 0;           // vtable+0x4c
	virtual void DestroyBoundingShape(GolBoundingShape*) = 0;   // vtable+0x50
	virtual void DestroyCamera(GolCamera*) = 0;                 // vtable+0x54
	virtual void VTable0x58(undefined4*) = 0;                   // vtable+0x58
	virtual void DestroyTiledTexture(GolTiledTexture*) = 0;     // vtable+0x5c
	virtual void DestroyFont(GolFontBase*) = 0;                 // vtable+0x60
	virtual void DestroyBillboard(GolWorldEntity*) = 0;         // vtable+0x64
	virtual void DestroyImageList(GolImageDefinitionList*) = 0; // vtable+0x68
	virtual void DestroyFontTable(GolNameTable*) = 0;           // vtable+0x6c
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

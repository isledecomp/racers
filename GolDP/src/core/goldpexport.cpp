#include "core/goldpexport.h"

#include "bounds/golboundingshape.h"
#include "camera/golcamera.h"
#include "camera/golscenetransformnode.h"
#include "font/golfont.h"
#include "font/golfontbase.h"
#include "font/golfonttable.h"
#include "golerror.h"
#include "golscenenode.h"
#include "image/whitebaffoon0x50.h"
#include "material/amberhaze0x20.h"
#include "material/awakekite0x20.h"
#include "material/purpleribbon0x24.h"
#include "mesh/golmodel.h"
#include "scene/golbillboardex.h"
#include "types.h"
#include "world/golworlddatabaseex.h"

DECOMP_SIZE_ASSERT(GolExport, 0x4)
DECOMP_SIZE_ASSERT(GolDPExport, 0xc8ac8)

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 GolDPExport::VTable0x24()
{
	MATCHING(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x10007060
GolDPExport::~GolDPExport()
{
}

// FUNCTION: GOLDP 0x10015090
GolCommonDrawState* GolDPExport::GetDrawState()
{
	return &m_state;
}

// FUNCTION: GOLDP 0x100150a0
GolWorldDatabase* GolDPExport::VTable0x08()
{
	GolWorldDatabase* obj = new GolWorldDatabaseEx;

	if (obj == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return obj;
}

// FUNCTION: GOLDP 0x10015110
GolTextureList* GolDPExport::CreateTextureList()
{
	GolTextureList* obj = new PurpleRibbon0x24;
	if (obj == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return obj;
}

// FUNCTION: GOLDP 0x10015180
GolMaterialLibrary* GolDPExport::CreateMaterialList()
{
	AmberHaze0x20* result = new AmberHaze0x20;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return result;
}

// FUNCTION: GOLDP 0x100151f0
GolModelBase* GolDPExport::VTable0x14()
{
	GolModel* result = new GolModel;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x10015260
GolSceneNode* GolDPExport::VTable0x18()
{
	GolSceneTransformNode* result = new GolSceneTransformNode;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x100152d0
GolBoundingShape* GolDPExport::CreateBoundingShape()
{
	GolBoundingShape* bdb = new GolBoundingShape;
	if (bdb == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return bdb;
}

// FUNCTION: GOLDP 0x10015340
GolCamera* GolDPExport::VTable0x20()
{
	GolCamera* result = new GolCamera;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x100153b0
WhiteBaffoon0x50* GolDPExport::VTable0x28()
{
	UtopianPan0xa4* result = new UtopianPan0xa4;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x10015420
GolFontBase* GolDPExport::CreateFont()
{
	GolFont* font = new GolFont;
	if (font == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return font;
}

// FUNCTION: GOLDP 0x10015490
GolWorldEntity* GolDPExport::VTable0x30()
{
	GolWorldEntity* result = new GolBillboardEx;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x10015500
AwakeKite0x20* GolDPExport::VTable0x34()
{
	AwakeKite0x20* result = new AwakeKite0x20;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x10015570
GolFontTable* GolDPExport::CreateFontTable()
{
	GolFontTable* result = new GolFontTable;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x100155e0
void GolDPExport::VTable0x3c(GolWorldDatabase* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015600 FOLDED
void GolDPExport::DestroyTextureList(GolTextureList* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015600 FOLDED
void GolDPExport::DestroyMaterialList(GolMaterialLibrary* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015620
void GolDPExport::VTable0x48(GolModelBase* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015600 FOLDED
void GolDPExport::VTable0x4c(GolSceneNode* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015600 FOLDED
void GolDPExport::DestroyBoundingShape(GolBoundingShape* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015640
void GolDPExport::VTable0x54(GolCamera* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015660
void GolDPExport::VTable0x5c(WhiteBaffoon0x50* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015680
void GolDPExport::DestroyFont(GolFontBase* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x100156a0
void GolDPExport::VTable0x64(undefined4* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void GolDPExport::VTable0x58(undefined4*)
{
	// empty
}

// FUNCTION: GOLDP 0x10015600 FOLDED
void GolDPExport::VTable0x68(AwakeKite0x20* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015600 FOLDED
void GolDPExport::DestroyFontTable(GolNameTable* p_fontTable)
{
	if (p_fontTable != NULL) {
		delete p_fontTable;
	}
}

#include "core/goldpexport.h"

#include "bounds/golbdbboundingshape.h"
#include "camera/golcamera.h"
#include "camera/golscenetransformnode.h"
#include "font/golfont0xa0.h"
#include "font/golfontbase0x40.h"
#include "font/golfonttable.h"
#include "golerror.h"
#include "golscenenode.h"
#include "image/whitebaffoon0x50.h"
#include "material/amberhaze0x20.h"
#include "material/awakekite0x20.h"
#include "material/purpleribbon0x24.h"
#include "mesh/golgdbmodel.h"
#include "scene/golwdbbillboardex.h"
#include "types.h"
#include "world/golwdbdatabaseex.h"

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
GolDrawState* GolDPExport::GetDrawState()
{
	return &m_state;
}

// FUNCTION: GOLDP 0x100150a0
GolWdbDatabase* GolDPExport::VTable0x08()
{
	GolWdbDatabase* obj = new GolWdbDatabaseEx;

	if (obj == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return obj;
}

// FUNCTION: GOLDP 0x10015110
GolTdbTextureList* GolDPExport::CreateTextureList()
{
	GolTdbTextureList* obj = new PurpleRibbon0x24;
	if (obj == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return obj;
}

// FUNCTION: GOLDP 0x10015180
GolMdbMaterialList* GolDPExport::CreateMaterialList()
{
	AmberHaze0x20* result = new AmberHaze0x20;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return result;
}

// FUNCTION: GOLDP 0x100151f0
GolGdbModelBase* GolDPExport::VTable0x14()
{
	GolGdbModel* result = new GolGdbModel;
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
GolBdbBoundingShape* GolDPExport::CreateBoundingShape()
{
	GolBdbBoundingShape* bdb = new GolBdbBoundingShape;
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
GolFontBase0x40* GolDPExport::CreateFont()
{
	GolFont0xa0* font = new GolFont0xa0;
	if (font == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return font;
}

// FUNCTION: GOLDP 0x10015490
GolWdbEntity* GolDPExport::VTable0x30()
{
	GolWdbEntity* result = new GolWdbBillboardEx;
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
void GolDPExport::VTable0x3c(GolWdbDatabase* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015600 FOLDED
void GolDPExport::DestroyTextureList(GolTdbTextureList* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015600 FOLDED
void GolDPExport::DestroyMaterialList(GolMdbMaterialList* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015620
void GolDPExport::VTable0x48(GolGdbModelBase* p_obj)
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
void GolDPExport::DestroyBoundingShape(GolBdbBoundingShape* p_obj)
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
void GolDPExport::DestroyFont(GolFontBase0x40* p_obj)
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

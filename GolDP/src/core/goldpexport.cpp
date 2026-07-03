#include "core/goldpexport.h"

#include "camera/golcamera.h"
#include "camera/golscenetransformnode.h"
#include "font/golfont.h"
#include "font/golfonttable.h"
#include "golboundingshape.h"
#include "golerror.h"
#include "golfontbase.h"
#include "golscenenode.h"
#include "image/goltiledtexture.h"
#include "material/gold3dtexturelist.h"
#include "material/golimagedefinitionlist.h"
#include "material/golsoftwaremateriallibrary.h"
#include "mesh/golmodel.h"
#include "scene/golbillboardex.h"
#include "types.h"
#include "world/golworlddatabaseex.h"

DECOMP_SIZE_ASSERT(GolExport, 0x4)
DECOMP_SIZE_ASSERT(GolDPExport, 0xc8ac8)

// FUNCTION: GOLDP 0x100016f0 FOLDED
undefined4 GolDPExport::VTable0x24()
{
	return 0;
}

// FUNCTION: GOLDP 0x10007060
GolDPExport::~GolDPExport()
{
}

// FUNCTION: GOLDP 0x10015090
GolCommonDrawState* GolDPExport::GetDrawState()
{
	return &m_state;
}

// FUNCTION: GOLDP 0x100150a0
GolWorldDatabase* GolDPExport::CreateWorldDatabase()
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
	GolTextureList* obj = new GolD3DTextureList;
	if (obj == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return obj;
}

// FUNCTION: GOLDP 0x10015180
GolMaterialLibrary* GolDPExport::CreateMaterialList()
{
	GolSoftwareMaterialLibrary* result = new GolSoftwareMaterialLibrary;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return result;
}

// FUNCTION: GOLDP 0x100151f0
GolModelBase* GolDPExport::CreateModel()
{
	GolModel* result = new GolModel;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x10015260
GolSceneNode* GolDPExport::CreateSceneNode()
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
GolCamera* GolDPExport::CreateCamera()
{
	GolCamera* result = new GolCamera;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x100153b0
GolTiledTexture* GolDPExport::CreateTiledTexture()
{
	GolImage* result = new GolImage;
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
GolWorldEntity* GolDPExport::CreateBillboard()
{
	GolWorldEntity* result = new GolBillboardEx;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x10015500
GolImageDefinitionList* GolDPExport::CreateImageList()
{
	GolImageDefinitionList* result = new GolImageDefinitionList;
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
void GolDPExport::DestroyWorldDatabase(GolWorldDatabase* p_obj)
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
void GolDPExport::DestroyModel(GolModelBase* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015600 FOLDED
void GolDPExport::DestroySceneNode(GolSceneNode* p_obj)
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
void GolDPExport::DestroyCamera(GolCamera* p_obj)
{
	if (p_obj != NULL) {
		delete p_obj;
	}
}

// FUNCTION: GOLDP 0x10015660
void GolDPExport::DestroyTiledTexture(GolTiledTexture* p_obj)
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
void GolDPExport::DestroyBillboard(GolWorldEntity* p_obj)
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
void GolDPExport::DestroyImageList(GolImageDefinitionList* p_obj)
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

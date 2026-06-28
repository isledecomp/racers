#include "world/golworlddatabaseex.h"

#include "camera/golcamera.h"
#include "camera/golscenetransformnode.h"
#include "cmbmodelpart0x34.h"
#include "golanimatedentity.h"
#include "golboundingshape.h"
#include "golcollidableentity.h"
#include "golerror.h"
#include "golmodelentity.h"
#include "golmodelmaterialtable.h"
#include "mabmaterialanimation0x14.h"
#include "material/amberhaze0x20.h"
#include "material/purpleribbon0x24.h"
#include "mesh/golmodel.h"
#include "render/gold3drenderdevice.h"
#include "scene/golbillboardex.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolWorldDatabaseEx, 0x118)

inline static void BuildResourceFileName(LegoChar* p_dest, const LegoChar* p_name, const LegoChar* p_suffix)
{
	::memcpy(p_dest, p_name, sizeof(GolName));
	p_dest[sizeof(GolName)] = '\0';
	::strcat(p_dest, p_suffix);
}

// FUNCTION: GOLDP 0x10017190
GolWorldDatabaseEx::GolWorldDatabaseEx()
{
	m_unk0xf0 = NULL;
	m_unk0xf4 = NULL;
	m_unk0x10c = NULL;
	m_unk0xf8 = NULL;
	m_unk0x104 = NULL;
	m_unk0xfc = NULL;
	m_unk0x110 = NULL;
	m_unk0x100 = NULL;
	m_unk0x108 = NULL;
	m_unk0x114 = NULL;
}

// FUNCTION: GOLDP 0x10017200
GolWorldDatabaseEx::~GolWorldDatabaseEx()
{
	VTable0x18();
}

// FUNCTION: GOLDP 0x10017250
GolTextureList* GolWorldDatabaseEx::VTable0x2c(LegoU32 p_index) const
{
	return &m_unk0xf0[p_index];
}

// FUNCTION: GOLDP 0x10017270
GolMaterialLibrary* GolWorldDatabaseEx::VTable0x30(LegoU32 p_index) const
{
	return &m_unk0xf4[p_index];
}

// FUNCTION: GOLDP 0x10017290
CmbModelPart0x34* GolWorldDatabaseEx::VTable0x34(LegoU32 p_index) const
{
	return &m_unk0x10c[p_index];
}

// FUNCTION: GOLDP 0x100172b0
GolModelBase* GolWorldDatabaseEx::VTable0x38(LegoU32 p_index) const
{
	return &m_unk0xf8[p_index];
}

// FUNCTION: GOLDP 0x100172d0
GolModelMaterialTable* GolWorldDatabaseEx::VTable0x3c(LegoU32 p_index) const
{
	return &m_unk0x104[p_index];
}

// FUNCTION: GOLDP 0x100172f0
GolSceneNode* GolWorldDatabaseEx::VTable0x40(LegoU32 p_index) const
{
	return &m_unk0xfc[p_index];
}

// FUNCTION: GOLDP 0x10017310
GolBoundingShape* GolWorldDatabaseEx::VTable0x44(LegoU32 p_index) const
{
	return &m_unk0x110[p_index];
}

// FUNCTION: GOLDP 0x10017330
GolWorldEntity* GolWorldDatabaseEx::VTable0x48(LegoU32 p_index) const
{
	return &m_unk0x100[p_index];
}

// FUNCTION: GOLDP 0x10017350
MabMaterialAnimation0x14* GolWorldDatabaseEx::VTable0x4c(LegoU32 p_index) const
{
	return &m_unk0x108[p_index];
}

// FUNCTION: GOLDP 0x10017370
GolCameraBase* GolWorldDatabaseEx::VTable0x50(LegoU32 p_index) const
{
	return &m_unk0x114[p_index];
}

// FUNCTION: GOLDP 0x10017390
void GolWorldDatabaseEx::VTable0x08()
{
	if (GetUnk0x0c() != 0) {
		m_unk0xf0 = new PurpleRibbon0x24[GetUnk0x0c()];
		if (m_unk0xf0 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x14() != 0) {
		m_unk0xf4 = new AmberHaze0x20[GetUnk0x14()];
		if (m_unk0xf4 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x1c() != 0) {
		m_unk0x10c = new CmbModelPart0x34[GetUnk0x1c()];
		if (m_unk0x10c == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x24() != 0) {
		m_unk0xf8 = new GolModel[GetUnk0x24()];
		if (m_unk0xf8 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x2c() != 0) {
		m_unk0x104 = new GolModelMaterialTable[GetUnk0x2c()];
		if (m_unk0x104 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x34() != 0) {
		m_unk0xfc = new GolSceneTransformNode[GetUnk0x34()];
		if (m_unk0xfc == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x3c() != 0) {
		m_unk0x110 = new GolBoundingShape[GetUnk0x3c()];
		if (m_unk0x110 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x6c() != 0) {
		m_unk0x100 = new GolBillboardEx[GetUnk0x6c()];
		if (m_unk0x100 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x74() != 0) {
		m_unk0x108 = new MabMaterialAnimation0x14[GetUnk0x74()];
		if (m_unk0x108 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x7c()) {
		m_unk0x114 = new GolCamera[GetUnk0x7c()];
		if (m_unk0x114 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// STUB: GOLDP 0x10017ac0
undefined4* GolWorldDatabaseEx::VTable0x0c()
{
	LegoU32 i;
	GolD3DRenderDevice* textureRenderer = static_cast<GolD3DRenderDevice*>(m_unk0x04);

	for (i = 0; i < m_unk0x0c; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_unk0x10[i], ".tdf");
		VTable0x2c(i)->VTable0x24(textureRenderer, fileName, m_binary);
	}

	for (i = 0; i < m_unk0x14; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_unk0x18[i], ".mdf");
		VTable0x30(i)->VTable0x24(m_unk0x04, fileName, m_binary);
	}

	for (i = 0; i < m_unk0x1c; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_unk0x20[i], ".adf");
		VTable0x34(i)->VTable0x14(fileName, m_binary);
	}

	for (i = 0; i < m_unk0x24; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_unk0x28[i], ".gdf");
		VTable0x38(i)->VTable0x1c(m_unk0x04, fileName, m_binary);
	}

	for (i = 0; i < m_unk0x2c; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_unk0x30[i], ".gdf");
		VTable0x3c(i)->FUN_10025e60(m_unk0x04, fileName, m_binary);
	}

	for (i = 0; i < m_unk0x34; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_unk0x38[i], ".sdf");
		VTable0x40(i)->VTable0x14(fileName, m_binary);
	}

	for (i = 0; i < m_unk0x3c; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_unk0x40[i], ".bdf");
		VTable0x44(i)->Deserialize(fileName, m_binary);
	}

	for (i = 0; i < m_unk0x74; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_unk0x78[i], ".maf");
		VTable0x4c(i)->VTable0x04(m_unk0x04, fileName, m_binary);
	}

	for (i = 0; i < m_unk0x6c; i++) {
		WdbBillboardSprite0x38* sprite = &m_unk0x70[i];
		GolBillboardEx* billboard = &m_unk0x100[i];
		LegoFloat maxDistanceSquared = sprite->m_unk0x28 * sprite->m_unk0x28;

		if (sprite->m_flags & WdbBillboardSprite0x38::c_flagBit2) {
			LegoU32 materialTableIndex = sprite->m_unk0x34;
			if (materialTableIndex >= m_unk0x2c) {
				GOL_FATALERROR_MESSAGE("Illegal mat assign reference");
			}

			billboard->FUN_10029e90(
				&m_unk0x104[materialTableIndex],
				sprite->m_unk0x36,
				sprite->m_unk0x20,
				sprite->m_unk0x24,
				maxDistanceSquared
			);
		}
		else {
			if (sprite->m_unk0x00[0] == '\0') {
				GOL_FATALERROR_MESSAGE("Sprite is missing material name");
			}

			DuskwindBananaRelic0x24* material = m_unk0x04->FindMaterialByName(sprite->m_unk0x00);
			if (material == NULL) {
				LegoChar message[64];
				::memset(message, 0, sizeof(message));
				::strncpy(message, sprite->m_unk0x00, sizeof(GolName));
				::strcat(message, " sprite material not found");
				GOL_FATALERROR_MESSAGE(message);
			}

			billboard->VTable0x4c(material, sprite->m_unk0x20, sprite->m_unk0x24, maxDistanceSquared);
		}

		billboard->VTable0x08(sprite->m_unk0x08);
		if (sprite->m_flags & WdbBillboardSprite0x38::c_flagBit1) {
			billboard->EnableFlagBit1();
			billboard->SetUnk0x30(sprite->m_unk0x14);
		}

		FUN_1002e250(billboard, sprite);
	}

	return NULL;
}

// FUNCTION: GOLDP 0x100180a0
void GolWorldDatabaseEx::VTable0x18()
{
	if (m_unk0x114) {
		delete[] m_unk0x114;
		m_unk0x114 = NULL;
	}
	if (m_unk0x100) {
		delete[] m_unk0x100;
		m_unk0x100 = NULL;
	}
	if (m_unk0x110) {
		delete[] m_unk0x110;
		m_unk0x110 = NULL;
	}
	if (m_unk0xfc) {
		delete[] m_unk0xfc;
		m_unk0xfc = NULL;
	}
	if (m_unk0x104) {
		delete[] m_unk0x104;
		m_unk0x104 = NULL;
	}
	if (m_unk0xf8) {
		delete[] m_unk0xf8;
		m_unk0xf8 = NULL;
	}
	if (m_unk0x10c) {
		delete[] m_unk0x10c;
		m_unk0x10c = NULL;
	}
	if (m_unk0xf4) {
		delete[] m_unk0xf4;
		m_unk0xf4 = NULL;
	}
	if (m_unk0xf0) {
		delete[] m_unk0xf0;
		m_unk0xf0 = NULL;
	}
	if (m_unk0x108) {
		delete[] m_unk0x108;
		m_unk0x108 = NULL;
	}

	GolWorldDatabase::VTable0x18();
}

// FUNCTION: GOLDP 0x100181b0
void GolWorldDatabaseEx::VTable0x1c(GolRenderDevice* p_renderer)
{
	LegoU32 i;
	for (i = 0; i < m_unk0x5c; i++) {
		p_renderer->VTable0x90(&m_unk0xa4[i]);
	}
}

// FUNCTION: GOLDP 0x100181f0
void GolWorldDatabaseEx::VTable0x20(GolRenderDevice* p_renderer)
{
	LegoU32 i;
	for (i = 0; i < m_unk0x4c; i++) {
		m_unk0x9c[i].VTable0x1c(*p_renderer);
	}
}

// FUNCTION: GOLDP 0x10018230
void GolWorldDatabaseEx::VTable0x24(GolRenderDevice* p_renderer)
{
	LegoU32 i;
	for (i = 0; i < m_unk0x54; i++) {
		m_unk0xa0[i].VTable0x1c(*p_renderer);
	}
}

// FUNCTION: GOLDP 0x10018270
void GolWorldDatabaseEx::VTable0x28(GolRenderDevice* p_renderer)
{
	LegoU32 i;
	for (i = 0; i < m_unk0x6c; i++) {
		p_renderer->VTable0xb4(m_unk0x100[i]);
	}
}

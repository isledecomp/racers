#include "util/tealcrucible0x50.h"

#include "core/gol.h"
#include "golmodelentity.h"
#include "mesh/golmodelbase.h"
#include "model/gdbpartlibrary0x1c.h"
#include "racer/lavendervault0x764.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(TealCrucible0x50, 0x50)

// FUNCTION: LEGORACERS 0x00499110
TealCrucible0x50::TealCrucible0x50()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00499120
TealCrucible0x50::~TealCrucible0x50()
{
	FUN_004991c0();
}

// FUNCTION: LEGORACERS 0x00499130
void TealCrucible0x50::Reset()
{
	m_golExport = NULL;
	m_renderer = NULL;
	m_worldDatabase = NULL;
	m_cosmeticTable = NULL;
	m_partLibrary = NULL;
	m_materialTable = NULL;
	::memset(m_unk0x30, 0, sizeof(m_unk0x30));
	::memset(m_unk0x14, 0, sizeof(m_unk0x14));
}

// FUNCTION: LEGORACERS 0x004991c0
LegoBool32 TealCrucible0x50::FUN_004991c0()
{
	if (m_worldDatabase == NULL) {
		return TRUE;
	}

	m_golExport->VTable0x3c(m_worldDatabase);

	for (LegoS32 i = 0; i < 7; i++) {
		if (m_unk0x14[i] != NULL) {
			m_golExport->VTable0x48(m_unk0x14[i]);
		}
	}

	Reset();
	return m_worldDatabase == NULL;
}

// FUNCTION: LEGORACERS 0x004992f0
void TealCrucible0x50::FUN_004992f0(GolModelBase* p_model)
{
	for (LegoS32 i = 0; i < 7; i++) {
		if (m_unk0x14[i] == p_model) {
			m_unk0x30[i] = TRUE;
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x00499320
GolModelBase* TealCrucible0x50::FUN_00499320(LegoS32 p_index)
{
	GolName name;
	m_cosmeticTable->CopyHatName(p_index, name);

	for (LegoS32 modelIndex = 0; modelIndex < 7; modelIndex++) {
		if (m_unk0x30[modelIndex] == 0) {
			m_partLibrary->CopyPartToModel(m_renderer, m_unk0x14[modelIndex], name);
			m_unk0x30[modelIndex] = TRUE;
			return m_unk0x14[modelIndex];
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00499380
GolModelBase* TealCrucible0x50::FUN_00499380(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_cosmeticTable->FUN_00498f70(p_index, modelName, materialName);

	GolWorldDatabase* db = m_worldDatabase;
	GolModelEntity* entity;
	if (db->m_unk0xb4.GetNameEntries() == NULL) {
		entity = NULL;
	}
	else {
		entity = static_cast<GolModelEntity*>(db->m_unk0xb4.GetName(modelName));
	}

	return entity->GetModel(0);
}

// FUNCTION: LEGORACERS 0x004993d0
GolModelBase* TealCrucible0x50::FUN_004993d0(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_cosmeticTable->FUN_00498fd0(p_index, modelName, materialName);

	GolWorldDatabase* db = m_worldDatabase;
	GolModelEntity* entity;
	if (db->m_unk0xb4.GetNameEntries() == NULL) {
		entity = NULL;
	}
	else {
		entity = static_cast<GolModelEntity*>(db->m_unk0xb4.GetName(modelName));
	}

	return entity->GetModel(0);
}

// FUNCTION: LEGORACERS 0x00499420
GolModelBase* TealCrucible0x50::FUN_00499420(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_cosmeticTable->FUN_00499020(p_index, modelName, materialName);

	GolWorldDatabase* db = m_worldDatabase;
	GolModelEntity* entity;
	if (db->m_unk0xb4.GetNameEntries() == NULL) {
		entity = NULL;
	}
	else {
		entity = static_cast<GolModelEntity*>(db->m_unk0xb4.GetName(modelName));
	}

	return entity->GetModel(0);
}

// FUNCTION: LEGORACERS 0x00499470
void* TealCrucible0x50::FUN_00499470(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_cosmeticTable->FUN_00498f70(p_index, modelName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}

// FUNCTION: LEGORACERS 0x004994b0
void* TealCrucible0x50::FUN_004994b0(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_cosmeticTable->FUN_00498fd0(p_index, modelName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}

// FUNCTION: LEGORACERS 0x004994f0
void* TealCrucible0x50::FUN_004994f0(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_cosmeticTable->FUN_00499020(p_index, modelName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}

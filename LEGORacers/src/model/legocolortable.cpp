#include "model/legocolortable.h"

#include "core/gol.h"
#include "golbinparser.h"
#include "golerror.h"
#include "goltxtparser.h"
#include "material/duskwindbananarelic0x24.h"
#include "material/golmateriallibrary.h"
#include "model/legopiecelibrary.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(LegoColorTable, 0x38)
DECOMP_SIZE_ASSERT(LegoColorTable::ColorRecord, 0x10)
DECOMP_SIZE_ASSERT(LegoColorTable::MaterialUsage, 0x04)

static LegoS32 CompareColorRecords(const void* p_lhs, const void* p_rhs);

// FUNCTION: LEGORACERS 0x00497830
LegoChar* LegoColorTable::ColorRecord::SetName(const LegoChar* p_name)
{
	::memset(m_name, 0, sizeof(m_name));
	return ::strncpy(m_name, p_name, sizeof(m_name));
}

// FUNCTION: LEGORACERS 0x00497860
LegoS32 LegoColorTable::Reset()
{
	m_golExport = NULL;
	m_renderer = NULL;
	m_wdf = NULL;
	m_materials = NULL;
	m_colorRecords = NULL;
	m_colorMaterialIndices = NULL;
	m_colorRecordCount = 0;
	m_materialUsage = NULL;

	return 0;
}

// FUNCTION: LEGORACERS 0x00497880
LegoColorTable::LegoColorTable()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004978a0
LegoColorTable::~LegoColorTable()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004978f0
void LegoColorTable::Initialize(GolExport* p_golExport, GolD3DRenderDevice* p_renderer)
{
	Destroy();
	m_golExport = p_golExport;
	m_renderer = p_renderer;
}

// FUNCTION: LEGORACERS 0x00497910
void LegoColorTable::Destroy()
{
	if (m_materialTable.m_renderer != NULL) {
		m_materialTable.Clear();
	}

	if (m_golExport != NULL && m_wdf != NULL) {
		m_wdf->VTable0x18();
		m_golExport->VTable0x3c(m_wdf);
	}

	if (m_colorRecords != NULL) {
		delete[] m_colorRecords;
	}
	if (m_colorMaterialIndices != NULL) {
		delete[] m_colorMaterialIndices;
	}
	if (m_materialUsage != NULL) {
		delete[] m_materialUsage;
	}

	Reset();
}

// STUB: LEGORACERS 0x00497980
void LegoColorTable::RebuildColorMaterialLookup()
{
	STUB(0x00497980);

	LegoS32 materialCount = static_cast<LegoS32>(m_materialTable.m_count);

	for (LegoS32 i = 0; i < m_colorRecordCount; i++) {
		ColorRecord& record = m_colorRecords[i];
		m_colorMaterialIndices[record.m_materialIndex] = -1;
		for (LegoS32 j = 0; j < materialCount; j++) {
			DuskwindBananaRelic0x24* material = static_cast<DuskwindBananaRelic0x24*>(m_materialTable.m_entries[j]);
			DuskWindName0x8 materialName = material->GetNameRecord();
			if (::strncmp(materialName.m_unk0x0, record.m_name, sizeof(GolName)) == 0) {
				m_colorMaterialIndices[record.m_materialIndex] = j;
				break;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00497a10
void LegoColorTable::LoadColors(const LegoChar* p_filename, undefined4 p_binary)
{
	if (m_colorRecords != NULL) {
		delete[] m_colorRecords;
	}
	if (m_colorMaterialIndices != NULL) {
		delete[] m_colorMaterialIndices;
	}
	m_colorRecords = NULL;
	m_colorMaterialIndices = NULL;
	m_colorRecordCount = 0;

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".leb");
	}
	else {
		parser = new LegoPieceLibrary::LebTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_filename);
	if (!parser->IsOpen()) {
		GOL_FATALERROR_MESSAGE("Unable to open LEGO Color file");
	}

	if (parser->GetNextToken() != GolFileParser::e_unknown0x2d) {
		parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
	m_colorRecordCount = LegoPieceLibrary::ReadBracketedCountAndLeftCurly(parser);
	m_colorRecords = new ColorRecord[m_colorRecordCount];
	m_colorMaterialIndices = new LegoS32[m_colorRecordCount];
	if (m_colorRecords == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	if (m_colorMaterialIndices == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoS32 i = 0; i < m_colorRecordCount; i++) {
		m_colorRecords[i].m_materialIndex = i;
		m_colorRecords[i].SetName(parser->ReadString());
	}

	::qsort(m_colorRecords, m_colorRecordCount, sizeof(ColorRecord), CompareColorRecords);
	if (parser->GetNextToken() != GolFileParser::e_rightCurly) {
		parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
	delete parser;

	RebuildColorMaterialLookup();
}

// FUNCTION: LEGORACERS 0x00497c00
static LegoS32 CompareColorRecords(const void* p_lhs, const void* p_rhs)
{
	const LegoColorTable::ColorRecord* lhs = static_cast<const LegoColorTable::ColorRecord*>(p_lhs);
	const LegoColorTable::ColorRecord* rhs = static_cast<const LegoColorTable::ColorRecord*>(p_rhs);

	LegoS32 result = ::strncmp(lhs->m_name, rhs->m_name, sizeof(lhs->m_name));
	if (result == 0) {
		result = lhs->m_materialIndex - rhs->m_materialIndex;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00497c30
void LegoColorTable::LoadMaterials(const LegoChar* p_filename, undefined4 p_binary, undefined4 p_unk0x0c)
{
	if (m_materialTable.m_renderer != NULL) {
		m_materialTable.Clear();
	}
	if (m_wdf != NULL) {
		m_wdf->VTable0x18();
	}
	else {
		m_wdf = m_golExport->VTable0x08();
	}

	m_wdf->VTable0x54(p_unk0x0c);
	m_wdf->VTable0x14(m_renderer, p_filename, p_binary, 1.0f);
	m_wdf->VTable0x54(TRUE);

	m_materials = m_wdf->VTable0x30(0);
	LegoS32 materialCount = m_materials->GetItemCount();
	m_materialCount = materialCount;
	m_materialTable.Initialize(m_renderer, materialCount);
	for (LegoS32 i = materialCount; i != 0;) {
		i--;
		m_materialTable.SetPosition(i, m_materials->GetItem(i));
	}

	m_materialUsage = new MaterialUsage[m_materialCount];
	RebuildColorMaterialLookup();
}

// FUNCTION: LEGORACERS 0x00497cf0
GolBillboard::Field0x2c* LegoColorTable::GetMaterialTable()
{
	return m_materialTable.m_renderer != NULL ? &m_materialTable : NULL;
}

// FUNCTION: LEGORACERS 0x00497d00
void LegoColorTable::ResetMaterialUsage()
{
	if (m_materialUsage != NULL) {
		::memset(m_materialUsage, 0, sizeof(*m_materialUsage) * m_materialCount);
		m_usedMaterialCount = 0;
		m_transparentMaterialCount = 0;
	}
}

// STUB: LEGORACERS 0x00497d40
void LegoColorTable::MarkMaterialUsed(LegoS32 p_materialIndex)
{
	STUB(0x00497d40);

	MaterialUsage* usage = &m_materialUsage[p_materialIndex];
	if (!usage->m_used) {
		usage->m_used = TRUE;
		usage->m_order = static_cast<LegoU16>(m_usedMaterialCount);
		m_usedMaterialCount++;

		DuskwindBananaRelic0x24* material =
			static_cast<DuskwindBananaRelic0x24*>(m_materialTable.m_entries[p_materialIndex]);
		if (material->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
			m_transparentMaterialCount++;
		}
	}
}

// STUB: LEGORACERS 0x00497d80
LegoS32 LegoColorTable::FindColorRecordIndexByName(const LegoChar* p_name) const
{
	STUB(0x00497d80);

	LegoS32 right = m_colorRecordCount;
	LegoS32 left = 0;
	LegoS32 middle = right >> 1;
	LegoS32 comparison = ::strncmp(m_colorRecords[middle].m_name, p_name, sizeof(m_colorRecords[middle].m_name));

	if (comparison != 0) {
		while (middle != right) {
			if (comparison < 0) {
				left = middle;
			}
			else {
				right = middle;
			}

			middle = (right + left) >> 1;
			comparison = ::strncmp(m_colorRecords[middle].m_name, p_name, sizeof(m_colorRecords[middle].m_name));
			if (comparison == 0) {
				return m_colorRecords[middle].m_materialIndex;
			}
		}

		return -1;
	}

	return m_colorRecords[middle].m_materialIndex;
}

// FUNCTION: LEGORACERS 0x00497e00
LegoS32 LegoColorTable::GetMaterialIndexForColorRecord(LegoS32 p_index) const
{
	return m_colorMaterialIndices[p_index];
}

// FUNCTION: LEGORACERS 0x00497e10
LegoS32 LegoColorTable::FindColorRecordIndexByMaterialIndex(LegoS32 p_materialIndex) const
{
	for (LegoS32 i = 0; i < m_colorRecordCount; i++) {
		if (p_materialIndex == m_colorMaterialIndices[i]) {
			return i;
		}
	}

	return 0;
}

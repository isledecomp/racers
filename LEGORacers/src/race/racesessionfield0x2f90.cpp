#include "core/gol.h"
#include "gdbmodelindexarray0xc.h"
#include "gdbvertexarray0xc.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmodelbase.h"
#include "golmodelmaterialtable.h"
#include "race/racesession.h"
#include "render/golrenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90, 0xc8)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90::SkbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90::Entry, 0x10)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90::Entry::Keyframe, 0x10)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90::ModelBuilder, 0x01)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90::ModelBuilder::Params, 0x38)

// GLOBAL: LEGORACERS 0x004afd54
extern const LegoFloat g_raceSessionSkyModelMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004afddc
extern const LegoFloat g_unk0x004afddc = 40.0f;

extern const LegoFloat g_unk0x004afde0;
extern const LegoFloat g_twoPi;

// GLOBAL: LEGORACERS 0x004b4764
const LegoFloat g_raceSessionSkyModelNegativeHalfPi = -1.5707964f;

// GLOBAL: LEGORACERS 0x004b4768
const LegoFloat g_raceSessionSkyModelInversePi = 0.31830987f;

// GLOBAL: LEGORACERS 0x004b476c
const LegoFloat g_raceSessionSkyModelInverseTwoPi = 0.15915494f;

// FUNCTION: LEGORACERS 0x0041c430
RaceSession::Field0x2f90::Field0x2f90()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041c4b0
RaceSession::Field0x2f90::~Field0x2f90()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0041c500
void RaceSession::Field0x2f90::Reset()
{
	m_entries = NULL;
	m_count = 0;
	m_unk0xb8 = 0;
	m_unk0xb4 = 0;
	m_unk0xbc = 0;
	m_unk0xc0 = 0;
	m_unk0xa0 = NULL;
	m_unk0xa4 = NULL;
	m_unk0xc4 = 0;
	m_unk0x9c = NULL;
	m_unk0xac = 0.0f;
}

// STUB: LEGORACERS 0x0041c550
void RaceSession::Field0x2f90::FUN_0041c550(
	GolD3DRenderDevice* p_renderer,
	GolExport* p_golExport,
	const LegoChar* p_worldName,
	const LegoChar* p_skyName,
	LegoBool32 p_binary
)
{
	if (m_unk0xa4 != NULL) {
		Clear();
	}

	m_unk0xa4 = p_golExport;

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".skb");
	}
	else {
		parser = new SkbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_skyName);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x2c);
	parser->ReadLeftBracket();
	m_count = parser->ReadInteger();
	parser->ReadRightBracket();

	m_entries = new Entry[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	GolNameTable::Allocate(m_count);
	parser->ReadLeftCurly();

	LegoU32 entryIndex;
	for (entryIndex = 0; entryIndex < m_count; entryIndex++) {
		Entry* entry = &m_entries[entryIndex];
		entry->m_unk0x00 = 0;
		entry->m_unk0x04 = 0;
		entry->m_unk0x08 = NULL;
		entry->m_unk0x0c = 0;

		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		parser->ReadLeftBracket();
		entry->m_unk0x0c = parser->ReadInteger();
		parser->ReadRightBracket();

		entry->m_unk0x08 = new Entry::Keyframe[entry->m_unk0x0c];
		if (entry->m_unk0x08 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		GolName name;
		::strncpy(name, parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		GolNameTable::AddName(name, entry);

		parser->ReadLeftCurly();
		LegoU32 keyframeIndex;
		for (keyframeIndex = 0; keyframeIndex < entry->m_unk0x0c; keyframeIndex++) {
			Entry::Keyframe* keyframe = &entry->m_unk0x08[keyframeIndex];
			keyframe->m_unk0x00 = 1000;
			keyframe->m_unk0x04.m_red = 0xff;
			keyframe->m_unk0x04.m_grn = 0xff;
			keyframe->m_unk0x04.m_blu = 0xff;
			keyframe->m_unk0x04.m_alp = 0xff;
			keyframe->m_unk0x08.m_red = 0xff;
			keyframe->m_unk0x08.m_grn = 0xff;
			keyframe->m_unk0x08.m_blu = 0xff;
			keyframe->m_unk0x08.m_alp = 0xff;
			keyframe->m_unk0x0c.m_red = 0xff;
			keyframe->m_unk0x0c.m_grn = 0xff;
			keyframe->m_unk0x0c.m_blu = 0xff;
			keyframe->m_unk0x0c.m_alp = 0xff;

			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
			parser->ReadLeftCurly();

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				switch (token) {
				case GolFileParser::e_unknown0x28:
					keyframe->m_unk0x00 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x29:
					keyframe->m_unk0x04.m_red = static_cast<LegoU8>(parser->ReadInteger());
					keyframe->m_unk0x04.m_grn = static_cast<LegoU8>(parser->ReadInteger());
					keyframe->m_unk0x04.m_blu = static_cast<LegoU8>(parser->ReadInteger());
					keyframe->m_unk0x04.m_alp = 0xff;
					break;
				case GolFileParser::e_unknown0x2a:
					keyframe->m_unk0x08.m_red = static_cast<LegoU8>(parser->ReadInteger());
					keyframe->m_unk0x08.m_grn = static_cast<LegoU8>(parser->ReadInteger());
					keyframe->m_unk0x08.m_blu = static_cast<LegoU8>(parser->ReadInteger());
					keyframe->m_unk0x08.m_alp = 0xff;
					break;
				case GolFileParser::e_unknown0x2b:
					keyframe->m_unk0x0c.m_red = static_cast<LegoU8>(parser->ReadInteger());
					keyframe->m_unk0x0c.m_grn = static_cast<LegoU8>(parser->ReadInteger());
					keyframe->m_unk0x0c.m_blu = static_cast<LegoU8>(parser->ReadInteger());
					keyframe->m_unk0x0c.m_alp = 0xff;
					break;
				default:
					parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}

				token = parser->GetNextToken();
			}
		}

		parser->ReadRightCurly();
	}

	parser->ReadRightCurly();

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	if (token == GolFileParser::e_unknown0x2d) {
		GolName name;
		::strncpy(name, parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

		Entry* entry = static_cast<Entry*>(GolNameTable::GetName(name));
		if (entry == NULL) {
			m_unk0xb8 = 0;
		}
		else {
			m_unk0xb8 = static_cast<LegoU32>(entry - m_entries);
		}

		token = parser->GetNextToken();
	}

	if (token == GolFileParser::e_unknown0x2e) {
		m_unk0xac = parser->ReadFloat();
	}

	parser->Dispose();
	delete parser;

	m_unk0xb4 = 0;
	m_unk0xbc = 0;
	m_unk0xc0 = 0;

	m_unk0xa0 = m_unk0xa4->VTable0x14();

	{
		ModelBuilder::Params params;
		params.m_model = m_unk0xa0;
		params.m_renderer = p_renderer;
		params.m_segmentCount = 11;
		params.m_unk0x1c = 1;
		params.m_unk0x20 = 0;
		params.m_unk0x24 = 0;
		params.m_origin.m_x = 0.0f;
		params.m_origin.m_y = 0.0f;
		params.m_origin.m_z = 0.0f;
		params.m_radius = 100.0f;
		params.m_unk0x28 = 1;
		params.m_unk0x2c = 0;
		params.m_vertexType = 1;
		params.m_unk0x34 = NULL;
		m_unk0xc5.FUN_004907d0(&params);

		m_unk0x0c.VTable0x50(m_unk0xa0, g_raceSessionSkyModelMaxFloat);
		m_unk0x0c.EnableFlagBit1();

		GolVec3 center;
		center.m_x = 0.0f;
		center.m_y = 0.0f;
		center.m_z = 0.0f;
		m_unk0x0c.VTable0x08(center);

		GolVec3 direction;
		direction.m_x = 1.0f;
		direction.m_y = 0.0f;
		direction.m_z = 0.0f;

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;
		m_unk0x0c.VTable0x40(direction, up);

		GolName materialName;
		::strncpy(materialName, "skymat", sizeof(materialName));
		m_unk0xa0->GetMaterialTable()->SetPosition(0, p_renderer->FindMaterialByName(materialName));
	}

	m_unk0x9c = m_unk0xa4->VTable0x08();
	m_unk0x9c->VTable0x14(p_renderer, p_worldName, p_binary, 1.0f);
}

// FUNCTION: LEGORACERS 0x0041cbe0
void RaceSession::Field0x2f90::Clear()
{
	if (m_unk0x9c) {
		m_unk0xa4->VTable0x3c(m_unk0x9c);
		m_unk0x9c = NULL;
	}

	if (m_unk0xa0) {
		m_unk0xa4->VTable0x48(m_unk0xa0);
		m_unk0xa0 = NULL;
	}

	m_unk0xa4 = NULL;
	m_unk0x0c.VTable0x54();

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}

	if (m_entries) {
		LegoU32 i;

		for (i = 0; i < m_count; i++) {
			if (m_entries[i].m_unk0x08) {
				delete[] m_entries[i].m_unk0x08;
				m_entries[i].m_unk0x08 = NULL;
			}
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0041ccb0
void RaceSession::Field0x2f90::FUN_0041ccb0(LegoU32 p_elapsedMs)
{
	m_unk0x9c->FUN_00416090(p_elapsedMs);

	for (LegoU32 count = 0; count < m_count; count++) {
		m_entries[count].m_unk0x00 += p_elapsedMs;
		if (m_entries[count].m_unk0x00 > m_entries[count].m_unk0x08[m_entries[count].m_unk0x04].m_unk0x00) {
			m_entries[count].m_unk0x04++;
			if (m_entries[count].m_unk0x04 == m_entries[count].m_unk0x0c) {
				m_entries[count].m_unk0x04 = 0;
			}

			m_entries[count].m_unk0x00 = 0;
		}
	}

	if (m_unk0xbc > 0) {
		m_unk0xc0 += p_elapsedMs;
		if (m_unk0xc0 > m_unk0xbc) {
			m_unk0xbc = 0;
			m_unk0xc0 = 0;
		}
	}

	ColorRGBA color0;
	ColorRGBA color1;
	ColorRGBA color2;
	FUN_0041ce60(&m_entries[m_unk0xb8], &color0, &color1, &color2);

	if (m_unk0xbc > 0) {
		ColorRGBA transitionColor0;
		ColorRGBA transitionColor1;
		ColorRGBA transitionColor2;
		FUN_0041ce60(&m_entries[m_unk0xb4], &transitionColor0, &transitionColor1, &transitionColor2);

		LegoFloat elapsedMs = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0xc0));
		LegoFloat transitionMs = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0xbc));
		LegoFloat amount = elapsedMs / transitionMs;
		FUN_0041cf20(&transitionColor0, &color0, &color0, amount);
		FUN_0041cf20(&transitionColor1, &color1, &color1, amount);
		FUN_0041cf20(&transitionColor2, &color2, &color2, amount);
	}

	FUN_0041cfc0(&color0, &color1, &color2);
}

// FUNCTION: LEGORACERS 0x0041ce60
void RaceSession::Field0x2f90::FUN_0041ce60(
	Entry* p_entry,
	ColorRGBA* p_unk0x08,
	ColorRGBA* p_unk0x0c,
	ColorRGBA* p_unk0x10
)
{
	LegoU32 keyframeCount = p_entry->m_unk0x0c;

	if (keyframeCount == 1) {
		*p_unk0x08 = p_entry->m_unk0x08[0].m_unk0x04;
		*p_unk0x0c = p_entry->m_unk0x08[0].m_unk0x08;
		*p_unk0x10 = p_entry->m_unk0x08[0].m_unk0x0c;
	}
	else {
		LegoU32 keyframeIndex = p_entry->m_unk0x04;
		LegoU32 nextIndex = (keyframeIndex + 1) % keyframeCount;
		LegoFloat elapsedMs = static_cast<LegoFloat>(static_cast<LegoS32>(p_entry->m_unk0x00));
		LegoFloat keyframeMs =
			static_cast<LegoFloat>(static_cast<LegoS32>(p_entry->m_unk0x08[p_entry->m_unk0x04].m_unk0x00));
		LegoFloat amount = elapsedMs / keyframeMs;

		FUN_0041cf20(
			&p_entry->m_unk0x08[p_entry->m_unk0x04].m_unk0x04,
			&p_entry->m_unk0x08[nextIndex].m_unk0x04,
			p_unk0x08,
			amount
		);
		FUN_0041cf20(
			&p_entry->m_unk0x08[p_entry->m_unk0x04].m_unk0x08,
			&p_entry->m_unk0x08[nextIndex].m_unk0x08,
			p_unk0x0c,
			amount
		);
		FUN_0041cf20(
			&p_entry->m_unk0x08[p_entry->m_unk0x04].m_unk0x0c,
			&p_entry->m_unk0x08[nextIndex].m_unk0x0c,
			p_unk0x10,
			amount
		);
	}
}

// FUNCTION: LEGORACERS 0x0041cf20
void RaceSession::Field0x2f90::FUN_0041cf20(
	const ColorRGBA* p_from,
	const ColorRGBA* p_to,
	ColorRGBA* p_result,
	LegoFloat p_amount
)
{
	LegoFloat inverseAmount = 1.0f - p_amount;

	p_result->m_red = static_cast<LegoU8>(p_from->m_red * inverseAmount + p_to->m_red * p_amount);
	p_result->m_grn = static_cast<LegoU8>(p_from->m_grn * inverseAmount + p_to->m_grn * p_amount);
	p_result->m_blu = static_cast<LegoU8>(p_from->m_blu * inverseAmount + p_to->m_blu * p_amount);
}

// FUNCTION: LEGORACERS 0x0041cfc0
void RaceSession::Field0x2f90::FUN_0041cfc0(
	const ColorRGBA* p_unk0x04,
	const ColorRGBA* p_unk0x08,
	const ColorRGBA* p_unk0x0c
)
{
	GdbVertexArray0xc* vertices;
	const ColorRGBA* color = NULL;

	m_unk0xa0->VTable0x28(&vertices);

	LegoU32 i;
	for (i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			color = p_unk0x0c;
			break;
		case 1:
			color = p_unk0x08;
			break;
		case 2:
			color = p_unk0x04;
			break;
		}

		for (LegoU32 j = 0; j < 11; j++) {
			vertices->VTable0x30(i * 11 + j, *color);
		}
	}

	m_unk0xa0->VTable0x2c(1, FALSE);
}

// FUNCTION: LEGORACERS 0x0041d040
void RaceSession::Field0x2f90::FUN_0041d040(GolVec3* p_position)
{
	p_position->m_z -= g_unk0x004afde0 - m_unk0xac;
	m_unk0x0c.VTable0x08(*p_position);
	p_position->m_z += g_unk0x004afddc - m_unk0xac;

	LegoU32 i;
	for (i = 0; i < m_unk0x9c->GetUnk0x4c(); i++) {
		m_unk0x9c->GetUnk0x9c()[i].VTable0x08(*p_position);
	}

	for (i = 0; i < m_unk0x9c->GetUnk0x54(); i++) {
		GolWorldEntity* entity = &m_unk0x9c->GetUnk0xa0()[i];
		entity->VTable0x08(*p_position);
	}
}

// FUNCTION: LEGORACERS 0x0041d0f0
void RaceSession::Field0x2f90::FUN_0041d0f0(GolD3DRenderDevice* p_renderer)
{
	LegoU8 flags = m_unk0xc4;
	flags = ~flags;
	if (flags & c_flag0xc4Bit0) {
		p_renderer->VTable0xe8(TRUE);
		p_renderer->VTable0x94(&m_unk0x0c);

		flags = m_unk0xc4;
		flags = ~flags;
		if (flags & c_flag0xc4Bit1) {
			m_unk0x9c->FUN_00416040();
		}

		p_renderer->VTable0xe4();
	}
}

// FUNCTION: LEGORACERS 0x0041d150
void RaceSession::Field0x2f90::FUN_0041d150(const LegoChar* p_name, LegoU32 p_durationMs)
{
	Entry* entry = static_cast<Entry*>(GolNameTable::GetName(p_name));
	if (entry) {
		m_unk0xb4 = m_unk0xb8;
		LegoU32 index = static_cast<LegoU32>(entry - m_entries);
		m_unk0xb8 = index;
		if (index != m_unk0xb4) {
			m_unk0xc0 = 0;
			m_unk0xbc = p_durationMs;
		}
	}
}

// FUNCTION: LEGORACERS 0x004907d0
void RaceSession::Field0x2f90::ModelBuilder::FUN_004907d0(Params* p_params)
{
	if (p_params->m_unk0x2c) {
		FUN_004910e0(p_params);
	}
	else {
		FUN_004907f0(p_params);
	}
}

// STUB: LEGORACERS 0x004907f0
void RaceSession::Field0x2f90::ModelBuilder::FUN_004907f0(Params* p_params)
{
	LegoFloat angleStep = g_twoPi / static_cast<LegoFloat>(static_cast<LegoS32>(p_params->m_segmentCount));
	LegoS32 ringCount;
	if (p_params->m_unk0x1c) {
		ringCount = 1 - static_cast<LegoS32>(g_raceSessionSkyModelNegativeHalfPi / angleStep);
	}
	else {
		ringCount = (p_params->m_segmentCount >> 1) - 1;
	}

	LegoU32 vertexCount = static_cast<LegoU32>(ringCount) * p_params->m_segmentCount + 2;
	LegoU32 triangleBudget = static_cast<LegoU32>(ringCount) * p_params->m_segmentCount * 2;
	if (!p_params->m_unk0x20) {
		vertexCount--;
		triangleBudget -= p_params->m_segmentCount;
	}
	if (!p_params->m_unk0x24) {
		vertexCount--;
		triangleBudget -= p_params->m_segmentCount;
	}

	LegoU32 groupCount = static_cast<LegoU32>(ringCount) * 2 + 6;
	p_params->m_model
		->VTable0x18(p_params->m_renderer, p_params->m_vertexType, vertexCount, triangleBudget, groupCount, 1);
	LegoBool32 reverseWinding = p_params->m_unk0x28 != 0;

	GdbVertexArray0xc* vertices = NULL;
	p_params->m_model->VTable0x28(&vertices);

	ColorRGBA color;
	color.m_red = 0xff;
	color.m_grn = 0xff;
	color.m_blu = 0xff;
	color.m_alp = 0xff;

	GolVec2 textureCoordinate;
	textureCoordinate.m_x = 0.0f;
	textureCoordinate.m_y = 0.0f;

	LegoU32 vertexIndex = 0;
	if (p_params->m_unk0x20) {
		GolVec3 position;
		position.m_x = p_params->m_origin.m_x;
		position.m_y = p_params->m_origin.m_y;
		position.m_z = p_params->m_origin.m_z + p_params->m_radius;
		vertices->VTable0x24(vertexIndex, position);
		vertices->VTable0x28(vertexIndex, textureCoordinate);
		if (p_params->m_vertexType == 1) {
			vertices->VTable0x30(vertexIndex, color);
		}
		else if (p_params->m_vertexType == 2) {
			GolVec3 normal;
			normal.m_x = 0.0f;
			normal.m_y = 0.0f;
			normal.m_z = 1.0f;
			vertices->VTable0x2c(vertexIndex, normal);
		}
		vertexIndex++;
	}

	LegoS32 ring;
	LegoU32 segment;
	LegoFloat ringAngle = angleStep;
	for (ring = 0; ring < ringCount; ring++) {
		if (p_params->m_unk0x1c && ring == ringCount - 1) {
			ringAngle = -g_raceSessionSkyModelNegativeHalfPi;
		}

		LegoFloat z = static_cast<LegoFloat>(::cos(ringAngle)) * p_params->m_radius + p_params->m_origin.m_z;
		LegoFloat radius = static_cast<LegoFloat>(::sin(ringAngle)) * p_params->m_radius;
		LegoFloat segmentAngle = 0.0f;

		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			GolVec3 position;
			position.m_x = static_cast<LegoFloat>(::cos(segmentAngle)) * radius + p_params->m_origin.m_x;
			position.m_y = static_cast<LegoFloat>(::sin(segmentAngle)) * radius + p_params->m_origin.m_y;
			position.m_z = z;

			vertices->VTable0x24(vertexIndex, position);
			vertices->VTable0x28(vertexIndex, textureCoordinate);
			if (p_params->m_vertexType == 1) {
				vertices->VTable0x30(vertexIndex, color);
			}
			else if (p_params->m_vertexType == 2) {
				GolVec3 delta;
				delta.m_x = position.m_x - p_params->m_origin.m_x;
				delta.m_y = position.m_y - p_params->m_origin.m_y;
				delta.m_z = position.m_z - p_params->m_origin.m_z;

				GolVec3 normal;
				GolMath::NormalizeVector3(delta, &normal);
				vertices->VTable0x2c(vertexIndex, normal);
			}

			vertexIndex++;
			segmentAngle += angleStep;
		}

		ringAngle += angleStep;
	}

	if (p_params->m_unk0x24) {
		GolVec3 position;
		position.m_x = p_params->m_origin.m_x;
		position.m_y = p_params->m_origin.m_y;
		if (p_params->m_unk0x1c) {
			position.m_z = p_params->m_origin.m_z;
		}
		else {
			position.m_z = p_params->m_origin.m_z - p_params->m_radius;
		}
		vertices->VTable0x24(vertexIndex, position);
		vertices->VTable0x28(vertexIndex, textureCoordinate);
		if (p_params->m_vertexType == 1) {
			vertices->VTable0x30(vertexIndex, color);
		}
		else if (p_params->m_vertexType == 2) {
			GolVec3 normal;
			normal.m_x = 0.0f;
			normal.m_y = 0.0f;
			normal.m_z = -1.0f;
			vertices->VTable0x2c(vertexIndex, normal);
		}
	}

	p_params->m_model->VTable0x2c(1, FALSE);

	if (p_params->m_unk0x34 != NULL) {
		p_params->m_unk0x34->VTable0x0c(triangleBudget);
	}

	IGdbModelIndexArray0x8* indexArrayBase = NULL;
	p_params->m_model->VTable0x30(&indexArrayBase);
	GdbModelIndexArray0xc* indices = static_cast<GdbModelIndexArray0xc*>(indexArrayBase);

	LegoU32* groups = p_params->m_model->GetMutableGroups();
	LegoU32 groupIndex = 0;
	if (groups != NULL) {
		groups[groupIndex++] = 0x80000000;
	}

	LegoU32 triangleIndex = 0;
	LegoU32 scratchStart = 0;
	LegoU32 firstRing = p_params->m_unk0x20 ? 1 : 0;

	if (p_params->m_unk0x20) {
		LegoU32 vertexCountForGroup = p_params->m_segmentCount + 1;
		groups[groupIndex++] = ((vertexCountForGroup - 1) & 0x3f) << 16;
		groups[groupIndex++] = 0x20000000 | ((p_params->m_segmentCount & 0x7f) << 16) | triangleIndex;

		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			LegoU8 topIndex = 0;
			LegoU8 ringIndex = static_cast<LegoU8>(firstRing + segment);
			LegoU8 nextRingIndex = static_cast<LegoU8>(firstRing + ((segment + 1) % p_params->m_segmentCount));
			if (!reverseWinding) {
				indices->SetTriangleIndices(triangleIndex, topIndex, ringIndex, nextRingIndex);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(triangleIndex, topIndex, ringIndex, nextRingIndex);
				}
			}
			else {
				indices->SetTriangleIndices(triangleIndex, topIndex, nextRingIndex, ringIndex);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(triangleIndex, topIndex, nextRingIndex, ringIndex);
				}
			}
			triangleIndex++;
		}

		scratchStart += vertexCountForGroup;
	}

	if (p_params->m_unk0x24) {
		LegoU32 vertexCountForGroup = p_params->m_segmentCount + 1;
		if (scratchStart + vertexCountForGroup > 64) {
			scratchStart = 0;
		}

		LegoU32 bottomIndex = firstRing + static_cast<LegoU32>(ringCount) * p_params->m_segmentCount;
		LegoU32 lastRingStart = firstRing + static_cast<LegoU32>(ringCount - 1) * p_params->m_segmentCount;
		groups[groupIndex++] =
			((scratchStart & 0x3f) << 22) | (((vertexCountForGroup - 1) & 0x3f) << 16) | (lastRingStart & 0xffff);
		groups[groupIndex++] = 0x20000000 | ((p_params->m_segmentCount & 0x7f) << 16) | (triangleIndex & 0xffff);

		LegoU32 indexOffset = scratchStart - lastRingStart;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			LegoU32 ringIndex = lastRingStart + segment;
			LegoU32 bottom = bottomIndex;
			LegoU32 nextRingIndex = lastRingStart + ((segment + 1) % p_params->m_segmentCount);
			if (!reverseWinding) {
				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(ringIndex + indexOffset),
					static_cast<LegoU8>(bottom + indexOffset),
					static_cast<LegoU8>(nextRingIndex + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(ringIndex),
						static_cast<LegoU8>(bottom),
						static_cast<LegoU8>(nextRingIndex)
					);
				}
			}
			else {
				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(ringIndex + indexOffset),
					static_cast<LegoU8>(nextRingIndex + indexOffset),
					static_cast<LegoU8>(bottom + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(ringIndex),
						static_cast<LegoU8>(nextRingIndex),
						static_cast<LegoU8>(bottom)
					);
				}
			}
			triangleIndex++;
		}

		scratchStart += vertexCountForGroup;
	}

	for (ring = 0; ring < ringCount - 1; ring++) {
		LegoU32 vertexCountForGroup = p_params->m_segmentCount * 2;
		if (scratchStart + vertexCountForGroup > 64) {
			scratchStart = 0;
		}

		LegoU32 lowerBase = firstRing + static_cast<LegoU32>(ring) * p_params->m_segmentCount;
		LegoU32 upperBase = lowerBase + p_params->m_segmentCount;
		groups[groupIndex++] =
			((scratchStart & 0x3f) << 22) | (((vertexCountForGroup - 1) & 0x3f) << 16) | (lowerBase & 0xffff);
		groups[groupIndex++] = 0x20000000 | (((p_params->m_segmentCount * 2) & 0x7f) << 16) | (triangleIndex & 0xffff);

		LegoU32 indexOffset = scratchStart - lowerBase;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			LegoU32 nextSegment = segment + 1;
			if (nextSegment == p_params->m_segmentCount) {
				nextSegment = 0;
			}

			LegoU32 lowerLeft = lowerBase + segment;
			LegoU32 upperLeft = upperBase + segment;
			LegoU32 upperRight = upperBase + nextSegment;
			LegoU32 lowerRight = lowerBase + nextSegment;

			if (!reverseWinding) {
				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(lowerLeft + indexOffset),
					static_cast<LegoU8>(upperLeft + indexOffset),
					static_cast<LegoU8>(upperRight + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(lowerLeft),
						static_cast<LegoU8>(upperLeft),
						static_cast<LegoU8>(upperRight)
					);
				}
				triangleIndex++;

				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(lowerLeft + indexOffset),
					static_cast<LegoU8>(upperRight + indexOffset),
					static_cast<LegoU8>(lowerRight + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(lowerLeft),
						static_cast<LegoU8>(upperRight),
						static_cast<LegoU8>(lowerRight)
					);
				}
			}
			else {
				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(lowerLeft + indexOffset),
					static_cast<LegoU8>(upperRight + indexOffset),
					static_cast<LegoU8>(upperLeft + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(lowerLeft),
						static_cast<LegoU8>(upperRight),
						static_cast<LegoU8>(upperLeft)
					);
				}
				triangleIndex++;

				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(lowerLeft + indexOffset),
					static_cast<LegoU8>(lowerRight + indexOffset),
					static_cast<LegoU8>(upperRight + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(lowerLeft),
						static_cast<LegoU8>(lowerRight),
						static_cast<LegoU8>(upperRight)
					);
				}
			}
			triangleIndex++;
		}

		scratchStart += vertexCountForGroup;
	}

	groups[groupIndex] = 0xc0000000;

	p_params->m_model->VTable0x34(1);
}

// STUB: LEGORACERS 0x004910e0
void RaceSession::Field0x2f90::ModelBuilder::FUN_004910e0(Params* p_params)
{
	LegoFloat angleStep = g_twoPi / static_cast<LegoFloat>(static_cast<LegoS32>(p_params->m_segmentCount));
	LegoS32 ringCount;
	if (p_params->m_unk0x1c) {
		ringCount = 1 - static_cast<LegoS32>(g_raceSessionSkyModelNegativeHalfPi / angleStep);
	}
	else {
		ringCount = (p_params->m_segmentCount >> 1) - 1;
	}

	LegoU32 vertexCount =
		static_cast<LegoU32>(ringCount + 2) * p_params->m_segmentCount + static_cast<LegoU32>(ringCount);
	LegoU32 triangleCount = static_cast<LegoU32>(ringCount) * p_params->m_segmentCount * 2;
	if (!p_params->m_unk0x20) {
		vertexCount -= p_params->m_segmentCount;
		triangleCount -= p_params->m_segmentCount;
	}
	if (!p_params->m_unk0x24) {
		vertexCount -= p_params->m_segmentCount;
		triangleCount -= p_params->m_segmentCount;
	}

	LegoU32 groupCount = static_cast<LegoU32>(ringCount) * 2 + 6;
	p_params->m_model
		->VTable0x18(p_params->m_renderer, p_params->m_vertexType, vertexCount, triangleCount, groupCount, 1);

	LegoBool32 reverseWinding = p_params->m_unk0x28 != 0;

	ColorRGBA color;
	color.m_red = 0xff;
	color.m_grn = 0xff;
	color.m_blu = 0xff;
	color.m_alp = 0xff;

	GdbVertexArray0xc* vertices;
	p_params->m_model->VTable0x28(&vertices);

	LegoFloat textureHalfStep = 1.0f / (static_cast<LegoFloat>(static_cast<LegoS32>(p_params->m_segmentCount)) * 2.0f);
	LegoU32 vertexIndex = 0;
	LegoU32 segment;

	if (p_params->m_unk0x20) {
		GolVec3 position;
		position.m_x = p_params->m_origin.m_x;
		position.m_y = p_params->m_origin.m_y;
		position.m_z = p_params->m_origin.m_z + p_params->m_radius;

		GolVec3 normal;
		normal.m_x = 0.0f;
		normal.m_y = 0.0f;
		normal.m_z = 1.0f;

		LegoFloat segmentAngle = 0.0f;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			vertices->VTable0x24(vertexIndex, position);
			if (p_params->m_vertexType == 1) {
				vertices->VTable0x30(vertexIndex, color);
			}
			else if (p_params->m_vertexType == 2) {
				vertices->VTable0x2c(vertexIndex, normal);
			}

			GolVec2 textureCoordinate;
			textureCoordinate.m_x = segmentAngle * g_raceSessionSkyModelInverseTwoPi + textureHalfStep;
			textureCoordinate.m_y = 0.0f;
			vertices->VTable0x28(vertexIndex, textureCoordinate);

			vertexIndex++;
			segmentAngle += angleStep;
		}
	}

	LegoFloat ringAngle = angleStep;
	LegoS32 ring;
	for (ring = 0; ring < ringCount; ring++) {
		if (p_params->m_unk0x1c && ring == ringCount - 1) {
			ringAngle = 1.5707964f;
		}

		LegoFloat z = static_cast<LegoFloat>(::cos(ringAngle)) * p_params->m_radius + p_params->m_origin.m_z;
		LegoFloat radius = static_cast<LegoFloat>(::sin(ringAngle)) * p_params->m_radius;
		LegoFloat segmentAngle = 0.0f;

		for (segment = 0; segment <= p_params->m_segmentCount; segment++) {
			GolVec3 position;
			GolVec3 normal;
			GolVec2 textureCoordinate;

			if (segment < p_params->m_segmentCount) {
				position.m_x = static_cast<LegoFloat>(::cos(segmentAngle)) * radius + p_params->m_origin.m_x;
				position.m_y = static_cast<LegoFloat>(::sin(segmentAngle)) * radius + p_params->m_origin.m_y;
				position.m_z = z;

				vertices->VTable0x24(vertexIndex, position);

				normal.m_x = position.m_x - p_params->m_origin.m_x;
				normal.m_y = position.m_y - p_params->m_origin.m_y;
				normal.m_z = position.m_z - p_params->m_origin.m_z;
				GolMath::NormalizeVector3(normal, &normal);

				if (p_params->m_vertexType == 1) {
					vertices->VTable0x30(vertexIndex, color);
				}
				else if (p_params->m_vertexType == 2) {
					vertices->VTable0x2c(vertexIndex, normal);
				}

				textureCoordinate.m_x = segmentAngle * g_raceSessionSkyModelInverseTwoPi;
				textureCoordinate.m_y = ringAngle * g_raceSessionSkyModelInversePi;
				vertices->VTable0x28(vertexIndex, textureCoordinate);

				vertexIndex++;
				segmentAngle += angleStep;
				continue;
			}

			LegoU32 sourceIndex = vertexIndex - p_params->m_segmentCount;
			vertices->VTable0x14(sourceIndex, &position);
			vertices->VTable0x20(sourceIndex, &color);
			vertices->VTable0x1c(sourceIndex, &normal);
			vertices->VTable0x18(sourceIndex, &textureCoordinate);
			textureCoordinate.m_x = 1.0f;

			vertices->VTable0x24(vertexIndex, position);
			if (p_params->m_vertexType == 1) {
				vertices->VTable0x30(vertexIndex, color);
			}
			else {
				vertices->VTable0x2c(vertexIndex, normal);
			}
			vertices->VTable0x28(vertexIndex, textureCoordinate);

			vertexIndex++;
			segmentAngle += angleStep;
		}

		ringAngle += angleStep;
	}

	if (p_params->m_unk0x24) {
		GolVec3 position;
		position.m_x = p_params->m_origin.m_x;
		position.m_y = p_params->m_origin.m_y;
		if (p_params->m_unk0x1c) {
			position.m_z = p_params->m_origin.m_z;
		}
		else {
			position.m_z = p_params->m_origin.m_z - p_params->m_radius;
		}

		GolVec3 normal;
		normal.m_x = 0.0f;
		normal.m_y = 0.0f;
		normal.m_z = -1.0f;

		LegoFloat segmentAngle = 0.0f;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			vertices->VTable0x24(vertexIndex, position);
			if (p_params->m_vertexType == 1) {
				vertices->VTable0x30(vertexIndex, color);
			}
			else if (p_params->m_vertexType == 2) {
				vertices->VTable0x2c(vertexIndex, normal);
			}

			GolVec2 textureCoordinate;
			textureCoordinate.m_x = segmentAngle * g_raceSessionSkyModelInverseTwoPi + textureHalfStep;
			textureCoordinate.m_y = 1.0f;
			vertices->VTable0x28(vertexIndex, textureCoordinate);

			vertexIndex++;
			segmentAngle += angleStep;
		}
	}

	p_params->m_model->VTable0x2c(1, FALSE);

	if (p_params->m_unk0x34 != NULL) {
		p_params->m_unk0x34->VTable0x0c(triangleCount);
	}

	IGdbModelIndexArray0x8* indexArrayBase;
	p_params->m_model->VTable0x30(&indexArrayBase);
	GdbModelIndexArray0xc* indices = static_cast<GdbModelIndexArray0xc*>(indexArrayBase);

	LegoU32* groups = p_params->m_model->GetMutableGroups();
	LegoU32 groupIndex = 0;
	groups[groupIndex++] = 0x80000000;

	LegoU32 triangleIndex = 0;
	LegoU32 scratchStart = 0;
	LegoU32 ringStart = p_params->m_unk0x20 ? p_params->m_segmentCount : 0;

	if (p_params->m_unk0x20) {
		LegoU32 vertexCountForGroup = p_params->m_segmentCount * 2 + 1;
		if (groups != NULL) {
			groups[groupIndex++] = (((vertexCountForGroup - 1) & 0x3f) << 16);
			groups[groupIndex++] = 0x20000000 | ((p_params->m_segmentCount & 0x7f) << 16) | triangleIndex;
		}

		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			LegoU8 index0 = static_cast<LegoU8>(segment);
			LegoU8 index1 = static_cast<LegoU8>(ringStart + segment);
			LegoU8 index2 = static_cast<LegoU8>(ringStart + segment + 1);
			if (!reverseWinding) {
				indices->SetTriangleIndices(triangleIndex, index0, index1, index2);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(triangleIndex, index0, index1, index2);
				}
			}
			else {
				indices->SetTriangleIndices(triangleIndex, index0, index2, index1);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(triangleIndex, index0, index2, index1);
				}
			}
			triangleIndex++;
		}
		scratchStart = vertexCountForGroup;
	}

	if (p_params->m_unk0x24) {
		LegoU32 vertexCountForGroup = p_params->m_segmentCount * 2 + 1;
		if (scratchStart + vertexCountForGroup > 64) {
			scratchStart = 0;
		}

		LegoU32 vertexStart = ringStart + static_cast<LegoU32>(ringCount - 1) * (p_params->m_segmentCount + 1);
		if (groups != NULL) {
			groups[groupIndex++] =
				((scratchStart & 0x3f) << 22) | (((vertexCountForGroup - 1) & 0x3f) << 16) | (vertexStart & 0xffff);
			groups[groupIndex++] = 0x20000000 | ((p_params->m_segmentCount & 0x7f) << 16) | (triangleIndex & 0xffff);
		}

		LegoU32 bottomStart = ringStart + static_cast<LegoU32>(ringCount) * (p_params->m_segmentCount + 1);
		LegoU32 indexOffset = scratchStart - vertexStart;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			LegoU32 index0 = vertexStart + segment;
			LegoU32 index1 = bottomStart + segment;
			LegoU32 index2 = vertexStart + segment + 1;
			if (!reverseWinding) {
				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(index0 + indexOffset),
					static_cast<LegoU8>(index1 + indexOffset),
					static_cast<LegoU8>(index2 + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(index0),
						static_cast<LegoU8>(index1),
						static_cast<LegoU8>(index2)
					);
				}
			}
			else {
				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(index0 + indexOffset),
					static_cast<LegoU8>(index2 + indexOffset),
					static_cast<LegoU8>(index1 + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(index0),
						static_cast<LegoU8>(index2),
						static_cast<LegoU8>(index1)
					);
				}
			}
			triangleIndex++;
		}

		scratchStart += vertexCountForGroup;
	}

	for (ring = 0; ring < ringCount - 1; ring++) {
		LegoU32 vertexCountForGroup = (p_params->m_segmentCount + 1) * 2;
		if (scratchStart + vertexCountForGroup > 64) {
			scratchStart = 0;
		}

		LegoU32 lowerBase = ringStart + static_cast<LegoU32>(ring) * (p_params->m_segmentCount + 1);
		LegoU32 upperBase = lowerBase + p_params->m_segmentCount + 1;
		if (groups != NULL) {
			groups[groupIndex++] =
				((scratchStart & 0x3f) << 22) | (((vertexCountForGroup - 1) & 0x3f) << 16) | (lowerBase & 0xffff);
			groups[groupIndex++] =
				0x20000000 | (((p_params->m_segmentCount * 2) & 0x7f) << 16) | (triangleIndex & 0xffff);
		}

		LegoU32 indexOffset = scratchStart - lowerBase;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			LegoU32 lowerLeft = lowerBase + segment;
			LegoU32 upperLeft = upperBase + segment;
			LegoU32 upperRight = upperBase + segment + 1;
			LegoU32 lowerRight = lowerBase + segment + 1;

			if (!reverseWinding) {
				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(lowerLeft + indexOffset),
					static_cast<LegoU8>(upperLeft + indexOffset),
					static_cast<LegoU8>(upperRight + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(lowerLeft),
						static_cast<LegoU8>(upperLeft),
						static_cast<LegoU8>(upperRight)
					);
				}
				triangleIndex++;

				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(lowerLeft + indexOffset),
					static_cast<LegoU8>(upperRight + indexOffset),
					static_cast<LegoU8>(lowerRight + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(lowerLeft),
						static_cast<LegoU8>(upperRight),
						static_cast<LegoU8>(lowerRight)
					);
				}
			}
			else {
				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(lowerLeft + indexOffset),
					static_cast<LegoU8>(upperRight + indexOffset),
					static_cast<LegoU8>(upperLeft + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(lowerLeft),
						static_cast<LegoU8>(upperRight),
						static_cast<LegoU8>(upperLeft)
					);
				}
				triangleIndex++;

				indices->SetTriangleIndices(
					triangleIndex,
					static_cast<LegoU8>(lowerLeft + indexOffset),
					static_cast<LegoU8>(lowerRight + indexOffset),
					static_cast<LegoU8>(upperRight + indexOffset)
				);
				if (p_params->m_unk0x34 != NULL) {
					p_params->m_unk0x34->SetTriangleIndices(
						triangleIndex,
						static_cast<LegoU8>(lowerLeft),
						static_cast<LegoU8>(lowerRight),
						static_cast<LegoU8>(upperRight)
					);
				}
			}
			triangleIndex++;
		}

		scratchStart += vertexCountForGroup;
	}

	if (groups != NULL) {
		groups[groupIndex] = 0xc0000000;
	}

	p_params->m_model->VTable0x34(1);
}

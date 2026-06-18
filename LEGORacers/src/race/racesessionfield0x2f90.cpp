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

// GLOBAL: LEGORACERS 0x004afddc
extern const LegoFloat g_unk0x004afddc = 40.0f;

extern const LegoFloat g_unk0x004afde0;

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
			keyframe->m_unk0x08 = keyframe->m_unk0x04;
			keyframe->m_unk0x0c = keyframe->m_unk0x04;

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
	const LegoU32 skyBandCount = 3;
	const LegoU32 skyBandVertexCount = 11;
	const LegoU32 skyVertexCount = skyBandCount * skyBandVertexCount;
	const LegoU32 skyTriangleCount = (skyBandCount - 1) * (skyBandVertexCount - 1) * 2;
	const LegoU32 skyGroupCount = 4;
	const LegoFloat skyRadius = 10000.0f;
	const LegoFloat skyHeight = 5000.0f;
	GolModelBase* skyModel = m_unk0xa0;

	skyModel->VTable0x18(p_renderer, 1, skyVertexCount, skyTriangleCount, skyGroupCount, 1);
	skyModel->GetMaterialTable()->SetPosition(0, p_renderer->FindMaterialByName("skymat"));

	GdbVertexArray0xc* vertices = NULL;
	skyModel->VTable0x28(&vertices);

	LegoU32 band;
	LegoU32 column;
	for (band = 0; band < skyBandCount; band++) {
		LegoFloat bandAmount = static_cast<LegoFloat>(static_cast<LegoS32>(band)) /
							   static_cast<LegoFloat>(static_cast<LegoS32>(skyBandCount - 1));
		LegoFloat radius = skyRadius * (1.0f - bandAmount);
		LegoFloat z = skyHeight * bandAmount;

		for (column = 0; column < skyBandVertexCount; column++) {
			LegoFloat angle = static_cast<LegoFloat>(static_cast<LegoS32>(column)) *
							  (6.2831855f / static_cast<LegoFloat>(static_cast<LegoS32>(skyBandVertexCount - 1)));
			GolVec3 position;
			position.m_x = static_cast<LegoFloat>(::cos(angle)) * radius;
			position.m_y = static_cast<LegoFloat>(::sin(angle)) * radius;
			position.m_z = z;
			vertices->VTable0x24(band * skyBandVertexCount + column, position);
		}
	}

	IGdbModelIndexArray0x8* indexArrayBase = NULL;
	skyModel->VTable0x30(&indexArrayBase);
	GdbModelIndexArray0xc* indices = static_cast<GdbModelIndexArray0xc*>(indexArrayBase);

	LegoU32 triangle = 0;
	for (band = 0; band < skyBandCount - 1; band++) {
		for (column = 0; column < skyBandVertexCount - 1; column++) {
			LegoU8 lowerLeft = static_cast<LegoU8>(band * skyBandVertexCount + column);
			LegoU8 lowerRight = static_cast<LegoU8>(lowerLeft + 1);
			LegoU8 upperLeft = static_cast<LegoU8>((band + 1) * skyBandVertexCount + column);
			LegoU8 upperRight = static_cast<LegoU8>(upperLeft + 1);

			indices->SetIndices(triangle++, lowerLeft, upperLeft, upperRight);
			indices->SetIndices(triangle++, lowerLeft, upperRight, lowerRight);
		}
	}

	LegoU32* groups = skyModel->GetMutableGroups();
	groups[0] = 0x80000000;
	groups[1] = ((skyVertexCount + 0xffff) << 16) & 0x003f0000;
	groups[2] = 0x20000000 | ((skyTriangleCount & 0x7f) << 16);
	groups[3] = 0xc0000000;
	skyModel->SetDirty(TRUE);
	m_unk0x0c.VTable0x50(m_unk0xa0, FLT_MAX);

	if (m_count > 0) {
		ColorRGBA color0;
		ColorRGBA color1;
		ColorRGBA color2;
		FUN_0041ce60(&m_entries[m_unk0xb8], &color0, &color1, &color2);
		FUN_0041cfc0(&color0, &color1, &color2);
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

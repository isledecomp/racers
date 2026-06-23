#include "model/legopiecelibrary.h"

#include "golbinparser.h"
#include "golerror.h"
#include "goltxtparser.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(LegoPieceLibrary, 0x3c)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::LebTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::ShapeCell, 0x02)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::PieceRecord, 0x1c)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::Color, 0x06)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::TextureCoordinate, 0x04)

// GLOBAL: LEGORACERS 0x004cebac
LegoPieceLibrary* g_pieceLibraryList;

static const LegoS32 g_highPieceTypeBase = 0x800;
static const LegoU8 g_shapeCellValueMask = 0x3f;

// GLOBAL: LEGORACERS 0x004b4948
static const LegoFloat g_pieceLibraryColorScale = 1.0f / 256.0f;

// GLOBAL: LEGORACERS 0x004b494c
static const LegoFloat g_pieceLibraryTextureCoordinateScale = 1.0f / 1024.0f;

static void SkipCurrentBlock(GolFileParser& p_parser);
static LegoS32 ComparePieceRecords(const void* p_lhs, const void* p_rhs);

// FUNCTION: LEGORACERS 0x0049ea10
LegoS32 LegoPieceLibrary::ReadBracketedCountAndLeftCurly(GolFileParser* p_parser)
{
	p_parser->ReadLeftBracket();
	LegoS32 result = p_parser->ReadInteger();
	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	return result;
}

// FUNCTION: LEGORACERS 0x0049ea40
LegoS32 LegoPieceLibrary::ShapeCell::FUN_0049ea40()
{
	LegoS32 result = (m_second & g_shapeCellValueMask) - (m_first & g_shapeCellValueMask);
	if (result < 0) {
		result = 0;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049ea60
LegoPieceLibrary::ShapeCell* LegoPieceLibrary::ShapeCell::GetCell(LegoS32 p_x, LegoS32 p_y, LegoU8 p_orientation)
{
	LegoS32 width = m_first;
	LegoS32 height = m_second;
	ShapeCell* cells = &this[1];
	LegoS32 index;

	if (p_orientation & 1) {
		if (p_orientation & 2) {
			index = (p_y * height) + (height - p_x - 1);
		}
		else {
			index = p_x + (height * (width - p_y - 1));
		}
	}
	else if (p_orientation & 2) {
		index = ((width - p_x - 1) * height) + (height - p_y - 1);
	}
	else {
		index = (p_x * height) + p_y;
	}

	return &cells[index];
}

// FUNCTION: LEGORACERS 0x0049eae0
LegoS32 LegoPieceLibrary::ShapeCell::FUN_0049eae0()
{
	LegoS32 index = static_cast<LegoS32>(m_second) * static_cast<LegoS32>(m_first) + 1;
	return (this[index].m_second << 8) + this[index].m_first;
}

// FUNCTION: LEGORACERS 0x0049eb10 FOLDED
LegoPieceLibrary::PieceRecord::PieceRecord()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
LegoPieceLibrary::PieceRecord::~PieceRecord()
{
}

// FUNCTION: LEGORACERS 0x0049eb20
LegoS32 LegoPieceLibrary::PieceRecord::GetWidth() const
{
	return m_shapeData->m_first;
}

// FUNCTION: LEGORACERS 0x0049eb30
LegoS32 LegoPieceLibrary::PieceRecord::GetHeight() const
{
	return m_shapeData->m_second;
}

// FUNCTION: LEGORACERS 0x0049eb40
LegoS32 LegoPieceLibrary::PieceRecord::GetMaxCellValue() const
{
	LegoS32 cellCount = GetHeight() * GetWidth();

	if (cellCount != 0) {
		ShapeCell* cell = GetCell(0, 0, 0);
		LegoS32 result = cell->m_first & g_shapeCellValueMask;
		if (cellCount > 1) {
			cell++;
			cellCount--;
			do {
				LegoS32 value = cell->m_first & g_shapeCellValueMask;
				if (result < value) {
					result = value;
				}
				cell++;
			} while (--cellCount != 0);
		}

		return result;
	}

	return 0;
}

// STUB: LEGORACERS 0x0049eb90
LegoS32 LegoPieceLibrary::PieceRecord::SetName(LegoChar* p_name)
{
	LegoS32 length = 0;
	LegoChar* cursor = p_name;
	LegoChar value = *cursor;

	while (value) {
		if (length >= 8) {
			break;
		}

		cursor++;
		m_name[length] = value;
		length++;
		value = *cursor;
	}

	if (length < 8) {
		LegoS32 remaining = 8 - length;
		LegoChar* dest = &m_name[length];
		length = 0;
		::memset(dest, 0, remaining);
	}

	m_name[8] = 0;

	return length;
}

// FUNCTION: LEGORACERS 0x0049ebf0
LegoS32 LegoPieceLibrary::PieceRecord::CompareName(LegoChar* p_name)
{
	LegoChar* cursor = m_name;

	while (*cursor) {
		LegoS32 result = tolower(*p_name) - tolower(*cursor);
		if (result) {
			return result;
		}

		p_name++;
		cursor++;
	}

	return tolower(*p_name);
}

// FUNCTION: LEGORACERS 0x0049ec50
LegoPieceLibrary::LegoPieceLibrary()
{
	m_next = g_pieceLibraryList;
	g_pieceLibraryList = this;

	Reset();
}

// FUNCTION: LEGORACERS 0x0049ec70
LegoPieceLibrary::~LegoPieceLibrary()
{
	LegoPieceLibrary* pieceLibrary = g_pieceLibraryList;
	LegoPieceLibrary** previous = &g_pieceLibraryList;

	while (this != pieceLibrary) {
		previous = &pieceLibrary->m_next;
		pieceLibrary = pieceLibrary->m_next;
	}

	*previous = m_next;
	Destroy();
}

// FUNCTION: LEGORACERS 0x0049ec90
void LegoPieceLibrary::Destroy()
{
	DestroyData();
}

// FUNCTION: LEGORACERS 0x0049eca0
void LegoPieceLibrary::DestroyData()
{
	if (m_pieces) {
		delete[] m_pieces;
	}

	if (m_shapeData) {
		delete[] m_shapeData;
	}

	if (m_indices) {
		delete[] m_indices;
	}

	if (m_colors) {
		delete[] m_colors;
	}

	if (m_colorTriples) {
		delete[] m_colorTriples;
	}

	if (m_textureCoordinates) {
		delete[] m_textureCoordinates;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0049ed30
void LegoPieceLibrary::Reset()
{
	m_pieceCount = 0;
	m_pieces = NULL;
	m_shapeDataPairCount = 0;
	m_shapeData = NULL;
	m_indexCount = 0;
	m_indices = NULL;
	m_colorCount = 0;
	m_colors = NULL;
	m_colorTripleCount = 0;
	m_colorTriples = NULL;
	m_textureCoordinateCount = 0;
	m_textureCoordinates = NULL;
	m_maxHighPieceOffset = 0;
	m_maxLowPieceOffset = 0;
}

// FUNCTION: LEGORACERS 0x0049ed60
LegoBool32 LegoPieceLibrary::IsColorBlack(LegoS32 p_index) const
{
	Color* color = &m_colors[p_index];
	if (static_cast<LegoU8>(color->m_red) == 0 && static_cast<LegoU8>(color->m_green) == 0 &&
		static_cast<LegoU8>(color->m_blue) == 0) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0049ed90
void LegoPieceLibrary::GetColor(LegoS32 p_index, LegoFloat* p_red, LegoFloat* p_green, LegoFloat* p_blue) const
{
	Color* color = &m_colors[p_index];
	*p_red = static_cast<LegoFloat>(color->m_red) * g_pieceLibraryColorScale;
	*p_green = static_cast<LegoFloat>(color->m_green) * g_pieceLibraryColorScale;
	*p_blue = static_cast<LegoFloat>(color->m_blue) * g_pieceLibraryColorScale;
}

// FUNCTION: LEGORACERS 0x0049edf0
void LegoPieceLibrary::GetTextureCoordinate(LegoS32 p_index, LegoFloat* p_u, LegoFloat* p_v) const
{
	TextureCoordinate* textureCoordinate = &m_textureCoordinates[p_index];
	*p_u = static_cast<LegoFloat>(textureCoordinate->m_u) * g_pieceLibraryTextureCoordinateScale;
	*p_v = static_cast<LegoFloat>(textureCoordinate->m_v) * g_pieceLibraryTextureCoordinateScale;
}

// STUB: LEGORACERS 0x0049ee30
LegoS32 LegoPieceLibrary::FUN_0049ee30(const LegoChar* p_filename, undefined4 p_binary)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".leb");
	}
	else {
		parser = new LebTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_filename);
	if (!parser->IsOpen()) {
		GOL_FATALERROR_MESSAGE("Unable to open LEGO Brick DataBase");
	}

	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27: {
			m_pieceCount = ReadBracketedCountAndLeftCurly(parser);
			m_pieces = new PieceRecord[m_pieceCount];

			LegoS32 i;
			for (i = 0; i < m_pieceCount; i++) {
				m_pieces[i].m_library = this;
				m_pieces[i].SetName(parser->ReadString());
				m_pieces[i].m_pieceType = static_cast<LegoU16>(parser->ReadInteger());
				m_pieces[i].m_shapeData = &m_shapeData[parser->ReadInteger()];
				m_pieces[i].m_indexCommandCount = static_cast<LegoU16>(parser->ReadInteger());
				m_pieces[i].m_indexOffset = parser->ReadInteger();
			}
			SkipCurrentBlock(*parser);
			break;
		}
		case GolFileParser::e_unknown0x28: {
			m_indexCount = ReadBracketedCountAndLeftCurly(parser);
			m_indices = new LegoU16[m_indexCount];
			if (m_indices == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			LegoS32 i;
			for (i = 0; i < m_indexCount; i++) {
				m_indices[i] = static_cast<LegoU16>(parser->ReadInteger());
			}
			SkipCurrentBlock(*parser);
			break;
		}
		case GolFileParser::e_unknown0x29: {
			m_colorCount = ReadBracketedCountAndLeftCurly(parser);
			m_colors = new Color[m_colorCount];
			if (m_colors == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			LegoS32 i;
			for (i = 0; i < m_colorCount; i++) {
				LegoS32 red = parser->ReadInteger();
				LegoS32 green = parser->ReadInteger();
				LegoS32 blue = parser->ReadInteger();
				Color* color = &m_colors[i];
				color->m_red = static_cast<LegoS16>(red);
				color->m_green = static_cast<LegoS16>(green);
				color->m_blue = static_cast<LegoS16>(blue);
			}
			SkipCurrentBlock(*parser);
			break;
		}
		case GolFileParser::e_unknown0x2a: {
			m_colorTripleCount = ReadBracketedCountAndLeftCurly(parser);
			m_colorTriples = new LegoU8[m_colorTripleCount * 3];
			if (m_colorTriples == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			LegoS32 i;
			for (i = 0; i < m_colorTripleCount; i++) {
				LegoS32 red = parser->ReadInteger();
				LegoS32 green = parser->ReadInteger();
				LegoS32 blue = parser->ReadInteger();
				LegoU8* triple = &m_colorTriples[i * 3];
				triple[0] = static_cast<LegoU8>(red);
				triple[1] = static_cast<LegoU8>(green);
				triple[2] = static_cast<LegoU8>(blue);
			}
			SkipCurrentBlock(*parser);
			break;
		}
		case GolFileParser::e_unknown0x2b: {
			m_textureCoordinateCount = ReadBracketedCountAndLeftCurly(parser);
			m_textureCoordinates = new TextureCoordinate[m_textureCoordinateCount];
			if (m_textureCoordinates == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			LegoS32 i;
			for (i = 0; i < m_textureCoordinateCount; i++) {
				LegoS32 u = parser->ReadInteger();
				LegoS32 v = parser->ReadInteger();
				TextureCoordinate* textureCoordinate = &m_textureCoordinates[i];
				textureCoordinate->m_u = static_cast<LegoS16>(u);
				textureCoordinate->m_v = static_cast<LegoS16>(v);
			}
			SkipCurrentBlock(*parser);
			break;
		}
		case GolFileParser::e_unknown0x2c: {
			m_shapeDataPairCount = ReadBracketedCountAndLeftCurly(parser);
			m_shapeData = new ShapeCell[m_shapeDataPairCount];
			if (m_shapeData == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			LegoS32 i;
			for (i = 0; i < m_shapeDataPairCount; i++) {
				LegoS32 first = parser->ReadInteger();
				LegoS32 second = parser->ReadInteger();
				ShapeCell* shapeData = &m_shapeData[i];
				shapeData->m_first = static_cast<LegoU8>(first);
				shapeData->m_second = static_cast<LegoU8>(second);
			}
			SkipCurrentBlock(*parser);
			break;
		}
		default:
			break;
		}
	}

	parser->Dispose();
	delete parser;

	if (m_pieces != NULL && m_pieceCount != 0) {
		::qsort(m_pieces, m_pieceCount, sizeof(PieceRecord), ComparePieceRecords);

		LegoS32 groupStart = 0;
		LegoU16 groupType = m_pieces[0].m_pieceType;
		LegoS32 i;
		LegoS32 j;
		for (i = 0; i < m_pieceCount; i++) {
			if (m_pieces[i].m_pieceType != groupType) {
				LegoS32 groupCount = i - groupStart;
				for (j = groupStart; j < i; j++) {
					m_pieces[j].m_variantCount = static_cast<LegoU8>(groupCount);
				}

				groupStart = i;
				groupType = m_pieces[i].m_pieceType;
			}

			m_pieces[i].m_variantIndex = static_cast<LegoU8>(i - groupStart);
		}

		LegoS32 groupCount = m_pieceCount - groupStart;
		for (i = groupStart; i < m_pieceCount; i++) {
			m_pieces[i].m_variantCount = static_cast<LegoU8>(groupCount);
		}
	}

	LegoS32 lowPieceOffset = 0;
	LegoS32 highPieceOffset = 0;
	LegoS32 highPieceBaseOffset = 0;

	PieceRecord* highBasePiece = FindPieceRecord(g_highPieceTypeBase, 1);
	if (highBasePiece != NULL) {
		highPieceBaseOffset = highBasePiece->m_indexCommandCount;
	}

	LegoS32 i;
	LegoS32 x;
	LegoS32 y;
	for (i = 0; i < m_pieceCount; i++) {
		PieceRecord& piece = m_pieces[i];
		LegoS32 offset = piece.m_indexCommandCount;
		LegoS32 width = piece.GetWidth();
		LegoS32 height = piece.GetHeight();
		for (y = 0; y < height; y++) {
			for (x = 0; x < width; x++) {
				if (static_cast<LegoS8>(piece.GetCell(x, y, 0)->m_first) < 0) {
					offset += highPieceBaseOffset;
				}
			}
		}

		if (piece.m_pieceType < g_highPieceTypeBase) {
			if (lowPieceOffset < offset) {
				lowPieceOffset = offset;
			}
		}
		else if (highPieceOffset < offset) {
			highPieceOffset = offset;
		}
	}

	if (m_maxHighPieceOffset < highPieceOffset) {
		m_maxHighPieceOffset = highPieceOffset;
	}
	if (m_maxLowPieceOffset < lowPieceOffset) {
		m_maxLowPieceOffset = lowPieceOffset;
	}

	return lowPieceOffset;
}

// FUNCTION: LEGORACERS 0x0049f410
static void SkipCurrentBlock(GolFileParser& p_parser)
{
	GolFileParser::ParserTokenType token;
	do {
		token = p_parser.GetNextToken();
	} while (token != GolFileParser::e_rightCurly && token != GolFileParser::e_syntaxerror);
}

// FUNCTION: LEGORACERS 0x0049f430
static LegoS32 ComparePieceRecords(const void* p_lhs, const void* p_rhs)
{
	const LegoPieceLibrary::PieceRecord* lhs = static_cast<const LegoPieceLibrary::PieceRecord*>(p_lhs);
	const LegoPieceLibrary::PieceRecord* rhs = static_cast<const LegoPieceLibrary::PieceRecord*>(p_rhs);

	LegoS32 result = lhs->m_pieceType - rhs->m_pieceType;
	if (result == 0) {
		result = lhs->m_indexCommandCount - rhs->m_indexCommandCount;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049f460
LegoPieceLibrary::PieceRecord* LegoPieceLibrary::FindPieceRecord(LegoS32 p_pieceType, LegoS32 p_variant)
{
	PieceRecord* pieces = m_pieces;
	if (pieces != NULL) {
		LegoS32 count = m_pieceCount;
		if (count != 0) {
			LegoS32 right = count;
			LegoS32 left = 0;
			for (;;) {
				LegoS32 middle = (right + left) >> 1;
				LegoS32 currentType = pieces[middle].m_pieceType;
				if (p_pieceType == currentType) {
					return pieces[middle].GetVariant(p_variant);
				}

				if (middle == left) {
					break;
				}

				if (p_pieceType < currentType) {
					right = middle;
				}
				else {
					left = middle;
				}
			}
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0049f4e0
LegoPieceLibrary::PieceRecord* LegoPieceLibrary::FindPieceRecordByName(LegoChar* p_name) const
{
	for (LegoS32 i = 0; i < m_pieceCount; i++) {
		if (m_pieces[i].CompareName(p_name) == 0) {
			return &m_pieces[i];
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0049f530
LegoPieceLibrary::PieceRecord* LegoPieceLibrary::PieceRecord::GetVariant(LegoS32 p_variant)
{
	if (p_variant >= m_variantCount) {
		p_variant = m_variantCount - 1;
	}
	if (p_variant < 0) {
		p_variant = 0;
	}

	PieceRecord* firstVariant = this - m_variantIndex;
	return &firstVariant[p_variant];
}

// FUNCTION: LEGORACERS 0x0049f560
LegoS32 LegoPieceLibrary::PieceRecord::FUN_0049f560(
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_height,
	LegoS32 p_rotation,
	LegoS32* p_unk0x14,
	LegoS32* p_unk0x18,
	LegoS32* p_unk0x1c
)
{
	LegoS32 result = 0;

	*p_unk0x1c = result;
	PieceRecord* pieceRecord = this;
	*p_unk0x18 = result;
	*p_unk0x14 = result;
	p_rotation &= 3;

	LegoS32 width;
	LegoS32 height;
	if (p_rotation & 1) {
		width = GetHeight();
		height = pieceRecord->GetWidth();
	}
	else {
		width = GetWidth();
		height = pieceRecord->GetHeight();
	}

	LegoS32 y = 0;
	LegoS32 yCount = height;
	if (height > 0) {
		do {
			LegoS32 x = 0;
			if (width > 0) {
				LegoS32 yOffset = y + p_y;
				do {
					ShapeCell* cell = pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
					LegoS32 lower = cell->m_second & g_shapeCellValueMask;
					LegoS32 upper = cell->m_first & g_shapeCellValueMask;
					if (lower > upper) {
						lower = 0;
					}

					LegoS32 delta = upper - lower;
					result += delta;
					*p_unk0x14 += delta * (x + p_x);
					*p_unk0x18 += delta * yOffset;
					for (LegoS32 z = lower; z < upper; z++) {
						*p_unk0x1c += z + p_height;
					}

					pieceRecord = this;
					x++;
				} while (x < width);
			}

			y++;
		} while (y < yCount);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049f690
LegoS32 LegoPieceLibrary::PieceRecord::FUN_0049f690() const
{
	if (m_pieceType < g_highPieceTypeBase) {
		return m_shapeData->FUN_0049eae0();
	}

	return 0xffff;
}

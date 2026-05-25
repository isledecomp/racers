#include "legopiecelibrary.h"

#include "golbinparser.h"
#include "golerror.h"
#include "goltxtparser.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(LegoPieceLibrary, 0x3c)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::ShapeCell, 0x02)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::PieceRecord, 0x1c)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::Color, 0x06)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::TextureCoordinate, 0x04)

// GLOBAL: LEGORACERS 0x004cebac
LegoPieceLibrary* g_pieceLibraryList;

static const LegoS32 g_highPieceTypeBase = 0x800;
static const LegoU8 g_shapeCellValueMask = 0x3f;

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
	LegoS32 cellCount = GetHeight();
	LegoS32 width = GetWidth();
	cellCount *= width;

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
LegoS32 LegoPieceLibrary::PieceRecord::SetName(const LegoChar* p_name)
{
	STUB(0x0049eb90);

	LegoS32 length = 0;
	LegoChar value = *p_name;

	if (value != 0) {
		do {
			if (length >= 8) {
				m_name[8] = 0;
				return length;
			}

			p_name++;
			m_name[length] = value;
			length++;
			value = *p_name;
		} while (value != 0);

		if (length >= 8) {
			m_name[8] = 0;
			return length;
		}
	}

	::memset(&m_name[length], 0, 8 - length);
	m_name[8] = 0;

	return 0;
}

// STUB: LEGORACERS 0x0049ebf0
LegoS32 LegoPieceLibrary::PieceRecord::CompareName(const LegoChar* p_name) const
{
	STUB(0x0049ebf0);

	LegoChar value = m_name[0];
	const LegoChar* cursor = m_name;
	if (value != '\0') {
		do {
			LegoS32 result = tolower(*p_name);
			LegoS32 lowerValue = tolower(value);
			result -= lowerValue;
			if (result != 0) {
				return result;
			}

			value = cursor[1];
			p_name++;
			cursor++;
		} while (value != '\0');
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

// STUB: LEGORACERS 0x0049ee30
void LegoPieceLibrary::FUN_0049ee30(const LegoChar* p_filename, undefined4 p_binary)
{
	STUB(0x0049ee30);

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".leb");
	}
	else {
		parser = new GolTxtParser2;
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
			if (m_pieces == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			LegoS32 i;
			for (i = 0; i < m_pieceCount; i++) {
				PieceRecord& piece = m_pieces[i];
				piece.m_library = this;
				piece.SetName(parser->ReadString());
				piece.m_pieceType = static_cast<LegoU16>(parser->ReadInteger());
				piece.m_shapeData = &m_shapeData[parser->ReadInteger()];
				piece.m_baseOffset = static_cast<LegoU16>(parser->ReadInteger());
				piece.m_unk0x18 = parser->ReadInteger();
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
				m_colors[i].m_red = static_cast<LegoS16>(parser->ReadInteger());
				m_colors[i].m_green = static_cast<LegoS16>(parser->ReadInteger());
				m_colors[i].m_blue = static_cast<LegoS16>(parser->ReadInteger());
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
				m_colorTriples[i * 3] = static_cast<LegoU8>(parser->ReadInteger());
				m_colorTriples[i * 3 + 1] = static_cast<LegoU8>(parser->ReadInteger());
				m_colorTriples[i * 3 + 2] = static_cast<LegoU8>(parser->ReadInteger());
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
				m_textureCoordinates[i].m_u = static_cast<LegoS16>(parser->ReadInteger());
				m_textureCoordinates[i].m_v = static_cast<LegoS16>(parser->ReadInteger());
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
				m_shapeData[i].m_first = static_cast<LegoU8>(parser->ReadInteger());
				m_shapeData[i].m_second = static_cast<LegoU8>(parser->ReadInteger());
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

	if (m_pieces != NULL && m_pieceCount > 0) {
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

	LegoS32 highPieceOffset = 0;
	LegoS32 lowPieceOffset = 0;
	LegoS32 highPieceBaseOffset = 0;

	PieceRecord* highBasePiece = FindPieceRecord(g_highPieceTypeBase, 1);
	if (highBasePiece != NULL) {
		highPieceBaseOffset = highBasePiece->m_baseOffset;
	}

	LegoS32 i;
	LegoS32 x;
	LegoS32 y;
	for (i = 0; i < m_pieceCount; i++) {
		PieceRecord& piece = m_pieces[i];
		LegoS32 offset = piece.m_baseOffset;
		for (y = 0; y < piece.GetHeight(); y++) {
			for (x = 0; x < piece.GetWidth(); x++) {
				if (static_cast<LegoS8>(piece.GetCell(x, y, 0)->m_first) < 0) {
					offset += highPieceBaseOffset;
				}
			}
		}

		if (piece.m_pieceType >= g_highPieceTypeBase) {
			if (highPieceOffset < offset) {
				highPieceOffset = offset;
			}
		}
		else if (lowPieceOffset < offset) {
			lowPieceOffset = offset;
		}
	}

	if (m_maxHighPieceOffset < highPieceOffset) {
		m_maxHighPieceOffset = highPieceOffset;
	}
	if (m_maxLowPieceOffset < lowPieceOffset) {
		m_maxLowPieceOffset = lowPieceOffset;
	}
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
		result = lhs->m_baseOffset - rhs->m_baseOffset;
	}

	return result;
}

// STUB: LEGORACERS 0x0049f460
LegoPieceLibrary::PieceRecord* LegoPieceLibrary::FindPieceRecord(LegoS32 p_pieceType, LegoS32 p_variant) const
{
	STUB(0x0049f460);

	PieceRecord* pieces = m_pieces;
	if (pieces != NULL) {
		LegoS32 count = m_pieceCount;
		if (count != 0) {
			LegoS32 right = count;
			LegoS32 left = 0;
			LegoS32 middle = count >> 1;
			LegoU32 currentType = pieces[middle].m_pieceType;
			if (p_pieceType == static_cast<LegoS32>(currentType)) {
				return pieces[middle].GetVariant(p_variant);
			}

			while (middle != left) {
				if (p_pieceType >= static_cast<LegoS32>(currentType)) {
					left = middle;
				}
				else {
					right = middle;
				}

				middle = (right + left) >> 1;
				currentType = pieces[middle].m_pieceType;
				if (p_pieceType == static_cast<LegoS32>(currentType)) {
					return pieces[middle].GetVariant(p_variant);
				}
			}
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0049f4e0
LegoPieceLibrary::PieceRecord* LegoPieceLibrary::FindPieceRecordByName(const LegoChar* p_name) const
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

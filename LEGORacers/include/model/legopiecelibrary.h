#ifndef LEGOPIECELIBRARY_H
#define LEGOPIECELIBRARY_H

#include "decomp.h"
#include "goltxtparser.h"
#include "types.h"

class GolFileParser;

// SIZE 0x3c
class LegoPieceLibrary {
public:
	// VTABLE: LEGORACERS 0x004b4810
	// SIZE 0x1fc
	class LebTxtParser : public GolTxtParser {
	public:
		enum {
			e_pieces = 0x27,
			e_indices = 0x28,
			e_colors = 0x29,
			e_colorTriples = 0x2a,
			e_textureCoordinates = 0x2b,
			e_shapes = 0x2c,
		};
	};

	// Shape blob layout: a header cell {width, height} followed by
	// width*height cells and a trailing u16 part type. Each cell packs the
	// solid column's top height in m_first (bit 7 = occupied) and its bottom
	// height in m_second, both masked with 0x3f; a bottom above the top marks
	// a raised underside (arches).
	// SIZE 0x02
	struct ShapeCell {
		LegoS32 GetRaisedBottomHeight();
		ShapeCell* GetCell(LegoS32 p_x, LegoS32 p_y, LegoU8 p_orientation);
		LegoS32 GetPartType();
		LegoS32 GetClampedLower()
		{
			LegoS32 lower = m_second & 0x3f;
			if (lower > (m_first & 0x3f)) {
				lower = 0;
			}
			return lower;
		}

		LegoU8 m_first;  // 0x00
		LegoU8 m_second; // 0x01
	};

	// SIZE 0x1c
	struct PieceRecord {
		PieceRecord();
		~PieceRecord();

		LegoS32 SetName(LegoChar* p_name);
		LegoS32 GetWidth() const;
		LegoS32 GetHeight() const;
		LegoS32 GetMaxCellValue() const;
		LegoS32 CompareName(LegoChar* p_name);
		PieceRecord* GetVariant(LegoS32 p_variant);
		LegoS32 GetPartType() const;
		LegoS32 ComputeVolumeMoments(
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_height,
			LegoS32 p_rotation,
			LegoS32* p_momentX,
			LegoS32* p_momentY,
			LegoS32* p_momentZ
		);
		ShapeCell* GetCell(LegoS32 p_x, LegoS32 p_y, LegoU8 p_orientation) const
		{
			return m_shapeData->GetCell(p_x, p_y, p_orientation);
		}

		LegoPieceLibrary* m_library; // 0x00
		LegoChar m_name[9];          // 0x04
		LegoU8 m_variantIndex;       // 0x0d
		LegoU8 m_variantCount;       // 0x0e
		ShapeCell* m_shapeData;      // 0x10
		LegoU16 m_pieceType;         // 0x14
		LegoU16 m_indexCommandCount; // 0x16
		LegoU32 m_indexOffset;       // 0x18
	};

	// SIZE 0x06
	struct Color {
		LegoS16 m_red;   // 0x00
		LegoS16 m_green; // 0x02
		LegoS16 m_blue;  // 0x04
	};

	// SIZE 0x04
	struct TextureCoordinate {
		LegoS16 m_u; // 0x00
		LegoS16 m_v; // 0x02
	};

	LegoPieceLibrary();
	~LegoPieceLibrary();

	static LegoS32 ReadBracketedCountAndLeftCurly(GolFileParser* p_parser);

	void Destroy();
	LegoS32 Load(const LegoChar* p_filename, undefined4 p_binary);
	LegoBool32 IsColorBlack(LegoS32 p_index) const;
	void GetColor(LegoS32 p_index, LegoFloat* p_red, LegoFloat* p_green, LegoFloat* p_blue) const;
	void GetTextureCoordinate(LegoS32 p_index, LegoFloat* p_u, LegoFloat* p_v) const;
	const LegoU8* GetColorTriple(LegoS32 p_index) const { return &m_colorTriples[p_index * 3]; }
	const LegoU16* GetIndexCursor(LegoU32 p_index) const { return &m_indices[p_index]; }
	PieceRecord* FindPieceRecord(LegoS32 p_pieceType, LegoS32 p_variant);
	PieceRecord* FindPieceRecordByName(LegoChar* p_name) const;
	LegoS32 GetMaxHighPieceOffset() const { return m_maxHighPieceOffset; }

private:
	void DestroyData();
	void Reset();

	LegoPieceLibrary* m_next;                // 0x00
	LegoS32 m_pieceCount;                    // 0x04
	PieceRecord* m_pieces;                   // 0x08
	LegoS32 m_shapeDataPairCount;            // 0x0c
	ShapeCell* m_shapeData;                  // 0x10
	LegoS32 m_indexCount;                    // 0x14
	LegoU16* m_indices;                      // 0x18
	LegoS32 m_colorCount;                    // 0x1c
	Color* m_colors;                         // 0x20
	LegoS32 m_colorTripleCount;              // 0x24
	LegoU8* m_colorTriples;                  // 0x28
	LegoS32 m_textureCoordinateCount;        // 0x2c
	TextureCoordinate* m_textureCoordinates; // 0x30
	LegoS32 m_maxHighPieceOffset;            // 0x34
	LegoS32 m_maxLowPieceOffset;             // 0x38
};

#endif // LEGOPIECELIBRARY_H

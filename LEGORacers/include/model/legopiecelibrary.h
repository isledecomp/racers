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
	class LebTxtParser : public GolTxtParser {};

	// SIZE 0x02
	struct ShapeCell {
		LegoS32 FUN_0049ea40();
		ShapeCell* GetCell(LegoS32 p_x, LegoS32 p_y, LegoU8 p_orientation);
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
		~PieceRecord();

		LegoS32 SetName(const LegoChar* p_name);
		LegoS32 GetWidth() const;
		LegoS32 GetHeight() const;
		LegoS32 GetMaxCellValue() const;
		LegoS32 CompareName(const LegoChar* p_name) const;
		PieceRecord* GetVariant(LegoS32 p_variant);
		ShapeCell* GetCell(LegoS32 p_x, LegoS32 p_y, LegoU8 p_orientation) const
		{
			return m_shapeData->GetCell(p_x, p_y, p_orientation);
		}

		LegoPieceLibrary* m_library; // 0x00
		LegoChar m_name[9];          // 0x04
		LegoU8 m_variantIndex;       // 0x0d
		LegoU8 m_variantCount;       // 0x0e
		undefined m_padding0x0f;     // 0x0f
		ShapeCell* m_shapeData;      // 0x10
		LegoU16 m_pieceType;         // 0x14
		LegoU16 m_baseOffset;        // 0x16
		LegoU32 m_unk0x18;           // 0x18
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
	void FUN_0049ee30(const LegoChar* p_filename, undefined4 p_binary);
	PieceRecord* FindPieceRecord(LegoS32 p_pieceType, LegoS32 p_variant) const;
	PieceRecord* FindPieceRecordByName(const LegoChar* p_name) const;
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

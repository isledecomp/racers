#ifndef LEGOPIECELIBRARY_H
#define LEGOPIECELIBRARY_H

#include "decomp.h"
#include "types.h"

// SIZE 0x3c
class LegoPieceLibrary {
public:
	// SIZE 0x1c
	struct PieceRecord {
		~PieceRecord();

		undefined m_unk0x00[0x1c - 0x00]; // 0x00
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

	void Destroy();

private:
	void DestroyData();
	void Reset();

	LegoPieceLibrary* m_next;                // 0x00
	LegoS32 m_pieceCount;                    // 0x04
	PieceRecord* m_pieces;                   // 0x08
	LegoS32 m_unk0x0c;                       // 0x0c
	LegoU8* m_unk0x10;                       // 0x10
	LegoS32 m_unk0x14;                       // 0x14
	LegoU16* m_unk0x18;                      // 0x18
	LegoS32 m_colorCount;                    // 0x1c
	Color* m_colors;                         // 0x20
	LegoS32 m_unk0x24;                       // 0x24
	LegoU8* m_unk0x28;                       // 0x28
	LegoS32 m_textureCoordinateCount;        // 0x2c
	TextureCoordinate* m_textureCoordinates; // 0x30
	LegoS32 m_unk0x34;                       // 0x34
	LegoS32 m_unk0x38;                       // 0x38
};

#endif // LEGOPIECELIBRARY_H

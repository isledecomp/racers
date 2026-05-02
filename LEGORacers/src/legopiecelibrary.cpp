#include "legopiecelibrary.h"

DECOMP_SIZE_ASSERT(LegoPieceLibrary, 0x3c)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::PieceRecord, 0x1c)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::Color, 0x06)
DECOMP_SIZE_ASSERT(LegoPieceLibrary::TextureCoordinate, 0x04)

// GLOBAL: LEGORACERS 0x004cebac
LegoPieceLibrary* g_pieceLibraryList;

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
LegoPieceLibrary::PieceRecord::~PieceRecord()
{
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

	if (m_unk0x10) {
		delete[] m_unk0x10;
	}

	if (m_unk0x18) {
		delete[] m_unk0x18;
	}

	if (m_colors) {
		delete[] m_colors;
	}

	if (m_unk0x28) {
		delete[] m_unk0x28;
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
	m_unk0x0c = 0;
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_colorCount = 0;
	m_colors = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_textureCoordinateCount = 0;
	m_textureCoordinates = NULL;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
}

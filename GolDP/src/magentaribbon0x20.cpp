#include "magentaribbon0x20.h"

#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golstream.h"
#include "goltgafile.h"
#include "purpledune0x7c.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MagentaRibbonSourceItem0x2c, 0x2c)
DECOMP_SIZE_ASSERT(MagentaRibbonSource0x4, 0x04)
DECOMP_SIZE_ASSERT(MagentaRibbon0x20, 0x20)

extern GolTgaFile g_unk0x10063ca0;

extern GolBmpFile g_unk0x10064280;

extern undefined4 g_unk0x1005cf0c;

// FUNCTION: GOLDP 0x1002b4d0
MagentaRibbon0x20::MagentaRibbon0x20()
{
	m_renderer = NULL;
	m_next = NULL;
	m_unk0x14 = 0;
	m_numItems = 0;
	m_unk0x18 = 0;
}

// FUNCTION: GOLDP 0x1002b520
MagentaRibbon0x20::~MagentaRibbon0x20()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveTextureList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// STUB: GOLDP 0x1002b5a0
void MagentaRibbon0x20::VTable0x24(BronzeFalcon0xc8770* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddTextureList(this);
	m_unk0x14 = NULL;

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".tdb");
	}
	else {
		parser = new TdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_numItems = parser->ReadBracketedCountAndLeftCurly();

	if (m_numItems == 0) {
		parser->Dispose();
		delete parser;
		return;
	}

	GolNameTable::Allocate(m_numItems);
	m_unk0x18 = g_hashTable ? g_hashTable->GetCurrentEntry() : NULL;
	AllocateItems();

	for (LegoU32 i = 0; i < m_numItems; i++) {
		GolName textureName;
		ColorRGBA colorKey;
		LegoU16 mipmapCount = 0;
		LegoU16 flags = 0;

		colorKey.m_red = 0;
		colorKey.m_grn = 0;
		colorKey.m_blu = 0;
		colorKey.m_alp = 0;

		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		GoldDune0x38* texture = GetItem(i);
		::strncpy(textureName, parser->ReadStringWithMaxLength(sizeof(textureName)), sizeof(textureName));

		if (m_renderer->FindTextureByName(textureName) != NULL) {
			textureName[0] = '\0';
		}
		else {
			AddName(textureName, texture);
		}

		parser->ReadLeftCurly();
		for (GolFileParser::ParserTokenType token = parser->GetNextToken(); token != GolFileParser::e_rightCurly;
			 token = parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				flags |= GoldDune0x38::c_unk0x36Bit2;
				break;
			case GolFileParser::e_unknown0x29:
				mipmapCount = static_cast<LegoU16>(parser->ReadInteger());
				flags |= GoldDune0x38::c_unk0x36Bit0;
				break;
			case GolFileParser::e_unknown0x2a:
				flags &= ~GoldDune0x38::c_unk0x36Bit4;
				flags |= GoldDune0x38::c_unk0x36Bit3;
				break;
			case GolFileParser::e_unknown0x2b:
				flags &= ~GoldDune0x38::c_unk0x36Bit3;
				flags |= GoldDune0x38::c_unk0x36Bit4;
				break;
			case GolFileParser::e_unknown0x2c:
				flags |= GoldDune0x38::c_unk0x36Bit5;
				colorKey.m_red = static_cast<LegoU8>(parser->ReadInteger());
				colorKey.m_grn = static_cast<LegoU8>(parser->ReadInteger());
				colorKey.m_blu = static_cast<LegoU8>(parser->ReadInteger());
				break;
			case GolFileParser::e_unknown0x2d:
				flags |= GoldDune0x38::c_unk0x36Bit8;
				break;
			case GolFileParser::e_unknown0x2e:
				flags |= GoldDune0x38::c_unk0x36Bit9;
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		flags |= GoldDune0x38::c_unk0x36Bit11;
		texture->SetTextureDefinition(mipmapCount, flags, colorKey);
	}

	parser->ReadRightCurly();
	parser->Dispose();

	if (g_unk0x1005cf0c != 0) {
		LoadTextures();
	}

	delete parser;
}

// STUB: GOLDP 0x1002b890
void MagentaRibbon0x20::LoadTextures()
{
	if (m_unk0x14 != NULL) {
		for (LegoU32 i = 0; i < m_numItems; i++) {
			GoldDune0x38* texture = GetItem(i);
			if (texture->GetPixelFlags() & SilverDune0x30::c_lockRequestRead) {
				continue;
			}

			MagentaRibbonSourceItem0x2c sourceItem;
			m_unk0x14->VTable0x00(i, &sourceItem);

			LegoU16 flags = sourceItem.m_flags;
			if (m_renderer->VTable0x110()) {
				flags |= GoldDune0x38::c_unk0x36Bit6;
			}
			if ((flags & GoldDune0x38::c_unk0x36Bit5) && (m_renderer->GetFlags() & BronzeFalcon0xc8770::c_flagBit9)) {
				flags |= GoldDune0x38::c_unk0x36Bit7;
			}

			texture->SetSourceTextureDefinition(sourceItem.m_mipmapCount, flags, sourceItem.m_colorKey);

			GolSurfaceFormat textureFormat;
			m_renderer
				->SelectTextureFormat(sourceItem.m_textureFormat, &textureFormat, flags & GoldDune0x38::c_unk0x36Bit5);
			VTable0x18(i, textureFormat, sourceItem.m_width, sourceItem.m_height);
			m_unk0x14->VTable0x04(i, 0, texture);
		}
		return;
	}

	if (m_unk0x18 != NULL && g_hashTable != NULL) {
		g_hashTable->SetCurrentEntry(m_unk0x18);
	}

	for (LegoU32 i = 0; i < m_numItems; i++) {
		GoldDune0x38* texture = GetItem(i);
		if (texture->GetPixelFlags() & SilverDune0x30::c_lockRequestRead) {
			continue;
		}

		GolName textureName;
		GetNameByValue(texture, textureName);
		if (textureName[0] == '\0') {
			continue;
		}

		GolImgFile* imageFile = &g_unk0x10063ca0;
		if (texture->GetUnk0x36() & GoldDune0x38::c_unk0x36Bit3) {
			imageFile = &g_unk0x10064280;
		}

		imageFile->VTable0x08(textureName);
		texture->VTable0x30(*m_renderer, imageFile);
		imageFile->Destroy();
	}
}

// FUNCTION: GOLDP 0x1002ba30
void MagentaRibbon0x20::VTable0x20(
	BronzeFalcon0xc8770* p_renderer,
	MagentaRibbonSource0x4* p_source,
	LegoU32 p_capacity
)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddTextureList(this);
	m_unk0x14 = p_source;
	m_numItems = p_capacity;
	AllocateItems();

	if (g_unk0x1005cf0c != 0) {
		LoadTextures();
	}
}

// FUNCTION: GOLDP 0x1002ba80
void MagentaRibbon0x20::VTable0x1c(BronzeFalcon0xc8770* p_renderer, LegoU32 p_capacity)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddTextureList(this);
	m_numItems = p_capacity;
	GolNameTable::Allocate(p_capacity);
	AllocateItems();
}

// FUNCTION: GOLDP 0x1002bac0
void MagentaRibbon0x20::Clear()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveTextureList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void MagentaRibbon0x20::VTable0x0c()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void MagentaRibbon0x20::VTable0x10()
{
	// empty
}

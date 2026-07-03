#include "material/goltexturelist.h"

#include "golbinparser.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golstream.h"
#include "goltgafile.h"
#include "render/gold3drenderdevice.h"
#include "surface/gold3dtexture.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolTextureSourceItem, 0x2c)
DECOMP_SIZE_ASSERT(GolTextureSource, 0x04)
DECOMP_SIZE_ASSERT(GolTextureList, 0x20)
DECOMP_SIZE_ASSERT(GolTextureList::TdbTxtParser, 0x1fc)

extern GolTgaFile g_unk0x10063ca0;

extern GolBmpFile g_unk0x10064280;

extern undefined4 g_unk0x1005cf0c;

// FUNCTION: GOLDP 0x1002b4d0
GolTextureList::GolTextureList()
{
	m_renderer = NULL;
	m_next = NULL;
	m_unk0x14 = 0;
	m_numItems = 0;
	m_unk0x18 = 0;
}

// FUNCTION: GOLDP 0x1002b520
GolTextureList::~GolTextureList()
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

// FUNCTION: GOLDP 0x1002b5a0
void GolTextureList::VTable0x24(GolD3DRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
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
		LegoU16 mipmapCount;
		LegoU16 flags;

		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		GolD3DTexture* texture = GetItem(i);
		::strncpy(textureName, parser->ReadStringWithMaxLength(sizeof(textureName)), sizeof(textureName));

		if (m_renderer->FindTextureByName(textureName) != NULL) {
			textureName[0] = '\0';
		}
		else {
			AddName(textureName, texture);
		}

		parser->ReadLeftCurly();
		mipmapCount = 0;
		flags = 0;
		colorKey.m_red = 0;
		colorKey.m_grn = 0;
		colorKey.m_blu = 0;

		for (GolFileParser::ParserTokenType token = parser->GetNextToken(); token != GolFileParser::e_rightCurly;
			 token = parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				flags |= GolTexture::c_textureFlagBit2;
				break;
			case GolFileParser::e_unknown0x29:
				mipmapCount = static_cast<LegoU16>(parser->ReadInteger());
				flags |= GolTexture::c_textureFlagBit0;
				break;
			case GolFileParser::e_unknown0x2a:
				flags &= ~GolTexture::c_textureFlagBit4;
				flags |= GolTexture::c_textureFlagBit3;
				break;
			case GolFileParser::e_unknown0x2b:
				flags &= ~GolTexture::c_textureFlagBit3;
				flags |= GolTexture::c_textureFlagBit4;
				break;
			case GolFileParser::e_unknown0x2c:
				flags |= GolTexture::c_textureFlagBit5;
				colorKey.m_red = static_cast<LegoU8>(parser->ReadInteger());
				colorKey.m_grn = static_cast<LegoU8>(parser->ReadInteger());
				colorKey.m_blu = static_cast<LegoU8>(parser->ReadInteger());
				break;
			case GolFileParser::e_unknown0x2d:
				flags |= GolTexture::c_textureFlagBit8;
				break;
			case GolFileParser::e_unknown0x2e:
				flags |= GolTexture::c_textureFlagBit9;
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		texture->SetName(textureName);
		texture->SetTextureDefinition(mipmapCount, flags, colorKey);
	}

	parser->ReadRightCurly();
	parser->Dispose();

	if (g_unk0x1005cf0c) {
		LoadTextures();
	}

	delete parser;
}

// FUNCTION: GOLDP 0x1002b890
void GolTextureList::LoadTextures()
{
	GolTextureSourceItem sourceItem;
	GolSurfaceFormat textureFormat;
	LegoChar textureName[sizeof(GolName) + 1];

	if (m_unk0x14 != NULL) {
		for (LegoU32 i = 0; i < m_numItems; i++) {
			GolTexture* texture = GetItem(i);
			if (texture->GetPixelFlags() & GolSurface::c_lockRequestRead) {
				continue;
			}

			m_unk0x14->VTable0x00(i, &sourceItem);

			LegoU16 flags = sourceItem.m_flags;
			if (m_renderer->VTable0x110()) {
				flags |= GolTexture::c_textureFlagBit6;
			}
			if ((flags & GolTexture::c_textureFlagBit5) && (m_renderer->GetFlags() & GolD3DRenderDevice::c_flagBit9)) {
				flags |= GolTexture::c_textureFlagBit7;
			}

			texture->SetTextureFlags(flags);
			texture->SetSourceTextureDefinition(sourceItem.m_mipmapCount, flags, sourceItem.m_colorKey);

			m_renderer->SelectTextureFormat(
				sourceItem.m_textureFormat,
				&textureFormat,
				flags & GolTexture::c_textureFlagBit5
			);
			VTable0x18(i, textureFormat, sourceItem.m_width, sourceItem.m_height);
			m_unk0x14->VTable0x04(i, 0, texture);
		}
		return;
	}

	if (m_unk0x18 != NULL && g_hashTable != NULL) {
		g_hashTable->SetCurrentEntry(m_unk0x18);
	}

	for (LegoU32 i = 0; i < m_numItems; i++) {
		GolD3DTexture* texture = GetItem(i);
		if (texture->GetPixelFlags() & GolSurface::c_lockRequestRead) {
			continue;
		}

		const GolName& sourceName = texture->GetName();
		if (sourceName[0] == '\0') {
			continue;
		}

		::memcpy(textureName, sourceName, sizeof(GolName));
		textureName[sizeof(GolName)] = '\0';

		LegoU8 textureFlags = static_cast<LegoU8>(texture->GetTextureFlags());
		GolImgFile* imageFile = &g_unk0x10064280;
		if (!(textureFlags & GolTexture::c_textureFlagBit3)) {
			imageFile = &g_unk0x10063ca0;
		}

		imageFile->Open(textureName);
		texture->VTable0x30(*m_renderer, imageFile);
		imageFile->Destroy();
	}
}

// FUNCTION: GOLDP 0x1002ba30
void GolTextureList::VTable0x20(GolD3DRenderDevice* p_renderer, GolTextureSource* p_source, LegoU32 p_capacity)
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
void GolTextureList::VTable0x1c(GolD3DRenderDevice* p_renderer, LegoU32 p_capacity)
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
void GolTextureList::Clear()
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
void GolTextureList::VTable0x0c()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolTextureList::VTable0x10()
{
	// empty
}

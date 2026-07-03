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

extern GolTgaFile g_textureTgaFile;

extern GolBmpFile g_textureBmpFile;

extern undefined4 g_loadTexturesImmediately;

// FUNCTION: GOLDP 0x1002b4d0
GolTextureList::GolTextureList()
{
	m_renderer = NULL;
	m_next = NULL;
	m_textureSource = 0;
	m_itemCount = 0;
	m_nameTableEntry = 0;
}

// FUNCTION: GOLDP 0x1002b520
GolTextureList::~GolTextureList()
{
	m_itemCount = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveTextureList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x1002b5a0
void GolTextureList::Load(GolD3DRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddTextureList(this);
	m_textureSource = NULL;

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
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TdbTxtParser::e_texture));
	m_itemCount = parser->ReadBracketedCountAndLeftCurly();

	if (m_itemCount == 0) {
		parser->Dispose();
		delete parser;
		return;
	}

	GolNameTable::Allocate(m_itemCount);
	m_nameTableEntry = g_hashTable ? g_hashTable->GetCurrentEntry() : NULL;
	AllocateItems();

	for (LegoU32 i = 0; i < m_itemCount; i++) {
		GolName textureName;
		ColorRGBA colorKey;
		LegoU16 mipmapCount;
		LegoU16 flags;

		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TdbTxtParser::e_texture));
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
			case TdbTxtParser::e_flipVertically:
				flags |= GolTexture::c_textureFlagFlipVertically;
				break;
			case TdbTxtParser::e_mipmaps:
				mipmapCount = static_cast<LegoU16>(parser->ReadInteger());
				flags |= GolTexture::c_textureFlagMipmapped;
				break;
			case TdbTxtParser::e_bmp:
				flags &= ~GolTexture::c_textureFlagTgaSource;
				flags |= GolTexture::c_textureFlagBmpSource;
				break;
			case TdbTxtParser::e_tga:
				flags &= ~GolTexture::c_textureFlagBmpSource;
				flags |= GolTexture::c_textureFlagTgaSource;
				break;
			case TdbTxtParser::e_colorKey:
				flags |= GolTexture::c_textureFlagColorKeyed;
				colorKey.m_red = static_cast<LegoU8>(parser->ReadInteger());
				colorKey.m_grn = static_cast<LegoU8>(parser->ReadInteger());
				colorKey.m_blu = static_cast<LegoU8>(parser->ReadInteger());
				break;
			case TdbTxtParser::e_unknown0x2d:
				flags |= GolTexture::c_textureFlagBit8;
				break;
			case TdbTxtParser::e_unknown0x2e:
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

	if (g_loadTexturesImmediately) {
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

	if (m_textureSource != NULL) {
		for (LegoU32 i = 0; i < m_itemCount; i++) {
			GolTexture* texture = GetItem(i);
			if (texture->GetPixelFlags() & GolSurface::c_lockRequestRead) {
				continue;
			}

			m_textureSource->GetTextureDefinition(i, &sourceItem);

			LegoU16 flags = sourceItem.m_flags;
			if (m_renderer->VTable0x110()) {
				flags |= GolTexture::c_textureFlagBit6;
			}
			if ((flags & GolTexture::c_textureFlagColorKeyed) &&
				(m_renderer->GetFlags() & GolD3DRenderDevice::c_flagBlackColorKey)) {
				flags |= GolTexture::c_textureFlagBlackColorKey;
			}

			texture->SetTextureFlags(flags);
			texture->SetSourceTextureDefinition(sourceItem.m_mipmapCount, flags, sourceItem.m_colorKey);

			m_renderer->SelectTextureFormat(
				sourceItem.m_textureFormat,
				&textureFormat,
				flags & GolTexture::c_textureFlagColorKeyed
			);
			AllocateTexture(i, textureFormat, sourceItem.m_width, sourceItem.m_height);
			m_textureSource->OnTextureLoaded(i, 0, texture);
		}
		return;
	}

	if (m_nameTableEntry != NULL && g_hashTable != NULL) {
		g_hashTable->SetCurrentEntry(m_nameTableEntry);
	}

	for (LegoU32 i = 0; i < m_itemCount; i++) {
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
		GolImgFile* imageFile = &g_textureBmpFile;
		if (!(textureFlags & GolTexture::c_textureFlagBmpSource)) {
			imageFile = &g_textureTgaFile;
		}

		imageFile->Open(textureName);
		texture->LoadFromImgFile(*m_renderer, imageFile);
		imageFile->Destroy();
	}
}

// FUNCTION: GOLDP 0x1002ba30
void GolTextureList::InitializeFromSource(
	GolD3DRenderDevice* p_renderer,
	GolTextureSource* p_source,
	LegoU32 p_capacity
)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddTextureList(this);
	m_textureSource = p_source;
	m_itemCount = p_capacity;
	AllocateItems();

	if (g_loadTexturesImmediately != 0) {
		LoadTextures();
	}
}

// FUNCTION: GOLDP 0x1002ba80
void GolTextureList::Initialize(GolD3DRenderDevice* p_renderer, LegoU32 p_capacity)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddTextureList(this);
	m_itemCount = p_capacity;
	GolNameTable::Allocate(p_capacity);
	AllocateItems();
}

// FUNCTION: GOLDP 0x1002bac0
void GolTextureList::Clear()
{
	m_itemCount = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveTextureList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolTextureList::ReleaseTextures()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolTextureList::RestoreTextures()
{
	// empty
}

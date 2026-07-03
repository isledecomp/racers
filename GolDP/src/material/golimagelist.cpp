#include "material/golimagelist.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "goltxtparser.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(GolImageList, 0x1c)

// FUNCTION: GOLDP 0x10022fa0
GolImageList::GolImageList()
{
	m_renderer = NULL;
	m_next = NULL;
	m_itemCount = 0;
	m_currentHashEntry = NULL;
}

// FUNCTION: GOLDP 0x10022fe0
GolImageList::~GolImageList()
{
	m_itemCount = 0;

	if (m_renderer) {
		m_renderer->RemoveImageList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10023060
void GolImageList::LoadImageDefinitions(GolD3DRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_itemCount > 0) {
		Clear();
	}

	m_renderer = p_renderer;
	m_renderer->AddImageList(this);

	GolFileParser* parser;

	if (p_binary) {
		parser = new GolBinParser();

		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}

		parser->SetSuffix(".idb");
	}
	else {
		parser = new GolTxtParser();

		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(e_image));

	m_itemCount = parser->ReadBracketedCountAndLeftCurly();

	if (!m_itemCount) {
		parser->Dispose();
		delete parser;
		return;
	}

	GolNameTable::Allocate(m_itemCount);
	m_currentHashEntry = g_hashTable ? g_hashTable->GetCurrentEntry() : NULL;
	AllocateItems();

	for (LegoU32 i = 0; i < m_itemCount; i++) {
		ColorRGBA colorKey;
		FourBytes local34;
		colorKey.m_alp = 0xff;
		local34.m_bytes[3] = -1;

		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(e_image));

		GolImage* item = GetItem(i);

		FourBytes name[2];
		strncpy(&name[0].m_bytes[0], parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
		AddName(&name[0].m_bytes[0], item);

		parser->ReadLeftCurly();

		LegoU16 flags = 0;

		colorKey.m_red = 0;
		colorKey.m_grn = 0;
		colorKey.m_blu = 0;

		local34.m_bytes[0] = -1;
		local34.m_bytes[1] = -1;
		local34.m_bytes[2] = -1;

		GolFileParser::ParserTokenType token = parser->GetNextToken();

		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case e_flipVertically:
				flags |= GolTexture::c_textureFlagFlipVertically;
				break;
			case e_bmp:
				flags = (flags & GolImage::c_sourceFlagsWithoutTga) | GolTexture::c_textureFlagBmpSource;
				break;
			case e_tga:
				flags = (flags & GolImage::c_sourceFlagsWithoutBmp) | GolTexture::c_textureFlagTgaSource;
				break;
			case e_colorKey:
				flags |= GolTexture::c_textureFlagColorKeyed;
				colorKey.m_red = parser->ReadInteger();
				colorKey.m_grn = parser->ReadInteger();
				colorKey.m_blu = parser->ReadInteger();
				break;
			case e_tint:
				local34.m_bytes[0] = parser->ReadInteger();
				local34.m_bytes[1] = parser->ReadInteger();
				local34.m_bytes[2] = parser->ReadInteger();
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			}

			token = parser->GetNextToken();
		}

		item->m_name[0] = name[0];
		item->m_name[1] = name[1];

		if (p_renderer->VTable0x110()) {
			flags = flags | GolTexture::c_textureFlagBit6;
		}

		if ((flags & GolTexture::c_textureFlagColorKeyed) &&
			(p_renderer->GetFlags() & GolD3DRenderDevice::c_flagBlackColorKey)) {
			flags = flags | GolTexture::c_textureFlagBlackColorKey;
		}

		item->m_flags = flags;
		item->m_tintColor = local34;

		if (flags & GolTexture::c_textureFlagColorKeyed) {
			item->m_colorKey = colorKey;
			item->m_flags = flags | GolTexture::c_textureFlagColorKeyDirty;
		}

		item->m_renderer = p_renderer;
	}

	parser->ReadRightCurly();
	parser->Dispose();
	delete parser;

	if (g_hashTable) {
		g_hashTable->SetCurrentEntry(m_currentHashEntry);
	}

	for (LegoU32 j = 0; j < m_itemCount; j++) {
		GolImage* entry = GetItem(j);
		if (!(entry->m_stateFlags & GolImage::c_stateCreated)) {
			entry->Load();
		}
	}
}

// FUNCTION: GOLDP 0x100233a0
void GolImageList::Initialize(GolD3DRenderDevice* p_renderer, LegoU32 p_numItems)
{
	if (m_itemCount > 0) {
		Clear();
	}

	m_renderer = p_renderer;
	m_renderer->AddImageList(this);
	m_itemCount = p_numItems;

	AllocateItems();

	for (LegoU32 i = 0; i < p_numItems; i++) {
		GetItem(i)->m_renderer = p_renderer;
	}
}

// FUNCTION: GOLDP 0x100233f0
void GolImageList::Clear()
{
	m_itemCount = 0;

	if (m_renderer) {
		m_renderer->RemoveImageList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolImageList::ReleaseImages()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolImageList::RestoreImages()
{
	// empty
}

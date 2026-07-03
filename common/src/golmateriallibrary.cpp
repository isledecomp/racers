#include "golmateriallibrary.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golmaterial.h"
#include "golname.h"
#include "render/golrenderdevice.h"

DECOMP_SIZE_ASSERT(GolMaterialLibrary, 0x1c)
DECOMP_SIZE_ASSERT(GolMaterialLibrary::MdbTxtParser, 0x1fc)

// FUNCTION: GOLDP 0x100261b0
GolMaterialLibrary::GolMaterialLibrary()
{
	m_renderer = NULL;
	m_next = NULL;
	m_materialSource = NULL;
	m_numItems = 0;
}

// FUNCTION: GOLDP 0x100261f0
GolMaterialLibrary::~GolMaterialLibrary()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveMaterialList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10026270
void GolMaterialLibrary::VTable0x24(GolRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddMaterialList(this);
	m_materialSource = NULL;
	GolFileParser* parser;

	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".mdb");
	}
	else {
		parser = new MdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_numItems = parser->ReadBracketedCountAndLeftCurly();

	if (m_numItems == 0) {
		parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	GolNameTable::Allocate(m_numItems);
	AllocateItems();

	LegoU32 i;
	LegoU32 j;
	GolName textureName;
	LegoU8 fullIntensity = 0xff;

	for (i = 0; i < m_numItems; i++) {
		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		GolMaterial::NameRecord name;
		::strncpy(name.m_name, parser->ReadStringWithMaxLength(sizeOfArray(name.m_name)), sizeOfArray(name.m_name));
		GolMaterial* material = GetItem(i);
		AddName(name.m_name, material);
		parser->ReadLeftCurly();
		GolMaterialParams params(fullIntensity);

		GolFileParser::ParserTokenType token = parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				params.m_ambient.m_red = parser->ReadInteger();
				params.m_ambient.m_grn = parser->ReadInteger();
				params.m_ambient.m_blu = parser->ReadInteger();
				params.m_ambient.m_alp = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x29:
				params.m_diffuse.m_red = parser->ReadInteger();
				params.m_diffuse.m_grn = parser->ReadInteger();
				params.m_diffuse.m_blu = parser->ReadInteger();
				params.m_diffuse.m_alp = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2a:
				params.m_flags &= ~GolMaterial::c_flagBit2;
				params.m_flags |= GolMaterial::c_flagBit1;
				break;
			case GolFileParser::e_unknown0x2b:
				params.m_flags &= ~GolMaterial::c_flagBit1;
				params.m_flags |= GolMaterial::c_flagBit2;
				break;
			case GolFileParser::e_unknown0x2c:
				::strncpy(textureName, parser->ReadStringWithMaxLength(sizeOfArray(textureName)), sizeof(textureName));
				params.m_texture = p_renderer->FindTextureByName(textureName);
				if (params.m_texture == NULL) {
					char message[128];
					::strcpy(message, "Mat def file references unknown texture: ");
					::strcat(message, textureName);
					GOL_FATALERROR_MESSAGE(message);
				}
				params.m_flags |= GolMaterial::c_flagBit3;
				break;
			case GolFileParser::e_unknown0x2d:
				params.m_flags &= ~GolMaterial::c_flagBit4;
				params.m_flags |= GolMaterial::c_flagBit5;
				break;
			case GolFileParser::e_unknown0x2e:
				params.m_flags &= ~GolMaterial::c_flagBit5;
				params.m_flags |= GolMaterial::c_flagBit4;
				break;
			case GolFileParser::e_unknown0x2f:
				params.m_flags &= ~GolMaterial::c_flagBit7;
				params.m_flags |= GolMaterial::c_flagBit6;
				switch (parser->GetNextToken()) {
				case GolFileParser::e_unknown0x30:
					params.m_alphaFunc = 0;
					break;
				case GolFileParser::e_unknown0x31:
					params.m_alphaFunc = 1;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x32:
					params.m_alphaFunc = 2;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x33:
					params.m_alphaFunc = 3;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x34:
					params.m_alphaFunc = 4;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x35:
					params.m_alphaFunc = 5;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x36:
					params.m_alphaFunc = 6;
					break;
				case GolFileParser::e_unknown0x37:
					params.m_alphaFunc = 7;
					params.m_alphaRef = parser->ReadInteger();
					break;
				default:
					if (params.m_alphaFunc != 0 && params.m_alphaFunc != 6) {
						params.m_alphaRef = parser->ReadInteger();
					}
					break;
				}
				break;
			case GolFileParser::e_unknown0x38: {
				undefined* ptr = &params.m_srcBlend;
				params.m_flags &= ~(GolMaterial::c_flagBit12 | GolMaterial::c_flagBit9);
				params.m_flags |= GolMaterial::c_flagBit8 | GolMaterial::c_flagBit13;
				for (j = 0; j < 2; j++) {
					switch (parser->GetNextToken()) {
					case GolFileParser::e_unknown0x39:
						*ptr = 0;
						break;
					case GolFileParser::e_unknown0x3a:
						*ptr = 1;
						break;
					case GolFileParser::e_unknown0x3b:
						*ptr = 2;
						break;
					case GolFileParser::e_unknown0x3c:
						*ptr = 3;
						break;
					case GolFileParser::e_unknown0x3d:
						*ptr = 4;
						break;
					case GolFileParser::e_unknown0x3e:
						*ptr = 5;
						break;
					case GolFileParser::e_unknown0x3f:
						*ptr = 6;
						break;
					case GolFileParser::e_unknown0x40:
						*ptr = 7;
						break;
					case GolFileParser::e_unknown0x41:
						*ptr = 8;
						break;
					case GolFileParser::e_unknown0x42:
						*ptr = 9;
						break;
					case GolFileParser::e_unknown0x43:
						*ptr = 10;
						break;
					default:
						parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
						break;
					}
					ptr = &params.m_destBlend;
				}
			} break;
			case GolFileParser::e_unknown0x44:
				params.m_flags &= ~GolMaterial::c_flagBit11;
				params.m_flags |= GolMaterial::c_flagBit10;
				break;
			case GolFileParser::e_unknown0x45:
				params.m_flags &= ~GolMaterial::c_flagBit10;
				params.m_flags |= GolMaterial::c_flagBit11;
				break;
			case GolFileParser::e_unknown0x47:
				params.m_flags |= GolMaterial::c_flagBit14;
				break;
			case GolFileParser::e_unknown0x48:
				params.m_flags &= ~GolMaterial::c_flagBit16;
				params.m_flags |= GolMaterial::c_flagBit15;
				break;
			case GolFileParser::e_unknown0x49:
				params.m_flags &= ~GolMaterial::c_flagBit15;
				params.m_flags |= GolMaterial::c_flagBit16;
				break;
			case GolFileParser::e_unknown0x4a:
				params.m_flags |= GolMaterial::c_flagBit17;
				break;
			case GolFileParser::e_unknown0x4b:
				params.m_flags &= ~GolMaterial::c_flagBit20;
				params.m_flags |= GolMaterial::c_flagBit19;
				break;
			case GolFileParser::e_unknown0x4c:
				params.m_flags &= ~GolMaterial::c_flagBit22;
				params.m_flags |= GolMaterial::c_flagBit21;
				break;
			case GolFileParser::e_unknown0x46:
			case GolFileParser::e_unknown0x4e:
				params.m_destBlend = parser->ReadInteger();
				params.m_flags &= ~(GolMaterial::c_flagBit8 | GolMaterial::c_flagBit13);
				params.m_flags |= GolMaterial::c_flagBit9 | GolMaterial::c_flagBit12;
				break;
			case GolFileParser::e_unknown0x4f:
				params.m_destBlend = parser->ReadInteger();
				params.m_flags = (params.m_flags & ~(GolMaterial::c_flagBit8 | GolMaterial::c_flagBit13)) |
								 (GolMaterial::c_flagBit9 | GolMaterial::c_flagBit12);
				break;
			case GolFileParser::e_unknown0x4d:
			case GolFileParser::e_unknown0x50:
				params.m_destBlend = parser->ReadInteger();
				params.m_flags &= ~(GolMaterial::c_flagBit8 | GolMaterial::c_flagBit13);
				params.m_flags |= GolMaterial::c_flagBit9 | GolMaterial::c_flagBit12;
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
			token = parser->GetNextToken();
		}
		material->m_nameRecord = name;
		material->SetParams(m_renderer, params);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	CreateMaterials();
	delete parser;
}

// FUNCTION: GOLDP 0x10026970
// FUNCTION: LEGORACERS 0x00410810
void GolMaterialLibrary::CreateMaterials()
{
	LegoU32 i;

	if (m_materialSource != NULL) {
		for (i = 0; i < m_numItems; i++) {
			GolMaterial* item = GetItem(i);
			if (!(item->GetFlags() & GolMaterial::c_flagBit0)) {
				GolMaterialParams params;
				m_materialSource->VTable0x00(i, &params);
				item->SetParams(m_renderer, params);
				VTable0x18(i);
			}
		}
	}
	else {
		for (i = 0; i < m_numItems; i++) {
			GolMaterial* item = GetItem(i);
			if (!(item->GetFlags() & GolMaterial::c_flagBit0)) {
				VTable0x18(i);
			}
		}
	}
}

// FUNCTION: GOLDP 0x10026a00
void GolMaterialLibrary::VTable0x20(GolRenderDevice* p_renderer, GolMaterialSource* p_arg2, LegoU32 p_capacity)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddMaterialList(this);
	m_materialSource = p_arg2;
	m_numItems = p_capacity;
	GolNameTable::Allocate(p_capacity);
	AllocateItems();
	CreateMaterials();
}

// FUNCTION: GOLDP 0x10026a50
void GolMaterialLibrary::Clear()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveMaterialList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10026a80
void GolMaterialLibrary::VTable0x1c(GolRenderDevice* p_renderer, LegoU32 p_capacity)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddMaterialList(this);
	m_numItems = p_capacity;
	GolNameTable::Allocate(p_capacity);
	AllocateItems();
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolMaterialLibrary::VTable0x0c()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolMaterialLibrary::VTable0x10()
{
	// empty
}

// FUNCTION: GOLDP 0x10028bc0
void GolRenderDevice::AddMaterialList(GolMaterialLibrary* p_param)
{
	p_param->SetNext(m_materialLists);
	m_materialLists = p_param;
}

// FUNCTION: GOLDP 0x10028bd0
void GolRenderDevice::RemoveMaterialList(GolMaterialLibrary* p_param)
{
	GolMaterialLibrary* node = m_materialLists;

	if (node != NULL) {
		if (p_param == node) {
			m_materialLists = node->GetNext();
			return;
		}

		GolMaterialLibrary* previous = node;
		node = node->GetNext();

		while (node != NULL) {
			if (node == p_param) {
				previous->SetNext(node->GetNext());
				node->SetNext(NULL);
				return;
			}

			previous = node;
			node = node->GetNext();
		}
	}
}

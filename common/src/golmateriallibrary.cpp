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
	m_itemCount = 0;
}

// FUNCTION: GOLDP 0x100261f0
GolMaterialLibrary::~GolMaterialLibrary()
{
	m_itemCount = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveMaterialList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10026270
void GolMaterialLibrary::Load(GolRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
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
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(MdbTxtParser::e_material));
	m_itemCount = parser->ReadBracketedCountAndLeftCurly();

	if (m_itemCount == 0) {
		parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	GolNameTable::Allocate(m_itemCount);
	AllocateItems();

	LegoU32 i;
	LegoU32 j;
	GolName textureName;
	LegoU8 fullIntensity = 0xff;

	for (i = 0; i < m_itemCount; i++) {
		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(MdbTxtParser::e_material));
		GolMaterial::NameRecord name;
		::strncpy(name.m_name, parser->ReadStringWithMaxLength(sizeOfArray(name.m_name)), sizeOfArray(name.m_name));
		GolMaterial* material = GetItem(i);
		AddName(name.m_name, material);
		parser->ReadLeftCurly();
		GolMaterialParams params(fullIntensity);

		GolFileParser::ParserTokenType token = parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case MdbTxtParser::e_ambient:
				params.m_ambient.m_red = parser->ReadInteger();
				params.m_ambient.m_grn = parser->ReadInteger();
				params.m_ambient.m_blu = parser->ReadInteger();
				params.m_ambient.m_alp = parser->ReadInteger();
				break;
			case MdbTxtParser::e_diffuse:
				params.m_diffuse.m_red = parser->ReadInteger();
				params.m_diffuse.m_grn = parser->ReadInteger();
				params.m_diffuse.m_blu = parser->ReadInteger();
				params.m_diffuse.m_alp = parser->ReadInteger();
				break;
			case MdbTxtParser::e_flatShading:
				params.m_flags &= ~GolMaterial::c_flagGouraudShading;
				params.m_flags |= GolMaterial::c_flagFlatShading;
				break;
			case MdbTxtParser::e_gouraudShading:
				params.m_flags &= ~GolMaterial::c_flagFlatShading;
				params.m_flags |= GolMaterial::c_flagGouraudShading;
				break;
			case MdbTxtParser::e_texture:
				::strncpy(textureName, parser->ReadStringWithMaxLength(sizeOfArray(textureName)), sizeof(textureName));
				params.m_texture = p_renderer->FindTextureByName(textureName);
				if (params.m_texture == NULL) {
					char message[128];
					::strcpy(message, "Mat def file references unknown texture: ");
					::strcat(message, textureName);
					GOL_FATALERROR_MESSAGE(message);
				}
				params.m_flags |= GolMaterial::c_flagTextured;
				break;
			case MdbTxtParser::e_modulate:
				params.m_flags &= ~GolMaterial::c_flagDecal;
				params.m_flags |= GolMaterial::c_flagModulate;
				break;
			case MdbTxtParser::e_decal:
				params.m_flags &= ~GolMaterial::c_flagModulate;
				params.m_flags |= GolMaterial::c_flagDecal;
				break;
			case MdbTxtParser::e_alphaTest:
				params.m_flags &= ~GolMaterial::c_flagNoAlphaTest;
				params.m_flags |= GolMaterial::c_flagAlphaTest;
				switch (parser->GetNextToken()) {
				case MdbTxtParser::e_alphaAlways:
					params.m_alphaFunc = 0;
					break;
				case MdbTxtParser::e_alphaEqual:
					params.m_alphaFunc = 1;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case MdbTxtParser::e_alphaGreater:
					params.m_alphaFunc = 2;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case MdbTxtParser::e_alphaGreaterEqual:
					params.m_alphaFunc = 3;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case MdbTxtParser::e_alphaLess:
					params.m_alphaFunc = 4;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case MdbTxtParser::e_alphaLessEqual:
					params.m_alphaFunc = 5;
					params.m_alphaRef = parser->ReadInteger();
					break;
				case MdbTxtParser::e_alphaNever:
					params.m_alphaFunc = 6;
					break;
				case MdbTxtParser::e_alphaNotEqual:
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
			case MdbTxtParser::e_blend: {
				undefined* ptr = &params.m_srcBlend;
				params.m_flags &= ~(GolMaterial::c_flagTransparent | GolMaterial::c_flagNoAlphaBlend);
				params.m_flags |= GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagNoTransparency;
				for (j = 0; j < 2; j++) {
					switch (parser->GetNextToken()) {
					case MdbTxtParser::e_blendZero:
						*ptr = 0;
						break;
					case MdbTxtParser::e_blendOne:
						*ptr = 1;
						break;
					case MdbTxtParser::e_blendSrcColor:
						*ptr = 2;
						break;
					case MdbTxtParser::e_blendDestColor:
						*ptr = 3;
						break;
					case MdbTxtParser::e_blendInvSrcColor:
						*ptr = 4;
						break;
					case MdbTxtParser::e_blendInvDestColor:
						*ptr = 5;
						break;
					case MdbTxtParser::e_blendSrcAlpha:
						*ptr = 6;
						break;
					case MdbTxtParser::e_blendDestAlpha:
						*ptr = 7;
						break;
					case MdbTxtParser::e_blendInvSrcAlpha:
						*ptr = 8;
						break;
					case MdbTxtParser::e_blendInvDestAlpha:
						*ptr = 9;
						break;
					case MdbTxtParser::e_blendSrcAlphaSat:
						*ptr = 10;
						break;
					default:
						parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
						break;
					}
					ptr = &params.m_destBlend;
				}
			} break;
			case MdbTxtParser::e_linearFilter:
				params.m_flags &= ~GolMaterial::c_flagPointFilter;
				params.m_flags |= GolMaterial::c_flagLinearFilter;
				break;
			case MdbTxtParser::e_pointFilter:
				params.m_flags &= ~GolMaterial::c_flagLinearFilter;
				params.m_flags |= GolMaterial::c_flagPointFilter;
				break;
			case MdbTxtParser::e_rotateVertices:
				params.m_flags |= GolMaterial::c_flagRotateVertices;
				break;
			case MdbTxtParser::e_wrap:
				params.m_flags &= ~GolMaterial::c_flagClamp;
				params.m_flags |= GolMaterial::c_flagWrap;
				break;
			case MdbTxtParser::e_clamp:
				params.m_flags &= ~GolMaterial::c_flagWrap;
				params.m_flags |= GolMaterial::c_flagClamp;
				break;
			case MdbTxtParser::e_unknown0x4a:
				params.m_flags |= GolMaterial::c_flagBit17;
				break;
			case MdbTxtParser::e_unknown0x4b:
				params.m_flags &= ~GolMaterial::c_flagBit20;
				params.m_flags |= GolMaterial::c_flagBit19;
				break;
			case MdbTxtParser::e_unknown0x4c:
				params.m_flags &= ~GolMaterial::c_flagBit22;
				params.m_flags |= GolMaterial::c_flagBit21;
				break;
			case MdbTxtParser::e_transparency:
			case MdbTxtParser::e_transparency3:
				params.m_destBlend = parser->ReadInteger();
				params.m_flags &= ~(GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagNoTransparency);
				params.m_flags |= GolMaterial::c_flagNoAlphaBlend | GolMaterial::c_flagTransparent;
				break;
			case MdbTxtParser::e_transparency4:
				params.m_destBlend = parser->ReadInteger();
				params.m_flags =
					(params.m_flags & ~(GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagNoTransparency)) |
					(GolMaterial::c_flagNoAlphaBlend | GolMaterial::c_flagTransparent);
				break;
			case MdbTxtParser::e_transparency2:
			case MdbTxtParser::e_transparency5:
				params.m_destBlend = parser->ReadInteger();
				params.m_flags &= ~(GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagNoTransparency);
				params.m_flags |= GolMaterial::c_flagNoAlphaBlend | GolMaterial::c_flagTransparent;
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
		for (i = 0; i < m_itemCount; i++) {
			GolMaterial* item = GetItem(i);
			if (!(item->GetFlags() & GolMaterial::c_flagCreated)) {
				GolMaterialParams params;
				m_materialSource->GetMaterialParams(i, &params);
				item->SetParams(m_renderer, params);
				CreateMaterial(i);
			}
		}
	}
	else {
		for (i = 0; i < m_itemCount; i++) {
			GolMaterial* item = GetItem(i);
			if (!(item->GetFlags() & GolMaterial::c_flagCreated)) {
				CreateMaterial(i);
			}
		}
	}
}

// FUNCTION: GOLDP 0x10026a00
void GolMaterialLibrary::InitializeFromSource(
	GolRenderDevice* p_renderer,
	GolMaterialSource* p_arg2,
	LegoU32 p_capacity
)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddMaterialList(this);
	m_materialSource = p_arg2;
	m_itemCount = p_capacity;
	GolNameTable::Allocate(p_capacity);
	AllocateItems();
	CreateMaterials();
}

// FUNCTION: GOLDP 0x10026a50
void GolMaterialLibrary::Clear()
{
	m_itemCount = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveMaterialList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10026a80
void GolMaterialLibrary::Initialize(GolRenderDevice* p_renderer, LegoU32 p_capacity)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddMaterialList(this);
	m_itemCount = p_capacity;
	GolNameTable::Allocate(p_capacity);
	AllocateItems();
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolMaterialLibrary::ReleaseMaterials()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolMaterialLibrary::RestoreMaterials()
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

#include "world/golworlddatabase.h"

#include "camera/goltransform.h"
#include "cmbmodelpart.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golboundedentity.h"
#include "golboundingshape.h"
#include "golboundingvolume.h"
#include "golcamerabase.h"
#include "golcollidableentity.h"
#include "golerror.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golmodelmaterialtable.h"
#include "golscenenode.h"
#include "mabmaterialanimation.h"
#include "mabmaterialtrack.h"
#include "render/rectangle.h"
#include "scene/golbillboard.h"

#include <float.h>

DECOMP_SIZE_ASSERT(GolWorldDatabase, 0xf0)
DECOMP_SIZE_ASSERT(GolWorldDatabase::WdbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(WdbModel, 0x8c)
DECOMP_SIZE_ASSERT(WdbCamera, 0x4c)
DECOMP_SIZE_ASSERT(WdbLight, 0x10)
DECOMP_SIZE_ASSERT(WdbBillboardSprite, 0x38)

// GLOBAL: GOLDP 0x100576e4
LegoFloat g_fltMax0x100576e4 = FLT_MAX;

static const LegoFloat g_floatyBoatMaxFloat = FLT_MAX;

// GLOBAL: GOLDP 0x100576e8
LegoFloat g_fltMax0x100576e8 = FLT_MAX;

// GLOBAL: GOLDP 0x1005cf0c
undefined4 g_loadTexturesImmediately = 1;

// FUNCTION: GOLDP 0x1002baf0
void SetLoadTexturesImmediately(undefined4 p_arg)
{
	g_loadTexturesImmediately = p_arg;
}

// FUNCTION: GOLDP 0x1002c030
GolWorldDatabase::GolWorldDatabase()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002c0e0
void GolWorldDatabase::Reset()
{
	m_worldScale = 1.0f;
	m_renderer = 0;
	m_textureListCount = 0;
	m_textureListNames = NULL;
	m_materialLibraryCount = 0;
	m_materialLibraryNames = NULL;
	m_modelPartCount = 0;
	m_modelPartNames = NULL;
	m_modelCount = 0;
	m_modelNames = NULL;
	m_materialTableCount = 0;
	m_materialTableNames = NULL;
	m_sceneNodeCount = 0;
	m_sceneNodeNames = NULL;
	m_boundingShapeCount = 0;
	m_boundingShapeNames = NULL;
	m_boundingVolumeCount = 0;
	m_boundingVolumeNames = NULL;
	m_modelEntityCount = 0;
	m_modelEntityRecords = NULL;
	m_animatedEntityCount = 0;
	m_animatedEntityRecords = NULL;
	m_collidableEntityCount = 0;
	m_collidableEntityRecords = NULL;
	m_boundedEntityCount = 0;
	m_boundedEntityRecords = NULL;
	m_spriteCount = 0;
	m_spriteRecords = NULL;
	m_materialAnimationCount = 0;
	m_materialAnimationNames = NULL;
	m_cameraCount = 0;
	m_cameraRecords = NULL;
	m_ambientLightCount = 0;
	m_ambientLightRecords = NULL;
	m_lightCount = 0;
	m_lightRecords = NULL;
	m_binary = FALSE;
	m_boundingVolumes = 0;
	m_modelEntities = 0;
	m_animatedEntities = 0;
	m_collidableEntities = NULL;
	m_boundedEntities = 0;
	m_ambientMaterial = 0;
	m_light = 0;
}

// FUNCTION: GOLDP 0x1002c1a0
GolWorldDatabase::~GolWorldDatabase()
{
	Destroy();
}

// FUNCTION: GOLDP 0x1002c240
void GolWorldDatabase::Load(GolRenderDevice* p_arg1, const LegoChar* p_name, LegoBool32 p_binary, LegoFloat p_arg4)
{
	if (m_renderer) {
		Destroy();
	}

	m_renderer = p_arg1;
	m_worldScale = p_arg4;

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".wdb");
	}
	else {
		parser = new WdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	m_binary = p_binary;

	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		switch (token) {
		case WdbTxtParser::e_textureLists:
			ParseTextureListNames(*parser);
			break;
		case WdbTxtParser::e_materialLibraries:
			ParseMaterialLibraryNames(*parser);
			break;
		case WdbTxtParser::e_modelParts:
			ParseModelPartNames(*parser);
			break;
		case WdbTxtParser::e_models:
			ParseModelNames(*parser);
			break;
		case WdbTxtParser::e_materialTables:
			ParseMaterialTableNames(*parser);
			break;
		case WdbTxtParser::e_sceneNodes:
			ParseSceneNodeNames(*parser);
			break;
		case WdbTxtParser::e_boundingShapes:
			ParseBoundingShapeNames(*parser);
			break;
		case WdbTxtParser::e_boundingVolumes:
			ParseBoundingVolumeNames(*parser);
			break;
		case WdbTxtParser::e_modelEntities:
			ParseModelEntities(*parser);
			break;
		case WdbTxtParser::e_animatedEntities:
			ParseAnimatedEntities(*parser);
			break;
		case WdbTxtParser::e_collidableEntities:
			ParseCollidableEntities(*parser);
			break;
		case WdbTxtParser::e_boundedEntities:
			ParseBoundedEntities(*parser);
			break;
		case WdbTxtParser::e_sprites:
			ParseSprites(*parser);
			break;
		case WdbTxtParser::e_materialAnimations:
			ParseMaterialAnimationNames(*parser);
			break;
		case WdbTxtParser::e_cameras:
			ParseCameras(*parser);
			break;
		case WdbTxtParser::e_ambientLights:
			ParseAmbientLights(*parser);
			break;
		case WdbTxtParser::e_lights:
			ParseLights(*parser);
			break;
		}
	}

	parser->Dispose();
	AllocateResources();
	AllocateEntities();
	LoadResources();
	InitializeEntities();

	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x1002c4d0
void GolWorldDatabase::DestroyRecords()
{
	if (m_lightRecords != NULL) {
		delete[] m_lightRecords;
		m_lightRecords = NULL;
	}

	if (m_ambientLightRecords != NULL) {
		delete[] m_ambientLightRecords;
		m_ambientLightRecords = NULL;
	}

	if (m_cameraRecords != NULL) {
		delete[] m_cameraRecords;
		m_cameraRecords = NULL;
	}

	if (m_spriteRecords != NULL) {
		delete[] m_spriteRecords;
		m_spriteRecords = NULL;
	}

	if (m_boundedEntityRecords != NULL) {
		delete[] m_boundedEntityRecords;
		m_boundedEntityRecords = NULL;
	}

	if (m_collidableEntityRecords != NULL) {
		for (LegoU32 i = 0; i < m_collidableEntityCount; i++) {
			if (m_collidableEntityRecords[i].m_animationBindings != NULL) {
				delete[] m_collidableEntityRecords[i].m_animationBindings;
			}
		}

		delete[] m_collidableEntityRecords;
		m_collidableEntityRecords = NULL;
	}

	if (m_animatedEntityRecords != NULL) {
		for (LegoU32 i = 0; i < m_animatedEntityCount; i++) {
			if (m_animatedEntityRecords[i].m_animationBindings != NULL) {
				delete[] m_animatedEntityRecords[i].m_animationBindings;
			}
		}

		delete[] m_animatedEntityRecords;
		m_animatedEntityRecords = NULL;
	}

	if (m_modelEntityRecords != NULL) {
		for (LegoU32 i = 0; i < m_modelEntityCount; i++) {
			if (m_modelEntityRecords[i].m_animationBindings != NULL) {
				delete[] m_modelEntityRecords[i].m_animationBindings;
			}
		}

		delete[] m_modelEntityRecords;
		m_modelEntityRecords = NULL;
	}

	if (m_boundingShapeNames != NULL) {
		delete[] m_boundingShapeNames;
		m_boundingShapeNames = NULL;
	}

	if (m_boundingVolumeNames != NULL) {
		delete[] m_boundingVolumeNames;
		m_boundingVolumeNames = NULL;
	}

	if (m_sceneNodeNames != NULL) {
		delete[] m_sceneNodeNames;
		m_sceneNodeNames = NULL;
	}

	if (m_materialTableNames != NULL) {
		delete[] m_materialTableNames;
		m_materialTableNames = NULL;
	}

	if (m_modelNames != NULL) {
		delete[] m_modelNames;
		m_modelNames = NULL;
	}

	if (m_modelPartNames != NULL) {
		delete[] m_modelPartNames;
		m_modelPartNames = NULL;
	}

	if (m_materialLibraryNames != NULL) {
		delete[] m_materialLibraryNames;
		m_materialLibraryNames = NULL;
	}

	if (m_textureListNames != NULL) {
		delete[] m_textureListNames;
		m_textureListNames = NULL;
	}
}

// FUNCTION: GOLDP 0x1002c6b0
void GolWorldDatabase::Destroy()
{
	DestroyRecords();

	if (m_materialAnimationNames != NULL) {
		delete[] m_materialAnimationNames;
		m_materialAnimationNames = NULL;
	}

	m_cameraNames.Clear();
	m_modelEntityNames.Clear();
	m_animatedEntityNames.Clear();
	m_collidableEntityNames.Clear();
	m_boundedEntityNames.Clear();

	if (m_boundedEntities != NULL) {
		delete[] m_boundedEntities;
	}

	if (m_collidableEntities != NULL) {
		delete[] m_collidableEntities;
	}

	if (m_animatedEntities != NULL) {
		delete[] m_animatedEntities;
	}

	if (m_modelEntities != NULL) {
		delete[] m_modelEntities;
	}

	if (m_boundingVolumes != NULL) {
		delete[] m_boundingVolumes;
	}

	if (m_ambientMaterial != NULL) {
		delete[] m_ambientMaterial;
	}

	if (m_light != NULL) {
		delete[] m_light;
	}

	Reset();
}

// FUNCTION: GOLDP 0x1002c7b0
void GolWorldDatabase::ParseTextureListNames(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_textureListNames != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_textureListCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_textureListCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_textureListNames = new GolName[m_textureListCount];
	if (m_textureListNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_textureListCount; i++) {
		::strncpy(m_textureListNames[i], p_parser.ReadString(), sizeOfArray(m_textureListNames[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002c840
void GolWorldDatabase::ParseMaterialLibraryNames(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_materialLibraryNames != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_materialLibraryCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_materialLibraryCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_materialLibraryNames = new GolName[m_materialLibraryCount];
	if (m_materialLibraryNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_materialLibraryCount; i++) {
		::strncpy(m_materialLibraryNames[i], p_parser.ReadString(), sizeOfArray(m_materialLibraryNames[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002c8d0
void GolWorldDatabase::ParseModelPartNames(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_modelPartNames != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_modelPartCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_modelPartCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_modelPartNames = new GolName[m_modelPartCount];
	if (m_modelPartNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_modelPartCount; i++) {
		::strncpy(m_modelPartNames[i], p_parser.ReadString(), sizeOfArray(m_modelPartNames[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002c960
void GolWorldDatabase::ParseModelNames(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_modelNames != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_modelCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_modelCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_modelNames = new GolName[m_modelCount];
	if (m_modelNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_modelCount; i++) {
		::strncpy(m_modelNames[i], p_parser.ReadString(), sizeOfArray(m_modelNames[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002c9f0
void GolWorldDatabase::ParseMaterialTableNames(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_materialTableNames != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_materialTableCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_materialTableCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_materialTableNames = new GolName[m_materialTableCount];
	if (m_materialTableNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_materialTableCount; i++) {
		::strncpy(m_materialTableNames[i], p_parser.ReadString(), sizeOfArray(m_materialTableNames[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002ca80
void GolWorldDatabase::ParseSceneNodeNames(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_sceneNodeNames != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_sceneNodeCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_sceneNodeCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_sceneNodeNames = new GolName[m_sceneNodeCount];
	if (m_sceneNodeNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_sceneNodeCount; i++) {
		::strncpy(m_sceneNodeNames[i], p_parser.ReadString(), sizeOfArray(m_sceneNodeNames[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002cb10
void GolWorldDatabase::ParseBoundingShapeNames(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_boundingShapeNames != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_boundingShapeCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_boundingShapeCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_boundingShapeNames = new GolName[m_boundingShapeCount];
	if (m_boundingShapeNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_boundingShapeCount; i++) {
		::strncpy(m_boundingShapeNames[i], p_parser.ReadString(), sizeOfArray(m_boundingShapeNames[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002cba0
void GolWorldDatabase::ParseBoundingVolumeNames(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_boundingVolumeNames != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_boundingVolumeCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_boundingVolumeCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_boundingVolumeNames = new GolName[m_boundingVolumeCount];
	if (m_boundingVolumeNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_boundingVolumeCount; i++) {
		::strncpy(m_boundingVolumeNames[i], p_parser.ReadString(), sizeOfArray(m_boundingVolumeNames[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002cc30
void GolWorldDatabase::ParseModelEntities(GolFileParser& p_parser)
{
	LegoU32 i;
	LegoS32 v;

	if (m_modelEntityRecords != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_modelEntityCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_modelEntityCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_modelEntityRecords = new WdbModel[m_modelEntityCount];
	if (m_modelEntityRecords == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_modelEntityRecords, 0, sizeof(*m_modelEntityRecords) * m_modelEntityCount);
	WdbModel* item = m_modelEntityRecords;
	for (i = 0; i < m_modelEntityCount; item++, i++) {
		LegoU32 cnt = 0;
		p_parser.AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(WdbTxtParser::e_modelEntities));
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetReplayToken(1);
			item->m_name[0] = '\0';
		}
		else {
			::strncpy(item->m_name, p_parser.GetLastString(), sizeof(item->m_name));
		}
		p_parser.ReadLeftCurly();
		LegoU32 j;
		for (j = 0; j < 3; j++) {
			item->m_modelIndices[j] = -1;
			item->m_materialTableIndices[j] = -1;
		}
		item->m_direction.m_x = 1.0f;
		item->m_up.m_z = 1.0f;
		item->m_scale = 1.0f;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case WdbTxtParser::e_models:
				if (p_parser.GetNextToken() != GolFileParser::e_int) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_int);
				}
				if (static_cast<LegoU32>(p_parser.GetLastInt()) >= m_modelCount && m_modelCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_modelIndices[cnt] = p_parser.GetLastInt();
				if (p_parser.GetNextToken() != GolFileParser::e_float) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_float);
				}
				if (p_parser.GetLastFloat() < 0.0f) {
					item->m_modelDistances[cnt] = g_fltMax0x100576e4;
				}
				else {
					item->m_modelDistances[cnt] = p_parser.GetLastFloat();
				}
				cnt++;
				break;
			case WdbTxtParser::e_position:
				item->m_position.m_x = p_parser.ReadFloat();
				item->m_position.m_y = p_parser.ReadFloat();
				item->m_position.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_orientation:
				item->m_direction.m_x = p_parser.ReadFloat();
				item->m_direction.m_y = p_parser.ReadFloat();
				item->m_direction.m_z = p_parser.ReadFloat();
				item->m_up.m_x = p_parser.ReadFloat();
				item->m_up.m_y = p_parser.ReadFloat();
				item->m_up.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_materialAssignment:
				if (p_parser.GetNextToken() != GolFileParser::e_int) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_int);
				}
				if (static_cast<LegoU32>(p_parser.GetLastInt()) >= m_materialTableCount && m_materialTableCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				v = p_parser.GetLastInt();
				if (p_parser.GetNextToken() != GolFileParser::e_int) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_int);
				}
				if (p_parser.GetLastInt() >= static_cast<LegoS32>(sizeOfArray(item->m_materialTableIndices))) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_materialTableIndices[p_parser.GetLastInt()] = v;
				break;
			case WdbTxtParser::e_scale:
				item->m_scale = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_materialAnimation:
				ParseAnimationBindings(p_parser, &item->m_animationBindings, &item->m_animationBindingCount);
				break;
			case WdbTxtParser::e_textureScroll:
				item->m_flags |= WdbModel::e_flagTextureScroll;
				item->m_textureScrollSpeedU = p_parser.ReadFloat();
				item->m_textureScrollSpeedV = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_modelFlag1:
				item->m_flags |= WdbModel::e_flagBit1;
				break;
			case WdbTxtParser::e_modelFlag2:
				item->m_flags |= WdbModel::e_flagBit2;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002cfa0
void GolWorldDatabase::ParseAnimatedEntities(GolFileParser& p_parser)
{
	LegoU32 i;
	LegoS32 v;

	if (m_animatedEntityRecords != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_animatedEntityCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_animatedEntityCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_animatedEntityRecords = new WdbModel[m_animatedEntityCount];
	if (m_animatedEntityRecords == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_animatedEntityRecords, 0, sizeof(*m_animatedEntityRecords) * m_animatedEntityCount);
	WdbModel* item = m_animatedEntityRecords;
	for (i = 0; i < m_animatedEntityCount; item++, i++) {
		p_parser.AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(WdbTxtParser::e_animatedEntities));
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetReplayToken(1);
			item->m_name[0] = '\0';
		}
		else {
			::strncpy(item->m_name, p_parser.GetLastString(), sizeof(item->m_name));
		}
		p_parser.ReadLeftCurly();
		LegoU32 cnt = 0;
		for (cnt = 0; cnt < 3; cnt++) {
			item->m_modelIndices[cnt] = -1;
			item->m_sceneNodeIndices[cnt] = -1;
			item->m_materialTableIndices[cnt] = -1;
		}
		cnt = 0;
		item->m_nodeIndex = -1;
		item->m_direction.m_x = 1.0f;
		item->m_up.m_z = 1.0f;
		item->m_scale = 1.0f;
		item->m_nodeName[0] = '\0';
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case WdbTxtParser::e_jointedModel:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_modelCount && m_modelCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_modelIndices[cnt] = p_parser.GetLastInt();
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_sceneNodeCount && m_sceneNodeCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_sceneNodeIndices[cnt] = p_parser.GetLastInt();
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_modelPartCount && m_modelPartCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_modelPartIndices[cnt] = p_parser.GetLastInt();
				if (p_parser.ReadFloat() < 0.0f) {
					item->m_modelDistances[cnt] = g_fltMax0x100576e4;
				}
				else {
					item->m_modelDistances[cnt] = p_parser.GetLastFloat();
				}
				cnt += 1;
				break;
			case WdbTxtParser::e_nodeLod:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_sceneNodeCount && m_sceneNodeCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_sceneNodeIndices[cnt] = p_parser.GetLastInt();
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_modelPartCount && m_modelPartCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_modelPartIndices[cnt] = p_parser.GetLastInt();
				if (p_parser.ReadFloat() < 0.0f) {
					item->m_modelDistances[cnt] = g_fltMax0x100576e4;
				}
				else {
					item->m_modelDistances[cnt] = p_parser.GetLastFloat();
				}
				cnt += 1;
				break;
			case WdbTxtParser::e_position:
				item->m_position.m_x = p_parser.ReadFloat();
				item->m_position.m_y = p_parser.ReadFloat();
				item->m_position.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_orientation:
				item->m_direction.m_x = p_parser.ReadFloat();
				item->m_direction.m_y = p_parser.ReadFloat();
				item->m_direction.m_z = p_parser.ReadFloat();
				item->m_up.m_x = p_parser.ReadFloat();
				item->m_up.m_y = p_parser.ReadFloat();
				item->m_up.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_materialAssignment:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_materialTableCount && m_materialTableCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				v = p_parser.GetLastInt();
				if (p_parser.ReadInteger() >= static_cast<LegoS32>(sizeOfArray(item->m_materialTableIndices))) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_materialTableIndices[p_parser.GetLastInt()] = v;
				break;
			case WdbTxtParser::e_node:
				token = p_parser.GetNextToken();
				if (token == GolFileParser::e_string) {
					item->m_nodeIndex = -1;
					::strncpy(item->m_nodeName, p_parser.GetLastString(), sizeof(item->m_nodeName));
				}
				else {
					if (token != GolFileParser::e_int) {
						p_parser.HandleUnexpectedToken(GolFileParser::e_int);
					}
					item->m_nodeIndex = p_parser.GetLastInt();
					item->m_nodeName[0] = '\0';
				}
				break;
			case WdbTxtParser::e_scale:
				item->m_scale = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_materialAnimation:
				ParseAnimationBindings(p_parser, &item->m_animationBindings, &item->m_animationBindingCount);
				break;
			case WdbTxtParser::e_lod:
				item->m_flags |= WdbModel::e_flagTextureScroll;
				item->m_textureScrollSpeedU = p_parser.ReadFloat();
				item->m_textureScrollSpeedV = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_modelFlag1:
				item->m_flags |= WdbModel::e_flagBit1;
				break;
			case WdbTxtParser::e_modelFlag2:
				item->m_flags |= WdbModel::e_flagBit2;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002d400
void GolWorldDatabase::ParseCollidableEntities(GolFileParser& p_parser)
{
	LegoU32 i;
	LegoS32 v;

	if (m_collidableEntityRecords != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_collidableEntityCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_collidableEntityCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_collidableEntityRecords = new WdbModel[m_collidableEntityCount];
	if (m_collidableEntityRecords == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_collidableEntityRecords, 0, sizeof(*m_collidableEntityRecords) * m_collidableEntityCount);
	WdbModel* item = m_collidableEntityRecords;
	for (i = 0; i < m_collidableEntityCount; item++, i++) {
		p_parser.AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(WdbTxtParser::e_collidableEntities));
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetReplayToken(1);
			item->m_name[0] = '\0';
		}
		else {
			::strncpy(item->m_name, p_parser.GetLastString(), sizeof(item->m_name));
		}
		p_parser.ReadLeftCurly();
		LegoU32 cnt = 0;
		for (cnt = 0; cnt < 3; cnt++) {
			item->m_modelIndices[cnt] = -1;
			item->m_materialTableIndices[cnt] = -1;
		}
		cnt = 0;
		item->m_direction.m_x = 1.0f;
		item->m_up.m_z = 1.0f;
		item->m_scale = 1.0f;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case WdbTxtParser::e_collidableModel:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_modelCount && m_modelCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_modelIndices[cnt] = p_parser.GetLastInt();
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_boundingShapeCount && m_boundingShapeCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_sceneNodeIndices[cnt] = p_parser.GetLastInt();
				if (p_parser.ReadFloat() < 0.0f) {
					item->m_modelDistances[cnt] = g_fltMax0x100576e4;
				}
				else {
					item->m_modelDistances[cnt] = p_parser.GetLastFloat();
				}
				cnt += 1;
				break;
			case WdbTxtParser::e_position:
				item->m_position.m_x = p_parser.ReadFloat();
				item->m_position.m_y = p_parser.ReadFloat();
				item->m_position.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_orientation:
				item->m_direction.m_x = p_parser.ReadFloat();
				item->m_direction.m_y = p_parser.ReadFloat();
				item->m_direction.m_z = p_parser.ReadFloat();
				item->m_up.m_x = p_parser.ReadFloat();
				item->m_up.m_y = p_parser.ReadFloat();
				item->m_up.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_materialAssignment:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_materialTableCount && m_materialTableCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				v = p_parser.GetLastInt();
				if (p_parser.ReadInteger() >= static_cast<LegoS32>(sizeOfArray(item->m_materialTableIndices))) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_materialTableIndices[p_parser.GetLastInt()] = v;
				break;
			case WdbTxtParser::e_materialAnimation:
				ParseAnimationBindings(p_parser, &item->m_animationBindings, &item->m_animationBindingCount);
				break;
			case WdbTxtParser::e_lod:
				item->m_flags |= WdbModel::e_flagTextureScroll;
				item->m_textureScrollSpeedU = p_parser.ReadFloat();
				item->m_textureScrollSpeedV = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_modelFlag1:
				item->m_flags |= WdbModel::e_flagBit1;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002d720
void GolWorldDatabase::ParseBoundedEntities(GolFileParser& p_parser)
{
	LegoU32 i;
	LegoS32 v;

	if (m_boundedEntityRecords != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_boundedEntityCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_boundedEntityCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_boundedEntityRecords = new WdbModel[m_boundedEntityCount];
	if (m_boundedEntityRecords == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_boundedEntityRecords, 0, sizeof(*m_boundedEntityRecords) * m_boundedEntityCount);
	WdbModel* item = m_boundedEntityRecords;
	for (i = 0; i < m_boundedEntityCount; item++, i++) {
		p_parser.AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(WdbTxtParser::e_boundedEntities));
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetReplayToken(1);
			item->m_name[0] = '\0';
		}
		else {
			::strncpy(item->m_name, p_parser.GetLastString(), sizeof(item->m_name));
		}
		p_parser.ReadLeftCurly();
		item->m_materialTableIndices[0] = -1;
		item->m_direction.m_x = 1.0f;
		item->m_up.m_z = 1.0f;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case WdbTxtParser::e_boundingVolumeRef:
				item->m_sceneNodeIndices[0] = v = p_parser.ReadInteger();
				if (static_cast<LegoU32>(v) >= m_boundingVolumeCount && m_boundingVolumeCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				break;
			case WdbTxtParser::e_position:
				item->m_position.m_x = p_parser.ReadFloat();
				item->m_position.m_y = p_parser.ReadFloat();
				item->m_position.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_orientation:
				item->m_direction.m_x = p_parser.ReadFloat();
				item->m_direction.m_y = p_parser.ReadFloat();
				item->m_direction.m_z = p_parser.ReadFloat();
				item->m_up.m_x = p_parser.ReadFloat();
				item->m_up.m_y = p_parser.ReadFloat();
				item->m_up.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_materialAssignment:
				v = p_parser.ReadInteger();
				if (static_cast<LegoU32>(v) >= m_materialTableCount && m_materialTableCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_materialTableIndices[0] = v;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002d950
void GolWorldDatabase::ParseSprites(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_spriteRecords != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_spriteCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_spriteCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_spriteRecords = new WdbBillboardSprite[m_spriteCount];
	if (m_spriteRecords == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_spriteRecords, 0, sizeof(*m_spriteRecords) * m_spriteCount);
	WdbBillboardSprite* item = m_spriteRecords;
	for (i = 0; i < m_spriteCount; item++, i++) {
		p_parser.AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(WdbTxtParser::e_sprites));
		p_parser.ReadLeftCurly();
		item->m_maxDistance = g_fltMax0x100576e8;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case WdbTxtParser::e_materialAssignment:
				item->m_flags |= WdbBillboardSprite::c_flagMaterialAssignment;
				item->m_materialTableIndex = p_parser.ReadInteger();
				item->m_materialIndex = p_parser.ReadInteger();
				break;
			case WdbTxtParser::e_position:
				item->m_position.m_x = p_parser.ReadFloat();
				item->m_position.m_y = p_parser.ReadFloat();
				item->m_position.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_axis:
				item->m_flags |= WdbBillboardSprite::c_flagAxisLocked;
				item->m_axis.m_x = p_parser.ReadFloat();
				item->m_axis.m_y = p_parser.ReadFloat();
				item->m_axis.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_materialName:
				::strncpy(item->m_materialName, p_parser.ReadString(), sizeof(item->m_materialName));
				break;
			case WdbTxtParser::e_width:
				item->m_width = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_height:
				item->m_height = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_maxDistance:
				item->m_maxDistance = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_materialAnimation:
				item->m_hasMaterialAnimation = 1;
				item->m_materialAnimationIndex = p_parser.ReadInteger();
				item->m_materialTrackIndex = p_parser.ReadInteger();
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002db50
void GolWorldDatabase::ParseMaterialAnimationNames(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_materialAnimationNames != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_materialAnimationCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_materialAnimationCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_materialAnimationNames = new GolName[m_materialAnimationCount];
	if (m_materialAnimationNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_materialAnimationCount; i++) {
		::strncpy(m_materialAnimationNames[i], p_parser.ReadString(), sizeOfArray(m_materialAnimationNames[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002dbe0
void GolWorldDatabase::ParseAnimationBindings(GolFileParser& p_parser, Rect** p_rects, LegoU32* p_count)
{
	LegoU32 i;
	LegoU32 count;
	Rect* rects;

	if (*p_rects != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	*p_count = count = p_parser.ReadBracketedCountAndLeftCurly();
	if (count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	*p_rects = rects = new Rect[count];
	if (rects == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	Rect* item = rects;
	for (i = 0; i < count; item++, i++) {
		item->m_left = p_parser.ReadInteger();
		item->m_top = p_parser.ReadInteger();
		item->m_right = p_parser.ReadInteger();
		item->m_bottom = p_parser.ReadInteger();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002dc80
void GolWorldDatabase::ParseCameras(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_cameraRecords != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_cameraCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_cameraCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_cameraRecords = new WdbCamera[m_cameraCount];
	if (m_cameraRecords == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	GolVec3 pos;
	pos.m_x = 0.0f;
	pos.m_y = 0.0f;
	pos.m_z = 0.0f;
	::memset(m_cameraRecords, 0, sizeof(*m_cameraRecords) * m_cameraCount);
	WdbCamera* item = m_cameraRecords;
	for (i = 0; i < m_cameraCount; item++, i++) {
		p_parser.AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(WdbTxtParser::e_cameras));
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetReplayToken(1);
			item->m_name[0] = '\0';
		}
		else {
			::strncpy(item->m_name, p_parser.GetLastString(), sizeof(item->m_name));
		}
		p_parser.ReadLeftCurly();
		item->m_animatedEntityIndex = -1;
		item->m_direction.m_x = 1.0f;
		item->m_up.m_z = -1.0f;
		item->m_nearClip = 1.0f;
		item->m_farClip = 100.0f;
		item->m_fov = 65.0f;
		LegoBool32 seen = FALSE;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case WdbTxtParser::e_trackedEntity:
				item->m_animatedEntityIndex = p_parser.ReadInteger();
				if (static_cast<LegoU32>(item->m_animatedEntityIndex) >= m_animatedEntityCount &&
					m_animatedEntityCount != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_trackedNodeIndex = p_parser.ReadInteger();
				break;
			case WdbTxtParser::e_node:
				token = p_parser.GetNextToken();
				if (token == GolFileParser::e_string) {
					item->m_partIndex = -1;
					::strncpy(item->m_partName, p_parser.GetLastString(), sizeof(item->m_partName));
				}
				else {
					if (token != GolFileParser::e_int) {
						p_parser.HandleUnexpectedToken(GolFileParser::e_int);
					}
					item->m_partIndex = p_parser.GetLastInt();
					item->m_partName[0] = '\0';
				}
				break;
			case WdbTxtParser::e_position:
				item->m_position.m_x = p_parser.ReadFloat();
				item->m_position.m_y = p_parser.ReadFloat();
				item->m_position.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_target:
				seen = TRUE;
				pos.m_x = p_parser.ReadFloat();
				pos.m_y = p_parser.ReadFloat();
				pos.m_z = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_orientation:
				item->m_direction.m_x = p_parser.ReadFloat();
				item->m_direction.m_y = p_parser.ReadFloat();
				item->m_direction.m_z = p_parser.ReadFloat();
				item->m_up.m_x = -p_parser.ReadFloat();
				item->m_up.m_y = -p_parser.ReadFloat();
				item->m_up.m_z = -p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_nearClip:
				item->m_nearClip = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_farClip:
				item->m_farClip = p_parser.ReadFloat();
				break;
			case WdbTxtParser::e_fov:
				item->m_fov = p_parser.ReadFloat();
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
		if (seen) {
			item->m_direction.m_x = pos.m_x - item->m_position.m_x;
			item->m_direction.m_y = pos.m_y - item->m_position.m_y;
			item->m_direction.m_z = pos.m_z - item->m_position.m_z;
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002df90
void GolWorldDatabase::ParseAmbientLights(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_ambientLightRecords != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_ambientLightCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_ambientLightCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_ambientLightRecords = new WdbLight[m_ambientLightCount];
	if (m_ambientLightRecords == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_ambientLightRecords, 0, sizeof(*m_ambientLightRecords) * m_ambientLightCount);
	for (i = 0; i < m_ambientLightCount; i++) {
		p_parser.AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(WdbTxtParser::e_ambientLights));
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetReplayToken(1);
		}
		p_parser.ReadLeftCurly();
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case WdbTxtParser::e_color:
				m_ambientLightRecords[i].m_color.m_red = p_parser.ReadInteger();
				m_ambientLightRecords[i].m_color.m_grn = p_parser.ReadInteger();
				m_ambientLightRecords[i].m_color.m_blu = p_parser.ReadInteger();
				m_ambientLightRecords[i].m_color.m_alp = 0xff;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002e0d0
void GolWorldDatabase::ParseLights(GolFileParser& p_parser)
{
	LegoU32 i;
	if (m_lightRecords != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_lightCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_lightCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_lightRecords = new WdbLight[m_lightCount];
	if (m_lightRecords == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_lightRecords, 0, sizeof(*m_lightRecords) * m_lightCount);
	for (i = 0; i < m_lightCount; i++) {
		p_parser.AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(WdbTxtParser::e_lights));
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetReplayToken(1);
		}
		p_parser.ReadLeftCurly();
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case WdbTxtParser::e_color:
				m_lightRecords[i].m_color.m_red = p_parser.ReadInteger();
				m_lightRecords[i].m_color.m_grn = p_parser.ReadInteger();
				m_lightRecords[i].m_color.m_blu = p_parser.ReadInteger();
				m_lightRecords[i].m_color.m_alp = 0xff;
				break;
			case WdbTxtParser::e_direction:
				m_lightRecords[i].m_direction.m_x = p_parser.ReadFloat();
				m_lightRecords[i].m_direction.m_y = p_parser.ReadFloat();
				m_lightRecords[i].m_direction.m_z = p_parser.ReadFloat();
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002e250
void GolWorldDatabase::BindSpriteMaterialAnimation(GolBillboard* p_billboard, WdbBillboardSprite* p_sprite)
{
	if (p_sprite->m_hasMaterialAnimation == 0) {
		return;
	}

	if (!(p_billboard->GetFlags() & GolBillboard::c_flagMaterialAssignment)) {
		GOL_FATALERROR_MESSAGE("Mat animation invalid for sprites without mat assignment");
	}

	LegoU32 animationIndex = p_sprite->m_materialAnimationIndex;
	if (animationIndex >= m_materialAnimationCount) {
		return;
	}

	LegoU32 materialIndex = p_sprite->m_materialTrackIndex;
	MabMaterialTrack* item = GetMaterialAnimation(animationIndex)->GetTracks();
	item[materialIndex].Assign(p_billboard->GetMaterialTable(), p_sprite->m_materialIndex, TRUE);
}

// FUNCTION: GOLDP 0x1002e2c0
void GolWorldDatabase::AllocateEntities()
{
	if (m_boundingVolumeCount != 0) {
		m_boundingVolumes = new GolBoundingVolume[m_boundingVolumeCount];
		if (m_boundingVolumes == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_modelEntityCount != 0) {
		m_modelEntities = new GolModelEntity[m_modelEntityCount];
		if (m_modelEntities == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_animatedEntityCount != 0) {
		m_animatedEntities = new GolAnimatedEntity[m_animatedEntityCount];
		if (m_animatedEntities == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_collidableEntityCount != 0) {
		m_collidableEntities = new GolCollidableEntity[m_collidableEntityCount];
		if (m_collidableEntities == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_boundedEntityCount != 0) {
		m_boundedEntities = new GolBoundedEntity[m_boundedEntityCount];
		if (m_boundedEntities == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_ambientLightCount != 0) {
		m_ambientMaterial = new GolRenderDevice::MaterialColor[m_ambientLightCount];
		if (m_ambientMaterial == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_lightCount != 0) {
		m_light = new GolRenderDevice::Light[m_lightCount];
		if (m_light == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// STUB: GOLDP 0x1002e640
void GolWorldDatabase::InitializeEntities()
{
	LegoU32 i;
	LegoU32 j;
	LegoU32 lod;
	LegoFloat maxDistances[3];

	for (i = 0; i < m_modelEntityCount; i++) {
		WdbModel* model = &m_modelEntityRecords[i];
		GolModelEntity* runtime = &m_modelEntities[i];

		if (static_cast<LegoU32>(model->m_modelIndices[0]) >= m_modelCount) {
			GOL_FATALERROR_MESSAGE("Illegal mesh reference");
		}

		for (lod = 0; lod < 3; lod++) {
			if (model->m_modelIndices[lod] < 0) {
				break;
			}

			if (!(model->m_modelDistances[lod] < g_floatyBoatMaxFloat)) {
				maxDistances[lod] = g_fltMax0x100576e4;
			}
			else {
				maxDistances[lod] = model->m_modelDistances[lod] * model->m_modelDistances[lod];
			}

			if (model->m_materialTableIndices[lod] >= 0) {
				if (model->m_materialTableIndices[lod] >= static_cast<LegoS32>(m_materialTableCount)) {
					GOL_FATALERROR_MESSAGE("Illegal alt mat assign ref val");
				}
				runtime->m_materialTables[lod] = GetMaterialTable(model->m_materialTableIndices[lod]);
			}
			else {
				runtime->m_materialTables[lod] = NULL;
			}
		}

		runtime->SetPrimaryModel(GetModel(model->m_modelIndices[0]), maxDistances[0]);
		for (lod = 1; lod < 3; lod++) {
			if (model->m_modelIndices[lod] < 0) {
				break;
			}
			runtime->AddModel(GetModel(model->m_modelIndices[lod]), maxDistances[lod]);
		}

		runtime->SetPosition(model->m_position);
		runtime->SetDirectionUp(model->m_direction, model->m_up);
		runtime->m_radius = -1.0f;
		runtime->m_scale = model->m_scale;

		if (model->m_flags & WdbModel::e_flagTextureScroll) {
			runtime->SetTextureScrollSpeedU(model->m_textureScrollSpeedU);
			runtime->SetTextureScrollSpeedV(model->m_textureScrollSpeedV);
		}
		if (model->m_flags & WdbModel::e_flagBit1) {
			runtime->m_flags |= GolModelEntity::c_flagBit1;
		}
		if (model->m_flags & WdbModel::e_flagBit2) {
			runtime->m_flags |= GolModelEntity::c_flagBit2;
		}

		for (j = 0; j < model->m_animationBindingCount; j++) {
			Rect* assignment = &model->m_animationBindings[j];
			if (static_cast<LegoU32>(assignment->m_left) >= m_materialAnimationCount) {
				continue;
			}

			MabMaterialTrack* item = GetMaterialAnimation(assignment->m_left)->GetTracks();
			LegoU32 targetIndex = assignment->m_bottom;
			MaterialTable* target = runtime->m_materialTables[targetIndex];
			if (target == NULL) {
				target = runtime->m_models[targetIndex]->GetMaterialTable();
			}
			item[assignment->m_top].Assign(target, assignment->m_right, TRUE);
		}

		if (model->m_name[0] != '\0') {
			if (m_modelEntityNames.GetNameEntries() == NULL) {
				m_modelEntityNames.Allocate(m_modelEntityCount);
			}
			m_modelEntityNames.AddName(model->m_name, runtime);
		}
	}

	for (i = 0; i < m_animatedEntityCount; i++) {
		WdbModel* model = &m_animatedEntityRecords[i];
		GolAnimatedEntity* runtime = &m_animatedEntities[i];

		if (model->m_modelIndices[0] >= 0 && static_cast<LegoU32>(model->m_modelIndices[0]) >= m_modelCount) {
			GOL_FATALERROR_MESSAGE("Illegal mesh reference");
		}
		if (static_cast<LegoU32>(model->m_sceneNodeIndices[0]) >= m_sceneNodeCount) {
			GOL_FATALERROR_MESSAGE("Illegal skeleton reference");
		}

		for (lod = 0; lod < 3; lod++) {
			if (model->m_sceneNodeIndices[lod] < 0) {
				break;
			}

			if (!(model->m_modelDistances[lod] < g_floatyBoatMaxFloat)) {
				maxDistances[lod] = g_fltMax0x100576e4;
			}
			else {
				maxDistances[lod] = model->m_modelDistances[lod] * model->m_modelDistances[lod];
			}

			if (model->m_materialTableIndices[lod] >= 0) {
				if (model->m_materialTableIndices[lod] >= static_cast<LegoS32>(m_materialTableCount)) {
					GOL_FATALERROR_MESSAGE("Illegal alt mat assign ref val");
				}
				runtime->m_materialTables[lod] = GetMaterialTable(model->m_materialTableIndices[lod]);
			}
			else {
				runtime->m_materialTables[lod] = NULL;
			}
		}

		GolSceneNode* node = GetSceneNode(model->m_sceneNodeIndices[0]);
		CmbModelPart* part = GetModelPart(model->m_modelPartIndices[0]);
		CmbModelPart* partForPartName = part;

		if (model->m_modelIndices[0] < 0) {
			runtime->SetNode(node, part, maxDistances[0]);
			for (lod = 1; lod < 3; lod++) {
				if (model->m_sceneNodeIndices[lod] < 0) {
					break;
				}

				node = GetSceneNode(model->m_sceneNodeIndices[lod]);
				part = GetModelPart(model->m_modelPartIndices[lod]);
				partForPartName = part;
				runtime->AddNode(node, part, maxDistances[lod]);
			}
		}
		else {
			runtime->SetModel(GetModel(model->m_modelIndices[0]), node, part, maxDistances[0]);
			for (lod = 1; lod < 3; lod++) {
				if (model->m_modelIndices[lod] < 0) {
					break;
				}

				node = GetSceneNode(model->m_sceneNodeIndices[lod]);
				part = GetModelPart(model->m_modelPartIndices[lod]);
				partForPartName = part;
				runtime->AddModel(GetModel(model->m_modelIndices[lod]), node, part, maxDistances[lod]);
			}
		}

		runtime->SetPosition(model->m_position);
		runtime->SetDirectionUp(model->m_direction, model->m_up);
		runtime->m_radius = -1.0f;
		runtime->m_scale = model->m_scale;

		if (model->m_flags & WdbModel::e_flagTextureScroll) {
			runtime->SetTextureScrollSpeedU(model->m_textureScrollSpeedU);
			runtime->SetTextureScrollSpeedV(model->m_textureScrollSpeedV);
		}

		if (model->m_nodeName[0] != '\0') {
			model->m_nodeIndex = partForPartName->GetPartIndex(model->m_nodeName);
		}

		if (model->m_nodeIndex >= 0) {
			runtime->PlayPartDirect(model->m_nodeIndex);
			runtime->SetPartAnimationEnabled(TRUE);
		}
		else {
			runtime->SetPartAnimationEnabled(FALSE);
		}

		if (model->m_flags & WdbModel::e_flagBit1) {
			runtime->m_flags |= GolModelEntity::c_flagBit1;
		}
		if (model->m_flags & WdbModel::e_flagBit2) {
			runtime->m_flags |= GolModelEntity::c_flagBit2;
		}

		for (j = 0; j < model->m_animationBindingCount; j++) {
			Rect* assignment = &model->m_animationBindings[j];
			if (static_cast<LegoU32>(assignment->m_left) >= m_materialAnimationCount) {
				continue;
			}

			MabMaterialTrack* item = GetMaterialAnimation(assignment->m_left)->GetTracks();
			LegoU32 targetIndex = assignment->m_bottom;
			MaterialTable* target = runtime->m_materialTables[targetIndex];
			if (target == NULL) {
				target = runtime->m_models[targetIndex]->GetMaterialTable();
			}
			item[assignment->m_top].Assign(target, assignment->m_right, TRUE);
		}

		if (model->m_name[0] != '\0') {
			if (m_animatedEntityNames.GetNameEntries() == NULL) {
				m_animatedEntityNames.Allocate(m_animatedEntityCount);
			}
			m_animatedEntityNames.AddName(model->m_name, runtime);
		}
	}

	for (i = 0; i < m_collidableEntityCount; i++) {
		WdbModel* model = &m_collidableEntityRecords[i];
		GolCollidableEntity* runtime = &m_collidableEntities[i];

		if (static_cast<LegoU32>(model->m_modelIndices[0]) >= m_modelCount) {
			GOL_FATALERROR_MESSAGE("Illegal mesh reference");
		}
		if (static_cast<LegoU32>(model->m_sceneNodeIndices[0]) >= m_boundingShapeCount) {
			GOL_FATALERROR_MESSAGE("Illegal bsp tree reference");
		}

		for (lod = 0; lod < 3; lod++) {
			if (model->m_modelIndices[lod] < 0) {
				break;
			}

			if (!(model->m_modelDistances[lod] < g_floatyBoatMaxFloat)) {
				maxDistances[lod] = g_fltMax0x100576e4;
			}
			else {
				maxDistances[lod] = model->m_modelDistances[lod] * model->m_modelDistances[lod];
			}

			if (model->m_materialTableIndices[lod] >= 0) {
				if (model->m_materialTableIndices[lod] >= static_cast<LegoS32>(m_materialTableCount)) {
					GOL_FATALERROR_MESSAGE("Illegal alt mat assign ref val");
				}
				runtime->m_materialTables[lod] = GetMaterialTable(model->m_materialTableIndices[lod]);
			}
			else {
				runtime->m_materialTables[lod] = NULL;
			}
		}

		runtime->SetPrimaryModelAndShape(
			GetModel(model->m_modelIndices[0]),
			GetBoundingShape(model->m_sceneNodeIndices[0]),
			maxDistances[0]
		);
		for (lod = 1; lod < 3; lod++) {
			if (model->m_modelIndices[lod] < 0) {
				break;
			}
			runtime->AddModel(
				GetModel(model->m_modelIndices[lod]),
				GetBoundingShape(model->m_sceneNodeIndices[lod]),
				maxDistances[lod]
			);
		}

		runtime->SetPosition(model->m_position);
		runtime->SetDirectionUp(model->m_direction, model->m_up);

		if (model->m_flags & WdbModel::e_flagTextureScroll) {
			runtime->SetTextureScrollSpeedU(model->m_textureScrollSpeedU);
			runtime->SetTextureScrollSpeedV(model->m_textureScrollSpeedV);
		}
		if (model->m_flags & WdbModel::e_flagBit1) {
			runtime->m_flags |= GolModelEntity::c_flagBit1;
		}

		for (j = 0; j < model->m_animationBindingCount; j++) {
			Rect* assignment = &model->m_animationBindings[j];
			if (static_cast<LegoU32>(assignment->m_left) >= m_materialAnimationCount) {
				continue;
			}

			MabMaterialTrack* item = GetMaterialAnimation(assignment->m_left)->GetTracks();
			LegoU32 targetIndex = assignment->m_bottom;
			MaterialTable* target = runtime->m_materialTables[targetIndex];
			if (target == NULL) {
				target = runtime->m_models[targetIndex]->GetMaterialTable();
			}
			item[assignment->m_top].Assign(target, assignment->m_right, TRUE);
		}

		if (model->m_name[0] != '\0') {
			if (m_collidableEntityNames.GetNameEntries() == NULL) {
				m_collidableEntityNames.Allocate(m_collidableEntityCount);
			}
			m_collidableEntityNames.AddName(model->m_name, runtime);
		}
	}

	for (i = 0; i < m_boundingVolumeCount; i++) {
		LegoChar name[sizeof(GolName) + 1];
		::memcpy(name, m_boundingVolumeNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_boundingVolumes[i].Load(m_renderer, name, m_binary);
	}

	for (i = 0; i < m_boundedEntityCount; i++) {
		WdbModel* model = &m_boundedEntityRecords[i];
		GolBoundedEntity* runtime = &m_boundedEntities[i];

		if (static_cast<LegoU32>(model->m_sceneNodeIndices[0]) >= m_boundingVolumeCount) {
			GOL_FATALERROR_MESSAGE("Illegal bsp volume reference");
		}

		if (model->m_materialTableIndices[0] >= 0) {
			if (model->m_materialTableIndices[0] >= static_cast<LegoS32>(m_materialTableCount)) {
				GOL_FATALERROR_MESSAGE("Illegal alt mat assign ref val");
			}
			runtime->m_materialTableOverride = GetMaterialTable(model->m_materialTableIndices[0]);
		}
		else {
			runtime->m_materialTableOverride = NULL;
		}

		runtime->SetBoundingVolume(&m_boundingVolumes[model->m_sceneNodeIndices[0]]);
		runtime->SetPosition(model->m_position);
		runtime->SetDirectionUp(model->m_direction, model->m_up);

		if (model->m_name[0] != '\0') {
			if (m_boundedEntityNames.GetNameEntries() == NULL) {
				m_boundedEntityNames.Allocate(m_boundedEntityCount);
			}
			m_boundedEntityNames.AddName(model->m_name, runtime);
		}
	}

	for (i = 0; i < m_cameraCount; i++) {
		SetupCamera(i, GetCamera(i));
	}

	for (i = 0; i < m_ambientLightCount; i++) {
		m_ambientMaterial[i].SetColor(m_ambientLightRecords[i].m_color);
	}

	for (i = 0; i < m_lightCount; i++) {
		m_light[i].SetColor(m_lightRecords[i].m_color);
		m_light[i].SetDirection(m_lightRecords[i].m_direction);
	}
}

// FUNCTION: GOLDP 0x1002f210
void GolWorldDatabase::SetupCamera(LegoU32 p_cameraIndex, GolCameraBase* p_lens)
{
	WdbCamera* camera = &m_cameraRecords[p_cameraIndex];

	p_lens->m_nearClip = camera->GetNearClip();
	p_lens->m_flags |= 2;
	p_lens->m_farClip = camera->GetFarClip();
	p_lens->m_flags |= 2;
	p_lens->m_fov = camera->GetFov();
	p_lens->m_flags |= 2;

	p_lens->m_transform->SetPosition(&camera->m_position);
	p_lens->m_flags |= 1;
	p_lens->m_transform->VTable0x24(&camera->m_direction, &camera->m_up);
	p_lens->m_flags |= 1;

	if (camera->m_animatedEntityIndex >= 0) {
		GolAnimatedEntity* model = &m_animatedEntities[camera->m_animatedEntityIndex];
		p_lens->SetTrackedEntity(model, camera->m_trackedNodeIndex);

		if (camera->m_partName[0] != '\0') {
			camera->m_partIndex = model->GetModelPart()->GetPartIndex(camera->m_partName);
		}

		if (camera->m_partIndex >= 0) {
			model->PlayPartDirect(camera->m_partIndex);
			model->SetPartAnimationEnabled(TRUE);
		}
		else {
			model->SetPartAnimationEnabled(FALSE);
		}
	}

	if (camera->m_name[0] != '\0') {
		if (m_cameraNames.GetNameEntries() == NULL) {
			GolNameTable* nameTable = &m_cameraNames;
			nameTable->Allocate(m_cameraCount);
		}
		m_cameraNames.AddName(camera->m_name, p_lens);
	}
}

// FUNCTION: GOLDP 0x1002f350
void GolWorldDatabase::SetLoadTexturesImmediately(undefined4 p_immediate)
{
	::SetLoadTexturesImmediately(p_immediate);
}

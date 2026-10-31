#include "race/racesky.h"

#include "core/gol.h"
#include "gdbmodelindexarray.h"
#include "gdbvertexarray.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmodelbase.h"
#include "golmodelmaterialtable.h"
#include "render/gold3drenderdevice.h"
#include "render/golrenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(RaceSkyState, 0xc8)
DECOMP_SIZE_ASSERT(RaceSkyState::SkbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(RaceSkyState::Entry, 0x10)
DECOMP_SIZE_ASSERT(RaceSkyState::Entry::Keyframe, 0x10)
DECOMP_SIZE_ASSERT(RaceSkyState::ModelBuilder, 0x01)
DECOMP_SIZE_ASSERT(RaceSkyState::ModelBuilder::Params, 0x38)

// GLOBAL: LEGORACERS 0x004afd54
extern const LegoFloat g_raceSkyMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004afddc
extern const LegoFloat g_raceSkyDomeDepth = 40.0f;

extern const LegoFloat g_unk0x004afde0;
extern const LegoFloat g_twoPi;

// GLOBAL: LEGORACERS 0x004b4764
const LegoFloat g_raceSkyNegativeHalfPi = -1.5707964f;

// GLOBAL: LEGORACERS 0x004b4768
const LegoFloat g_raceSkyInversePi = 0.31830987f;

// GLOBAL: LEGORACERS 0x004b476c
const LegoFloat g_raceSkyInverseTwoPi = 0.15915494f;

// FUNCTION: LEGORACERS 0x0041c430
RaceSkyState::RaceSkyState()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041c4b0
RaceSkyState::~RaceSkyState()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0041c500
void RaceSkyState::Reset()
{
	m_entries = NULL;
	m_count = 0;
	m_stateIndex = 0;
	m_previousStateIndex = 0;
	m_transitionMs = 0;
	m_transitionElapsedMs = 0;
	m_domeModel = NULL;
	m_golExport = NULL;
	m_hideFlags = 0;
	m_skyWorld = NULL;
	m_heightOffset = 0.0f;
}

// FUNCTION: LEGORACERS 0x0041c550
void RaceSkyState::Load(
	GolD3DRenderDevice* p_renderer,
	GolExport* p_golExport,
	const LegoChar* p_skyName,
	const LegoChar* p_worldName,
	LegoBool32 p_binary
)
{
	if (m_golExport != NULL) {
		Clear();
	}

	m_golExport = p_golExport;

	GolName name;
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".skb");
	}
	else {
		parser = new SkbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_skyName);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(SkbTxtParser::e_states));
	parser->ReadLeftBracket();
	m_count = parser->ReadInteger();
	parser->ReadRightBracket();

	m_entries = new Entry[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	GolNameTable::Allocate(m_count);
	parser->ReadLeftCurly();

	LegoU32 entryIndex;
	for (entryIndex = 0; entryIndex < m_count; entryIndex++) {
		m_entries[entryIndex].m_elapsedMs = 0;
		m_entries[entryIndex].m_keyframeIndex = 0;
		m_entries[entryIndex].m_keyframes = NULL;
		m_entries[entryIndex].m_keyframeCount = 0;

		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(SkbTxtParser::e_state));
		parser->ReadLeftBracket();
		m_entries[entryIndex].m_keyframeCount = parser->ReadInteger();
		parser->ReadRightBracket();

		m_entries[entryIndex].m_keyframes = new Entry::Keyframe[m_entries[entryIndex].m_keyframeCount];
		if (m_entries[entryIndex].m_keyframes == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		::strncpy(name, parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		GolNameTable::AddName(name, &m_entries[entryIndex]);

		parser->ReadLeftCurly();
		LegoU32 keyframeIndex;
		for (keyframeIndex = 0; keyframeIndex < m_entries[entryIndex].m_keyframeCount; keyframeIndex++) {
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_durationMs = 1000;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_topColor.m_red = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_topColor.m_grn = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_topColor.m_blu = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_topColor.m_alp = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_middleColor.m_red = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_middleColor.m_grn = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_middleColor.m_blu = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_middleColor.m_alp = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_bottomColor.m_red = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_bottomColor.m_grn = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_bottomColor.m_blu = 0xff;
			m_entries[entryIndex].m_keyframes[keyframeIndex].m_bottomColor.m_alp = 0xff;

			parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(SkbTxtParser::e_state));
			parser->ReadLeftCurly();

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				switch (token) {
				case SkbTxtParser::e_duration:
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_durationMs = parser->ReadInteger();
					break;
				case SkbTxtParser::e_topColor:
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_topColor.m_red =
						static_cast<LegoU8>(parser->ReadInteger());
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_topColor.m_grn =
						static_cast<LegoU8>(parser->ReadInteger());
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_topColor.m_blu =
						static_cast<LegoU8>(parser->ReadInteger());
					break;
				case SkbTxtParser::e_middleColor:
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_middleColor.m_red =
						static_cast<LegoU8>(parser->ReadInteger());
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_middleColor.m_grn =
						static_cast<LegoU8>(parser->ReadInteger());
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_middleColor.m_blu =
						static_cast<LegoU8>(parser->ReadInteger());
					break;
				case SkbTxtParser::e_bottomColor:
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_bottomColor.m_red =
						static_cast<LegoU8>(parser->ReadInteger());
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_bottomColor.m_grn =
						static_cast<LegoU8>(parser->ReadInteger());
					m_entries[entryIndex].m_keyframes[keyframeIndex].m_bottomColor.m_blu =
						static_cast<LegoU8>(parser->ReadInteger());
					break;
				default:
					parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}

				token = parser->GetNextToken();
			}
		}

		parser->ReadRightCurly();
	}

	parser->ReadRightCurly();

	Entry* entry = NULL;
	GolFileParser::ParserTokenType token = parser->GetNextToken();
	if (token == SkbTxtParser::e_initialState) {
		::strncpy(name, parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		entry = static_cast<Entry*>(GolNameTable::GetName(name));
	}

	if (entry == NULL) {
		m_stateIndex = 0;
	}
	else {
		m_stateIndex = static_cast<LegoU32>(entry - m_entries);
	}

	token = parser->GetNextToken();
	if (token == SkbTxtParser::e_heightOffset) {
		m_heightOffset = parser->ReadFloat();
	}

	parser->Dispose();
	delete parser;

	m_previousStateIndex = 0;
	m_transitionMs = 0;
	m_transitionElapsedMs = 0;

	m_domeModel = m_golExport->CreateModel();

	{
		ModelBuilder::Params params;
		params.m_model = m_domeModel;
		params.m_renderer = p_renderer;
		params.m_segmentCount = 11;
		params.m_hemisphere = 1;
		params.m_hasTopCap = 0;
		params.m_hasBottomCap = 0;
		params.m_origin.m_x = 0.0f;
		params.m_origin.m_y = 0.0f;
		params.m_origin.m_z = 0.0f;
		params.m_radius = 100.0f;
		params.m_reverseWinding = 1;
		params.m_useTextureSeam = 0;
		params.m_vertexType = 1;
		params.m_absoluteIndexArray = NULL;
		m_modelBuilder.Build(&params);

		m_domeEntity.SetPrimaryModel(m_domeModel, g_raceSkyMaxFloat);
		m_domeEntity.EnableFlagBit1();

		GolVec3 center;
		center.m_x = 0.0f;
		center.m_y = 0.0f;
		center.m_z = 0.0f;

		GolVec3 direction;
		direction.m_x = 1.0f;
		direction.m_y = 0.0f;
		direction.m_z = 0.0f;

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;
		m_domeEntity.SetPosition(center);
		m_domeEntity.SetDirectionUp(direction, up);

		MaterialTable* materialTable = m_domeModel->GetMaterialTable();
		::strncpy(name, "skymat", sizeof(name));
		materialTable->SetEntry(0, p_renderer->FindMaterialByName(name));
	}

	m_skyWorld = m_golExport->CreateWorldDatabase();
	m_skyWorld->Load(p_renderer, p_worldName, p_binary, 1.0f);
}

// FUNCTION: LEGORACERS 0x0041cbe0
void RaceSkyState::Clear()
{
	if (m_skyWorld) {
		m_golExport->DestroyWorldDatabase(m_skyWorld);
		m_skyWorld = NULL;
	}

	if (m_domeModel) {
		m_golExport->DestroyModel(m_domeModel);
		m_domeModel = NULL;
	}

	m_golExport = NULL;
	m_domeEntity.ResetModelState();

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}

	if (m_entries) {
		LegoU32 i;

		for (i = 0; i < m_count; i++) {
			if (m_entries[i].m_keyframes) {
				delete[] m_entries[i].m_keyframes;
				m_entries[i].m_keyframes = NULL;
			}
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0041ccb0
void RaceSkyState::Update(LegoU32 p_elapsedMs)
{
	m_skyWorld->Update(p_elapsedMs);

	for (LegoU32 count = 0; count < m_count; count++) {
		m_entries[count].m_elapsedMs += p_elapsedMs;
		if (m_entries[count].m_elapsedMs >
			m_entries[count].m_keyframes[m_entries[count].m_keyframeIndex].m_durationMs) {
			m_entries[count].m_keyframeIndex++;
			if (m_entries[count].m_keyframeIndex == m_entries[count].m_keyframeCount) {
				m_entries[count].m_keyframeIndex = 0;
			}

			m_entries[count].m_elapsedMs = 0;
		}
	}

	if (m_transitionMs > 0) {
		m_transitionElapsedMs += p_elapsedMs;
		if (m_transitionElapsedMs > m_transitionMs) {
			m_transitionMs = 0;
			m_transitionElapsedMs = 0;
		}
	}

	ColorRGBA color0;
	ColorRGBA color1;
	ColorRGBA color2;
	EvaluateColors(&m_entries[m_stateIndex], &color0, &color1, &color2);

	if (m_transitionMs > 0) {
		ColorRGBA transitionColor0;
		ColorRGBA transitionColor1;
		ColorRGBA transitionColor2;
		EvaluateColors(&m_entries[m_previousStateIndex], &transitionColor0, &transitionColor1, &transitionColor2);

		LegoFloat elapsedMs = static_cast<LegoFloat>(static_cast<LegoS32>(m_transitionElapsedMs));
		LegoFloat transitionMs = static_cast<LegoFloat>(static_cast<LegoS32>(m_transitionMs));
		LegoFloat amount = elapsedMs;
		amount /= transitionMs;
		LerpColor(&transitionColor0, &color0, &color0, amount);
		LerpColor(&transitionColor1, &color1, &color1, amount);
		LerpColor(&transitionColor2, &color2, &color2, amount);
	}

	ApplyColors(&color0, &color1, &color2);
}

// FUNCTION: LEGORACERS 0x0041ce60
void RaceSkyState::EvaluateColors(
	Entry* p_entry,
	ColorRGBA* p_topColor,
	ColorRGBA* p_middleColor,
	ColorRGBA* p_bottomColor
)
{
	LegoU32 keyframeCount = p_entry->m_keyframeCount;

	if (keyframeCount == 1) {
		*p_topColor = p_entry->m_keyframes[0].m_topColor;
		*p_middleColor = p_entry->m_keyframes[0].m_middleColor;
		*p_bottomColor = p_entry->m_keyframes[0].m_bottomColor;
	}
	else {
		LegoU32 keyframeIndex = p_entry->m_keyframeIndex;
		LegoU32 nextIndex = (keyframeIndex + 1) % keyframeCount;
		LegoFloat elapsedMs = static_cast<LegoFloat>(static_cast<LegoS32>(p_entry->m_elapsedMs));
		LegoFloat keyframeMs =
			static_cast<LegoFloat>(static_cast<LegoS32>(p_entry->m_keyframes[p_entry->m_keyframeIndex].m_durationMs));
		LegoFloat amount = elapsedMs / keyframeMs;

		LerpColor(
			&p_entry->m_keyframes[p_entry->m_keyframeIndex].m_topColor,
			&p_entry->m_keyframes[nextIndex].m_topColor,
			p_topColor,
			amount
		);
		LerpColor(
			&p_entry->m_keyframes[p_entry->m_keyframeIndex].m_middleColor,
			&p_entry->m_keyframes[nextIndex].m_middleColor,
			p_middleColor,
			amount
		);
		LerpColor(
			&p_entry->m_keyframes[p_entry->m_keyframeIndex].m_bottomColor,
			&p_entry->m_keyframes[nextIndex].m_bottomColor,
			p_bottomColor,
			amount
		);
	}
}

// FUNCTION: LEGORACERS 0x0041cf20
void RaceSkyState::LerpColor(const ColorRGBA* p_from, const ColorRGBA* p_to, ColorRGBA* p_result, LegoFloat p_amount)
{
	LegoFloat inverseAmount = 1.0f - p_amount;

	p_result->m_red = static_cast<LegoU8>(p_from->m_red * inverseAmount + p_to->m_red * p_amount);
	p_result->m_grn = static_cast<LegoU8>(p_from->m_grn * inverseAmount + p_to->m_grn * p_amount);
	p_result->m_blu = static_cast<LegoU8>(p_from->m_blu * inverseAmount + p_to->m_blu * p_amount);
}

// FUNCTION: LEGORACERS 0x0041cfc0
void RaceSkyState::ApplyColors(
	const ColorRGBA* p_topColor,
	const ColorRGBA* p_middleColor,
	const ColorRGBA* p_bottomColor
)
{
	GdbVertexArray* vertices;
	const ColorRGBA* color = NULL;

	m_domeModel->GetVertexArray(&vertices);

	LegoU32 i;
	for (i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			color = p_bottomColor;
			break;
		case 1:
			color = p_middleColor;
			break;
		case 2:
			color = p_topColor;
			break;
		}

		for (LegoU32 j = 0; j < 11; j++) {
			vertices->SetColor(i * 11 + j, *color);
		}
	}

	m_domeModel->AddFlagsWithBounds(1, FALSE);
}

// FUNCTION: LEGORACERS 0x0041d040
void RaceSkyState::SetPosition(GolVec3* p_position)
{
	p_position->m_z -= g_unk0x004afde0 - m_heightOffset;
	m_domeEntity.SetPosition(*p_position);
	p_position->m_z += g_raceSkyDomeDepth - m_heightOffset;

	LegoU32 i;
	for (i = 0; i < m_skyWorld->GetModelEntityCount(); i++) {
		m_skyWorld->GetModelEntities()[i].SetPosition(*p_position);
	}

	for (i = 0; i < m_skyWorld->GetAnimatedEntityCount(); i++) {
		GolWorldEntity* entity = &m_skyWorld->GetAnimatedEntities()[i];
		entity->SetPosition(*p_position);
	}
}

// FUNCTION: LEGORACERS 0x0041d0f0
void RaceSkyState::Draw(GolD3DRenderDevice* p_renderer)
{
	LegoU8 flags = m_hideFlags;
	flags = ~flags;
	if (flags & c_hideDome) {
		p_renderer->DisableZBuffer(TRUE);
		p_renderer->DrawModelEntity(&m_domeEntity);

		flags = m_hideFlags;
		flags = ~flags;
		if (flags & c_hideSkyWorld) {
			m_skyWorld->DrawWorld();
		}

		p_renderer->EnableZBuffer();
	}
}

// FUNCTION: LEGORACERS 0x0041d150
void RaceSkyState::StartTransition(const LegoChar* p_name, LegoU32 p_durationMs)
{
	Entry* entry = static_cast<Entry*>(GolNameTable::GetName(p_name));
	if (entry) {
		m_previousStateIndex = m_stateIndex;
		LegoU32 index = static_cast<LegoU32>(entry - m_entries);
		m_stateIndex = index;
		if (index != m_previousStateIndex) {
			m_transitionElapsedMs = 0;
			m_transitionMs = p_durationMs;
		}
	}
}

// FUNCTION: LEGORACERS 0x004907d0
void RaceSkyState::ModelBuilder::Build(Params* p_params)
{
	if (p_params->m_useTextureSeam) {
		BuildSeamedSphere(p_params);
	}
	else {
		BuildSphere(p_params);
	}
}

// FUNCTION: LEGORACERS 0x004907f0
void RaceSkyState::ModelBuilder::BuildSphere(Params* p_params)
{
	LegoU32 vertexIndex = 0;
	LegoU32 triangleIndex = 0;
	LegoFloat angleStep = g_twoPi / static_cast<LegoFloat>(static_cast<LegoS32>(p_params->m_segmentCount));
	LegoU32 ringCount;
	if (p_params->m_hemisphere) {
		ringCount = 1 - static_cast<LegoS32>(g_raceSkyNegativeHalfPi / angleStep);
	}
	else {
		ringCount = (p_params->m_segmentCount >> 1) - 1;
	}

	LegoU32 vertexCount = static_cast<LegoU32>(ringCount) * p_params->m_segmentCount + 2;
	LegoU32 triangleBudget = static_cast<LegoU32>(ringCount) * p_params->m_segmentCount * 2;
	if (!p_params->m_hasTopCap) {
		vertexCount--;
		triangleBudget -= p_params->m_segmentCount;
	}
	if (!p_params->m_hasBottomCap) {
		vertexCount--;
		triangleBudget -= p_params->m_segmentCount;
	}

	LegoU32 groupCount = static_cast<LegoU32>(ringCount) * 2 + 6;
	p_params->m_model
		->Allocate(p_params->m_renderer, p_params->m_vertexType, vertexCount, triangleBudget, groupCount, 1);
	LegoU32 second;
	LegoU32 third;
	if (p_params->m_reverseWinding) {
		second = 2;
		third = 1;
	}
	else {
		second = 1;
		third = 2;
	}

	ColorRGBA color;
	color.m_red = 0xff;
	color.m_grn = 0xff;
	color.m_blu = 0xff;
	color.m_alp = 0xff;
	GolVec2 textureCoordinate;
	textureCoordinate.m_x = 0.0f;
	textureCoordinate.m_y = 0.0f;
	GolVec3 position;
	GolVec3 normal;
	GdbVertexArray* vertices;
	p_params->m_model->GetVertexArray(&vertices);

	if (p_params->m_hasTopCap) {
		position.m_x = p_params->m_origin.m_x;
		position.m_y = p_params->m_origin.m_y;
		position.m_z = p_params->m_radius + p_params->m_origin.m_z;
		vertices->SetPosition(vertexIndex, position);
		normal.m_x = 0.0f;
		normal.m_y = 0.0f;
		normal.m_z = 1.0f;
		if (p_params->m_vertexType == Params::c_vertexColored) {
			vertices->SetColor(vertexIndex, color);
		}
		else if (p_params->m_vertexType == Params::c_vertexLit) {
			vertices->SetNormal(vertexIndex, normal);
		}
		vertices->SetTextureCoordinate(vertexIndex, textureCoordinate);
		vertexIndex = 1;
	}

	LegoFloat ringAngle = angleStep;
	LegoU32 ring;
	LegoU32 segment;
	for (ring = 0; ring < ringCount; ring++) {
		if (p_params->m_hemisphere && ring == ringCount - 1) {
			ringAngle = 1.5707964f;
		}
		position.m_z = static_cast<LegoFloat>(::cos(ringAngle)) * p_params->m_radius + p_params->m_origin.m_z;
		LegoFloat radius = static_cast<LegoFloat>(::sin(ringAngle)) * p_params->m_radius;
		LegoFloat segmentAngle = 0.0f;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			position.m_x = static_cast<LegoFloat>(::cos(segmentAngle)) * radius + p_params->m_origin.m_x;
			position.m_y = static_cast<LegoFloat>(::sin(segmentAngle)) * radius + p_params->m_origin.m_y;
			segmentAngle += angleStep;
			vertices->SetPosition(vertexIndex, position);
			normal.m_x = position.m_x - p_params->m_origin.m_x;
			normal.m_y = position.m_y - p_params->m_origin.m_y;
			normal.m_z = position.m_z - p_params->m_origin.m_z;
			GolMath::NormalizeVector3(normal, &normal);
			if (p_params->m_vertexType == Params::c_vertexColored) {
				vertices->SetColor(vertexIndex, color);
			}
			else if (p_params->m_vertexType == Params::c_vertexLit) {
				vertices->SetNormal(vertexIndex, normal);
			}
			vertices->SetTextureCoordinate(vertexIndex, textureCoordinate);
			vertexIndex++;
		}
		ringAngle += angleStep;
	}

	if (p_params->m_hasBottomCap) {
		position.m_x = p_params->m_origin.m_x;
		position.m_y = p_params->m_origin.m_y;
		if (p_params->m_hemisphere) {
			position.m_z = p_params->m_origin.m_z;
		}
		else {
			position.m_z = p_params->m_origin.m_z - p_params->m_radius;
		}
		vertices->SetPosition(vertexIndex, position);
		normal.m_x = 0.0f;
		normal.m_y = 0.0f;
		normal.m_z = -1.0f;
		if (p_params->m_vertexType == Params::c_vertexColored) {
			vertices->SetColor(vertexIndex, color);
		}
		else if (p_params->m_vertexType == Params::c_vertexLit) {
			vertices->SetNormal(vertexIndex, normal);
		}
		vertices->SetTextureCoordinate(vertexIndex, textureCoordinate);
		vertexIndex++;
	}

	p_params->m_model->AddFlagsWithBounds(1, FALSE);
	LegoU32 groupIndex = 0;
	p_params->m_model->GetMutableGroups()[groupIndex++] = 0x80000000;
	if (p_params->m_absoluteIndexArray != NULL) {
		p_params->m_absoluteIndexArray->Allocate(triangleBudget);
	}
	GdbModelIndexArrayBase* indexArrayBase;
	p_params->m_model->GetIndexArrayInto(&indexArrayBase);
	GdbModelIndexArray* indices = static_cast<GdbModelIndexArray*>(indexArrayBase);
	LegoU8 triangle[3];
	LegoU32 scratchStart = 0;

	if (p_params->m_hasTopCap) {
		scratchStart = p_params->m_segmentCount + 1;
		p_params->m_model->GetMutableGroups()[groupIndex++] = (p_params->m_segmentCount & 0x3f) << 16;
		p_params->m_model->GetMutableGroups()[groupIndex++] = ((p_params->m_segmentCount & 0x7f) << 16) | 0x20000000;
		for (segment = 1; segment <= p_params->m_segmentCount; segment++) {
			triangle[0] = 0;
			triangle[second] = static_cast<LegoU8>(segment);
			triangle[third] = static_cast<LegoU8>(segment == p_params->m_segmentCount ? 1 : segment + 1);
			if (p_params->m_absoluteIndexArray != NULL) {
				p_params->m_absoluteIndexArray
					->SetTriangleIndices(triangleIndex, triangle[0], triangle[1], triangle[2]);
			}
			indices->SetTriangleIndices(triangleIndex++, triangle[0], triangle[1], triangle[2]);
		}
	}

	if (p_params->m_hasBottomCap) {
		if (scratchStart + p_params->m_segmentCount + 1 > 64) {
			scratchStart = 0;
		}
		LegoU32 first = (ringCount - 1) * p_params->m_segmentCount;
		if (p_params->m_hasTopCap) {
			first++;
		}
		p_params->m_model->GetMutableGroups()[groupIndex++] =
			((scratchStart & 0x3f) << 22) | ((p_params->m_segmentCount & 0x3f) << 16) | (first & 0xffff);
		p_params->m_model->GetMutableGroups()[groupIndex++] =
			((p_params->m_segmentCount & 0x7f) << 16) | 0x20000000 | (triangleIndex & 0xffff);
		LegoU32 indexOffset = scratchStart - first;
		for (segment = 1; segment <= p_params->m_segmentCount; segment++) {
			triangle[0] = static_cast<LegoU8>(vertexCount - 1);
			triangle[third] = static_cast<LegoU8>(first + segment - 1);
			triangle[second] = static_cast<LegoU8>(segment == p_params->m_segmentCount ? first : triangle[third] + 1);
			if (p_params->m_absoluteIndexArray != NULL) {
				p_params->m_absoluteIndexArray
					->SetTriangleIndices(triangleIndex, triangle[0], triangle[1], triangle[2]);
			}
			triangle[0] += static_cast<LegoU8>(indexOffset);
			triangle[second] += static_cast<LegoU8>(indexOffset);
			triangle[third] += static_cast<LegoU8>(indexOffset);
			indices->SetTriangleIndices(triangleIndex++, triangle[0], triangle[1], triangle[2]);
		}
		scratchStart += p_params->m_segmentCount + 1;
	}

	for (ring = 1; ring < ringCount; ring++) {
		if (scratchStart + p_params->m_segmentCount * 2 > 64) {
			scratchStart = 0;
		}
		LegoU32 first = (ring - 1) * p_params->m_segmentCount;
		if (p_params->m_hasTopCap) {
			first++;
		}
		p_params->m_model->GetMutableGroups()[groupIndex++] =
			((scratchStart & 0x3f) << 22) | (((p_params->m_segmentCount * 2 - 1) & 0x3f) << 16) | (first & 0xffff);
		p_params->m_model->GetMutableGroups()[groupIndex++] =
			(((p_params->m_segmentCount * 2) & 0x7f) << 16) | 0x20000000 | (triangleIndex & 0xffff);
		LegoU32 indexOffset = scratchStart - first;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			triangle[0] = static_cast<LegoU8>(first + segment);
			triangle[second] = static_cast<LegoU8>(triangle[0] + p_params->m_segmentCount);
			triangle[third] = static_cast<LegoU8>(
				segment == p_params->m_segmentCount - 1 ? first + p_params->m_segmentCount : triangle[second] + 1
			);
			if (p_params->m_absoluteIndexArray != NULL) {
				p_params->m_absoluteIndexArray
					->SetTriangleIndices(triangleIndex, triangle[0], triangle[1], triangle[2]);
			}
			triangle[0] += static_cast<LegoU8>(indexOffset);
			triangle[second] += static_cast<LegoU8>(indexOffset);
			triangle[third] += static_cast<LegoU8>(indexOffset);
			indices->SetTriangleIndices(triangleIndex++, triangle[0], triangle[1], triangle[2]);

			triangle[0] = static_cast<LegoU8>(first + segment);
			triangle[second] = static_cast<LegoU8>(
				segment == p_params->m_segmentCount - 1 ? first + p_params->m_segmentCount
														: triangle[0] + p_params->m_segmentCount + 1
			);
			triangle[third] = static_cast<LegoU8>(segment == p_params->m_segmentCount - 1 ? first : triangle[0] + 1);
			if (p_params->m_absoluteIndexArray != NULL) {
				p_params->m_absoluteIndexArray
					->SetTriangleIndices(triangleIndex, triangle[0], triangle[1], triangle[2]);
			}
			triangle[0] += static_cast<LegoU8>(indexOffset);
			triangle[second] += static_cast<LegoU8>(indexOffset);
			triangle[third] += static_cast<LegoU8>(indexOffset);
			indices->SetTriangleIndices(triangleIndex++, triangle[0], triangle[1], triangle[2]);
		}
	}

	p_params->m_model->GetMutableGroups()[groupIndex] = 0xc0000000;
	p_params->m_model->AddFlags(1);
}

// FUNCTION: LEGORACERS 0x004910e0
LegoU32 RaceSkyState::ModelBuilder::BuildSeamedSphere(Params* p_params)
{
	LegoU32 triangleIndex = 0;
	LegoFloat angleStep = g_twoPi / static_cast<LegoFloat>(static_cast<LegoS32>(p_params->m_segmentCount));
	LegoU32 ringCount;
	if (p_params->m_hemisphere) {
		ringCount = 1 - static_cast<LegoS32>(g_raceSkyNegativeHalfPi / angleStep);
	}
	else {
		ringCount = (p_params->m_segmentCount >> 1) - 1;
	}

	LegoU32 vertexCount =
		static_cast<LegoU32>(ringCount + 2) * p_params->m_segmentCount + static_cast<LegoU32>(ringCount);
	LegoU32 triangleCount = static_cast<LegoU32>(ringCount) * p_params->m_segmentCount * 2;
	if (!p_params->m_hasTopCap) {
		vertexCount -= p_params->m_segmentCount;
		triangleCount -= p_params->m_segmentCount;
	}
	if (!p_params->m_hasBottomCap) {
		vertexCount -= p_params->m_segmentCount;
		triangleCount -= p_params->m_segmentCount;
	}

	LegoU32 groupCount = static_cast<LegoU32>(ringCount) * 2 + 6;
	p_params->m_model
		->Allocate(p_params->m_renderer, p_params->m_vertexType, vertexCount, triangleCount, groupCount, 1);

	LegoU32 second;
	LegoU32 third;
	if (p_params->m_reverseWinding) {
		second = 2;
		third = 1;
	}
	else {
		second = 1;
		third = 2;
	}
	LegoFloat textureHalfStep = 1.0f / (static_cast<LegoFloat>(static_cast<LegoS32>(p_params->m_segmentCount)) * 2.0f);
	ColorRGBA color;
	color.m_red = 0xff;
	color.m_grn = 0xff;
	color.m_blu = 0xff;
	color.m_alp = 0xff;
	GolVec2 textureCoordinate;
	GolVec3 position;
	GolVec3 normal;
	GdbVertexArray* vertices;
	p_params->m_model->GetVertexArray(&vertices);
	LegoU32 vertexIndex = 0;
	LegoU32 segment;
	LegoFloat segmentAngle;
	if (p_params->m_hasTopCap) {
		position.m_x = p_params->m_origin.m_x;
		position.m_y = p_params->m_origin.m_y;
		position.m_z = p_params->m_radius + p_params->m_origin.m_z;
		normal.m_x = 0.0f;
		normal.m_y = 0.0f;
		normal.m_z = 1.0f;
		segmentAngle = 0.0f;
		for (; vertexIndex < p_params->m_segmentCount; vertexIndex++) {
			vertices->SetPosition(vertexIndex, position);
			if (p_params->m_vertexType == Params::c_vertexColored) {
				vertices->SetColor(vertexIndex, color);
			}
			else if (p_params->m_vertexType == Params::c_vertexLit) {
				vertices->SetNormal(vertexIndex, normal);
			}
			textureCoordinate.m_x = segmentAngle * g_raceSkyInverseTwoPi + textureHalfStep;
			textureCoordinate.m_y = 0.0f;
			vertices->SetTextureCoordinate(vertexIndex, textureCoordinate);
			segmentAngle += angleStep;
		}
	}

	LegoFloat ringAngle = angleStep;
	LegoU32 ring;
	for (ring = 0; ring < ringCount; ring++) {
		if (p_params->m_hemisphere && ring == ringCount - 1) {
			ringAngle = 1.5707964f;
		}
		position.m_z = static_cast<LegoFloat>(::cos(ringAngle)) * p_params->m_radius + p_params->m_origin.m_z;
		LegoFloat radius = static_cast<LegoFloat>(::sin(ringAngle)) * p_params->m_radius;
		segmentAngle = 0.0f;
		for (segment = 0; segment < p_params->m_segmentCount + 1; segment++) {
			if (segment < p_params->m_segmentCount) {
				position.m_x = static_cast<LegoFloat>(::cos(segmentAngle)) * radius + p_params->m_origin.m_x;
				position.m_y = static_cast<LegoFloat>(::sin(segmentAngle)) * radius + p_params->m_origin.m_y;
				segmentAngle += angleStep;
				vertices->SetPosition(vertexIndex, position);
				normal.m_x = position.m_x - p_params->m_origin.m_x;
				normal.m_y = position.m_y - p_params->m_origin.m_y;
				normal.m_z = position.m_z - p_params->m_origin.m_z;
				GolMath::NormalizeVector3(normal, &normal);
				if (p_params->m_vertexType == Params::c_vertexColored) {
					vertices->SetColor(vertexIndex, color);
				}
				else if (p_params->m_vertexType == Params::c_vertexLit) {
					vertices->SetNormal(vertexIndex, normal);
				}
				textureCoordinate.m_x = (segmentAngle - angleStep) * g_raceSkyInverseTwoPi;
				textureCoordinate.m_y = ringAngle * g_raceSkyInversePi;
				vertices->SetTextureCoordinate(vertexIndex, textureCoordinate);
				vertexIndex++;
			}
			else {
				vertices->GetPosition(vertexIndex - p_params->m_segmentCount, &position);
				vertices->GetColor(vertexIndex - p_params->m_segmentCount, &color);
				vertices->GetNormal(vertexIndex - p_params->m_segmentCount, &normal);
				vertices->GetTextureCoordinate(vertexIndex - p_params->m_segmentCount, &textureCoordinate);
				textureCoordinate.m_x = 1.0f;
				vertices->SetPosition(vertexIndex, position);
				if (p_params->m_vertexType == Params::c_vertexColored) {
					vertices->SetColor(vertexIndex, color);
				}
				else {
					vertices->SetNormal(vertexIndex, normal);
				}
				vertices->SetTextureCoordinate(vertexIndex, textureCoordinate);
				vertexIndex++;
			}
		}
		ringAngle += angleStep;
	}

	if (p_params->m_hasBottomCap) {
		position.m_x = p_params->m_origin.m_x;
		position.m_y = p_params->m_origin.m_y;
		if (p_params->m_hemisphere) {
			position.m_z = p_params->m_origin.m_z;
		}
		else {
			position.m_z = p_params->m_origin.m_z - p_params->m_radius;
		}
		normal.m_x = 0.0f;
		normal.m_y = 0.0f;
		normal.m_z = -1.0f;
		segmentAngle = 0.0f;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			vertices->SetPosition(vertexIndex, position);
			if (p_params->m_vertexType == Params::c_vertexColored) {
				vertices->SetColor(vertexIndex, color);
			}
			else if (p_params->m_vertexType == Params::c_vertexLit) {
				vertices->SetNormal(vertexIndex, normal);
			}
			textureCoordinate.m_x = segmentAngle * g_raceSkyInverseTwoPi + textureHalfStep;
			textureCoordinate.m_y = 1.0f;
			vertices->SetTextureCoordinate(vertexIndex, textureCoordinate);
			vertexIndex++;
			segmentAngle += angleStep;
		}
	}

	p_params->m_model->AddFlagsWithBounds(1, FALSE);
	LegoU32 groupIndex = 0;
	p_params->m_model->GetMutableGroups()[groupIndex++] = 0x80000000;
	if (p_params->m_absoluteIndexArray != NULL) {
		p_params->m_absoluteIndexArray->Allocate(triangleCount);
	}
	GdbModelIndexArrayBase* indexArrayBase;
	p_params->m_model->GetIndexArrayInto(&indexArrayBase);
	GdbModelIndexArray* indices = static_cast<GdbModelIndexArray*>(indexArrayBase);
	LegoU8 triangle[3];
	LegoU32 scratchStart = 0;
	if (p_params->m_hasTopCap) {
		scratchStart = p_params->m_segmentCount * 2 + 1;
		p_params->m_model->GetMutableGroups()[groupIndex++] = ((p_params->m_segmentCount * 2) & 0x3f) << 16;
		p_params->m_model->GetMutableGroups()[groupIndex++] = ((p_params->m_segmentCount & 0x7f) << 16) | 0x20000000;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			triangle[0] = static_cast<LegoU8>(segment);
			triangle[second] = static_cast<LegoU8>(triangle[0] + p_params->m_segmentCount);
			triangle[third] = static_cast<LegoU8>(triangle[second] + 1);
			if (p_params->m_absoluteIndexArray != NULL) {
				p_params->m_absoluteIndexArray
					->SetTriangleIndices(triangleIndex, triangle[0], triangle[1], triangle[2]);
			}
			indices->SetTriangleIndices(triangleIndex++, triangle[0], triangle[1], triangle[2]);
		}
	}
	if (p_params->m_hasBottomCap) {
		if (scratchStart + p_params->m_segmentCount * 2 + 1 > 64) {
			scratchStart = 0;
		}
		LegoU32 first = (p_params->m_segmentCount + 1) * (ringCount - 1);
		if (p_params->m_hasTopCap) {
			first += p_params->m_segmentCount;
		}
		p_params->m_model->GetMutableGroups()[groupIndex++] =
			((scratchStart & 0x3f) << 22) | (((p_params->m_segmentCount * 2) & 0x3f) << 16) | (first & 0xffff);
		p_params->m_model->GetMutableGroups()[groupIndex++] =
			((p_params->m_segmentCount & 0x7f) << 16) | 0x20000000 | (triangleIndex & 0xffff);
		LegoU32 indexOffset = scratchStart - first;
		for (segment = 1; segment <= p_params->m_segmentCount; segment++) {
			triangle[0] = static_cast<LegoU8>(segment + first + p_params->m_segmentCount);
			triangle[third] = static_cast<LegoU8>(segment + first - 1);
			triangle[second] = static_cast<LegoU8>(triangle[third] + 1);
			if (p_params->m_absoluteIndexArray != NULL) {
				p_params->m_absoluteIndexArray
					->SetTriangleIndices(triangleIndex, triangle[0], triangle[1], triangle[2]);
			}
			triangle[0] += static_cast<LegoU8>(indexOffset);
			triangle[second] += static_cast<LegoU8>(indexOffset);
			triangle[third] += static_cast<LegoU8>(indexOffset);
			indices->SetTriangleIndices(triangleIndex++, triangle[0], triangle[1], triangle[2]);
		}
		scratchStart += p_params->m_segmentCount * 2 + 1;
	}
	for (ring = 1; ring < ringCount; ring++) {
		if (scratchStart + (p_params->m_segmentCount + 1) * 2 > 64) {
			scratchStart = 0;
		}
		LegoU32 first = (ring - 1) * (p_params->m_segmentCount + 1);
		if (p_params->m_hasTopCap) {
			first += p_params->m_segmentCount;
		}
		p_params->m_model->GetMutableGroups()[groupIndex++] =
			((scratchStart & 0x3f) << 22) | (((p_params->m_segmentCount * 2 + 1) & 0x3f) << 16) | (first & 0xffff);
		p_params->m_model->GetMutableGroups()[groupIndex++] =
			(((p_params->m_segmentCount * 2) & 0x7f) << 16) | 0x20000000 | (triangleIndex & 0xffff);
		LegoU32 indexOffset = scratchStart - first;
		for (segment = 0; segment < p_params->m_segmentCount; segment++) {
			triangle[0] = static_cast<LegoU8>(first + segment);
			triangle[second] = static_cast<LegoU8>(triangle[0] + p_params->m_segmentCount + 1);
			triangle[third] = static_cast<LegoU8>(triangle[second] + 1);
			if (p_params->m_absoluteIndexArray != NULL) {
				p_params->m_absoluteIndexArray
					->SetTriangleIndices(triangleIndex, triangle[0], triangle[1], triangle[2]);
			}
			triangle[0] += static_cast<LegoU8>(indexOffset);
			triangle[second] += static_cast<LegoU8>(indexOffset);
			triangle[third] += static_cast<LegoU8>(indexOffset);
			indices->SetTriangleIndices(triangleIndex++, triangle[0], triangle[1], triangle[2]);
			triangle[0] = static_cast<LegoU8>(first + segment);
			triangle[second] = static_cast<LegoU8>(triangle[0] + p_params->m_segmentCount + 2);
			triangle[third] = static_cast<LegoU8>(triangle[0] + 1);
			if (p_params->m_absoluteIndexArray != NULL) {
				p_params->m_absoluteIndexArray
					->SetTriangleIndices(triangleIndex, triangle[0], triangle[1], triangle[2]);
			}
			triangle[0] += static_cast<LegoU8>(indexOffset);
			triangle[second] += static_cast<LegoU8>(indexOffset);
			triangle[third] += static_cast<LegoU8>(indexOffset);
			indices->SetTriangleIndices(triangleIndex++, triangle[0], triangle[1], triangle[2]);
		}
	}
	p_params->m_model->GetMutableGroups()[groupIndex] = 0xc0000000;
	p_params->m_model->AddFlags(1);

	return vertexCount;
}

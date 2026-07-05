#include "race/powerups/beammesh.h"

#include "camera/golcamera.h"
#include "camera/goltransform.h"
#include "core/gol.h"
#include "decomp.h"
#include "gdbvertexarray.h"
#include "golmaterial.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "material/materialtable.h"
#include "render/gold3drenderdevice.h"

#include <math.h>
#include <string.h>

DECOMP_SIZE_ASSERT(BeamMesh, 0x170)
DECOMP_SIZE_ASSERT(BeamEntity, 0x98)

// GLOBAL: LEGORACERS 0x004b47a4
extern const LegoFloat g_beamMinStepDistanceSquared = 0.02f;

extern LegoFloat g_minSoundPan;

// FUNCTION: LEGORACERS 0x00493ae0
BeamMesh::BeamMesh()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00493b30
BeamMesh::~BeamMesh()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00493b80
void BeamMesh::Reset()
{
	m_golExport = NULL;
	m_model = NULL;
	m_vertices = 0;
	m_indices = 0;
	m_sceneNode = NULL;
	m_material = 0;
	m_windowBaseVertex = 0;
	m_ringVertexIndex = 0;
	m_previousRingVertexIndex = 0;
	m_vertexCursor = 0;
	m_runStartVertex = 0;
	m_runStartIndex = 0;
	m_indexCursor = 0;
	m_groupCursor = 0;
	m_sectionIndex = 0;
	m_textureColumn = 0;
	m_sectionCount = 0;
	m_segmentCount = 0;
	m_ringQuadCount = 0;
	m_ringVertexCount = 0;
	::memset(m_ringVertices, 0, sizeof(m_ringVertices));
	::memset(m_ringTextureXs, 0, sizeof(m_ringTextureXs));
	m_baseColor.m_alp = 0xff;
	m_secondaryColor.m_alp = 0xff;
	m_tertiaryColor.m_alp = 0xff;
	m_textureColumnCount = 0;
	m_flags = 0;
	m_segmentOffsets = NULL;
	m_startPosition.Clear();
	m_baseColor.m_red = 0;
	m_baseColor.m_grn = 0;
	m_baseColor.m_blu = 0;
	m_secondaryColor.m_red = 0;
	m_secondaryColor.m_grn = 0;
	m_secondaryColor.m_blu = 0;
	m_tertiaryColor.m_red = 0;
	m_tertiaryColor.m_grn = 0;
	m_tertiaryColor.m_blu = 0;
	m_vertexCapacity = 0;
}

// FUNCTION: LEGORACERS 0x00493c90
void BeamMesh::Initialize(const SetupParams* p_params)
{
	if (m_model != NULL) {
		Destroy();
	}

	const SetupParams* params = p_params;

	m_golExport = params->m_golExport;
	m_material = params->m_material;
	m_sectionCount = params->m_sectionCount;
	m_segmentCount = params->m_segmentCount;
	m_ringQuadCount = params->m_ringQuadCount;
	m_ringVertexCount = m_ringQuadCount + 1;
	m_segmentStep = 1.0f / (LegoS32) m_segmentCount;

	LegoU32 i;
	for (i = 0; i < m_ringVertexCount; i++) {
		m_ringVertices[i] = params->m_ringVertices[i];
		m_ringTextureXs[i] = params->m_ringTextureXs[i];
	}

	LegoU32 modelIndexCount = m_ringQuadCount * m_sectionCount * m_segmentCount;
	LegoU32 doubledIndexCount = 2 * modelIndexCount;
	LegoU32 segmentCount = m_segmentCount;
	m_textureColumnCount = params->m_textureColumnCount;

	LegoU32 generatedPointCount;
	if (m_material->GetFlags() & GolMaterial::c_flagTextured) {
		generatedPointCount = 0;
		if (m_textureColumnCount <= segmentCount) {
			generatedPointCount = segmentCount - m_textureColumnCount;
		}
		generatedPointCount += segmentCount + 1;
	}
	else {
		generatedPointCount = segmentCount + 1;
	}

	m_vertexCapacity = generatedPointCount * m_sectionCount * m_ringVertexCount;
	if (segmentCount >= m_textureColumnCount) {
		segmentCount = 2 * segmentCount - m_textureColumnCount + 1;
	}

	LegoU32 stride = segmentCount * m_ringVertexCount;
	LegoU32 vertexCount = m_sectionCount * (2 * (0x40 / stride) + 5) + 2;
	m_model = m_golExport->CreateModel();
	m_model->Allocate(params->m_renderer, 1, m_vertexCapacity, doubledIndexCount, vertexCount, 1);

	m_sceneNode = m_golExport->CreateSceneNode();
	m_sceneNode->Allocate(m_sectionCount);
	m_entity.Initialize(m_model, m_sceneNode, params->m_faceCamera, params->m_modelDistance);
	m_model->GetMaterialTable()->SetEntry(0, params->m_material);
}

// FUNCTION: LEGORACERS 0x00493e60
void BeamMesh::Destroy()
{
	m_entity.ResetModelState();

	if (m_golExport != NULL) {
		if (m_sceneNode != NULL) {
			m_golExport->DestroySceneNode(m_sceneNode);
		}

		if (m_model != NULL) {
			m_golExport->DestroyModel(m_model);
		}
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00493ea0
void BeamMesh::Begin(const GolVec3* p_position, const GolVec3* p_direction)
{
	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	m_model->GetVertexArray(&m_vertices);

	GdbModelIndexArrayBase* indexArray;
	m_model->GetIndexArrayInto(&indexArray);
	m_indices = static_cast<GdbModelIndexArray*>(indexArray)->GetMutableIndices();

	m_windowBaseVertex = 0;
	m_ringVertexIndex = -static_cast<LegoS32>(m_ringVertexCount);
	m_previousRingVertexIndex = 0;
	m_vertexCursor = 0;
	m_runStartVertex = 0;
	m_indexCursor = 0;
	m_runStartIndex = 0;
	m_flags &= ~c_flagVisible;
	m_groupCursor = 1;

	m_model->GetMutableGroups()[0] = c_groupBegin;
	m_startPosition = *p_position;
	m_model->SetDirty(TRUE);
	m_lastPosition = *p_position;
	m_sectionIndex = 0;

	GolVec3 localPosition;
	localPosition.Clear();
	EmitRing(&localPosition, &m_baseColor, 0, 0);
	m_textureColumn = 1;

	m_entity.SetPosition(*p_position);

	GolVec3 direction;
	GolMath::NormalizeVector3(*p_direction, &direction);

	LegoFloat dot = GOLVECTOR3_DOT(direction, up);
	if (dot >= 1.0f || dot <= g_minSoundPan) {
		up.m_x = 1.0f;
		up.m_y = 0.0f;
		up.m_z = 0.0f;
	}

	m_entity.SetDirectionUp(direction, up);
}

// FUNCTION: LEGORACERS 0x00494030
void BeamMesh::AdvanceSection(const GolVec3* p_position)
{
	GolTransformBase* transform = m_sceneNode->GetTransform(m_sectionIndex);

	GolVec3 vector;
	vector.m_x = m_lastPosition.m_x - m_startPosition.m_x;
	vector.m_y = m_lastPosition.m_y - m_startPosition.m_y;
	vector.m_z = m_lastPosition.m_z - m_startPosition.m_z;

	GolVec3 transformed;
	m_entity.RotateToLocal(vector, &transformed);
	transform->SetPosition(&transformed);

	vector.m_x = p_position->m_x - m_lastPosition.m_x;
	vector.m_y = p_position->m_y - m_lastPosition.m_y;
	vector.m_z = p_position->m_z - m_lastPosition.m_z;
	m_entity.RotateToLocal(vector, &transformed);

	vector.m_x = 0.0f;
	vector.m_y = 0.0f;
	vector.m_z = 1.0f;
	transform->SetRightDirection(&transformed, &vector);

	m_sectionIndex++;
	m_lastPosition = *p_position;
	m_flags &= ~c_flagSectionAttached;
}

// FUNCTION: LEGORACERS 0x00494140
void BeamMesh::AppendPoint(const GolVec3* p_position)
{
	GolVec3 delta;
	delta.m_x = p_position->m_x - m_lastPosition.m_x;
	delta.m_y = p_position->m_y - m_lastPosition.m_y;
	delta.m_z = p_position->m_z - m_lastPosition.m_z;

	LegoFloat distanceSquared = GOLVECTOR3_DOT(delta, delta);
	if (distanceSquared < g_beamMinStepDistanceSquared) {
		return;
	}

	GolVec3 localPosition;
	localPosition.m_x = static_cast<LegoFloat>(::sqrt(distanceSquared));
	localPosition.m_y = 0.0f;
	localPosition.m_z = 0.0f;

	EmitRing(&localPosition, &m_baseColor, m_textureColumn, 0);
	EmitQuads();

	if (m_material->GetFlags() & GolMaterial::c_flagTextured) {
		m_textureColumn++;
		if (m_textureColumn > m_textureColumnCount) {
			EmitRing(&localPosition, &m_baseColor, 0, 0);
			m_textureColumn = 1;
		}
	}

	FlushRuns();
	AdvanceSection(p_position);
}

// FUNCTION: LEGORACERS 0x00494230
void BeamMesh::Finish()
{
	if (m_indexCursor != 0) {
		FlushRuns();

		GolModelBase* model = m_model;
		model->GetMutableGroups()[m_groupCursor] = c_groupClose;
		LegoU32 dirty = TRUE;
		model->SetDirty(dirty);
		m_flags |= dirty;
	}

	m_model->AddFlags(FALSE);
	m_model->AddFlagsWithBounds(FALSE, FALSE);
}

// FUNCTION: LEGORACERS 0x00494290
void BeamMesh::EmitRing(
	const GolVec3* p_position,
	const ColorRGBA* p_color,
	LegoU32 p_textureColumn,
	LegoU32 p_offsetIndex
)
{
	GolVec2 texture;
	texture.m_y = static_cast<LegoFloat>(static_cast<LegoS32>(p_textureColumn));

	if (static_cast<LegoU32>(m_ringVertexIndex) + m_ringVertexCount * 2 >= 0x40) {
		FlushWindow();
	}
	else {
		m_previousRingVertexIndex = m_ringVertexIndex;
		m_ringVertexIndex += m_ringVertexCount;
	}

	LegoU32 i;
	if (m_flags & c_flagUseSegmentOffsets) {
		for (i = 0; i < m_ringVertexCount; i++) {
			GolVec3 vertex;
			vertex.m_x = m_ringVertices[i].m_x + p_position->m_x;
			vertex.m_x += m_segmentOffsets[p_offsetIndex].m_x;
			vertex.m_y = p_position->m_y + m_ringVertices[i].m_y + m_segmentOffsets[p_offsetIndex].m_y;
			vertex.m_z = p_position->m_z + m_ringVertices[i].m_z + m_segmentOffsets[p_offsetIndex].m_z;

			m_vertices->SetPosition(m_vertexCursor, vertex);
			m_vertices->SetColor(m_vertexCursor, *p_color);

			texture.m_x = m_ringTextureXs[i];
			m_vertices->SetTextureCoordinate(m_vertexCursor++, texture);
		}
	}
	else {
		for (i = 0; i < m_ringVertexCount; i++) {
			GolVec3 vertex;
			vertex.m_x = p_position->m_x + m_ringVertices[i].m_x;
			vertex.m_y = p_position->m_y + m_ringVertices[i].m_y;
			vertex.m_z = p_position->m_z + m_ringVertices[i].m_z;

			m_vertices->SetPosition(m_vertexCursor, vertex);
			m_vertices->SetColor(m_vertexCursor, *p_color);

			texture.m_x = m_ringTextureXs[i];
			m_vertices->SetTextureCoordinate(m_vertexCursor++, texture);
		}
	}
}

// FUNCTION: LEGORACERS 0x00494480
void BeamMesh::EmitQuads()
{
	GdbModelIndexArray::Indices* indices = &m_indices[m_indexCursor];
	m_indexCursor += m_ringQuadCount * 2;

	for (LegoU32 i = 0; i < m_ringQuadCount; i++) {
		LegoU32 lower = m_ringVertexIndex + i;
		LegoU32 upper = m_previousRingVertexIndex + i;

		indices->m_c = static_cast<LegoU8>(lower);
		indices->m_b = static_cast<LegoU8>(lower + 1);
		indices->m_a = static_cast<LegoU8>(upper);
		indices++;

		indices->m_c = static_cast<LegoU8>(lower + 1);
		indices->m_b = static_cast<LegoU8>(upper + 1);
		indices->m_a = static_cast<LegoU8>(upper);
		indices++;
	}
}

// FUNCTION: LEGORACERS 0x004944e0
void BeamMesh::FlushWindow()
{
	LegoU32 vertexCount = m_vertexCursor - m_runStartVertex;
	LegoU32 triangleCount = m_indexCursor - m_runStartIndex;
	GolModelBase* model = m_model;

	if (vertexCount != 0 || triangleCount != 0) {
		if (!(m_flags & c_flagSectionAttached)) {
			LegoU32 groupIndex = m_groupCursor++;
			model->GetMutableGroups()[groupIndex] = c_groupAttachSection;
			model->GetMutableGroups()[groupIndex] |= m_sectionIndex & 0x00ffffff;
			model->SetDirty(TRUE);
			m_flags |= c_flagSectionAttached;
		}

		LegoU32 groupIndex = m_groupCursor++;
		model->GetMutableGroups()[groupIndex] = 0;
		model->GetMutableGroups()[groupIndex] |= (m_windowBaseVertex & 0x3f) << 22;
		model->GetMutableGroups()[groupIndex] |= ((vertexCount - 1) << 16) & 0x003f0000;
		model->GetMutableGroups()[groupIndex] |= m_runStartVertex & 0xffff;
		model->SetDirty(TRUE);

		groupIndex = m_groupCursor++;
		model->GetMutableGroups()[groupIndex] = c_groupTriangleRun;
		model->GetMutableGroups()[groupIndex] |= (triangleCount & 0x7f) << 16;
		model->GetMutableGroups()[groupIndex] |= m_runStartIndex & 0xffff;
		model->SetDirty(TRUE);
	}

	LegoU32 groupIndex = m_groupCursor++;
	model->GetMutableGroups()[groupIndex] = 0;
	model->GetMutableGroups()[groupIndex] |= ((m_ringVertexCount - 1) << 16) & 0x003f0000;
	model->GetMutableGroups()[groupIndex] |= (m_vertexCursor - m_ringVertexCount) & 0xffff;
	model->SetDirty(TRUE);

	m_ringVertexIndex = m_ringVertexCount;
	m_windowBaseVertex = m_ringVertexCount;
	m_previousRingVertexIndex = 0;
	m_runStartVertex = m_vertexCursor;
	m_runStartIndex = m_indexCursor;
}

// FUNCTION: LEGORACERS 0x004946b0
void BeamMesh::FlushRuns()
{
	LegoU32 vertexCount = m_vertexCursor - m_runStartVertex;
	LegoU32 triangleCount = m_indexCursor - m_runStartIndex;

	if (vertexCount == 0 && triangleCount == 0) {
		return;
	}

	if (!(m_flags & c_flagSectionAttached)) {
		LegoU32 groupIndex = m_groupCursor++;
		m_model->GetMutableGroups()[groupIndex] = c_groupAttachSection;
		m_model->GetMutableGroups()[groupIndex] |= m_sectionIndex & 0x00ffffff;
		m_model->SetDirty(TRUE);
		m_flags |= c_flagSectionAttached;
	}

	LegoU32 groupIndex = m_groupCursor++;
	m_model->GetMutableGroups()[groupIndex] = 0;
	m_model->GetMutableGroups()[groupIndex] |= (m_windowBaseVertex & 0x3f) << 22;
	m_model->GetMutableGroups()[groupIndex] |= ((vertexCount - 1) << 16) & 0x003f0000;
	m_model->GetMutableGroups()[groupIndex] |= m_runStartVertex & 0xffff;
	m_model->SetDirty(TRUE);

	groupIndex = m_groupCursor++;
	m_model->GetMutableGroups()[groupIndex] = c_groupTriangleRun;
	m_model->GetMutableGroups()[groupIndex] |= (triangleCount & 0x7f) << 16;
	m_model->GetMutableGroups()[groupIndex] |= m_runStartIndex & 0xffff;
	m_model->SetDirty(TRUE);

	m_windowBaseVertex += vertexCount;
	m_runStartVertex = m_vertexCursor;
	m_runStartIndex = m_indexCursor;
}

// FUNCTION: LEGORACERS 0x00494820
void BeamMesh::SetColors(
	const ColorRGBA* p_baseColor,
	const ColorRGBA* p_secondaryColor,
	const ColorRGBA* p_tertiaryColor
)
{
	m_baseColor = *p_baseColor;
	m_secondaryColor = *p_secondaryColor;
	m_tertiaryColor = *p_tertiaryColor;
}

// FUNCTION: LEGORACERS 0x00494850
void BeamMesh::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_flags & 1) {
		m_entity.Draw(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00494870
void BeamMesh::AppendSpan(const GolVec3* p_position, LegoFloat p_amount)
{
	if (m_segmentCount <= 1) {
		AppendPoint(p_position);
		return;
	}

	GolVec3 delta;
	delta.m_x = p_position->m_x - m_lastPosition.m_x;
	delta.m_y = p_position->m_y - m_lastPosition.m_y;
	delta.m_z = p_position->m_z - m_lastPosition.m_z;

	LegoFloat distanceSquared = GOLVECTOR3_DOT(delta, delta);
	if (distanceSquared < g_beamMinStepDistanceSquared) {
		return;
	}

	LegoFloat distance = static_cast<LegoFloat>(::sqrt(distanceSquared));
	GolVec3 startPosition;
	startPosition.m_x = 0.0f;
	startPosition.m_y = 0.0f;
	startPosition.m_z = 0.0f;

	GolVec3 endPosition;
	endPosition.m_x = distance;
	endPosition.m_y = 0.0f;
	endPosition.m_z = 0.0f;

	GolVec3 middlePosition;
	middlePosition.m_x = distance * 0.5f;
	middlePosition.m_y = 0.0f;
	middlePosition.m_z = 0.0f;

	ColorRGBA endColor = p_amount > 0.0f ? m_secondaryColor : m_tertiaryColor;
	LegoFloat amount = 0.0f;

	LegoU32 offsetIndex = 0;
	for (LegoU32 i = 0; i < m_segmentCount - 1; i++) {
		amount += m_segmentStep;

		GolVec3 firstPosition;
		ColorRGBA firstColor;
		Interpolate(&startPosition, &middlePosition, &m_baseColor, &endColor, amount, &firstPosition, &firstColor);

		GolVec3 secondPosition;
		ColorRGBA secondColor;
		Interpolate(&middlePosition, &endPosition, &endColor, &m_baseColor, amount, &secondPosition, &secondColor);

		GolVec3 localPosition;
		ColorRGBA color;
		Interpolate(&firstPosition, &secondPosition, &firstColor, &secondColor, amount, &localPosition, &color);

		EmitRing(&localPosition, &color, m_textureColumn, offsetIndex);
		EmitQuads();

		if (m_material->GetFlags() & GolMaterial::c_flagTextured) {
			m_textureColumn++;
			if (m_textureColumn > m_textureColumnCount) {
				EmitRing(&localPosition, &color, 0, offsetIndex);
				m_textureColumn = 1;
			}
		}

		offsetIndex++;
	}

	EmitRing(&endPosition, &m_baseColor, m_textureColumn, offsetIndex);
	EmitQuads();

	if (m_material->GetFlags() & GolMaterial::c_flagTextured) {
		m_textureColumn++;
		if (m_textureColumn > m_textureColumnCount) {
			m_textureColumn = 1;
		}
	}

	FlushRuns();
	AdvanceSection(p_position);
}

// FUNCTION: LEGORACERS 0x00494ad0
void BeamMesh::Interpolate(
	const GolVec3* p_fromPosition,
	const GolVec3* p_toPosition,
	const ColorRGBA* p_fromColor,
	const ColorRGBA* p_toColor,
	LegoFloat p_amount,
	GolVec3* p_positionResult,
	ColorRGBA* p_colorResult
)
{
	p_positionResult->m_x = p_toPosition->m_x - p_fromPosition->m_x;
	p_positionResult->m_y = p_toPosition->m_y - p_fromPosition->m_y;
	GolVec3 scaledPosition;
	p_positionResult->m_z = p_toPosition->m_z - p_fromPosition->m_z;

	scaledPosition.m_x = p_positionResult->m_x * p_amount;
	scaledPosition.m_y = p_positionResult->m_y * p_amount;
	p_positionResult->m_z *= p_amount;

	p_positionResult->m_x = scaledPosition.m_x + p_fromPosition->m_x;
	p_positionResult->m_y = scaledPosition.m_y + p_fromPosition->m_y;
	p_positionResult->m_z += p_fromPosition->m_z;

	p_colorResult->m_red = static_cast<LegoU8>(
		p_fromColor->m_red + static_cast<LegoS32>((p_toColor->m_red - p_fromColor->m_red) * p_amount)
	);
	p_colorResult->m_grn = static_cast<LegoU8>(
		p_fromColor->m_grn + static_cast<LegoS32>((p_toColor->m_grn - p_fromColor->m_grn) * p_amount)
	);
	p_colorResult->m_blu = static_cast<LegoU8>(
		p_fromColor->m_blu + static_cast<LegoS32>((p_toColor->m_blu - p_fromColor->m_blu) * p_amount)
	);
	p_colorResult->m_alp = static_cast<LegoU8>(
		p_fromColor->m_alp + static_cast<LegoS32>((p_toColor->m_alp - p_fromColor->m_alp) * p_amount)
	);
}

// FUNCTION: LEGORACERS 0x00494be0
void BeamMesh::SetSegmentOffsets(const GolVec3* p_offsets)
{
	m_segmentOffsets = p_offsets;
	m_flags |= c_flagUseSegmentOffsets;
}

// FUNCTION: LEGORACERS 0x00494c00
BeamEntity::BeamEntity()
{
	m_sceneNode = 0;
	m_faceCamera = 0;
}

// FUNCTION: LEGORACERS 0x00494c20
BeamEntity* BeamEntity::Destroy(undefined4 p_flags)
{
	BeamEntity* result = this;
	this->~BeamEntity();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00494c40
BeamEntity::~BeamEntity()
{
	ResetModelState();
}

// FUNCTION: LEGORACERS 0x00494c50
void BeamEntity::Initialize(
	GolModelBase* p_model,
	GolSceneNode* p_sceneNode,
	undefined4 p_faceCamera,
	LegoFloat p_modelDistance
)
{
	GolModelEntity::SetPrimaryModel(p_model, p_modelDistance);
	m_sceneNode = p_sceneNode;
	m_faceCamera = p_faceCamera;
}

// FUNCTION: LEGORACERS 0x00494c80
void BeamEntity::ResetModelState()
{
	m_sceneNode = 0;
}

// FUNCTION: LEGORACERS 0x00494c90
GolSceneNode* BeamEntity::GetSceneNode(undefined4)
{
	return m_sceneNode;
}

// FUNCTION: LEGORACERS 0x00494ca0
void BeamEntity::Draw(GolRenderDevice& p_renderer)
{
	if (m_faceCamera != 0) {
		GolVec3 cameraRight;
		p_renderer.GetCurrentCamera()->GetTransform()->GetRight(&cameraRight);
		cameraRight.m_x = -cameraRight.m_x;
		cameraRight.m_y = -cameraRight.m_y;
		cameraRight.m_z = -cameraRight.m_z;

		GolVec3 localRight;
		RotateToLocal(cameraRight, &localRight);

		for (LegoU32 i = 0; i < m_sceneNode->GetCapacity(); i++) {
			GolTransformBase* transform = m_sceneNode->GetTransform(i);
			GolVec3 right;
			transform->GetRightDirection(&cameraRight, &right);

			LegoFloat dot =
				localRight.m_z * cameraRight.m_z + localRight.m_y * cameraRight.m_y + localRight.m_x * cameraRight.m_x;
			if (dot < 1.0f && dot > g_minSoundPan) {
				transform->SetRightDirection(&cameraRight, &localRight);
			}
		}
	}

	p_renderer.DrawModelEntity(this);
}

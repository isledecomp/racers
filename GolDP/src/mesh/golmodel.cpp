#include "mesh/golmodel.h"

#include "gdbmodelindexarray.h"
#include "gdbvertexarray.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmaterial.h"
#include "mesh/gdbcoloredvertexarray.h"
#include "mesh/gdbcoloredvertexarraybase.h"
#include "mesh/gdbnormalvertexarray.h"
#include "mesh/gdbprelitvertexarray.h"
#include "mesh/gdbuncoloredvertexarray.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(GolModel, 0x48)

// FUNCTION: GOLDP 0x10006840
GolModel::GolModel()
{
	m_modelVertexArray = NULL;
}

// FUNCTION: GOLDP 0x10006860
GolModel::~GolModel()
{
	Destroy();
}

// FUNCTION: GOLDP 0x100068e0
void GolModel::Load(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_groups) {
		Destroy();
	}

	GolModelBase::Load(p_renderer, p_name, p_binary);

	if (m_modelVertexArray != NULL) {
		ComputeBounds(&m_center, &m_radius, m_scale);
	}

	m_dirty = TRUE;
}

// FUNCTION: GOLDP 0x10006930
void GolModel::Allocate(
	GolRenderDevice* p_renderer,
	undefined2 p_vertexType,
	undefined4 p_arg3,
	undefined4 p_arg4,
	undefined4 p_arg5,
	undefined4 p_arg6
)
{
	if (m_groups) {
		Destroy();
	}

	if (p_arg6 > 0) {
		m_materialTable.Initialize(p_renderer, p_arg6);
	}

	switch (p_vertexType) {
	case e_vertexType1:
		m_modelVertexArray = new GdbColoredVertexArray;
		break;
	case e_vertexType2:
		m_modelVertexArray = new GdbNormalVertexArray;
		break;
	case e_vertexType3:
		m_modelVertexArray = new GdbPrelitVertexArray;
		break;
	default:
		GOL_FATALERROR_MESSAGE("Unsupported vertex type");
		break;
	}

	m_vertexArray = m_modelVertexArray;
	if (m_vertexArray == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	AllocateIndices(p_arg4, p_arg5);
	m_modelVertexArray->Allocate(p_arg3);
	m_dirty = 1;
}

// FUNCTION: GOLDP 0x10006a60
void GolModel::Destroy()
{
	if (m_modelVertexArray != NULL) {
		m_modelVertexArray->Destroy();
		delete m_modelVertexArray;
		m_modelVertexArray = NULL;
		m_vertexArray = 0;
	}

	GolModelBase::Destroy();
}

// FUNCTION: GOLDP 0x10006aa0
void GolModel::ParseUncoloredVertices(GolFileParser& p_parser)
{
	if (m_modelVertexArray != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_modelVertexArray = new GdbUncoloredVertexArray;
	m_vertexArray = m_modelVertexArray;
	if (m_vertexArray == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_modelVertexArray->Parse(p_parser);
}

// FUNCTION: GOLDP 0x10006b30
void GolModel::ParseColoredVertices(GolFileParser& p_parser)
{
	if (m_modelVertexArray != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_modelVertexArray = new GdbColoredVertexArray;
	m_vertexArray = m_modelVertexArray;
	if (m_vertexArray == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_modelVertexArray->Parse(p_parser);
}

// FUNCTION: GOLDP 0x10006bc0
void GolModel::ParseNormalVertices(GolFileParser& p_parser)
{
	if (m_modelVertexArray != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_modelVertexArray = new GdbNormalVertexArray;
	m_vertexArray = m_modelVertexArray;
	if (m_vertexArray == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_modelVertexArray->Parse(p_parser);
}

// STUB: GOLDP 0x10006c50
void GolModel::Draw(GolD3DRenderDevice* p_renderer, MaterialTable* p_materialTable)
{
	if (p_materialTable == NULL) {
		p_materialTable = &m_materialTable;
	}

	if (m_dirty) {
		LegoU32* group = m_groups;
		LegoU32* end = m_groups + m_groupCount;

		for (; group < end; group++) {
			LegoU32 groupData = *group;
			LegoU32 groupType = groupData;
			groupType &= c_groupTypeMask;
			if (groupType == c_groupTypeTriangleBatch) {
				LegoU32 firstTriangle = groupData;
				LegoU32 triangleCount = groupData;
				triangleCount >>= c_groupDataUpperWordShift;
				triangleCount &= c_triangleCountMask;
				firstTriangle &= c_materialMatrixIndexMask;
				LegoU32 lastVertex = FindMaxVertexIndex(firstTriangle, triangleCount) & c_vertexCountMask;
				*group = ((((lastVertex | c_vertexIndexHighFlag) << 7) | (triangleCount & c_triangleCountMask))
						  << c_groupDataUpperWordShift) |
						 (firstTriangle & c_materialMatrixIndexMask);
			}
			else if (groupType == c_groupTypeEnd) {
				break;
			}
		}

		m_dirty = FALSE;
	}

	GdbColoredVertexArrayBase* vertexArray = static_cast<GdbColoredVertexArrayBase*>(m_modelVertexArray);
	p_renderer->m_sourcePositions = vertexArray->GetPositions();
	p_renderer->m_sourceTexCoords = vertexArray->GetTextureCoordinates();
	if (vertexArray->HasTransformedColors()) {
		p_renderer->m_sourceColors = vertexArray->GetTransformedColors();
	}
	else {
		p_renderer->m_sourceColors = vertexArray->GetColors();
	}

	GdbModelIndexArray* indexArray = static_cast<GdbModelIndexArray*>(m_indexArray);
	p_renderer->m_sourceIndices = indexArray->GetIndexBytes();
	p_renderer->m_materialCommand.m_indices = p_renderer->m_sourceIndices;

	LegoU32* group = m_groups;
	LegoU32* end = m_groups + m_groupCount;

	for (; group < end; group++) {
		LegoU32 groupData = *group;
		LegoU32 groupType = groupData & c_groupTypeMask;
		if (groupType <= c_groupTypeMaterial) {
			if (groupType == c_groupTypeMaterial) {
				GolMaterial* material =
					static_cast<GolMaterial*>(p_materialTable->GetEntry(groupData & c_materialMatrixIndexMask));
				(p_renderer->*p_renderer->m_applyMaterialFn)(material);
				p_renderer->SetCurrentTexture(material->GetTexture());
			}
			else if (groupType == c_groupTypeTriangles) {
				LegoU32 vertexCount = groupData >> c_groupDataUpperWordShift;
				LegoU32 firstVertex = groupData;
				vertexCount &= c_vertexCountMask;
				firstVertex &= c_materialMatrixIndexMask;
				vertexCount++;
				(p_renderer->*p_renderer->m_drawTriangleFn1)(
					(groupData >> c_matrixSelectShift) & c_vertexCountMask,
					firstVertex,
					vertexCount
				);
			}
			else if (groupType == c_groupTypeTriangleBatch) {
				LegoU32 lastVertex = groupData >> c_lastVertexShift;
				LegoU32 triangleCount = groupData >> c_groupDataUpperWordShift;
				lastVertex &= c_vertexCountMask;
				triangleCount &= c_triangleCountMask;
				(p_renderer->*p_renderer->m_drawTriangleFn2)(
					groupData & c_materialMatrixIndexMask,
					triangleCount,
					lastVertex
				);
			}
		}
		else if (groupType == c_groupTypeMatrix) {
			p_renderer->FUN_1000acf0(groupData & c_materialMatrixIndexMask);
		}
		else if (groupType == c_groupTypeEnd) {
			break;
		}
	}
}

// STUB: GOLDP 0x10006e00
void GolModel::DrawNode(
	GolD3DRenderDevice* p_renderer,
	MaterialTable* p_materialTable,
	GolBoundingShape::TreeNode::Node* p_node
)
{
	if (p_materialTable == NULL) {
		p_materialTable = &m_materialTable;
	}

	if (m_dirty) {
		LegoU32* group = m_groups;
		LegoU32* end = m_groups + m_groupCount;

		for (; group < end; group++) {
			LegoU32 groupData = *group;
			LegoU32 groupType = groupData;
			groupType &= c_groupTypeMask;
			if (groupType == c_groupTypeTriangleBatch) {
				LegoU32 firstTriangle = groupData;
				LegoU32 triangleCount = groupData;
				triangleCount >>= c_groupDataUpperWordShift;
				triangleCount &= c_triangleCountMask;
				firstTriangle &= c_materialMatrixIndexMask;
				LegoU32 lastVertex = FindMaxVertexIndex(firstTriangle, triangleCount);
				lastVertex &= c_vertexCountMask;
				*group = ((((lastVertex | c_vertexIndexHighFlag) << 7) | (triangleCount & c_triangleCountMask))
						  << c_groupDataUpperWordShift) |
						 (firstTriangle & c_materialMatrixIndexMask);
			}
			else if (groupType == c_groupTypeEnd) {
				break;
			}
		}

		m_dirty = FALSE;
	}

	GdbColoredVertexArrayBase* vertexArray = static_cast<GdbColoredVertexArrayBase*>(m_modelVertexArray);
	p_renderer->m_sourcePositions = vertexArray->GetPositions();
	p_renderer->m_sourceTexCoords = vertexArray->GetTextureCoordinates();
	if (vertexArray->HasTransformedColors()) {
		p_renderer->m_sourceColors = vertexArray->GetTransformedColors();
	}
	else {
		p_renderer->m_sourceColors = vertexArray->GetColors();
	}

	GdbModelIndexArray* indexArray = static_cast<GdbModelIndexArray*>(m_indexArray);
	p_renderer->m_sourceIndices = indexArray->GetIndexBytes();
	p_renderer->m_materialCommand.m_indices = p_renderer->m_sourceIndices;

	LegoU32* group = m_groups + p_node->m_firstGroup;
	LegoU32* end = m_groups + (p_node->m_firstGroup + p_node->m_groupCount);
	for (; group < end; group++) {
		LegoU32 groupData = *group;
		LegoU32 groupType = groupData & c_groupTypeMask;

		if (groupType <= c_groupTypeMaterial) {
			if (groupType == c_groupTypeMaterial) {
				GolMaterial* material =
					static_cast<GolMaterial*>(p_materialTable->GetEntry(groupData & c_materialMatrixIndexMask));
				(p_renderer->*p_renderer->m_applyMaterialFn)(material);
				p_renderer->SetCurrentTexture(material->GetTexture());
			}
			else if (groupType == c_groupTypeTriangles) {
				LegoU32 vertexCount = groupData >> c_groupDataUpperWordShift;
				LegoU32 firstVertex = groupData;
				vertexCount &= c_vertexCountMask;
				firstVertex &= c_materialMatrixIndexMask;
				vertexCount++;
				(p_renderer->*p_renderer->m_drawTriangleFn1)(
					(groupData >> c_matrixSelectShift) & c_vertexCountMask,
					firstVertex,
					vertexCount
				);
			}
			else if (groupType == c_groupTypeTriangleBatch) {
				LegoU32 lastVertex = groupData >> c_lastVertexShift;
				LegoU32 triangleCount = groupData >> c_groupDataUpperWordShift;
				lastVertex &= c_vertexCountMask;
				triangleCount &= c_triangleCountMask;
				(p_renderer->*p_renderer->m_drawTriangleFn2)(
					groupData & c_materialMatrixIndexMask,
					triangleCount,
					lastVertex
				);
			}
		}
		else if (groupType == c_groupTypeEnd) {
			break;
		}
	}
}

// FUNCTION: GOLDP 0x10006fa0
LegoU32 GolModel::FindMaxVertexIndex(LegoU32 p_firstTriangle, LegoU32 p_triangleCount) const
{
	GdbModelIndexArray::Indices* indices = static_cast<GdbModelIndexArray*>(m_indexArray)->GetMutableIndices();
	GdbModelIndexArray::Indices* triangle = indices + p_firstTriangle;
	GdbModelIndexArray::Indices* end = indices + (p_firstTriangle + p_triangleCount);
	LegoU16 result = 0;

	for (; triangle < end; triangle++) {
		LegoU16 index = triangle->m_a;
		if (index > result) {
			result = index;
		}
		index = triangle->m_b;
		if (index > result) {
			result = index;
		}
		index = triangle->m_c;
		if (index > result) {
			result = index;
		}
	}

	return result & 0xffff;
}

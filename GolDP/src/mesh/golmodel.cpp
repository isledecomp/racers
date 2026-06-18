#include "mesh/golmodel.h"

#include "duskwindbananarelic0x24.h"
#include "gdbmodelindexarray0xc.h"
#include "gdbvertexarray0xc.h"
#include "golerror.h"
#include "golfileparser.h"
#include "mesh/gdbcommonvertexarray0x1c.h"
#include "mesh/gdbvertexarraymistery0x1c.h"
#include "mesh/gdbvertexarraytypeone0x1c.h"
#include "mesh/gdbvertexarraytypethree0x20.h"
#include "mesh/gdbvertexarraytypetwo0x20.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(GolModel, 0x48)

// FUNCTION: GOLDP 0x10006840
GolModel::GolModel()
{
	m_unk0x40 = NULL;
}

// FUNCTION: GOLDP 0x10006860
GolModel::~GolModel()
{
	VTable0x24();
}

// FUNCTION: GOLDP 0x100068e0
void GolModel::VTable0x1c(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_unk0x24) {
		VTable0x24();
	}

	GolModelBase::VTable0x1c(p_renderer, p_name, p_binary);

	if (m_unk0x40 != NULL) {
		VTable0x38(&m_unk0x28, &m_unk0x34, m_unk0x38);
	}

	m_unk0x3c = TRUE;
}

// FUNCTION: GOLDP 0x10006930
void GolModel::VTable0x18(
	GolRenderDevice* p_renderer,
	undefined2 p_vertexType,
	undefined4 p_arg3,
	undefined4 p_arg4,
	undefined4 p_arg5,
	undefined4 p_arg6
)
{
	if (m_unk0x24) {
		VTable0x24();
	}

	if (p_arg6 > 0) {
		m_unk0x04.FUN_10025df0(p_renderer, p_arg6);
	}

	switch (p_vertexType) {
	case e_vertexType1:
		m_unk0x40 = new GdbVertexArrayTypeOne0x1c;
		break;
	case e_vertexType2:
		m_unk0x40 = new GdbVertexArrayTypeTwo0x20;
		break;
	case e_vertexType3:
		m_unk0x40 = new GdbVertexArrayTypeThree0x20;
		break;
	default:
		GOL_FATALERROR_MESSAGE("Unsupported vertex type");
		break;
	}

	m_unk0x10 = m_unk0x40;
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	FUN_100272e0(p_arg4, p_arg5);
	m_unk0x40->VTable0x04(p_arg3);
	m_unk0x3c = 1;
}

// FUNCTION: GOLDP 0x10006a60
void GolModel::VTable0x24()
{
	if (m_unk0x40 != NULL) {
		m_unk0x40->VTable0x0c();
		delete m_unk0x40;
		m_unk0x40 = NULL;
		m_unk0x10 = 0;
	}

	GolModelBase::VTable0x24();
}

// FUNCTION: GOLDP 0x10006aa0
void GolModel::VTable0x0c(GolFileParser& p_parser)
{
	if (m_unk0x40 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x40 = new GdbVertexArrayMistery0x1c;
	m_unk0x10 = m_unk0x40;
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x40->VTable0x08(p_parser);
}

// FUNCTION: GOLDP 0x10006b30
void GolModel::VTable0x10(GolFileParser& p_parser)
{
	if (m_unk0x40 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x40 = new GdbVertexArrayTypeOne0x1c;
	m_unk0x10 = m_unk0x40;
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x40->VTable0x08(p_parser);
}

// FUNCTION: GOLDP 0x10006bc0
void GolModel::VTable0x14(GolFileParser& p_parser)
{
	if (m_unk0x40 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x40 = new GdbVertexArrayTypeTwo0x20;
	m_unk0x10 = m_unk0x40;
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x40->VTable0x08(p_parser);
}

// STUB: GOLDP 0x10006c50
void GolModel::FUN_10006c50(GolD3DRenderDevice* p_renderer, MaterialTable0x0c* p_materialTable)
{
	if (p_materialTable == NULL) {
		p_materialTable = &m_unk0x04;
	}

	if (m_unk0x3c) {
		LegoU32* group = m_unk0x24;
		LegoU32* end = m_unk0x24 + m_countGroups;

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
				LegoU32 lastVertex = FUN_10006fa0(firstTriangle, triangleCount) & c_vertexCountMask;
				*group = ((((lastVertex | c_vertexIndexHighFlag) << 7) | (triangleCount & c_triangleCountMask))
						  << c_groupDataUpperWordShift) |
						 (firstTriangle & c_materialMatrixIndexMask);
			}
			else if (groupType == c_groupTypeEnd) {
				break;
			}
		}

		m_unk0x3c = FALSE;
	}

	GdbCommonVertexArray0x1c* vertexArray = static_cast<GdbCommonVertexArray0x1c*>(m_unk0x40);
	p_renderer->m_unk0xc4c0c = vertexArray->GetPositions();
	p_renderer->m_unk0xc4c10 = vertexArray->GetTextureCoordinates();
	if (vertexArray->HasTransformedColors()) {
		p_renderer->m_unk0xc4c14 = vertexArray->GetTransformedColors();
	}
	else {
		p_renderer->m_unk0xc4c14 = vertexArray->GetColors();
	}

	GdbModelIndexArray0xc* indexArray = static_cast<GdbModelIndexArray0xc*>(m_unk0x18);
	p_renderer->m_unk0xc4c18 = indexArray->GetIndexBytes();
	p_renderer->m_unk0xc855c = p_renderer->m_unk0xc4c18;

	LegoU32* group = m_unk0x24;
	LegoU32* end = m_unk0x24 + m_countGroups;

	for (; group < end; group++) {
		LegoU32 groupData = *group;
		LegoU32 groupType = groupData & c_groupTypeMask;
		if (groupType <= c_groupTypeMaterial) {
			if (groupType == c_groupTypeMaterial) {
				DuskwindBananaRelic0x24* material = static_cast<DuskwindBananaRelic0x24*>(
					p_materialTable->GetPosition(groupData & c_materialMatrixIndexMask)
				);
				(p_renderer->*p_renderer->m_unk0xc876c)(material);
				p_renderer->FUN_1000ac00(material->GetUnk0x04());
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
void GolModel::FUN_10006e00(
	GolD3DRenderDevice* p_renderer,
	MaterialTable0x0c* p_materialTable,
	GolBoundingShape::StructField0x08::Node* p_node
)
{
	if (p_materialTable == NULL) {
		p_materialTable = &m_unk0x04;
	}

	if (m_unk0x3c) {
		LegoU32* group = m_unk0x24;
		LegoU32* end = m_unk0x24 + m_countGroups;

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
				LegoU32 lastVertex = FUN_10006fa0(firstTriangle, triangleCount);
				lastVertex &= c_vertexCountMask;
				*group = ((((lastVertex | c_vertexIndexHighFlag) << 7) | (triangleCount & c_triangleCountMask))
						  << c_groupDataUpperWordShift) |
						 (firstTriangle & c_materialMatrixIndexMask);
			}
			else if (groupType == c_groupTypeEnd) {
				break;
			}
		}

		m_unk0x3c = FALSE;
	}

	GdbCommonVertexArray0x1c* vertexArray = static_cast<GdbCommonVertexArray0x1c*>(m_unk0x40);
	p_renderer->m_unk0xc4c0c = vertexArray->GetPositions();
	p_renderer->m_unk0xc4c10 = vertexArray->GetTextureCoordinates();
	if (vertexArray->HasTransformedColors()) {
		p_renderer->m_unk0xc4c14 = vertexArray->GetTransformedColors();
	}
	else {
		p_renderer->m_unk0xc4c14 = vertexArray->GetColors();
	}

	GdbModelIndexArray0xc* indexArray = static_cast<GdbModelIndexArray0xc*>(m_unk0x18);
	p_renderer->m_unk0xc4c18 = indexArray->GetIndexBytes();
	p_renderer->m_unk0xc855c = p_renderer->m_unk0xc4c18;

	LegoU32* group = m_unk0x24 + p_node->m_firstGroup;
	LegoU32* end = m_unk0x24 + (p_node->m_firstGroup + p_node->m_groupCount);
	for (; group < end; group++) {
		LegoU32 groupData = *group;
		LegoU32 groupType = groupData & c_groupTypeMask;

		if (groupType <= c_groupTypeMaterial) {
			if (groupType == c_groupTypeMaterial) {
				DuskwindBananaRelic0x24* material = static_cast<DuskwindBananaRelic0x24*>(
					p_materialTable->GetPosition(groupData & c_materialMatrixIndexMask)
				);
				(p_renderer->*p_renderer->m_unk0xc876c)(material);
				p_renderer->FUN_1000ac00(material->GetUnk0x04());
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
LegoU32 GolModel::FUN_10006fa0(LegoU32 p_firstTriangle, LegoU32 p_triangleCount) const
{
	GdbModelIndexArray0xc::Indices* indices = static_cast<GdbModelIndexArray0xc*>(m_unk0x18)->GetMutableIndices();
	GdbModelIndexArray0xc::Indices* triangle = indices + p_firstTriangle;
	GdbModelIndexArray0xc::Indices* end = indices + (p_firstTriangle + p_triangleCount);
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

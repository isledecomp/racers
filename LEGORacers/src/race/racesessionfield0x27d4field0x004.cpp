#include "decomp.h"
#include "duskwindbananarelic0x24.h"
#include "gdbmodelindexarray0xc.h"
#include "gdbvertexarray0xc.h"
#include "golboundingshape.h"
#include "golcollidableentity.h"
#include "golmodelbase.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSessionField0x27d4::Item::Field0x004, 0x11c)
DECOMP_SIZE_ASSERT(RaceSessionField0x27d4::Item::Field0x004::FloatBits, 0x04)
DECOMP_SIZE_ASSERT(RaceSessionField0x27d4::Item::Field0x004::ProjectedCoordinates, 0x08)
DECOMP_SIZE_ASSERT(RaceSessionField0x27d4::Item::Field0x004::ProjectedVertex, 0x20)

// GLOBAL: LEGORACERS 0x004c47a8
GolVec3 g_unk0x004c47a8[5];

// GLOBAL: LEGORACERS 0x004c3de8
LegoFloat g_unk0x004c3de8;

// GLOBAL: LEGORACERS 0x004c3dec
LegoFloat g_unk0x004c3dec;

// GLOBAL: LEGORACERS 0x004c3df4
LegoFloat g_unk0x004c3df4;

// GLOBAL: LEGORACERS 0x004c3df8
LegoFloat g_unk0x004c3df8;

// GLOBAL: LEGORACERS 0x004c3dfc
LegoFloat g_unk0x004c3dfc;

// GLOBAL: LEGORACERS 0x004c3e04
LegoFloat g_unk0x004c3e04;

// GLOBAL: LEGORACERS 0x004c3e08
LegoFloat g_unk0x004c3e08;

// GLOBAL: LEGORACERS 0x004c3e0c
LegoFloat g_unk0x004c3e0c;

// GLOBAL: LEGORACERS 0x004c3e14
LegoFloat g_unk0x004c3e14;

// GLOBAL: LEGORACERS 0x004c3e18
LegoFloat g_unk0x004c3e18;

// GLOBAL: LEGORACERS 0x004c3e1c
LegoFloat g_unk0x004c3e1c;

// GLOBAL: LEGORACERS 0x004c3e24
LegoFloat g_unk0x004c3e24;

// GLOBAL: LEGORACERS 0x004c3e28
RaceSessionField0x27d4::Item::Field0x004::ProjectedVertex g_unk0x004c3e28[76];

// FUNCTION: LEGORACERS 0x00403cc0
void GolBoundingShape::FUN_00403cc0(GolVec3* p_unk0x04, LegoU32 p_unk0x08)
{
	LegoFloat planeOffset;
	m_unk0x10++;
	StructField0x08* node = m_unk0x0c;

	while (node->m_type == StructField0x08::e_type0) {
		LegoFloat dot = node->m_unk0x04.m_t0.m_unk0x08;
		dot *= p_unk0x04->m_z;
		dot += node->m_unk0x04.m_t0.m_unk0x04 * p_unk0x04->m_y;
		LegoFloat dotX = p_unk0x04->m_x;
		dotX *= node->m_unk0x04.m_t0.m_unk0x00;
		dot += dotX;
		dot += node->m_unk0x04.m_t0.m_unk0x0c;

		LegoU32 nodeIndex;
		if (dot < 0.0f && node->m_unk0x04.m_t0.m_unk0x1a != StructField0x08::c_invalidIndex) {
			node->m_unk0x04.m_t0.m_unk0x14 = m_unk0x10;
			nodeIndex = node->m_unk0x04.m_t0.m_unk0x1a;
		}
		else if (node->m_unk0x04.m_t0.m_unk0x18 == StructField0x08::c_invalidIndex) {
			node->m_unk0x04.m_t0.m_unk0x14 = m_unk0x10;
			nodeIndex = node->m_unk0x04.m_t0.m_unk0x1a;
		}
		else {
			node->m_unk0x04.m_t0.m_unk0x10 = m_unk0x10;
			nodeIndex = node->m_unk0x04.m_t0.m_unk0x18;
		}

		node = &m_unk0x08[nodeIndex];
	}

	node->m_unk0x04.m_node.m_previous = NULL;
	node->m_unk0x04.m_node.m_next = NULL;
	if (node->m_unk0x02 == StructField0x08::c_invalidIndex) {
		StructField0x08::Node* entry = &node->m_unk0x04.m_node;
		m_unk0x28 = entry;
		m_unk0x24 = entry;
		return;
	}

	LegoU32 count = p_unk0x08;
	StructField0x08* firstNode = node;
	StructField0x08* previousNode = node;
	node = &m_unk0x08[node->m_unk0x02];
	LegoU32 stamp;

	for (;;) {
		stamp = m_unk0x10;

		if (node->m_unk0x04.m_t0.m_unk0x10 != stamp) {
			if (node->m_unk0x04.m_t0.m_unk0x14 != stamp) {
				LegoFloat dot = node->m_unk0x04.m_t0.m_unk0x08;
				dot *= p_unk0x04->m_z;
				dot += node->m_unk0x04.m_t0.m_unk0x04 * p_unk0x04->m_y;
				dot += node->m_unk0x04.m_t0.m_unk0x00 * p_unk0x04->m_x;

				if (dot < -node->m_unk0x04.m_t0.m_unk0x0c) {
					node->m_unk0x04.m_t0.m_unk0x14 = stamp;
					if (node->m_unk0x04.m_t0.m_unk0x1a == StructField0x08::c_invalidIndex) {
						continue;
					}

					node = &m_unk0x08[node->m_unk0x04.m_t0.m_unk0x1a];
				}
				else {
					node->m_unk0x04.m_t0.m_unk0x10 = stamp;
					if (node->m_unk0x04.m_t0.m_unk0x18 == StructField0x08::c_invalidIndex) {
						continue;
					}

					node = &m_unk0x08[node->m_unk0x04.m_t0.m_unk0x18];
				}
			}
			else {
				node->m_unk0x04.m_t0.m_unk0x10 = stamp;
				if (node->m_unk0x04.m_t0.m_unk0x18 == StructField0x08::c_invalidIndex) {
					continue;
				}
				LegoU32 i = 1;
				if (count <= i) {
					continue;
				}

				planeOffset = -node->m_unk0x04.m_t0.m_unk0x0c;
				LegoFloat* vertexY = &p_unk0x04[i].m_y;
				while (i < count) {
					LegoFloat dot = vertexY[1] * node->m_unk0x04.m_t0.m_unk0x08;
					dot += node->m_unk0x04.m_t0.m_unk0x04 * vertexY[0];
					dot += vertexY[-1] * node->m_unk0x04.m_t0.m_unk0x00;
					if (dot > planeOffset) {
						break;
					}

					i++;
					vertexY += 3;
				}

				if (i >= count) {
					continue;
				}

				node = &m_unk0x08[node->m_unk0x04.m_t0.m_unk0x18];
			}
		}
		else {
			if (node->m_unk0x04.m_t0.m_unk0x14 != stamp) {
				node->m_unk0x04.m_t0.m_unk0x14 = stamp;
				if (node->m_unk0x04.m_t0.m_unk0x1a == StructField0x08::c_invalidIndex) {
					continue;
				}
				LegoU32 i = 1;
				if (count <= i) {
					continue;
				}

				planeOffset = -node->m_unk0x04.m_t0.m_unk0x0c;
				LegoFloat* vertexY = &p_unk0x04[i].m_y;
				while (i < count) {
					LegoFloat dot = vertexY[1] * node->m_unk0x04.m_t0.m_unk0x08;
					dot += node->m_unk0x04.m_t0.m_unk0x04 * vertexY[0];
					dot += vertexY[-1] * node->m_unk0x04.m_t0.m_unk0x00;
					if (dot < planeOffset) {
						break;
					}

					i++;
					vertexY += 3;
				}

				if (i >= count) {
					continue;
				}

				node = &m_unk0x08[node->m_unk0x04.m_t0.m_unk0x1a];
			}
			else {
				if (node->m_unk0x02 == StructField0x08::c_invalidIndex) {
					break;
				}

				node = &m_unk0x08[node->m_unk0x02];
				continue;
			}
		}

		if (node->m_type != StructField0x08::e_type0) {
			previousNode->m_unk0x04.m_node.m_next = &node->m_unk0x04.m_node;
			node->m_unk0x04.m_node.m_previous = &previousNode->m_unk0x04.m_node;
			node->m_unk0x04.m_node.m_next = NULL;
			previousNode = node;
			node = &m_unk0x08[node->m_unk0x02];
		}
	}

	m_unk0x24 = &firstNode->m_unk0x04.m_node;
	m_unk0x28 = &previousNode->m_unk0x04.m_node;
}

// FUNCTION: LEGORACERS 0x00414a30
void RaceSessionField0x27d4::Item::Field0x004::FUN_00414a30(GolCollidableEntity* p_unk0x04)
{
	FUN_00415a60();

	GolBoundingShape* boundingShape = p_unk0x04->GetBoundingShape(0);
	GolModelBase* model = p_unk0x04->GetModel(0);
	boundingShape->FUN_00403cc0(g_unk0x004c47a8, sizeOfArray(g_unk0x004c47a8));
	FUN_00414a90(model);

	GolBoundingShape::StructField0x08::Node* entry = boundingShape->GetUnk0x24();
	while (entry != NULL) {
		FUN_00414b30(model, entry->m_firstGroup, entry->m_groupCount);
		entry = entry->m_next;
	}

	FUN_00414c00(model);
}

// FUNCTION: LEGORACERS 0x00414a90
void RaceSessionField0x27d4::Item::Field0x004::FUN_00414a90(GolModelBase* p_unk0x04)
{
	FUN_00414d50();

	p_unk0x04->VTable0x28(&m_unk0x114);

	IGdbModelIndexArray0x8* indexArrayBase;
	p_unk0x04->VTable0x30(&indexArrayBase);
	m_unk0x118 = static_cast<GdbModelIndexArray0xc*>(indexArrayBase)->GetIndexBytes();

	GolModelBase* model = m_unk0x004;
	model->VTable0x28(&m_unk0x008);

	m_unk0x004->VTable0x30(&indexArrayBase);
	LegoU8* destIndexBytes = static_cast<GdbModelIndexArray0xc*>(indexArrayBase)->GetIndexBytes();

	m_unk0x0b0 = 0;
	m_unk0x0a8 = 0;
	m_unk0x0b4 = 0;
	m_unk0x0ac = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;

	model = m_unk0x004;
	m_unk0x00c = destIndexBytes;
	LegoU32 one = 1;
	model->GetMutableGroups()[0] = c_commandModelFlags;
	model->SetDirty(one);
	m_unk0x0b8 = one;
}

// FUNCTION: LEGORACERS 0x00414b30
void RaceSessionField0x27d4::Item::Field0x004::FUN_00414b30(
	GolModelBase* p_unk0x04,
	LegoU32 p_unk0x08,
	LegoU32 p_unk0x0c
)
{
	LegoU32 start = p_unk0x08;
	GolModelBase* model = p_unk0x04;
	LegoU32 count = p_unk0x0c;
	if (count == 0) {
		count = model->GetGroupCount();
	}

	LegoU32 enabled = 1;
	LegoU32 end = start + count;
	if (start < end) {
		do {
			LegoU32 command = model->GetMutableGroups()[start];
			start++;
			LegoU32 commandType = command & c_commandMask;
			if (commandType <= c_commandModelFlags) {
				if (commandType != c_commandModelFlags) {
					if (commandType != c_commandVertices) {
						if (commandType == c_commandPolygon && enabled) {
							FUN_00414f40(command & c_commandVertexMask, (command >> 16) & 0x7f);
						}
					}
					else if (enabled) {
						FUN_00414e40(
							(command >> 22) & 0x3f,
							command & c_commandVertexMask,
							((command >> 16) & 0x3f) + 1
						);
					}
				}
				else {
					enabled = model->GetMaterialTable()->GetMaterial(command & c_commandVertexMask)->GetUnk0x08() &
							  c_commandModelFlagBit17;
				}
			}
			else if (commandType == c_commandEnd) {
				return;
			}
		} while (start < end);
	}
}

// FUNCTION: LEGORACERS 0x00414c00
void RaceSessionField0x27d4::Item::Field0x004::FUN_00414c00(GolModelBase* p_unk0x04)
{
	if (m_unk0x0c0) {
		FUN_00415980();
	}

	GolModelBase* model = m_unk0x004;
	LegoU32 groupIndex = m_unk0x0b8;
	model->GetMutableGroups()[groupIndex] = c_commandEnd;
	model->SetDirty(TRUE);
	GetUnk0x004()->VTable0x34(TRUE);
	GetUnk0x004()->VTable0x2c(TRUE, FALSE);
	p_unk0x04->VTable0x34(FALSE);
	p_unk0x04->VTable0x2c(FALSE, FALSE);

	if (m_unk0x0b4) {
		m_flags0x100 |= c_flags0x100Bit2;
	}
	else {
		m_flags0x100 &= ~c_flags0x100Bit2;
	}
}

// FUNCTION: LEGORACERS 0x00414c90
void RaceSessionField0x27d4::Item::Field0x004::FUN_00414c90(GolVec3* p_unk0x04, GolVec3* p_unk0x08)
{
	GolVec3* normalized = &m_unk0x0dc;
	GolMath::NormalizeVector3(*p_unk0x04, normalized);

	GolVec3* perpendicular = &m_unk0x0d0;
	LegoFloat dot = normalized->m_z * p_unk0x08->m_z;
	dot += normalized->m_y * p_unk0x08->m_y;
	dot += normalized->m_x * p_unk0x08->m_x;

	GolVec3 scaled;
	scaled.m_x = dot * normalized->m_x;
	scaled.m_y = normalized->m_y * dot;
	scaled.m_z = dot * normalized->m_z;
	perpendicular->m_x = p_unk0x08->m_x - scaled.m_x;
	perpendicular->m_y = p_unk0x08->m_y - scaled.m_y;
	perpendicular->m_z = p_unk0x08->m_z - scaled.m_z;
	GolMath::NormalizeVector3(*perpendicular, perpendicular);

	m_unk0x0c4.m_x = perpendicular->m_y * normalized->m_z - perpendicular->m_z * normalized->m_y;
	m_unk0x0c4.m_y = perpendicular->m_z * normalized->m_x - normalized->m_z * perpendicular->m_x;
	m_unk0x0c4.m_z = normalized->m_y * perpendicular->m_x - perpendicular->m_y * normalized->m_x;
}

// FUNCTION: LEGORACERS 0x00414d50
void RaceSessionField0x27d4::Item::Field0x004::FUN_00414d50()
{
	LegoFloat scaleX = m_unk0x104;
	scaleX = 0.99000001f / scaleX;
	LegoFloat scaleY = m_unk0x108;
	scaleY = 0.99000001f / scaleY;

	LegoFloat value = m_unk0x0c4.m_x;
	value *= scaleX;
	g_unk0x004c3de8 = value;

	value = m_unk0x0d0.m_x;
	value *= scaleY;
	g_unk0x004c3dec = value;

	value = m_unk0x0c4.m_y;
	value *= scaleX;
	g_unk0x004c3df8 = value;

	value = m_unk0x0d0.m_y;
	value *= scaleY;
	g_unk0x004c3dfc = value;

	value = m_unk0x0c4.m_z;
	value *= scaleX;
	g_unk0x004c3e08 = value;

	value = m_unk0x0d0.m_z;
	value *= scaleY;
	g_unk0x004c3e0c = value;

	LegoFloat dotX = m_unk0x0c4.m_z;
	dotX *= m_unk0x0e8.m_z;
	value = m_unk0x0c4.m_y;
	value *= m_unk0x0e8.m_y;
	dotX += value;
	value = m_unk0x0c4.m_x;
	value *= m_unk0x0e8.m_x;
	dotX += value;
	dotX = -dotX;
	dotX *= scaleX;
	g_unk0x004c3e18 = dotX + 0.5f;

	LegoFloat dotY = m_unk0x0d0.m_z;
	dotY *= m_unk0x0e8.m_z;
	value = m_unk0x0d0.m_y;
	value *= m_unk0x0e8.m_y;
	dotY += value;
	value = m_unk0x0d0.m_x;
	value *= m_unk0x0e8.m_x;
	dotY += value;
	dotY = -dotY;
	dotY *= scaleY;
	g_unk0x004c3e1c = dotY + 0.5f;
}

// FUNCTION: LEGORACERS 0x00414e40
LegoU32 RaceSessionField0x27d4::Item::Field0x004::FUN_00414e40(LegoU32 p_unk0x04, LegoU32 p_unk0x08, LegoU32 p_unk0x0c)
{
	LegoU32 result = p_unk0x0c;
	LegoU32 vertexIndex = p_unk0x08;
	ProjectedVertex* projected = &g_unk0x004c3e28[p_unk0x04];
	LegoU32 end = p_unk0x08 + p_unk0x0c;
	while (vertexIndex < end) {
		m_unk0x114->VTable0x14(vertexIndex, &projected->m_position);

		projected->m_projected.m_x.m_float = g_unk0x004c3de8 * projected->m_position.m_x;
		projected->m_projected.m_y.m_float = g_unk0x004c3dec * projected->m_position.m_x;
		projected->m_projected.m_x.m_float =
			projected->m_position.m_y * g_unk0x004c3df8 + projected->m_projected.m_x.m_float;
		projected->m_projected.m_y.m_float =
			projected->m_position.m_y * g_unk0x004c3dfc + projected->m_projected.m_y.m_float;
		projected->m_projected.m_x.m_float =
			projected->m_position.m_z * g_unk0x004c3e08 + projected->m_projected.m_x.m_float;
		projected->m_projected.m_y.m_float =
			projected->m_position.m_z * g_unk0x004c3e0c + projected->m_projected.m_y.m_float;
		projected->m_projected.m_x.m_float = g_unk0x004c3e18 + projected->m_projected.m_x.m_float;

		LegoU32 projectedXBits = projected->m_projected.m_x.m_bits;
		projected->m_projected.m_y.m_float = g_unk0x004c3e1c + projected->m_projected.m_y.m_float;
		result = ((projectedXBits >> 2) | (projected->m_projected.m_y.m_bits & c_clipYMinMask)) >> 29;

		LegoU32 projectedYBits = projected->m_projected.m_y.m_bits;
		LegoU32 highFlags = (((c_floatOneBits - projectedYBits) & c_clipYMaxMask) |
							 (((c_floatOneBits - projectedXBits) >> 2) & c_clipXMaxMask)) >>
							28;
		projected->m_clipFlags = result | (~(2 * result) & highFlags);

		vertexIndex++;
		projected++;
	}

	return result;
}

// STUB: LEGORACERS 0x00414f40
void RaceSessionField0x27d4::Item::Field0x004::FUN_00414f40(LegoU32 p_unk0x04, LegoU32 p_unk0x08)
{
	LegoU8* indices = m_unk0x118 + 4 * p_unk0x04;
	LegoU8* end = m_unk0x118 + 4 * (p_unk0x04 + p_unk0x08);

	while (indices < end) {
		LegoU32 index0 = indices[0];
		LegoU32 index1 = indices[1];
		LegoU32 index2 = indices[2];
		ProjectedVertex* vertex0 = &g_unk0x004c3e28[index0];
		ProjectedVertex* vertex1 = &g_unk0x004c3e28[index1];
		ProjectedVertex* vertex2 = &g_unk0x004c3e28[index2];
		LegoU32 flags0 = vertex0->m_clipFlags;
		LegoU32 flags1 = vertex1->m_clipFlags;
		LegoU32 flags2 = vertex2->m_clipFlags;

		if (!(flags0 & flags1 & flags2)) {
			LegoFloat cross = (vertex1->m_projected.m_x.m_float - vertex2->m_projected.m_x.m_float) *
								  (vertex0->m_projected.m_y.m_float - vertex2->m_projected.m_y.m_float) -
							  (vertex1->m_projected.m_y.m_float - vertex2->m_projected.m_y.m_float) *
								  (vertex0->m_projected.m_x.m_float - vertex2->m_projected.m_x.m_float);

			if (cross > 0.0f) {
				LegoU32 combinedFlags = flags0 | flags1 | flags2;
				if (combinedFlags) {
					LegoU32 indicesA[16];
					LegoU32 indicesB[16];
					LegoU32 flagsA[16];
					LegoU32 flagsB[16];
					LegoU32* inputIndices = indicesA;
					LegoU32* outputIndices = indicesB;
					LegoU32* inputFlags = flagsA;
					LegoU32* outputFlags = flagsB;
					LegoU32 generatedIndex = c_projectedVertexCount;
					LegoU32 inputCount = 3;
					LegoU32 i;

					inputIndices[0] = index0;
					inputIndices[1] = index1;
					inputIndices[2] = index2;
					inputFlags[0] = flags0;
					inputFlags[1] = flags1;
					inputFlags[2] = flags2;

					if (combinedFlags & c_clipXMinFlag) {
						LegoU32 outputCount = 0;
						LegoU32 previousIndex = inputCount - 1;
						LegoU32 previousOutside = inputFlags[previousIndex] & c_clipXMinFlag;
						for (i = 0; i < inputCount; i++) {
							LegoU32 currentOutside = inputFlags[i] & c_clipXMinFlag;
							if (previousOutside != currentOutside) {
								ProjectedVertex* previous = &g_unk0x004c3e28[inputIndices[previousIndex]];
								ProjectedVertex* current = &g_unk0x004c3e28[inputIndices[i]];
								ProjectedVertex* clipped = &g_unk0x004c3e28[generatedIndex];
								LegoFloat amount =
									previous->m_projected.m_x.m_float /
									(previous->m_projected.m_x.m_float - current->m_projected.m_x.m_float);

								clipped->m_projected.m_x.m_float = 0.0f;
								clipped->m_position.m_x =
									(current->m_position.m_x - previous->m_position.m_x) * amount +
									previous->m_position.m_x;
								clipped->m_position.m_y =
									(current->m_position.m_y - previous->m_position.m_y) * amount +
									previous->m_position.m_y;
								clipped->m_position.m_z =
									(current->m_position.m_z - previous->m_position.m_z) * amount +
									previous->m_position.m_z;
								clipped->m_projected.m_y.m_float =
									(current->m_projected.m_y.m_float - previous->m_projected.m_y.m_float) * amount +
									previous->m_projected.m_y.m_float;

								LegoU32 projectedYBits = clipped->m_projected.m_y.m_bits;
								clipped->m_clipFlags =
									(((projectedYBits >> 1) & 0x40000000) |
									 (~projectedYBits & (c_floatOneBits - projectedYBits) & c_clipYMaxMask)) >>
									28;

								outputIndices[outputCount] = generatedIndex;
								outputFlags[outputCount] = clipped->m_clipFlags;
								generatedIndex++;
								outputCount++;
							}
							if (!currentOutside) {
								outputIndices[outputCount] = inputIndices[i];
								outputFlags[outputCount] = inputFlags[i];
								outputCount++;
							}
							previousIndex = i;
							previousOutside = currentOutside;
						}

						LegoU32* tempIndices = inputIndices;
						inputIndices = outputIndices;
						outputIndices = tempIndices;
						LegoU32* tempFlags = inputFlags;
						inputFlags = outputFlags;
						outputFlags = tempFlags;
						inputCount = outputCount;
					}

					if ((combinedFlags & c_clipXMaxFlag) && inputCount > 0) {
						LegoU32 outputCount = 0;
						LegoU32 previousIndex = inputCount - 1;
						LegoU32 previousOutside = inputFlags[previousIndex] & c_clipXMaxFlag;
						for (i = 0; i < inputCount; i++) {
							LegoU32 currentOutside = inputFlags[i] & c_clipXMaxFlag;
							if (previousOutside != currentOutside) {
								ProjectedVertex* previous = &g_unk0x004c3e28[inputIndices[previousIndex]];
								ProjectedVertex* current = &g_unk0x004c3e28[inputIndices[i]];
								ProjectedVertex* clipped = &g_unk0x004c3e28[generatedIndex];
								LegoFloat amount =
									(1.0f - previous->m_projected.m_x.m_float) /
									(current->m_projected.m_x.m_float - previous->m_projected.m_x.m_float);

								clipped->m_projected.m_x.m_float = 0.99000001f;
								clipped->m_position.m_x =
									(current->m_position.m_x - previous->m_position.m_x) * amount +
									previous->m_position.m_x;
								clipped->m_position.m_y =
									(current->m_position.m_y - previous->m_position.m_y) * amount +
									previous->m_position.m_y;
								clipped->m_position.m_z =
									(current->m_position.m_z - previous->m_position.m_z) * amount +
									previous->m_position.m_z;
								clipped->m_projected.m_y.m_float =
									(current->m_projected.m_y.m_float - previous->m_projected.m_y.m_float) * amount +
									previous->m_projected.m_y.m_float;

								LegoU32 projectedYBits = clipped->m_projected.m_y.m_bits;
								clipped->m_clipFlags =
									(((projectedYBits >> 1) & 0x40000000) |
									 (~projectedYBits & (c_floatOneBits - projectedYBits) & c_clipYMaxMask)) >>
									28;

								outputIndices[outputCount] = generatedIndex;
								outputFlags[outputCount] = clipped->m_clipFlags;
								generatedIndex++;
								outputCount++;
							}
							if (!currentOutside) {
								outputIndices[outputCount] = inputIndices[i];
								outputFlags[outputCount] = inputFlags[i];
								outputCount++;
							}
							previousIndex = i;
							previousOutside = currentOutside;
						}

						LegoU32* tempIndices = inputIndices;
						inputIndices = outputIndices;
						outputIndices = tempIndices;
						LegoU32* tempFlags = inputFlags;
						inputFlags = outputFlags;
						outputFlags = tempFlags;
						inputCount = outputCount;
					}

					if ((combinedFlags & c_clipYMinFlag) && inputCount > 0) {
						LegoU32 outputCount = 0;
						LegoU32 previousIndex = inputCount - 1;
						LegoU32 previousOutside = inputFlags[previousIndex] & c_clipYMinFlag;
						for (i = 0; i < inputCount; i++) {
							LegoU32 currentOutside = inputFlags[i] & c_clipYMinFlag;
							if (previousOutside != currentOutside) {
								ProjectedVertex* previous = &g_unk0x004c3e28[inputIndices[previousIndex]];
								ProjectedVertex* current = &g_unk0x004c3e28[inputIndices[i]];
								ProjectedVertex* clipped = &g_unk0x004c3e28[generatedIndex];
								LegoFloat amount =
									previous->m_projected.m_y.m_float /
									(previous->m_projected.m_y.m_float - current->m_projected.m_y.m_float);

								clipped->m_projected.m_y.m_float = 0.0f;
								clipped->m_clipFlags = 0;
								clipped->m_position.m_x =
									(current->m_position.m_x - previous->m_position.m_x) * amount +
									previous->m_position.m_x;
								clipped->m_position.m_y =
									(current->m_position.m_y - previous->m_position.m_y) * amount +
									previous->m_position.m_y;
								clipped->m_position.m_z =
									(current->m_position.m_z - previous->m_position.m_z) * amount +
									previous->m_position.m_z;
								clipped->m_projected.m_x.m_float =
									(current->m_projected.m_x.m_float - previous->m_projected.m_x.m_float) * amount +
									previous->m_projected.m_x.m_float;

								outputIndices[outputCount] = generatedIndex;
								outputFlags[outputCount] = clipped->m_clipFlags;
								generatedIndex++;
								outputCount++;
							}
							if (!currentOutside) {
								outputIndices[outputCount] = inputIndices[i];
								outputFlags[outputCount] = inputFlags[i];
								outputCount++;
							}
							previousIndex = i;
							previousOutside = currentOutside;
						}

						LegoU32* tempIndices = inputIndices;
						inputIndices = outputIndices;
						outputIndices = tempIndices;
						LegoU32* tempFlags = inputFlags;
						inputFlags = outputFlags;
						outputFlags = tempFlags;
						inputCount = outputCount;
					}

					if ((combinedFlags & c_clipYMaxFlag) && inputCount > 0) {
						LegoU32 outputCount = 0;
						LegoU32 previousIndex = inputCount - 1;
						LegoU32 previousOutside = inputFlags[previousIndex] & c_clipYMaxFlag;
						for (i = 0; i < inputCount; i++) {
							LegoU32 currentOutside = inputFlags[i] & c_clipYMaxFlag;
							if (previousOutside != currentOutside) {
								ProjectedVertex* previous = &g_unk0x004c3e28[inputIndices[previousIndex]];
								ProjectedVertex* current = &g_unk0x004c3e28[inputIndices[i]];
								ProjectedVertex* clipped = &g_unk0x004c3e28[generatedIndex];
								LegoFloat amount =
									(1.0f - previous->m_projected.m_y.m_float) /
									(current->m_projected.m_y.m_float - previous->m_projected.m_y.m_float);

								clipped->m_projected.m_y.m_float = 0.99000001f;
								clipped->m_clipFlags = 0;
								clipped->m_position.m_x =
									(current->m_position.m_x - previous->m_position.m_x) * amount +
									previous->m_position.m_x;
								clipped->m_position.m_y =
									(current->m_position.m_y - previous->m_position.m_y) * amount +
									previous->m_position.m_y;
								clipped->m_position.m_z =
									(current->m_position.m_z - previous->m_position.m_z) * amount +
									previous->m_position.m_z;
								clipped->m_projected.m_x.m_float =
									(current->m_projected.m_x.m_float - previous->m_projected.m_x.m_float) * amount +
									previous->m_projected.m_x.m_float;

								outputIndices[outputCount] = generatedIndex;
								outputFlags[outputCount] = clipped->m_clipFlags;
								generatedIndex++;
								outputCount++;
							}
							if (!currentOutside) {
								outputIndices[outputCount] = inputIndices[i];
								outputFlags[outputCount] = inputFlags[i];
								outputCount++;
							}
							previousIndex = i;
							previousOutside = currentOutside;
						}

						inputIndices = outputIndices;
						inputCount = outputCount;
					}

					if (inputCount > 2) {
						for (i = 1; i < inputCount - 1; i++) {
							FUN_00415810(
								&g_unk0x004c3e28[inputIndices[0]],
								&g_unk0x004c3e28[inputIndices[i]],
								&g_unk0x004c3e28[inputIndices[i + 1]]
							);
						}
					}
				}
				else {
					FUN_00415810(vertex0, vertex1, vertex2);
				}
			}
		}

		indices += 4;
	}
}

// FUNCTION: LEGORACERS 0x00415810
void RaceSessionField0x27d4::Item::Field0x004::FUN_00415810(
	ProjectedVertex* p_unk0x04,
	ProjectedVertex* p_unk0x08,
	ProjectedVertex* p_unk0x0c
)
{
	if (m_unk0x0b4 < m_unk0x0a4) {
		if (m_unk0x0c0 >= 10) {
			FUN_00415980();
			LegoU32 polygonIndex = m_unk0x0b4;
			m_unk0x0a8 = m_unk0x0b0;
			m_unk0x0bc = 0;
			m_unk0x0c0 = 0;
			m_unk0x0ac = polygonIndex;
		}

		m_unk0x008->VTable0x24(m_unk0x0b0, p_unk0x04->m_position);
		m_unk0x008->VTable0x30(m_unk0x0b0, m_unk0x110);
		LegoU32 vertexIndex = m_unk0x0b0;
		m_unk0x0b0 = vertexIndex + 1;
		m_unk0x008->VTable0x28(vertexIndex, p_unk0x04->m_projected.m_vec);

		m_unk0x008->VTable0x24(m_unk0x0b0, p_unk0x08->m_position);
		m_unk0x008->VTable0x30(m_unk0x0b0, m_unk0x110);
		vertexIndex = m_unk0x0b0;
		m_unk0x0b0 = vertexIndex + 1;
		m_unk0x008->VTable0x28(vertexIndex, p_unk0x08->m_projected.m_vec);

		m_unk0x008->VTable0x24(m_unk0x0b0, p_unk0x0c->m_position);
		m_unk0x008->VTable0x30(m_unk0x0b0, m_unk0x110);
		vertexIndex = m_unk0x0b0;
		m_unk0x0b0 = vertexIndex + 1;
		m_unk0x008->VTable0x28(vertexIndex, p_unk0x0c->m_projected.m_vec);

		LegoU32 polygonIndex = m_unk0x0b4;
		LegoU32 polygonCount = m_unk0x0c0;
		LegoU8* indices = m_unk0x00c + 4 * polygonIndex;
		polygonIndex++;
		m_unk0x0b4 = polygonIndex;
		polygonIndex = m_unk0x0bc;
		m_unk0x0c0 = polygonCount + 1;
		indices[0] = static_cast<LegoU8>(polygonIndex);

		LegoU32 batchVertexIndex = m_unk0x0bc + 1;
		m_unk0x0bc = batchVertexIndex;
		indices[1] = static_cast<LegoU8>(batchVertexIndex);
		polygonIndex = m_unk0x0bc;
		polygonIndex++;
		m_unk0x0bc = polygonIndex;
		indices[2] = static_cast<LegoU8>(polygonIndex);
		m_unk0x0bc++;
	}
}

// FUNCTION: LEGORACERS 0x00415980
void RaceSessionField0x27d4::Item::Field0x004::FUN_00415980()
{
	LegoU32 groupIndex = m_unk0x0b8;
	LegoU32 vertexCount = m_unk0x0bc;
	LegoU32 firstVertex = m_unk0x0a8;
	m_unk0x0b8 = groupIndex + 1;

	GolModelBase* model = m_unk0x004;
	model->GetMutableGroups()[groupIndex] = c_commandVertices;
	model->GetMutableGroups()[groupIndex] |= ((vertexCount + 0xffff) << 16) & 0x3f0000;
	model->GetMutableGroups()[groupIndex] |= firstVertex & c_commandVertexMask;
	model->SetDirty(TRUE);

	groupIndex = m_unk0x0b8;
	LegoU32 polygonCount = m_unk0x0c0 & 0x7f;
	LegoU32 firstPolygon = m_unk0x0ac & c_commandVertexMask;
	m_unk0x0b8 = groupIndex + 1;

	model = m_unk0x004;
	model->GetMutableGroups()[groupIndex] = c_commandPolygon;
	model->GetMutableGroups()[groupIndex] |= polygonCount << 16;
	model->GetMutableGroups()[groupIndex] |= firstPolygon;
	model->SetDirty(TRUE);
}

// FUNCTION: LEGORACERS 0x00415a60
GolVec3* RaceSessionField0x27d4::Item::Field0x004::FUN_00415a60()
{
	LegoFloat scratch[13];

	LegoFloat v1 = m_unk0x104 * 0.5f;
	scratch[0] = m_unk0x108 * 0.5f;
	GolVec3* result = &m_unk0x0e8;
	scratch[4] = v1 * m_unk0x0c4.m_x;
	scratch[5] = m_unk0x0c4.m_y;
	scratch[5] *= v1;
	LegoFloat v3 = v1 * m_unk0x0c4.m_z;
	LegoFloat v4 = scratch[0] * m_unk0x0d0.m_x;
	scratch[8] = m_unk0x0d0.m_y;
	scratch[8] *= scratch[0];
	scratch[9] = m_unk0x0d0.m_z;
	scratch[9] *= scratch[0];
	LegoFloat v5 = m_unk0x10c;
	scratch[10] = v5 * m_unk0x0dc.m_x;
	scratch[11] = m_unk0x0dc.m_y;
	scratch[11] *= v5;
	LegoFloat v6 = v5 * m_unk0x0dc.m_z;

	g_unk0x004c47a8[0] = *result;

	scratch[1] = result->m_x - v4;
	scratch[2] = result->m_y - scratch[8];
	scratch[3] = result->m_z - scratch[9];
	scratch[1] = scratch[1] + scratch[10];
	scratch[2] = scratch[2] + scratch[11];
	LegoFloat v7 = v6 + scratch[3];
	g_unk0x004c47a8[1].m_x = scratch[1] - scratch[4];
	g_unk0x004c47a8[1].m_y = scratch[2] - scratch[5];
	g_unk0x004c47a8[1].m_z = v7 - v3;
	g_unk0x004c47a8[2].m_x = scratch[1] + scratch[4];
	g_unk0x004c47a8[2].m_y = scratch[2] + scratch[5];
	g_unk0x004c47a8[2].m_z = v7 + v3;

	LegoFloat v8 = v4 + result->m_x;
	scratch[2] = scratch[8] + result->m_y;
	scratch[3] = scratch[9] + result->m_z;
	g_unk0x004c47a8[3].m_x = v8 - scratch[4];
	g_unk0x004c47a8[3].m_y = scratch[2] - scratch[5];
	g_unk0x004c47a8[3].m_z = scratch[3] - v3;
	g_unk0x004c47a8[4].m_x = v8 + scratch[4];
	g_unk0x004c47a8[4].m_y = scratch[2] + scratch[5];
	g_unk0x004c47a8[4].m_z = scratch[3] + v3;

	return result;
}

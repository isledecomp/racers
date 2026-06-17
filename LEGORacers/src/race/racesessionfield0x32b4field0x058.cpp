#include "camera/golcamerabase.h"
#include "race/racesessionfield0x32b4.h"

// GLOBAL: LEGORACERS 0x004c26f8
GolVec3 g_unk0x004c26f8;

// GLOBAL: LEGORACERS 0x004c2704
undefined4 g_unk0x004c2704;

// GLOBAL: LEGORACERS 0x004c2708
GolVec3 g_unk0x004c2708;

// GLOBAL: LEGORACERS 0x004c2714
undefined4 g_unk0x004c2714;

// GLOBAL: LEGORACERS 0x004c2718
GolVec3 g_unk0x004c2718;

// GLOBAL: LEGORACERS 0x004c2724
undefined4 g_unk0x004c2724;

// GLOBAL: LEGORACERS 0x004c2728
GolVec3 g_unk0x004c2728;

// FUNCTION: LEGORACERS 0x00403fa0
LegoBool32 RaceSessionField0x32b4::Field0x058::FUN_00403fa0(
	GolVec3* p_start,
	GolVec3* p_end,
	Field0x0c* p_record,
	GolVec3* p_hit,
	Field0x10** p_hitRecord,
	LegoFloat* p_amountOut
)
{
	GolVec3* start = p_start;
	GolVec3 delta;
	GolVec3 scaledDelta;
	LegoU32 childIndex;

	m_unk0x30 = *start;
	m_unk0x3c = *p_end;
	m_unk0x54 = p_record;
	m_unk0x58 = p_hit;
	m_unk0x5c = p_hitRecord;
	m_unk0x60 = p_amountOut;

	TraversalEntry* stack = m_unk0x2c;
	stack->m_unk0x0a = 0;
	stack->m_unk0x08 = 0;

	Node* node = m_unk0x08;
	GolVec3* vertices = m_unk0x0c->m_unk0x08;

	for (;;) {
		LegoU32 stage = stack->m_unk0x0a;
		if (stage == 0) {
			Triangle* firstTriangle = &m_unk0x14[node->m_unk0x0c];
			GolVec3* planePoint = &vertices[firstTriangle->m_unk0x00];
			stack->m_unk0x00 = planePoint;

			delta.m_x = start->m_x - planePoint->m_x;
			delta.m_y = start->m_y - planePoint->m_y;
			delta.m_z = start->m_z - planePoint->m_z;

			LegoFloat startDistance = GolCameraBase::FUN_00404680(&node->m_unk0x00, &delta);
			stack->m_unk0x04 = startDistance;

			if (startDistance > 0.0f) {
				childIndex = node->m_unk0x10;
			}
			else {
				childIndex = node->m_unk0x12;
			}

			stack->m_unk0x0a++;
			if (childIndex < c_invalidChildIndex) {
				stack++;
				stack->m_unk0x08 = childIndex;
				stack->m_unk0x0a = 0;
				node = &m_unk0x08[childIndex];
			}
		}
		else if (stage == 1) {
			stack->m_unk0x0a++;

			GolVec3* planePoint = stack->m_unk0x00;
			delta.m_x = p_end->m_x - planePoint->m_x;
			delta.m_y = p_end->m_y - planePoint->m_y;
			delta.m_z = p_end->m_z - planePoint->m_z;

			LegoFloat endDistance = GolCameraBase::FUN_00404680(&node->m_unk0x00, &delta);
			LegoFloat startDistance = stack->m_unk0x04;

			if (endDistance <= 0.0f) {
				if (startDistance <= 0.0f) {
					continue;
				}

				m_unk0x48 = startDistance;
				m_unk0x4c = -endDistance;
				childIndex = node->m_unk0x12;
			}
			else {
				if (startDistance > 0.0f) {
					continue;
				}

				m_unk0x48 = -startDistance;
				m_unk0x4c = endDistance;
				childIndex = node->m_unk0x10;
			}

			m_unk0x50 = node;
			g_unk0x004c2728.m_x = m_unk0x3c.m_x - m_unk0x30.m_x;
			g_unk0x004c2728.m_y = m_unk0x3c.m_y - m_unk0x30.m_y;
			g_unk0x004c2728.m_z = m_unk0x3c.m_z - m_unk0x30.m_z;

			LegoFloat amount = m_unk0x48 / (m_unk0x48 + m_unk0x4c);
			GolCameraBase::FUN_004045b0(&g_unk0x004c2728, amount, &scaledDelta);
			GolCameraBase::FUN_00404550(&m_unk0x30, &scaledDelta, m_unk0x58);

			vertices = m_unk0x0c->m_unk0x08;
			node = m_unk0x50;

			Triangle* triangle = &m_unk0x14[node->m_unk0x0c];
			Triangle* end = triangle + node->m_unk0x0e;
			Triangle* candidate = NULL;

			node->FUN_00404660(&g_unk0x004c2718);
			m_unk0x54->m_unk0x24.m_x = g_unk0x004c2718.m_x;
			m_unk0x54->m_unk0x24.m_y = g_unk0x004c2718.m_y;
			m_unk0x54->m_unk0x24.m_z = g_unk0x004c2718.m_z;

			while (triangle < end) {
				m_unk0x54->m_unk0x00 = vertices[triangle->m_unk0x00];
				m_unk0x54->m_unk0x0c = vertices[triangle->m_unk0x02];
				m_unk0x54->m_unk0x18 = vertices[triangle->m_unk0x04];

				if (GolMath::FUN_004497f0(m_unk0x58, m_unk0x54->GetFloatData())) {
					GolCameraBase::FUN_00404580(&m_unk0x54->m_unk0x00, &m_unk0x54->m_unk0x0c, &g_unk0x004c26f8);
					GolCameraBase::FUN_00404580(&m_unk0x54->m_unk0x18, &m_unk0x54->m_unk0x0c, &g_unk0x004c2708);
					GolCameraBase::FUN_00404510(&g_unk0x004c2708, &g_unk0x004c26f8, &g_unk0x004c2718);

					if (GolCameraBase::FUN_004044f0(&g_unk0x004c2718, &g_unk0x004c2728) <= 0.0f) {
						GolMath::NormalizeVector3(g_unk0x004c2718, &g_unk0x004c2718);
						m_unk0x54->m_unk0x24.m_x = g_unk0x004c2718.m_x;
						m_unk0x54->m_unk0x24.m_y = g_unk0x004c2718.m_y;
						m_unk0x54->m_unk0x24.m_z = g_unk0x004c2718.m_z;
						m_unk0x54->m_unk0x30 =
							-(m_unk0x54->m_unk0x00.m_z * g_unk0x004c2718.m_z +
							  m_unk0x54->m_unk0x00.m_y * g_unk0x004c2718.m_y +
							  m_unk0x54->m_unk0x00.m_x * g_unk0x004c2718.m_x);

						if (m_unk0x5c) {
							*m_unk0x5c = m_unk0x24->m_unk0x08[triangle->m_unk0x06];
						}

						if (m_unk0x60) {
							*m_unk0x60 = amount;
							return TRUE;
						}

						goto successReturn;
					}

					candidate = triangle;
				}

				triangle++;
			}

			if (candidate) {
				m_unk0x54->m_unk0x00 = vertices[candidate->m_unk0x00];
				m_unk0x54->m_unk0x0c = vertices[candidate->m_unk0x02];
				m_unk0x54->m_unk0x18 = vertices[candidate->m_unk0x04];

				GolMath::NormalizeVector3(g_unk0x004c2718, &g_unk0x004c2718);
				m_unk0x54->m_unk0x24.m_x = g_unk0x004c2718.m_x;
				m_unk0x54->m_unk0x24.m_y = g_unk0x004c2718.m_y;
				m_unk0x54->m_unk0x24.m_z = g_unk0x004c2718.m_z;
				m_unk0x54->m_unk0x30 =
					-(m_unk0x54->m_unk0x00.m_z * g_unk0x004c2718.m_z + m_unk0x54->m_unk0x00.m_y * g_unk0x004c2718.m_y +
					  m_unk0x54->m_unk0x00.m_x * g_unk0x004c2718.m_x);

				if (m_unk0x5c) {
					*m_unk0x5c = m_unk0x24->m_unk0x08[candidate->m_unk0x06];
				}

				if (m_unk0x60) {
					*m_unk0x60 = amount;
				}

				goto successReturn;
			}

			if (childIndex < c_invalidChildIndex) {
				stack++;
				stack->m_unk0x08 = childIndex;
				stack->m_unk0x0a = 0;
				node = &m_unk0x08[childIndex];
			}

			start = p_start;
		}
		else {
			stack--;
			if (stack < m_unk0x2c) {
				return FALSE;
			}

			node = &m_unk0x08[stack->m_unk0x08];
		}
	}

successReturn:
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00404660
GolVec3* RaceSessionField0x32b4::Field0x058::Node::FUN_00404660(GolVec3* p_dest) const
{
	p_dest->m_x = m_unk0x00.m_x;
	p_dest->m_y = m_unk0x00.m_y;
	p_dest->m_z = m_unk0x00.m_z;

	return p_dest;
}

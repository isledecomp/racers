#include "camera/golscenetransformnode.h"

#include "camera/goltransform.h"
#include "golerror.h"

// FUNCTION: GOLDP 0x100148e0
GolSceneTransformNode::GolSceneTransformNode()
{
	m_unk0x18 = 0;
}
// FUNCTION: GOLDP 0x10014900
GolSceneTransformNode::~GolSceneTransformNode()
{
	Clear();
}

// FUNCTION: GOLDP 0x10014970
void GolSceneTransformNode::Clear()
{
	if (m_unk0x18 != NULL) {
		delete[] m_unk0x18;
		m_unk0x18 = NULL;
	}

	GolSceneNode::Clear();
}

// FUNCTION: GOLDP 0x100149a0
void GolSceneTransformNode::VTable0x0c()
{
	m_unk0x18 = new GolTransform[m_capacity];
	if (m_unk0x18 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x10014a40
GolTransformBase* GolSceneTransformNode::VTable0x18(LegoU32 p_index) const
{
	return &m_unk0x18[p_index];
}

// FUNCTION: GOLDP 0x10014a60
void GolSceneTransformNode::FUN_10014a60(const GolMatrix4& p_m1, const GolMatrix4& p_m2, const GolMatrix4& p_m3)
{
	GolTransform* obj;
	GolTransform* end;

	if (m_unk0x14 != NULL) {
		VTable0x20(p_m2);
		obj = m_unk0x18;
		end = &m_unk0x18[m_capacity];
		for (; obj < end; obj++) {
			GolMath::FUN_1002f3a0(obj->m_unk0x90, p_m3, &obj->m_unk0x50);
		}
	}
	else {
		obj = m_unk0x18;
		end = &m_unk0x18[m_capacity];
		for (; obj < end; obj++) {
			GolTransform* parent = static_cast<GolTransform*>(obj->m_unk0x04);
			if (parent == NULL) {
				GolMath::FUN_1002f3a0(obj->m_unk0x10, p_m1, &obj->m_unk0x50);
			}
			else {
				GolMath::FUN_1002f3a0(obj->m_unk0x10, parent->m_unk0x50, &obj->m_unk0x50);
			}
		}
	}
}

// FUNCTION: GOLDP 0x10014b30
void GolSceneTransformNode::VTable0x24(const GolMatrix34* p_m)
{
	GolMatrix4 m;
	if (p_m != NULL) {
		m.m_m[0][0] = p_m->m_m[0][0];
		m.m_m[0][1] = p_m->m_m[0][1];
		m.m_m[0][2] = p_m->m_m[0][2];
		m.m_m[1][0] = p_m->m_m[1][0];
		m.m_m[1][1] = p_m->m_m[1][1];
		m.m_m[1][2] = p_m->m_m[1][2];
		m.m_m[2][0] = p_m->m_m[2][0];
		m.m_m[2][1] = p_m->m_m[2][1];
		m.m_m[2][2] = p_m->m_m[2][2];
		m.m_m[3][0] = p_m->m_m[3][0];
		m.m_m[3][1] = p_m->m_m[3][1];
		m.m_m[3][2] = p_m->m_m[3][2];
	}
	else {
		m.m_m[0][0] = 1.0f;
		m.m_m[0][1] = 0.0f;
		m.m_m[0][2] = 0.0f;
		m.m_m[1][0] = 0.0f;
		m.m_m[1][1] = 1.0f;
		m.m_m[1][2] = 0.0f;
		m.m_m[2][0] = 0.0f;
		m.m_m[2][1] = 0.0f;
		m.m_m[2][2] = 1.0f;
		m.m_m[3][0] = 0.0f;
		m.m_m[3][1] = 0.0f;
		m.m_m[3][2] = 0.0f;
	}

	m.m_m[0][3] = 0.0f;
	m.m_m[1][3] = 0.0f;
	m.m_m[2][3] = 0.0f;
	m.m_m[3][3] = 1.0f;

	VTable0x20(m);
}

// STUB: GOLDP 0x10014c20
void GolSceneTransformNode::VTable0x20(const GolMatrix4& p_m)
{
	LegoU32 i = 0;

	if (m_unk0x14 == NULL) {
		GolTransform* obj = m_unk0x18;
		GolTransform* end = &m_unk0x18[m_capacity];

		for (; obj < end; obj++) {
			GolTransform* parent = static_cast<GolTransform*>(obj->m_unk0x04);
			if (parent == NULL) {
				GolMath::FUN_1002f450(obj->m_unk0x10, p_m, &obj->m_unk0x90);
			}
			else {
				GolMath::FUN_1002f450(obj->m_unk0x10, parent->m_unk0x90, &obj->m_unk0x90);
			}
		}
		return;
	}

	for (; i < m_capacity; i++) {
		GolTransform* obj = &m_unk0x18[i];
		GolTransform* parent = static_cast<GolTransform*>(obj->m_unk0x04);

		if (m_unk0x14->VTable0x00(i)) {
			GolQuat rotation;
			GolMath::FUN_1002f720(obj->m_unk0x10, &rotation);

			GolVec3 position;
			position.m_x = obj->m_unk0x10.m_m[3][0];
			position.m_y = obj->m_unk0x10.m_m[3][1];
			position.m_z = obj->m_unk0x10.m_m[3][2];

			if (parent != NULL) {
				m_unk0x14->VTable0x04(i, rotation, position, parent->m_unk0x90, &obj->m_unk0x90);
			}
			else {
				m_unk0x14->VTable0x04(i, rotation, position, p_m, &obj->m_unk0x90);
			}
		}
		else {
			if (parent != NULL) {
				GolMath::FUN_1002f450(obj->m_unk0x10, parent->m_unk0x90, &obj->m_unk0x90);
			}
			else {
				GolMath::FUN_1002f450(obj->m_unk0x10, p_m, &obj->m_unk0x90);
			}
		}
	}
}

// FUNCTION: GOLDP 0x10014d70
void GolSceneTransformNode::VTable0x2c(LegoU32 p_index, GolMatrix34* p_dest) const
{
	GolTransform* obj = &m_unk0x18[p_index];
	p_dest->m_m[0][0] = obj->m_unk0x90.m_m[0][0];
	p_dest->m_m[0][1] = obj->m_unk0x90.m_m[0][1];
	p_dest->m_m[0][2] = obj->m_unk0x90.m_m[0][2];
	p_dest->m_m[1][0] = obj->m_unk0x90.m_m[1][0];
	p_dest->m_m[1][1] = obj->m_unk0x90.m_m[1][1];
	p_dest->m_m[1][2] = obj->m_unk0x90.m_m[1][2];
	p_dest->m_m[2][0] = obj->m_unk0x90.m_m[2][0];
	p_dest->m_m[2][1] = obj->m_unk0x90.m_m[2][1];
	p_dest->m_m[2][2] = obj->m_unk0x90.m_m[2][2];
	p_dest->m_m[3][0] = obj->m_unk0x90.m_m[3][0];
	p_dest->m_m[3][1] = obj->m_unk0x90.m_m[3][1];
	p_dest->m_m[3][2] = obj->m_unk0x90.m_m[3][2];
}

// FUNCTION: GOLDP 0x10014e00
LegoU32 GolSceneTransformNode::VTable0x1c(const GolTransformBase& p_obj) const
{
	return &static_cast<const GolTransform&>(p_obj) - m_unk0x18;
}

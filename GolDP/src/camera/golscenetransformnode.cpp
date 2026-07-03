#include "camera/golscenetransformnode.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GolSceneTransformNode, 0x1c)

#include "camera/goltransform.h"
#include "golerror.h"

// FUNCTION: GOLDP 0x100148e0
GolSceneTransformNode::GolSceneTransformNode()
{
	m_transforms = 0;
}
// FUNCTION: GOLDP 0x10014900
GolSceneTransformNode::~GolSceneTransformNode()
{
	Clear();
}

// FUNCTION: GOLDP 0x10014970
void GolSceneTransformNode::Clear()
{
	if (m_transforms != NULL) {
		delete[] m_transforms;
		m_transforms = NULL;
	}

	GolSceneNode::Clear();
}

// FUNCTION: GOLDP 0x100149a0
void GolSceneTransformNode::AllocateTransforms()
{
	m_transforms = new GolTransform[m_capacity];
	if (m_transforms == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x10014a40
GolTransformBase* GolSceneTransformNode::GetTransform(LegoU32 p_index) const
{
	return &m_transforms[p_index];
}

// FUNCTION: GOLDP 0x10014a60
void GolSceneTransformNode::UpdateWorldViewMatrices(
	const GolMatrix4& p_m1,
	const GolMatrix4& p_m2,
	const GolMatrix4& p_m3
)
{
	GolTransform* obj;
	GolTransform* end;

	if (m_composer != NULL) {
		UpdateWorldMatrices(p_m2);
		obj = m_transforms;
		end = &m_transforms[m_capacity];
		for (; obj < end; obj++) {
			GolMath::MultiplyMatrix4(obj->m_worldMatrix, p_m3, &obj->m_worldViewMatrix);
		}
	}
	else {
		obj = m_transforms;
		end = &m_transforms[m_capacity];
		for (; obj < end; obj++) {
			GolTransform* parent = static_cast<GolTransform*>(obj->m_parent);
			if (parent == NULL) {
				GolMath::MultiplyMatrix4(obj->m_matrix, p_m1, &obj->m_worldViewMatrix);
			}
			else {
				GolMath::MultiplyMatrix4(obj->m_matrix, parent->m_worldViewMatrix, &obj->m_worldViewMatrix);
			}
		}
	}
}

// FUNCTION: GOLDP 0x10014b30
void GolSceneTransformNode::UpdateWorldMatricesAffine(const GolMatrix34* p_m)
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

	UpdateWorldMatrices(m);
}

// STUB: GOLDP 0x10014c20
void GolSceneTransformNode::UpdateWorldMatrices(const GolMatrix4& p_m)
{
	LegoU32 i = 0;

	if (m_composer == NULL) {
		GolTransform* obj = m_transforms;
		GolTransform* end = &m_transforms[m_capacity];

		for (; obj < end; obj++) {
			GolTransform* parent = static_cast<GolTransform*>(obj->m_parent);
			if (parent == NULL) {
				GolMath::MultiplyMatrix4Affine(obj->m_matrix, p_m, &obj->m_worldMatrix);
			}
			else {
				GolMath::MultiplyMatrix4Affine(obj->m_matrix, parent->m_worldMatrix, &obj->m_worldMatrix);
			}
		}
		return;
	}

	for (; i < m_capacity; i++) {
		GolTransform* obj = &m_transforms[i];
		GolTransform* parent = static_cast<GolTransform*>(obj->m_parent);

		if (m_composer->HasOverride(i)) {
			GolQuat rotation;
			GolMath::Matrix4ToQuat(obj->m_matrix, &rotation);

			GolVec3 position;
			position.m_x = obj->m_matrix.m_m[3][0];
			position.m_y = obj->m_matrix.m_m[3][1];
			position.m_z = obj->m_matrix.m_m[3][2];

			if (parent != NULL) {
				m_composer->Compose(i, rotation, position, parent->m_worldMatrix, &obj->m_worldMatrix);
			}
			else {
				m_composer->Compose(i, rotation, position, p_m, &obj->m_worldMatrix);
			}
		}
		else {
			if (parent != NULL) {
				GolMath::MultiplyMatrix4Affine(obj->m_matrix, parent->m_worldMatrix, &obj->m_worldMatrix);
			}
			else {
				GolMath::MultiplyMatrix4Affine(obj->m_matrix, p_m, &obj->m_worldMatrix);
			}
		}
	}
}

// FUNCTION: GOLDP 0x10014d70
void GolSceneTransformNode::GetWorldMatrix(LegoU32 p_index, GolMatrix34* p_dest) const
{
	GolTransform* obj = &m_transforms[p_index];
	p_dest->m_m[0][0] = obj->m_worldMatrix.m_m[0][0];
	p_dest->m_m[0][1] = obj->m_worldMatrix.m_m[0][1];
	p_dest->m_m[0][2] = obj->m_worldMatrix.m_m[0][2];
	p_dest->m_m[1][0] = obj->m_worldMatrix.m_m[1][0];
	p_dest->m_m[1][1] = obj->m_worldMatrix.m_m[1][1];
	p_dest->m_m[1][2] = obj->m_worldMatrix.m_m[1][2];
	p_dest->m_m[2][0] = obj->m_worldMatrix.m_m[2][0];
	p_dest->m_m[2][1] = obj->m_worldMatrix.m_m[2][1];
	p_dest->m_m[2][2] = obj->m_worldMatrix.m_m[2][2];
	p_dest->m_m[3][0] = obj->m_worldMatrix.m_m[3][0];
	p_dest->m_m[3][1] = obj->m_worldMatrix.m_m[3][1];
	p_dest->m_m[3][2] = obj->m_worldMatrix.m_m[3][2];
}

// FUNCTION: GOLDP 0x10014e00
LegoU32 GolSceneTransformNode::IndexOf(const GolTransformBase& p_obj) const
{
	return &static_cast<const GolTransform&>(p_obj) - m_transforms;
}

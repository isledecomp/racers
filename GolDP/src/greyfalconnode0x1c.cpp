#include "../include/greyfalconnode0x1c.h"

#include "golerror.h"
#include "jadeorbit0xd0.h"

// FUNCTION: GOLDP 0x100148e0
GreyFalconNode0x1c::GreyFalconNode0x1c()
{
	m_unk0x18 = 0;
}
// FUNCTION: GOLDP 0x10014900
GreyFalconNode0x1c::~GreyFalconNode0x1c()
{
	Clear();
}

// FUNCTION: GOLDP 0x10014970
void GreyFalconNode0x1c::Clear()
{
	if (m_unk0x18 != NULL) {
		delete[] m_unk0x18;
		m_unk0x18 = NULL;
	}

	WhiteFalconNode0x18::Clear();
}

// FUNCTION: GOLDP 0x100149a0
void GreyFalconNode0x1c::VTable0x0c()
{
	m_unk0x18 = new JadeOrbit0xd0[m_capacity];
	if (m_unk0x18 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x10014a40
JadeOrbitBase0x10* GreyFalconNode0x1c::VTable0x18(LegoU32 p_index) const
{
	return &m_unk0x18[p_index];
}

// FUNCTION: GOLDP 0x10014a60
void GreyFalconNode0x1c::FUN_10014a60(const GolMatrix4& p_m1, const GolMatrix4& p_m2, const GolMatrix4& p_m3)
{
	JadeOrbit0xd0* obj;
	JadeOrbit0xd0* end;

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
			JadeOrbit0xd0* parent = static_cast<JadeOrbit0xd0*>(obj->m_unk0x04);
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
void GreyFalconNode0x1c::VTable0x24(const GolMatrix34* p_m)
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
void GreyFalconNode0x1c::VTable0x20(const GolMatrix4& p_m)
{
	if (m_unk0x14 == NULL) {
		JadeOrbit0xd0* obj;
		JadeOrbit0xd0* end;

		obj = m_unk0x18;
		end = m_unk0x18 + m_capacity;

		for (; obj < end; obj++) {
			if (obj->m_unk0x04 != NULL) {
				GolMath::FUN_1002f450(
					obj->m_unk0x10,
					static_cast<JadeOrbit0xd0*>(obj->m_unk0x04)->m_unk0x90,
					&obj->m_unk0x90
				);
			}
			else {
				GolMath::FUN_1002f450(obj->m_unk0x10, p_m, &obj->m_unk0x90);
			}
		}
	}
	else {
		LegoU32 i;
		for (i = 0; i < m_unk0x14; i++) {
			// TODO
			STUB(0x10014c20);
#if 0
		JadeOrbit0xd0* obj = &m_unk0x18[i];
		GolQuat quat;
		if (m_unk0x14->VTable0x00(i)) {
				GolMath::FUN_1002f720(obj->m_unk0x10, &quat);
				GolVec3 v3;
				v3.m_x = obj->m_unk0x10.m_m[3][0];
				v3.m_y = obj->m_unk0x10.m_m[3][1];
				v3.m_z = obj->m_unk0x10.m_m[3][2];
				if (obj->m_unk0x04 != NULL) {
					m_unk0x14->VTable0x04(i, quat, v3, static_cast<JadeOrbit0xd0*>(obj->m_unk0x04)->m_unk0x90, &obj->m_unk0x90);
				} else {
					m_unk0x14->VTable0x04(i, quat, v3, p_m, &obj->m_unk0x90);
				}
			} else {
				if (obj->m_unk0x04 != NULL) {
					GolMath::FUN_1002f450(obj->m_unk0x10, static_cast<JadeOrbit0xd0*>(obj->m_unk0x04)->m_unk0x90, &obj->m_unk0x90);
				} else {
					GolMath::FUN_1002f450(obj->m_unk0x10, p_m, &obj->m_unk0x90);
				}
			}
#endif
		}
	}
}

// FUNCTION: GOLDP 0x10014d70
void GreyFalconNode0x1c::VTable0x2c(LegoU32 p_index, GolMatrix34* p_dest) const
{
	JadeOrbit0xd0* obj = &m_unk0x18[p_index];
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
LegoU32 GreyFalconNode0x1c::VTable0x1c(const JadeOrbitBase0x10& p_obj) const
{
	return &static_cast<const JadeOrbit0xd0&>(p_obj) - m_unk0x18;
}

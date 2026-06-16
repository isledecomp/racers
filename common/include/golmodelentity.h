#ifndef GOLMODELENTITY_H
#define GOLMODELENTITY_H

#include "compat.h"
#include "decomp.h"
#include "golorientedentity.h"

class GolModelBase;
class GolModelMaterialTable;
struct MaterialTable0x0c;
class GolSceneNode;
class GolWorldDatabase;

// VTABLE: GOLDP 0x10057270
// VTABLE: LEGORACERS 0x004af754
// SIZE 0x90
class GolModelEntity : public GolOrientedEntity {
public:
	GolModelEntity();

	void VTable0x00() override;                                                     // vtable+0x00
	void VTable0x10(LegoS32 p_elapsed) override;                                    // vtable+0x10
	void VTable0x14(const GolViewFrustum& p_view, ResultStruct* p_result) override; // vtable+0x14
	void VTable0x1c(GolRenderDevice& p_renderer) override;                          // vtable+0x1c
	LegoBool32 VTable0x20() override;                                               // vtable+0x20
	void VTable0x24(ColorTransform0x20* p_transform) override;                      // vtable+0x24
	void VTable0x28() override;                                                     // vtable+0x28
	virtual void VTable0x4c(LegoU32 p_index);                                       // vtable+0x4c
	virtual void VTable0x50(GolModelBase* p_model, LegoFloat p_modelDistance);      // vtable+0x50
	virtual void VTable0x54();                                                      // vtable+0x54
	virtual GolSceneNode* VTable0x58(undefined4);                                   // vtable+0x58
	virtual void VTable0x5c(undefined4);                                            // vtable+0x5c

	void FUN_10027c50(GolModelBase* p_model, LegoFloat p_modelDistance);
	void FUN_10027cc0(const GolVec3& p_vector, ResultStruct* p_result);
	void FUN_10027e70(GolMatrix4* p_dest, LegoU32 p_index);
	void FUN_10027fe0(LegoU32 p_index, GolVec3* p_destVec, LegoFloat* p_destScalar);
	LegoFloat FUN_00411640() const;
	LegoFloat FUN_00411660() const;
	void FUN_00411680(LegoFloat p_arg);
	void FUN_004116b0(LegoFloat p_arg);
	LegoFloat FUN_004116e0() const;
	LegoFloat FUN_004116f0() const;
	void FUN_00411700(LegoFloat p_arg);
	void FUN_00411730(LegoFloat p_arg);
	GolModelBase* GetModel(LegoU32 p_index) const { return m_models[p_index]; }
	MaterialTable0x0c* GetMaterialTable(LegoU32 p_index) const { return m_materialTables[p_index]; }
	LegoFloat GetModelDistance(LegoU32 p_index) const { return m_modelDistances[p_index]; }
	void SetModelDistance(LegoU32 p_index, LegoFloat p_modelDistance) { m_modelDistances[p_index] = p_modelDistance; }
	LegoFloat GetUnk0x58() const { return m_unk0x58; }
	LegoBool32 HasModel() const { return m_flags & c_flagBit0; }
	void CopyOrientationAndPositionFrom(const GolModelEntity& p_other)
	{
		m_orientation.m_m[0][0] = p_other.m_orientation.m_m[0][0];
		m_orientation.m_m[0][1] = p_other.m_orientation.m_m[0][1];
		m_orientation.m_m[0][2] = p_other.m_orientation.m_m[0][2];
		m_orientation.m_m[1][0] = p_other.m_orientation.m_m[1][0];
		m_orientation.m_m[1][1] = p_other.m_orientation.m_m[1][1];
		m_orientation.m_m[1][2] = p_other.m_orientation.m_m[1][2];
		m_orientation.m_m[2][0] = p_other.m_orientation.m_m[2][0];
		m_orientation.m_m[2][1] = p_other.m_orientation.m_m[2][1];
		m_orientation.m_m[2][2] = p_other.m_orientation.m_m[2][2];
		m_position = p_other.m_position;
	}
	void CopyOrientationAndPositionTo(GolModelEntity* p_dest) const
	{
		p_dest->m_orientation.m_m[0][0] = m_orientation.m_m[0][0];
		p_dest->m_orientation.m_m[0][1] = m_orientation.m_m[0][1];
		p_dest->m_orientation.m_m[0][2] = m_orientation.m_m[0][2];
		p_dest->m_orientation.m_m[1][0] = m_orientation.m_m[1][0];
		p_dest->m_orientation.m_m[1][1] = m_orientation.m_m[1][1];
		p_dest->m_orientation.m_m[1][2] = m_orientation.m_m[1][2];
		p_dest->m_orientation.m_m[2][0] = m_orientation.m_m[2][0];
		p_dest->m_orientation.m_m[2][1] = m_orientation.m_m[2][1];
		p_dest->m_orientation.m_m[2][2] = m_orientation.m_m[2][2];
		p_dest->m_position = m_position;
		p_dest->m_radius = -1.0f;
	}
	void InvalidateRadius() { m_radius = -1.0f; }
	void SetUnk0x58AndInvalidateRadius(LegoFloat p_unk0x58)
	{
		m_radius = -1.0f;
		m_unk0x58 = p_unk0x58;
	}
	MaterialTable0x0c* GetPrimaryMaterialTable() const { return m_materialTables[0]; }
	void SetPrimaryMaterialTable(MaterialTable0x0c* p_materialTable) { m_materialTables[0] = p_materialTable; }

protected:
	friend class GolWorldDatabase;

	enum {
		c_flagBit0 = 1 << 0,
		c_flagBit1 = 1 << 1,
		c_flagBit2 = 1 << 2,
		c_flagBit3 = 1 << 3,
	};

	LegoFloat m_unk0x58;                    // 0x58
	LegoU32 m_flags;                        // 0x5c
	LegoU16 m_unk0x60;                      // 0x60
	LegoU16 m_unk0x62;                      // 0x62
	LegoS32 m_unk0x64;                      // 0x64
	LegoS32 m_unk0x68;                      // 0x68
	MaterialTable0x0c* m_materialTables[3]; // 0x6c
	GolModelBase* m_models[3];              // 0x78
	LegoFloat m_modelDistances[3];          // 0x84
};

#endif // GOLMODELENTITY_H

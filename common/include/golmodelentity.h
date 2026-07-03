#ifndef GOLMODELENTITY_H
#define GOLMODELENTITY_H

#include "compat.h"
#include "decomp.h"
#include "golorientedentity.h"

class GolModelBase;
class GolModelMaterialTable;
struct MaterialTable;
class GolSceneNode;
class GolWorldDatabase;

// VTABLE: GOLDP 0x10057270
// VTABLE: LEGORACERS 0x004af754
// SIZE 0x90
class GolModelEntity : public GolOrientedEntity {
public:
	GolModelEntity();

	void UpdateBounds() override;                                                          // vtable+0x00
	void Update(LegoS32 p_elapsed) override;                                               // vtable+0x10
	void ComputeVisibility(const GolViewFrustum& p_view, ResultStruct* p_result) override; // vtable+0x14
	void Draw(GolRenderDevice& p_renderer) override;                                       // vtable+0x1c
	LegoBool32 GetKind() override;                                                         // vtable+0x20
	void ApplyColorTransform(ColorTransform* p_transform) override;                        // vtable+0x24
	void ClearColorTransform() override;                                                   // vtable+0x28
	virtual void ComputeBoundsFromModel(LegoU32 p_index);                                  // vtable+0x4c
	virtual void SetPrimaryModel(GolModelBase* p_model, LegoFloat p_modelDistance);        // vtable+0x50
	virtual void ResetModelState();                                                        // vtable+0x54
	virtual GolSceneNode* GetSceneNode(undefined4);                                        // vtable+0x58
	virtual void ApplyPartAnimation(undefined4);                                           // vtable+0x5c

	void AddModel(GolModelBase* p_model, LegoFloat p_modelDistance);
	void SelectLod(const GolVec3& p_vector, ResultStruct* p_result);
	void BuildModelMatrix(GolMatrix4* p_dest, LegoU32 p_index);
	void GetModelBounds(LegoU32 p_index, GolVec3* p_destVec, LegoFloat* p_destScalar);
	LegoFloat GetTextureScrollU() const;
	LegoFloat GetTextureScrollV() const;
	void SetTextureScrollU(LegoFloat p_arg);
	void SetTextureScrollV(LegoFloat p_arg);
	LegoFloat GetTextureScrollSpeedU() const;
	LegoFloat GetTextureScrollSpeedV() const;
	void SetTextureScrollSpeedU(LegoFloat p_arg);
	void SetTextureScrollSpeedV(LegoFloat p_arg);
	GolModelBase* GetModel(LegoU32 p_index) const { return m_models[p_index]; }
	MaterialTable* GetMaterialTable(LegoU32 p_index) const { return m_materialTables[p_index]; }
	LegoFloat GetModelDistance(LegoU32 p_index) const { return m_modelDistances[p_index]; }
	void SetModelDistance(LegoU32 p_index, LegoFloat p_modelDistance) { m_modelDistances[p_index] = p_modelDistance; }
	void ClearModelDistances()
	{
		for (LegoS32 i = 0; i < 3; i++) {
			m_modelDistances[i] = 0.0f;
		}
	}
	void CopyModelDistancesFrom(const GolVec3& p_modelDistances)
	{
		const LegoFloat* modelDistances = &p_modelDistances.m_x;
		for (LegoS32 i = 0; i < 3; i++) {
			m_modelDistances[i] = modelDistances[i];
		}
	}
	void CopyModelDistancesTo(GolVec3* p_modelDistances) const
	{
		LegoFloat* modelDistances = &p_modelDistances->m_x;
		for (LegoS32 i = 0; i < 3; i++) {
			modelDistances[i] = m_modelDistances[i];
		}
	}
	LegoFloat GetScale() const { return m_scale; }
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
	void SetScaleThenInvalidateRadius(LegoFloat p_scale)
	{
		m_scale = p_scale;
		m_radius = -1.0f;
	}
	void SetScaleAndInvalidateRadius(LegoFloat p_scale)
	{
		m_radius = -1.0f;
		m_scale = p_scale;
	}
	MaterialTable* GetPrimaryMaterialTable() const { return m_materialTables[0]; }
	void SetPrimaryMaterialTable(MaterialTable* p_materialTable) { m_materialTables[0] = p_materialTable; }
	void EnableFlagBit1() { m_flags |= c_flagBit1; }

protected:
	friend class GolWorldDatabase;

	enum {
		c_flagBit0 = 1 << 0,
		c_flagBit1 = 1 << 1,
		c_flagBit2 = 1 << 2,
		c_flagBit3 = 1 << 3,
	};

	LegoFloat m_scale;                  // 0x58
	LegoU32 m_flags;                    // 0x5c
	LegoU16 m_textureScrollU;           // 0x60
	LegoU16 m_textureScrollV;           // 0x62
	LegoS32 m_textureScrollSpeedU;      // 0x64
	LegoS32 m_textureScrollSpeedV;      // 0x68
	MaterialTable* m_materialTables[3]; // 0x6c
	GolModelBase* m_models[3];          // 0x78
	LegoFloat m_modelDistances[3];      // 0x84
};

#endif // GOLMODELENTITY_H

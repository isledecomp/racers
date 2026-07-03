#ifndef GOLWORLDENTITYGROUP_H
#define GOLWORLDENTITYGROUP_H

#include "compat.h"
#include "golworldentity.h"

// VTABLE: LEGORACERS 0x004af81c
// SIZE 0x38
class GolWorldEntityGroup : public GolWorldEntity {
public:
	GolWorldEntityGroup();
	virtual ~GolWorldEntityGroup(); // vtable+0x4c

	void UpdateBounds() override;                                                  // vtable+0x00
	void GetPosition(GolVec3* p_center) const override;                            // vtable+0x04
	void SetPosition(const GolVec3& p_center) override;                            // vtable+0x08
	void Update(LegoS32 p_elapsed) override;                                       // vtable+0x10
	void Draw(GolRenderDevice& p_renderer) override;                               // vtable+0x1c
	void ApplyColorTransform(ColorTransform* p_transform) override;                // vtable+0x24
	void ClearColorTransform() override;                                           // vtable+0x28
	void LocalToWorld(const GolVec3& p_add, GolVec3* p_dest) const override;       // vtable+0x2c
	void WorldToLocal(const GolVec3& p_src, GolVec3* p_dest) const override;       // vtable+0x30
	void RotateToWorld(const GolVec3& p_src, GolVec3* p_dest) override;            // vtable+0x34
	void RotateToLocal(const GolVec3& p_src, GolVec3* p_dest) const override;      // vtable+0x38
	void SetDirectionUp(const GolVec3& p_direction, const GolVec3& p_up) override; // vtable+0x40
	void CopyOrientation(GolMatrix3* p_dest) const override;                       // vtable+0x44
	void GetAxes(GolVec3* p_right, GolVec3* p_forward) const override;             // vtable+0x48

	void Allocate(LegoU32 p_capacity);
	void Destroy();
	void AddEntity(GolWorldEntity* p_entity);

	// SYNTHETIC: LEGORACERS 0x00411e00
	// GolWorldEntityGroup::`scalar deleting destructor'

protected:
	LegoU32 m_capacity;          // 0x28
	LegoFloat m_inverseCount;    // 0x2c
	LegoS32 m_count;             // 0x30
	GolWorldEntity** m_entities; // 0x34
};

#endif // GOLWORLDENTITYGROUP_H

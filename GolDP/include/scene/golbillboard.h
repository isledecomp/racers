#ifndef GOLBILLBOARD_H
#define GOLBILLBOARD_H

#include "compat.h"
#include "golworldentity.h"
#include "material/materialtable.h"

#include <d3d.h>

class GolD3DRenderDevice;
class GolRenderDevice;
class GolMaterial;

typedef void(__cdecl* GolBillboardInitializerFunction)();
extern GolBillboardInitializerFunction g_billboardTexCoordInit;

// VTABLE: GOLDP 0x10057500
// SIZE 0x4c
class GolBillboard : public GolWorldEntity {
public:
	enum {
		c_flagAxisLocked = 1 << 1,
		c_flagMaterialAssignment = 1 << 2,
	};

#ifdef BUILDING_LEGORACERS
	typedef LegoU32 VTable0x4cReturn;
#else
	typedef void VTable0x4cReturn;
#endif

	// SIZE 0x0c
	struct ManagedMaterialTable : public MaterialTable {
		ManagedMaterialTable();
		~ManagedMaterialTable();

		void Initialize(GolRenderDevice* p_renderer, LegoU32 p_count);
		void Clear();
	};

	GolBillboard();
	static void InitializeTexCoords();

	// FUNCTION: GOLDP 0x100156c0
	void SetPosition(const GolVec3& p_v) override { GolWorldEntity::SetPosition(p_v); } // vtable+0x08

	void ComputeVisibility(const GolViewFrustum& p_view, ResultStruct* p_result) override; // vtable+0x14
	void Draw(GolRenderDevice&) override;                                                  // vtable+0x1c
	LegoBool32 GetKind() override;                                                         // vtable+0x20
	virtual VTable0x4cReturn Configure(
		GolMaterial* p_material,
		LegoFloat p_width,
		LegoFloat p_height,
		LegoFloat p_maxDistanceSquared
	);                              // vtable+0x4c
	virtual void SetPrimaryModel(); // vtable+0x50

	LegoBool32 BuildModelMatrix(const GolVec3* p_right, const GolVec3* p_forward, GolMatrix4* p_matrix);
	void DrawQuad(GolD3DRenderDevice* p_renderer);
	void SetBoundsRadius(LegoFloat p_arg1);
	VTable0x4cReturn ConfigureFromMaterialTable(
		MaterialTable* p_container,
		LegoS32 p_index,
		LegoFloat p_width,
		LegoFloat p_height,
		LegoFloat p_maxDistanceSquared
	);
	void TestVisibility(const GolVec3& p_cameraPosition, LegoBool32* p_visibility);
	GolMaterial* ResolveMaterial();
	MaterialTable* GetMaterialTable() const { return m_materialTable; }
	LegoU16 GetFlags() const { return m_flags; }
	void SetWidth(LegoFloat p_width) { m_width = p_width; }
	void SetHeight(LegoFloat p_height) { m_height = p_height; }
	void EnableAxisLock() { m_flags |= c_flagAxisLocked; }
	void SetAxis(const GolVec3& p_axis) { m_axis = p_axis; }

private:
	static GolVec3 g_billboardPositions[4];
	static GolVec2 g_billboardTexCoords[4];
	static LegoU32 g_billboardColors[4];
	static LegoU8 g_billboardTriangleIndices[8];

	GolMaterial* m_material;        // 0x28
	MaterialTable* m_materialTable; // 0x2c
	GolVec3 m_axis;                 // 0x30
	LegoFloat m_width;              // 0x3c
	LegoFloat m_height;             // 0x40
	LegoFloat m_maxDistanceSquared; // 0x44
	LegoU16 m_flags;                // 0x48
	LegoU16 m_materialIndex;        // 0x4a
};

#endif // GOLBILLBOARD_H

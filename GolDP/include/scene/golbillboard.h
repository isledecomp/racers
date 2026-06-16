#ifndef GOLBILLBOARD_H
#define GOLBILLBOARD_H

#include "compat.h"
#include "golworldentity.h"
#include "material/materialtable0x0c.h"

#include <d3d.h>

class GolD3DRenderDevice;
class GolRenderDevice;
class DuskwindBananaRelic0x24;

// VTABLE: GOLDP 0x10057500
// SIZE 0x4c
class GolBillboard : public GolWorldEntity {
public:
	enum {
		c_flagBit1 = 1 << 1,
		c_flagBit2 = 1 << 2,
	};

	// SIZE 0x0c
	struct Field0x2c : public MaterialTable0x0c {
		Field0x2c();
		~Field0x2c();

		void Initialize(GolRenderDevice* p_renderer, LegoU32 p_count);
		void Clear();
	};

	GolBillboard();

	// FUNCTION: GOLDP 0x100156c0
	void VTable0x08(const GolVec3& p_v) override { GolWorldEntity::VTable0x08(p_v); } // vtable+0x08

	void VTable0x14(const GolViewFrustum& p_view, ResultStruct* p_result) override; // vtable+0x14
	void VTable0x1c(GolRenderDevice&) override;                                     // vtable+0x1c
	LegoBool32 VTable0x20() override;                                               // vtable+0x20
	virtual void VTable0x4c(
		DuskwindBananaRelic0x24* p_position,
		LegoFloat p_width,
		LegoFloat p_height,
		LegoFloat p_maxDistanceSquared
	);                         // vtable+0x4c
	virtual void VTable0x50(); // vtable+0x50

	LegoBool32 FUN_10014e50(const GolVec3* p_arg1, const GolVec3* p_arg2, GolMatrix4* p_matrix);
	void FUN_10014ff0(GolD3DRenderDevice* p_renderer);
	void FUN_10026fa0(LegoFloat p_arg1);
	void FUN_10029e90(
		Field0x2c* p_container,
		LegoS32 p_index,
		LegoFloat p_width,
		LegoFloat p_height,
		LegoFloat p_maxDistanceSquared
	);
	void FUN_10029fa0(const GolVec3& p_arg1, LegoBool32* p_result);
	DuskwindBananaRelic0x24* FUN_1002a020();
	Field0x2c* GetPositionContainer() const { return m_positionContainer; }
	LegoU16 GetFlags() const { return m_flags; }
	void SetWidth(LegoFloat p_width) { m_width = p_width; }
	void SetHeight(LegoFloat p_height) { m_height = p_height; }

private:
	static GolVec3 g_billboardPositions[4];
	static GolVec2 g_billboardTexCoords[4];
	static LegoU32 g_billboardColors[4];
	static LegoU8 g_billboardTriangleIndices[8];

	DuskwindBananaRelic0x24* m_position; // 0x28
	Field0x2c* m_positionContainer;      // 0x2c
	GolVec3 m_unk0x30;                   // 0x30
	LegoFloat m_width;                   // 0x3c
	LegoFloat m_height;                  // 0x40
	LegoFloat m_maxDistanceSquared;      // 0x44
	LegoU16 m_flags;                     // 0x48
	LegoU16 m_positionIndex;             // 0x4a
};

#endif // GOLBILLBOARD_H

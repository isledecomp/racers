#ifndef RACERBILLBOARDRENDERSTATE0X33C_H
#define RACERBILLBOARDRENDERSTATE0X33C_H

#include "compat.h"
#include "decomp.h"
#include "render/gold3drenderstate.h"
#include "surface/color.h"

class GolD3DRenderDevice;
class GolModelEntity;
class GoldDune0x38;

// VTABLE: LEGORACERS 0x004af574
// SIZE 0x33c
class RacerBillboardRenderState0x33c : public GolD3DRenderState {
public:
	typedef GolD3DRenderState::DrawCommand DrawCommand;
	typedef GolD3DRenderState::CommandVertex CommandVertex;
	typedef GolD3DRenderState::MaterialCommand MaterialCommand;

	RacerBillboardRenderState0x33c();
	virtual ~RacerBillboardRenderState0x33c(); // vtable+0x14

	void VTable0x00(
		GolD3DRenderDevice* p_renderer,
		GolModelEntity* p_model,
		LegoU32 p_lodIndex
	) override; // vtable+0x00
	void VTable0x04(
		GolD3DRenderDevice* p_renderer,
		GolModelEntity* p_model,
		LegoU32 p_lodIndex
	) override;                                             // vtable+0x04
	void VTable0x08(DrawCommand* p_command) override;       // vtable+0x08
	void VTable0x0c(MaterialCommand* p_command) override;   // vtable+0x0c
	undefined4 VTable0x10(DrawCommand* p_command) override; // vtable+0x10

	// SYNTHETIC: LEGORACERS 0x00409790
	// RacerBillboardRenderState0x33c::`scalar deleting destructor'

	void FUN_004097c0(GolD3DRenderDevice* p_renderer, GoldDune0x38* p_texture);
	void FUN_00409830();
	void FUN_00409850(ColorRGBA* p_color);
	void FUN_004098a0(ColorRGBA* p_color);
	void FUN_004098f0(const LegoFloat* p_origin, LegoFloat p_unk0x08, LegoFloat p_unk0x0c, LegoU32 p_flags);
	void FUN_00409970(GolModelEntity* p_model, LegoU32 p_lodIndex);
	void FUN_004099d0();

	// SIZE 0x0c
	struct Field0x038 {
		LegoFloat m_unk0x00; // 0x00
		LegoFloat m_unk0x04; // 0x04
		LegoU32 m_unk0x08;   // 0x08
	};

private:
	typedef void (RacerBillboardRenderState0x33c::*DrawFunction)(Field0x038** p_triangle);

	void FUN_00409b10(Field0x038** p_triangle);
	void FUN_00409f90(Field0x038** p_triangle);
	void FUN_0040a3e0(Field0x038** p_triangle);

	GolD3DRenderDevice* m_renderer;   // 0x004
	GoldDune0x38* m_texture;          // 0x008
	LegoU32 m_unk0x00c;               // 0x00c
	LegoU32 m_unk0x010;               // 0x010
	LegoU32 m_flags0x014;             // 0x014
	LegoFloat m_unk0x018;             // 0x018
	LegoFloat m_unk0x01c;             // 0x01c
	LegoFloat m_unk0x020;             // 0x020
	LegoFloat m_unk0x024;             // 0x024
	LegoFloat m_unk0x028;             // 0x028
	LegoFloat m_unk0x02c;             // 0x02c
	LegoU8* m_unk0x030;               // 0x030
	LegoU32 m_unk0x034;               // 0x034
	Field0x038 m_unk0x038[64];        // 0x038
	DrawFunction m_drawFunction0x338; // 0x338
};

extern RacerBillboardRenderState0x33c g_racerBillboardRenderState0x33c;

#endif // RACERBILLBOARDRENDERSTATE0X33C_H

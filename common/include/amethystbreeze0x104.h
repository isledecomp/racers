#ifndef AMETHYSTBREEZE0X104_H
#define AMETHYSTBREEZE0X104_H

#include "decomp.h"
#include "golmath.h"
#include "render/gold3drenderdevice.h"
#include "surface/color.h"

class DuskwindBananaRelic0x24;
class GdbVertexArray0xc;
class GolModelBase;
class GolModelEntity;

// VTABLE: LEGORACERS 0x004af64c
// SIZE 0x104
class AmethystBreeze0x104 : public GolD3DRenderState {
public:
	typedef GolD3DRenderState::CommandVertex CommandVertex;
	typedef GolD3DRenderState::DrawCommand DrawCommand;
	typedef GolD3DRenderState::MaterialCommand MaterialCommand;

	typedef void (AmethystBreeze0x104::*DrawFunction)(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);

	AmethystBreeze0x104();

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

	void Reset();
	void FUN_0040eb60();
	void FUN_0040eb70(const GolRenderDevice::MaterialColor* p_material);
	void FUN_0040eba0(const GolRenderDevice::Light* p_light);

private:
	void UpdateMaterialCaches();
	void FUN_0040edb0(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void FUN_0040ede0(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void FUN_0040ef10(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void FUN_0040f0a0(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void FUN_0040f280(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void FUN_0040f4c0(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void FUN_0040f760(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void FUN_0040fa50(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);

	static DrawFunction g_drawFunctions[8];

	LegoU32 m_lightCount;                                  // 0x004
	const GolRenderDevice::MaterialColor* m_materialColor; // 0x008
	ColorRGBA m_materialColorValue;                        // 0x00c
	const GolRenderDevice::Light* m_lights[7];             // 0x010
	DuskwindBananaRelic0x24* m_activeMaterial;             // 0x02c
	ColorRGBA m_activeMaterialColor;                       // 0x030
	GolModelBase* m_model;                                 // 0x034
	GdbVertexArray0xc* m_vertexArray;                      // 0x038
	ColorRGBA m_lightColors[7];                            // 0x03c
	FColorRGB m_lightColorProducts[7];                     // 0x058
	GolVec3 m_lightDirections[7];                          // 0x0ac
	DrawFunction m_drawFunction;                           // 0x100
};

#endif // AMETHYSTBREEZE0X104_H

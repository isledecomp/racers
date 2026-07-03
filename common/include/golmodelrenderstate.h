#ifndef GOLMODELRENDERSTATE_H
#define GOLMODELRENDERSTATE_H

#include "decomp.h"
#include "golmath.h"
#include "render/gold3drenderdevice.h"
#include "surface/color.h"

class GolMaterial;
class GdbVertexArray;
class GolModelBase;
class GolModelEntity;

// VTABLE: LEGORACERS 0x004af64c
// SIZE 0x104
class GolModelRenderState : public GolD3DRenderState {
public:
	typedef GolD3DRenderState::CommandVertex CommandVertex;
	typedef GolD3DRenderState::DrawCommand DrawCommand;
	typedef GolD3DRenderState::MaterialCommand MaterialCommand;

	typedef void (GolModelRenderState::*DrawFunction)(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);

	GolModelRenderState();

	void Begin(GolD3DRenderDevice* p_renderer, GolModelEntity* p_model,
			   LegoU32 p_lodIndex) override; // vtable+0x00
	void End(GolD3DRenderDevice* p_renderer, GolModelEntity* p_model,
			 LegoU32 p_lodIndex) override;                             // vtable+0x04
	void ProcessVertices(DrawCommand* p_command) override;             // vtable+0x08
	void ProcessMaterial(MaterialCommand* p_command) override;         // vtable+0x0c
	undefined4 ProcessVerticesPrelit(DrawCommand* p_command) override; // vtable+0x10

	void Reset();
	void ResetLighting();
	void SetAmbientColor(const GolRenderDevice::MaterialColor* p_material);
	void AddLight(const GolRenderDevice::Light* p_light);

private:
	void UpdateMaterialCaches();
	void LightVertices0(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void LightVertices1(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void LightVertices2(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void LightVertices3(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void LightVertices4(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void LightVertices5(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void LightVertices6(
		const CommandVertex* p_vertices,
		LegoU32 p_outputFirst,
		LegoU32 p_firstVertex,
		LegoU32 p_vertexCount
	);
	void LightVertices7(
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
	GolMaterial* m_activeMaterial;                         // 0x02c
	ColorRGBA m_activeMaterialColor;                       // 0x030
	GolModelBase* m_model;                                 // 0x034
	GdbVertexArray* m_vertexArray;                         // 0x038
	ColorRGBA m_lightColors[7];                            // 0x03c
	FColorRGB m_lightColorProducts[7];                     // 0x058
	GolVec3 m_lightDirections[7];                          // 0x0ac
	DrawFunction m_drawFunction;                           // 0x100
};

#endif // GOLMODELRENDERSTATE_H

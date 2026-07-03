#ifndef CARSHADOWRENDERSTATE_H
#define CARSHADOWRENDERSTATE_H

#include "compat.h"
#include "decomp.h"
#include "render/gold3drenderstate.h"
#include "surface/color.h"

class GolD3DRenderDevice;
class GolModelEntity;
class GolTexture;

// VTABLE: LEGORACERS 0x004af574
// SIZE 0x33c
class CarShadowRenderState : public GolD3DRenderState {
public:
	typedef GolD3DRenderState::DrawCommand DrawCommand;
	typedef GolD3DRenderState::CommandVertex CommandVertex;
	typedef GolD3DRenderState::MaterialCommand MaterialCommand;

	CarShadowRenderState();
	virtual ~CarShadowRenderState(); // vtable+0x14

	void Begin(GolD3DRenderDevice* p_renderer, GolModelEntity* p_model,
			   LegoU32 p_lodIndex) override; // vtable+0x00
	void End(GolD3DRenderDevice* p_renderer, GolModelEntity* p_model,
			 LegoU32 p_lodIndex) override;                             // vtable+0x04
	void ProcessVertices(DrawCommand* p_command) override;             // vtable+0x08
	void ProcessMaterial(MaterialCommand* p_command) override;         // vtable+0x0c
	undefined4 ProcessVerticesPrelit(DrawCommand* p_command) override; // vtable+0x10

	// SYNTHETIC: LEGORACERS 0x00409790
	// CarShadowRenderState::`scalar deleting destructor'

	void Initialize(GolD3DRenderDevice* p_renderer, GolTexture* p_texture);
	void Reset();
	void SetFillColor(ColorRGBA* p_color);
	void SetSilhouetteColor(ColorRGBA* p_color);
	void BeginCapture(const LegoFloat* p_origin, LegoFloat p_width, LegoFloat p_height, LegoU32 p_flags);
	void RenderEntity(GolModelEntity* p_model, LegoU32 p_lodIndex);
	void EndCapture();

	// SIZE 0x0c
	struct TransformedVertex {
		LegoFloat m_x;     // 0x00
		LegoFloat m_y;     // 0x04
		LegoU32 m_clipped; // 0x08
	};

private:
	typedef void (CarShadowRenderState::*DrawFunction)(TransformedVertex** p_triangle);

	void DrawTriangles4Bpp(TransformedVertex** p_triangle);
	void DrawTriangles8Bpp(TransformedVertex** p_triangle);
	void DrawTriangles16Bpp(TransformedVertex** p_triangle);

	GolD3DRenderDevice* m_renderer;      // 0x004
	GolTexture* m_texture;               // 0x008
	LegoU32 m_fillValue;                 // 0x00c
	LegoU32 m_silhouetteValue;           // 0x010
	LegoU32 m_flags;                     // 0x014
	LegoFloat m_offsetX;                 // 0x018
	LegoFloat m_offsetY;                 // 0x01c
	LegoFloat m_scaleX;                  // 0x020
	LegoFloat m_scaleY;                  // 0x024
	LegoFloat m_textureWidth;            // 0x028
	LegoFloat m_textureHeight;           // 0x02c
	LegoU8* m_pixels;                    // 0x030
	LegoU32 m_pitch;                     // 0x034
	TransformedVertex m_transformed[64]; // 0x038
	DrawFunction m_drawFunction;         // 0x338
};

extern CarShadowRenderState g_carShadowRenderState;

#endif // CARSHADOWRENDERSTATE_H

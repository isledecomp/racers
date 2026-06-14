#include "util/amethystbreeze0x104.h"

#include "golmodelentity.h"
#include "material/duskwindbananarelic0x24.h"
#include "mesh/golmodelbase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(AmethystBreeze0x104, 0x104)
DECOMP_SIZE_ASSERT(GolD3DRenderState::CommandVertex, 0x20)
DECOMP_SIZE_ASSERT(GolD3DRenderState::MaterialCommand, 0x10)
DECOMP_SIZE_ASSERT(GolD3DRenderState::DrawCommand, 0x1c)

// GLOBAL: LEGORACERS 0x004be2d8
AmethystBreeze0x104::DrawFunction AmethystBreeze0x104::g_drawFunctions[8] = {
	&AmethystBreeze0x104::FUN_0040edb0,
	&AmethystBreeze0x104::FUN_0040ede0,
	&AmethystBreeze0x104::FUN_0040ef10,
	&AmethystBreeze0x104::FUN_0040f0a0,
	&AmethystBreeze0x104::FUN_0040f280,
	&AmethystBreeze0x104::FUN_0040f4c0,
	&AmethystBreeze0x104::FUN_0040f760,
	&AmethystBreeze0x104::FUN_0040fa50,
};

// FUNCTION: LEGORACERS 0x0040ead0
AmethystBreeze0x104::AmethystBreeze0x104()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0040eaf0
void AmethystBreeze0x104::Reset()
{
	m_materialColorValue.m_red = 0xff;
	m_materialColorValue.m_grn = 0xff;
	m_materialColorValue.m_blu = 0xff;
	m_materialColorValue.m_alp = 0xff;
	m_activeMaterialColor.m_red = 0xff;
	m_activeMaterialColor.m_grn = 0xff;
	m_activeMaterialColor.m_blu = 0xff;
	m_activeMaterialColor.m_alp = 0xff;
	m_lightCount = 0;
	m_materialColor = NULL;
	::memset(m_lights, 0, sizeof(m_lights));
	::memset(m_lightColors, 0, sizeof(m_lightColors));
	::memset(m_lightColorProducts, 0, sizeof(m_lightColorProducts));
	::memset(m_lightDirections, 0, sizeof(m_lightDirections));
	m_activeMaterial = NULL;
	m_model = NULL;
	m_vertexArray = NULL;
	m_drawFunction = g_drawFunctions[m_lightCount];
}

// FUNCTION: LEGORACERS 0x0040eb60
void AmethystBreeze0x104::FUN_0040eb60()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0040eb70
void AmethystBreeze0x104::FUN_0040eb70(const GolRenderDevice::MaterialColor* p_material)
{
	m_materialColor = p_material;
	m_materialColorValue = p_material->GetColor();
	m_drawFunction = g_drawFunctions[m_lightCount];
	UpdateMaterialCaches();
}

// FUNCTION: LEGORACERS 0x0040eba0
void AmethystBreeze0x104::FUN_0040eba0(const GolRenderDevice::Light* p_light)
{
	if (m_lightCount < sizeOfArray(m_lights)) {
		m_lightColors[m_lightCount] = p_light->GetColor();
		m_lightDirections[m_lightCount] = p_light->m_direction;
		m_lights[m_lightCount] = p_light;
		m_lightCount++;
		m_drawFunction = g_drawFunctions[m_lightCount];
		UpdateMaterialCaches();
	}
}

// STUB: LEGORACERS 0x0040ec00
void AmethystBreeze0x104::UpdateMaterialCaches()
{
	if (m_activeMaterial == NULL) {
		m_activeMaterialColor.m_red = 0;
		m_activeMaterialColor.m_grn = 0;
		m_activeMaterialColor.m_blu = 0;
		m_activeMaterialColor.m_alp = 0xff;

		for (LegoU32 i = 0; i < m_lightCount; i++) {
			m_lightColorProducts[i].m_red = 0.0f;
			m_lightColorProducts[i].m_grn = 0.0f;
			m_lightColorProducts[i].m_blu = 0.0f;
		}

		return;
	}

	DuskwindBananaRelicColor ambient = m_activeMaterial->GetColor0x10();
	m_activeMaterialColor.m_red = (static_cast<LegoU32>(ambient.m_unk0x0 & 0xff) * m_materialColorValue.m_red) >> 8;
	m_activeMaterialColor.m_grn = (static_cast<LegoU32>(ambient.m_unk0x1 & 0xff) * m_materialColorValue.m_grn) >> 8;
	m_activeMaterialColor.m_blu = (static_cast<LegoU32>(ambient.m_unk0x2 & 0xff) * m_materialColorValue.m_blu) >> 8;
	m_activeMaterialColor.m_alp = ambient.m_unk0x3;

	DuskwindBananaRelicColor diffuse = m_activeMaterial->GetColor0x0c();
	if (m_lightCount > 0) {
		LegoU32 red = diffuse.m_unk0x0 & 0xff;
		LegoU32 grn = diffuse.m_unk0x1 & 0xff;
		LegoU32 blu = diffuse.m_unk0x2 & 0xff;
		ColorRGBA* lightColor = m_lightColors;
		FColorRGB* lightProduct = m_lightColorProducts;

		for (LegoU32 i = 0; i < m_lightCount; i++) {
			LegoS32 product = static_cast<LegoS32>((red * lightColor->m_red) >> 8);
			lightProduct->m_red = static_cast<LegoFloat>(product);

			product = static_cast<LegoS32>((grn * lightColor->m_grn) >> 8);
			lightProduct->m_grn = static_cast<LegoFloat>(product);

			product = static_cast<LegoS32>((blu * lightColor->m_blu) >> 8);
			lightProduct->m_blu = static_cast<LegoFloat>(product);
			lightColor++;
			lightProduct++;
		}
	}
}

// FUNCTION: LEGORACERS 0x0040ed40
void AmethystBreeze0x104::VTable0x00(GolD3DRenderDevice*, GolModelEntity* p_model, LegoU32 p_lodIndex)
{
	m_model = p_model->GetModel(p_lodIndex);
	m_model->VTable0x28(&m_vertexArray);
}

// FUNCTION: LEGORACERS 0x0040ed60
void AmethystBreeze0x104::VTable0x04(GolD3DRenderDevice*, GolModelEntity*, LegoU32)
{
	m_model->VTable0x2c(1, FALSE);
}

// FUNCTION: LEGORACERS 0x0040ed70
void AmethystBreeze0x104::VTable0x08(DrawCommand* p_command)
{
	if (p_command->m_material != m_activeMaterial) {
		m_activeMaterial = p_command->m_material;
		UpdateMaterialCaches();
	}

	(this->*m_drawFunction)(
		p_command->m_vertices,
		p_command->m_outputFirst,
		p_command->m_firstVertex,
		p_command->m_vertexCount
	);
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void AmethystBreeze0x104::VTable0x0c(MaterialCommand*)
{
	// empty
}

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 AmethystBreeze0x104::VTable0x10(DrawCommand*)
{
	return 0;
}

// STUB: LEGORACERS 0x0040edb0
void AmethystBreeze0x104::FUN_0040edb0(const CommandVertex*, LegoU32, LegoU32, LegoU32)
{
	STUB(0x0040edb0);
}

// STUB: LEGORACERS 0x0040ede0
void AmethystBreeze0x104::FUN_0040ede0(const CommandVertex*, LegoU32, LegoU32, LegoU32)
{
	STUB(0x0040ede0);
}

// STUB: LEGORACERS 0x0040ef10
void AmethystBreeze0x104::FUN_0040ef10(const CommandVertex*, LegoU32, LegoU32, LegoU32)
{
	STUB(0x0040ef10);
}

// STUB: LEGORACERS 0x0040f0a0
void AmethystBreeze0x104::FUN_0040f0a0(const CommandVertex*, LegoU32, LegoU32, LegoU32)
{
	STUB(0x0040f0a0);
}

// STUB: LEGORACERS 0x0040f280
void AmethystBreeze0x104::FUN_0040f280(const CommandVertex*, LegoU32, LegoU32, LegoU32)
{
	STUB(0x0040f280);
}

// STUB: LEGORACERS 0x0040f4c0
void AmethystBreeze0x104::FUN_0040f4c0(const CommandVertex*, LegoU32, LegoU32, LegoU32)
{
	STUB(0x0040f4c0);
}

// STUB: LEGORACERS 0x0040f760
void AmethystBreeze0x104::FUN_0040f760(const CommandVertex*, LegoU32, LegoU32, LegoU32)
{
	STUB(0x0040f760);
}

// STUB: LEGORACERS 0x0040fa50
void AmethystBreeze0x104::FUN_0040fa50(const CommandVertex*, LegoU32, LegoU32, LegoU32)
{
	STUB(0x0040fa50);
}

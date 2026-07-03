#include "golmaterial.h"

#include "goltexture.h"
#include "render/golrenderdevice.h"

DECOMP_SIZE_ASSERT(GolMaterial::NameRecord, 0x8)
DECOMP_SIZE_ASSERT(GolMaterial, 0x24)
DECOMP_SIZE_ASSERT(GolMaterialParams, 0x14)

// FUNCTION: GOLDP 0x10025770
GolMaterial::GolMaterial() : m_diffuse(0xff, 0xff, 0xff, 0xff), m_ambient(0xff, 0xff, 0xff, 0xff)
{
	m_userData = NULL;
	m_flags = 0x50a694;
	m_texture = NULL;
	m_alphaRef = 0;
	m_alphaFunc = 0;
	m_srcBlend = 1;
	m_destBlend = 0;
}

// FUNCTION: GOLDP 0x100257d0
GolMaterial::~GolMaterial()
{
}

// FUNCTION: GOLDP 0x100257e0
// FUNCTION: LEGORACERS 0x0040fda0
void GolMaterial::SetParams(GolRenderDevice* p_renderer, const GolMaterialParams& p_params)
{
	m_ambient = p_params.m_ambient;
	m_diffuse = p_params.m_diffuse;
	m_flags = p_params.m_flags;
	m_alphaFunc = p_params.m_alphaFunc;
	m_alphaRef = p_params.m_alphaRef;
	m_srcBlend = p_params.m_srcBlend;
	m_srcBlend = p_params.m_srcBlend;
	m_destBlend = p_params.m_destBlend;
	m_destBlend = p_params.m_destBlend;

	if (m_flags & c_flagBit3) {
		m_texture = p_params.m_texture;
		if (m_texture->GetUnk0x36() & GolTexture::c_unk0x36Bit5) {
			if (p_renderer->GetFlags() & (GolRenderDevice::c_flagBit7 | GolRenderDevice::c_flagBit8)) {
				if ((p_renderer->GetFlags() & GolRenderDevice::c_flagBit7) && !(m_flags & c_flagBit12)) {
					m_srcBlend = 6;
					m_destBlend = 8;
					m_flags &= ~(c_flagBit9 | c_flagBit5 | c_flagBit2);
					m_flags |= c_flagBit8 | c_flagBit4 | c_flagBit1;
				}
				if (p_renderer->GetFlags() & GolRenderDevice::c_flagBit8) {
					m_alphaFunc = 2;
					m_alphaRef = 0;
					m_flags &= ~c_flagBit7;
					m_flags |= c_flagBit6;
				}
			}
		}
	}
	else {
		m_texture = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0040fe50
void GolMaterial::CopyParamsTo(GolMaterialParams* p_params) const
{
	p_params->m_flags = m_flags;
	p_params->m_texture = m_texture;
	p_params->m_ambient = m_ambient;
	p_params->m_diffuse = m_diffuse;
	p_params->m_alphaFunc = m_alphaFunc;
	p_params->m_alphaRef = m_alphaRef;
	p_params->m_srcBlend = m_srcBlend;
	p_params->m_srcBlend = m_srcBlend;
	p_params->m_destBlend = m_destBlend;
	p_params->m_destBlend = m_destBlend;
}

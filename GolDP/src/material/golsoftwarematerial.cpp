#include "material/golsoftwarematerial.h"

#include "golerror.h"
#include "goltexture.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolSoftwareMaterial, 0x30)

// FUNCTION: GOLDP 0x10006280
GolSoftwareMaterial::GolSoftwareMaterial()
{
	m_d3dMaterial = NULL;
	m_materialHandle = 0;
	m_pipelines = NULL;
}

// FUNCTION: GOLDP 0x100062a0
GolSoftwareMaterial::~GolSoftwareMaterial()
{
	Destroy();
}

// FUNCTION: GOLDP 0x10006320
void GolSoftwareMaterial::Create(GolRenderDevice& p_renderer)
{
	if (m_flags & c_flagCreated) {
		Destroy();
	}

	m_flags |= c_flagCreated;
	GolD3DRenderDevice* renderer = static_cast<GolD3DRenderDevice*>(p_renderer.GetDrawState()->m_currentRenderer);

	if (renderer->GetFlags() & GolRenderDevice::c_flagSoftwareRenderer) {
		LegoU32 textureCount;
		if (m_texture != NULL) {
			textureCount = m_texture->GetMipmapCount();
		}
		else {
			textureCount = 1;
		}

		m_pipelines = new GolSoftwareRenderer::RasterizerPipeline[textureCount];
		if (m_pipelines == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		::memset(m_pipelines, 0, textureCount * sizeof(*m_pipelines));
		if (m_texture == NULL) {
			renderer->GetSoftwareRenderer().SetupPipeline(m_pipelines, this, 0);
			UpdateD3DMaterial(renderer);
			return;
		}

		for (LegoU32 i = 0; i < m_texture->GetMipmapCount(); i++) {
			renderer->GetSoftwareRenderer().SetupPipeline(m_pipelines + i, this, i);
		}
	}
	else {
		HRESULT result = renderer->GetDirect3D3()->CreateMaterial(&m_d3dMaterial, NULL);
		if (result != D3D_OK) {
			LegoChar errorMessage[64];
			::sprintf(errorMessage, "Unable to create material\nerrcode = %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}
	}

	UpdateD3DMaterial(renderer);
}

// FUNCTION: GOLDP 0x10006490
void GolSoftwareMaterial::Destroy()
{
	if (m_pipelines != NULL) {
		delete[] m_pipelines;
		m_pipelines = NULL;
	}
	if (m_d3dMaterial != NULL) {
		m_d3dMaterial->Release();
		m_d3dMaterial = NULL;
	}
	m_materialHandle = 0;
	m_flags &= ~c_flagCreated;
}

// FUNCTION: GOLDP 0x100064d0
void GolSoftwareMaterial::UpdateD3DMaterial(GolD3DRenderDevice* p_renderer)
{
	D3DMATERIAL material;
	LegoChar errorMessage[64];

	material.dwSize = sizeof(D3DMATERIAL);
	material.ambient.r = static_cast<LegoFloat>(static_cast<double>(m_ambient.m_red & 0xff) / 255.0);
	material.ambient.g = static_cast<LegoFloat>(static_cast<double>(m_ambient.m_grn & 0xff) / 255.0);
	material.ambient.b = static_cast<LegoFloat>(static_cast<double>(m_ambient.m_blu & 0xff) / 255.0);
	material.ambient.a = static_cast<LegoFloat>(static_cast<double>(m_ambient.m_alp & 0xff) / 255.0);
	material.diffuse.r = static_cast<LegoFloat>(static_cast<double>(m_diffuse.m_red & 0xff) / 255.0);
	material.diffuse.g = static_cast<LegoFloat>(static_cast<double>(m_diffuse.m_grn & 0xff) / 255.0);
	material.diffuse.b = static_cast<LegoFloat>(static_cast<double>(m_diffuse.m_blu & 0xff) / 255.0);
	material.diffuse.a = static_cast<LegoFloat>(static_cast<double>(m_diffuse.m_alp & 0xff) / 255.0);
	material.specular.r = 0.0f;
	material.specular.g = 0.0f;
	material.specular.b = 0.0f;
	material.specular.a = 0.0f;
	material.emissive.r = 0.0f;
	material.emissive.g = 0.0f;
	material.emissive.b = 0.0f;
	material.emissive.a = 0.0f;
	material.power = 0.0f;
	material.hTexture = 0;
	material.dwRampSize = 16;

	if (m_d3dMaterial != NULL) {
		HRESULT result = m_d3dMaterial->SetMaterial(&material);
		if (result != D3D_OK) {
			::sprintf(errorMessage, "Unable to set material\nerrcode = %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		result = m_d3dMaterial->GetHandle(p_renderer->GetDirect3DDevice(), &m_materialHandle);
		if (result != D3D_OK) {
			::sprintf(errorMessage, "Unable to get material handle\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}
	}
}

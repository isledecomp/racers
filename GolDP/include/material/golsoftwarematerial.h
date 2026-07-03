#ifndef GOLSOFTWAREMATERIAL_H
#define GOLSOFTWAREMATERIAL_H

#include "compat.h"
#include "golmaterial.h"
#include "render/golsoftwarerenderer.h"

#include <d3d.h>

class GolRenderDevice;
class GolD3DRenderDevice;

// VTABLE: GOLDP 0x100563c4
// SIZE 0x30
class GolSoftwareMaterial : public GolMaterial {
public:
	GolSoftwareMaterial();
	~GolSoftwareMaterial() override; // vtable+0x00

	void Create(GolRenderDevice& p_renderer);
	GolSoftwareRenderer::RasterizerPipeline* GetPipelines() const { return m_pipelines; }

	// SYNTHETIC: GOLDP 0x10004b00
	// GolSoftwareMaterial::`vector deleting destructor'

	void Destroy();

private:
	void UpdateD3DMaterial(GolD3DRenderDevice* p_renderer);

	LPDIRECT3DMATERIAL3 m_d3dMaterial;                    // 0x24
	D3DMATERIALHANDLE m_materialHandle;                   // 0x28
	GolSoftwareRenderer::RasterizerPipeline* m_pipelines; // 0x2c
};

#endif // GOLSOFTWAREMATERIAL_H

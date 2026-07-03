#ifndef GOLD3DRENDERSTATE_H
#define GOLD3DRENDERSTATE_H

#include "decomp.h"
#include "types.h"

class GolMaterial;
class GolD3DRenderDevice;
class GolModelEntity;

class GolD3DRenderState {
public:
	// SIZE 0x20
	struct CommandVertex {
		LegoFloat m_x; // 0x00
		LegoFloat m_y; // 0x04
		LegoFloat m_z; // 0x08
		LegoFloat m_u; // 0x0c
		LegoFloat m_v; // 0x10
		union {
			struct {
				LegoFloat m_nx; // 0x14
				LegoFloat m_ny; // 0x18
				LegoFloat m_nz; // 0x1c
			};
			struct {
				LegoU32 m_color;      // 0x14
				undefined4 m_unused0; // 0x18
				undefined4 m_unused1; // 0x1c
			};
		};
	};

	// SIZE 0x1c
	struct MaterialCommand {
		GolD3DRenderDevice* m_renderer;  // 0x00
		GolModelEntity* m_model;         // 0x04
		GolMaterial* m_material;         // 0x08
		const CommandVertex* m_vertices; // 0x0c
		LegoU8* m_indices;               // 0x10
		LegoU32 m_firstTriangle;         // 0x14
		LegoU32 m_triangleCount;         // 0x18
	};

	// SIZE 0x1c
	struct DrawCommand {
		GolD3DRenderDevice* m_renderer;  // 0x00
		GolModelEntity* m_model;         // 0x04
		GolMaterial* m_material;         // 0x08
		const CommandVertex* m_vertices; // 0x0c
		LegoU32 m_outputFirst;           // 0x10
		LegoU32 m_firstVertex;           // 0x14
		LegoU32 m_vertexCount;           // 0x18
	};

	virtual void Begin(GolD3DRenderDevice* p_renderer, GolModelEntity* p_model,
					   LegoU32 p_lodIndex) = 0; // vtable+0x00
	virtual void End(GolD3DRenderDevice* p_renderer, GolModelEntity* p_model,
					 LegoU32 p_lodIndex) = 0;                             // vtable+0x04
	virtual void ProcessVertices(DrawCommand* p_command) = 0;             // vtable+0x08
	virtual void ProcessMaterial(MaterialCommand* p_command) = 0;         // vtable+0x0c
	virtual undefined4 ProcessVerticesPrelit(DrawCommand* p_command) = 0; // vtable+0x10
};

#endif // GOLD3DRENDERSTATE_H

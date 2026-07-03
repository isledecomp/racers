#ifndef MABMATERIALFRAME_H
#define MABMATERIALFRAME_H

#include "decomp.h"
#include "types.h"

class GolRenderDevice;
class GolMaterial;

// SIZE 0x8
class MabMaterialFrame {
public:
	MabMaterialFrame();

	void Initialize(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoU32 p_id);
	GolMaterial* GetMaterial() const { return m_material; }
	void SetMaterial(GolMaterial* p_material) { m_material = p_material; }
	LegoU32 GetFrame() const { return m_frame; }

private:
	GolMaterial* m_material; // 0x00
	LegoU32 m_frame;         // 0x04
};

#endif // MABMATERIALFRAME_H

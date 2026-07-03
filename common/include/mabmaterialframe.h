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

	void FUN_10026110(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoU32 p_id);
	GolMaterial* GetMaterial() const { return m_unk0x00; }
	void SetMaterial(GolMaterial* p_material) { m_unk0x00 = p_material; }
	LegoU32 GetFrame() const { return m_unk0x04; }

private:
	GolMaterial* m_unk0x00; // 0x00
	LegoU32 m_unk0x04;      // 0x04
};

#endif // MABMATERIALFRAME_H

#ifndef GLASSSHARD0X3B8_H
#define GLASSSHARD0X3B8_H

#include "compat.h"
#include "decomp.h"
#include "golmodelentity.h"
#include "render/gold3drenderdevice.h"
#include "types.h"
#include "util/opalhaven0xf4.h"

class GolExport;
class GolWorldDatabase;

// VTABLE: LEGORACERS 0x004b01a0
// SIZE 0x3b8
class GlassShard0x3b8 {
public:
	GlassShard0x3b8();
	virtual ~GlassShard0x3b8(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x00422390
	// GlassShard0x3b8::`scalar deleting destructor'

	void Reset();
	void Initialize(GolD3DRenderDevice* p_renderer, GolExport* p_golExport, undefined4 p_unk0x0c, undefined4 p_unk0x10);
	void Shutdown();
	void FUN_004230e0();
	LegoBool32 FUN_004234b0();
	undefined4* GetUnk0x14() { return m_unk0x14; }

private:
	enum {
		c_flag0x3b4Bit0 = 1 << 0,
		c_flag0x3b4Bit3 = 1 << 3,
		c_flag0x3b4Bit4 = 1 << 4,
	};

	GolWorldDatabase* m_unk0x04;         // 0x04
	GolExport* m_golExport;              // 0x08
	undefined4* m_unk0x0c;               // 0x0c
	undefined4* m_unk0x10;               // 0x10
	undefined4* m_unk0x14;               // 0x14
	undefined4* m_unk0x18;               // 0x18
	OpalHaven0xf4 m_unk0x1c;             // 0x1c
	undefined m_unk0x110[0x114 - 0x110]; // 0x110
	OpalHaven0xf4 m_unk0x114;            // 0x114
	undefined m_unk0x208[0x20c - 0x208]; // 0x208
	OpalHaven0xf4 m_unk0x20c;            // 0x20c
	GolModelEntity m_unk0x300;           // 0x300
	GolSceneNode* m_nodes[3];            // 0x390
	LegoS32 m_partIndices[3];            // 0x39c
	CmbModelPart0x34* m_modelParts[3];   // 0x3a8
	LegoU8 m_flags0x3b4;                 // 0x3b4
};

#endif // GLASSSHARD0X3B8_H

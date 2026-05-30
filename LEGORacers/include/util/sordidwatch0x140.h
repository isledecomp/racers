#ifndef SORDIDWATCH0x140_H
#define SORDIDWATCH0x140_H

#include "decomp.h"
#include "types.h"
#include "util/silverhollow0xb8.h"

class GolExport;
class GolD3DRenderDevice;

class SordidWatch0x140 {
public:
	SordidWatch0x140();
	~SordidWatch0x140();

	undefined4 GetWhatever() const { return (LegoU32)m_modelParts[0]; }

	void Reset();

	void FUN_00412430(GolExport* p_golExport, GolD3DRenderDevice* p_renderer, undefined4 p_param3, undefined4 p_param4);

	undefined4 FUN_00412760(GolVec3* p_param1, GolVec3* p_param2, LegoFloat p_param3);
	void FUN_00412840();
	void FUN_00412970();
	GolWorldEntity* FUN_00412a00();

	// LegoU8 GetFlags0xb4() const { return m_flags0xb4; }
	// void SetFlags0xb4(LegoU8 p_flags) { m_flags0xb4 = p_flags; }
	// LegoU32 GetWhatever0xa8() const { return (LegoU32)m_modelParts[0]; }
	// void SetWhatever0xa8(LegoU32 p_flags) { m_modelParts[0] = (CmbModelPart0x34 *)p_flags; }

private:
	undefined4 m_unk0x000;             // 0x000
	undefined4 m_unk0x004;             // 0x000
	undefined4 m_unk0x008;             // 0x000
	undefined4 m_unk0x00c;             // 0x000
	SilverHollow0xb8 m_unk0x010;       // 0x004

	// TODO: This block may be in a new subclass of SilverHollow0xb8
	GolSceneNode* m_nodes[3];                   // 0x90
	LegoS32 m_partIndices[3];                   // 0x9c
	CmbModelPart0x34* m_modelParts[3];          // 0xa8
	union {
		LegoFloat m_unk0xb4;    // 0xb4
		LegoU8 m_flags0xb4;     // 0xb4
	};

	undefined4 m_unk0xc8;              // 0x0c8
	undefined4 m_unk0xcc;              // 0x0cc
	undefined4 m_unk0xd0;              // 0x0d0
	undefined4 m_unk0xd4;              // 0x0d4
	undefined4 m_unk0xd8;              // 0x0d8
	undefined4 m_unk0xdc;              // 0x0dc
	undefined4 m_unk0xe0;              // 0x0e0
	undefined4 m_unk0xe4;              // 0x0e4
	undefined4 m_unk0xe8;              // 0x0e8
	undefined m_unk0xec[0x120 - 0xec]; // 0x0e8
	undefined4 m_unk0x120;             // 0x120
	undefined4 m_unk0x134;             // 0x134
	undefined4 m_unk0x12c;             // 0x12c
	undefined4 m_unk0x130;             // 0x130
	undefined4 m_unk0x124;             // 0x124
	undefined4 m_unk0x128;             // 0x128
	undefined4 m_unk0x138;             // 0x138
	undefined4 m_unk0x13c;             // 0x13c
};

#endif // SORDIDWATCH0x140_H

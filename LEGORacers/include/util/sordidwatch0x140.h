#ifndef SORDIDWATCH0x140_H
#define SORDIDWATCH0x140_H

#include "decomp.h"
#include "golmodelentity.h"
#include "types.h"

class GolExport;
class GolD3DRenderDevice;

class SordidWatch0x140 {
public:
	// VTABLE: LEGORACERS 0x004af8c0
	class SordidWatchInner0x38 : public GolWorldEntity {
	public:
		SordidWatchInner0x38();

		LegoU32 m_unk0x28;
		undefined4 m_unk0x2c;
		undefined4 m_unk0x30;
		SordidWatchInner0x38* m_next;
	};

	SordidWatch0x140();
	~SordidWatch0x140() { Destroy(); }

	void Destroy();

	undefined4 GetUnk0xb8() const { return m_unk0x0b8; }

	void Reset();

	void FUN_00412430(GolExport* p_golExport, GolD3DRenderDevice* p_renderer, undefined4 p_param3, undefined4 p_param4);

	SordidWatchInner0x38* FUN_00412760(GolVec3* p_param1, GolVec3* p_param2, undefined4 p_param3);
	void FUN_00412840();
	void FUN_00412970();
	SordidWatchInner0x38* FUN_00412a00();

private:
	GolExport* m_unk0x000;              // 0x000
	GolModelBase* m_unk0x004;           // 0x004
	undefined4 m_unk0x008;              // 0x008
	undefined4 m_unk0x00c;              // 0x00c
	GolModelEntity m_unk0x010;          // 0x010
	undefined4 m_unk0x0a0;              // 0x0a0
	undefined4 m_unk0x0a4;              // 0x0a4
	undefined4 m_unk0x0a8;              // 0x0a8
	SordidWatchInner0x38* m_unk0x0ac;   // 0x0ac
	SordidWatchInner0x38* m_unk0x0b0;   // 0x0b0
	SordidWatchInner0x38* m_unk0x0b4;   // 0x0b4
	undefined4 m_unk0x0b8;              // 0x0b8
	undefined4 m_unk0x0bc;              // 0x0bc
	undefined4 m_unk0x0c0;              // 0x0c0
	undefined4 m_unk0x0c4;              // 0x0c4
	undefined4 m_unk0x0c8;              // 0x0c8
	undefined4 m_unk0x0cc;              // 0x0cc
	undefined4 m_unk0x0d0;              // 0x0d0
	undefined4 m_unk0x0d4;              // 0x0d4
	undefined4 m_unk0x0d8;              // 0x0d8
	undefined4 m_unk0x0dc;              // 0x0dc
	undefined4 m_unk0x0e0;              // 0x0e0
	undefined4 m_unk0x0e4;              // 0x0e4
	undefined4 m_unk0x0e8;              // 0x0e8
	undefined m_unk0x0ec[0x120 - 0xec]; // 0x0ec
	undefined4 m_unk0x120;              // 0x120
	undefined4 m_unk0x134;              // 0x134
	undefined4 m_unk0x12c;              // 0x12c
	undefined4 m_unk0x130;              // 0x130
	undefined4 m_unk0x124;              // 0x124
	undefined4 m_unk0x128;              // 0x128
	undefined4 m_unk0x138;              // 0x138
	undefined4 m_unk0x13c;              // 0x13c
};

#endif // SORDIDWATCH0x140_H

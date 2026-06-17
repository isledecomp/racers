#ifndef MARBLEPATH0X114_H
#define MARBLEPATH0X114_H

#include "decomp.h"
#include "golmodelentity.h"
#include "surface/color.h"
#include "types.h"

class GolRenderDevice;
class GdbVertexArray0xc;
class GolExport;
class GolModelBase;

// SIZE 0x114
class MarblePath0x114 {
public:
	MarblePath0x114();
	~MarblePath0x114();
	void FUN_00414950(GolExport* p_golExport, GolRenderDevice* p_renderer, LegoU32 p_count);
	void FUN_004149f0();
	void FUN_00415a40(GolRenderDevice* p_renderer);
	LegoU8 FUN_00415bf0(const ColorRGBA* p_color);
	GolModelBase* GetUnk0x004() const { return m_unk0x004; }
	LegoU32 GetUnk0x0b0() const { return m_unk0x0b0; }
	LegoU32 GetUnk0x0b4() const { return m_unk0x0b4; }
	GolModelEntity& GetUnk0x010() { return m_unk0x010; }

public:
	enum {
		c_flags0x100Bit0 = 1 << 0,
		c_flags0x100Bit2 = 1 << 2,
	};

	GolExport* m_unk0x000;         // 0x000
	GolModelBase* m_unk0x004;      // 0x004
	GdbVertexArray0xc* m_unk0x008; // 0x008
	LegoU8* m_unk0x00c;            // 0x00c
	GolModelEntity m_unk0x010;     // 0x010
	LegoU32 m_unk0x0a0;            // 0x0a0
	LegoU32 m_unk0x0a4;            // 0x0a4
	LegoU32 m_unk0x0a8;            // 0x0a8
	LegoU32 m_unk0x0ac;            // 0x0ac
	LegoU32 m_unk0x0b0;            // 0x0b0
	LegoU32 m_unk0x0b4;            // 0x0b4
	LegoU32 m_unk0x0b8;            // 0x0b8
	LegoU32 m_unk0x0bc;            // 0x0bc
	LegoU32 m_unk0x0c0;            // 0x0c0
	GolVec3 m_unk0x0c4;            // 0x0c4
	GolVec3 m_unk0x0d0;            // 0x0d0
	GolVec3 m_unk0x0dc;            // 0x0dc
	GolVec3 m_unk0x0e8;            // 0x0e8
	GolVec3 m_unk0x0f4;            // 0x0f4
	LegoU32 m_flags0x100;          // 0x100
	LegoFloat m_unk0x104;          // 0x104
	LegoFloat m_unk0x108;          // 0x108
	LegoFloat m_unk0x10c;          // 0x10c
	ColorRGBA m_unk0x110;          // 0x110
};

#endif // MARBLEPATH0X114_H

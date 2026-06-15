#ifndef MARBLEPATH0X114_H
#define MARBLEPATH0X114_H

#include "decomp.h"
#include "golmodelentity.h"
#include "surface/color.h"
#include "types.h"

class GolD3DRenderDevice;
class GdbVertexArray0xc;
class GolModelBase;

// SIZE 0x114
class MarblePath0x114 {
public:
	class Field0x0 {
	public:
		virtual void VTable0x00() = 0;              // vtable+0x00
		virtual void VTable0x04() = 0;              // vtable+0x04
		virtual void VTable0x08() = 0;              // vtable+0x08
		virtual void VTable0x0c() = 0;              // vtable+0x0c
		virtual void VTable0x10() = 0;              // vtable+0x10
		virtual GolModelBase* VTable0x14() = 0;     // vtable+0x14
		virtual void VTable0x18() = 0;              // vtable+0x18
		virtual void VTable0x1c() = 0;              // vtable+0x1c
		virtual void VTable0x20() = 0;              // vtable+0x20
		virtual void VTable0x24() = 0;              // vtable+0x24
		virtual void VTable0x28() = 0;              // vtable+0x28
		virtual void VTable0x2c() = 0;              // vtable+0x2c
		virtual void VTable0x30() = 0;              // vtable+0x30
		virtual void VTable0x34() = 0;              // vtable+0x34
		virtual void VTable0x38() = 0;              // vtable+0x38
		virtual void VTable0x3c() = 0;              // vtable+0x3c
		virtual void VTable0x40() = 0;              // vtable+0x40
		virtual void VTable0x44() = 0;              // vtable+0x44
		virtual void VTable0x48(GolModelBase*) = 0; // vtable+0x48
	};

	void FUN_004149f0();
	void FUN_00415a40(GolD3DRenderDevice* p_renderer);
	LegoU8 FUN_00415bf0(const ColorRGBA* p_color);
	GolModelBase* GetUnk0x004() const { return m_unk0x004; }
	LegoU32 GetUnk0x0b0() const { return m_unk0x0b0; }
	LegoU32 GetUnk0x0b4() const { return m_unk0x0b4; }
	GolModelEntity& GetUnk0x010() { return m_unk0x010; }

public:
	enum {
		c_flags0x100Bit2 = 1 << 2,
	};

	Field0x0* m_unk0x000;                // 0x000
	GolModelBase* m_unk0x004;            // 0x004
	GdbVertexArray0xc* m_unk0x008;       // 0x008
	LegoU8* m_unk0x00c;                  // 0x00c
	GolModelEntity m_unk0x010;           // 0x010
	LegoU32 m_unk0x0a0;                  // 0x0a0
	LegoU32 m_unk0x0a4;                  // 0x0a4
	LegoU32 m_unk0x0a8;                  // 0x0a8
	LegoU32 m_unk0x0ac;                  // 0x0ac
	LegoU32 m_unk0x0b0;                  // 0x0b0
	LegoU32 m_unk0x0b4;                  // 0x0b4
	LegoU32 m_unk0x0b8;                  // 0x0b8
	LegoU32 m_unk0x0bc;                  // 0x0bc
	LegoU32 m_unk0x0c0;                  // 0x0c0
	GolVec3 m_unk0x0c4;                  // 0x0c4
	GolVec3 m_unk0x0d0;                  // 0x0d0
	GolVec3 m_unk0x0dc;                  // 0x0dc
	GolVec3 m_unk0x0e8;                  // 0x0e8
	undefined m_unk0x0f4[0x100 - 0x0f4]; // 0x0f4
	LegoU32 m_flags0x100;                // 0x100
	LegoFloat m_unk0x104;                // 0x104
	LegoFloat m_unk0x108;                // 0x108
	LegoFloat m_unk0x10c;                // 0x10c
	ColorRGBA m_unk0x110;                // 0x110
};

#endif // MARBLEPATH0X114_H

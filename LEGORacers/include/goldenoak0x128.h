#ifndef GOLDENOAK0X128_H
#define GOLDENOAK0X128_H

#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "rubyhaze0x08.h"

class AmberLeaf0x10;
class IndigoStar0x18;

// VTABLE: LEGORACERS 0x004afbc8
// SIZE 0x128
class GoldenOak0x128 : public RubyHaze0x08, public GolListLink {
public:
	GoldenOak0x128();
	~GoldenOak0x128() override;                     // vtable+0x00
	GolListLink* VTable0x04(undefined4) override;   // vtable+0x04
	GolListLink* VTable0x08() override;             // vtable+0x08
	undefined4 VTable0x0c() override;               // vtable+0x0c
	AmberLeaf0x10* VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(AmberLeaf0x10*) override;       // vtable+0x14
	void* VTable0x18() override;                    // vtable+0x18

	void SetUnk0x10(IndigoStar0x18* p_unk0x10) { m_unk0x10 = p_unk0x10; }

	// SYNTHETIC: LEGORACERS 0x0041a690
	// GoldenOak0x128::`scalar deleting destructor'

private:
	IndigoStar0x18* m_unk0x10;         // 0x10
	GolListHead m_unk0x14;             // 0x14
	undefined m_unk0x20;               // 0x20
	undefined m_unk0x21[0x124 - 0x21]; // 0x21
	undefined4 m_unk0x124;             // 0x124
};

#endif // GOLDENOAK0X128_H

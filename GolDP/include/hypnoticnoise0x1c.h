#ifndef GOLDP_HYPNOTICNOISE_H
#define GOLDP_HYPNOTICNOISE_H

#include "floatypontoon0x4c.h"
#include "golhashtable.h"
#include "smallcocoon0xc.h"

class BronzeFalcon0xc8770;

class HypnoticNoise0x1cInner {
public:
	// TODO: VTable is preliminary
	virtual void VTable0x00() = 0;
	virtual void VTable0x04() = 0;
	virtual void VTable0x08() = 0;
	virtual void VTable0x0c() = 0;
	virtual void VTable0x10() = 0;

	undefined2 m_unk0x04; // 0x04
	undefined4 m_unk0x08;
	undefined m_unk0x0c[0x24 - 0x0c]; // 0x06
	BronzeFalcon0xc8770* m_unk0x24;   // 0x24
	undefined4 m_unk0x28;             // 0x28
	undefined m_unk0x2c[0x3c - 0x2c]; // 0x28
	LegoU8 m_unk0x3c;                 // 0x3c
	// undefined m_unk0x3d[0x40 - 0x3d]; // 0x28
	// Likely wrong because unaligned, but we'll see
	undefined4 m_unk0x40;
	undefined4 m_unk0x44; // 0x46
	undefined4 m_unk0x48;
	undefined m_unk0x4v[0xa4 - 0x4c]; // 0x46
};

// const x = sizeof(HypnoticNoise0x1cInner);

// VTABLE: GOLDP 0x10056f28
class HypnoticNoise0x1c : public SmallCocoon0xc {
public:
	HypnoticNoise0x1c();
	~HypnoticNoise0x1c() override;

	void VTable0x08() override; // vtable+0x08

	// SYNTHETIC: GOLDP 0x10022fc0
	// HypnoticNoise0x1c::`scalar deleting destructor'

	virtual void VTable0x0c() = 0;                                                               // vtable+0x0c
	virtual void VTable0x10();                                                                   // vtable+0x10
	virtual void VTable0x14();                                                                   // vtable+0x14
	virtual void VTable0x18(BronzeFalcon0xc8770* p_param1, char* p_param2, undefined4 p_param3); // vtable+0x18
	virtual void VTable0x1c(BronzeFalcon0xc8770* p_param1, LegoU32 p_param2);                    // vtable+0x1c
	virtual HypnoticNoise0x1cInner* VTable0x20(undefined4 p_index) = 0;                          // vtable+0x20

private:
	BronzeFalcon0xc8770* m_unk0x0c; // 0x0c
	undefined4 m_unk0x10;           // 0x10
	LegoU32 m_unk0x14;              // 0x14
	GolHashTable::Entry* m_unk0x18; // 0x18
};

#endif // GOLDP_HYPNOTICNOISE_H

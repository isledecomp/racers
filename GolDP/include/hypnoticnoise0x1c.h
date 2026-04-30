#ifndef GOLDP_HYPNOTICNOISE_H
#define GOLDP_HYPNOTICNOISE_H

#include "floatypontoon0x4c.h"
#include "golhashtable.h"
#include "golnametable.h"
#include "utopianpan0xa4.h"

class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x10056f28
class HypnoticNoise0x1c : public GolNameTable {
public:
	HypnoticNoise0x1c();
	~HypnoticNoise0x1c() override;

	void Clear() override; // vtable+0x08

	// SYNTHETIC: GOLDP 0x10022fc0
	// HypnoticNoise0x1c::`scalar deleting destructor'

	virtual void VTable0x0c() = 0; // vtable+0x0c
	virtual void VTable0x10();     // vtable+0x10
	virtual void VTable0x14();     // vtable+0x14
	virtual void LoadMaterialDefinitions(
		BronzeFalcon0xc8770* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                                                            // vtable+0x18
	virtual void VTable0x1c(BronzeFalcon0xc8770* p_renderer, LegoU32 p_numItems); // vtable+0x1c
	virtual UtopianPan0xa4* GetItem(undefined4 p_index) = 0;                      // vtable+0x20

protected:
	BronzeFalcon0xc8770* m_renderer;         // 0x0c
	undefined4 m_unk0x10;                    // 0x10
	LegoU32 m_numItems;                      // 0x14
	GolHashTable::Entry* m_currentHashEntry; // 0x18
};

#endif // GOLDP_HYPNOTICNOISE_H

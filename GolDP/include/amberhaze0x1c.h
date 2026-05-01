#ifndef AMBERHAZE0X1C_H
#define AMBERHAZE0X1C_H

#include "golnametable.h"

class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x10057134
// SIZE 0x1c
class AmberHaze0x1c : public GolNameTable {
public:
	AmberHaze0x1c();
	~AmberHaze0x1c() override; // vtable+0x00
	void Clear() override;     // vtable+0x08

	virtual void VTable0x0c();                                                                          // vtable+0x0c
	virtual void VTable0x10();                                                                          // vtable+0x10
	virtual void VTable0x14() = 0;                                                                      // vtable+0x14
	virtual void VTable0x18() = 0;                                                                      // vtable+0x18
	virtual void VTable0x1c(BronzeFalcon0xc8770* p_renderer, LegoU32 p_capacity);                       // vtable+0x1c
	virtual void VTable0x20(BronzeFalcon0xc8770* p_renderer, undefined4 p_unk0x08, LegoU32 p_capacity); // vtable+0x20
	virtual void VTable0x24(
		BronzeFalcon0xc8770* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                                     // vtable+0x24
	virtual undefined4 VTable0x28(undefined4 p_index) = 0; // vtable+0x28

	// SYNTHETIC: GOLDP 0x100261d0
	// AmberHaze0x1c::`scalar deleting destructor'

	AmberHaze0x1c* GetNext() const { return m_next; }
	void SetNext(AmberHaze0x1c* p_next) { m_next = p_next; }
	Entry* GetNameEntries() const { return m_nameEntries; }

private:
	BronzeFalcon0xc8770* m_renderer; // 0x0c
	AmberHaze0x1c* m_next;           // 0x10
	undefined4 m_unk0x14;            // 0x14
	LegoU32 m_numItems;              // 0x18
};

#endif // AMBERHAZE0X1C_H

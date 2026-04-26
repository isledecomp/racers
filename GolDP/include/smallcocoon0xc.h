#ifndef GOL_SMALLCOCOON0xC_H
#define GOL_SMALLCOCOON0xC_H

#include "utopianpan0xa4.h"

// SIZE 0xc
// VTABLE: GOLDP 0x100572d8
class SmallCocoon0xc {
public:
	struct Item {
		LegoChar m_key[8];        // 0x00
		UtopianPan0xa4* m_unk0x8; // 0x08
	};

	SmallCocoon0xc();

	// FUNCTION: GOLDP 0x10028220
	virtual ~SmallCocoon0xc()
	{
		if (m_data != NULL) {
			delete[] m_data;
			m_data = NULL;
		}
	} // vtable+0x00

	virtual void VTable0x04(LegoU32 p_size); // vtable+0x04
	virtual void VTable0x08();               // vtable+0x08

	void AddName(const LegoChar* p_arg1, UtopianPan0xa4* p_arg2);
	UtopianPan0xa4* GetName(const LegoChar* p_str) const;
	void FUN_10028470(const UtopianPan0xa4* p_needle, LegoChar* p_buffer) const;

	// SYNTHETIC: GOLDP 0x100281e0
	// SmallCocoon0xc::`scalar deleting destructor'

protected:
	Item* m_data;      // 0x04
	undefined4 m_size; // 0x08
};

#endif // GOL_SMALLCOCOON0xC_H

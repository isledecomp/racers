#ifndef GOL_SMALLCOCOON0xC_H
#define GOL_SMALLCOCOON0xC_H

#include "utopianpan0xa4.h"

#ifdef BUILDING_LEGORACERS
#pragma inline_depth(0)
#endif

// SIZE 0xc
// VTABLE: GOLDP 0x100572d8
// VTABLE: LEGORACERS 0x004af7c0
class SmallCocoon0xc {
public:
	struct Item {
		LegoChar m_key[8];        // 0x00
		UtopianPan0xa4* m_unk0x8; // 0x08
	};

	SmallCocoon0xc();

	// FUNCTION: GOLDP 0x10028220
	// FUNCTION: LEGORACERS 0x004117f0
	virtual ~SmallCocoon0xc() { VTable0x08(); } // vtable+0x00

	virtual void VTable0x04(LegoU32 p_size); // vtable+0x04

	// FUNCTION: GOLDP 0x100282a0
	// FUNCTION: LEGORACERS 0x00411850
	virtual void VTable0x08()
	{
		if (m_data != NULL) {
			delete[] m_data;
			m_data = NULL;
		}
	} // vtable+0x08

	void AddName(const LegoChar* p_arg1, UtopianPan0xa4* p_arg2);
	UtopianPan0xa4* GetName(const LegoChar* p_str) const;
	void FUN_10028470(const UtopianPan0xa4* p_needle, LegoChar* p_buffer) const;

	// SYNTHETIC: GOLDP 0x100281e0
	// SYNTHETIC: LEGORACERS 0x004117d0
	// SmallCocoon0xc::`scalar deleting destructor'

protected:
	Item* m_data;      // 0x04
	undefined4 m_size; // 0x08
};

#ifdef BUILDING_LEGORACERS
#pragma inline_depth()
#endif

#endif // GOL_SMALLCOCOON0xC_H

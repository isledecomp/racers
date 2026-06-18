#ifndef GDBMODELINDEXARRAY0XC_H
#define GDBMODELINDEXARRAY0XC_H

#include "compat.h"
#include "igdbmodelindexarray0x8.h"
#include "types.h"

// VTABLE: GOLDP 0x1005759c
// SIZE 0xc
class GdbModelIndexArray0xc : public IGdbModelIndexArray0x8 {
public:
	GdbModelIndexArray0xc();
	~GdbModelIndexArray0xc() override; // vtable+0x00

	void VTable0x04(GolFileParser& p_parser) override; // vtable+0x04
	void VTable0x08() override;                        // vtable+0x08
	virtual void VTable0x0c(LegoU32 p_count);          // vtable+0x0c

	// SYNTHETIC: GOLDP 0x1002b330
	// GdbModelIndexArray0xc::`scalar deleting destructor'

	struct Indices {
		LegoU8 m_a; // 0x0
		LegoU8 m_b; // 0x1
		LegoU8 m_c; // 0x2
		LegoU8 m_x; // 0x3
	};

	const Indices* GetIndices() const { return m_unk0x08; }
	Indices* GetMutableIndices() { return m_unk0x08; }
	const Indices* GetIndex(LegoU32 p_index) const { return m_unk0x08 + p_index; }
	Indices* GetMutableIndex(LegoU32 p_index) { return m_unk0x08 + p_index; }
	LegoU8* GetIndexBytes() const { return &m_unk0x08->m_a; }
	void SetIndices(LegoU32 p_index, LegoU8 p_a, LegoU8 p_b, LegoU8 p_c)
	{
		m_unk0x08[p_index].m_a = p_a;
		m_unk0x08[p_index].m_b = p_b;
		m_unk0x08[p_index].m_c = p_c;
		m_unk0x08[p_index].m_x = 0;
	}

protected:
	Indices* m_unk0x08;
};

#endif // GDBMODELINDEXARRAY0XC_H

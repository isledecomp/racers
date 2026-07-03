#ifndef GDBMODELINDEXARRAY_H
#define GDBMODELINDEXARRAY_H

#include "compat.h"
#include "gdbmodelindexarraybase.h"
#include "types.h"

// VTABLE: GOLDP 0x1005759c
// SIZE 0xc
class GdbModelIndexArray : public GdbModelIndexArrayBase {
public:
	GdbModelIndexArray();
	~GdbModelIndexArray() override; // vtable+0x00

	void Parse(GolFileParser& p_parser) override; // vtable+0x04
	void Destroy() override;                      // vtable+0x08
	virtual void Allocate(LegoU32 p_count);       // vtable+0x0c

	// SYNTHETIC: GOLDP 0x1002b330
	// GdbModelIndexArray::`scalar deleting destructor'

	struct Indices {
		LegoU8 m_a; // 0x0
		LegoU8 m_b; // 0x1
		LegoU8 m_c; // 0x2
		LegoU8 m_x; // 0x3
	};

	const Indices* GetIndices() const { return m_indices; }
	Indices* GetMutableIndices() { return m_indices; }
	const Indices* GetIndex(LegoU32 p_index) const { return m_indices + p_index; }
	Indices* GetMutableIndex(LegoU32 p_index) { return m_indices + p_index; }
	LegoU8* GetIndexBytes() const { return &m_indices->m_a; }
	void SetIndices(LegoU32 p_index, LegoU8 p_a, LegoU8 p_b, LegoU8 p_c)
	{
		m_indices[p_index].m_a = p_a;
		m_indices[p_index].m_b = p_b;
		m_indices[p_index].m_c = p_c;
		m_indices[p_index].m_x = 0;
	}
	void SetTriangleIndices(LegoU32 p_index, LegoU8 p_a, LegoU8 p_b, LegoU8 p_c)
	{
		m_indices[p_index].m_a = p_a;
		m_indices[p_index].m_b = p_b;
		m_indices[p_index].m_c = p_c;
	}

protected:
	Indices* m_indices; // 0x08
};

#endif // GDBMODELINDEXARRAY_H

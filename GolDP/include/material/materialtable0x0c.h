#ifndef MATERIALTABLE0X0C_H
#define MATERIALTABLE0X0C_H

#include "decomp.h"
#include "types.h"

class GolRenderDevice;

// SIZE 0x0c
struct MaterialTable0x0c {
	MaterialTable0x0c* FUN_004a00b0();
	void Destroy();
	void Initialize(GolRenderDevice* p_renderer, LegoU32 p_count);
	void Clear();
	LegoS32 FindEntryIndexByName(const LegoChar* p_name) const;
	void AssignEntryByName(LegoS32 p_index, const LegoChar* p_name);
	void SetPosition(LegoU32 p_index, void* p_position);
	void* GetPosition(LegoU32 p_index) const { return m_entries[p_index]; }

	GolRenderDevice* m_renderer; // 0x00
	LegoU32 m_count;             // 0x04
	void** m_entries;            // 0x08
};

#endif // MATERIALTABLE0X0C_H

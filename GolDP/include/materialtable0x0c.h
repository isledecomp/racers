#ifndef MATERIALTABLE0X0C_H
#define MATERIALTABLE0X0C_H

#include "types.h"

class WhiteFalcon0x140;

// SIZE 0x0c
struct MaterialTable0x0c {
	void SetPosition(LegoU32 p_index, void* p_position) { m_entries[p_index] = p_position; }
	undefined4* GetPosition(LegoU32 p_index) const { return static_cast<undefined4*>(m_entries[p_index]); }

	WhiteFalcon0x140* m_renderer; // 0x00
	LegoU32 m_count;              // 0x04
	void** m_entries;             // 0x08
};

#endif // MATERIALTABLE0X0C_H

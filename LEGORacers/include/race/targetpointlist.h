#ifndef TARGETPOINTLIST_H
#define TARGETPOINTLIST_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

class GolFileParser;

class TargetPointList {
public:
	// SIZE 0x14
	class Entry {
	public:
		enum {
			c_flagEnabled = 1 << 1,
		};

		Entry();
		~Entry();
		void Set(GolVec3* p_position, LegoS32 p_index);

		GolVec3 m_position;               // 0x00
		LegoS32 m_index;                  // 0x0c
		LegoU8 m_flags;                   // 0x10
		undefined m_unk0x11[0x14 - 0x11]; // 0x11
	};

	LegoU32 DisableTargetPoints(undefined4 p_index);
	Entry* FindTargetInCone(
		GolVec3* p_position,
		GolVec3* p_direction,
		LegoFloat p_minDistanceSquared,
		LegoFloat p_maxDistanceSquared,
		LegoFloat p_coneCosine
	);

	Entry* m_entries; // 0x00
	LegoS32 m_count;  // 0x04
};

#endif // TARGETPOINTLIST_H

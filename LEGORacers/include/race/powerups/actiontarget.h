#ifndef ACTIONTARGET_H
#define ACTIONTARGET_H

#include "golmath.h"
#include "types.h"

class Racer;
class RaceActionSource;

// SIZE 0x1c
class ActionTarget {
public:
	GolVec3 m_position;  // 0x00
	GolVec3 m_direction; // 0x0c
	union {
		const LegoChar* m_materialName; // 0x18
		RaceActionSource* m_source;     // 0x18
	};
};

#endif // ACTIONTARGET_H

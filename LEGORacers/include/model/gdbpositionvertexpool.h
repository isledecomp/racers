#ifndef GDBPOSITIONVERTEXPOOL_H
#define GDBPOSITIONVERTEXPOOL_H

#include "decomp.h"
#include "golmath.h"
#include "surface/color.h"
#include "types.h"

class GolFileParser;

// VTABLE: LEGORACERS 0x004af964
// SIZE 0x0c
class GdbPositionVertexPool {
public:
	GdbPositionVertexPool();
	virtual ~GdbPositionVertexPool();                                 // vtable+0x00
	virtual void Allocate(LegoU16 p_count);                           // vtable+0x04
	virtual void Read(GolFileParser& p_parser);                       // vtable+0x08
	virtual void Clear();                                             // vtable+0x0c
	virtual void VTable0x10();                                        // vtable+0x10
	virtual void GetPosition(LegoU32 p_index, GolVec3* p_dest) const; // vtable+0x14
	virtual void GetTexCoord(LegoU32 p_index, GolVec2* p_dest) const; // vtable+0x18
	virtual void GetNormal(LegoU32 p_index, GolVec3* p_dest) const;   // vtable+0x1c
	virtual void GetColor(LegoU32 p_index, ColorRGBA* p_dest) const;  // vtable+0x20
	virtual void SetPosition(LegoU32 p_index, const GolVec3* p_src);  // vtable+0x24
	virtual void SetTexCoord(LegoU32 p_index, const GolVec2* p_src);  // vtable+0x28
	virtual void SetNormal(LegoU32 p_index, const GolVec3* p_src);    // vtable+0x2c
	virtual void SetColor(LegoU32 p_index, const ColorRGBA* p_src);   // vtable+0x30
	virtual void VTable0x34(const LegoChar* p_name);                  // vtable+0x34
	virtual void VTable0x38();                                        // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x00415df0
	// GdbPositionVertexPool::`scalar deleting destructor'

protected:
	LegoU16 m_count;      // 0x04
	LegoU16 m_vertexType; // 0x06
	GolVec3* m_positions; // 0x08
};

#endif // GDBPOSITIONVERTEXPOOL_H

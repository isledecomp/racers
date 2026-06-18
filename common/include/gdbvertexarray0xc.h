#ifndef GDBVERTEXARRAY0xC_H
#define GDBVERTEXARRAY0xC_H

#include "decomp.h"
#include "types.h"

class GolFileParser;
struct GolVec2;
struct GolVec3;
struct ColorRGBA;

// SIZE 0x20
struct ColorTransform0x20 {
	LegoU32 m_redShift;  // 0x00
	LegoU32 m_grnShift;  // 0x04
	LegoU32 m_bluShift;  // 0x08
	LegoU32 m_alpShift;  // 0x0c
	LegoU32 m_redOffset; // 0x10
	LegoU32 m_grnOffset; // 0x14
	LegoU32 m_bluOffset; // 0x18
	LegoU32 m_alpOffset; // 0x1c
};

// VTABLE: GOLDP 0x100576a8
// VTABLE: LEGORACERS 0x004af964
// SIZE 0xc
class GdbVertexArray0xc {
public:
	GdbVertexArray0xc();
	virtual ~GdbVertexArray0xc();                                      // vtable+0x00
	virtual void VTable0x04(LegoU16 p_count);                          // vtable+0x04
	virtual void VTable0x08(GolFileParser& p_parser);                  // vtable+0x08
	virtual void VTable0x0c();                                         // vtable+0x0c
	virtual void VTable0x10();                                         // vtable+0x10
	virtual void VTable0x14(LegoU32 p_index, GolVec3* p_dest) const;   // vtable+0x14
	virtual void VTable0x18(LegoU32 p_index, GolVec2* p_dest) const;   // vtable+0x18
	virtual void VTable0x1c(LegoU32 p_index, GolVec3* p_dest) const;   // vtable+0x1c
	virtual void VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) const; // vtable+0x20
	virtual void VTable0x24(LegoU32 p_index, const GolVec3&);          // vtable+0x24
	virtual void VTable0x28(LegoU32 p_index, const GolVec2&);          // vtable+0x28
	virtual void VTable0x2c(LegoU32 p_index, const GolVec3&);          // vtable+0x2c
	virtual void VTable0x30(LegoU32 p_index, const ColorRGBA&);        // vtable+0x30
	virtual void VTable0x34(const ColorTransform0x20& p_details);      // vtable+0x34
	virtual void VTable0x38();                                         // vtable+0x38

	// LEGORACERS and GOLDP order these shared methods differently in the common .cpp,
	// so keep the conflicting LEGORACERS annotations here as by-name references.
	// Maybe some of these are FOLDED.
	// FUNCTION: LEGORACERS 0x00415f60
	// GdbVertexArray0xc::VTable0x14

	// FUNCTION: LEGORACERS 0x00415fb0
	// GdbVertexArray0xc::VTable0x1c

	// FUNCTION: LEGORACERS 0x00415ff0
	// GdbVertexArray0xc::VTable0x24

	// SYNTHETIC: GOLDP 0x1002be20
	// SYNTHETIC: LEGORACERS 0x00415df0
	// GdbVertexArray0xc::`scalar deleting destructor'

	LegoU16 GetVertexType() const { return m_vertexType; }
	LegoU16 GetCount() const { return m_count; }
	GolVec3* GetPositions() const { return m_positions; }

protected:
	LegoU16 m_count;      // 0x04
	LegoU16 m_vertexType; // 0x06
	GolVec3* m_positions; // 0x08
};
//
// // SIZE 0x1c
// class GdbVertexArrayTypeOne0x1c : public GdbCommonVertexArray0x1c {
// public:
// 	GdbVertexArrayTypeOne0x1c();
// };
//
// // SIZE 0x20
// class GdbVertexArrayTypeTwo0x20 : public GdbCommonVertexArray0x1c{
// public:
// 	GdbVertexArrayTypeTwo0x20();
// };
//
// // SIZE 0x20
// class GdbVertexArrayTypeThree0x20 : public GdbVertexArrayTypeTwo0x20 {
// public:
// 	GdbVertexArrayTypeThree0x20();
// };

#endif // GDBVERTEXARRAY0XC_H

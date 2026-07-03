#ifndef GDBVERTEXARRAY_H
#define GDBVERTEXARRAY_H

#include "colortransform.h"
#include "decomp.h"
#include "types.h"

class GolFileParser;
struct GolVec2;
struct GolVec3;
struct ColorRGBA;

// VTABLE: GOLDP 0x100576a8
// VTABLE: LEGORACERS 0x004af964
// SIZE 0xc
class GdbVertexArray {
public:
	// values match the .gdb vertex-type tokens; Prelit downgrades itself to
	// Colored once DiscardNormals runs after the lighting bake
	enum {
		c_vertexTypeColored = 1,
		c_vertexTypeNormal = 2,
		c_vertexTypePrelit = 3,
		c_vertexTypePosition = 5,
	};

	GdbVertexArray();
	virtual ~GdbVertexArray();                                                 // vtable+0x00
	virtual void Allocate(LegoU16 p_count);                                    // vtable+0x04
	virtual void Parse(GolFileParser& p_parser);                               // vtable+0x08
	virtual void Destroy();                                                    // vtable+0x0c
	virtual void DiscardNormals();                                             // vtable+0x10
	virtual void GetPosition(LegoU32 p_index, GolVec3* p_dest) const;          // vtable+0x14
	virtual void GetTextureCoordinate(LegoU32 p_index, GolVec2* p_dest) const; // vtable+0x18
	virtual void GetNormal(LegoU32 p_index, GolVec3* p_dest) const;            // vtable+0x1c
	virtual void GetColor(LegoU32 p_index, ColorRGBA* p_dest) const;           // vtable+0x20
	virtual void SetPosition(LegoU32 p_index, const GolVec3&);                 // vtable+0x24
	virtual void SetTextureCoordinate(LegoU32 p_index, const GolVec2&);        // vtable+0x28
	virtual void SetNormal(LegoU32 p_index, const GolVec3&);                   // vtable+0x2c
	virtual void SetColor(LegoU32 p_index, const ColorRGBA&);                  // vtable+0x30
	virtual void ApplyColorTransform(const ColorTransform& p_details);         // vtable+0x34
	virtual void ClearColorTransform();                                        // vtable+0x38

	// LEGORACERS and GOLDP order these shared methods differently in the common .cpp,
	// so keep the conflicting LEGORACERS annotations here as by-name references.
	// Maybe some of these are FOLDED.
	// FUNCTION: LEGORACERS 0x00415f60
	// GdbVertexArray::GetPosition

	// FUNCTION: LEGORACERS 0x00415fb0
	// GdbVertexArray::GetNormal

	// FUNCTION: LEGORACERS 0x00415ff0
	// GdbVertexArray::SetPosition

	// SYNTHETIC: GOLDP 0x1002be20
	// SYNTHETIC: LEGORACERS 0x00415df0
	// GdbVertexArray::`scalar deleting destructor'

	LegoU16 GetVertexType() const { return m_vertexType; }
	LegoU16 GetCount() const { return m_count; }
	GolVec3* GetPositions() const { return m_positions; }

protected:
	LegoU16 m_count;      // 0x04
	LegoU16 m_vertexType; // 0x06
	GolVec3* m_positions; // 0x08
};
#endif // GDBVERTEXARRAY_H

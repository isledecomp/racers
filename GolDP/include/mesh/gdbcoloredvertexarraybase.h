#ifndef GDBCOLOREDVERTEXARRAYBASE_H
#define GDBCOLOREDVERTEXARRAYBASE_H

#include "compat.h"
#include "gdbvertexarray.h"

// VTABLE: GOLDP 0x100568d0
// SIZE 0x1c
class GdbColoredVertexArrayBase : public GdbVertexArray {
public:
	GdbColoredVertexArrayBase();
	~GdbColoredVertexArrayBase() override; // vtable+0x00
	void Destroy() override;
	void ApplyColorTransform(const ColorTransform& p_details) override;
	void ClearColorTransform() override;

	// SYNTHETIC: GOLDP 0x10016f40
	// GdbColoredVertexArrayBase::`scalar deleting destructor'

	GolVec2* GetTextureCoordinates() const { return m_textureCoordinates; }
	LegoU32* GetColors() const { return m_colors; }
	LegoBool32 HasTransformedColors() const { return m_hasTransformedColors; }
	LegoU32* GetTransformedColors() const { return m_transformedColors; }

protected:
	GolVec2* m_textureCoordinates;     // 0x0c
	LegoU32* m_colors;                 // 0x10
	undefined4 m_hasTransformedColors; // 0x14
	LegoU32* m_transformedColors;      // 0x18
};

#endif // GDBCOLOREDVERTEXARRAYBASE_H

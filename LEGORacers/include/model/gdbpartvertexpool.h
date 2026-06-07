#ifndef GDBPARTVERTEXPOOL_H
#define GDBPARTVERTEXPOOL_H

#include "compat.h"
#include "decomp.h"
#include "model/gdbpositionvertexpool.h"
#include "surface/color.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af4b4
// SIZE 0x14
class GdbPartVertexPool : public GdbPositionVertexPool {
public:
	// SIZE 0x0e
	struct Vertex {
		// SIZE 0x04
		union Tail0x04 {
			// SIZE 0x04
			struct Normal {
				LegoS8 m_nx;   // 0x00
				LegoS8 m_ny;   // 0x01
				LegoS8 m_nz;   // 0x02
				LegoU8 m_argb; // 0x03
			} m_normal;

			ColorRGBA m_color; // 0x00
		};

		LegoS16 m_x;     // 0x00
		LegoS16 m_y;     // 0x02
		LegoS16 m_z;     // 0x04
		LegoS16 m_u;     // 0x06
		LegoS16 m_v;     // 0x08
		Tail0x04 m_tail; // 0x0a
	};

	GdbPartVertexPool();
	~GdbPartVertexPool() override;

	void Clear() override;
	void Read(GolFileParser& p_parser, LegoU16 p_vertexType);
	void GetPosition(LegoU32 p_index, GolVec3* p_dest) const override;
	void GetTexCoord(LegoU32 p_index, GolVec2* p_dest) const override;
	void GetNormal(LegoU32 p_index, GolVec3* p_dest) const override;
	void GetColor(LegoU32 p_index, ColorRGBA* p_dest) const override;
	void SetPosition(LegoU32 p_index, const GolVec3* p_src) override;
	void SetTexCoord(LegoU32 p_index, const GolVec2* p_src) override;
	void SetNormal(LegoU32 p_index, const GolVec3* p_src) override;
	void SetColor(LegoU32 p_index, const ColorRGBA* p_src) override;
	LegoU16 GetVertexType() const { return m_vertexType; }

	// SYNTHETIC: LEGORACERS 0x00408000
	// GdbPartVertexPool::`scalar deleting destructor'

private:
	Vertex* m_vertices; // 0x0c
	LegoU32 m_unk0x10;  // 0x10
};

#endif // GDBPARTVERTEXPOOL_H

#ifndef DECALGEOMETRY_H
#define DECALGEOMETRY_H

#include "decomp.h"
#include "golmodelentity.h"
#include "surface/color.h"
#include "types.h"

class GolRenderDevice;
class GdbVertexArray;
class GolExport;
class GolModelBase;

// SIZE 0x114
class DecalGeometry {
public:
	DecalGeometry();
	~DecalGeometry();
	void Initialize(GolExport* p_golExport, GolRenderDevice* p_renderer, LegoU32 p_count);
	void Destroy();
	void Draw(GolRenderDevice* p_renderer);
	LegoU8 SetColor(const ColorRGBA* p_color);
	GolModelBase* GetModel() const { return m_model; }
	LegoU32 GetVertexCount() const { return m_vertexCount; }
	LegoU32 GetTriangleCount() const { return m_triangleCount; }
	GolModelEntity& GetEntity() { return m_entity; }

public:
	enum {
		c_initialized = 1 << 0,
		c_hasGeometry = 1 << 2,
	};

	GolExport* m_golExport;       // 0x000
	GolModelBase* m_model;        // 0x004
	GdbVertexArray* m_vertices;   // 0x008
	LegoU8* m_indexBytes;         // 0x00c
	GolModelEntity m_entity;      // 0x010
	LegoU32 m_vertexCapacity;     // 0x0a0
	LegoU32 m_triangleCapacity;   // 0x0a4
	LegoU32 m_batchFirstVertex;   // 0x0a8
	LegoU32 m_batchFirstTriangle; // 0x0ac
	LegoU32 m_vertexCount;        // 0x0b0
	LegoU32 m_triangleCount;      // 0x0b4
	LegoU32 m_groupIndex;         // 0x0b8
	LegoU32 m_batchVertexCount;   // 0x0bc
	LegoU32 m_batchTriangleCount; // 0x0c0
	GolVec3 m_widthAxis;          // 0x0c4
	GolVec3 m_lengthAxis;         // 0x0d0
	GolVec3 m_normal;             // 0x0dc
	GolVec3 m_center;             // 0x0e8
	GolVec3 m_position;           // 0x0f4
	LegoU32 m_flags;              // 0x100
	LegoFloat m_width;            // 0x104
	LegoFloat m_length;           // 0x108
	LegoFloat m_depth;            // 0x10c
	ColorRGBA m_color;            // 0x110
};

#endif // DECALGEOMETRY_H

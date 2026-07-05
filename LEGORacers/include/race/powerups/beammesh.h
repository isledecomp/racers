#ifndef BEAMMESH_H
#define BEAMMESH_H

#include "gdbmodelindexarray.h"
#include "golmath.h"
#include "race/powerups/beamentity.h"
#include "surface/color.h"
#include "types.h"

class GdbVertexArray;
class GolD3DRenderDevice;
class GolExport;
class GolMaterial;
class RacePowerupManager;

// SIZE 0x170
class BeamMesh {
public:
	enum {
		c_flagVisible = 1 << 0,
		c_flagUseSegmentOffsets = 1 << 1,
		c_flagSectionAttached = 1 << 2,
		c_groupTriangleRun = 0x20000000,
		c_groupBegin = 0x80000000,
		c_groupAttachSection = 0xa0000000,
		c_groupClose = 0xc0000000
	};

	// SIZE 0x74
	struct SetupParams {
		GolExport* m_golExport;       // 0x00
		GolRenderDevice* m_renderer;  // 0x04
		GolMaterial* m_material;      // 0x08
		LegoU32 m_sectionCount;       // 0x0c
		LegoU32 m_segmentCount;       // 0x10
		LegoU32 m_ringQuadCount;      // 0x14
		GolVec3 m_ringVertices[3];    // 0x18
		undefined4 m_unk0x3c[6];      // 0x3c
		LegoFloat m_ringTextureXs[5]; // 0x54
		LegoU32 m_textureColumnCount; // 0x68
		LegoFloat m_modelDistance;    // 0x6c
		undefined4 m_faceCamera;      // 0x70
	};

	BeamMesh();
	~BeamMesh();
	void Reset();
	void Initialize(const SetupParams* p_params);
	void Destroy();
	void Begin(const GolVec3* p_position, const GolVec3* p_direction);
	void AdvanceSection(const GolVec3* p_position);
	void AppendPoint(const GolVec3* p_position);
	void Finish();
	void EmitRing(const GolVec3* p_position, const ColorRGBA* p_color, LegoU32 p_textureColumn, LegoU32 p_offsetIndex);
	void EmitQuads();
	void FlushWindow();
	void FlushRuns();
	void SetColors(const ColorRGBA* p_baseColor, const ColorRGBA* p_secondaryColor, const ColorRGBA* p_tertiaryColor);
	void Draw(GolD3DRenderDevice* p_renderer);
	void AppendSpan(const GolVec3* p_position, LegoFloat p_amount);
	void Interpolate(
		const GolVec3* p_fromPosition,
		const GolVec3* p_toPosition,
		const ColorRGBA* p_fromColor,
		const ColorRGBA* p_toColor,
		LegoFloat p_amount,
		GolVec3* p_positionResult,
		ColorRGBA* p_colorResult
	);
	void SetSegmentOffsets(const GolVec3* p_offsets);

private:
	GolExport* m_golExport;                 // 0x000
	GolModelBase* m_model;                  // 0x004
	GdbVertexArray* m_vertices;             // 0x008
	GdbModelIndexArray::Indices* m_indices; // 0x00c
	GolSceneNode* m_sceneNode;              // 0x010
	GolMaterial* m_material;                // 0x014
	BeamEntity m_entity;                    // 0x018
	LegoS32 m_windowBaseVertex;             // 0x0b0
	LegoS32 m_ringVertexIndex;              // 0x0b4
	LegoS32 m_previousRingVertexIndex;      // 0x0b8
	LegoU32 m_vertexCursor;                 // 0x0bc
	LegoU32 m_runStartVertex;               // 0x0c0
	LegoU32 m_runStartIndex;                // 0x0c4
	LegoU32 m_indexCursor;                  // 0x0c8
	LegoU32 m_groupCursor;                  // 0x0cc
	LegoU32 m_sectionIndex;                 // 0x0d0
	LegoU32 m_textureColumn;                // 0x0d4
	LegoFloat m_segmentStep;                // 0x0d8
	LegoU32 m_sectionCount;                 // 0x0dc
	LegoU32 m_segmentCount;                 // 0x0e0
	LegoU32 m_ringQuadCount;                // 0x0e4
	LegoU32 m_ringVertexCount;              // 0x0e8
	GolVec3 m_ringVertices[5];              // 0x0ec
	LegoFloat m_ringTextureXs[5];           // 0x128
	LegoU32 m_textureColumnCount;           // 0x13c
	LegoU32 m_flags;                        // 0x140
	const GolVec3* m_segmentOffsets;        // 0x144
	GolVec3 m_startPosition;                // 0x148
	GolVec3 m_lastPosition;                 // 0x154
	ColorRGBA m_baseColor;                  // 0x160
	ColorRGBA m_secondaryColor;             // 0x164
	ColorRGBA m_tertiaryColor;              // 0x168
	undefined4 m_vertexCapacity;            // 0x16c
};

#endif // BEAMMESH_H

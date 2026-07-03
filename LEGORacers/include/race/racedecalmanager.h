#ifndef RACEDECALMANAGER_H
#define RACEDECALMANAGER_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "types.h"
#include "util/decalgeometry.h"

class GolD3DRenderDevice;
class GolExport;
class GdbVertexArray;
class GolCollidableEntity;
class GolModelBase;
struct ColorRGBA;

// VTABLE: LEGORACERS 0x004b478c
// SIZE 0x0c
class RaceDecalManager {
public:
	RaceDecalManager();
	virtual ~RaceDecalManager(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x00492600
	// RaceDecalManager::`scalar deleting destructor'

	void Destroy();

	// VTABLE: LEGORACERS 0x004b4788
	// SIZE 0x334
	class Trail {
	public:
		// SIZE 0x11c
		class Decal : public DecalGeometry {
		public:
			enum {
				c_commandMask = 0xe0000000,
				c_commandVertices = 0x00000000,
				c_commandModelFlags = 0x80000000,
				c_commandPolygon = 0x20000000,
				c_commandEnd = 0xc0000000,
				c_commandModelFlagBit17 = 1 << 17,
				c_commandVertexMask = 0xffff,
				c_floatOneBits = 0x3f800000,
				c_clipYMaxMask = 0x8fffffff,
				c_clipXMaxMask = 0x20000000,
				c_clipYMinMask = 0x9fffffff,
				c_clipXMinFlag = 1 << 0,
				c_clipXMaxFlag = 1 << 1,
				c_clipYMinFlag = 1 << 2,
				c_clipYMaxFlag = 1 << 3,
				c_projectedVertexCount = 64,
				c_projectedScratchVertexCount = 12,
			};

			// SIZE 0x04
			union FloatBits {
				LegoFloat m_float; // 0x00
				LegoU32 m_bits;    // 0x00
			};

			// SIZE 0x08
			union ProjectedCoordinates {
				struct {
					FloatBits m_x; // 0x000
					FloatBits m_y; // 0x004
				};
				GolVec2 m_vec; // 0x000
			};

			// SIZE 0x20
			struct ProjectedVertex {
				GolVec3 m_position;               // 0x000
				ProjectedCoordinates m_projected; // 0x00c
				LegoU32 m_clipFlags;              // 0x014
				undefined4 m_unk0x018;            // 0x018
				undefined4 m_unk0x01c;            // 0x01c
			};

			void Project(GolCollidableEntity* p_collidable);
			void BeginGeometry(GolModelBase* p_model);
			void ProcessGroups(GolModelBase* p_model, LegoU32 p_firstCommand, LegoU32 p_commandCount);
			void EndGeometry(GolModelBase* p_model);
			void SetOrientation(GolVec3* p_normal, GolVec3* p_lengthAxis);
			void ComputeProjection();
			LegoU32 TransformVertices(LegoU32 p_destIndex, LegoU32 p_firstVertex, LegoU32 p_vertexCount);
			void EmitPolygon(LegoU32 p_firstPolygon, LegoU32 p_polygonCount);
			void EmitTriangle(ProjectedVertex* p_vertex0, ProjectedVertex* p_vertex1, ProjectedVertex* p_vertex2);
			void FlushBatch();
			GolVec3* ComputeQueryPoints();

		private:
			GdbVertexArray* m_sourceVertices; // 0x114
			LegoU8* m_sourceIndexBytes;       // 0x118
		};

		enum {
			c_active = 1 << 0,
			c_fading = 1 << 1,
			c_slotsWrapped = 1 << 2,
			c_liveSegment = 1 << 3,
			c_firstSample = 1 << 4,
			c_samplePending = 1 << 5,
		};

		// SYNTHETIC: LEGORACERS 0x00492760
		// RaceDecalManager::Trail::`vector deleting destructor'
		Trail();
		virtual ~Trail(); // vtable+0x00

		// SIZE 0x9c
		struct ModelEntry {
			void SetPosition(const GolVec3& p_position) { m_entity.SetPosition(p_position); }
			void VTable0x50(GolModelBase* p_model, LegoFloat p_modelDistance)
			{
				m_entity.SetPrimaryModel(p_model, p_modelDistance);
			}
			void ResetModelState() { m_entity.ResetModelState(); }
			void EnableFlagBit1() { m_entity.EnableFlagBit1(); }

			GolModelEntity m_entity; // 0x00
			LegoU32 m_vertexCount;   // 0x90
			LegoU32 m_triangleCount; // 0x94
		};

		// SIZE 0x9c
		struct ModelSlot {
			GolModelBase* m_model; // 0x00
			ModelEntry m_entry;    // 0x04
		};

		void Destroy();
		void SetMaterialTable(MaterialTable* p_materialTable);
		LegoU8 SetColor(const ColorRGBA* p_color);
		void Start(LegoU32 p_durationMs);
		void StartFade(LegoU32 p_durationMs);
		void Stop();
		void Update(LegoU32 p_elapsedMs);
		void AddSample(LegoU32 p_elapsedMs, GolVec3 p_position);
		void DrawOpaque(GolD3DRenderDevice* p_renderer);
		void DrawTransparent(GolD3DRenderDevice* p_renderer);
		void BakeSegment();
		void WeldVertices();
		LegoU32 GetDurationMs() const { return m_durationMs; }
		LegoU8 GetFlags() const { return m_flags; }
		LegoBool32 IsActive() const { return m_flags & c_active; }
		void SetWidth(LegoFloat p_width) { m_width = p_width; }

	private:
		friend class RaceDecalManager;

		void Initialize(GolD3DRenderDevice* p_renderer, GolExport* p_golExport, GolCollidableEntity* p_params);

		Decal m_decal;                       // 0x004
		ModelSlot m_slots[3];                // 0x120
		GolExport* m_golExport;              // 0x2f4
		GolCollidableEntity* m_collidable;   // 0x2f8
		LegoFloat m_anchorX;                 // 0x2fc
		LegoFloat m_anchorY;                 // 0x300
		LegoFloat m_anchorZ;                 // 0x304
		LegoFloat m_lastX;                   // 0x308
		LegoFloat m_lastY;                   // 0x30c
		LegoFloat m_lastZ;                   // 0x310
		LegoU32 m_durationMs;                // 0x314
		LegoU32 m_segmentMs;                 // 0x318
		LegoU32 m_elapsedMs;                 // 0x31c
		LegoU32 m_slotIndex;                 // 0x320
		LegoFloat m_width;                   // 0x324
		LegoU8 m_flags;                      // 0x328
		undefined m_unk0x329[0x32c - 0x329]; // 0x329
		LegoU32 m_alpha;                     // 0x32c
		LegoFloat m_alphaScale;              // 0x330

		void Reset();
	};

	LegoU32 DrawOpaque(GolD3DRenderDevice* p_renderer);
	LegoU32 DrawTransparent(GolD3DRenderDevice* p_renderer);
	void Initialize(
		GolD3DRenderDevice* p_renderer,
		GolExport* p_golExport,
		GolCollidableEntity* p_params,
		LegoU32 p_count
	);
	Trail* AcquireTrail(LegoU32 p_durationMs);
	void ReleaseTrail(Trail* p_item, LegoU32 p_fadeMs);
	void StopAll();
	void Update(LegoU32 p_elapsedMs);

private:
	Trail* m_items;  // 0x04
	LegoU32 m_count; // 0x08
};

#endif // RACEDECALMANAGER_H

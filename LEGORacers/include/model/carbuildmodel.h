#ifndef CARBUILDMODEL_H
#define CARBUILDMODEL_H

#include "decomp.h"
#include "gdbmodelindexarray.h"
#include "gdbvertexarray.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "model/legopiecelibrary.h"
#include "types.h"

class GolD3DRenderDevice;
class GolExport;
class GolModelBase;
class LegoColorTable;
class GolMaterialLibrary;
class GolTextureList;

// SIZE 0x2030
class CarBuildModel {
public:
	// SIZE 0x30
	class Placement {
	public:
		Placement();
		~Placement();

		void Reset();
		void Destroy();
		void FUN_004513d0(CarBuildModel* p_buildModel);
		void SetPiece(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_colorRecordIndex, LegoS32 p_partType);
		void ClampToGrid();
		void Rotate();
		void MoveX(LegoS32 p_delta);
		void MoveY(LegoS32 p_delta);
		void GetPlacement(LegoS32* p_x, LegoS32* p_y, LegoS32* p_rotation);
		void SetPlacement(LegoS32 p_x, LegoS32 p_y, LegoS32 p_rotation, LegoS32 p_anchor);
		LegoPieceLibrary::PieceRecord* GetPieceRecord() const { return m_pieceRecord; }
		LegoS32 GetColorRecordIndex() const { return m_colorRecordIndex; }
		LegoS32 GetPartType() const { return m_partType; }

	private:
		void ToGridPosition();
		void FromGridPosition();
		void SetAnchor(LegoS32 p_anchor);
		void SelectAnchorQuadrant();
		void MoveRight();
		void MoveLeft();
		void MoveForward();
		void MoveBackward();

		undefined4 m_unk0x00;                         // 0x00
		LegoS32 m_x;                                  // 0x04
		LegoS32 m_y;                                  // 0x08
		LegoPieceLibrary::PieceRecord* m_pieceRecord; // 0x0c
		LegoS32 m_colorRecordIndex;                   // 0x10
		LegoS32 m_partType;                           // 0x14
		LegoS32 m_gridX;                              // 0x18
		LegoS32 m_gridY;                              // 0x1c
		LegoS32 m_width;                              // 0x20
		LegoS32 m_height;                             // 0x24
		LegoS32 m_rotation;                           // 0x28
		LegoS32 m_anchor;                             // 0x2c
	};

	struct PieceGrid;

	// SIZE 0x18
	struct PieceList {
		// SIZE 0x1c
		struct Entry {
			void GetPlacement(LegoS32* p_x, LegoS32* p_y, LegoS32* p_height, LegoS32* p_rotation);
			void SetPlacement(LegoS32 p_x, LegoS32 p_y, LegoS32 p_height, LegoS32 p_rotation);

			LegoPieceLibrary::PieceRecord* m_pieceRecord; // 0x00
			LegoS32 m_colorRecordIndex;                   // 0x04
			LegoS32 m_partType;                           // 0x08
			LegoS32 m_rotation;                           // 0x0c
			LegoS32 m_x;                                  // 0x10
			LegoS32 m_y;                                  // 0x14
			LegoS32 m_height;                             // 0x18
		};

		PieceList();
		~PieceList();
		void Clear();
		LegoBool32 Initialize(LegoS32 p_capacity);
		LegoS32 AddEntry(
			LegoPieceLibrary::PieceRecord* p_pieceRecord,
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_rotation,
			LegoS32 p_colorRecordIndex,
			LegoS32 p_partType,
			LegoS32 p_height
		);
		LegoBool32 RemoveEntry(LegoS32 p_index);
		LegoBool32 RebuildGrid();
		void SetVariant(LegoS32 p_variant, LegoBool32 p_force);
		LegoS32 ReadU16();
		void WriteU16(LegoS32 p_value);
		LegoBool32 Deserialize(LegoU8* p_source, LegoPieceLibrary* p_pieceLibrary, LegoS32 p_maxHeight);
		void Serialize(LegoU8* p_dest);
		void RemoveAllEntries();

		LegoS32 m_variant;      // 0x00
		LegoS32 m_capacity;     // 0x04
		LegoS32 m_entryCount;   // 0x08
		Entry* m_entries;       // 0x0c
		PieceGrid* m_pieceGrid; // 0x10
		LegoU8* m_cursor;       // 0x14
	};

	// SIZE 0x14
	struct PieceGrid {
		typedef void (*CellCallback)(
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_height,
			LegoS32 p_colorRecordIndex,
			LegoS32 p_delta
		);

		// SIZE 0x0c
		struct Cell {
			void Reset();
			void SetOccupied(LegoU8 p_cellFlags)
			{
				if (p_cellFlags & 0x80) {
					m_occupied = TRUE;
				}
				else {
					m_occupied = FALSE;
				}
			}

			LegoS32 m_entryIndex; // 0x00
			LegoS32 m_height;     // 0x04
			LegoBool m_occupied;  // 0x08
			LegoU8 m_unk0x09;     // 0x09
		};

		PieceGrid();
		~PieceGrid();
		void Clear();
		LegoBool32 Initialize(LegoS32 p_width, LegoS32 p_height);
		void ResetEntries();
		void StampPiece(
			LegoPieceLibrary::PieceRecord* p_pieceRecord,
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_rotation,
			LegoS32 p_height,
			LegoS32 p_entryIndex
		);
		LegoS32 FindPlacementHeight(
			LegoPieceLibrary::PieceRecord* p_pieceRecord,
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_rotation,
			LegoBool32 p_allowEmpty
		);
		LegoS32 HasCollision(
			LegoPieceLibrary::PieceRecord* p_pieceRecord,
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_rotation,
			LegoS32 p_height
		);
		void MarkOverlayCells(
			CarBuildModel* p_model,
			LegoPieceLibrary::PieceRecord* p_pieceRecord,
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_rotation,
			LegoS32 p_height
		);
		LegoBool32 AddPiece(
			LegoPieceLibrary::PieceRecord* p_pieceRecord,
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_rotation,
			LegoS32 p_colorRecordIndex,
			LegoS32 p_partType,
			LegoBool32 p_allowEmpty
		);
		void ForEachOccupiedCell(CellCallback p_callback);
		void RebuildGridWithCallback(CellCallback p_callback);
		LegoPieceLibrary::PieceRecord* UnstampPiece(LegoS32 p_index);
		LegoPieceLibrary::PieceRecord* RemovePiece(LegoS32 p_index);

		LegoS32 m_width;             // 0x00
		LegoS32 m_height;            // 0x04
		Cell* m_entries;             // 0x08
		PieceList* m_pieceList;      // 0x0c
		CellCallback m_cellCallback; // 0x10
	};

	// SIZE 0x28
	struct BuildVertex {
		BuildVertex* m_parent;       // 0x00
		BuildVertex* m_left;         // 0x04
		BuildVertex* m_right;        // 0x08
		LegoU16 m_index;             // 0x0c
		LegoBool m_treeBlack;        // 0x0e
		LegoS8 m_normalX;            // 0x0f
		LegoS8 m_normalY;            // 0x10
		LegoS8 m_normalZ;            // 0x11
		GolVec3 m_position;          // 0x14
		GolVec2 m_textureCoordinate; // 0x20
	};

	// SIZE 0x10
	struct BuildPrimitive {
		LegoU8 m_vertexCount;       // 0x00
		LegoU8 m_flags;             // 0x01
		LegoU16 m_materialIndex;    // 0x02
		LegoU16 m_partIndex;        // 0x04
		LegoU16 m_commandFlags;     // 0x06
		LegoU16 m_vertexIndices[4]; // 0x08
	};

	// SIZE 0x18
	struct BuildPrimitiveBounds {
		LegoFloat m_minX; // 0x00
		LegoFloat m_maxX; // 0x04
		LegoFloat m_minY; // 0x08
		LegoFloat m_maxY; // 0x0c
		LegoFloat m_minZ; // 0x10
		LegoFloat m_maxZ; // 0x14
	};

	// SIZE 0x04
	struct VertexUse {
		LegoU16 m_referenceCount; // 0x00
		LegoBool m_inBatch;       // 0x02
	};

	// SIZE 0x01
	struct OverlayCell {
		LegoU8 m_flags; // 0x00
	};

	CarBuildModel();
	~CarBuildModel();
	LegoBool32 IsInitialized();
	LegoBool32 Initialize(
		GolExport* p_golExport,
		GolD3DRenderDevice* p_renderer,
		LegoPieceLibrary* p_pieceLibrary,
		LegoColorTable* p_colorTable
	);
	void FindHighBasePiece();
	void AcquireBuffers();
	void ReleaseBuffers();
	void InitializeModel(GolModelBase* p_model);
	void Destroy();
	LegoBool32 PlacePiece(
		LegoPieceLibrary::PieceRecord* p_pieceRecord,
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_rotation,
		LegoS32 p_colorRecordIndex,
		LegoS32 p_partType
	);
	LegoS32 TestPlacement(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_x, LegoS32 p_y, LegoS32 p_rotation);
	LegoS32 BuildPieceModel(
		GolModelEntity* p_entity,
		LegoPieceLibrary::PieceRecord* p_pieceRecord,
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_height,
		LegoS32 p_rotation,
		LegoS32 p_colorRecordIndex,
		LegoS32 p_partType
	);
	void CenterOnPiece(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_rotation);
	void UpdateOffset(LegoBool32 p_restoreCachedOffset);
	void RebuildModel(LegoS32 p_variant, LegoU32 p_buildFlags);
	void BuildIntoModel(GolModelBase* p_model, undefined4 p_variant, undefined4 p_buildFlags);
	void GetPieceInfo(
		LegoS32 p_index,
		LegoPieceLibrary::PieceRecord** p_pieceRecord,
		LegoS32* p_x,
		LegoS32* p_y,
		LegoS32* p_height,
		LegoS32* p_rotation,
		LegoS32* p_colorRecordIndex,
		LegoS32* p_partType
	);
	LegoS32 GetPiecePartType(LegoS32 p_index) const;
	LegoPieceLibrary::PieceRecord* RemovePiece(LegoS32 p_index);
	void RemoveLastPiece();
	void DrawOverlay(GolD3DRenderDevice* p_renderer, LegoFloat p_zOffset);
	void MarkOverlayCell(LegoS32 p_x, LegoS32 p_y);
	void RefreshOverlay(Placement* p_placement, GolModelEntity* p_entity);
	LegoS32 ComputeHighPieceCentroid(LegoFloat* p_centroidX, LegoFloat* p_centroidY, LegoFloat* p_centroidZ);
	LegoBool32 Deserialize(LegoU8* p_source);
	void Serialize(LegoU8* p_dest);
	void ExportModel(GolModelBase* p_model, GolMaterialLibrary* p_materials, GolTextureList* p_textures);
	GolModelBase* GetModel() const { return m_modelEntity.GetModel(0); }
	LegoS32 GetPlacedPieceCount() const { return m_placedPieceCount; }
	GolModelEntity* GetModelEntity() { return &m_modelEntity; }
	GolModelEntity* GetOverlayEntity() { return &m_overlayEntity; }
	PieceList& GetPieceList() { return m_pieceList; }
	void SetPlacedPieceCount(LegoS32 p_count) { m_placedPieceCount = p_count; }
	LegoU8 GetBuildStatus() const { return m_buildStatus; }
	undefined4 GetFinalMaterialCount() const { return m_finalMaterialCount; }
	undefined4 GetFinalTextureCount() const { return m_finalTextureCount; }
	undefined4 GetFinalGroupCount() const { return m_finalGroupCount; }
	undefined4 GetFinalTriangleCount() const { return m_finalTriangleCount; }
	undefined4 GetFinalVertexCount() const { return m_finalVertexCount; }
	LegoS32 GetOverlayHeight() const { return m_overlayHeight; }

	enum {
		c_indexCommandModeMask = 0x3000,
		c_indexCommandTextured = 0x1000,
		c_indexCommandQuad = 0x2000,
		c_buildVertexCapacity = 7500,
		c_buildPrimitiveCapacity = 2500,
		c_modelTriangleCapacity = 2502,
		c_modelGroupCapacity = 1610,
		c_modelBatchVertexCapacity = 64,
		c_modelMaterialGroup = 0x80000000,
		c_buildPrimitiveFlagAllBlack = 0x01,
		c_buildPrimitiveFlagSameX = 0x02,
		c_buildPrimitiveFlagSameY = 0x04,
		c_buildPrimitiveFlagSameZ = 0x08,
		c_buildPrimitiveFlagParallelogram = 0x80,
		c_buildPrimitiveInitialFlags = 0x0f,
		c_buildPrimitiveCommandMask = 0x0fff,
		c_buildPrimitiveCommandMaterial1 = 0x0001,
		c_buildPrimitiveCommandMaterial2 = 0x0002,
		c_buildPrimitiveCommandTextureBit = 0x0800,
		c_buildAxisX = 0,
		c_buildAxisY = 1,
		c_buildAxisZ = 2,
		c_buildStatusOverflow = 0x01,
		c_finalizePostSortFlag = 0x01,
		c_finalizeResolveIntersectionsFlag = 0x02,
		c_finalizeCullSingleMaterialFlag = 0x10,
		c_overlayCellNeighborPosY = 0x01,
		c_overlayCellNeighborPosX = 0x02,
		c_overlayCellNeighborNegY = 0x04,
		c_overlayCellNeighborNegX = 0x08,
		c_overlayCellFlagOccupied = 0x10,
		c_overlayCellFlagDraw = 0x20,
		c_overlayCellFlagOccupiedDraw = c_overlayCellFlagOccupied | c_overlayCellFlagDraw,
	};

private:
	void Reset();
	void AllocateBuffers();
	void FreeBuffers();
	void SetColorTable(LegoColorTable* p_colorTable);
	void BeginModelWrite(GolModelBase* p_model);
	void FlushBatch(GolModelBase* p_model);
	void EndModelWrite(GolModelBase* p_model);
	LegoS32 ResetBuildVertexTree();
	LegoS32 AddBuildVertex(BuildVertex* p_vertex);
	static BuildVertex* InsertOrFindBuildVertex(BuildVertex** p_root, BuildVertex* p_vertex);
	static LegoS32 __fastcall CompareBuildVertex(const BuildVertex* p_lhs, const BuildVertex* p_rhs);
	static void __fastcall RebalanceBuildVertexInsert(BuildVertex** p_root, BuildVertex* p_vertex);
	static void __fastcall RotateBuildVertexLeft(BuildVertex** p_root, BuildVertex* p_vertex);
	static void __fastcall RotateBuildVertexRight(BuildVertex** p_root, BuildVertex* p_vertex);
	LegoS32 GetBatchVertexIndex(LegoS32 p_vertexIndex);
	static LegoS32 ComparePrimitiveDrawOrder(const void* p_lhs, const void* p_rhs);
	static void GetBuildPrimitiveBounds(BuildPrimitive* p_primitive, BuildPrimitiveBounds* p_bounds);
	LegoS32 ResolvePrimitiveIntersections();
	static void InterpolateBuildVertex(
		BuildVertex* p_dest,
		BuildVertex* p_left,
		BuildVertex* p_right,
		LegoFloat p_leftScale,
		LegoFloat p_rightScale
	);
	LegoS32 BuildBatches(LegoS8 p_buildFlags);
	static void AddHighBasePieceCallback(
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_height,
		LegoS32 p_colorRecordIndex,
		LegoS32 p_delta
	);
	static LegoS32 ComparePrimitiveMaterial(const void* p_lhs, const void* p_rhs);
	LegoS16 EmitPieceGeometry(
		LegoPieceLibrary::PieceRecord* p_pieceRecord,
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_rotation,
		LegoS32 p_height,
		LegoS32 p_colorRecordIndex,
		LegoU16 p_partIndex
	);
	LegoS16 EmitCellGeometry(
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_height,
		LegoS32 p_colorRecordIndex,
		LegoS32 p_materialIndex
	);
	void FinalizeBuild(LegoU8 p_buildFlags);
	void EmitPrimitiveToModel(GolModelEntity* p_entity, BuildPrimitive* p_primitive);
	void EmitPrimitives(GolModelEntity* p_entity);
	void ComputePieceBounds(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_rotation);
	void SetOffset(LegoFloat p_offsetX, LegoFloat p_offsetY, LegoFloat p_offsetZ);
	void SetDefaultOffset();
	LegoS32 GetCellEntryIndex(LegoS32 p_x, LegoS32 p_y) const;
	void BuildOverlay(LegoBool32 p_visible, LegoS32 p_height);

	GolExport* m_golExport;                                        // 0x0000
	GolD3DRenderDevice* m_renderer;                                // 0x0004
	GolModelBase* m_model;                                         // 0x0008
	GolModelEntity m_modelEntity;                                  // 0x000c
	LegoColorTable* m_colorTable;                                  // 0x009c
	LegoPieceLibrary* m_pieceLibrary;                              // 0x00a0
	PieceList m_pieceList;                                         // 0x00a4
	PieceGrid m_pieceGrid;                                         // 0x00bc
	undefined4 m_unk0xd0;                                          // 0x00d0
	LegoS32 m_placedPieceCount;                                    // 0x00d4
	LegoBool m_hasHighBasePiece;                                   // 0x00d8
	LegoBool m_savedHasHighBasePiece;                              // 0x00d9
	LegoBool m_baseTextureEnabled;                                 // 0x00da
	LegoBool m_applyBaseTexture;                                   // 0x00db
	LegoU8 m_buildStatus;                                          // 0x00dc
	LegoU16 m_buildFlags;                                          // 0x00de
	LegoPieceLibrary::PieceRecord* m_highBasePiece;                // 0x00e0
	LegoU8 m_batchVertexSlotByBuildVertex[c_buildVertexCapacity];  // 0x00e4
	BuildVertex* m_buildVertices;                                  // 0x1e30
	BuildPrimitive* m_buildPrimitives;                             // 0x1e34
	BuildPrimitive** m_buildPrimitiveOrder;                        // 0x1e38
	LegoU16 m_batchBuildVertexIndices[c_modelBatchVertexCapacity]; // 0x1e3c
	LegoS32 m_buildPrimitiveCount;                                 // 0x1ebc
	LegoS32 m_buildVertexCount;                                    // 0x1ec0
	BuildVertex* m_buildVertexTreeRoot;                            // 0x1ec4
	LegoU32 m_currentMaterialIndex;                                // 0x1ec8
	LegoU32 m_modelGroupCount;                                     // 0x1ecc
	LegoU32 m_modelVertexCount;                                    // 0x1ed0
	LegoU32 m_modelTriangleCount;                                  // 0x1ed4
	LegoU32 m_batchFirstVertex;                                    // 0x1ed8
	LegoU32 m_batchFirstTriangle;                                  // 0x1edc
	LegoS32 m_batchVertexCount;                                    // 0x1ee0
	LegoU32 m_batchTriangleCount;                                  // 0x1ee4
	LegoU32 m_finalMaterialCount;                                  // 0x1ee8
	LegoU32 m_finalTextureCount;                                   // 0x1eec
	LegoU32 m_finalGroupCount;                                     // 0x1ef0
	LegoU32 m_finalTriangleCount;                                  // 0x1ef4
	LegoU32 m_finalVertexCount;                                    // 0x1ef8
	GdbVertexArray* m_modelVertices;                               // 0x1efc
	GdbModelIndexArray::Indices* m_modelTriangles;                 // 0x1f00
	LegoFloat m_offsetX;                                           // 0x1f04
	LegoFloat m_offsetY;                                           // 0x1f08
	LegoFloat m_offsetZ;                                           // 0x1f0c
	LegoFloat m_cachedOffsetX;                                     // 0x1f10
	LegoFloat m_cachedOffsetY;                                     // 0x1f14
	LegoFloat m_cachedOffsetZ;                                     // 0x1f18
	LegoFloat m_pieceMinX;                                         // 0x1f1c
	LegoFloat m_pieceMaxX;                                         // 0x1f20
	LegoFloat m_pieceMinY;                                         // 0x1f24
	LegoFloat m_pieceMaxY;                                         // 0x1f28
	LegoFloat m_pieceMinZ;                                         // 0x1f2c
	LegoFloat m_pieceMaxZ;                                         // 0x1f30
	GolModelEntity m_overlayEntity;                                // 0x1f34
	GolModelBase* m_overlayModel;                                  // 0x1fc4
	OverlayCell m_overlayCells[12][8];                             // 0x1fc8
	LegoS32 m_overlayHeight;                                       // 0x2028
	undefined4 m_overlayVisible;                                   // 0x202c
};

#endif // CARBUILDMODEL_H

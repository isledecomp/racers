#ifndef CARBUILDMODEL_H
#define CARBUILDMODEL_H

#include "decomp.h"
#include "gdbmodelindexarray0xc.h"
#include "gdbvertexarray0xc.h"
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
		void FUN_004513d0(CarBuildModel* p_unk0x04);
		void SetPiece(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_colorRecordIndex, LegoS32 p_partType);
		void FUN_00499a60();
		void Rotate();
		void FUN_00499c20(LegoS32 p_delta);
		void FUN_00499c60(LegoS32 p_delta);
		void GetPlacement(LegoS32* p_x, LegoS32* p_y, LegoS32* p_rotation);
		void SetPlacement(LegoS32 p_x, LegoS32 p_y, LegoS32 p_rotation, LegoS32 p_anchor);
		LegoPieceLibrary::PieceRecord* GetPieceRecord() const { return m_pieceRecord; }
		LegoS32 GetColorRecordIndex() const { return m_colorRecordIndex; }
		LegoS32 GetPartType() const { return m_partType; }

	private:
		void FUN_00499570();
		void FUN_00499640();
		void SetAnchor(LegoS32 p_anchor);
		void FUN_004997e0();
		void FUN_00499b40();
		void FUN_00499b90();
		void FUN_00499bb0();
		void FUN_00499c00();

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
		struct Entry0x1c {
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
		LegoBool32 FUN_0049f930();
		void SetVariant(LegoS32 p_variant, LegoBool32 p_force);
		LegoS32 ReadU16();
		void WriteU16(LegoS32 p_value);
		LegoBool32 Deserialize(LegoU8* p_source, LegoPieceLibrary* p_pieceLibrary, LegoS32 p_maxHeight);
		void Serialize(LegoU8* p_dest);
		void FUN_0049fd60();

		LegoS32 m_variant;      // 0x00
		LegoS32 m_capacity;     // 0x04
		LegoS32 m_entryCount;   // 0x08
		Entry0x1c* m_entries;   // 0x0c
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
		struct Entry0x0c {
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

			LegoS32 m_entryIndex;                 // 0x00
			LegoS32 m_height;                     // 0x04
			LegoBool m_occupied;                  // 0x08
			LegoU8 m_unk0x09;                     // 0x09
			undefined m_padding0x0a[0x0c - 0x0a]; // 0x0a
		};

		PieceGrid();
		~PieceGrid();
		void Clear();
		LegoBool32 Initialize(LegoS32 p_width, LegoS32 p_height);
		void ResetEntries();
		void FUN_0049df40(
			LegoPieceLibrary::PieceRecord* p_pieceRecord,
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_rotation,
			LegoS32 p_height,
			LegoS32 p_entryIndex
		);
		LegoS32 FUN_0049e2d0(
			LegoPieceLibrary::PieceRecord* p_pieceRecord,
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_rotation,
			LegoBool32 p_allowEmpty
		);
		LegoS32 FUN_0049e450(
			LegoPieceLibrary::PieceRecord* p_pieceRecord,
			LegoS32 p_x,
			LegoS32 p_y,
			LegoS32 p_rotation,
			LegoS32 p_height
		);
		void FUN_0049e590(
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
		void FUN_0049e7c0(CellCallback p_callback);
		void FUN_0049e8c0(CellCallback p_callback);
		LegoPieceLibrary::PieceRecord* FUN_0049e8e0(LegoS32 p_index);
		LegoPieceLibrary::PieceRecord* FUN_0049e9e0(LegoS32 p_index);

		LegoS32 m_width;             // 0x00
		LegoS32 m_height;            // 0x04
		Entry0x0c* m_entries;        // 0x08
		PieceList* m_pieceList;      // 0x0c
		CellCallback m_cellCallback; // 0x10
	};

	// SIZE 0x28
	struct BuildVertex {
		BuildVertex* m_parent;         // 0x00
		BuildVertex* m_left;           // 0x04
		BuildVertex* m_right;          // 0x08
		LegoU16 m_index;               // 0x0c
		LegoBool m_treeBlack;          // 0x0e
		LegoS8 m_normalX;              // 0x0f
		LegoS8 m_normalY;              // 0x10
		LegoS8 m_normalZ;              // 0x11
		undefined m_padding0x12[0x02]; // 0x12
		GolVec3 m_position;            // 0x14
		GolVec2 m_textureCoordinate;   // 0x20
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
		undefined m_pad0x03;      // 0x03
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
		LegoColorTable* p_unk0x10
	);
	void FindHighBasePiece();
	void FUN_00499ee0();
	void FUN_00499f00();
	void FUN_00499eb0(GolModelBase* p_model);
	void Destroy();
	LegoBool32 FUN_0049a160(
		LegoPieceLibrary::PieceRecord* p_pieceRecord,
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_rotation,
		LegoS32 p_colorRecordIndex,
		LegoS32 p_partType
	);
	LegoS32 FUN_0049a1e0(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_x, LegoS32 p_y, LegoS32 p_rotation);
	LegoS32 FUN_0049b170(
		GolModelEntity* p_entity,
		LegoPieceLibrary::PieceRecord* p_pieceRecord,
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_height,
		LegoS32 p_rotation,
		LegoS32 p_colorRecordIndex,
		LegoS32 p_unk0x20
	);
	void FUN_0049b8b0(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_rotation);
	void FUN_0049b740(LegoBool32 p_restoreCachedOffset);
	void FUN_0049b920(LegoS32 p_variant, LegoU32 p_buildFlags);
	void FUN_0049bc60(GolModelBase* p_model, undefined4 p_unk0x08, undefined4 p_unk0x0c);
	void FUN_0049bce0(
		LegoS32 p_index,
		LegoPieceLibrary::PieceRecord** p_pieceRecord,
		LegoS32* p_x,
		LegoS32* p_y,
		LegoS32* p_height,
		LegoS32* p_rotation,
		LegoS32* p_colorRecordIndex,
		LegoS32* p_partType
	);
	LegoS32 FUN_0049bd50(LegoS32 p_index) const;
	LegoPieceLibrary::PieceRecord* FUN_0049bd70(LegoS32 p_index);
	void FUN_0049bdc0();
	void FUN_0049bdd0(GolD3DRenderDevice* p_renderer, LegoFloat p_unk0x08);
	void FUN_0049be50(LegoS32 p_x, LegoS32 p_y);
	void FUN_0049c230(Placement* p_placement, GolModelEntity* p_entity);
	LegoS32 FUN_0049c6a0(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08, LegoFloat* p_unk0x0c);
	LegoBool32 FUN_0049c7f0(LegoU8* p_source);
	void FUN_0049c820(LegoU8* p_dest);
	void FUN_0049c840(GolModelBase* p_model, GolMaterialLibrary* p_materials, GolTextureList* p_textures);
	GolModelBase* GetUnk0x84() const { return m_unk0x0c.GetModel(0); }
	LegoS32 GetPlacedPieceCount() const { return m_placedPieceCount; }
	GolModelEntity* GetUnk0x0c() { return &m_unk0x0c; }
	GolModelEntity* GetUnk0x1f34() { return &m_unk0x1f34; }
	PieceList& GetPieceList() { return m_pieceList; }
	void SetPlacedPieceCount(LegoS32 p_count) { m_placedPieceCount = p_count; }
	LegoU8 GetUnk0xdc() const { return m_unk0xdc; }
	undefined4 GetUnk0x1ee8() const { return m_unk0x1ee8; }
	undefined4 GetUnk0x1eec() const { return m_unk0x1eec; }
	undefined4 GetUnk0x1ef0() const { return m_unk0x1ef0; }
	undefined4 GetUnk0x1ef4() const { return m_unk0x1ef4; }
	undefined4 GetUnk0x1ef8() const { return m_unk0x1ef8; }
	LegoS32 GetUnk0x2028() const { return m_unk0x2028; }

	enum {
		c_indexCommandModeMask = 0x3000,
		c_indexCommandMode0x1000 = 0x1000,
		c_indexCommandMode0x2000 = 0x2000,
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
		c_overlayCellFlag0x01 = 0x01,
		c_overlayCellFlag0x02 = 0x02,
		c_overlayCellFlag0x04 = 0x04,
		c_overlayCellFlag0x08 = 0x08,
		c_overlayCellFlagOccupied = 0x10,
		c_overlayCellFlagDraw = 0x20,
		c_overlayCellFlagOccupiedDraw = c_overlayCellFlagOccupied | c_overlayCellFlagDraw,
	};

private:
	void Reset();
	void AllocateBuffers();
	void FreeBuffers();
	void FUN_00499e80(LegoColorTable* p_verdantTide);
	void FUN_0049a290(GolModelBase* p_model);
	void FUN_0049a300(GolModelBase* p_model);
	void FUN_0049a3e0(GolModelBase* p_model);
	LegoS32 FUN_00495020();
	LegoS32 AddBuildVertex(BuildVertex* p_vertex);
	static BuildVertex* InsertOrFindBuildVertex(BuildVertex** p_root, BuildVertex* p_vertex);
	static LegoS32 __fastcall CompareBuildVertex(const BuildVertex* p_lhs, const BuildVertex* p_rhs);
	static void __fastcall RebalanceBuildVertexInsert(BuildVertex** p_root, BuildVertex* p_vertex);
	static void __fastcall RotateBuildVertexLeft(BuildVertex** p_root, BuildVertex* p_vertex);
	static void __fastcall RotateBuildVertexRight(BuildVertex** p_root, BuildVertex* p_vertex);
	LegoS32 GetBatchVertexIndex(LegoS32 p_vertexIndex);
	static LegoS32 ComparePrimitiveDrawOrder(const void* p_lhs, const void* p_rhs);
	static void GetBuildPrimitiveBounds(BuildPrimitive* p_primitive, BuildPrimitiveBounds* p_bounds);
	LegoS32 FUN_00495440();
	static void InterpolateBuildVertex(
		BuildVertex* p_dest,
		BuildVertex* p_left,
		BuildVertex* p_right,
		LegoFloat p_leftScale,
		LegoFloat p_rightScale
	);
	LegoS32 FUN_00497360(LegoS8 p_buildFlags);
	static void AddHighBasePieceCallback(
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_height,
		LegoS32 p_colorRecordIndex,
		LegoS32 p_delta
	);
	static LegoS32 ComparePrimitiveMaterial(const void* p_lhs, const void* p_rhs);
	LegoS16 FUN_0049a450(
		LegoPieceLibrary::PieceRecord* p_pieceRecord,
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_rotation,
		LegoS32 p_height,
		LegoS32 p_colorRecordIndex,
		LegoU16 p_partIndex
	);
	LegoS16 FUN_0049ad30(LegoS32 p_x, LegoS32 p_y, LegoS32 p_height, LegoS32 p_colorRecordIndex, LegoS32 p_unk0x14);
	void FUN_00497690(LegoU8 p_unk0x04);
	void EmitPrimitiveToModel(GolModelEntity* p_entity, BuildPrimitive* p_primitive);
	void FUN_0049b100(GolModelEntity* p_entity);
	void FUN_0049b340(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_rotation);
	void FUN_0049b6f0(LegoFloat p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c);
	void FUN_0049b720();
	LegoS32 FUN_0049bcc0(LegoS32 p_x, LegoS32 p_y) const;
	void FUN_0049be70(LegoBool32 p_unk0x04, LegoS32 p_height);

	GolExport* m_golExport;                                        // 0x0000
	GolD3DRenderDevice* m_renderer;                                // 0x0004
	GolModelBase* m_model;                                         // 0x0008
	GolModelEntity m_unk0x0c;                                      // 0x000c
	LegoColorTable* m_verdantTide;                                 // 0x009c
	LegoPieceLibrary* m_pieceLibrary;                              // 0x00a0
	PieceList m_pieceList;                                         // 0x00a4
	PieceGrid m_pieceGrid;                                         // 0x00bc
	undefined4 m_unk0xd0;                                          // 0x00d0
	LegoS32 m_placedPieceCount;                                    // 0x00d4
	LegoBool m_hasHighBasePiece;                                   // 0x00d8
	LegoBool m_unk0xd9;                                            // 0x00d9
	LegoBool m_unk0xda;                                            // 0x00da
	LegoBool m_unk0xdb;                                            // 0x00db
	LegoU8 m_unk0xdc;                                              // 0x00dc
	undefined m_unk0xdd;                                           // 0x00dd
	LegoU16 m_unk0xde;                                             // 0x00de
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
	LegoU32 m_unk0x1ee8;                                           // 0x1ee8
	LegoU32 m_unk0x1eec;                                           // 0x1eec
	LegoU32 m_unk0x1ef0;                                           // 0x1ef0
	LegoU32 m_unk0x1ef4;                                           // 0x1ef4
	LegoU32 m_unk0x1ef8;                                           // 0x1ef8
	GdbVertexArray0xc* m_modelVertices;                            // 0x1efc
	GdbModelIndexArray0xc::Indices* m_modelTriangles;              // 0x1f00
	LegoFloat m_unk0x1f04;                                         // 0x1f04
	LegoFloat m_unk0x1f08;                                         // 0x1f08
	LegoFloat m_unk0x1f0c;                                         // 0x1f0c
	LegoFloat m_unk0x1f10;                                         // 0x1f10
	LegoFloat m_unk0x1f14;                                         // 0x1f14
	LegoFloat m_unk0x1f18;                                         // 0x1f18
	LegoFloat m_unk0x1f1c;                                         // 0x1f1c
	LegoFloat m_unk0x1f20;                                         // 0x1f20
	LegoFloat m_unk0x1f24;                                         // 0x1f24
	LegoFloat m_unk0x1f28;                                         // 0x1f28
	LegoFloat m_unk0x1f2c;                                         // 0x1f2c
	LegoFloat m_unk0x1f30;                                         // 0x1f30
	GolModelEntity m_unk0x1f34;                                    // 0x1f34
	GolModelBase* m_auxModel;                                      // 0x1fc4
	OverlayCell m_overlayCells[12][8];                             // 0x1fc8
	LegoS32 m_unk0x2028;                                           // 0x2028
	undefined4 m_unk0x202c;                                        // 0x202c
};

#endif // CARBUILDMODEL_H

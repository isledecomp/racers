#ifndef CARBUILDMODEL_H
#define CARBUILDMODEL_H

#include "decomp.h"
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
		void SetPiece(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_colorRecordIndex, LegoS32 p_unk0x0c);
		void FUN_00499a60();
		void Rotate();
		void FUN_00499c20(LegoS32 p_delta);
		void FUN_00499c60(LegoS32 p_delta);
		void GetPlacement(LegoS32* p_x, LegoS32* p_y, LegoS32* p_rotation);
		void SetPlacement(LegoS32 p_x, LegoS32 p_y, LegoS32 p_rotation, LegoS32 p_anchor);
		LegoPieceLibrary::PieceRecord* GetPieceRecord() const { return m_pieceRecord; }
		LegoS32 GetColorRecordIndex() const { return m_colorRecordIndex; }

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
		undefined4 m_unk0x14;                         // 0x14
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
	struct Field0x1e30Entry0x28 {
		undefined m_unk0x00[0x0c];        // 0x00
		LegoU16 m_index;                  // 0x0c
		undefined m_unk0x0e[0x28 - 0x0e]; // 0x0e
	};

	CarBuildModel();
	~CarBuildModel();
	LegoBool32 IsInitialized();
	void Initialize(
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
	void FUN_0049b170(
		GolModelEntity* p_entity,
		LegoPieceLibrary::PieceRecord* p_pieceRecord,
		undefined4 p_unk0x0c,
		undefined4 p_unk0x10,
		undefined4 p_unk0x14,
		undefined4 p_unk0x18,
		undefined4 p_unk0x1c,
		undefined4 p_unk0x20
	);
	void FUN_0049b8b0(LegoPieceLibrary::PieceRecord* p_pieceRecord, undefined4 p_unk0x08);
	void FUN_0049b740(undefined4 p_unk0x04);
	void FUN_0049b920(undefined4 p_unk0x04, undefined4 p_unk0x08);
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

private:
	void Reset();
	void AllocateBuffers();
	void FreeBuffers();
	void FUN_0049b720();

	GolExport* m_golExport;                         // 0x0000
	GolD3DRenderDevice* m_renderer;                 // 0x0004
	GolModelBase* m_model;                          // 0x0008
	GolModelEntity m_unk0x0c;                       // 0x000c
	LegoColorTable* m_verdantTide;                  // 0x009c
	LegoPieceLibrary* m_pieceLibrary;               // 0x00a0
	PieceList m_pieceList;                          // 0x00a4
	PieceGrid m_pieceGrid;                          // 0x00bc
	undefined4 m_unk0xd0;                           // 0x00d0
	LegoS32 m_placedPieceCount;                     // 0x00d4
	LegoU8 m_hasHighBasePiece;                      // 0x00d8
	undefined m_unk0xd9;                            // 0x00d9
	LegoBool m_unk0xda;                             // 0x00da
	undefined m_unk0xdb;                            // 0x00db
	LegoU8 m_unk0xdc;                               // 0x00dc
	undefined m_unk0xdd;                            // 0x00dd
	LegoU16 m_unk0xde;                              // 0x00de
	LegoPieceLibrary::PieceRecord* m_highBasePiece; // 0x00e0
	undefined m_unk0xe4[0x1e30 - 0x00e4];           // 0x00e4
	Field0x1e30Entry0x28* m_unk0x1e30;              // 0x1e30
	LegoU8* m_unk0x1e34;                            // 0x1e34
	LegoU8* m_unk0x1e38;                            // 0x1e38
	undefined m_unk0x1e3c[0x1ee8 - 0x1e3c];         // 0x1e3c
	undefined4 m_unk0x1ee8;                         // 0x1ee8
	undefined4 m_unk0x1eec;                         // 0x1eec
	undefined4 m_unk0x1ef0;                         // 0x1ef0
	undefined4 m_unk0x1ef4;                         // 0x1ef4
	undefined4 m_unk0x1ef8;                         // 0x1ef8
	undefined4 m_unk0x1efc;                         // 0x1efc
	undefined4 m_unk0x1f00;                         // 0x1f00
	LegoFloat m_unk0x1f04;                          // 0x1f04
	LegoFloat m_unk0x1f08;                          // 0x1f08
	LegoFloat m_unk0x1f0c;                          // 0x1f0c
	LegoFloat m_unk0x1f10;                          // 0x1f10
	LegoFloat m_unk0x1f14;                          // 0x1f14
	LegoFloat m_unk0x1f18;                          // 0x1f18
	undefined m_unk0x1f1c[0x1f34 - 0x1f1c];         // 0x1f1c
	GolModelEntity m_unk0x1f34;                     // 0x1f34
	GolModelBase* m_auxModel;                       // 0x1fc4
	undefined m_unk0x1fc8[0x1fd1 - 0x1fc8];         // 0x1fc8
	LegoU8 m_unk0x1fd1[0x2021 - 0x1fd1];            // 0x1fd1
	undefined m_unk0x2021[0x2028 - 0x2021];         // 0x2021
	LegoS32 m_unk0x2028;                            // 0x2028
	undefined4 m_unk0x202c;                         // 0x202c
};

#endif // CARBUILDMODEL_H

#ifndef CARBUILDMODEL_H
#define CARBUILDMODEL_H

#include "decomp.h"
#include "model/legopiecelibrary.h"
#include "scene/golbillboard.h"
#include "types.h"

class GolD3DRenderDevice;
class GolExport;
class GolModelBase;
class GolModelEntity;
class OpalHaven0xf4;
class LegoColorTable;

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

	struct Field0xbc;

	// SIZE 0x14
	struct Field0xa4 {
		// SIZE 0x1c
		struct Entry0x1c {
			undefined4 m_unk0x00;             // 0x00
			undefined4 m_unk0x04;             // 0x04
			LegoS32 m_unk0x08;                // 0x08
			undefined m_unk0x0c[0x1c - 0x0c]; // 0x0c
		};

		Field0xa4();
		~Field0xa4();
		void Clear();
		LegoBool32 Initialize(LegoS32 p_count);
		void FUN_0049fca0(LegoU8* p_dest);
		void FUN_0049fd60();

		undefined4 m_unk0x00; // 0x00
		LegoS32 m_count;      // 0x04
		undefined4 m_unk0x08; // 0x08
		Entry0x1c* m_entries; // 0x0c
		Field0xbc* m_unk0x10; // 0x10
	};

	// SIZE 0x14
	struct Field0xbc {
		// SIZE 0x0c
		struct Entry0x0c {
			void Reset();

			LegoS32 m_unk0x00;                    // 0x00
			undefined4 m_unk0x04;                 // 0x04
			LegoU8 m_unk0x08;                     // 0x08
			LegoU8 m_unk0x09;                     // 0x09
			undefined m_padding0x0a[0x0c - 0x0a]; // 0x0a
		};

		Field0xbc();
		~Field0xbc();
		void Clear();
		LegoBool32 Initialize(LegoS32 p_width, LegoS32 p_height);
		void ResetEntries();

		LegoS32 m_width;      // 0x00
		LegoS32 m_height;     // 0x04
		Entry0x0c* m_entries; // 0x08
		Field0xa4* m_unk0x0c; // 0x0c
		undefined4 m_unk0x10; // 0x10
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
	LegoBool32* GetUnk0x30() { return m_unk0x30; }
	void FUN_0049a160(
		LegoPieceLibrary::PieceRecord* p_pieceRecord,
		undefined4 p_unk0x08,
		undefined4 p_unk0x0c,
		undefined4 p_unk0x10,
		undefined4 p_unk0x14,
		undefined4 p_unk0x18
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
		LegoS32* p_anchor,
		LegoS32* p_rotation,
		LegoS32* p_unk0x20,
		LegoS32* p_unk0x24
	);
	LegoS32 FUN_0049bd50(LegoS32 p_index) const;
	void FUN_0049bdc0();
	void FUN_0049bdd0(GolD3DRenderDevice* p_renderer, LegoFloat p_unk0x08);
	void FUN_0049c230(Placement* p_placement, GolModelEntity* p_entity);
	void FUN_0049c7f0(LegoU8* p_source);
	void FUN_0049c820(LegoU8* p_dest);
	GolModelBase* GetUnk0x84() const { return m_unk0x84; }
	LegoS32 GetPlacedPieceCount() const { return m_placedPieceCount; }
	OpalHaven0xf4* GetUnk0x0c() { return reinterpret_cast<OpalHaven0xf4*>(&m_unk0x0c); }
	Field0xa4& GetUnk0xa4() { return m_unk0xa4; }
	void SetPlacedPieceCount(undefined4 p_unk0xd4) { m_placedPieceCount = p_unk0xd4; }
	LegoU8 GetUnk0xdc() const { return m_unk0xdc; }
	LegoS32 GetUnk0x2028() const { return m_unk0x2028; }

private:
	void Reset();
	void AllocateBuffers();
	void FreeBuffers();
	void FUN_0049b720();

	GolExport* m_golExport;                         // 0x0000
	GolD3DRenderDevice* m_renderer;                 // 0x0004
	GolModelBase* m_model;                          // 0x0008
	undefined4 m_unk0x0c;                           // 0x000c
	undefined4 m_unk0x10;                           // 0x0010
	GolModelBase* m_unk0x14[7];                     // 0x0014
	LegoBool32 m_unk0x30[7];                        // 0x0030
	undefined m_unk0x4c[0x0078 - 0x004c];           // 0x004c
	GolBillboard::Field0x2c* m_materialTable;       // 0x0078
	undefined m_unk0x7c[0x0084 - 0x007c];           // 0x007c
	GolModelBase* m_unk0x84;                        // 0x0084
	undefined m_unk0x88[0x009c - 0x0088];           // 0x0088
	LegoColorTable* m_verdantTide;                  // 0x009c
	LegoPieceLibrary* m_pieceLibrary;               // 0x00a0
	Field0xa4 m_unk0xa4;                            // 0x00a4
	undefined4 m_unk0xb8;                           // 0x00b8
	Field0xbc m_unk0xbc;                            // 0x00bc
	undefined4 m_unk0xd0;                           // 0x00d0
	undefined4 m_placedPieceCount;                  // 0x00d4
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
	undefined m_unk0x1e3c[0x1efc - 0x1e3c];         // 0x1e3c
	undefined4 m_unk0x1efc;                         // 0x1efc
	undefined4 m_unk0x1f00;                         // 0x1f00
	LegoFloat m_unk0x1f04;                          // 0x1f04
	LegoFloat m_unk0x1f08;                          // 0x1f08
	LegoFloat m_unk0x1f0c;                          // 0x1f0c
	LegoFloat m_unk0x1f10;                          // 0x1f10
	LegoFloat m_unk0x1f14;                          // 0x1f14
	LegoFloat m_unk0x1f18;                          // 0x1f18
	undefined m_unk0x1f1c[0x1fc4 - 0x1f1c];         // 0x1f1c
	GolModelBase* m_auxModel;                       // 0x1fc4
	undefined m_unk0x1fc8[0x2028 - 0x1fc8];         // 0x1fc8
	LegoS32 m_unk0x2028;                            // 0x2028
	undefined4 m_unk0x202c;                         // 0x202c
};

#endif // CARBUILDMODEL_H

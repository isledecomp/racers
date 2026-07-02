#ifndef RACESKY_H
#define RACESKY_H

#include "decomp.h"
#include "golmath.h"
#include "golname.h"
#include "golnametable.h"
#include "types.h"

class GolWorldDatabase;
class GolModelEntity;
class GolTextureList;
class GolCamera;
class GolD3DRenderDevice;
class GolFileParser;
class GolExport;
class MabMaterialAnimation0x14;
class MabMaterialAnimationItem0x18;
class MaterialTable0x0c;
class DuskwindBananaRelic0x24;
class RaceSession;

// Sky/backdrop state for a race (sky model + material animation swaps
// driven by track events).
// VTABLE: LEGORACERS 0x004afd58
// SIZE 0xc8
class RaceSkyState : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004afd64
	// SIZE 0x1fc
	class SkbTxtParser : public GolTxtParser {};

	// SIZE 0x10
	struct Entry {
		// SIZE 0x10
		struct Keyframe {
			LegoU32 m_unk0x00;   // 0x00
			ColorRGBA m_unk0x04; // 0x04
			ColorRGBA m_unk0x08; // 0x08
			ColorRGBA m_unk0x0c; // 0x0c
		};

		LegoU32 m_unk0x00;   // 0x00
		LegoU32 m_unk0x04;   // 0x04
		Keyframe* m_unk0x08; // 0x08
		LegoU32 m_unk0x0c;   // 0x0c
	};

	// SIZE 0x01
	class ModelBuilder {
	public:
		// SIZE 0x38
		struct Params {
			GolD3DRenderDevice* m_renderer;              // 0x00
			GolModelBase* m_model;                       // 0x04
			GolVec3 m_origin;                            // 0x08
			LegoFloat m_radius;                          // 0x14
			LegoU32 m_segmentCount;                      // 0x18
			LegoU32 m_hemisphere;                        // 0x1c
			LegoU32 m_hasTopCap;                         // 0x20
			LegoU32 m_hasBottomCap;                      // 0x24
			LegoU32 m_reverseWinding;                    // 0x28
			LegoU32 m_useTextureSeam;                    // 0x2c
			LegoU16 m_vertexType;                        // 0x30
			undefined2 m_unk0x32;                        // 0x32
			GdbModelIndexArray0xc* m_absoluteIndexArray; // 0x34
		};

		void FUN_004907d0(Params* p_params);
		void FUN_004907f0(Params* p_params);
		void FUN_004910e0(Params* p_params);
	};

	RaceSkyState();
	~RaceSkyState() override;
	void Clear() override;
	void FUN_0041c550(
		GolD3DRenderDevice* p_renderer,
		GolExport* p_golExport,
		const LegoChar* p_skyName,
		const LegoChar* p_worldName,
		LegoBool32 p_binary
	);
	void FUN_0041ccb0(LegoU32 p_elapsedMs);
	void FUN_0041d040(GolVec3* p_position);
	void FUN_0041d0f0(GolD3DRenderDevice* p_renderer);
	void FUN_0041d150(const LegoChar* p_name, LegoU32 p_durationMs);

	// SYNTHETIC: LEGORACERS 0x0041c490
	// RaceSkyState::`scalar deleting destructor'

public:
	friend class RaceEventTable;

	enum {
		c_flag0xc4Bit0 = 1 << 0,
		c_flag0xc4Bit1 = 1 << 1,
	};

	void Reset();
	void FUN_0041ce60(Entry* p_entry, ColorRGBA* p_unk0x08, ColorRGBA* p_unk0x0c, ColorRGBA* p_unk0x10);
	void FUN_0041cf20(const ColorRGBA* p_from, const ColorRGBA* p_to, ColorRGBA* p_result, LegoFloat p_amount);
	void FUN_0041cfc0(const ColorRGBA* p_unk0x04, const ColorRGBA* p_unk0x08, const ColorRGBA* p_unk0x0c);

	GolModelEntity m_unk0x0c;         // 0x0c
	GolWorldDatabase* m_unk0x9c;      // 0x9c
	GolModelBase* m_unk0xa0;          // 0xa0
	GolExport* m_unk0xa4;             // 0xa4
	Entry* m_entries;                 // 0xa8
	LegoFloat m_unk0xac;              // 0xac
	LegoU32 m_count;                  // 0xb0
	LegoU32 m_unk0xb4;                // 0xb4
	LegoU32 m_unk0xb8;                // 0xb8
	LegoU32 m_unk0xbc;                // 0xbc
	LegoU32 m_unk0xc0;                // 0xc0
	LegoU8 m_unk0xc4;                 // 0xc4
	ModelBuilder m_unk0xc5;           // 0xc5
	undefined m_unk0xc6[0xc8 - 0xc6]; // 0xc6
};

#endif // RACESKY_H

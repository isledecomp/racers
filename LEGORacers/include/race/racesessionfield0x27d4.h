#ifndef RACESESSIONFIELD0X27D4_H
#define RACESESSIONFIELD0X27D4_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "types.h"
#include "util/marblepath0x114.h"

class GolD3DRenderDevice;
class GolExport;
class GdbVertexArray0xc;
class GolModelBase;
struct ColorRGBA;

// VTABLE: LEGORACERS 0x004b478c
// SIZE 0x0c
class RaceSessionField0x27d4 {
public:
	RaceSessionField0x27d4();
	virtual ~RaceSessionField0x27d4(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x00492600
	// RaceSessionField0x27d4::`scalar deleting destructor'

	void Destroy();

	// SIZE 0x334
	class Item {
	public:
		// SIZE 0x11c
		class Field0x004 : public MarblePath0x114 {
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

			union FloatBits {
				LegoFloat m_float;
				LegoU32 m_bits;
			};

			union ProjectedCoordinates {
				struct {
					FloatBits m_x; // 0x000
					FloatBits m_y; // 0x004
				};
				GolVec2 m_vec; // 0x000
			};

			struct ProjectedVertex {
				GolVec3 m_position;               // 0x000
				ProjectedCoordinates m_projected; // 0x00c
				LegoU32 m_clipFlags;              // 0x014
				undefined4 m_unk0x018;            // 0x018
				undefined4 m_unk0x01c;            // 0x01c
			};

			struct Entry {
				undefined4 m_unk0x000; // 0x000
				undefined4 m_unk0x004; // 0x004
				undefined4 m_unk0x008; // 0x008
				Entry* m_unk0x00c;     // 0x00c
			};

			struct Field0x90 {
				void FUN_00403cc0(GolVec3* p_unk0x04, LegoU32 p_unk0x08);

				undefined m_unk0x000[0x024 - 0x000]; // 0x000
				Entry* m_unk0x024;                   // 0x024
			};

			struct Params {
				undefined m_unk0x000[0x078 - 0x000]; // 0x000
				GolModelBase* m_unk0x078;            // 0x078
				undefined m_unk0x07c[0x090 - 0x07c]; // 0x07c
				Field0x90* m_unk0x090;               // 0x090
			};

			void FUN_00414a30(Params* p_unk0x04);
			void FUN_00414a90(GolModelBase* p_unk0x04);
			void FUN_00414b30(GolModelBase* p_unk0x04, LegoU32 p_unk0x08, LegoU32 p_unk0x0c);
			void FUN_00414c00(GolModelBase* p_unk0x04);
			void FUN_00414c90(GolVec3* p_unk0x04, GolVec3* p_unk0x08);
			void FUN_00414d50();
			LegoU32 FUN_00414e40(LegoU32 p_unk0x04, LegoU32 p_unk0x08, LegoU32 p_unk0x0c);
			void FUN_00414f40(LegoU32 p_unk0x04, LegoU32 p_unk0x08);
			void FUN_00415810(ProjectedVertex* p_unk0x04, ProjectedVertex* p_unk0x08, ProjectedVertex* p_unk0x0c);
			void FUN_00415980();
			void FUN_00415a60();

		private:
			GdbVertexArray0xc* m_unk0x114; // 0x114
			LegoU8* m_unk0x118;            // 0x118
		};

		enum {
			c_flags0x328Bit0 = 1 << 0,
			c_flags0x328Bit1 = 1 << 1,
			c_flags0x328Bit2 = 1 << 2,
			c_flags0x328Bit3 = 1 << 3,
			c_flags0x328Bit4 = 1 << 4,
			c_flags0x328Bit5 = 1 << 5,
		};

		virtual void VTable0x00(undefined4 p_flags); // vtable+0x00

		// SIZE 0x9c
		struct ModelEntry : public GolModelEntity {
			LegoU32 m_unk0x90; // 0x90
			LegoU32 m_unk0x94; // 0x94
		};

		// SIZE 0x9c
		struct ModelSlot {
			GolModelBase* m_model; // 0x00
			ModelEntry m_entry;    // 0x04
		};

		~Item();
		void Destroy();
		LegoU8 FUN_00491d80(const ColorRGBA* p_color);
		void FUN_00491d90(LegoU32 p_unk0x04);
		void FUN_00491de0(LegoU32 p_unk0x04);
		void FUN_00491e10();
		void FUN_00491e20(LegoU32 p_elapsedMs);
		void FUN_004513d0(GolD3DRenderDevice* p_renderer);
		void FUN_00492180(GolD3DRenderDevice* p_renderer);
		void FUN_00492220();
		void FUN_00492470();
		LegoU8 GetFlags0x328() const { return m_flags0x328; }
		LegoBool32 IsActive() const { return m_flags0x328 & c_flags0x328Bit0; }

	private:
		friend class RaceSessionField0x27d4;

		Field0x004 m_unk0x004;               // 0x004
		ModelSlot m_unk0x120[3];             // 0x120
		GolExport* m_unk0x2f4;               // 0x2f4
		Field0x004::Params* m_unk0x2f8;      // 0x2f8
		undefined4 m_unk0x2fc;               // 0x2fc
		undefined4 m_unk0x300;               // 0x300
		undefined4 m_unk0x304;               // 0x304
		undefined4 m_unk0x308;               // 0x308
		undefined4 m_unk0x30c;               // 0x30c
		undefined4 m_unk0x310;               // 0x310
		LegoU32 m_unk0x314;                  // 0x314
		LegoU32 m_unk0x318;                  // 0x318
		LegoU32 m_unk0x31c;                  // 0x31c
		LegoU32 m_unk0x320;                  // 0x320
		LegoFloat m_unk0x324;                // 0x324
		LegoU8 m_flags0x328;                 // 0x328
		undefined m_unk0x329[0x32c - 0x329]; // 0x329
		LegoU32 m_unk0x32c;                  // 0x32c
		LegoFloat m_unk0x330;                // 0x330

		void Reset();
	};

	LegoU32 FUN_004928b0(GolD3DRenderDevice* p_renderer);
	LegoU32 FUN_004928f0(GolD3DRenderDevice* p_renderer);
	Item* FUN_004927c0(LegoU32 p_unk0x04);
	void FUN_00492820(Item* p_item, LegoU32 p_unk0x08);
	void FUN_00492840();
	void FUN_00492870(LegoU32 p_elapsedMs);

private:
	Item* m_items;   // 0x04
	LegoU32 m_count; // 0x08
};

#endif // RACESESSIONFIELD0X27D4_H

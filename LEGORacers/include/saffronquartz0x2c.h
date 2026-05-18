#ifndef SAFFRONQUARTZ0X2C_H
#define SAFFRONQUARTZ0X2C_H

#include "decomp.h"
#include "golnametable.h"
#include "rectangle.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GolExport;
class ZoweeBlubberworth0xf0;

// VTABLE: LEGORACERS 0x004af38c
// SIZE 0x2c
class SaffronQuartz0x2c : public GolNameTable {
public:
	// SIZE 0xb8
	class Frame0xb8 {
	public:
		class Resource {
		public:
			virtual void VTable0x00(undefined4) = 0; // vtable+0x00
		};

		Frame0xb8();
		~Frame0xb8();

		void Reset();
		void Destroy();
		void FUN_00406310();
		void FUN_00406330();
		void FUN_00406380();
		void FUN_00406390(undefined4 p_elapsedMs);
		void FUN_00406490(Rect* p_rect);
		void FUN_004064c0(BronzeFalcon0xc8770* p_renderer, undefined4 p_unk0x08);
		void FUN_004065a0(undefined4 p_unk0x04);
		void FUN_004065d0(LegoU32 p_unk0x04, LegoU32 p_unk0x08);
		void FUN_00406680(undefined4 p_unk0x04);
		void FUN_004066b0(undefined4 p_unk0x04);
		LegoU32 FUN_004066d0(undefined4 p_unk0x04);
		void FUN_00406710(undefined4 p_unk0x04);
		void FUN_00406760(undefined4 p_unk0x04);
		void FUN_00406770(undefined4 p_unk0x04);
		LegoU32 FUN_00406790(undefined4 p_unk0x04);
		void FUN_004067f0(undefined4 p_unk0x04);
		void FUN_00406860();
		undefined4 FUN_00406890();

		LegoU32 GetUnk0x44() const { return m_unk0x44; }
		LegoU32 GetUnk0x48() const { return m_unk0x48; }
		LegoU32 GetUnk0x58() const { return m_unk0x58; }

	private:
		undefined4 m_unk0x00;     // 0x00
		LegoU32 m_unk0x04;        // 0x04
		Resource* m_unk0x08;      // 0x08
		LegoU32 m_unk0x0c;        // 0x0c
		Resource* m_unk0x10;      // 0x10
		LegoU32 m_unk0x14;        // 0x14
		Resource* m_unk0x18;      // 0x18
		LegoU32 m_unk0x1c;        // 0x1c
		Resource* m_unk0x20;      // 0x20
		LegoU32 m_unk0x24;        // 0x24
		Resource* m_unk0x28;      // 0x28
		LegoU32 m_unk0x2c;        // 0x2c
		undefined4** m_unk0x30;   // 0x30
		LegoU32 m_unk0x34;        // 0x34
		undefined4** m_unk0x38;   // 0x38
		LegoU32 m_unk0x3c;        // 0x3c
		undefined4* m_unk0x40;    // 0x40
		LegoU32 m_unk0x44;        // 0x44
		LegoU32 m_unk0x48;        // 0x48
		LegoU32 m_unk0x4c;        // 0x4c
		LegoU32 m_unk0x50;        // 0x50
		LegoU32 m_unk0x54;        // 0x54
		LegoU32 m_unk0x58;        // 0x58
		LegoU32 m_unk0x5c;        // 0x5c
		undefined4* m_unk0x60[8]; // 0x60
		undefined4 m_unk0x80;     // 0x80
		LegoU32 m_unk0x84;        // 0x84
		undefined4* m_unk0x88[7]; // 0x88
		LegoFloat m_unk0xa4;      // 0xa4
		Rect m_unk0xa8;           // 0xa8
	};

	SaffronQuartz0x2c();
	~SaffronQuartz0x2c() override; // vtable+0x00
	void Clear() override;         // vtable+0x08

	void Reset();
	void FUN_00406980(
		GolExport* p_golExport,
		BronzeFalcon0xc8770* p_renderer,
		const LegoChar* p_fileName,
		undefined4 p_binary
	);
	void FUN_00406b90(undefined4 p_unk0x04);
	void FUN_00406c50(undefined4 p_unk0x04);
	void FUN_00406cb0(undefined4 p_unk0x04);
	undefined4 FUN_00406de0(const LegoChar* p_name);
	undefined4 FUN_00406e30(const LegoChar* p_name);
	undefined4 FUN_00406e80(const LegoChar* p_name);
	undefined4 FUN_00406ed0(const LegoChar* p_name);
	undefined4 FUN_00406f20(LegoU32 p_index, undefined4 p_unk0x08);
	undefined4 FUN_00406f40(LegoU32 p_index, undefined4 p_unk0x08);
	undefined4 FUN_00406f60(LegoU32 p_index, undefined4 p_unk0x08, undefined4 p_unk0x0c);
	LegoU32 FUN_00406f90(LegoFloat p_scale);

	void SetUnk0x0c(void* p_unk0x0c) { m_unk0x0c = p_unk0x0c; }
	LegoU32 GetFrameCount() const { return m_frameCount; }
	Frame0xb8* GetFrames() const { return m_frames; }

	// SYNTHETIC: LEGORACERS 0x004068f0
	// SaffronQuartz0x2c::`scalar deleting destructor'

private:
	void* m_unk0x0c;                   // 0x0c
	GolExport* m_golExport;            // 0x10
	BronzeFalcon0xc8770* m_renderer;   // 0x14
	LegoU32 m_unk0x18;                 // 0x18
	ZoweeBlubberworth0xf0** m_unk0x1c; // 0x1c
	LegoChar* m_unk0x20;               // 0x20
	LegoU32 m_frameCount;              // 0x24
	Frame0xb8* m_frames;               // 0x28
};

#endif // SAFFRONQUARTZ0X2C_H

#ifndef IMAGINARYTOOL0X368_H
#define IMAGINARYTOOL0X368_H

#include "compat.h"
#include "decomp.h"
#include "imaginarynotion0x290.h"
#include "porcelainveil0x50.h"

class MenuToolContext0x4bc8;
class MenuToolCreateParams0x30;
class ObscureVantage0x58;
class GolFont0xa0;
class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b3518
// SIZE 0x368
class ImaginaryTool0x368 : public ImaginaryNotion0x290 {
public:
	// VTABLE: LEGORACERS 0x004b3480
	// SIZE 0x60
	class FieldAt0x2e0 : public CeruleanQueen0x58 {
	public:
		FieldAt0x2e0();
		~FieldAt0x2e0() override;             // vtable+0x00
		void Clear() override;                // vtable+0x08
		void VTable0x0c() override;           // vtable+0x0c
		void VTable0x10(undefined4) override; // vtable+0x10
		void VTable0x14(undefined4) override; // vtable+0x14

		// SIZE 0xe0
		class Entry0xe0 {
		public:
			undefined m_unk0x00[0x38 - 0x00]; // 0x00
			LegoU8 m_unk0x38;                 // 0x38
			undefined m_unk0x39[0x52 - 0x39]; // 0x39
			LegoS8 m_unk0x52[6][4];           // 0x52
			undefined m_unk0x6a[0x74 - 0x6a]; // 0x6a
			undefined4 m_unk0x74;             // 0x74
			undefined4 m_unk0x78;             // 0x78
			undefined m_unk0x7c[0x84 - 0x7c]; // 0x7c
			GolFont0xa0* m_unk0x84[6];        // 0x84
			UtopianPan0xa4* m_unk0x9c[6];     // 0x9c
			LegoS8 m_unk0xb4[6][4];           // 0xb4
			undefined m_unk0xcc[0xd0 - 0xcc]; // 0xcc
			LegoS8 m_unk0xd0[4];              // 0xd0
			undefined m_unk0xd4[0xd8 - 0xd4]; // 0xd4
			undefined4 m_unk0xd8;             // 0xd8
			undefined4 m_unk0xdc;             // 0xdc
		};

		// SYNTHETIC: LEGORACERS 0x0047f0f0
		// ImaginaryTool0x368::FieldAt0x2e0::`scalar deleting destructor'

		// VTABLE: LEGORACERS 0x004b3498
		// SIZE 0x1fc
		class MidTxtParser : public GolTxtParser {};

	private:
		void FUN_00469b50(Entry0xe0* p_entry);
		void FUN_0047f2b0(Entry0xe0* p_entry);
		void FUN_0047f410();

		Entry0xe0* m_unk0x5c; // 0x5c
	};

	// SIZE 0x4
	class FieldAt0x350 {
	public:
		FieldAt0x350();

	private:
		LegoU8 m_unk0x00; // 0x00
		LegoU8 m_unk0x01; // 0x01
		LegoU8 m_unk0x02; // 0x02
		LegoU8 m_unk0x03; // 0x03
	};

	// SIZE 0x10
	class FieldAt0x340 {
	public:
		FieldAt0x340();

	private:
		FieldAt0x350 m_unk0x00; // 0x00
		LegoFloat m_unk0x04;    // 0x04
		LegoFloat m_unk0x08;    // 0x08
		LegoFloat m_unk0x0c;    // 0x0c
	};

	ImaginaryTool0x368();

	undefined4 VTable0x18(
		ObscureIcon0x1a8*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) override; // vtable+0x18
	undefined4 VTable0x1c(
		ObscureIcon0x1a8*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) override;                                 // vtable+0x1c
	void VTable0x34(undefined4) override;       // vtable+0x34
	void VTable0x3c(undefined4) override;       // vtable+0x3c
	void VTable0x40(undefined4) override;       // vtable+0x40
	void VTable0x54() override;                 // vtable+0x54
	CeruleanEmperor0x4c* VTable0x5c() override; // vtable+0x5c
	CeruleanQueen0x58* VTable0x64() override;   // vtable+0x64
	~ImaginaryTool0x368() override;             // vtable+0x68
	LegoFloat VTable0x6c() override;            // vtable+0x6c
	LegoBool32 VTable0x74() override;           // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override; // vtable+0x78
	virtual void VTable0x80();                  // vtable+0x80
	virtual void VTable0x84() = 0;              // vtable+0x84
	virtual LegoBool32 VTable0x88();            // vtable+0x88
	virtual LegoBool32 VTable0x8c(MenuToolContext0x4bc8*,
								  MenuToolCreateParams0x30*); // vtable+0x8c
	virtual void VTable0x90(undefined4);                      // vtable+0x90
	virtual void VTable0x94(undefined4);                      // vtable+0x94

	void FUN_00480470(MenuToolContext0x4bc8* p_context, undefined4 p_unk0x08, undefined4 p_unk0x0c);

	// SYNTHETIC: LEGORACERS 0x0047fb60
	// ImaginaryTool0x368::`scalar deleting destructor'

protected:
	PorcelainVeil0x50 m_unk0x290;      // 0x290
	FieldAt0x2e0 m_unk0x2e0;           // 0x2e0
	FieldAt0x340 m_unk0x340;           // 0x340
	FieldAt0x350 m_unk0x350;           // 0x350
	MenuToolContext0x4bc8* m_unk0x354; // 0x354
	undefined4 m_unk0x358;             // 0x358
	ObscureVantage0x58* m_unk0x35c;    // 0x35c
	LegoU16 m_unk0x360;                // 0x360
	LegoU16 m_unk0x362;                // 0x362
	LegoBool32 m_unk0x364;             // 0x364
};

#endif // IMAGINARYTOOL0X368_H

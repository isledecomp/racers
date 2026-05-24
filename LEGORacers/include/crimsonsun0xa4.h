#ifndef CRIMSONSUN0XA4_H
#define CRIMSONSUN0XA4_H

#include "ceruleanqueen0x58.h"
#include "decomp.h"
#include "imaginarydrillfieldat0x420.h"
#include "imaginarynotion0x290.h"
#include "menutoolcreateparams0x30.h"
#include "obscuretome0x3dc.h"
#include "types.h"

class CopperCrest0x40;
class PorcelainVeil0x50;

// SIZE 0xa4
class CrimsonSun0xa4 {
public:
	// VTABLE: LEGORACERS 0x004b2784
	// SIZE 0x78
	class FieldAt0x6c8 : public ImaginaryDrillFieldAt0x420 {
	public:
		FieldAt0x6c8();
		~FieldAt0x6c8() override;                         // vtable+0x04
		undefined4 VTable0x38(Rect*, Rect*) override;     // vtable+0x38
		void VTable0x40(GolString*, undefined4) override; // vtable+0x40

		// SYNTHETIC: LEGORACERS 0x0046f860
		// CrimsonSun0xa4::FieldAt0x6c8::`scalar deleting destructor'
	};

	// VTABLE: LEGORACERS 0x004b20e0
	// SIZE 0x74c
	class Entry0x74c : public ImaginaryNotion0x290 {
	public:
		// SIZE 0x18
		class CreateParams0x18 {
		public:
			MenuToolCreateParams0x30* m_createParams; // 0x00
			CrimsonSun0xa4* m_owner;                  // 0x04
			ImaginaryNotion0x290* m_eventHandler;     // 0x08
			undefined4 m_unk0x0c;                     // 0x0c
			undefined2 m_unk0x10;                     // 0x10
			undefined4 m_unk0x14;                     // 0x14
		};

		Entry0x74c();
		~Entry0x74c() override; // vtable+0x68
		undefined4 VTable0x18(
			ObscureVantage0x58*,
			OnyxCircularBuffer0x1c::Item*,
			undefined4,
			undefined4
		) override; // vtable+0x18
		undefined4 VTable0x1c(
			ObscureVantage0x58*,
			OnyxCircularBuffer0x1c::Item*,
			undefined4,
			undefined4
		) override;                                                 // vtable+0x1c
		void VTable0x38(ObscureVantage0x58*) override;              // vtable+0x38
		void VTable0x4c() override;                                 // vtable+0x4c
		undefined4 VTable0x50() override;                           // vtable+0x50
		void Reset() override;                                      // vtable+0x54
		CeruleanEmperor0x4c* GetMenuStyles() override;              // vtable+0x5c
		CeruleanQueen0x58* GetMenuInputBindings() override;         // vtable+0x64
		LegoBool32 VTable0x78(undefined4 p_elapsedMs) override;     // vtable+0x78
		LegoBool32 VTable0x7c(Rect* p_arg1, Rect* p_arg2) override; // vtable+0x7c

		// SYNTHETIC: LEGORACERS 0x00468bf0
		// CrimsonSun0xa4::Entry0x74c::`vector deleting destructor'

		LegoBool32 FUN_00468300(CreateParams0x18* p_createParams);
		void FUN_00468590();
		void FUN_004687a0();
		undefined4 GetUnk0x2c0() const;
		void SetUnk0x740(ObscureIcon0x1a8* p_unk0x740) { m_unk0x740 = p_unk0x740; }
		void SetUnk0x744(ObscureIcon0x1a8* p_unk0x744) { m_unk0x744 = p_unk0x744; }
		void SetUnk0x748(ObscureIcon0x1a8* p_unk0x748) { m_unk0x748 = p_unk0x748; }

	private:
		void FUN_00468390();
		void FUN_00468430();
		void FUN_004684e0();
		void FUN_004686f0();
		void FUN_00468740();

		CrimsonSun0xa4* m_unk0x290;          // 0x290
		CeruleanEmperor0x4c* m_unk0x294;     // 0x294
		ImaginaryNotion0x290* m_unk0x298;    // 0x298
		LegoS32 m_unk0x29c;                  // 0x29c
		LegoS32 m_unk0x2a0;                  // 0x2a0
		LegoFloat m_unk0x2a4;                // 0x2a4
		LegoFloat m_unk0x2a8;                // 0x2a8
		undefined2 m_unk0x2ac;               // 0x2ac
		undefined m_unk0x2ae[0x2b0 - 0x2ae]; // 0x2ae
		LegoU32 m_unk0x2b0;                  // 0x2b0
		LegoS32 m_unk0x2b4;                  // 0x2b4
		undefined4 m_unk0x2b8;               // 0x2b8
		undefined4 m_unk0x2bc;               // 0x2bc
		undefined4 m_unk0x2c0;               // 0x2c0
		undefined4 m_unk0x2c4;               // 0x2c4
		undefined4 m_unk0x2c8;               // 0x2c8
		ObscureTome0x3fc m_unk0x2cc;         // 0x2cc
		FieldAt0x6c8 m_unk0x6c8;             // 0x6c8
		ObscureIcon0x1a8* m_unk0x740;        // 0x740
		ObscureIcon0x1a8* m_unk0x744;        // 0x744
		ObscureIcon0x1a8* m_unk0x748;        // 0x748
	};

	CrimsonSun0xa4();
	~CrimsonSun0xa4();

	LegoS32 Reset();
	LegoS32 FUN_00468ab0();
	Entry0x74c* FUN_00468c50(
		undefined4 p_unk0x04,
		undefined2 p_unk0x08,
		ImaginaryNotion0x290* p_unk0x0c,
		undefined4 p_unk0x10
	);
	void FUN_00468cf0();
	void FUN_00468da0(LegoU32 p_unk0x04);
	void FUN_00468e20();
	LegoBool32 FUN_00468af0(MenuToolCreateParams0x30* p_createParams, LegoS32 p_count, CopperCrest0x40* p_copperCrest);
	LegoU32 GetUnk0x9c() const { return m_unk0x9c; }

private:
	void FUN_00468d20();

	CeruleanQueen0x58 m_unk0x00;             // 0x00
	MenuToolCreateParams0x30 m_createParams; // 0x5c
	Entry0x74c* m_entries;                   // 0x8c
	CopperCrest0x40* m_unk0x90;              // 0x90
	ImaginaryNotion0x290* m_unk0x94;         // 0x94
	LegoS32 m_count;                         // 0x98
	LegoU32 m_unk0x9c;                       // 0x9c
	undefined4 m_unk0xa0;                    // 0xa0
};

#endif // CRIMSONSUN0XA4_H

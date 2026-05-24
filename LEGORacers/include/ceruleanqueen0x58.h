#ifndef CERULEANQUEEN0X58_H
#define CERULEANQUEEN0X58_H

#include "ceruleanknight0x20.h"
#include "compat.h"
#include "decomp.h"
#include "goltxtparser.h"
#include "obscureanchor0x5c.h"
#include "obscureicon0x1a8.h"
#include "obscuretome0x3dc.h"
#include "types.h"
#include "visualstate0x4.h"

class BronzeFalcon0xc8770;
class GolFont0xa0;
class GolStringTable;
class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b2180
// SIZE 0x5c
class CeruleanQueen0x58 : public CeruleanKnight0x20 {
public:
	// VTABLE: LEGORACERS 0x004b2198
	// SIZE 0x1fc
	class MidTxtParser : public GolTxtParser {
		// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
		// CeruleanQueen0x58::MidTxtParser::`scalar deleting destructor'

		// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
		// CeruleanQueen0x58::MidTxtParser::~MidTxtParser
	};

	// SIZE 0x38
	class Entry0x38 : public ObscureVantage0x58::CreateParams0x30 {
	public:
		undefined m_unk0x30[0x38 - 0x30]; // 0x30
	};

	// SIZE 0x3c
	class Entry0x3c : public ObscureAnchor0x5c::CreateParams0x3c {};

	// SIZE 0x48
	class Entry0x48 : public ObscureVantage0x58::CreateParams0x30 {
	public:
		undefined4 m_unk0x30;      // 0x30
		undefined4 m_unk0x34;      // 0x34
		GolStringTable* m_unk0x38; // 0x38
		GolFont0xa0* m_unk0x3c;    // 0x3c
		undefined2 m_unk0x40;      // 0x40
		undefined m_unk0x42[2];    // 0x42
		undefined4 m_unk0x44;      // 0x44
	};

	// SIZE 0x60
	class Entry0x60 : public ObscureTome0x3fc::CreateParams0x60 {};

	// SIZE 0x84
	class Entry0x84 : public ObscureIcon0x1a8::CreateParams0x84 {};

	// SIZE 0x88
	class Entry0x88 : public ObscureVantage0x58::CreateParams0x30 {
	public:
		undefined m_unk0x30[0x38 - 0x30]; // 0x30
		LegoFloat m_unk0x38[9];           // 0x38
		LegoFloat m_unk0x5c;              // 0x5c
		LegoChar m_unk0x60[0x70 - 0x60];  // 0x60
		undefined4 m_unk0x70;             // 0x70
		LegoBool32 m_unk0x74;             // 0x74
		undefined4 m_unk0x78;             // 0x78
		undefined4 m_unk0x7c;             // 0x7c
		LegoFloat m_unk0x80;              // 0x80
		void* m_unk0x84;                  // 0x84
	};

	// SIZE 0x98
	class Entry0x98 : public Entry0x84 {
	public:
		void* m_unk0x84;      // 0x84
		void* m_unk0x88;      // 0x88
		void* m_unk0x8c;      // 0x8c
		undefined4 m_unk0x90; // 0x90
		undefined4 m_unk0x94; // 0x94
	};

	// SIZE 0x9c
	class Entry0x9c : public Entry0x84 {
	public:
		UtopianPan0xa4* m_unk0x84[6]; // 0x84
	};

	// SIZE 0xa0
	class Entry0xa0 : public Entry0x9c {
	public:
		UtopianPan0xa4* m_unk0x9c; // 0x9c
	};

	// SIZE 0xa0
	class Entry0xa0WithFont : public Entry0x84 {
	public:
		undefined m_unk0x84[0x8c - 0x84]; // 0x84
		GolFont0xa0* m_unk0x8c;           // 0x8c
		undefined m_unk0x90[0x94 - 0x90]; // 0x90
		undefined2 m_unk0x94;             // 0x94
		undefined2 m_unk0x96[4];          // 0x96
		undefined m_unk0x9e[0xa0 - 0x9e]; // 0x9e
	};

	// SIZE 0xb8
	class Entry0xb8 : public Entry0x84 {
	public:
		void* m_unk0x84;              // 0x84
		void* m_unk0x88;              // 0x88
		void* m_unk0x8c;              // 0x8c
		void* m_unk0x90;              // 0x90
		UtopianPan0xa4* m_unk0x94[6]; // 0x94
		undefined2 m_unk0xac;         // 0xac
		undefined2 m_unk0xae;         // 0xae
		undefined4 m_unk0xb0;         // 0xb0
		undefined4 m_unk0xb4;         // 0xb4
	};

	// SIZE 0xec
	class Entry0xec : public Entry0x84 {
	public:
		// SIZE 0x0c
		class ImageTriplet {
		public:
			UtopianPan0xa4* m_unk0x00; // 0x00
			UtopianPan0xa4* m_unk0x04; // 0x04
			UtopianPan0xa4* m_unk0x08; // 0x08
		};

		undefined4 m_unk0x84;      // 0x84
		GolFont0xa0* m_unk0x88[6]; // 0x88
		union {
			ImageTriplet m_unk0xa0[6];            // 0xa0
			UtopianPan0xa4* m_utopianunk0xa0[18]; // 0xa0
		};
		undefined4 m_unk0xe8; // 0xe8
	};

	// SIZE 0x54
	class Entry0x54 : public ObscureVantage0x58::CreateParams0x30 {
	public:
		undefined m_unk0x30[0x38 - 0x30]; // 0x30
		LegoChar m_unk0x38[0x48 - 0x38];  // 0x38
		undefined4 m_unk0x48;             // 0x48
		LegoU32 m_unk0x4c;                // 0x4c
		LegoFloat m_unk0x50;              // 0x50
	};

	// SIZE 0x74
	class Struct0x74 : public ObscureVantage0x58::CreateParams0x30 {
	public:
		undefined m_unk0x30[0x38 - 0x30]; // 0x30
		LegoS32 m_unk0x38;                // 0x38
		Rect* m_unk0x3c;                  // 0x3c
		LegoFloat m_unk0x40;              // 0x40
		undefined4 m_unk0x44;             // 0x44
		LegoFloat m_unk0x48[9];           // 0x48
		undefined m_unk0x6c[0x74 - 0x6c]; // 0x6c
	};

	// SIZE 0x0c
	struct ResourceLoadParams {
		BronzeFalcon0xc8770* m_renderer; // 0x00
		const LegoChar* m_fileName;      // 0x04
		undefined4 m_binary;             // 0x08
	};

	CeruleanQueen0x58();
	~CeruleanQueen0x58() override;        // vtable+0x00
	void Clear() override;                // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14
	LegoBool32 Load(ResourceLoadParams* p_params);
	Entry0x3c* GetEntry0x3c(const LegoChar* p_name) { return static_cast<Entry0x3c*>(FUN_0046aff0(p_name)); }
	Entry0x84* GetEntry0x84(const LegoChar* p_name) { return static_cast<Entry0x84*>(FUN_0046aff0(p_name)); }

	// SYNTHETIC: LEGORACERS 0x00469600
	// CeruleanQueen0x58::`scalar deleting destructor'

private:
	void FUN_00469900(ResourceLoadParams* p_params);
	void FUN_00469a20(ObscureVantage0x58::CreateParams0x30* p_entry);
	void FUN_00469c90(Entry0x98* p_entry);
	void FUN_00469d20(LegoFloat* p_floats);
	void FUN_00469d90(Entry0x3c* p_entry);
	void FUN_00469e20(Entry0x48* p_entry);
	void FUN_00469ee0(Entry0x60* p_entry);
	void FUN_00469fd0(Entry0x9c* p_entry);
	void FUN_0046a050(Entry0xec* p_entry);
	void FUN_0046a110(Entry0xa0* p_entry);
	void FUN_0046a190(Entry0x98* p_entry);
	void FUN_0046a1f0(Struct0x74* p_entry);
	void FUN_0046a310(Entry0xb8* p_entry);
	void FUN_0046a490(Entry0x88* p_entry);
	void FUN_0046a590(Entry0x54* p_entry);
	void FUN_0046a640(Entry0xa0WithFont* p_entry);
	void FUN_0046a750();
	void FUN_0046a800();
	void FUN_0046a8a0();
	void FUN_0046a940();
	void FUN_0046a9e0();
	void FUN_0046aa90();
	void FUN_0046ab40();
	void FUN_0046abe0();
	void FUN_0046ac90();
	void FUN_0046ad40();
	void FUN_0046adf0();
	void FUN_0046af50();
	void FUN_0046aea0();

protected:
	void FUN_00469b20(Entry0x84* p_entry);
	void FUN_00469b50(Entry0x84* p_entry);

	Entry0x38* m_unk0x20;         // 0x20
	Entry0x3c* m_unk0x24;         // 0x24
	Entry0x48* m_unk0x28;         // 0x28
	Entry0x60* m_unk0x2c;         // 0x2c
	Entry0x9c* m_unk0x30;         // 0x30
	Entry0xec* m_unk0x34;         // 0x34
	Entry0xa0* m_unk0x38;         // 0x38
	Entry0x98* m_unk0x3c;         // 0x3c
	Struct0x74* m_unk0x40;        // 0x40
	Entry0xb8* m_unk0x44;         // 0x44
	Entry0x88* m_unk0x48;         // 0x48
	Entry0xa0WithFont* m_unk0x4c; // 0x4c
	Entry0x54* m_unk0x50;         // 0x50
	undefined2 m_unk0x54;         // 0x54
	undefined m_unk0x56[2];       // 0x56
	LegoS32 m_unk0x58;            // 0x58
};

#endif // CERULEANQUEEN0X58_H

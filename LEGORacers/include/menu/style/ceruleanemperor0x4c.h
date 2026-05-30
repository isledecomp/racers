#ifndef CERULEANEMPEROR0X4C_H
#define CERULEANEMPEROR0X4C_H

#include "compat.h"
#include "decomp.h"
#include "goltxtparser.h"
#include "menu/style/ceruleanknight0x20.h"
#include "menu/widgets/obscureicon0x1a8.h"
#include "render/rectangle.h"
#include "types.h"
#include "util/visualstate0x4.h"

class GolD3DRenderDevice;
class GolFont0xa0;
class PorcelainVeil0x50;
class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b27cc
// SIZE 0x50
class CeruleanEmperor0x4c : public CeruleanKnight0x20 {
public:
	// SIZE 0x0c
	class Entry0x0c {
	public:
		UtopianPan0xa4* m_unk0x00; // 0x00
		VisualState0x4 m_unk0x04;  // 0x04
		LegoBool32 m_unk0x08;      // 0x08
	};

	// SIZE 0x14
	class Entry0x14 {
	public:
		GolFont0xa0* m_unk0x00;   // 0x00
		VisualState0x4 m_unk0x04; // 0x04
		LegoS32 m_unk0x08;        // 0x08
		LegoBool32 m_unk0x0c;     // 0x0c
		LegoS32 m_unk0x10;        // 0x10
	};

	// SIZE 0x18
	class Entry0x18 {
	public:
		undefined4 m_unk0x00[3]; // 0x00
		LegoS32 m_unk0x0c;       // 0x0c
		LegoS32 m_unk0x10;       // 0x10
		LegoS32 m_unk0x14;       // 0x14
	};

	// SIZE 0x2c
	class Entry0x2c {
	public:
		UtopianPan0xa4* m_unk0x00[8]; // 0x00
		VisualState0x4 m_unk0x20;     // 0x20
		VisualState0x4 m_unk0x24;     // 0x24
		LegoBool32 m_unk0x28;         // 0x28
	};

	// SIZE 0x90
	class Entry0x90 : public ObscureIcon0x1a8::CreateState0x90 {};

	// SIZE 0xa8
	class Entry0xa8 : public Entry0x90 {
	public:
		UtopianPan0xa4* m_unk0x90[6]; // 0x90
	};

	// SIZE 0x104
	class Entry0x104 : public Entry0x90 {
	public:
		GolFont0xa0* m_unk0x90[6];    // 0x90
		UtopianPan0xa4* m_unk0xa8[6]; // 0xa8
		VisualState0x4 m_unk0xc0[6];  // 0xc0
		VisualState0x4 m_unk0xd8;     // 0xd8
		Rect m_unk0xdc;               // 0xdc
		Rect m_unk0xec;               // 0xec
		undefined4 m_unk0xfc;         // 0xfc
		undefined4 m_unk0x100;        // 0x100
	};

	// SIZE 0x100
	class Entry0x100 : public Entry0x90 {
	public:
		// SIZE 0x0c
		class ImageTriplet {
		public:
			UtopianPan0xa4* m_unk0x00; // 0x00
			UtopianPan0xa4* m_unk0x04; // 0x04
			UtopianPan0xa4* m_unk0x08; // 0x08
		};

		GolFont0xa0* m_unk0x90[6]; // 0x90
		union {
			ImageTriplet m_unk0xa8[6];            // 0xa8
			UtopianPan0xa4* m_utopianunk0xa8[18]; // 0xa8
		};
		Rect m_unk0xf0; // 0xf0
	};

	// SIZE 0x150
	class Entry0x150 : public Entry0x90 {
	public:
		undefined m_unk0x90[0xa8 - 0x90]; // 0x90
		UtopianPan0xa4* m_unk0xa8;        // 0xa8
		LegoS32 m_unk0xac;                // 0xac
		undefined4 m_unk0xb0[8];          // 0xb0
		Rect m_unk0xd0[8];                // 0xd0
	};

	// SIZE 0xbc
	class Entry0xbc : public Entry0x90 {
	public:
		Entry0xa8* m_unk0x90;        // 0x90
		Entry0xa8* m_unk0x94;        // 0x94
		Entry0x2c* m_unk0x98;        // 0x98
		VisualState0x4 m_unk0x9c[4]; // 0x9c
		VisualState0x4 m_unk0xac[4]; // 0xac
	};

	// SIZE 0xbc
	class Entry0xbcWithImages : public Entry0x90 {
	public:
		Entry0x90* m_unk0x90;         // 0x90
		Entry0x90* m_unk0x94;         // 0x94
		Entry0x90* m_unk0x98;         // 0x98
		Entry0x90* m_unk0x9c;         // 0x9c
		UtopianPan0xa4* m_unk0xa0[6]; // 0xa0
		undefined2 m_unk0xb8;         // 0xb8
		undefined2 m_unk0xba;         // 0xba
	};

	// SIZE 0x10
	struct ResourceLoadParams {
		GolD3DRenderDevice* m_renderer; // 0x00
		PorcelainVeil0x50* m_unk0x04;   // 0x04
		const LegoChar* m_fileName;     // 0x08
		undefined4 m_binary;            // 0x0c
	};

	CeruleanEmperor0x4c();
	~CeruleanEmperor0x4c() override;      // vtable+0x00
	void Clear() override;                // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14
	LegoBool32 Load(ResourceLoadParams* p_params);
	void* FUN_00470e60(const LegoChar* p_name);
	Entry0x0c* GetEntry0x0c(const LegoChar* p_name) { return static_cast<Entry0x0c*>(FUN_00470e60(p_name)); }
	Entry0x14* GetEntry0x14(const LegoChar* p_name) { return static_cast<Entry0x14*>(FUN_00470e60(p_name)); }
	Entry0x90* GetEntry0x90(const LegoChar* p_name) { return static_cast<Entry0x90*>(FUN_00470e60(p_name)); }
	Entry0x104* GetEntry0x104(const LegoChar* p_name) { return static_cast<Entry0x104*>(FUN_00470e60(p_name)); }

	// SYNTHETIC: LEGORACERS 0x0046faa0
	// CeruleanEmperor0x4c::`scalar deleting destructor'

protected:
	void FUN_0046fd30(ResourceLoadParams* p_params);
	void FUN_0046fe20(Entry0x0c* p_entry);
	void FUN_0046feb0(Entry0x14* p_entry);
	void FUN_0046ff70(Entry0x2c* p_entry);
	void FUN_00470020(Entry0x90* p_entry);
	void FUN_00470110(Entry0xa8* p_entry);
	void FUN_004701a0(Entry0x100* p_entry);
	void FUN_004702e0(Entry0x150* p_entry);
	void FUN_00470410(Entry0x18* p_entry);
	void FUN_004704b0(Entry0xbc* p_entry);
	void FUN_00470650(Entry0xbcWithImages* p_entry);

private:
	void FUN_004707e0();
	void FUN_00470880();
	void FUN_00470920();
	void FUN_004709c0();
	void FUN_00470a70();
	void FUN_00470b10();
	void FUN_00470bc0();
	void FUN_00470c60();
	void FUN_00470d10();
	void FUN_00470dc0();

protected:
	CeruleanEmperor0x4c* m_unk0x20; // 0x20
	Entry0x0c* m_unk0x24;           // 0x24
	Entry0x14* m_unk0x28;           // 0x28
	Entry0x2c* m_unk0x2c;           // 0x2c
	Entry0xa8* m_unk0x30;           // 0x30
	Entry0x100* m_unk0x34;          // 0x34
	Entry0x150* m_unk0x38;          // 0x38
	Entry0x18* m_unk0x3c;           // 0x3c
	Entry0xbc* m_unk0x40;           // 0x40
	Entry0xbcWithImages* m_unk0x44; // 0x44
	Entry0x90* m_unk0x48;           // 0x48
};

#endif // CERULEANEMPEROR0X4C_H

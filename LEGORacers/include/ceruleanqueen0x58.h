#ifndef CERULEANQUEEN0X58_H
#define CERULEANQUEEN0X58_H

#include "ceruleanknight0x20.h"
#include "compat.h"
#include "decomp.h"
#include "goltxtparser.h"
#include "types.h"

class BronzeFalcon0xc8770;

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

	// SIZE 0x74
	class Struct0x74 {
	public:
		undefined m_unk0x00[0x3c - 0x00]; // 0x00
		undefined* m_unk0x3c;             // 0x3c
		undefined m_unk0x40[0x74 - 0x40]; // 0x40
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

	// SYNTHETIC: LEGORACERS 0x00469600
	// CeruleanQueen0x58::`scalar deleting destructor'

private:
	void FUN_00469900(ResourceLoadParams* p_params);
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
	undefined* m_unk0x20;   // 0x20
	undefined* m_unk0x24;   // 0x24
	undefined* m_unk0x28;   // 0x28
	undefined* m_unk0x2c;   // 0x2c
	undefined* m_unk0x30;   // 0x30
	undefined* m_unk0x34;   // 0x34
	undefined* m_unk0x38;   // 0x38
	undefined* m_unk0x3c;   // 0x3c
	Struct0x74* m_unk0x40;  // 0x40
	undefined* m_unk0x44;   // 0x44
	undefined* m_unk0x48;   // 0x48
	undefined* m_unk0x4c;   // 0x4c
	undefined* m_unk0x50;   // 0x50
	undefined2 m_unk0x54;   // 0x54
	undefined m_unk0x56[2]; // 0x56
	LegoS32 m_unk0x58;      // 0x58
};

#endif // CERULEANQUEEN0X58_H

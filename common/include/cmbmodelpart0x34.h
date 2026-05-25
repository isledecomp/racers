#ifndef CMBMODELPART0X34_H
#define CMBMODELPART0X34_H

#include "cmbmodelpartdata0x18.h"
#include "cmbmodelpartdata0x28.h"
#include "decomp.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolFileParser;

// VTABLE: GOLDP 0x10056a50
// VTABLE: LEGORACERS 0x004af224
// SIZE 0x34
class CmbModelPart0x34 : public GolNameTable {
	// VTABLE: GOLDP 0x10056a68
	// VTABLE: LEGORACERS 0x004af23c
	// SIZE 0x1fc
	class AdbTxtParser : public GolTxtParser {
		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
		// CmbModelPart0x34::AdbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
		// CmbModelPart0x34::AdbTxtParser::~AdbTxtParser
	};

public:
	CmbModelPart0x34();
	~CmbModelPart0x34() override;                                         // vtable+0x00
	void Clear() override;                                                // vtable+0x08
	virtual void VTable0x0c(GolFileParser& p_parser);                     // vtable+0x0c
	virtual void VTable0x10(GolFileParser& p_parser);                     // vtable+0x10
	virtual void VTable0x14(const LegoChar* p_name, LegoBool32 p_binary); // vtable+0x14

	CmbModelPartData0x28* GetPartData() const { return m_unk0x2c; }
	LegoU32 GetPartCount() const { return m_unk0x30; }
	CmbModelPartData0x18& GetAnimationData() { return m_data; }
	const CmbModelPartTrack0x14& GetTrack(LegoU32 p_index) const { return m_unk0x24[p_index]; }
	CmbModelPartData0x28* FindPart(const LegoChar* p_name) const
	{
		return static_cast<CmbModelPartData0x28*>(GetName(p_name));
	}
	LegoS32 GetPartIndex(const LegoChar* p_name) const
	{
		CmbModelPartData0x28* part = FindPart(p_name);
		return part == NULL ? -1 : part - m_unk0x2c;
	}

	// SYNTHETIC: GOLDP 0x10017880
	// SYNTHETIC: LEGORACERS 0x0041e1b0
	// CmbModelPart0x34::`vector deleting destructor'

private:
	CmbModelPartData0x18 m_data;      // 0x0c
	CmbModelPartTrack0x14* m_unk0x24; // 0x24
	LegoU32 m_unk0x28;                // 0x28
	CmbModelPartData0x28* m_unk0x2c;  // 0x2c
	LegoU32 m_unk0x30;                // 0x30
};

#endif // CMBMODELPART0X34_H

#ifndef CMBMODELPART_H
#define CMBMODELPART_H

#include "cmbmodelpartdata.h"
#include "cmbmodelparttrackdata.h"
#include "decomp.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolFileParser;

// VTABLE: GOLDP 0x10056a50
// VTABLE: LEGORACERS 0x004af224
// SIZE 0x34
class CmbModelPart : public GolNameTable {
public:
	// VTABLE: GOLDP 0x10056a68
	// VTABLE: LEGORACERS 0x004af23c
	// SIZE 0x1fc
	class AdbTxtParser : public GolTxtParser {
		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
		// CmbModelPart::AdbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
		// CmbModelPart::AdbTxtParser::~AdbTxtParser
	};

	CmbModelPart();
	~CmbModelPart() override;                                             // vtable+0x00
	void Clear() override;                                                // vtable+0x08
	virtual void VTable0x0c(GolFileParser& p_parser);                     // vtable+0x0c
	virtual void VTable0x10(GolFileParser& p_parser);                     // vtable+0x10
	virtual void VTable0x14(const LegoChar* p_name, LegoBool32 p_binary); // vtable+0x14

	CmbModelPartData* GetPartData() const { return m_unk0x2c; }
	LegoU32 GetPartCount() const { return m_unk0x30; }
	void MirrorY();
	CmbModelPartTrackData& GetAnimationData() { return m_data; }
	const CmbModelPartTrack& GetTrack(LegoU32 p_index) const { return m_unk0x24[p_index]; }
	CmbModelPartData* FindPart(const LegoChar* p_name) const { return static_cast<CmbModelPartData*>(GetName(p_name)); }
	LegoS32 GetPartIndex(const LegoChar* p_name) const
	{
		CmbModelPartData* part = FindPart(p_name);
		return part == NULL ? -1 : part - m_unk0x2c;
	}

	// SYNTHETIC: GOLDP 0x10017880
	// SYNTHETIC: LEGORACERS 0x0041e1b0
	// CmbModelPart::`vector deleting destructor'

private:
	CmbModelPartTrackData m_data; // 0x0c
	CmbModelPartTrack* m_unk0x24; // 0x24
	LegoU32 m_unk0x28;            // 0x28
	CmbModelPartData* m_unk0x2c;  // 0x2c
	LegoU32 m_unk0x30;            // 0x30
};

#endif // CMBMODELPART_H

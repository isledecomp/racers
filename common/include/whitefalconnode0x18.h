#ifndef WHITEFALCONNODE0X18_H
#define WHITEFALCONNODE0X18_H

#include "golnametable.h"
#include "goltxtparser.h"

class GolFileParser;
struct GolMatrix34;
struct GolMatrix4;
struct GolVec3;
class JadeOrbitBase0x10;

// VTABLE: GOLDP 0x10057454
// SIZE 0x18
class WhiteFalconNode0x18 : public GolNameTable {
public:
	WhiteFalconNode0x18();
	~WhiteFalconNode0x18() override;                                      // vtable+0x00
	void Allocate(LegoU32 p_capacity) override;                           // vtable+0x04
	void Clear() override;                                                // vtable+0x08
	virtual void VTable0x0c() = 0;                                        // vtable+0x0c
	virtual void VTable0x10(WhiteFalconNode0x18* p_node);                 // vtable+0x10
	virtual void VTable0x14(const LegoChar* p_name, LegoBool32 p_binary); // vtable+0x14
	virtual JadeOrbitBase0x10* VTable0x18(LegoU32 p_index) const = 0;     // vtable+0x18
	virtual LegoU32 VTable0x1c(const JadeOrbitBase0x10&) const;           // vtable+0x1c
	virtual void VTable0x20(const GolMatrix4& p_m);                       // vtable+0x20
	virtual void VTable0x24(const GolMatrix34* p_m);                      // vtable+0x24
	virtual void VTable0x28(undefined4, undefined4);                      // vtable+0x28
	virtual void VTable0x2c(LegoU32 p_index, GolMatrix34* p_dest) const;  // vtable+0x2c

	// SYNTHETIC: GOLDP 0x100299a0
	// WhiteFalconNode0x18::`scalar deleting destructor'

	void FUN_004132a0(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3);
	LegoU32 GetUpdateSerial() const { return m_unk0x0c; }
	LegoU32 GetCapacity() const { return m_capacity; }
	LegoU32 AdvanceUpdateSerial()
	{
		m_unk0x0c++;
		if (m_unk0x0c == static_cast<LegoU32>(-1)) {
			m_unk0x0c = 0;
		}
		return m_unk0x0c;
	}

protected:
	// VTABLE: GOLDP 0x10057484
	// SIZE 0x1fc
	class DdfTxtParser : public GolTxtParser {
		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// WhiteFalconNode0x18::DdfTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// WhiteFalconNode0x18::DdfTxtParser::~DdfTxtParser
	};

	void FUN_10029c60(GolFileParser* p_parser);

	undefined4 m_unk0x0c; // 0x0c
	LegoU32 m_capacity;   // 0x10
	undefined4 m_unk0x14; // 0x14
};

#endif // WHITEFALCONNODE0X18_H

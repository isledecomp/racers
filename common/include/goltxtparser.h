#ifndef GOLTXTPARSER_H
#define GOLTXTPARSER_H

#include "compat.h"
#include "decomp.h"
#include "golfileparser.h"

// VTABLE: LEGORACERS 0x004b27e4
// SIZE 0x1fc
class GolTxtParser : public GolFileParser {
public:
	GolTxtParser() {}

	const LegoChar* GetSuffix() override;                   // vtable+0x3c
	void VTable0x40(undefined4) override;                   // vtable+0x40
	undefined4 VTable0x44() override;                       // vtable+0x44
	undefined4 VTable0x48(undefined4, undefined4) override; // vtable+0x48
	void VTable0x4c() override;                             // vtable+0x4c
	void VTable0x50() override;                             // vtable+0x50
	void VTable0x54() override;                             // vtable+0x54
	void VTable0x58() override;                             // vtable+0x58
	void VTable0x5c() override;                             // vtable+0x5c
	void VTable0x60() override;                             // vtable+0x60
	void VTable0x64() override;                             // vtable+0x64
	void VTable0x68() override;                             // vtable+0x68
	void VTable0x6c() override;                             // vtable+0x6c
	void VTable0x70() override;                             // vtable+0x70
	void VTable0x74(undefined4) override;                   // vtable+0x74

	// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
	// GolTxtParser::`scalar deleting destructor'

protected:
	undefined m_unk0x1f0[12]; // 0x1f0
};

#endif // GOLTXTPARSER_H

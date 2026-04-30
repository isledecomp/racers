#ifndef GOLDPEXPORT_H
#define GOLDPEXPORT_H

#include "compat.h"
#include "decomp.h"
#include "gol.h"
#include "goldrawdpstate.h"

// VTABLE: GOLDP 0x10056440
// SIZE 0xc8ac8
class GolDPExport : public GolExport {
public:
	~GolDPExport() override; // vtable+0x00

	// SYNTHETIC: GOLDP 0x10007040
	// GolDPExport::`scalar deleting destructor'

	GolDrawState* VTable0x04() override;          // vtable+0x04
	ZoweeBlubberworth0xf0* VTable0x08() override; // vtable+0x08
	undefined4* VTable0x0c() override;            // vtable+0x0c
	undefined4* VTable0x10() override;            // vtable+0x10
	undefined4* VTable0x14() override;            // vtable+0x14
	undefined4* VTable0x18() override;            // vtable+0x18
	undefined4* VTable0x1c() override;            // vtable+0x1c
	AmberLens0x344* VTable0x20() override;        // vtable+0x20
	undefined4 VTable0x24() override;             // vtable+0x24
	WhiteBaffoon0x50* VTable0x28() override;      // vtable+0x28
	undefined4* VTable0x2c() override;            // vtable+0x2c
	FloatyBoat0x28* VTable0x30() override;        // vtable+0x30
	AwakeKite0x20* VTable0x34() override;         // vtable+0x34
	GolNameTable* VTable0x38() override;          // vtable+0x38
	void VTable0x3c(undefined4*) override;        // vtable+0x3c
	void VTable0x40(undefined4*) override;        // vtable+0x40
	void VTable0x44(undefined4*) override;        // vtable+0x44
	void VTable0x48(undefined4*) override;        // vtable+0x48
	void VTable0x4c(undefined4*) override;        // vtable+0x4c
	void VTable0x50(undefined4*) override;        // vtable+0x50
	void VTable0x54(undefined4*) override;        // vtable+0x54
	void VTable0x58(undefined4*) override;        // vtable+0x58
	void VTable0x5c(undefined4*) override;        // vtable+0x5c
	void VTable0x60(undefined4*) override;        // vtable+0x60
	void VTable0x64(undefined4*) override;        // vtable+0x64
	void VTable0x68(AwakeKite0x20*) override;     // vtable+0x68
	void VTable0x6c(GolNameTable*) override;      // vtable+0x6c

private:
	GolDrawDPState m_state; // 0x04
};

#endif // GOLDPEXPORT_H

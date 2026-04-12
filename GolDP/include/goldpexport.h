#ifndef GolDPExport_H
#define GolDPExport_H

#include "compat.h"
#include "decomp.h"
#include "gol.h"

// VTABLE: GOLDP 0x10056440
// SIZE 0xc8ac8
class GolDPExport : public GolExport {
public:
	~GolDPExport() override; // vtable+0x00

	// SYNTHETIC: GOLDP 0x10007040
	// GolDPExport::`scalar deleting destructor'

	undefined4* VTable0x04() override;
	undefined4* VTable0x08() override;
	undefined4* VTable0x0c() override;
	undefined4* VTable0x10() override;
	undefined4* VTable0x14() override;
	undefined4* VTable0x18() override;
	undefined4* VTable0x1c() override;
	undefined4* VTable0x20() override;
	undefined4 VTable0x24() override;
	undefined4* VTable0x28() override;
	undefined4* VTable0x2c() override;
	undefined4* VTable0x30() override;
	undefined4* VTable0x34() override;
	undefined4* VTable0x38() override;
	void VTable0x3c(undefined4*) override;
	void VTable0x40(undefined4*) override;
	void VTable0x44(undefined4*) override;
	void VTable0x48(undefined4*) override;
	void VTable0x4c(undefined4*) override;
	void VTable0x50(undefined4*) override;
	void VTable0x54(undefined4*) override;
	void VTable0x58(undefined4*) override;
	void VTable0x5c(undefined4*) override;
	void VTable0x60(undefined4*) override;
	void VTable0x64(undefined4*) override;
	void VTable0x68(undefined4*) override;
	void VTable0x6c(undefined4*) override;

private:
	undefined m_unk0x04[0xc8ac8 - 0x4]; // 0x04
};

#endif // GolDPExport_H

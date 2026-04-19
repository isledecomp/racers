#ifndef IMAGINARYWRENCH0X23BC_H
#define IMAGINARYWRENCH0X23BC_H

#include "compat.h"
#include "crimsonray0x20.h"
#include "decomp.h"
#include "golstring.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b31f8
// SIZE 0x23bc
class ImaginaryWrench0x23bc : public ImaginaryTool0x368 {
public:
	ImaginaryWrench0x23bc();

	void VTable0x38(undefined4) override;             // vtable+0x38
	void VTable0x3c(undefined4) override;             // vtable+0x3c
	void VTable0x40(undefined4) override;             // vtable+0x40
	void VTable0x44(undefined4) override;             // vtable+0x44
	void VTable0x4c(undefined4) override;             // vtable+0x4c
	void VTable0x54() override;                       // vtable+0x54
	~ImaginaryWrench0x23bc() override;                // vtable+0x68
	void VTable0x74() override;                       // vtable+0x74
	void VTable0x84() override;                       // vtable+0x84
	void VTable0x8c(undefined4, undefined4) override; // vtable+0x8c
	void VTable0x90(undefined4) override;             // vtable+0x90
	void VTable0x94(undefined4) override;             // vtable+0x94

	void FUN_0047ba00();

	// SYNTHETIC: LEGORACERS 0x0047b070
	// ImaginaryWrench0x23bc::`scalar deleting destructor'

protected:
	enum {
		c_nslwj = 1 << 0,
		c_flyskyhgh = 1 << 1,
		c_pgllrd = 1 << 2,
		c_pgllyll = 1 << 3,
		c_pgllgrn = 1 << 4,
		c_lnfrrrm = 1 << 5,
		c_rpcrnly = 1 << 6,
		c_mxpmx = 1 << 7,
		c_fstfrwrd = 1 << 8,
		c_nwhls = 1 << 9,
		c_nchsss = 1 << 10,
		c_ndrvr = 1 << 11,
		c_nmrchts = 1 << 12
	};

	undefined m_unk0x04[0x23a8 - 0x368]; // 0x0004
	GolString m_unk0x23a8;               // 0x23a8
	undefined m_unk0x23b2[8];            // 0x23b2
};

#endif // IMAGINARYWRENCH0X23BC_H

#ifndef CERULEANEMPEROR0X4C_H
#define CERULEANEMPEROR0X4C_H

#include "ceruleanknight0x20.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;

// VTABLE: LEGORACERS 0x004b27cc
// SIZE 0x50
class CeruleanEmperor0x4c : public CeruleanKnight0x20 {
public:
	// SIZE 0x10
	struct ResourceLoadParams {
		BronzeFalcon0xc8770* m_renderer; // 0x00
		undefined4 m_unk0x04;            // 0x04
		const LegoChar* m_fileName;      // 0x08
		undefined4 m_binary;             // 0x0c
	};

	CeruleanEmperor0x4c();
	~CeruleanEmperor0x4c() override;      // vtable+0x00
	void Clear() override;                // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14
	LegoBool32 Load(ResourceLoadParams* p_params);

	// SYNTHETIC: LEGORACERS 0x0046faa0
	// CeruleanEmperor0x4c::`scalar deleting destructor'

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
	undefined4 m_unk0x20; // 0x20
	undefined* m_unk0x24; // 0x24
	undefined* m_unk0x28; // 0x28
	undefined* m_unk0x2c; // 0x2c
	undefined* m_unk0x30; // 0x30
	undefined* m_unk0x34; // 0x34
	undefined* m_unk0x38; // 0x38
	undefined* m_unk0x3c; // 0x3c
	undefined* m_unk0x40; // 0x40
	undefined* m_unk0x44; // 0x44
	undefined* m_unk0x48; // 0x48
};

#endif // CERULEANEMPEROR0X4C_H

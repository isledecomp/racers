#ifndef IRONFLAME0X944_H
#define IRONFLAME0X944_H

#include "compat.h"
#include "crimsonforge0x800.h"
#include "decomp.h"
#include "opalvault0xf0.h"
#include "types.h"

// VTABLE: LEGORACERS 0x4af9f4
// SIZE 0x944
class IronFlame0x944 : public CrimsonForge0x800 {
public:
	IronFlame0x944();
	void VTable0x00() override;                                 // vtable+0x00
	~IronFlame0x944() override;                                 // vtable+0x04
	void VTable0x0c(const LegoChar*, const LegoChar*) override; // vtable+0x0c
	void VTable0x10() override;                                 // vtable+0x10
	void VTable0x14() override;                                 // vtable+0x14
	void VTable0x18() override;                                 // vtable+0x18
	void VTable0x1c() override;                                 // vtable+0x1c
	void VTable0x20() override;                                 // vtable+0x20
	void VTable0x24() override;                                 // vtable+0x24
	void VTable0x28() override;                                 // vtable+0x28
	void VTable0x2c() override;                                 // vtable+0x2c
	void VTable0x30() override;                                 // vtable+0x30
	void VTable0x34() override;                                 // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x416560
	// IronFlame0x944::`scalar deleting destructor'

	undefined4 GetUnk0x928() { return m_unk0x928; }
	void SetUnk0x928(undefined4 p_unk0x928) { m_unk0x928 = p_unk0x928; }

private:
	undefined4 m_unk0x800;               // 0x800
	undefined m_unk0x804[0x830 - 0x804]; // 0x804
	undefined4 m_unk0x830;               // 0x830
	OpalVault0xf0 m_unk0x834;            // 0x834
	undefined4 m_unk0x924;               // 0x924
	undefined4 m_unk0x928;               // 0x928
	undefined4 m_unk0x92c;               // 0x92c
	undefined4 m_unk0x930;               // 0x930
	undefined4 m_unk0x934;               // 0x934
	undefined4 m_unk0x938;               // 0x938
	undefined4 m_unk0x93c;               // 0x93c
	undefined4 m_unk0x940;               // 0x940
};

#endif // IRONFLAME0X944_H

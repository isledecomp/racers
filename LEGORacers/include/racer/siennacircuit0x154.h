#ifndef SIENNACIRCUIT0X154_H
#define SIENNACIRCUIT0X154_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/ceruleanemperor0x4c.h"
#include "menu/widgets/violetshoal0xc0.h"
#include "model/topazburst0x14.h"
#include "types.h"

class GolModelEntity;
class LegoPieceLibrary;
class ObscureIcon0x1a8;
class SapphireReef0x2030;
class VerdantTide0x38;

extern const LegoFloat g_siennaCircuitTwoPi;

// VTABLE: LEGORACERS 0x004b3c10
// SIZE 0x154
class SiennaCircuit0x154 : public VioletShoal0xc0 {
public:
	// SIZE 0x84
	class CreateParams0x84 : public VioletShoal0xc0::CreateParams0x74 {
	public:
		TopazBurst0x14* m_unk0x74;        // 0x74
		LegoPieceLibrary* m_pieceLibrary; // 0x78
		SapphireReef0x2030* m_unk0x7c;    // 0x7c
		VerdantTide0x38* m_unk0x80;       // 0x80
	};

	SiennaCircuit0x154();

	void Reset() override;                                 // vtable+0x00
	~SiennaCircuit0x154() override;                        // vtable+0x04
	LegoBool32 VTable0x08() override;                      // vtable+0x08
	undefined4 VTable0x3c(undefined4) override;            // vtable+0x3c
	void VTable0x50(undefined4) override;                  // vtable+0x50
	LegoS32 VTable0x54() override;                         // vtable+0x54
	LegoS32 VTable0x58() override;                         // vtable+0x58
	void VTable0x5c(undefined4, GolModelEntity*) override; // vtable+0x5c
	void VTable0x60(LegoS32) override;                     // vtable+0x60

	LegoBool32 FUN_00485300(CreateParams0x84* p_createParams, CeruleanEmperor0x4c::Entry0x18* p_styleEntry);
	LegoS32 FUN_004853a0();
	void FUN_004853f0();
	void FUN_00485440(LegoS32 p_unk0x04);
	void FUN_004856c0(LegoS32 p_unk0x04, LegoS32 p_unk0x08);
	LegoS32 GetUnk0xd4(LegoS32 p_index) const { return m_unk0xd4[p_index]; }

	// SYNTHETIC: LEGORACERS 0x00485250
	// SiennaCircuit0x154::`scalar deleting destructor'

private:
	TopazBurst0x14* m_unk0xc0;        // 0xc0
	LegoPieceLibrary* m_pieceLibrary; // 0xc4
	SapphireReef0x2030* m_unk0xc8;    // 0xc8
	VerdantTide0x38* m_unk0xcc;       // 0xcc
	TopazBurst0x14::Entry* m_unk0xd0; // 0xd0
	LegoS32 m_unk0xd4[30];            // 0xd4
	LegoS32 m_unk0x14c;               // 0x14c
	LegoFloat m_unk0x150;             // 0x150
};

#endif // SIENNACIRCUIT0X154_H

#ifndef OBSCUREICON0X1A8_H
#define OBSCUREICON0X1A8_H

#include "compat.h"
#include "decomp.h"
#include "obscurevantage0x58.h"
#include "rectangle.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GolExport;
class SoundGroupBinding;

// VTABLE: LEGORACERS 0x004b2944
// SIZE 0x1a8
class ObscureIcon0x1a8 : public ObscureVantage0x58 {
public:
	// SIZE 0x84
	class CreateParams0x84 : public ObscureVantage0x58::CreateParams0x30 {
	public:
		undefined m_unk0x30[0x38 - 0x30]; // 0x30
		LegoBool m_unk0x38;               // 0x38
		undefined m_unk0x39[0x40 - 0x39]; // 0x39
		undefined2 m_unk0x40;             // 0x40
		undefined m_unk0x42[0x44 - 0x42]; // 0x42
		ObscureIcon0x1a8* m_parentIcon;   // 0x44
		undefined m_unk0x48[0x52 - 0x48]; // 0x48
		undefined m_unk0x52[0x6a - 0x52]; // 0x52
		undefined m_unk0x6a[0x74 - 0x6a]; // 0x6a
		undefined4 m_unk0x74;             // 0x74
		undefined4 m_unk0x78;             // 0x78
		undefined4 m_unk0x7c;             // 0x7c
		ImaginaryInterface* m_unk0x80;    // 0x80
	};

	// SIZE 0x90
	class CreateState0x90 {
	public:
		undefined m_unk0x00[0x18 - 0x00]; // 0x00
		undefined m_unk0x18[0x24 - 0x18]; // 0x18
		Rect m_unk0x24[6];                // 0x24
		undefined4 m_unk0x84;             // 0x84
		undefined m_unk0x88[0x90 - 0x88]; // 0x88
	};

	enum {
		c_flagBit0 = 1 << 0, // VTable0x44 sets / VTable0x48 clears
		c_flagBit1 = 1 << 1, // FUN_00471fb0 sets / FUN_00472010 clears
		c_flagBit2 = 1 << 2, // VTable0x54 sets / VTable0x58 clears
	};

	ObscureIcon0x1a8();
	void Reset() override;                                                                 // vtable+0x00
	~ObscureIcon0x1a8() override;                                                          // vtable+0x04
	undefined4 VTable0x08() override;                                                      // vtable+0x08
	void VTable0x10(Rect*) override;                                                       // vtable+0x10
	undefined4 VTable0x2c(void*, undefined4, undefined4) override;                         // vtable+0x2c
	undefined4 VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x30
	undefined4 VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x34
	undefined4 VTable0x38(Rect*, Rect*) override;                                          // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;                                            // vtable+0x3c
	virtual void VTable0x40(ImaginaryInterface*);
	virtual void VTable0x44(undefined4);
	virtual void VTable0x48(undefined4);
	virtual void VTable0x4c(undefined4);
	virtual void VTable0x50(undefined4);
	virtual void VTable0x54(undefined4);
	virtual void VTable0x58(undefined4);
	virtual LegoBool32 VTable0x5c();
	virtual ObscureIcon0x1a8* VTable0x60();
	virtual ObscureIcon0x1a8* VTable0x64();
	virtual ObscureIcon0x1a8* VTable0x68();
	virtual ObscureIcon0x1a8* VTable0x6c();

	LegoBool32 FUN_00471e30(CreateParams0x84* p_createParams, const CreateState0x90* p_createState);
	void FUN_00471ec0(ObscureIcon0x1a8* p_parentIcon);
	void FUN_00471f00();

	// SYNTHETIC: LEGORACERS 0x00471c80
	// ObscureIcon0x1a8::`scalar deleting destructor'

protected:
	void FUN_00471d90(CreateParams0x84* p_createParams, const CreateState0x90* p_createState);
	ObscureIcon0x1a8* FUN_00471f70();
	ObscureIcon0x1a8* FUN_00471f90();
	void FUN_00471fb0(undefined4 p_flags);
	void FUN_00472010(undefined4 p_flags);
	void FUN_00472080();
	void FUN_00472540();

	ObscureIcon0x1a8* m_parentIcon;         // 0x058
	ObscureIcon0x1a8* m_prevIcon;           // 0x05c
	ObscureIcon0x1a8* m_nextIcon;           // 0x060
	ObscureIcon0x1a8* m_firstIcon;          // 0x064
	ObscureIcon0x1a8* m_lastIcon;           // 0x068
	Rect m_unk0x6c[6];                      // 0x06c
	Rect m_unk0xcc[6];                      // 0x0cc
	LegoU8 m_unk0x12c;                      // 0x12c
	LegoBool m_unk0x12d;                    // 0x12d
	undefined m_unk0x12e[0x130 - 0x12e];    // 0x12e
	LegoS32 m_unk0x130;                     // 0x130
	LegoS32 m_unk0x134;                     // 0x134
	LegoFloat m_unk0x138;                   // 0x138
	LegoFloat m_unk0x13c;                   // 0x13c
	LegoFloat m_unk0x140;                   // 0x140
	LegoFloat m_unk0x144;                   // 0x144
	LegoFloat m_unk0x148;                   // 0x148
	LegoFloat m_unk0x14c;                   // 0x14c
	LegoFloat m_unk0x150;                   // 0x150
	LegoFloat m_unk0x154;                   // 0x154
	undefined4 m_unk0x158[4];               // 0x158
	undefined2 m_unk0x168;                  // 0x168
	SoundGroupBinding* m_soundGroupBinding; // 0x16c
	ImaginaryInterface* m_eventHandler;     // 0x170
	undefined4 m_unk0x174[6];               // 0x174
	LegoU16 m_soundIds[5];                  // 0x18c
	undefined m_unk0x196[0x198 - 0x196];    // 0x196
	ObscureIcon0x1a8* m_unk0x198;           // 0x198
	LegoU8 m_unk0x19c;                      // 0x19c
	undefined m_unk0x19d[0x1a0 - 0x19d];    // 0x19d
	undefined4 m_unk0x1a0;                  // 0x1a0
	undefined4 m_unk0x1a4;                  // 0x1a4
};

#endif // OBSCUREICON0X1A8_H

#ifndef OBSCURESIGIL0XDC
#define OBSCURESIGIL0XDC

#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "menu/widgets/obscurelink0x1c.h"
#include "menu/widgets/obscurevantage0x58.h"
#include "types.h"

class GolCamera;
class GolWorldEntity;
class GolWorldDatabase;

// VTABLE: LEGORACERS 0x004b1dfc
// SIZE: 0xdc
class ObscureSigil0xdc : public ObscureVantage0x58 {
public:
	// SIZE 0x84
	class CreateParams0x84 : public ObscureVantage0x58::CreateParams0x38 {
	public:
		GolVec3 m_unk0x38;               // 0x38
		GolVec3 m_unk0x44;               // 0x44
		GolVec3 m_unk0x50;               // 0x50
		LegoFloat m_unk0x5c;             // 0x5c
		LegoChar m_unk0x60[0x70 - 0x60]; // 0x60
		undefined4 m_unk0x70;            // 0x70
		LegoBool32 m_unk0x74;            // 0x74
		undefined4 m_unk0x78;            // 0x78
		undefined4 m_unk0x7c;            // 0x7c
		LegoFloat m_unk0x80;             // 0x80
	};

	ObscureSigil0xdc();

	void Reset() override;                                                                    // vtable+0x00
	~ObscureSigil0xdc() override;                                                             // vtable+0x04
	LegoBool32 VTable0x08() override;                                                         // vtable+0x08
	ObscureVantage0x58* VTable0x2c(void*, undefined4, undefined4) override;                   // vtable+0x2c
	ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	ObscureVantage0x58* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;                                               // vtable+0x3c
	LegoBool32 FUN_00465820(CreateParams0x84* p_createParams, undefined4 p_unk0x08);
	ObscureLink0x1c* FUN_00465b40(ObscureLink0x1c* p_unk0x04);
	void FUN_00465b60(GolWorldEntity* p_entity, Rect* p_rect);
	GolWorldDatabase* GetUnk0x60() const { return m_unk0x60; }

	// SYNTHETIC: LEGORACERS 0x00465730
	// ObscureSigil0xdc::`scalar deleting destructor'

protected:
	void FUN_00465900(CreateParams0x84* p_createParams, undefined4 p_unk0x08);
	void FUN_004659b0(CreateParams0x84* p_createParams);
	void FUN_00465ab0(GolVec3* p_unk0x04, GolVec3* p_unk0x08);
	void FUN_00465c00(undefined4 p_elapsedMs);
	void FUN_00465e40(Rect* p_rect);
	void FUN_00465ea0();

	ObscureLink0x1c* m_unk0x58;  // 0x58
	GolWorldDatabase* m_unk0x5c; // 0x5c
	GolWorldDatabase* m_unk0x60; // 0x60
	GolCamera* m_unk0x64;        // 0x64
	GolCamera* m_unk0x68;        // 0x68
	undefined4 m_unk0x6c;        // 0x6c
	GolVec3 m_unk0x70;           // 0x70
	GolVec3 m_unk0x7c;           // 0x7c
	undefined4 m_unk0x88;        // 0x88
	LegoFloat m_unk0x8c;         // 0x8c
	GolVec3 m_unk0x90;           // 0x90
	GolVec3 m_unk0x9c;           // 0x9c
	GolVec3 m_unk0xa8;           // 0xa8
	LegoFloat m_unk0xb4;         // 0xb4
	LegoFloat m_unk0xb8;         // 0xb8
	LegoFloat m_unk0xbc;         // 0xbc
	LegoFloat m_unk0xc0;         // 0xc0
	LegoFloat m_unk0xc4;         // 0xc4
	LegoFloat m_unk0xc8;         // 0xc8
	LegoFloat m_unk0xcc;         // 0xcc
	LegoFloat m_unk0xd0;         // 0xd0
	LegoFloat m_unk0xd4;         // 0xd4
	LegoFloat m_unk0xd8;         // 0xd8
};

#endif // OBSCURESIGIL0XDC

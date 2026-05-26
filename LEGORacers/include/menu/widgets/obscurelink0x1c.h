#ifndef OBSCURELINK0X1C_H
#define OBSCURELINK0X1C_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GolExport;
class ObscureSigil0xdc;

// VTABLE: LEGORACERS 0x004b2228
// SIZE 0x1c
class ObscureLink0x1c {
public:
	// SIZE 0x0c
	struct CreateParams0x0c {
		GolExport* m_golExport;          // 0x00
		BronzeFalcon0xc8770* m_renderer; // 0x04
		ObscureSigil0xdc* m_unk0x08;     // 0x08
	};

	ObscureLink0x1c();
	virtual void Reset();                          // vtable+0x00
	virtual ~ObscureLink0x1c();                    // vtable+0x04
	virtual LegoBool32 VTable0x08();               // vtable+0x08
	virtual LegoBool32 VTable0x0c() = 0;           // vtable+0x0c
	virtual LegoBool32 VTable0x10(undefined4) = 0; // vtable+0x10

	LegoBool32 FUN_0046b300(CreateParams0x0c* p_createParams);
	ObscureLink0x1c* FUN_0046b350(ObscureLink0x1c* p_parent);
	ObscureLink0x1c* GetNext() const { return m_unk0x08; }

	// SYNTHETIC: LEGORACERS 0x0046b2b0
	// ObscureLink0x1c::`scalar deleting destructor'

protected:
	ObscureLink0x1c* m_unk0x04;     // 0x04
	ObscureLink0x1c* m_unk0x08;     // 0x08
	GolExport* m_unk0x0c;           // 0x0c
	BronzeFalcon0xc8770* m_unk0x10; // 0x10
	ObscureSigil0xdc* m_unk0x14;    // 0x14
	LegoBool32 m_unk0x18;           // 0x18
};

#endif // OBSCURELINK0X1C_H

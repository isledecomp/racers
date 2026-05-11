#ifndef AMBERLENS0X344_H
#define AMBERLENS0X344_H

#include "amberlensbase0x120.h"
#include "compat.h"
#include "decomp.h"
#include "jadeorbit0x220.h"
#include "types.h"

#include <d3d.h>

class AmberLens0x344;
class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x100561f8
// SIZE 0x344
class AmberLens0x344 : public AmberLensBase0x120 {
public:
	enum {
		c_flagBit0 = 1 << 0,
		c_flagBit1 = 1 << 1,
		c_flagBit3 = 1 << 3,
	};

	AmberLens0x344();
	void VTable0x00() override;                                           // vtable+0x00
	void VTable0x04() override;                                           // vtable+0x04
	~AmberLens0x344() override;                                           // vtable+0x08
	void VTable0x0c(Rect* p_rect) override;                               // vtable+0x0c
	void VTable0x10() override;                                           // vtable+0x10
	void VTable0x14() override;                                           // vtable+0x14
	void VTable0x18() override;                                           // vtable+0x18
	void VTable0x1c() override;                                           // vtable+0x1c
	void VTable0x20(undefined4 p_unk0x04, undefined4 p_unk0x08) override; // vtable+0x20
	using AmberLensBase0x120::VTable0x24;                                 // vtable+0x24
	void VTable0x28() override;                                           // vtable+0x28

	// SYNTHETIC: GOLDP 0x10017a60
	// AmberLens0x344::`vector deleting destructor'

	JadeOrbit0x220* GetUnk0x04() { return m_unk0x04; }

protected:
	friend class BronzeFalcon0xc8770;

	void FUN_10001f60(BronzeFalcon0xc8770*);
	void FUN_10002860(D3DVIEWPORT2* p_viewport);

	JadeOrbit0x220 m_unk0x120;       // 0x120
	BronzeFalcon0xc8770* m_renderer; // 0x340
};

#endif // AMBERLENS0X344_H

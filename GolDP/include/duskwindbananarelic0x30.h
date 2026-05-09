#ifndef DUSKWINDBANANARELIC0x30_H
#define DUSKWINDBANANARELIC0x30_H

#include "compat.h"
#include "duskwindbananarelic0x24.h"

#include <d3d.h>

class WhiteFalcon0x140;
class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x100563c4
// SIZE 0x30
class DuskwindBananaRelic0x30 : public DuskwindBananaRelic0x24 {
public:
	DuskwindBananaRelic0x30();
	~DuskwindBananaRelic0x30() override; // vtable+0x00

	void FUN_10006320(WhiteFalcon0x140& p_renderer);
	LegoU8* GetUnk0x2c() const { return m_unk0x2c; }

	// SYNTHETIC: GOLDP 0x10004b00
	// DuskwindBananaRelic0x30::`vector deleting destructor'

	void Destroy();

private:
	void FUN_100064d0(BronzeFalcon0xc8770* p_renderer);

	LPDIRECT3DMATERIAL3 m_unk0x24; // 0x24
	D3DMATERIALHANDLE m_unk0x28;   // 0x28
	LegoU8* m_unk0x2c;             // 0x2c
};

#endif // DUSKWINDBANANARELIC0x30_H

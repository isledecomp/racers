#ifndef MABMATERIALANIMATIONITEM0X8_H
#define MABMATERIALANIMATIONITEM0X8_H

#include "decomp.h"
#include "types.h"

class WhiteFalcon0x140;
class DuskwindBananaRelic0x24;

// SIZE 0x8
class MabMaterialAnimationItem0x8 {
public:
	MabMaterialAnimationItem0x8();

	void FUN_10026110(WhiteFalcon0x140* p_renderer, const LegoChar* p_name, LegoU32 p_id);
	DuskwindBananaRelic0x24* GetMaterial() const { return m_unk0x00; }
	LegoU32 GetFrame() const { return m_unk0x04; }

private:
	DuskwindBananaRelic0x24* m_unk0x00; // 0x00
	LegoU32 m_unk0x04;                  // 0x04
};

#endif // MABMATERIALANIMATIONITEM0X8_H

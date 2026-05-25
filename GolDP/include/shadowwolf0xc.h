#ifndef SHADOWWOLF0xC_H
#define SHADOWWOLF0xC_H

#include "decomp.h"
#include "materialtable0x0c.h"
#include "types.h"

class GolFileParser;
class DuskwindBananaRelic0x24;
class WhiteFalcon0x140;

class ShadowWolf0xc : public MaterialTable0x0c {
public:
	ShadowWolf0xc();
	~ShadowWolf0xc();

	void Destroy();

	void FUN_10025df0(WhiteFalcon0x140* p_renderer, undefined4);
	void FUN_10025e60(WhiteFalcon0x140* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary);
	void FUN_10025f90(WhiteFalcon0x140* p_renderer, GolFileParser& p_parser);

	WhiteFalcon0x140* GetRenderer() const { return m_renderer; }
	LegoU32 GetCount() const { return m_count; }
	DuskwindBananaRelic0x24* GetMaterial(LegoU32 p_index) const
	{
		return static_cast<DuskwindBananaRelic0x24*>(m_entries[p_index]);
	}
};

#endif // SHADOWWOLF0xC_H

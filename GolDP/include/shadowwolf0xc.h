#ifndef SHADOWWOLF0xC_H
#define SHADOWWOLF0xC_H

#include "decomp.h"
#include "types.h"

class GolFileParser;
class WhiteFalcon0x140;

class ShadowWolf0xc {
public:
	ShadowWolf0xc();
	~ShadowWolf0xc();

	void Destroy();

	void FUN_10025df0(WhiteFalcon0x140* p_renderer, undefined4);
	void FUN_10025e60(WhiteFalcon0x140* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary);
	void FUN_10025f90(WhiteFalcon0x140* p_renderer, GolFileParser& p_parser);

	WhiteFalcon0x140* GetUnk0x00() const { return m_unk0x00; }

protected:
	WhiteFalcon0x140* m_unk0x00; // 0x00
	LegoU32 m_unk0x04;           // 0x04
	undefined4** m_unk0x08;      // 0x08
};

#endif // SHADOWWOLF0xC_H

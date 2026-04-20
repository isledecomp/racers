#ifndef AQUACORAL0X37B8_H
#define AQUACORAL0X37B8_H

#include "decomp.h"
#include "glassblock0x3368.h"
#include "glassshard0x3b8.h"
#include "glassstream0x94.h"
#include "types.h"

// SIZE 0x37b8
class AquaCoral0x37b8 {
public:
	AquaCoral0x37b8();
	~AquaCoral0x37b8();

	static void FUN_0042b130(LegoBool32* p_unk0x00);

	void FUN_0042c280(LegoBool32* p_unk0x00);
	void FUN_0042c330();
	void FUN_0042c380();

private:
	undefined4 m_unk0x00;        // 0x00
	GlassStream0x94 m_unk0x04;   // 0x04
	GlassBlock0x3368 m_unk0x98;  // 0x98
	GlassShard0x3b8 m_unk0x3400; // 0x3400
};

#endif // AQUACORAL0X37B8_H

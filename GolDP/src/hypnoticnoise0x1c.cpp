#include "hypnoticnoise0x1c.h"

#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golerror.h"
#include "goltxtparser.h"

DECOMP_SIZE_ASSERT(HypnoticNoise0x1c, 0x1c)
DECOMP_SIZE_ASSERT(HypnoticNoise0x1cInner, 0xa4)

// FUNCTION: GOLDP 0x10022fa0
HypnoticNoise0x1c::HypnoticNoise0x1c()
{
	m_unk0x0c = NULL;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// FUNCTION: GOLDP 0x10022fe0
#pragma inline_depth(0)
HypnoticNoise0x1c::~HypnoticNoise0x1c()
{
	m_unk0x14 = 0;

	if (m_unk0x0c) {
		m_unk0x0c->FUN_10028ae0(this);
		m_unk0x0c = 0;
	}

	if (m_data) {
		SmallCocoon0xc::VTable0x08();
	}
}
#pragma inline_depth()

// FUNCTION: GOLDP 0x10023060
void HypnoticNoise0x1c::VTable0x18(BronzeFalcon0xc8770* p_param1, char* p_param2, undefined4 p_param3)
{
	undefined4 local18;

	if (m_unk0x14 > 0) {
		VTable0x08();
	}

	m_unk0x0c = p_param1;
	m_unk0x0c->FUN_10028ad0(this);

	GolFileParser* parser;

	if (p_param3) {
		parser = new GolBinParser();

		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}

		parser->SetSuffix(".idb");
	}
	else {
		parser = new GolTxtParser();

		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
	}

	parser->VTable0x38((undefined4) p_param2);
	parser->FUN_10032740(0x27);
	m_unk0x14 = parser->FUN_100327e0();

	if (!m_unk0x14) {
		parser->Dispose();
		delete parser;
		return;
	}

	// TODO: m_unk0x14 could be a size
	SmallCocoon0xc::VTable0x04(m_unk0x14);

	if (g_hashTable) {
		m_unk0x18 = g_hashTable->GetCurrentEntry();
	}
	else {
		m_unk0x18 = NULL;
	}

	VTable0x0c();

	for (LegoU32 i = 0; i < m_unk0x14; i++) {
		union {
			char bytes[4];
			undefined4 dword;
		} esp0x30;
		union {
			char bytes[4];
			undefined4 dword;
		} esp0x34;
		esp0x30.bytes[3] = -1;
		esp0x34.bytes[3] = -1;

		parser->FUN_10032740(0x27);
		HypnoticNoise0x1cInner* val1 = VTable0x20(i);

		LegoChar* name = parser->FUN_10032700(8);

		// TODO: Currently guesswork (3 lines)
		LegoChar nameCopy[8];
		strncpy(nameCopy, name, 8);
		AddName(nameCopy, (undefined4*) val1); // TODO: Get rid of typecast once matched

		parser->FUN_100327a0();

		undefined4 val4 = 0;

		esp0x30.bytes[0] = 0;
		esp0x30.bytes[1] = 0;
		esp0x30.bytes[2] = 0;

		esp0x34.bytes[0] = -1;
		esp0x34.bytes[1] = -1;
		esp0x34.bytes[2] = -1;

		undefined4 val3 = parser->VTable0x44();

		// uVar10 = 0;
		// p_param1 = (BronzeFalcon0xc8770*) ((uint) p_param1 & 0xff000000);
		// p_param2 = (char*) CONCAT13(p_param2._3_1_, 0xffffff);
		// iVar6 = (**(code**) ((int) (this_00->base).base.vftable + 0x44))();
		// pBVar2 = p_param1;
		// pcVar3 = p_param2;

		while (val3 != 6) {
			switch (val3) {
			case 0x28:
				val4 = val4 | 4;
				break;
			case 0x29:
				val4 = val4 & 0xffef | 8;
				break;
			case 0x2a:
				val4 = val4 & 0xfff7 | 0x10;
				break;
			case 0x2b:
				val4 = val4 | 0x20;
				esp0x30.bytes[0] = parser->FUN_100326a0();
				esp0x30.bytes[1] = parser->FUN_100326a0();
				esp0x30.bytes[2] = parser->FUN_100326a0();
				break;
			case 0x2c:
				esp0x34.bytes[0] = parser->FUN_100326a0();
				esp0x34.bytes[1] = parser->FUN_100326a0();
				esp0x34.bytes[2] = parser->FUN_100326a0();
				break;
			default:
				val3 = parser->VTable0x44();
			}
		}

		val1->m_unk0x40 = i;
		val1->m_unk0x44 = local18;

		// TODO: Most likely wrong; this is the vtable+0x110 I am afraid of
		int ivar4;
		/* int ivar4 = */p_param1->VTable0x24();

		if (ivar4) {
			val4 = val4 | 0x40;
		}

		if ((val4 & 0x20) && val1->m_unk0x04 & 2) {
			val4 = val4 | 0x80;
		}

		val1->m_unk0x08 = val4;
		val1->m_unk0x48 = esp0x34.dword;
		if (val4 & 0x20) {
			val1->m_unk0x28 = esp0x30.dword;
			val1->m_unk0x08 = val4 | 0x800;
		}

		val1->m_unk0x24 = m_unk0x0c; // wild guess, most likely wrong
		// TODO
		// *(uint*) ((int) p_arg2 + 0x42) = uStack_18;
		// *(undefined4*) ((int) p_arg2 + 0x46) = uStack_14;

		// iVar6 = (**(code**) (*unaff_retaddr + 0x110))();
		// if (iVar6 != 0) {
		// 	uVar10 = uVar10 | 0x40;
		// }
		// if (((uVar10 & 0x20) != 0) && ((*(uint*) pBVar2->m_unk0x04 & 0x200) != 0)) {
		// 	uVar10 = uVar10 | 0x80;
		// }
		// *(ushort*) (p_arg2 + 0x10) = uVar10;
		// *(uint*) ((int) p_arg2 + 0x4a) = p_param3;
		// if ((uVar10 & 0x20) != 0) {
		// 	p_arg2[10] = (uint) pcVar3;
		// 	*(ushort*) (p_arg2 + 0x10) = uVar10 | 0x800;
		// p_arg2[9] = (uint) pBVar2;
		// uStack_18 = uStack_18 + 1;
	}

	parser->FUN_100327c0();
	parser->Dispose();
	delete parser;

	if (g_hashTable) {
		g_hashTable->SetCurrentEntry(m_unk0x18);
	}

	for (LegoU32 j = 0; j < m_unk0x14; j++) {
		HypnoticNoise0x1cInner* entry = VTable0x20(j);
		entry->VTable0x10();
	}
}

// FUNCTION: GOLDP 0x100233a0
void HypnoticNoise0x1c::VTable0x1c(BronzeFalcon0xc8770* p_param1, LegoU32 p_param2)
{
	if (m_unk0x14 > 0) {
		VTable0x08();
	}

	m_unk0x0c = p_param1;
	m_unk0x0c->FUN_10028ad0(this);
	m_unk0x14 = p_param2;

	VTable0x0c();

	for (LegoU32 i = 0; i < p_param2; i++) {
		VTable0x20(i)->m_unk0x24 = p_param1;
	}
}

// FUNCTION: GOLDP 0x100233f0
void HypnoticNoise0x1c::VTable0x08()
{
	m_unk0x14 = 0;
	if (m_unk0x0c) {
		m_unk0x0c->FUN_10028ae0(this);
		m_unk0x0c = 0;
	}

	if (m_data) {
		SmallCocoon0xc::VTable0x08();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void HypnoticNoise0x1c::VTable0x10()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void HypnoticNoise0x1c::VTable0x14()
{
	// empty
}

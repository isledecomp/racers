#include "whitefalcon0x140.h"

#include "amberhaze0x1c.h"
#include "cinderbasin0x28.h"
#include "hypnoticnoise0x1c.h"
#include "magentaribbon0x20.h"

#include <string.h>

DECOMP_SIZE_ASSERT(WhiteFalcon0x140::WhiteFalconWing0x1c, 0x1c)
DECOMP_SIZE_ASSERT(WhiteFalcon0x140, 0x140)

// FUNCTION: GOLDP 0x10028840
WhiteFalcon0x140::WhiteFalcon0x140()
{
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x30 = 0;
	m_unk0x34 = NULL;
	m_unk0x38 = NULL;
	m_unk0x3c = NULL;
	m_unk0x40 = NULL;
	m_unk0x44 = NULL;
	m_nextDrawStateRenderer = NULL;
	m_unk0x0c = NULL;
	m_unk0x04 = 0;
	m_unk0x0a = 0;
	::memset(m_unk0x4c, 0, sizeof(m_unk0x4c));
	m_unk0x11c = 0;
	m_unk0x120 = 0;
	::memset(&m_unk0x124, 0, sizeof(m_unk0x124));
	m_unk0x124.m_unk0x00 = 0;
}

// FUNCTION: GOLDP 0x100288e0
WhiteFalcon0x140::~WhiteFalcon0x140()
{
	Destroy();
}

// FUNCTION: GOLDP 0x100288f0
void WhiteFalcon0x140::Destroy()
{
	if (m_unk0x34 != NULL) {
		delete m_unk0x34;
		m_unk0x34 = NULL;
	}

	AmberHaze0x1c* amberHaze = m_unk0x3c;
	m_unk0x30 = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;

	while (amberHaze != NULL) {
		AmberHaze0x1c* next = amberHaze->GetNext();
		amberHaze->Clear();
		amberHaze = next;
	}

	MagentaRibbon0x20* magentaRibbon = m_unk0x38;
	while (magentaRibbon != NULL) {
		MagentaRibbon0x20* next = magentaRibbon->GetNext();
		magentaRibbon->Clear();
		magentaRibbon = next;
	}

	HypnoticNoise0x1c* hypnoticNoise = m_unk0x40;
	while (hypnoticNoise != NULL) {
		HypnoticNoise0x1c* next = hypnoticNoise->GetNext();
		hypnoticNoise->Clear();
		hypnoticNoise = next;
	}

	CinderBasin0x28* cinderBasin = m_unk0x44;
	while (cinderBasin != NULL) {
		CinderBasin0x28* next = cinderBasin->GetNext();
		cinderBasin->Clear();
		cinderBasin = next;
	}
}

// STUB: GOLDP 0x10028980
void WhiteFalcon0x140::VTable0x04()
{
	STUB(0x10028980);
}

// STUB: GOLDP 0x10028a10
void WhiteFalcon0x140::VTable0x00()
{
	STUB(0x10028a10);
}

// FUNCTION: GOLDP 0x10028a70
void WhiteFalcon0x140::FUN_10028a70(CinderBasin0x28* p_param)
{
	p_param->SetNext(m_unk0x44);
	m_unk0x44 = p_param;
}

// FUNCTION: GOLDP 0x10028a80
void WhiteFalcon0x140::FUN_10028a80(CinderBasin0x28* p_param)
{
	CinderBasin0x28* node = m_unk0x44;

	if (node != NULL) {
		if (p_param == node) {
			m_unk0x44 = node->GetNext();
			return;
		}

		CinderBasin0x28* previous = node;
		node = node->GetNext();

		while (node != NULL) {
			if (node == p_param) {
				previous->SetNext(node->GetNext());
				node->SetNext(NULL);
				return;
			}

			previous = node;
			node = node->GetNext();
		}
	}
}

// FUNCTION: GOLDP 0x10028ad0
void WhiteFalcon0x140::FUN_10028ad0(HypnoticNoise0x1c* p_param)
{
	p_param->SetNext(m_unk0x40);
	m_unk0x40 = p_param;
}

// FUNCTION: GOLDP 0x10028ae0
void WhiteFalcon0x140::FUN_10028ae0(HypnoticNoise0x1c* p_param)
{
	HypnoticNoise0x1c* node = m_unk0x40;

	if (node != NULL) {
		if (p_param == node) {
			m_unk0x40 = node->GetNext();
			return;
		}

		HypnoticNoise0x1c* previous = node;
		node = node->GetNext();

		while (node != NULL) {
			if (node == p_param) {
				previous->SetNext(node->GetNext());
				node->SetNext(NULL);
				return;
			}

			previous = node;
			node = node->GetNext();
		}
	}
}

// FUNCTION: GOLDP 0x10028b30
void WhiteFalcon0x140::FUN_10028b30(MagentaRibbon0x20* p_param)
{
	p_param->SetNext(m_unk0x38);
	m_unk0x38 = p_param;
}

// FUNCTION: GOLDP 0x10028b40
void WhiteFalcon0x140::FUN_10028b40(MagentaRibbon0x20* p_param)
{
	MagentaRibbon0x20* node = m_unk0x38;

	if (node != NULL) {
		if (p_param == node) {
			m_unk0x38 = node->GetNext();
			return;
		}

		MagentaRibbon0x20* previous = node;
		node = node->GetNext();

		while (node != NULL) {
			if (node == p_param) {
				previous->SetNext(node->GetNext());
				node->SetNext(NULL);
				return;
			}

			previous = node;
			node = node->GetNext();
		}
	}
}

// FUNCTION: GOLDP 0x10028b90
void* WhiteFalcon0x140::FUN_10028b90(const LegoChar* p_name)
{
	MagentaRibbon0x20* node = m_unk0x38;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			void* value = node->GetName(p_name);
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: GOLDP 0x10028bc0
void WhiteFalcon0x140::FUN_10028bc0(AmberHaze0x1c* p_param)
{
	p_param->SetNext(m_unk0x3c);
	m_unk0x3c = p_param;
}

// FUNCTION: GOLDP 0x10028bd0
void WhiteFalcon0x140::FUN_10028bd0(AmberHaze0x1c* p_param)
{
	AmberHaze0x1c* node = m_unk0x3c;

	if (node != NULL) {
		if (p_param == node) {
			m_unk0x3c = node->GetNext();
			return;
		}

		AmberHaze0x1c* previous = node;
		node = node->GetNext();

		while (node != NULL) {
			if (node == p_param) {
				previous->SetNext(node->GetNext());
				node->SetNext(NULL);
				return;
			}

			previous = node;
			node = node->GetNext();
		}
	}
}

// FUNCTION: GOLDP 0x10028c20
void* WhiteFalcon0x140::FUN_10028c20(const LegoChar* p_name)
{
	AmberHaze0x1c* node = m_unk0x3c;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			void* value = node->GetName(p_name);
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// STUB: GOLDP 0x10028c50
void WhiteFalcon0x140::VTable0x0c(undefined4, undefined4, undefined4)
{
	STUB(0x10028c50);
}

// STUB: GOLDP 0x10029500
void WhiteFalcon0x140::VTable0xa4()
{
	STUB(0x10029500);
}

// STUB: GOLDP 0x10029680
void WhiteFalcon0x140::VTable0xa0()
{
	STUB(0x10029680);
}

// STUB: GOLDP 0x10029840
void WhiteFalcon0x140::VTable0xa8(undefined4, undefined4, undefined4)
{
	STUB(0x10029500);
}

// STUB: GOLDP 0x10029850
void WhiteFalcon0x140::VTable0xb8(undefined4, undefined4)
{
	STUB(0x10029850);
}

// STUB: GOLDP 0x10029870
void WhiteFalcon0x140::VTable0xbc()
{
	STUB(0x10029870);
}

// STUB: GOLDP 0x10029880
void WhiteFalcon0x140::VTable0xc0(undefined4)
{
	STUB(0x10029880);
}

// STUB: GOLDP 0x100298a0
void WhiteFalcon0x140::VTable0xc4()
{
	STUB(0x100298a0);
}

// STUB: GOLDP 0x100298b0
void WhiteFalcon0x140::VTable0x28()
{
	STUB(0x100298b0);
}

// STUB: GOLDP 0x100298d0
void WhiteFalcon0x140::VTable0x2c(undefined4)
{
	STUB(0x100298d0);
}

// STUB: GOLDP 0x100298f0
void WhiteFalcon0x140::VTable0x30(undefined4)
{
	STUB(0x100298f0);
}

// STUB: GOLDP 0x10029930
void WhiteFalcon0x140::VTable0x44()
{
	STUB(0x10029930);
}

// STUB: GOLDP 0x10029940
void WhiteFalcon0x140::VTable0x48()
{
	STUB(0x10029940);
}

// STUB: GOLDP 0x10029960
void WhiteFalcon0x140::VTable0x58(undefined4, undefined4)
{
	STUB(0x10029960);
}

// STUB: GOLDP 0x10029970
void WhiteFalcon0x140::VTable0x24()
{
	STUB(0x10029970);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0x38()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0x40()
{
	// empty
}

// FUNCTION: GOLDP 0x10029950 FOLDED
undefined4 WhiteFalcon0x140::VTable0x4c(undefined4, undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalcon0x140::VTable0x50(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0x60()
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void WhiteFalcon0x140::VTable0x88(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void WhiteFalcon0x140::VTable0x8c(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void WhiteFalcon0x140::VTable0x98(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void WhiteFalcon0x140::VTable0x9c(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalcon0x140::VTable0x34(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalcon0x140::VTable0xac(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalcon0x140::VTable0xb0(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalcon0x140::VTable0x3c(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0xc8()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0xcc()
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalcon0x140::VTable0xec(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void WhiteFalcon0x140::VTable0xf4()
{
	// empty
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoBool32 WhiteFalcon0x140::VTable0x110() const
{
	MATCHING(0x100016f0);
	return FALSE;
}

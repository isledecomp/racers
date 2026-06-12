#include "menu/screens/editdriverscreen.h"

#include "golhashtable.h"
#include "golname.h"
#include "golstream.h"
#include "golstring.h"
#include "golstringtable.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "racer/drivercosmetics.h"
#include "save/savegame.h"
#include "surface/color.h"

#include <string.h>

DECOMP_SIZE_ASSERT(EditDriverScreen, 0x4774)
DECOMP_SIZE_ASSERT(MenuRacerCarousel, 0x170)
DECOMP_SIZE_ASSERT(DriverHeadBuilder, 0x50)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

// GLOBAL: LEGORACERS 0x004c20b8
LegoU16 g_unk0x004c20b8[8] = {0x74, 0x75, 0x76, 0xd3, 0x81, 0x82, 0x78, 0x79};

// GLOBAL: LEGORACERS 0x004c20c8
LegoU16 g_unk0x004c20c8[2] = {0x7c, 0x80};

// FUNCTION: LEGORACERS 0x0047ce30
EditDriverScreen::EditDriverScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047cf90
EditDriverScreen::~EditDriverScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047d0d0
void EditDriverScreen::Reset()
{
	m_unk0x476c = 1;
	m_unk0x4764 = 0;
	m_unk0x4768 = 0;
	m_unk0x4770 = 0;

	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047d100
void EditDriverScreen::FUN_0047d100(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	DriverHeadBuilder::LoadParams params;
	::memset(&params, 0, sizeof(params));

	params.m_renderer = p_createParams->m_renderer;
	params.m_golExport = p_createParams->m_golExport;
	params.m_partCatalog = &p_context->m_partCatalog;
	params.m_binary = p_context->m_context->m_unk0x18;
	params.m_partLibrary = p_context->m_partResources.GetPartLibrary();
	m_headBuilder.Load(&params, 2);
}

// FUNCTION: LEGORACERS 0x0047d170
LegoBool32 EditDriverScreen::FUN_0047d170(
	MenuRacerCarousel* p_widget,
	undefined2 p_createParamId,
	undefined2 p_styleId,
	LegoU32 p_category
)
{
	MenuRacerCarousel::CreateParams* sourceParams =
		static_cast<MenuRacerCarousel::CreateParams*>(GetBindingEntry(p_createParamId));
	MenuStyleTable::CarouselStyle* styleEntry = static_cast<MenuStyleTable::CarouselStyle*>(GetStyleEntry(p_styleId));

	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuRacerCarousel::CreateParams createParams;
	::memcpy(&createParams, sourceParams, sizeof(createParams));
	ApplyWidgetDefaults(&createParams);

	createParams.m_context = m_context;
	createParams.m_unk0x6c = m_unk0x476c++;
	createParams.m_headBuilder = &m_headBuilder;
	createParams.m_unk0x7c = p_category;
	createParams.m_unk0x70 = VTable0x6c();
	return p_widget->FUN_00483a60(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0047d230
void EditDriverScreen::FUN_0047d230()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\CB_SET");
	}

	CreateFramedSceneView(&m_unk0x31b0, 0, 0xd0);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	MainMenuModelSlot::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	createParams.m_golExport = m_golExport;
	createParams.m_renderer = m_renderer;
	createParams.m_unk0x08 = &m_unk0x31b0;
	createParams.m_unk0x0c = &m_context->m_modelBuilder;
	createParams.m_position.m_x = -5.3590002f;
	createParams.m_position.m_y = -3.1500001f;
	createParams.m_position.m_z = 0.026000001f;

	m_unk0x4600.FUN_0047e0a0(&createParams);
	m_unk0x31b0.FUN_00465b40(&m_unk0x4600);
}

// FUNCTION: LEGORACERS 0x0047d2f0
void EditDriverScreen::VTable0x4c()
{
	CreateImage(&m_unk0x368, 0x49, 0x49);
	FUN_0047d170(&m_unk0x420[0], 0xcd, 0x3b, 0);
	FUN_0047d170(&m_unk0x420[1], 0xce, 0x3b, 1);
	FUN_0047d170(&m_unk0x420[2], 0xcd, 0x3b, 2);
	FUN_0047d170(&m_unk0x420[3], 0xcd, 0x3b, 3);
	CreateSelector(&m_unk0x9e0[0], &m_unk0x420[0], 0xc8, 0xcc);
	CreateSelector(&m_unk0x9e0[1], &m_unk0x420[1], 0xc9, 0xcc);
	CreateSelector(&m_unk0x9e0[2], &m_unk0x420[2], 0xca, 0xcc);
	CreateSelector(&m_unk0x9e0[3], &m_unk0x420[3], 0xcb, 0xcc);
	FUN_0047d230();
	CreateTextLabel(&m_unk0x3688, 0x3a, 0x3a, 9);
	m_unk0x3688.FUN_0046f6b0(0x14);
	FUN_0047fdc0(&m_unk0x3700, 0xd2, 0x42, 0x38);

	if (m_context->m_modelBuilder.GetUnk0x78() & 1) {
		FUN_0047fdc0(&m_unk0x3ce0, 0x40, 0x44, 0x0a);
	}
	else {
		FUN_0047fdc0(&m_unk0x3ce0, 0x40, 0x46, 0x72);
	}

	FUN_0047fdc0(&m_unk0x39f0, 0x3f, 0x45, 0x1f);
}

// FUNCTION: LEGORACERS 0x0047d460
LegoBool32 EditDriverScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!p_context->m_modelBuilder.HasMenuResources()) {
		FUN_00480210(p_context, FALSE);
	}

	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	ColorRGBA materialColor;
	ColorRGBA lightColor;
	materialColor.m_blu = 0x80;
	materialColor.m_grn = 0x80;
	materialColor.m_red = 0x80;
	lightColor.m_alp = 0xff;
	lightColor.m_blu = 0xff;
	lightColor.m_grn = 0xff;
	lightColor.m_red = 0xff;
	materialColor.m_alp = 0xff;
	FUN_0047fec0(&materialColor, &lightColor);

	m_unk0x4600.GetUnk0x118()->VTable0x14("cbanim", p_context->m_context->m_unk0x18);
	p_context->m_unk0x21f4.FUN_00499f00();
	FUN_0047d100(p_context, p_createParams);
	FUN_0047d840();
	FUN_0047d6f0();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047d520
LegoBool32 EditDriverScreen::Destroy()
{
	MenuGameContext* context = m_context;

	if (!m_initialized) {
		return TRUE;
	}

	m_headBuilder.ReleaseResources();
	context->m_unk0x21f4.FUN_00499ee0();

	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x0047d560
LegoBool32 EditDriverScreen::FUN_0047d560()
{
	if (m_context->m_modelBuilder.GetUnk0x78() & 1) {
		return FALSE;
	}

	DriverCosmetics cosmetics;
	m_context->m_saveSystem.GetActiveRecord().GetCosmetics(&cosmetics);

	if (cosmetics.m_hatIndex == m_driverCosmetics.m_components[0] &&
		cosmetics.m_faceIndex == m_driverCosmetics.m_components[1] &&
		cosmetics.m_torsoIndex == m_driverCosmetics.m_components[2]) {
		return cosmetics.m_legIndex != m_driverCosmetics.m_components[3];
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047d5d0
LegoS32 EditDriverScreen::FUN_0047d5d0()
{
	GolString string;
	m_menuNameStrings->CopyStringByIndex(&string, 0x83);

	if (m_unk0x4768) {
		m_menuNameStrings->CopyStringByIndex(&string, m_unk0x4768);
		m_unk0x4768 = 0;
	}
	else {
		g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
		LegoU16 random = g_unk0x004befec[g_unk0x004c6ee4];
		LegoU16 textIdIndex = static_cast<LegoU16>(static_cast<LegoS32>(random) % 8);
		m_menuNameStrings->CopyStringByIndex(&string, g_unk0x004c20b8[textIdIndex]);
	}

	GolName name;
	string.CopyToBuf8(name);
	return m_unk0x4600.GetUnk0x118()->GetPartIndex(name);
}

// FUNCTION: LEGORACERS 0x0047d6f0
void EditDriverScreen::FUN_0047d6f0()
{
	GolAnimatedEntity* entity = m_unk0x4600.GetUnk0x1c();
	LegoS32 partIndex;

	do {
		partIndex = FUN_0047d5d0();
	} while (partIndex == entity->GetActiveState());

	entity->FUN_0040dad0(partIndex);
	entity->SetFlags((entity->GetFlags() & ~0x40000) | 0x10000);
}

// FUNCTION: LEGORACERS 0x0047d740
void EditDriverScreen::FUN_0047d740()
{
	GolString string;
	GolName name;

	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
	LegoU16 random = g_unk0x004befec[g_unk0x004c6ee4];
	LegoS32 textIdIndex = static_cast<LegoS32>(random) % 2;
	m_menuNameStrings->CopyStringByIndex(&string, g_unk0x004c20c8[textIdIndex]);
	string.CopyToBuf8(name);

	GolAnimatedEntity* entity = m_unk0x4600.GetUnk0x1c();
	LegoS32 partIndex = m_unk0x4600.GetUnk0x118()->GetPartIndex(name);
	entity->FUN_0040db80(partIndex, 0xc8, 0.0f, FALSE, FALSE, FALSE);
	entity->SetFlags((entity->GetFlags() & ~0x40000) | 0x10000);
}

// FUNCTION: LEGORACERS 0x0047d840
void EditDriverScreen::FUN_0047d840()
{
	m_context->m_saveSystem.GetActiveRecord().GetCosmetics(&m_driverCosmetics);

	m_unk0x420[0].FUN_00484170(m_driverCosmetics.m_components[0]);
	m_unk0x420[1].FUN_00484170(m_driverCosmetics.m_components[1]);
	m_unk0x420[2].FUN_00484170(m_driverCosmetics.m_components[2]);
	m_unk0x420[3].FUN_00484170(m_driverCosmetics.m_components[3]);

	m_unk0x4600.FUN_0047e210(&m_driverCosmetics);
	m_unk0x9e0[0].VTable0x4c(4);
	m_unk0x4764 = 0;
}

// FUNCTION: LEGORACERS 0x0047d8e0
void EditDriverScreen::FUN_0047d8e0()
{
	m_context->m_saveSystem.GetActiveRecord().SetCosmetics(&m_driverCosmetics);

	if ((m_context->m_modelBuilder.GetUnk0x78() == 0) & TRUE) {
		m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord()->CopyFrom(
			&m_context->m_saveSystem.GetActiveRecord()
		);
		m_unk0x4770 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0047d940
void EditDriverScreen::FUN_0047d940()
{
	SaveRecordList::Record* record = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord();
	SaveRecordList* records = NULL;

	switch (record->m_unk0x08) {
	case 1:
		records = &m_context->m_saveSystem.GetSessionSave();
		break;
	case 2:
		records = &m_context->m_saveSystem.GetMemoryCardSaves()[record->m_unk0x0c];
		break;
	}

	records->FUN_0042b920(record);
	m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(NULL);
}

// FUNCTION: LEGORACERS 0x0047d9a0
LegoBool32 EditDriverScreen::VTable0x88()
{
	GolAnimatedEntity* entity = m_unk0x4600.GetUnk0x1c();

	return entity->FUN_0040e360() || !(entity->GetFlags() & 0x10000);
}

// FUNCTION: LEGORACERS 0x0047d9d0
void EditDriverScreen::VTable0x84()
{
	switch (m_unk0x360) {
	case 0x10:
		m_context->m_menuStack.Pop();
		m_context->m_menuStack.Push(0x10);
		break;

	case 3:
		m_context->m_menuStack.Pop();

		if (m_unk0x4770) {
			m_context->m_menuStack.Push(0x30);
		}

		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() & ~1);
		break;
	}
}

// FUNCTION: LEGORACERS 0x0047da50
LegoBool32 EditDriverScreen::VTable0x18(MenuWidget* p_unk0x04, InputEventQueue::Event*, undefined4, undefined4)
{
	if (m_unk0x364) {
		return TRUE;
	}

	for (LegoS32 i = 0; i < 4; i++) {
		if (p_unk0x04 == &m_unk0x420[i]) {
			VTable0x44(&m_unk0x9e0[i]);
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0047dab0
void EditDriverScreen::VTable0x44(MenuWidget* p_source)
{
	m_unk0x4764 = TRUE;

	if (p_source == &m_unk0x9e0[0]) {
		LegoU32 index = m_unk0x420[0].GetSelectedValue();
		m_driverCosmetics.m_components[0] = static_cast<LegoU8>(index);
		index &= 0xff;
		m_unk0x4600.FUN_0047e130(index);
		m_unk0x4768 = 0x83;
		return;
	}
	else if (p_source == &m_unk0x9e0[1]) {
		LegoU32 index = m_unk0x420[1].GetSelectedValue();
		m_driverCosmetics.m_components[1] = static_cast<LegoU8>(index);
		index &= 0xff;
		m_unk0x4600.FUN_0047e160(index, 0);
		m_unk0x4768 = 0x83;
		return;
	}
	else if (p_source == &m_unk0x9e0[2]) {
		LegoU32 index = m_unk0x420[2].GetSelectedValue();
		m_driverCosmetics.m_components[2] = static_cast<LegoU8>(index);
		index &= 0xff;
		m_unk0x4600.FUN_0047e1b0(index);
		m_unk0x4768 = 0x84;
		return;
	}
	else if (p_source == &m_unk0x9e0[3]) {
		LegoU32 index = m_unk0x420[3].GetSelectedValue();
		m_driverCosmetics.m_components[3] = static_cast<LegoU8>(index);
		index &= 0xff;
		m_unk0x4600.FUN_0047e1e0(index);

		g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
		LegoU16 random = g_unk0x004befec[g_unk0x004c6ee4];
		m_unk0x4768 = (static_cast<LegoS32>(random) % 2) ? 0xd4 : 0x85;
		return;
	}
	else {
		m_unk0x4764 = FALSE;
	}
}

// FUNCTION: LEGORACERS 0x0047dbf0
void EditDriverScreen::VTable0x38(MenuWidget* p_source)
{
	if (p_source == &m_unk0x3700) {
		LegoS32 i;
		for (i = 0; i < 4; i++) {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
			LegoU16 random = g_unk0x004befec[g_unk0x004c6ee4];
			m_unk0x420[i].VTable0x50(static_cast<LegoS32>(random) % m_unk0x420[i].GetItemCount());
		}

		m_driverCosmetics.m_components[0] = static_cast<LegoU8>(m_unk0x420[0].GetSelectedValue());
		m_driverCosmetics.m_components[1] = static_cast<LegoU8>(m_unk0x420[1].GetSelectedValue());
		m_driverCosmetics.m_components[2] = static_cast<LegoU8>(m_unk0x420[2].GetSelectedValue());
		m_driverCosmetics.m_components[3] = static_cast<LegoU8>(m_unk0x420[3].GetSelectedValue());

		m_unk0x4600.FUN_0047e210(&m_driverCosmetics);
	}
	else if (p_source == &m_unk0x39f0) {
		if (FUN_0047d560()) {
			FUN_0047fdc0(&m_unk0x3fd0, 0x99, 0x46, 0x20);
			FUN_0047fdc0(&m_unk0x42c0, 0x99, 0x45, 0x1f);
			FUN_0046c6f0(&m_unk0x3fd0, &m_unk0x42c0, 0x7b);
		}
		else if (m_context->m_modelBuilder.GetUnk0x78() & 1) {
			FUN_0047fdc0(&m_unk0x3fd0, 0x99, 0x46, 0x73);
			FUN_0047fdc0(&m_unk0x42c0, 0x99, 0x45, 0x74);
			FUN_0046c6f0(&m_unk0x3fd0, &m_unk0x42c0, 0x77);
		}
		else {
			VTable0x38(&m_unk0x3fd0);
		}
	}
	else if (p_source == &m_unk0x3ce0) {
		FUN_0047d8e0();
		FUN_0047d740();

		if (m_context->m_modelBuilder.GetUnk0x78() & 1) {
			m_unk0x360 = 0x10;
		}
		else {
			m_unk0x360 = 3;
		}
	}
	else if (p_source == &m_unk0x3fd0) {
		if (m_context->m_modelBuilder.GetUnk0x78() & 1) {
			FUN_0047d940();
		}

		GolAnimatedEntity* entity = m_unk0x4600.GetUnk0x1c();
		entity->SetFlags(entity->GetFlags() & ~0x10000);

		if (m_unk0x284->GetUnk0x9c() > 0) {
			m_unk0x284->FUN_00468cf0();
		}

		m_unk0x360 = 3;
	}
	else if (p_source == &m_unk0x42c0) {
		m_unk0x284->FUN_00468cf0();
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
		m_unk0x35c = p_source;
	}
}

// FUNCTION: LEGORACERS 0x0047de30
LegoBool32 EditDriverScreen::VTable0x78(undefined4 p_unk0x04)
{
	if (!m_unk0x364 && m_unk0x4600.GetUnk0x1c()->FUN_0040e360()) {
		FUN_0047d6f0();
	}

	return MenuGameScreen::VTable0x78(p_unk0x04);
}

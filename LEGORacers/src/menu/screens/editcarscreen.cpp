#include "menu/screens/editcarscreen.h"

#include "cmbmodelpart0x34.h"
#include "core/gol.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golscenenode.h"
#include "golstream.h"
#include "material/awakekite0x20.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "mesh/golmodelbase.h"
#include "racer/turquoiseglowcolor.h"
#include "surface/color.h"
#include "util/tanzanitewisp0x88.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(EditCarScreen, 0x36c4)

// GLOBAL: LEGORACERS 0x004b3290
static const LegoFloat g_editCarMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004c766c
static AwakeKite0x20* g_editCarImageList = NULL;

// FUNCTION: LEGORACERS 0x0047bc50
EditCarScreen::EditCarScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047be00
EditCarScreen::~EditCarScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047bf70
void EditCarScreen::Reset()
{
	m_unk0x3678 = NULL;
	m_unk0x35a4 = NULL;
	m_unk0x35a8 = NULL;
	m_unk0x3684 = 0;

	::memset(m_unk0x3688, 0, sizeof(m_unk0x3688));
	::memset(m_unk0x325c, 0, sizeof(m_unk0x325c));
	m_unk0x36c0 = FALSE;

	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047bfc0
void EditCarScreen::FUN_0047bfc0()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\GARAGE");
	}

	CreateFramedSceneView(&m_unk0x43c, 0, 3);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	RacerModelSlot::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	createParams.m_golExport = m_golExport;
	createParams.m_renderer = m_renderer;
	createParams.m_unk0x08 = &m_unk0x43c;
	createParams.m_unk0x2c.m_x = 0.0f;
	createParams.m_unk0x2c.m_y = 0.0f;
	createParams.m_unk0x2c.m_z = 1.0f;
	createParams.m_unk0x40 = 0.001f;

	m_unk0x35b0.FUN_004875d0(&createParams);
	m_unk0x43c.FUN_00465b40(&m_unk0x35b0);
}

// FUNCTION: LEGORACERS 0x0047c080
void EditCarScreen::FUN_0047c080()
{
	CreateCarousel(&m_unk0x2384, 0x3e, 0x3b);
	CreateSelector(&m_unk0x2418, &m_unk0x2384, 0x95, 0x4d);

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x2e0c); i++) {
		CreateImage(&m_unk0x2e0c[i], 0x9d, static_cast<undefined2>(0x9e + i));
	}
}

// FUNCTION: LEGORACERS 0x0047c0e0
void EditCarScreen::VTable0x4c()
{
	CreateImage(&m_unk0x368, 0x49, 0x49);
	FUN_0047bfc0();
	CreateTextLabel(&m_unk0x3c4, 0x3a, 0x3a, 0x0b);
	m_unk0x3c4.FUN_0046f6b0(0x14);

	FUN_0047fdc0(&m_unk0x914, 0x9a, 0x42, 0x25);
	FUN_0047fdc0(&m_unk0xef4, 0x9b, 0x42, 0x3c);
	FUN_0047fdc0(&m_unk0xc04, 0x9c, 0x42, 0x3d);

	if (m_context->m_unk0x4b40.GetUnk0x78() & 1) {
		FUN_0047fdc0(&m_unk0x11e4, 0x40, 0x46, 0x1e);
		FUN_0047fdc0(&m_unk0x14d4, 0x3f, 0x43, 0x0a);
	}
	else {
		FUN_0047fdc0(&m_unk0x11e4, 0x40, 0x46, 0x72);
		FUN_0047fdc0(&m_unk0x14d4, 0x3f, 0x45, 0x1f);
	}

	FUN_0047c080();
}

// FUNCTION: LEGORACERS 0x0047c1d0
void EditCarScreen::VTable0x80()
{
	ColorRGBA materialColor;
	ColorRGBA lightColor;

	materialColor.m_blu = 0x78;
	materialColor.m_grn = 0x78;
	materialColor.m_red = 0x78;
	materialColor.m_alp = 0x78;
	lightColor.m_blu = 0x78;
	lightColor.m_grn = 0x78;
	lightColor.m_red = 0x78;
	lightColor.m_alp = 0x78;

	FUN_0047fec0(&materialColor, &lightColor);
}

// FUNCTION: LEGORACERS 0x0047c210
LegoBool32 EditCarScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	FUN_0047c400(p_context, p_createParams);

	if (!p_context->m_unk0x21f4.IsInitialized()) {
		FUN_0047ff50(p_context, TRUE);
	}

	if (!p_context->m_unk0x4b40.HasMenuResources()) {
		FUN_00480210(p_context, FALSE);
	}

	p_context->m_unk0x4ae0.SetUnk0x5c(1);

	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	FUN_0047c610();
	FUN_0047c450();
	FUN_0047c790();

	m_unk0x914.VTable0x4c(5);
	m_unk0x3650.FUN_00442e60(&p_context->m_unk0x258);
	m_unk0x3650.FUN_00442ef0(4);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047c2c0
LegoBool32 EditCarScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	m_unk0x34b0.VTable0x54();

	if (m_unk0x35a8) {
		m_golExport->VTable0x4c(m_unk0x35a8);
	}

	if (m_unk0x35a4) {
		m_golExport->VTable0x48(m_unk0x35a4);
	}

	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x0047c320
void EditCarScreen::FUN_0047c320()
{
	LegoS32 i;

	m_unk0x3684 = m_context->m_unk0x258.GetUnk0x18c4().FUN_0042f1e0();

	for (i = 0; i < 4; i++) {
		m_unk0x3688[i] = TRUE;
	}

	LegoU32 mask = 1;
	for (i = 0; i < 8; i++) {
		if (m_unk0x3684 & mask) {
			m_unk0x3688[i + 4] = TRUE;
		}
		mask <<= 1;
	}

	for (i = 0; i < m_context->m_unk0x21f4.GetPlacedPieceCount(); i++) {
		LegoS32 index = m_context->m_unk0x21a4.FindEntryIndex(m_context->m_unk0x21f4.FUN_0049bd50(i));
		m_unk0x3688[index] = TRUE;
	}

	for (i = 0; i < 12; i++) {
		if (m_unk0x3688[i]) {
			m_unk0x2384.FUN_0046d9c0(&m_unk0x2e0c[i]);
		}
	}
}

// FUNCTION: LEGORACERS 0x0047c400
void EditCarScreen::FUN_0047c400(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (g_editCarImageList != NULL) {
		return;
	}

	g_editCarImageList = p_createParams->m_golExport->VTable0x34();
	if (g_editCarImageList == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	g_editCarImageList->LoadImageDefinitions(
		p_createParams->m_renderer,
		"Builder",
		static_cast<LegoBool32>(p_context->m_context->m_unk0x18)
	);
}

// FUNCTION: LEGORACERS 0x0047c450
void EditCarScreen::FUN_0047c450()
{
	m_unk0x3678 = &m_context->m_unk0x258.GetUnk0x1cfc();
	m_unk0x3678->FUN_0042b360(m_unk0x325c);
	m_context->m_unk0x21f4.FUN_0049c7f0(m_unk0x325c);
	FUN_0047c320();

	if (m_context->m_unk0x21f4.GetPlacedPieceCount()) {
		LegoChar name[9];

		m_context->m_unk0x21f4.FUN_0049b740(0);
		m_context->m_unk0x21f4.FUN_0049b920(1, 0x7f);
		m_unk0x3678->FUN_0042b380(m_unk0x367c);

		::strncpy(name, m_unk0x367c, 8);
		name[8] = '\0';

		LegoPieceLibrary::PieceRecord* pieceRecord = m_context->m_pieceLibrary.FindPieceRecordByName(name);
		CarPartSet::Entry* entry = m_context->m_unk0x21a4.FindEntry(pieceRecord->m_pieceType);
		m_context->m_unk0x21a4.SetSelectedEntry(entry);

		LegoS32 index = entry->GetIndex();
		if (m_unk0x3688[index]) {
			m_unk0x2384.FUN_0046d920(&m_unk0x2e0c[index]);
		}

		FUN_0047c720();
	}
	else {
		m_unk0x2384.VTable0x50(0);
		VTable0x44(&m_unk0x2418);
	}
}

// FUNCTION: LEGORACERS 0x0047c5a0
void EditCarScreen::FUN_0047c5a0()
{
	::memset(m_unk0x325c, 0, sizeof(m_unk0x325c));
	m_context->m_unk0x21f4.FUN_0049c820(m_unk0x325c);
	m_context->m_unk0x258.GetUnk0x1cfc().FUN_0042b4f0(m_unk0x325c);
	m_context->m_unk0x258.GetUnk0x1cfc().GetUnk0x248()->FUN_0042b5c0(&m_context->m_unk0x258.GetUnk0x1cfc());

	m_unk0x36c0 = TRUE;
}

// FUNCTION: LEGORACERS 0x0047c610
void EditCarScreen::FUN_0047c610()
{
	TurquoiseGlowColor color;

	m_context->m_unk0x4b40.SetUnk0x10(0xffff);
	m_context->m_unk0x258.GetUnk0x1cfc().FUN_0042b330(&color);
	m_unk0x35a4 = m_context->m_unk0x4b40.FUN_0049db90(&color, NULL, 0);
	if (m_unk0x35a4 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_context->m_unk0x4b40.FUN_0049dce0(m_unk0x35a4, &color);

	m_unk0x35a8 = m_golExport->VTable0x18();
	m_unk0x35a8->VTable0x10(m_context->m_unk0x4b40.FUN_0049dc10(&color));
	if (m_unk0x35a8 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x35ac = m_context->m_unk0x4b40.FUN_0049dc50(&color);
	m_unk0x34b0.FUN_0040d550(m_unk0x35a4, m_unk0x35a8, m_unk0x35ac, g_editCarMaxFloat);
}

// FUNCTION: LEGORACERS 0x0047c720
void EditCarScreen::FUN_0047c720()
{
	AwardCinematicScreen::SceneEntityGroup::CreateParams createParams;
	createParams.m_unk0x00 = &m_context->m_unk0x42dc;
	createParams.m_unk0x04 = &m_context->m_unk0x21f4;
	createParams.m_unk0x08 = m_context->m_unk0x21f4.GetUnk0x0c();
	createParams.m_unk0x0c = &m_unk0x34b0;
	m_context->m_unk0x258.GetUnk0x1cfc().FUN_0042b380(createParams.m_unk0x10);

	m_unk0x3460.FUN_00479510(&createParams);
	m_unk0x35b0.FUN_00487600(&m_unk0x3460);
}

// STUB: LEGORACERS 0x0047c790
void EditCarScreen::FUN_0047c790()
{
	if (m_context->m_unk0x21f4.GetPlacedPieceCount() > 1) {
		if (!m_unk0x3678->FUN_0042b460()) {
			m_unk0x2418.VTable0x48(5);
			m_unk0xef4.VTable0x44(5);
			return;
		}

		m_unk0x2418.VTable0x44(5);
		m_unk0xef4.VTable0x44(5);
		return;
	}

	m_unk0x2418.VTable0x44(5);
	m_unk0xef4.VTable0x48(5);
}

// FUNCTION: LEGORACERS 0x0047c810
void EditCarScreen::FUN_0047c810()
{
	LegoS32 remaining = m_unk0x3650.FUN_00442e80(4);
	remaining += 5;

	GolName name;
	while (remaining != 0) {
		PeridotTraceBase0x24::Record* record = m_unk0x3650.FUN_00442fe0();
		remaining--;
		record->FUN_0042b380(name);
		if (::strncmp(m_unk0x367c, name, sizeof(name)) == 0) {
			record->FUN_0042b360(m_unk0x325c);

			CarBuildModel* model = &m_context->m_unk0x21f4;
			model->GetUnk0xa4().FUN_0049fd60();
			model->SetPlacedPieceCount(0);
			m_context->m_unk0x21f4.FUN_0049c7f0(m_unk0x325c);
			m_context->m_unk0x21f4.FUN_0049b740(0);
			m_context->m_unk0x21f4.FUN_0049b920(1, 0x7f);

			m_unk0x3678->FUN_0042b470();
			FUN_0047c790();
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x0047c900
LegoBool32 EditCarScreen::FUN_0047c900()
{
	LegoU8* buffer = new LegoU8[sizeof(m_unk0x325c)];
	if (buffer == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(buffer, 0, sizeof(m_unk0x325c));
	m_context->m_unk0x21f4.FUN_0049c820(buffer);
	m_unk0x3678->FUN_0042b360(m_unk0x325c);

	LegoBool32 result = ::memcmp(buffer, m_unk0x325c, sizeof(m_unk0x325c));
	delete[] buffer;
	return result;
}

// FUNCTION: LEGORACERS 0x0047c980
void EditCarScreen::VTable0x38(MenuWidget* p_source)
{
	if (p_source == &m_unk0x914) {
		m_unk0x360 = c_menuCarBuild;
	}
	else if (p_source == &m_unk0xc04) {
		if (m_unk0x3678 && m_unk0x3678->FUN_0042b460()) {
			VTable0x38(&m_unk0x1da4);
		}
		else {
			FUN_0047fdc0(&m_unk0x1da4, 0x99, 0x46, 0x20);
			FUN_0047fdc0(&m_unk0x1ab4, 0x99, 0x46, 0x1f);
			FUN_0046c6f0(&m_unk0x1da4, &m_unk0x1ab4, 0x7b);
		}
	}
	else if (p_source == &m_unk0xef4) {
		if (m_unk0x3678 && m_unk0x3678->FUN_0042b460()) {
			VTable0x38(&m_unk0x2094);
		}
		else {
			FUN_0047fdc0(&m_unk0x2094, 0x99, 0x46, 0x20);
			FUN_0047fdc0(&m_unk0x1ab4, 0x99, 0x46, 0x1f);
			FUN_0046c6f0(&m_unk0x2094, &m_unk0x1ab4, 0x7b);
		}
		FUN_0047c790();
	}
	else if (p_source == &m_unk0x11e4) {
		if (m_context->m_unk0x4b40.GetUnk0x78() & 1) {
			m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() & ~1);
			FUN_0047cde0();
		}
		FUN_0047c5a0();
		m_unk0x360 = c_menuGarage;
	}
	else if (p_source == &m_unk0x14d4) {
		if (m_context->m_unk0x4b40.GetUnk0x78() & 1) {
			m_unk0x360 = c_menuDriverLicense;
		}
		else if (FUN_0047c900()) {
			FUN_0047fdc0(&m_unk0x17c4, 0x99, 0x46, 0x20);
			FUN_0047fdc0(&m_unk0x1ab4, 0x99, 0x46, 0x1f);
			FUN_0046c6f0(&m_unk0x17c4, &m_unk0x1ab4, 0x7b);
		}
		else {
			VTable0x38(&m_unk0x17c4);
		}
	}
	else if (p_source == &m_unk0x17c4) {
		m_unk0x360 = c_menuGarage;
		if (m_unk0x284 && m_unk0x284->GetUnk0x9c()) {
			m_unk0x284->FUN_00468cf0();
		}
	}
	else if (p_source == &m_unk0x1ab4) {
		if (m_unk0x284 && m_unk0x284->GetUnk0x9c()) {
			m_unk0x284->FUN_00468cf0();
		}
	}
	else if (p_source == &m_unk0x1da4) {
		FUN_0047c810();
		if (m_unk0x284 && m_unk0x284->GetUnk0x9c()) {
			m_unk0x284->FUN_00468cf0();
		}
	}
	else if (p_source == &m_unk0x2094) {
		VTable0x44(&m_unk0x2418);
		if (m_unk0x284 && m_unk0x284->GetUnk0x9c()) {
			m_unk0x284->FUN_00468cf0();
		}
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
	}
	m_unk0x35c = p_source;
}

// FUNCTION: LEGORACERS 0x0047cbc0
void EditCarScreen::VTable0x44(MenuWidget* p_source)
{
	if (p_source != &m_unk0x2418) {
		return;
	}

	CarBuildModel* model = &m_context->m_unk0x21f4;
	model->GetUnk0xa4().FUN_0049fd60();
	model->SetPlacedPieceCount(0);

	MenuWidget* selectedChild = m_unk0x2384.GetUnk0x78();
	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x2e0c); i++) {
		if (selectedChild == &m_unk0x2e0c[i]) {
			m_context->m_unk0x21a4.SetSelectedEntry(&m_context->m_unk0x21a4.GetEntries()[i]);
			break;
		}
	}

	CarPartSet::Entry* entry = m_context->m_unk0x21a4.GetSelectedEntry();
	::strncpy(m_unk0x367c, entry->GetName(), sizeof(m_unk0x367c));

	LegoChar name[9];
	::strncpy(name, m_unk0x367c, sizeof(m_unk0x367c));
	name[8] = '\0';

	m_context->m_unk0x258.GetUnk0x1cfc().FUN_0042b510(m_unk0x367c);
	LegoPieceLibrary::PieceRecord* pieceRecord = m_context->m_pieceLibrary.FindPieceRecordByName(name);
	m_context->m_unk0x21f4.FUN_0049a160(pieceRecord, 0, 0, 0, 3, 0);
	m_context->m_unk0x21f4.FUN_0049b740(0);
	m_context->m_unk0x21f4.FUN_0049b920(1, 0x7f);

	m_unk0x3678->FUN_0042b470();
	FUN_0047c720();
	FUN_0047c790();
}

// FUNCTION: LEGORACERS 0x0047ccf0
void EditCarScreen::VTable0x84()
{
	switch (m_unk0x360) {
	case c_menuDriverLicense:
		m_context->m_menuStack.Pop();
		m_context->m_unk0x4ae0.SetUnk0x5c(0);
		if (g_editCarImageList) {
			m_golExport->VTable0x68(g_editCarImageList);
			g_editCarImageList = NULL;
		}
		m_context->m_unk0x21f4.FUN_0049c820(m_unk0x325c);
		m_unk0x3678->FUN_0042b4f0(m_unk0x325c);
		m_context->m_menuStack.Push(m_unk0x360);
		break;
	case c_menuCarBuild:
		m_context->m_menuStack.Push(m_unk0x360);
		break;
	case c_menuGarage:
		m_context->m_menuStack.Pop();
		if (m_unk0x36c0) {
			m_context->m_menuStack.Push(c_menuSaveAll);
		}
		m_context->m_unk0x4ae0.SetUnk0x5c(0);
		if (g_editCarImageList) {
			m_golExport->VTable0x68(g_editCarImageList);
			g_editCarImageList = NULL;
		}
		break;
	}
}

// FUNCTION: LEGORACERS 0x0047cde0
void EditCarScreen::FUN_0047cde0()
{
	MenuGameContext* context = m_context;
	PeridotTraceBase0x24::Record* record = context->m_unk0x258.GetUnk0x1cfc().GetUnk0x248();
	GameState& state = context->m_unk0x258.GetUnk0x18c4();
	undefined4 value = record->m_unk0x08;
	state.GetState().m_inputBindings.m_players[0].m_unk0x01 = static_cast<LegoU8>(value);
	state.SetUnk0x00(1);
	value = record->m_unk0x0c;
	state.GetState().m_inputBindings.m_players[0].m_unk0x02 = static_cast<LegoU8>(value);
	state.SetUnk0x00(1);
	value = record->m_unk0x10;
	state.GetState().m_inputBindings.m_players[0].m_unk0x00 = static_cast<LegoU8>(value);
	state.SetUnk0x00(1);
}

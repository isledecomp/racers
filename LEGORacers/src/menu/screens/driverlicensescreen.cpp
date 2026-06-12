#include "menu/screens/driverlicensescreen.h"

#include "input/inputdevice.h"
#include "input/keyboarddevice.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "surface/color.h"

#include <ctype.h>
#include <string.h>

DECOMP_SIZE_ASSERT(DriverLicenseScreen, 0x23bc)

// GLOBAL: LEGORACERS 0x004c1fec
LegoU32 g_unk0x4c1fec[2] = {1, 2};

// GLOBAL: LEGORACERS 0x004c1ff4
const LegoChar* g_cheatNames[] = {
	"NSLWJ",
	"FLYSKYHGH",
	"PGLLRD",
	"PGLLYLL",
	"PGLLGRN",
	"LNFRRRM",
	"RPCRNLY",
	"MXPMX",
	"FSTFRWRD",
	"NWHLS",
	"NCHSSS",
	"NDRVR",
	"NMRCHTS"
};

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void DriverLicenseScreen::VTable0x44(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void DriverLicenseScreen::VTable0x94(undefined4)
{
}

// FUNCTION: LEGORACERS 0x0047af30
DriverLicenseScreen::DriverLicenseScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047b090
DriverLicenseScreen::~DriverLicenseScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047b1d0
void DriverLicenseScreen::Reset()
{
	memset(GetCheatBuffer(), 0, sizeof(undefined2) * c_cheatBufferStorageLength);
	m_cheatString.CopyFromBufSelection(GetCheatBuffer(), c_cheatBufferLength);
	m_unk0x23b4 = TRUE;
	m_unk0x23b8 = FALSE;
	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047b220
void DriverLicenseScreen::FUN_0047b220()
{
	CreateFramedSceneView(&m_unk0x1648, 0, 0xd0);

	MainMenuModelSlot::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	createParams.m_golExport = m_golExport;
	createParams.m_renderer = m_renderer;
	createParams.m_unk0x08 = &m_unk0x1648;
	createParams.m_unk0x0c = &m_context->m_modelBuilder;
	createParams.m_position.m_x = -5.3593369f;
	createParams.m_position.m_y = -3.1500180f;
	createParams.m_position.m_z = 0.0f;

	m_unk0x224c.FUN_0047e0a0(&createParams);
	m_unk0x1648.FUN_00465b40(&m_unk0x224c);

	GolVec3 direction;
	direction.m_x = 1.0f;
	direction.m_y = 0.0f;
	direction.m_z = 0.0f;

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = -0.0348990f;
	up.m_z = 0.9993910f;
	m_unk0x224c.GetUnk0x1c()->VTable0x40(direction, up);
}

// FUNCTION: LEGORACERS 0x0047b300
void DriverLicenseScreen::VTable0x4c()
{
	CreateImage(&m_unk0x368, 0x49, 0x49);
	CreateImage(&m_unk0x3e4, 0xd6, 0xd6);
	CreateFrame(&m_unk0x1b20, 0xd9, 0x48);
	m_unk0x1b20.ClearFlags(2);

	CreateTextLabel(&m_unk0x720, 0x3a, 0x3a, 0x0a);
	m_unk0x720.FUN_0046f6b0(0x14);

	CreateTextField(&m_unk0x1f1c, 0xdb, 0xd7, 1, &m_cheatString);
	FUN_0047fdc0(&m_unk0x798, 0xdc, 0x42, 0x3b);

	if (m_context->m_modelBuilder.GetUnk0x78() & 1) {
		FUN_0047fdc0(&m_unk0xd78, 0x40, 0x44, 0x0b);
		FUN_0047fdc0(&m_unk0xa88, 0x3f, 0x43, 9);
	}
	else {
		FUN_0047fdc0(&m_unk0xd78, 0x40, 0x46, 0x72);
		FUN_0047fdc0(&m_unk0xa88, 0x3f, 0x45, 0x1f);
	}

	ActiveRecordBuffer& record = m_context->m_saveSystem.GetActiveRecord();
	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x440); i++) {
		switch (record.GetTrophy(i)) {
		case 1:
			CreateImage(&m_unk0x440[i], static_cast<undefined2>(i + 0xe0), 0xdd);
			break;
		case 2:
			CreateImage(&m_unk0x440[i], static_cast<undefined2>(i + 0xe0), 0xde);
			break;
		case 3:
			CreateImage(&m_unk0x440[i], static_cast<undefined2>(i + 0xe0), 0xdf);
			break;
		}
	}

	FUN_0047b220();
}

// FUNCTION: LEGORACERS 0x0047b470
LegoBool32 DriverLicenseScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	MenuGameContext* context = p_context;
	if (!context->m_modelBuilder.HasMenuResources()) {
		FUN_00480210(context, FALSE);
	}

	if (!MenuGameScreen::VTable0x8c(context, p_createParams)) {
		return FALSE;
	}

	GolAnimatedEntity* entity;
	ColorRGBA materialColor;
	ColorRGBA lightColor;
	materialColor.m_red = 0x78;
	materialColor.m_grn = 0x78;
	materialColor.m_blu = 0x78;
	lightColor.m_red = 0xb4;
	lightColor.m_grn = 0xb4;
	lightColor.m_blu = 0xb4;
	FUN_0047fec0(&materialColor, &lightColor);

	FUN_0047b6b0();
	m_unk0x224c.GetUnk0x118()->VTable0x14("cmaman", context->m_context->m_unk0x18);
	entity = m_unk0x224c.GetUnk0x1c();
	entity->FUN_0040dad0(0);
	entity->SetFlags(entity->GetFlags() | 0x10000);

	if (context->m_inputBindings.HasInputManager() && !context->m_inputBindings.HasKeyboard()) {
		m_unk0x1f1c.FUN_00471100(4);
	}

	static_cast<MenuIcon*>(&m_unk0x1f1c)->VTable0x4c(4);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047b550
LegoBool32 DriverLicenseScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	m_context->m_modelBuilder.SetExpressionMask(TRUE);
	return MenuGameScreen::Destroy();
}

// STUB: LEGORACERS 0x0047b580
LegoBool32 DriverLicenseScreen::FUN_0047b580()
{
	GolString name;
	DriverCosmetics cosmetics;
	undefined2 buffer[24];

	if (m_context->m_modelBuilder.GetUnk0x78() & 1) {
		return TRUE;
	}

	::memset(buffer, 0, sizeof(buffer));
	name.CopyFromBufSelection(buffer, 0x17);
	m_cheatString.CopyFromBufSelection(m_unk0x1f1c.GetBuffer(), 0);

	m_context->m_saveSystem.GetActiveRecord().GetName(&name);
	m_context->m_saveSystem.GetActiveRecord().GetCosmetics(&cosmetics);

	if (!name.GolStrcmp(&m_cheatString)) {
		return TRUE;
	}

	return cosmetics.m_hatIndex != GetUnk0x2244().m_expressionIndex;
}

// FUNCTION: LEGORACERS 0x0047b6b0
void DriverLicenseScreen::FUN_0047b6b0()
{
	DriverCosmetics* cosmetics;
	GolString* cheatString = &m_cheatString;
	m_context->m_saveSystem.GetActiveRecord().GetName(cheatString);

	cosmetics = &GetUnk0x2244();
	m_context->m_saveSystem.GetActiveRecord().GetCosmetics(cosmetics);

	m_context->m_modelBuilder.SetExpressionMask(0xffff);
	MainMenuModelSlot* preview = &m_unk0x224c;
	preview->FUN_0047e210(cosmetics);
	LegoU32 colorValue = GetUnk0x2244().m_faceIndex;
	LegoU32 colorIndex = GetUnk0x2244().m_expressionIndex;
	preview->FUN_0047e160(colorValue, colorIndex);

	if (cheatString->SelectionLength() == 0) {
		m_menuTextStrings->CopyStringByIndex(cheatString, 0x3a);
	}

	m_unk0x1f1c.FUN_004711f0(cheatString);
}

// STUB: LEGORACERS 0x0047b750
void DriverLicenseScreen::FUN_0047b750()
{
	if (m_cheatString.SelectionLength() == 0) {
		m_unk0x360 = 0xffff;
		m_unk0x364 = FALSE;
		return;
	}

	m_cheatString.CopyFromBufSelection(m_unk0x1f1c.GetBuffer(), 0);
	m_context->m_saveSystem.GetActiveRecord().SetName(&m_cheatString);
	m_context->m_saveSystem.GetActiveRecord().SetCosmetics(&GetUnk0x2244());

	if (!(m_context->m_modelBuilder.GetUnk0x78() & 1)) {
		m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord()->CopyFrom(
			&m_context->m_saveSystem.GetActiveRecord()
		);
		m_unk0x23b8 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0047b7f0
void DriverLicenseScreen::VTable0x84()
{
	m_context->m_menuStack.Pop();

	switch (m_unk0x360) {
	case 0x0f:
	case 0x11:
		m_context->m_menuStack.Push(m_unk0x360);
		break;
	}

	if (m_unk0x23b8) {
		m_context->m_menuStack.Push(0x30);
	}
}

// STUB: LEGORACERS 0x0047b850
void DriverLicenseScreen::VTable0x38(MenuWidget* p_source)
{
	if (p_source == &m_unk0x798) {
		LegoS32 colorIndex = GetUnk0x2244().m_expressionIndex;
		colorIndex++;
		GetUnk0x2244().m_expressionIndex = static_cast<LegoU8>(colorIndex % 6);
		m_unk0x224c.FUN_0047e160(GetUnk0x2244().m_faceIndex, GetUnk0x2244().m_expressionIndex);
	}
	else if (p_source == &m_unk0xd78) {
		if (m_context->m_modelBuilder.GetUnk0x78() & 1) {
			m_unk0x360 = 0x11;
		}
		else {
			m_unk0x360 = 3;
		}
		FUN_0047b750();
		ApplyCheatCode();
	}
	else if (p_source == &m_unk0xa88) {
		if (m_context->m_modelBuilder.GetUnk0x78() & 1) {
			m_unk0x360 = 0x0f;
			FUN_0047b750();
			ApplyCheatCode();
		}
		else if (FUN_0047b580()) {
			FUN_0047fdc0(&m_unk0x1068, 0x99, 0x46, 0x20);
			FUN_0047fdc0(&m_unk0x1358, 0x99, 0x45, 0x1f);
			FUN_0046c6f0(&m_unk0x1068, &m_unk0x1358, 0x7b);
		}
		else {
			m_unk0x360 = 3;
		}
	}
	else if (p_source == &m_unk0x1068) {
		m_unk0x360 = 3;
		m_unk0x284->FUN_00468cf0();
	}
	else if (p_source == &m_unk0x1358) {
		m_unk0x284->FUN_00468cf0();
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
	}
	m_unk0x35c = p_source;
}

// FUNCTION: LEGORACERS 0x0047b9c0
void DriverLicenseScreen::VTable0x40(MenuIcon* p_source)
{
	if (p_source == &m_unk0x1f1c) {
		m_unk0x1b20.ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x0047b9e0
void DriverLicenseScreen::VTable0x3c(MenuIcon* p_source)
{
	if (p_source == &m_unk0x1f1c) {
		m_unk0x1b20.SetFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x0047ba00
void DriverLicenseScreen::ApplyCheatCode()
{
	LegoChar buf[14];
	m_cheatString.CopyToString(buf);
	buf[13] = '\0';

	for (LegoU32 i = 0; i < sizeOfArray(g_cheatNames); ++i) {
		if (strcmp(g_cheatNames[i], buf) == 0) {
			if (i < sizeOfArray(g_cheatNames) - 1) {
				LegoU32 flag = 1 << i;
				LegoU32 current = m_context->m_context->m_unk0x20;

				if (current & flag) {
					m_context->m_context->m_unk0x20 = current & ~flag;
				}
				else {
					m_context->m_context->m_unk0x20 = current | flag;

					switch (flag) {
					case c_pgllrd:
						m_context->m_context->m_unk0x20 &= ~(c_pgllyll | c_pgllgrn | c_rpcrnly);
						break;
					case c_pgllyll:
						m_context->m_context->m_unk0x20 &= ~(c_pgllrd | c_pgllgrn | c_rpcrnly);
						break;
					case c_pgllgrn:
						m_context->m_context->m_unk0x20 &= ~(c_pgllrd | c_pgllyll | c_rpcrnly);
						break;
					case c_rpcrnly:
						m_context->m_context->m_unk0x20 &= ~(c_pgllrd | c_pgllyll | c_pgllgrn | c_mxpmx);
						break;
					case c_mxpmx:
						m_context->m_context->m_unk0x20 &= ~c_rpcrnly;
						break;
					case c_nwhls: {
						LegoU32 v = m_context->m_context->m_unk0x20;
						if ((v & c_nchsss) && (v & c_ndrvr)) {
							m_context->m_context->m_unk0x20 = v & ~c_ndrvr;
						}
						break;
					}
					case c_nchsss: {
						LegoU32 v = m_context->m_context->m_unk0x20;
						if ((v & c_nwhls) && (v & c_ndrvr)) {
							m_context->m_context->m_unk0x20 = v & ~c_nwhls;
						}
						break;
					}
					case c_ndrvr: {
						LegoU32 v = m_context->m_context->m_unk0x20;
						if ((v & c_nchsss) && (v & c_nwhls)) {
							m_context->m_context->m_unk0x20 = v & ~c_nchsss;
						}
						break;
					}
					}
				}
			}
			else if (i == sizeOfArray(g_cheatNames) - 1) {
				m_context->m_context->m_unk0x20 = 0;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0047bbf0
void DriverLicenseScreen::VTable0x90(undefined4 p_keyCode)
{
	LegoU32 keyCode = p_keyCode;
	InputDevice* keyboard = m_inputManager->GetKeyboard();

	LegoU16 character = static_cast<LegoU16>(keyCode);
	if (character >= 0x80 && character > 0xe0) {
		keyCode += 0xffe0;
	}
	else if (islower(character)) {
		keyCode += 0xffe0;
	}

	m_inputEvents->OnKeyDown(keyboard, (keyCode & InputDevice::c_keyCodeMask) | InputDevice::c_sourceCharacter, 0);
}

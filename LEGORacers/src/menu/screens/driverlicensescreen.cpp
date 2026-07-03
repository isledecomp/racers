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
void DriverLicenseScreen::OnWidgetValueChanged(MenuWidget*)
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
	memset(GetNameBuffer(), 0, sizeof(undefined2) * c_cheatBufferStorageLength);
	m_nameString.CopyFromBufSelection(GetNameBuffer(), c_cheatBufferLength);
	m_unk0x23b4 = TRUE;
	m_savePending = FALSE;
	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047b220
void DriverLicenseScreen::CreateDriverScene()
{
	CreateFramedSceneView(&m_sceneView, 0, 0xd0);

	MainMenuModelSlot::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	createParams.m_golExport = m_golExport;
	createParams.m_renderer = m_renderer;
	createParams.m_sceneView = &m_sceneView;
	createParams.m_modelBuilder = &m_context->m_modelBuilder;
	createParams.m_position.m_x = -5.3593369f;
	createParams.m_position.m_y = -3.1500180f;
	createParams.m_position.m_z = 0.0f;

	m_modelSlot.Create(&createParams);
	m_sceneView.AddElement(&m_modelSlot);

	GolVec3 direction;
	direction.m_x = 1.0f;
	direction.m_y = 0.0f;
	direction.m_z = 0.0f;

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = -0.0348990f;
	up.m_z = 0.9993910f;
	m_modelSlot.GetDriverEntity()->SetDirectionUp(direction, up);
}

// FUNCTION: LEGORACERS 0x0047b300
void DriverLicenseScreen::CreateWidgets()
{
	CreateImage(&m_photoImage, 0x49, 0x49);
	CreateImage(&m_licenseImage, 0xd6, 0xd6);
	CreateFrame(&m_nameFieldFrame, 0xd9, 0x48);
	m_nameFieldFrame.ClearFlags(2);

	CreateTextLabel(&m_infoLabel, 0x3a, 0x3a, 0x0a);
	m_infoLabel.WrapText(0x14);

	CreateTextField(&m_nameEntry, 0xdb, 0xd7, 1, &m_nameString);
	CreateTextButton(&m_expressionButton, 0xdc, 0x42, 0x3b);

	if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
		CreateTextButton(&m_doneButton, 0x40, 0x44, 0x0b);
		CreateTextButton(&m_backButton, 0x3f, 0x43, 9);
	}
	else {
		CreateTextButton(&m_doneButton, 0x40, 0x46, 0x72);
		CreateTextButton(&m_backButton, 0x3f, 0x45, 0x1f);
	}

	ActiveRecordBuffer& record = m_context->m_saveSystem.GetActiveRecord();
	for (LegoU32 i = 0; i < sizeOfArray(m_trophyImages); i++) {
		switch (record.GetTrophy(i)) {
		case 1:
			CreateImage(&m_trophyImages[i], static_cast<undefined2>(i + 0xe0), 0xdd);
			break;
		case 2:
			CreateImage(&m_trophyImages[i], static_cast<undefined2>(i + 0xe0), 0xde);
			break;
		case 3:
			CreateImage(&m_trophyImages[i], static_cast<undefined2>(i + 0xe0), 0xdf);
			break;
		}
	}

	CreateDriverScene();
}

// FUNCTION: LEGORACERS 0x0047b470
LegoBool32 DriverLicenseScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	MenuGameContext* context = p_context;
	if (!context->m_modelBuilder.HasMenuResources()) {
		LoadPartResources(context, FALSE);
	}

	if (!MenuGameScreen::Initialize(context, p_createParams)) {
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
	SetLighting(&materialColor, &lightColor);

	LoadLicenseData();
	m_modelSlot.GetBodyModelPart()->Load("cmaman", context->m_context->m_useBinaryFiles);
	entity = m_modelSlot.GetDriverEntity();
	entity->PlayPart(0);
	entity->SetFlags(entity->GetFlags() | 0x10000);

	if (context->m_inputBindings.HasInputManager() && !context->m_inputBindings.HasKeyboard()) {
		m_nameEntry.HandleEditAction(4);
	}

	static_cast<MenuIcon*>(&m_nameEntry)->Select(4);

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
LegoBool32 DriverLicenseScreen::HasUnsavedChanges()
{
	GolString name;
	DriverCosmetics cosmetics;
	undefined2 buffer[24];

	if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
		return TRUE;
	}

	::memset(buffer, 0, sizeof(buffer));
	name.CopyFromBufSelection(buffer, 0x17);
	m_nameString.CopyFromBufSelection(m_nameEntry.GetBuffer(), 0);

	m_context->m_saveSystem.GetActiveRecord().GetName(&name);
	m_context->m_saveSystem.GetActiveRecord().GetCosmetics(&cosmetics);

	if (!name.GolStrcmp(&m_nameString)) {
		return TRUE;
	}

	return cosmetics.m_expressionIndex != GetCosmetics().m_expressionIndex;
}

// FUNCTION: LEGORACERS 0x0047b6b0
void DriverLicenseScreen::LoadLicenseData()
{
	DriverCosmetics* cosmetics;
	GolString* cheatString = &m_nameString;
	m_context->m_saveSystem.GetActiveRecord().GetName(cheatString);

	cosmetics = &GetCosmetics();
	m_context->m_saveSystem.GetActiveRecord().GetCosmetics(cosmetics);

	m_context->m_modelBuilder.SetExpressionMask(0xffff);
	MainMenuModelSlot* preview = &m_modelSlot;
	preview->SetCosmetics(cosmetics);
	LegoU32 colorValue = GetCosmetics().m_faceIndex;
	LegoU32 colorIndex = GetCosmetics().m_expressionIndex;
	preview->SetFace(colorValue, colorIndex);

	if (cheatString->SelectionLength() == 0) {
		m_menuTextStrings->CopyStringByIndex(cheatString, 0x3a);
	}

	m_nameEntry.SetText(cheatString);
}

// FUNCTION: LEGORACERS 0x0047b750
void DriverLicenseScreen::SaveLicenseData()
{
	GolString* cheatString = &m_nameString;

	if (cheatString->SelectionLength() == 0) {
		m_nextMenuId = 0xffff;
		m_navPending = FALSE;
		return;
	}

	cheatString->CopyFromBufSelection(m_nameEntry.GetBuffer(), 0);
	ActiveRecordBuffer& record = m_context->m_saveSystem.GetActiveRecord();
	record.SetName(cheatString);
	record.SetCosmetics(&GetCosmetics());

	if ((m_context->m_modelBuilder.GetMenuFlowFlags() == 0) & TRUE) {
		m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord()->CopyFrom(
			&m_context->m_saveSystem.GetActiveRecord()
		);
		m_savePending = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0047b7f0
void DriverLicenseScreen::Navigate()
{
	m_context->m_menuStack.Pop();

	switch (m_nextMenuId) {
	case 0x0f:
	case 0x11:
		m_context->m_menuStack.Push(m_nextMenuId);
		break;
	}

	if (m_savePending) {
		m_context->m_menuStack.Push(0x30);
	}
}

// FUNCTION: LEGORACERS 0x0047b850
void DriverLicenseScreen::OnIconUnfocused(MenuWidget* p_source)
{
	LegoBool32 updateRecord = FALSE;

	if (p_source == &m_expressionButton) {
		LegoS32 colorIndex = GetCosmetics().m_expressionIndex;
		colorIndex++;
		GetCosmetics().m_expressionIndex = static_cast<LegoU8>(colorIndex % 6);
		m_modelSlot.SetFace(GetCosmetics().m_faceIndex, GetCosmetics().m_expressionIndex);
	}
	else if (p_source == &m_doneButton) {
		if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
			m_nextMenuId = 0x11;
		}
		else {
			m_nextMenuId = 3;
		}
		updateRecord = TRUE;
	}
	else if (p_source == &m_backButton) {
		if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
			m_nextMenuId = 0x0f;
			updateRecord = TRUE;
		}
		else if (HasUnsavedChanges()) {
			CreateTextButton(&m_confirmYesButton, 0x99, 0x46, 0x20);
			CreateTextButton(&m_confirmNoButton, 0x99, 0x45, 0x1f);
			ShowConfirmDialog(&m_confirmYesButton, &m_confirmNoButton, 0x7b);
		}
		else {
			m_nextMenuId = 3;
		}
	}
	else if (p_source == &m_confirmYesButton) {
		m_nextMenuId = 3;
		m_dialog->DismissTop();
	}
	else if (p_source == &m_confirmNoButton) {
		m_dialog->DismissTop();
	}

	if (updateRecord) {
		SaveLicenseData();
		ApplyCheatCode();
	}

	if (m_nextMenuId != 0xffff) {
		m_navPending = TRUE;
	}
	m_clickedWidget = p_source;
}

// FUNCTION: LEGORACERS 0x0047b9c0
void DriverLicenseScreen::OnIconDeselected(MenuIcon* p_source)
{
	if (p_source == &m_nameEntry) {
		m_nameFieldFrame.ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x0047b9e0
void DriverLicenseScreen::OnIconSelected(MenuIcon* p_source)
{
	if (p_source == &m_nameEntry) {
		m_nameFieldFrame.SetFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x0047ba00
void DriverLicenseScreen::ApplyCheatCode()
{
	LegoChar buf[14];
	m_nameString.CopyToString(buf);
	buf[13] = '\0';

	for (LegoU32 i = 0; i < sizeOfArray(g_cheatNames); ++i) {
		if (strcmp(g_cheatNames[i], buf) == 0) {
			if (i < sizeOfArray(g_cheatNames) - 1) {
				LegoU32 flag = 1 << i;
				LegoU32 current = m_context->m_context->m_cheatFlags;

				if (current & flag) {
					m_context->m_context->m_cheatFlags = current & ~flag;
				}
				else {
					m_context->m_context->m_cheatFlags = current | flag;

					switch (flag) {
					case c_pgllrd:
						m_context->m_context->m_cheatFlags &= ~(c_pgllyll | c_pgllgrn | c_rpcrnly);
						break;
					case c_pgllyll:
						m_context->m_context->m_cheatFlags &= ~(c_pgllrd | c_pgllgrn | c_rpcrnly);
						break;
					case c_pgllgrn:
						m_context->m_context->m_cheatFlags &= ~(c_pgllrd | c_pgllyll | c_rpcrnly);
						break;
					case c_rpcrnly:
						m_context->m_context->m_cheatFlags &= ~(c_pgllrd | c_pgllyll | c_pgllgrn | c_mxpmx);
						break;
					case c_mxpmx:
						m_context->m_context->m_cheatFlags &= ~c_rpcrnly;
						break;
					case c_nwhls: {
						LegoU32 v = m_context->m_context->m_cheatFlags;
						if ((v & c_nchsss) && (v & c_ndrvr)) {
							m_context->m_context->m_cheatFlags = v & ~c_ndrvr;
						}
						break;
					}
					case c_nchsss: {
						LegoU32 v = m_context->m_context->m_cheatFlags;
						if ((v & c_nwhls) && (v & c_ndrvr)) {
							m_context->m_context->m_cheatFlags = v & ~c_nwhls;
						}
						break;
					}
					case c_ndrvr: {
						LegoU32 v = m_context->m_context->m_cheatFlags;
						if ((v & c_nchsss) && (v & c_nwhls)) {
							m_context->m_context->m_cheatFlags = v & ~c_nchsss;
						}
						break;
					}
					}
				}
			}
			else if (i == sizeOfArray(g_cheatNames) - 1) {
				m_context->m_context->m_cheatFlags = 0;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0047bbf0
void DriverLicenseScreen::OnChar(undefined4 p_keyCode)
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

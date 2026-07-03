#include "menu/screens/editcarscreen.h"

#include "cmbmodelpart.h"
#include "core/gol.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "golstream.h"
#include "material/golimagedefinitionlist.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "racer/drivercosmetics.h"
#include "racer/drivermodelbuilder.h"
#include "surface/color.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(EditCarScreen, 0x36c4)

// GLOBAL: LEGORACERS 0x004b3290
static const LegoFloat g_editCarMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004c766c
static GolImageDefinitionList* g_editCarImageList = NULL;

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
	m_activeRecord = NULL;
	m_driverModel = NULL;
	m_bodySceneNode = NULL;
	m_partCategoryUnlockFlags = 0;

	::memset(m_partCategoryAvailable, 0, sizeof(m_partCategoryAvailable));
	::memset(m_carBuildSaveBuffer, 0, sizeof(m_carBuildSaveBuffer));
	m_savePending = FALSE;

	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047bfc0
void EditCarScreen::CreateCarScene()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\GARAGE");
	}

	CreateFramedSceneView(&m_sceneView, 0, 3);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	RacerModelSlot::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	createParams.m_golExport = m_golExport;
	createParams.m_renderer = m_renderer;
	createParams.m_sceneView = &m_sceneView;
	createParams.m_position.m_x = 0.0f;
	createParams.m_position.m_y = 0.0f;
	createParams.m_position.m_z = 1.0f;
	createParams.m_spinSpeed = 0.001f;

	m_modelSlot.Create(&createParams);
	m_sceneView.AddElement(&m_modelSlot);
}

// FUNCTION: LEGORACERS 0x0047c080
void EditCarScreen::CreateCategoryCarousel()
{
	CreateCarousel(&m_categoryCarousel, 0x3e, 0x3b);
	CreateSelector(&m_categorySelector, &m_categoryCarousel, 0x95, 0x4d);

	for (LegoU32 i = 0; i < sizeOfArray(m_categoryIcons); i++) {
		CreateImage(&m_categoryIcons[i], 0x9d, static_cast<undefined2>(0x9e + i));
	}
}

// FUNCTION: LEGORACERS 0x0047c0e0
void EditCarScreen::CreateWidgets()
{
	CreateImage(&m_photoImage, 0x49, 0x49);
	CreateCarScene();
	CreateTextLabel(&m_infoLabel, 0x3a, 0x3a, 0x0b);
	m_infoLabel.WrapText(0x14);

	CreateTextButton(&m_buildButton, 0x9a, 0x42, 0x25);
	CreateTextButton(&m_newCarButton, 0x9b, 0x42, 0x3c);
	CreateTextButton(&m_quickBuildButton, 0x9c, 0x42, 0x3d);

	if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
		CreateTextButton(&m_doneButton, 0x40, 0x46, 0x1e);
		CreateTextButton(&m_backButton, 0x3f, 0x43, 0x0a);
	}
	else {
		CreateTextButton(&m_doneButton, 0x40, 0x46, 0x72);
		CreateTextButton(&m_backButton, 0x3f, 0x45, 0x1f);
	}

	CreateCategoryCarousel();
}

// FUNCTION: LEGORACERS 0x0047c1d0
void EditCarScreen::SetupLighting()
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

	SetLighting(&materialColor, &lightColor);
}

// FUNCTION: LEGORACERS 0x0047c210
LegoBool32 EditCarScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	LoadBuilderImages(p_context, p_createParams);

	if (!p_context->m_carBuildModel.IsInitialized()) {
		LoadPieceResources(p_context, TRUE);
	}

	if (!p_context->m_modelBuilder.HasMenuResources()) {
		LoadPartResources(p_context, FALSE);
	}

	p_context->m_partResources.SetResourceIndex(1);

	if (!MenuGameScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	CreateDriverModel();
	LoadCarData();
	UpdateButtonStates();

	m_buildButton.Select(5);
	m_recordCursor.SetSaveSystem(&p_context->m_saveSystem);
	m_recordCursor.Begin(4);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047c2c0
LegoBool32 EditCarScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	m_driverEntity.ResetModelState();

	if (m_bodySceneNode) {
		m_golExport->DestroySceneNode(m_bodySceneNode);
	}

	if (m_driverModel) {
		m_golExport->DestroyModel(m_driverModel);
	}

	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x0047c320
void EditCarScreen::PopulateCategoryCarousel()
{
	LegoS32 i;
	LegoU32 mask = 1;

	SaveSystem* saveSystem = &m_context->m_saveSystem;
	m_partCategoryUnlockFlags = saveSystem->GetGameState().GetPartUnlockFlags();

	for (i = 0; i < 4; i++) {
		m_partCategoryAvailable[i] = TRUE;
	}

	for (i = 0; i < 8; i++) {
		if (m_partCategoryUnlockFlags & mask) {
			m_partCategoryAvailable[i + 4] = TRUE;
		}
		mask <<= 1;
	}

	for (i = 0; i < m_context->m_carBuildModel.GetPlacedPieceCount(); i++) {
		LegoS32 index = m_context->m_partSet.FindEntryIndex(m_context->m_carBuildModel.GetPiecePartType(i));
		m_partCategoryAvailable[index] = TRUE;
	}

	for (i = 0; i < 12; i++) {
		if (m_partCategoryAvailable[i]) {
			m_categoryCarousel.AddItem(&m_categoryIcons[i]);
		}
	}
}

// FUNCTION: LEGORACERS 0x0047c400
void EditCarScreen::LoadBuilderImages(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (g_editCarImageList != NULL) {
		return;
	}

	g_editCarImageList = p_createParams->m_golExport->CreateImageList();
	if (g_editCarImageList == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	g_editCarImageList->LoadImageDefinitions(
		p_createParams->m_renderer,
		"Builder",
		static_cast<LegoBool32>(p_context->m_context->m_useBinaryFiles)
	);
}

// FUNCTION: LEGORACERS 0x0047c450
void EditCarScreen::LoadCarData()
{
	m_activeRecord = &m_context->m_saveSystem.GetActiveRecord();
	m_activeRecord->CopyCarData(m_carBuildSaveBuffer);
	m_context->m_carBuildModel.Deserialize(m_carBuildSaveBuffer);
	PopulateCategoryCarousel();

	if (m_context->m_carBuildModel.GetPlacedPieceCount()) {
		LegoChar name[9];

		m_context->m_carBuildModel.UpdateOffset(0);
		m_context->m_carBuildModel.RebuildModel(1, 0x7f);
		m_context->m_saveSystem.GetActiveRecord().GetChassisName(m_chassisName);

		::strncpy(name, m_chassisName, 8);
		name[8] = '\0';

		LegoPieceLibrary::PieceRecord* pieceRecord = m_context->m_pieceLibrary.FindPieceRecordByName(name);
		LegoS32 pieceType = pieceRecord->m_pieceType;
		m_context->m_partSet.SetSelectedEntry(m_context->m_partSet.FindEntry(pieceType));

		LegoS32 index = m_context->m_partSet.GetSelectedEntry()->GetIndex();
		if (m_partCategoryAvailable[index]) {
			m_categoryCarousel.SelectChild(&m_categoryIcons[index]);
		}

		CreateCarGroup();
	}
	else {
		m_categoryCarousel.SetSelection(0);
		OnWidgetValueChanged(&m_categorySelector);
	}
}

// FUNCTION: LEGORACERS 0x0047c5a0
void EditCarScreen::SaveCarData()
{
	::memset(m_carBuildSaveBuffer, 0, sizeof(m_carBuildSaveBuffer));
	m_context->m_carBuildModel.Serialize(m_carBuildSaveBuffer);
	m_context->m_saveSystem.GetActiveRecord().SetCarData(m_carBuildSaveBuffer);
	m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord()->CopyFrom(&m_context->m_saveSystem.GetActiveRecord());

	m_savePending = TRUE;
}

// FUNCTION: LEGORACERS 0x0047c610
void EditCarScreen::CreateDriverModel()
{
	DriverCosmetics cosmetics;

	m_context->m_modelBuilder.SetExpressionMask(0xffff);
	m_context->m_saveSystem.GetActiveRecord().GetCosmetics(&cosmetics);
	m_driverModel = m_context->m_modelBuilder.BuildDriverModel(&cosmetics, NULL, 0);
	if (m_driverModel == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_context->m_modelBuilder.ApplyFaceExpression(m_driverModel, &cosmetics);

	m_bodySceneNode = m_golExport->CreateSceneNode();
	m_bodySceneNode->CopyFrom(m_context->m_modelBuilder.GetBodySceneNode(&cosmetics));
	if (m_bodySceneNode == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_bodyModelPart = m_context->m_modelBuilder.GetBodyModelPart(&cosmetics);
	m_driverEntity.SetModel(m_driverModel, m_bodySceneNode, m_bodyModelPart, g_editCarMaxFloat);
}

// FUNCTION: LEGORACERS 0x0047c720
void EditCarScreen::CreateCarGroup()
{
	AwardCinematicScreen::SceneEntityGroup::CreateParams createParams;
	createParams.m_chassisModels = &m_context->m_chassisModels;
	createParams.m_buildModel = &m_context->m_carBuildModel;
	createParams.m_carEntity = m_context->m_carBuildModel.GetModelEntity();
	createParams.m_driverEntity = &m_driverEntity;
	m_context->m_saveSystem.GetActiveRecord().GetChassisName(createParams.m_chassisName);

	m_carGroup.Create(&createParams);
	m_modelSlot.SetEntity(&m_carGroup);
}

// FUNCTION: LEGORACERS 0x0047c790
void EditCarScreen::UpdateButtonStates()
{
	if (m_context->m_carBuildModel.GetPlacedPieceCount() > 1) {
		if (!m_activeRecord->IsCarSaved()) {
			m_categorySelector.Disable(5);
		}
		else {
			m_categorySelector.Enable(5);
		}

		m_newCarButton.Enable(5);
	}
	else {
		m_categorySelector.Enable(5);
		m_newCarButton.Disable(5);
	}
}

// FUNCTION: LEGORACERS 0x0047c810
void EditCarScreen::LoadQuickBuildCar()
{
	LegoS32 remaining = m_recordCursor.CountRecords(4);
	remaining += 5;

	GolName name;
	while (remaining != 0) {
		SaveRecordList::Record* record = m_recordCursor.SelectNext();
		remaining--;
		record->GetChassisName(name);
		if (::strncmp(m_chassisName, name, sizeof(name)) == 0) {
			record->CopyCarData(m_carBuildSaveBuffer);

			CarBuildModel* model = &m_context->m_carBuildModel;
			model->GetPieceList().RemoveAllEntries();
			model->SetPlacedPieceCount(0);
			m_context->m_carBuildModel.Deserialize(m_carBuildSaveBuffer);
			m_context->m_carBuildModel.UpdateOffset(0);
			m_context->m_carBuildModel.RebuildModel(1, 0x7f);

			m_activeRecord->MarkCarSaved();
			UpdateButtonStates();
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x0047c900
LegoBool32 EditCarScreen::HasUnsavedChanges()
{
	LegoU8* buffer = new LegoU8[sizeof(m_carBuildSaveBuffer)];
	if (buffer == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(buffer, 0, sizeof(m_carBuildSaveBuffer));
	m_context->m_carBuildModel.Serialize(buffer);
	m_activeRecord->CopyCarData(m_carBuildSaveBuffer);

	LegoBool32 result = ::memcmp(buffer, m_carBuildSaveBuffer, sizeof(m_carBuildSaveBuffer));
	delete[] buffer;
	return result;
}

// FUNCTION: LEGORACERS 0x0047c980
void EditCarScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_buildButton) {
		m_nextMenuId = c_menuCarBuild;
	}
	else if (p_source == &m_quickBuildButton) {
		if (m_activeRecord->IsCarSaved()) {
			OnIconUnfocused(&m_quickBuildYesButton);
		}
		else {
			CreateTextButton(&m_quickBuildYesButton, 0x99, 0x46, 0x20);
			CreateTextButton(&m_confirmNoButton, 0x99, 0x45, 0x1f);
			ShowConfirmDialog(&m_quickBuildYesButton, &m_confirmNoButton, 0x7b);
		}
	}
	else if (p_source == &m_newCarButton) {
		if (m_activeRecord->IsCarSaved()) {
			OnIconUnfocused(&m_newCarYesButton);
		}
		else {
			CreateTextButton(&m_newCarYesButton, 0x99, 0x46, 0x20);
			CreateTextButton(&m_confirmNoButton, 0x99, 0x45, 0x1f);
			ShowConfirmDialog(&m_newCarYesButton, &m_confirmNoButton, 0x7b);
		}
		UpdateButtonStates();
	}
	else if (p_source == &m_doneButton) {
		if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
			m_context->m_modelBuilder.SetMenuFlowFlags(
				m_context->m_modelBuilder.GetMenuFlowFlags() & ~DriverModelBuilder::c_menuFlowNewRacer
			);
			SetPlayerOneRecord();
		}
		SaveCarData();
		m_nextMenuId = c_menuGarage;
	}
	else if (p_source == &m_backButton) {
		if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowNewRacer) {
			m_nextMenuId = c_menuDriverLicense;
		}
		else if (HasUnsavedChanges()) {
			CreateTextButton(&m_discardYesButton, 0x99, 0x46, 0x20);
			CreateTextButton(&m_confirmNoButton, 0x99, 0x45, 0x1f);
			ShowConfirmDialog(&m_discardYesButton, &m_confirmNoButton, 0x7b);
		}
		else {
			OnIconUnfocused(&m_discardYesButton);
		}
	}
	else if (p_source == &m_discardYesButton) {
		m_nextMenuId = c_menuGarage;
		if (m_dialog->GetOpenCount() > 0) {
			m_dialog->DismissTop();
		}
	}
	else if (p_source == &m_confirmNoButton) {
		m_dialog->DismissTop();
	}
	else if (p_source == &m_quickBuildYesButton) {
		LoadQuickBuildCar();
		if (m_dialog->GetOpenCount() > 0) {
			m_dialog->DismissTop();
		}
	}
	else if (p_source == &m_newCarYesButton) {
		OnWidgetValueChanged(&m_categorySelector);
		if (m_dialog->GetOpenCount() > 0) {
			m_dialog->DismissTop();
		}
	}

	if (m_nextMenuId != 0xffff) {
		m_navPending = TRUE;
	}
	m_clickedWidget = p_source;
}

// FUNCTION: LEGORACERS 0x0047cbc0
void EditCarScreen::OnWidgetValueChanged(MenuWidget* p_source)
{
	if (p_source != &m_categorySelector) {
		return;
	}

	CarBuildModel* model = &m_context->m_carBuildModel;
	model->GetPieceList().RemoveAllEntries();
	model->SetPlacedPieceCount(0);

	MenuWidget* selectedChild = m_categoryCarousel.GetSelectedChild();
	for (LegoU32 i = 0; i < sizeOfArray(m_categoryIcons); i++) {
		if (selectedChild == &m_categoryIcons[i]) {
			m_context->m_partSet.SetSelectedEntry(&m_context->m_partSet.GetEntries()[i]);
			break;
		}
	}

	CarPartSet::Entry* entry = m_context->m_partSet.GetSelectedEntry();
	::strncpy(m_chassisName, entry->GetName(), sizeof(m_chassisName));

	LegoChar name[9];
	::strncpy(name, m_chassisName, sizeof(m_chassisName));
	name[8] = '\0';

	m_context->m_saveSystem.GetActiveRecord().SetChassisName(m_chassisName);
	LegoPieceLibrary::PieceRecord* pieceRecord = m_context->m_pieceLibrary.FindPieceRecordByName(name);
	m_context->m_carBuildModel.PlacePiece(pieceRecord, 0, 0, 0, 3, 0);
	m_context->m_carBuildModel.UpdateOffset(0);
	m_context->m_carBuildModel.RebuildModel(1, 0x7f);

	m_activeRecord->MarkCarSaved();
	CreateCarGroup();
	UpdateButtonStates();
}

// FUNCTION: LEGORACERS 0x0047ccf0
void EditCarScreen::Navigate()
{
	switch (m_nextMenuId) {
	case c_menuDriverLicense:
		m_context->m_menuStack.Pop();
		m_context->m_partResources.SetResourceIndex(0);
		if (g_editCarImageList) {
			m_golExport->DestroyImageList(g_editCarImageList);
			g_editCarImageList = NULL;
		}
		m_context->m_carBuildModel.Serialize(m_carBuildSaveBuffer);
		m_activeRecord->SetCarData(m_carBuildSaveBuffer);
		m_context->m_menuStack.Push(m_nextMenuId);
		break;
	case c_menuCarBuild:
		m_context->m_menuStack.Push(m_nextMenuId);
		break;
	case c_menuGarage:
		m_context->m_menuStack.Pop();
		if (m_savePending) {
			m_context->m_menuStack.Push(c_menuSaveAll);
		}
		m_context->m_partResources.SetResourceIndex(0);
		if (g_editCarImageList) {
			m_golExport->DestroyImageList(g_editCarImageList);
			g_editCarImageList = NULL;
		}
		break;
	}
}

// FUNCTION: LEGORACERS 0x0047cde0
void EditCarScreen::SetPlayerOneRecord()
{
	MenuGameContext* context = m_context;
	SaveRecordList::Record* record = context->m_saveSystem.GetActiveRecord().GetSelectedRecord();
	GameState& state = context->m_saveSystem.GetGameState();
	LegoU32 value = record->m_recordSource;
	state.GetState().m_inputBindings.m_players[0].m_selectedRecordSource = static_cast<LegoU8>(value);
	state.SetDirty(1);
	value = record->m_saveIndex;
	state.GetState().m_inputBindings.m_players[0].m_selectedSaveIndex = static_cast<LegoU8>(value);
	state.SetDirty(1);
	value = record->m_recordId;
	state.GetState().m_inputBindings.m_players[0].m_selectedRecordId = static_cast<LegoU8>(value);
	state.SetDirty(1);
}

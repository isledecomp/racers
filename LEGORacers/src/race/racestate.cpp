#include "race/racestate.h"

#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmaterial.h"
#include "golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/racecameracontroller.h"
#include "race/raceeventtable.h"
#include "race/raceforcefeedback.h"
#include "race/racehud.h"
#include "race/racer/racerouterecord.h"
#include "race/racesession.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/gold3dtexture.h"
#include "util/carshadowrenderstate.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern LegoFloat g_carBuildPreviewMouseScale;
extern const LegoFloat g_carBuildModelTextureCoordinateScale;
extern LegoFloat g_minSoundPan;

DECOMP_SIZE_ASSERT(RaceState, 0x320)
DECOMP_SIZE_ASSERT(RaceState::RacerProgressEntry, 0x0c)
DECOMP_SIZE_ASSERT(RaceRoster, 0x194)
DECOMP_SIZE_ASSERT(RaceSetup, 0x1c)

extern const LegoFloat g_ghostAnimationRateScale;
extern const LegoFloat g_ghostSampleFractionScale;
extern const LegoFloat g_sweepCannonRadiansToTableIndex;
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_violetShoalTwo;
extern LegoU32 g_silhouetteClearFlag;
extern LegoU32 g_silhouetteFlattenFlag;
extern LegoFloat g_cosineTable[1024];

extern const LegoFloat g_twoPi;
extern const LegoFloat g_pathMinSegmentLengthSquared;

extern const LegoFloat g_unk0x004b02e0;
extern const LegoChar* g_racerDatabaseNames[3];
extern const LegoFloat g_rubberBandScale;
extern const LegoFloat g_proximityPitchFloor;
extern const LegoFloat g_proximityPitchBand;
extern const LegoFloat g_proximityPitchSpeedRange;
extern const LegoFloat g_carModelScale;
extern const LegoFloat g_proximitySoundMinDistance;
extern const LegoFloat g_proximitySoundMaxDistance;

DECOMP_SIZE_ASSERT(RaceRouteRecord, 0x48)
DECOMP_SIZE_ASSERT(Racer::StandingsDeltaEntry, 0x0c)

// FUNCTION: LEGORACERS 0x0043a410
RaceSetup::RaceSetup()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a420
RaceSetup::~RaceSetup()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0043a430
void RaceSetup::Reset()
{
	m_racers = NULL;
	m_racerCount = 0;
	m_updateDelayMs = 0;
	m_rubberBandBoost = 0.0f;
}

// FUNCTION: LEGORACERS 0x0043a440
void RaceSetup::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a450
void RaceSetup::Initialize(Racer* p_racers, LegoU32 p_racerCount)
{
	if (m_racers) {
		Destroy();
	}

	m_racers = p_racers;
	m_racerCount = p_racerCount;
	m_updateDelayMs = 15000;
}

// FUNCTION: LEGORACERS 0x0043a480
LegoU32 RaceSetup::Update(LegoU32 p_elapsedMs)
{
	LegoU32 delayMs = m_updateDelayMs;
	LegoFloat bestProgress = -1.0f;
	LegoU32 result;

	if (p_elapsedMs > delayMs) {
		result = m_racerCount;
		LegoU32 racerIndex = 0;
		LegoU32 ignoredState;
		m_updateDelayMs = 0;

		if (result <= 0) {
			goto ResetRacerPacing;
		}

		ignoredState = 2;
		do {
			LegoU32 state = m_racers[racerIndex].m_controlMode;
			if (state != ignoredState && m_racers[racerIndex].GetRaceProgress() > bestProgress) {
				bestProgress = m_racers[racerIndex].GetRaceProgress();
			}

			result = m_racerCount;
			racerIndex++;
		} while (racerIndex < result);

		if (bestProgress == g_minSoundPan) {
		ResetRacerPacing:
			result = m_racerCount;
			LegoU32 index = 0;
			if (result > 0) {
				LegoU32 pushedMask = RacerPhysics::c_flagRoutePushed;
				do {
					Racer* racer = &m_racers[index];
					if (!(racer->m_flags & c_rubberBandFlags)) {
						LegoU32 physicsFlags = racer->m_physics.m_flags;
						racer->m_physics.m_routeBaseSpeed = 1.0f;
						if (!(pushedMask & physicsFlags)) {
							racer->m_physics.m_routeTargetSpeed = 1.0f;
						}
					}

					result = m_racerCount;
					index++;
				} while (index < result);
			}
		}
		else {
			result = m_racerCount;
			racerIndex = 0;
			if (result > 0) {
				LegoU32 pushedMask = RacerPhysics::c_flagRoutePushed;
				do {
					if (racerIndex) {
						if (!(m_racers[racerIndex].m_flags & c_rubberBandFlags)) {
							if (m_racers[racerIndex].GetRaceProgress() > bestProgress) {
								LegoFloat adjustment = 1.0f - g_rubberBandScale;
								adjustment += m_rubberBandBoost;
								RacerPhysics* physics = &m_racers[racerIndex].m_physics;
								LegoU32 physicsFlags = physics->m_flags;
								physics->m_routeBaseSpeed = adjustment;
								if (!(pushedMask & physicsFlags)) {
									physics->m_routeTargetSpeed = adjustment;
								}
							}
							else if (m_racers[racerIndex].GetRaceProgress() < bestProgress) {
								LegoFloat adjustment = g_rubberBandScale + m_rubberBandBoost;
								adjustment += 1.0f;
								RacerPhysics* physics = &m_racers[racerIndex].m_physics;
								LegoU32 physicsFlags = physics->m_flags;
								physics->m_routeBaseSpeed = adjustment;
								if (!(pushedMask & physicsFlags)) {
									physics->m_routeTargetSpeed = adjustment;
								}
							}
						}
					}

					result = m_racerCount;
					racerIndex++;
				} while (racerIndex < result);
			}
		}
	}
	else {
		result = delayMs - p_elapsedMs;
		m_updateDelayMs = result;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0043ae40
RaceState::RaceState()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043aee0
RaceState::~RaceState()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0043af80
void RaceState::Reset()
{
	m_roster.m_racers = NULL;
	m_roster.m_checkpointGraph = NULL;
	m_roster.m_racerCount = 0;
	m_roster.m_soundSource = NULL;

	LegoS32 i;
	for (i = 0; i < sizeOfArray(m_roster.m_racerEvents); i++) {
		m_roster.m_racerEvents[i] = 0;
		m_roster.m_startPositions[i].m_x = 0.0f;
		m_roster.m_startPositions[i].m_y = 0.0f;
		m_roster.m_startPositions[i].m_z = 0.0f;
		m_roster.m_startDirections[i].m_x = 0.0f;
		m_roster.m_startDirections[i].m_y = 0.0f;
		m_roster.m_startDirections[i].m_z = 0.0f;
		m_roster.m_startUps[i].m_x = 0.0f;
		m_roster.m_startUps[i].m_y = 0.0f;
		m_roster.m_startUps[i].m_z = 0.0f;
		m_roster.m_placementSlots[i] = 0;
	}

	m_roster.m_proximitySound = NULL;
	m_roster.m_currentRacer = NULL;
	m_roster.m_golExport = NULL;
	m_roster.m_timeRaceManager = NULL;

	for (i = 0; i < sizeOfArray(m_roster.m_customCarModels); i++) {
		m_roster.m_customCarModels[i] = 0;
		m_roster.m_customCarEntities[i] = 0;
	}

	m_roster.m_customCarCount = 0;
	m_roster.m_routeRecords = NULL;
	m_setup.m_textureList = 0;
	m_setup.m_materialLibrary = 0;
	m_setup.m_lapCount = 0;
}

// FUNCTION: LEGORACERS 0x0043b030
void RaceState::Destroy()
{
	m_setup.Destroy();

	if (m_setup.m_materialLibrary) {
		m_roster.m_golExport->DestroyMaterialList(m_setup.m_materialLibrary);
		m_setup.m_materialLibrary = NULL;
	}

	if (m_setup.m_textureList) {
		m_roster.m_golExport->DestroyTextureList(m_setup.m_textureList);
		m_setup.m_textureList = NULL;
	}

	LegoS32 i;
	for (i = 0; i < 2; i++) {
		if (m_roster.m_customCarModels[i]) {
			delete m_roster.m_customCarModels[i];
			m_roster.m_customCarModels[i] = NULL;
		}

		if (m_roster.m_customCarEntities[i]) {
			delete m_roster.m_customCarEntities[i];
			m_roster.m_customCarEntities[i] = NULL;
		}
	}

	GolNameTable* table = &m_chassisTable;
	table->Clear();

	table = &m_championList;
	table->Clear();

	table = &m_driverTable;
	table->Clear();

	if (m_roster.m_proximitySound) {
		m_roster.m_soundSource->ReleaseSound(m_roster.m_proximitySound);
		m_roster.m_proximitySound = NULL;
	}

	LegoU32 racerIndex;
	for (racerIndex = 0; racerIndex < m_roster.m_racerCount; racerIndex++) {
		if (m_roster.m_racerEvents[racerIndex]) {
			m_roster.m_racerEvents[racerIndex]->m_active = 0;
			m_roster.m_racerEvents[racerIndex] = NULL;
		}
	}

	LegoEventQueue* queue = &m_roster;
	queue->Destroy();

	if (m_roster.m_racers) {
		for (racerIndex = 0; racerIndex < m_roster.m_racerCount; racerIndex++) {
			(*(m_roster.m_racers + racerIndex)).Destroy();
		}

		delete[] m_roster.m_racers;

		m_roster.m_racers = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0043b190
void RaceState::CreateRacers(CreateRacersParams* p_params, RacerContext* p_context, LegoBool32 p_binary)
{
	m_roster.m_checkpointGraph = p_context->m_checkpointGraph;
	m_roster.m_soundSource = p_context->m_soundSource;
	m_roster.m_powerupManager = p_context->m_powerupManager;
	m_roster.m_golExport = p_context->m_golExport;
	m_roster.m_timeRaceManager = p_params->m_timeRaceManager;
	m_roster.m_routeRecords = p_params->m_routeRecords;
	m_setup.m_lapCount = p_params->m_lapCount;
	static_cast<LegoEventQueue*>(&m_roster)->Initialize(100);

	m_roster.m_raceState = this;
	m_roster.m_racerCount = p_params->m_racerCount;
	m_roster.m_racers = new Racer[m_roster.m_racerCount];
	if (m_roster.m_racers == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_setup.m_textureList = m_roster.m_golExport->CreateTextureList();
	m_setup.m_materialLibrary = m_roster.m_golExport->CreateMaterialList();
	m_setup.m_textureList->Initialize(p_context->m_renderer, m_roster.m_racerCount);
	m_setup.m_materialLibrary->Initialize(p_context->m_renderer, m_roster.m_racerCount);

	DriverCosmeticTable::LoadParams driverParams;
	driverParams.m_golExport = p_context->m_golExport;
	driverParams.m_renderer = p_context->m_renderer;
	driverParams.m_entryCapacity = m_roster.m_racerCount;
	driverParams.m_filename = g_racerDatabaseNames[0];
	driverParams.m_binary = p_binary;
	m_driverTable.Load(&driverParams);

	ChampionDefinitionList::LoadParams championParams;
	championParams.m_golExport = p_context->m_golExport;
	championParams.m_renderer = p_context->m_renderer;
	championParams.m_entryCapacity = m_roster.m_racerCount;
	championParams.m_fileName = g_racerDatabaseNames[1];
	championParams.m_binary = p_binary;
	m_championList.Load(&championParams);

	ChassisModelTable::Params chassisParams;
	chassisParams.m_golExport = p_context->m_golExport;
	chassisParams.m_renderer = p_context->m_renderer;
	chassisParams.m_instantiateCount = m_roster.m_racerCount;
	chassisParams.m_filename = g_racerDatabaseNames[2];
	chassisParams.m_binary = p_binary;
	m_chassisTable.Load(&chassisParams);

	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		p_context->m_routeRecord = p_params->m_racerRoutes[i];
		CreateRacer(p_params->m_slots[i], p_context, i, p_params->m_splitScreen);
	}

	m_chassisTable.ReleaseInstances();
	m_championList.ClearDefinitions();
	m_driverTable.ClearEntries();
	m_setup.m_textureList->LoadTextures();
	m_setup.m_materialLibrary->CreateMaterials();
	m_setup.Initialize(m_roster.m_racers, m_roster.m_racerCount);
}

// STUB: LEGORACERS 0x0043b480
void RaceState::CreateRacer(
	LegoRacers::Context::PlayerSetupSlot* p_slot,
	RacerContext* p_context,
	LegoU32 p_racerIndex,
	undefined4 p_splitScreen
)
{
	Racer::SetupParams racerParams;
	CarVisuals::InitParams initParams;
	::memset(&racerParams, 0, sizeof(racerParams));
	::memset(&initParams, 0, sizeof(initParams));

	ChampionDefinitionList::ChampionDefinition* championDefinition = NULL;
	ChassisModelTable::Item* chassisItem;
	if (p_slot->m_driverName[0]) {
		DriverCosmeticTable::Entry* driverEntry =
			static_cast<DriverCosmeticTable::Entry*>(m_driverTable.GetName(p_slot->m_driverName));

		initParams.m_driverEntity = m_driverTable.LoadEntry(p_slot->m_driverName);
		championDefinition = static_cast<ChampionDefinitionList::ChampionDefinition*>(
			m_championList.GetName(driverEntry->m_championName)
		);
		initParams.m_bodyModel = m_championList.CreateChampionModel(driverEntry->m_championName);
		chassisItem = static_cast<ChassisModelTable::Item*>(m_chassisTable.GetName(championDefinition->m_chassisName));
		m_chassisTable.InstantiateModels(chassisItem, &initParams.m_carEntity, &initParams.m_secondaryModel);

		racerParams.m_handlingStat = chassisItem->m_handlingStat;
		racerParams.m_accelerationStat = chassisItem->m_accelerationStat;
		racerParams.m_topSpeedStat = chassisItem->m_topSpeedStat;
		racerParams.m_driverStats[0] = driverEntry->m_redStat;
		racerParams.m_driverStats[1] = driverEntry->m_yellowStat;
		racerParams.m_driverStats[2] = driverEntry->m_greenStat;
		racerParams.m_driverStats[3] = driverEntry->m_blueStat;
		racerParams.m_driverStats[4] = driverEntry->m_stat4;
		racerParams.m_driverStats[5] = driverEntry->m_stat5;
		racerParams.m_voiceBank = driverEntry->m_voiceBankIndex * 12 + 1100;

		switch (driverEntry->m_aiChargeColor) {
		case 1:
		case 2:
		case 3:
		case 4:
			racerParams.m_aiChargeColor = driverEntry->m_aiChargeColor;
			break;
		default:
			racerParams.m_aiChargeColor = 0;
			break;
		}

		racerParams.m_aiChargeTarget = driverEntry->m_aiChargeTarget;
		racerParams.m_displayNameWide = m_driverTable.GetStringBuffer(p_slot->m_driverName);
	}
	else {
		LegoU32 customIndex = m_roster.m_customCarCount;
		m_roster.m_customCarModels[customIndex] = new GolModelEntity;
		if (m_roster.m_customCarModels[customIndex] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_roster.m_customCarEntities[customIndex] = new GolAnimatedEntity;
		if (m_roster.m_customCarEntities[customIndex] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		p_slot->m_textures->LoadTextures();
		p_slot->m_materials->CreateMaterials();
		initParams.m_bodyModel = m_roster.m_customCarModels[customIndex];
		initParams.m_bodyModel->SetPrimaryModel(p_slot->m_model, g_carModelScale);

		if (p_slot->m_altModel == NULL) {
			LegoChar fallbackName[3];
			fallbackName[0] = 'b';
			fallbackName[1] = 'b';
			fallbackName[2] = '\0';
			m_driverTable.GetName(fallbackName);
			initParams.m_driverEntity = m_driverTable.LoadEntry(fallbackName);
		}
		else {
			p_slot->m_altTextures->LoadTextures();
			p_slot->m_altMaterials->CreateMaterials();
			initParams.m_driverEntity = m_roster.m_customCarEntities[customIndex];
			initParams.m_driverEntity
				->SetModel(p_slot->m_altModel, m_driverTable.m_rootNode, &m_driverTable.m_modelParts, g_carModelScale);
		}

		chassisItem = static_cast<ChassisModelTable::Item*>(m_chassisTable.GetName(p_slot->m_chassisName));
		m_chassisTable.InstantiateModels(chassisItem, &initParams.m_carEntity, &initParams.m_secondaryModel);
		racerParams.m_handlingStat = chassisItem->m_handlingStat;
		racerParams.m_accelerationStat = chassisItem->m_accelerationStat;
		racerParams.m_topSpeedStat = chassisItem->m_topSpeedStat;

		for (LegoU32 i = 0; i < sizeOfArray(racerParams.m_driverStats); i++) {
			racerParams.m_driverStats[i] = 100;
		}

		racerParams.m_voiceBank = p_racerIndex * 100 + 1000;
		::strcpy(racerParams.m_displayName, p_slot->m_playerName);
		m_roster.m_customCarCount = customIndex + 1;
	}

	initParams.m_driverMountOffset = chassisItem->m_driverMountOffset;
	initParams.m_racer = &m_roster.m_racers[p_racerIndex];
	initParams.m_shadowWidth = chassisItem->m_shadowSize.m_x;
	initParams.m_shadowLength = chassisItem->m_shadowSize.m_y;
	initParams.m_frontSkidWidth = chassisItem->m_skidWidths.m_x;
	initParams.m_rearSkidWidth = chassisItem->m_skidWidths.m_y;
	::strncpy(initParams.m_materialName, "carshad", sizeof(initParams.m_materialName));
	initParams.m_materialName[sizeof(initParams.m_materialName) - 1] = static_cast<LegoChar>('0' + p_racerIndex);

	for (LegoU32 i = 0; i < sizeOfArray(initParams.m_wheelOffsets); i++) {
		initParams.m_wheelOffsets[i] = chassisItem->m_wheelOffsets[i];
	}

	racerParams.m_anchorWheelPosition = chassisItem->m_wheelPositions[1];
	racerParams.m_rearWheelY0 = chassisItem->m_wheelPositions[2].m_y;
	racerParams.m_rearWheelX = chassisItem->m_wheelPositions[3].m_x;
	racerParams.m_rearWheelY1 = chassisItem->m_wheelPositions[3].m_y;

	racerParams.m_lapCount = m_setup.m_lapCount;
	racerParams.m_eventTable = p_context->m_eventTable;
	racerParams.m_surfaceTable = p_context->m_surfaceTable;
	racerParams.m_trackWorld = p_context->m_trackWorld;
	racerParams.m_enginePitchScale = chassisItem->m_enginePitchScale;

	if (championDefinition) {
		racerParams.m_centerOfMass.m_x = championDefinition->m_centerOfMassX;
		racerParams.m_centerOfMass.m_y = championDefinition->m_centerOfMassY;
		racerParams.m_centerOfMass.m_z = championDefinition->m_centerOfMassZ;
		racerParams.m_mass = championDefinition->m_mass;
		racerParams.m_weight = 0.0f;
	}
	else {
		racerParams.m_centerOfMass.m_x =
			p_slot->m_centroidX * g_carBuildModelTextureCoordinateScale + chassisItem->m_centerOfMass.m_x;
		racerParams.m_centerOfMass.m_y =
			p_slot->m_centroidY * g_carBuildModelTextureCoordinateScale + chassisItem->m_centerOfMass.m_y;
		racerParams.m_centerOfMass.m_z = chassisItem->m_centerOfMass.m_z;
		racerParams.m_mass = chassisItem->m_baseMass + p_slot->m_highPieceCount;
		racerParams.m_weight = p_slot->m_highPieceCount;
	}

	m_roster.m_placementSlots[p_racerIndex] = p_racerIndex;
	if (m_roster.m_timeRaceManager) {
		if (m_roster.m_timeRaceManager->HasRecordRunLapTimes()) {
			m_roster.m_placementSlots[p_racerIndex] = 2;
		}
		else {
			m_roster.m_placementSlots[p_racerIndex] = 1;
		}
	}
	else if (p_splitScreen && p_racerIndex == 0) {
		m_roster.m_placementSlots[0] = 2;
	}

	LegoU32 placementIndex = m_roster.m_placementSlots[p_racerIndex];
	initParams.m_carEntity->SetPosition(m_roster.m_startPositions[placementIndex]);
	initParams.m_carEntity->SetDirectionUp(
		m_roster.m_startDirections[placementIndex],
		m_roster.m_startUps[placementIndex]
	);

	m_roster.m_racers[p_racerIndex].Initialize(p_context, &initParams, &racerParams, this, p_racerIndex);

	GolD3DTexture* shadowTexture = m_setup.m_textureList->GetItem(p_racerIndex);
	GolMaterial* shadowMaterial = m_setup.m_materialLibrary->GetItem(p_racerIndex);
	shadowTexture->SetNameFromBuffer(chassisItem->m_shadowName);
	shadowTexture->SetTextureFlags(GolTexture::c_textureFlagFlipVertically | GolTexture::c_textureFlagBmpSource);
	shadowMaterial->SetName(chassisItem->m_shadowName);

	GolMaterialParams shadowMaterialParams;
	::memset(&shadowMaterialParams, 0, sizeof(shadowMaterialParams));
	shadowMaterialParams.m_flags = GolMaterial::c_flagGouraudShading | GolMaterial::c_flagTextured |
								   GolMaterial::c_flagModulate | GolMaterial::c_flagNoAlphaTest |
								   GolMaterial::c_flagNoAlphaBlend | GolMaterial::c_flagLinearFilter |
								   GolMaterial::c_flagNoTransparency | GolMaterial::c_flagWrap |
								   GolMaterial::c_flagBit20 | GolMaterial::c_flagBit22;
	shadowMaterialParams.m_texture = shadowTexture;
	shadowMaterial->SetParams(p_context->m_renderer, shadowMaterialParams);

	Racer* racer = &m_roster.m_racers[p_racerIndex];
	racer->m_driveController.m_previewCursor = &m_sharedRouteCursor;

	LegoEventQueue::Descriptor descriptor;
	descriptor.m_type = LegoEventQueue::Descriptor::c_typeCollision;
	descriptor.m_flags = 5;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_data = &racer->m_physics;
	descriptor.m_elapsedMs = 0;
	m_roster.m_racerEvents[p_racerIndex] = m_roster.AllocateEvent(racer, &descriptor);
}

// FUNCTION: LEGORACERS 0x0043bc10
void RaceState::LoadStartPositions(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".spb");
	}
	else {
		parser = new SpbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(SpbTxtParser::e_startPosition));
	LegoU32 count = parser->ReadBracketedCountAndLeftCurly();

	if (count > 0) {
		LegoU32 remaining = count;
		do {
			parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(SpbTxtParser::e_startPosition));
			LegoU32 index = parser->ReadInteger();
			parser->ReadLeftCurly();

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				switch (token) {
				case SpbTxtParser::e_position:
					m_roster.m_startPositions[index].m_x = parser->ReadFloat();
					m_roster.m_startPositions[index].m_y = parser->ReadFloat();
					m_roster.m_startPositions[index].m_z = parser->ReadFloat();
					if (p_mirror) {
						m_roster.m_startPositions[index].m_y = -m_roster.m_startPositions[index].m_y;
					}
					break;
				case SpbTxtParser::e_orientation:
					m_roster.m_startDirections[index].m_x = parser->ReadFloat();
					m_roster.m_startDirections[index].m_y = parser->ReadFloat();
					m_roster.m_startDirections[index].m_z = parser->ReadFloat();
					m_roster.m_startUps[index].m_x = parser->ReadFloat();
					m_roster.m_startUps[index].m_y = parser->ReadFloat();
					m_roster.m_startUps[index].m_z = parser->ReadFloat();
					if (p_mirror) {
						m_roster.m_startDirections[index].m_y = -m_roster.m_startDirections[index].m_y;
						m_roster.m_startUps[index].m_y = -m_roster.m_startUps[index].m_y;
					}
					break;
				default:
					parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}

				token = parser->GetNextToken();
			}
		} while (--remaining);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x0043be60
void RaceState::InitializeRacerVisuals(GolD3DRenderDevice* p_renderer, GolExport* p_golExport)
{
	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		m_roster.m_racers[i].m_visuals.InitializeVisuals(p_renderer, p_golExport);
	}
}

// FUNCTION: LEGORACERS 0x0043beb0
void RaceState::RecordBestTimes(LegoRacers::Context* p_context)
{
	LegoU32 bestLapTime = c_invalidTime;
	LegoU32 bestRaceTime = c_invalidTime;
	LegoU32 bestRacerIndex = c_invalidTime;
	LegoU32 racerCount = m_roster.m_racerCount;

	if (racerCount > 0) {
		LegoU32 racerIndex;

		racerIndex = 0;
		do {
			if (!p_context->m_playerSetupSlots[racerIndex].m_slotState) {
				Racer* racer = &m_roster.m_racers[racerIndex];
				LegoU32 lapCount = m_setup.m_lapCount;
				if (lapCount <= racer->m_lapsCompleted) {
					if (lapCount) {
						LegoU32 remaining = lapCount;
						LegoU32 raceTime = 0;
						LegoU32* lapTimes = racer->m_lapTimes;

						do {
							LegoU32 lapTime = *lapTimes;
							if (lapTime < bestLapTime) {
								bestLapTime = lapTime;
								bestRacerIndex = racerIndex;
							}
							raceTime += lapTime;
							lapTimes++;
						} while (--remaining);

						if (raceTime < bestRaceTime) {
							bestRaceTime = raceTime;
						}
					}
					else if (0 < bestRaceTime) {
						bestRaceTime = 0;
					}
				}
			}

			racerIndex++;
		} while (racerIndex < racerCount);
	}

	if (bestLapTime < c_invalidTime) {
		LegoU32* lapRecord = &p_context->m_bestLapTimes[p_context->m_currentRaceIndex];
		if (!*lapRecord || bestLapTime <= *lapRecord) {
			*lapRecord = bestLapTime;
			p_context->m_bestLapHolders[p_context->m_currentRaceIndex] = bestRacerIndex;
		}
	}

	if (bestRaceTime < c_invalidTime) {
		LegoU32* raceRecord = &p_context->m_bestRaceTimes[p_context->m_currentRaceIndex];
		if (!*raceRecord || bestRaceTime <= *raceRecord) {
			*raceRecord = bestRaceTime;
			p_context->m_bestRaceHolders[p_context->m_currentRaceIndex] = bestRacerIndex;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043bff0
void RaceState::DrawRacersTransparent(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		m_roster.m_racers[i].m_visuals.DrawTransparent(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x0043c030
void RaceState::UpdateRacers(LegoU32 p_elapsedMs)
{
	Racer* racer = m_roster.m_racers;
	Racer* end = racer + m_roster.m_racerCount;

	for (; racer < end; racer++) {
		if (racer->m_driveController.m_flags & DriveController::c_flagBrakeToStop) {
			racer->m_driveController.UpdateBrakeToStop(p_elapsedMs);
		}
		else {
			if (racer->m_controlMode != Racer::c_controlAi) {
				racer->m_driveController.Update(p_elapsedMs);
			}
			else if (racer->m_driveController.m_flags & DriveController::c_flagReturnToPath) {
				racer->m_driveController.UpdateReturnToPath(p_elapsedMs);
			}
		}
	}

	for (racer = m_roster.m_racers; racer < end; racer++) {
		racer->m_physics.Update(p_elapsedMs);
	}

	for (racer = m_roster.m_racers; racer < end; racer++) {
		if (racer->m_flags & Racer::c_flagDrifting) {
			racer->UpdateDriftLean();
		}
	}

	RaceRoster* queue = &m_roster;
	queue->Update(p_elapsedMs);

	for (racer = m_roster.m_racers; racer < end; racer++) {
		racer->UpdateCarAnimation(p_elapsedMs);
	}

	for (racer = m_roster.m_racers; racer < end; racer++) {
		racer->UpdateEngineSound(p_elapsedMs);
		racer->UpdateSpatialSounds();
	}

	for (racer = m_roster.m_racers; racer < end; racer++) {
		racer->UpdateTimers(p_elapsedMs);
	}

	UpdateStandings();
	m_setup.Update(p_elapsedMs);
}

// STUB: LEGORACERS 0x0043c1b0
void RaceState::UpdateStandings()
{
	RaceState::RacerProgressEntry* entries = g_racerProgressEntries;
	LegoU32 racerCount = m_roster.m_racerCount;

	LegoU32 racerIndex;
	for (racerIndex = 0; racerIndex < racerCount; racerIndex++) {
		Racer* racer = &m_roster.m_racers[racerIndex];
		entries[racerIndex].m_racer = racer;
		entries[racerIndex].m_progress = racer->GetRaceProgress();
	}

	LegoU32 sortIndex;
	for (sortIndex = 0; sortIndex + 1 < racerCount; sortIndex++) {
		LegoU32 minIndex = sortIndex;
		LegoFloat minProgress = entries[sortIndex].m_progress;

		LegoU32 scanIndex;
		for (scanIndex = sortIndex + 1; scanIndex < racerCount; scanIndex++) {
			if (minProgress > entries[scanIndex].m_progress) {
				minProgress = entries[scanIndex].m_progress;
				minIndex = scanIndex;
			}
		}

		if (minIndex > sortIndex) {
			LegoFloat progress = entries[sortIndex].m_progress;
			entries[sortIndex].m_progress = entries[minIndex].m_progress;
			entries[minIndex].m_progress = progress;

			Racer* racer = entries[sortIndex].m_racer;
			entries[sortIndex].m_racer = entries[minIndex].m_racer;
			entries[minIndex].m_racer = racer;
		}
	}

	LegoU32 groupStart;
	for (groupStart = 0; groupStart + 1 < racerCount;) {
		LegoU32 groupEnd = groupStart + 1;
		while (groupEnd < racerCount && entries[groupStart].m_progress == entries[groupEnd].m_progress) {
			groupEnd++;
		}

		CheckpointGraph::Entry* pathField = entries[groupStart].m_racer->m_checkpoint;
		if (groupEnd > groupStart + 1 && pathField) {
			LegoU32 tiedIndex;
			for (tiedIndex = groupStart; tiedIndex < groupEnd; tiedIndex++) {
				GolVec3 position;
				entries[tiedIndex].m_racer->m_visuals.m_carEntity->GetPosition(&position);

				LegoFloat nearestPlaneDistance = FLT_MAX;
				LegoU32 planeIndex;
				for (planeIndex = 0; planeIndex < sizeOfArray(pathField->m_next.m_items); planeIndex++) {
					if (pathField->m_next.m_items[planeIndex] != 0xff) {
						CheckpointGraph::Entry* plane =
							m_roster.m_checkpointGraph->GetCheckpoint(pathField->m_next.m_items[planeIndex]);
						LegoFloat distance = plane->m_planeNormal.m_x * position.m_x +
											 plane->m_planeNormal.m_y * position.m_y +
											 plane->m_planeNormal.m_z * position.m_z + plane->m_planeDistance;
						if (distance < nearestPlaneDistance) {
							nearestPlaneDistance = distance;
						}
					}
				}

				entries[tiedIndex].m_tieBreakDistance = nearestPlaneDistance;
			}

			LegoU32 tiedSortIndex;
			for (tiedSortIndex = groupStart; tiedSortIndex + 1 < groupEnd; tiedSortIndex++) {
				LegoU32 maxIndex = tiedSortIndex;
				LegoFloat maxDistance = entries[tiedSortIndex].m_tieBreakDistance;

				LegoU32 tiedScanIndex;
				for (tiedScanIndex = tiedSortIndex + 1; tiedScanIndex < groupEnd; tiedScanIndex++) {
					if (maxDistance < entries[tiedScanIndex].m_tieBreakDistance) {
						maxDistance = entries[tiedScanIndex].m_tieBreakDistance;
						maxIndex = tiedScanIndex;
					}
				}

				if (maxIndex > tiedSortIndex) {
					RaceState::RacerProgressEntry progressEntry = entries[tiedSortIndex];
					entries[tiedSortIndex] = entries[maxIndex];
					entries[maxIndex] = progressEntry;
				}
			}
		}

		groupStart++;
	}

	LegoU32 rankIndex;
	for (rankIndex = 0; rankIndex < racerCount; rankIndex++) {
		if (!(entries[rankIndex].m_racer->m_flags & Racer::c_flagFinished)) {
			entries[rankIndex].m_racer->SetStandingsPosition(racerCount - rankIndex);
		}
	}

	SpatialSoundInstance* sound = m_roster.m_proximitySound;
	Racer* trackedRacer = m_roster.m_currentRacer;
	if (sound && trackedRacer) {
		GolVec3 trackedPosition;
		trackedRacer->m_visuals.m_carEntity->GetPosition(&trackedPosition);

		Racer* nearestRacer = NULL;
		LegoFloat nearestDistanceSquared = FLT_MAX;
		LegoU32 nearestIndex;
		for (nearestIndex = 0; nearestIndex < racerCount; nearestIndex++) {
			Racer* racer = &m_roster.m_racers[nearestIndex];
			if (racer != trackedRacer) {
				GolVec3 position;
				racer->m_visuals.m_carEntity->GetPosition(&position);

				LegoFloat deltaX = trackedPosition.m_x - position.m_x;
				LegoFloat deltaY = trackedPosition.m_y - position.m_y;
				LegoFloat deltaZ = trackedPosition.m_z - position.m_z;
				LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
				if (distanceSquared < nearestDistanceSquared) {
					nearestDistanceSquared = distanceSquared;
					nearestRacer = racer;
				}
			}
		}

		if (nearestDistanceSquared >= g_proximitySoundMaxDistance * g_proximitySoundMaxDistance) {
			if (sound->IsPlaying()) {
				sound->Stop();
				return;
			}
		}
		else {
			if (!sound->IsPlaying()) {
				sound->Play(TRUE);
			}

			GolVec3 position;
			nearestRacer->m_visuals.m_carEntity->GetPosition(&position);
			sound->SetPosition(position);

			GolVec3 velocity = nearestRacer->m_physics.m_velocity;
			velocity.m_x *= 2.0f;
			velocity.m_y *= 2.0f;
			velocity.m_z *= 2.0f;
			sound->SetVelocity(velocity);

			LegoFloat frequencyScale = nearestRacer->m_physics.m_speed / g_proximityPitchSpeedRange;
			frequencyScale *= 1.0f - g_proximityPitchFloor - g_proximityPitchBand;
			frequencyScale *= nearestRacer->m_enginePitchScale;
			frequencyScale += g_proximityPitchFloor;

			if (frequencyScale < 0.0f) {
				frequencyScale = 0.0f;
			}
			else if (frequencyScale > 1.0f) {
				frequencyScale = 1.0f;
			}

			if (nearestRacer->m_airborneMs > Racer::c_boostSoundElapsedThreshold) {
				frequencyScale += g_unk0x004b02e0;
			}

			sound->SetFrequencyScale(frequencyScale);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043c6a0
void RaceState::UpdateShadows(GolCamera* p_camera)
{
	LegoU32 i = 0;
	if (i < m_roster.m_racerCount) {
		do {
			m_roster.m_racers[i].m_visuals.UpdateShadow(p_camera);
			i++;
		} while (i < m_roster.m_racerCount);
	}
}

// FUNCTION: LEGORACERS 0x0043c6e0
Racer* RaceState::FindRacerInCone(
	GolVec3* p_position,
	GolVec3* p_direction,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared,
	LegoFloat p_coneCosine
)
{
	LegoS32 i;
	for (i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount);) {
		GolVec3* origin = p_position;
		Racer* racer = &m_roster.m_racers[i];
		CarVisuals* racerField = &racer->m_visuals;

		GolVec3 position;
		racerField->m_carEntity->GetPosition(&position);

		LegoFloat deltaX = position.m_x - origin->m_x;
		LegoFloat deltaY = position.m_y - origin->m_y;
		LegoFloat deltaZ = position.m_z - origin->m_z;
		LegoFloat distanceSquared = deltaX * deltaX;
		distanceSquared += deltaY * deltaY;
		distanceSquared += deltaZ * deltaZ;
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared) {
			GolVec3 delta;
			delta.m_x = deltaX;
			delta.m_y = deltaY;
			delta.m_z = deltaZ;
			GolMath::NormalizeVector3(delta, &delta);

			LegoFloat dot = p_direction->m_z;
			dot *= delta.m_z;
			LegoFloat yDot = p_direction->m_y;
			yDot *= delta.m_y;
			dot += yDot;
			dot += delta.m_x * p_direction->m_x;
			if (dot >= p_coneCosine) {
				return &m_roster.m_racers[i];
			}
		}

		i++;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0043c7f0
Racer* RaceState::FindNextRacerInCone(
	Racer* p_racer,
	GolVec3* p_position,
	GolVec3* p_direction,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared,
	LegoFloat p_coneCosine
)
{
	LegoS32 i;
	for (i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount); i++) {
		Racer* racer = &m_roster.m_racers[i];
		if (racer <= p_racer) {
			continue;
		}

		GolVec3 position;
		racer->m_visuals.m_carEntity->GetPosition(&position);

		LegoFloat deltaX = position.m_x - p_position->m_x;
		LegoFloat deltaY = position.m_y - p_position->m_y;
		LegoFloat deltaZ = position.m_z - p_position->m_z;
		LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared) {
			GolVec3 delta;
			delta.m_x = deltaX;
			delta.m_y = deltaY;
			delta.m_z = deltaZ;
			GolMath::NormalizeVector3(delta, &delta);

			if (GOLVECTOR3_DOT(*p_direction, delta) >= p_coneCosine) {
				break;
			}
		}
	}

	if (i >= static_cast<LegoS32>(m_roster.m_racerCount)) {
		return NULL;
	}

	return &m_roster.m_racers[i];
}

// FUNCTION: LEGORACERS 0x0043c910
Racer* RaceState::FindFarthestRacerInCone(
	GolVec3* p_position,
	GolVec3* p_direction,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared,
	LegoFloat p_coneCosine
)
{
	LegoFloat farthestDistanceSquared = 0.0f;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount); i++) {
		Racer* racer = &m_roster.m_racers[i];
		CarVisuals* racerField = &racer->m_visuals;

		GolVec3 position;
		racerField->m_carEntity->GetPosition(&position);

		LegoFloat distanceSquared = (position.m_x - p_position->m_x) * (position.m_x - p_position->m_x) +
									(position.m_y - p_position->m_y) * (position.m_y - p_position->m_y) +
									(position.m_z - p_position->m_z) * (position.m_z - p_position->m_z);
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared) {
			GolVec3 delta;
			delta.m_x = position.m_x - p_position->m_x;
			delta.m_y = position.m_y - p_position->m_y;
			delta.m_z = position.m_z - p_position->m_z;
			GolMath::NormalizeVector3(delta, &delta);

			if (GOLVECTOR3_DOT(*p_direction, delta) >= p_coneCosine && distanceSquared > farthestDistanceSquared) {
				resultIndex = i;
				farthestDistanceSquared = distanceSquared;
			}
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_roster.m_racers[resultIndex];
}

// FUNCTION: LEGORACERS 0x0043ca60
Racer* RaceState::FindNearestRacerInCone(
	GolVec3* p_position,
	GolVec3* p_direction,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared,
	LegoFloat p_coneCosine
)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount); i++) {
		Racer* racer = &m_roster.m_racers[i];
		CarVisuals* racerField = &racer->m_visuals;

		GolVec3 position;
		racerField->m_carEntity->GetPosition(&position);

		LegoFloat distanceSquared = (position.m_x - p_position->m_x) * (position.m_x - p_position->m_x) +
									(position.m_y - p_position->m_y) * (position.m_y - p_position->m_y) +
									(position.m_z - p_position->m_z) * (position.m_z - p_position->m_z);
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared) {
			GolVec3 delta;
			delta.m_x = position.m_x - p_position->m_x;
			delta.m_y = position.m_y - p_position->m_y;
			delta.m_z = position.m_z - p_position->m_z;
			GolMath::NormalizeVector3(delta, &delta);

			if (GOLVECTOR3_DOT(*p_direction, delta) >= p_coneCosine && distanceSquared < nearestDistanceSquared) {
				resultIndex = i;
				nearestDistanceSquared = distanceSquared;
			}
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_roster.m_racers[resultIndex];
}

// FUNCTION: LEGORACERS 0x0043cbb0
Racer* RaceState::FindNearestRacerInRange(
	GolVec3* p_position,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared
)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount); i++) {
		Racer* racer = &m_roster.m_racers[i];

		GolVec3 position;
		racer->m_visuals.m_carEntity->GetPosition(&position);

		LegoFloat deltaX = position.m_x - p_position->m_x;
		LegoFloat deltaY = position.m_y - p_position->m_y;
		LegoFloat deltaZ = position.m_z - p_position->m_z;
		LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared &&
			distanceSquared < nearestDistanceSquared) {
			resultIndex = i;
			nearestDistanceSquared = distanceSquared;
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_roster.m_racers[resultIndex];
}

// FUNCTION: LEGORACERS 0x0043ccb0
void RaceState::StartRace()
{
	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		m_roster.m_racers[i].OnRaceStart();
	}

	SpatialSoundInstance* sound = m_roster.m_soundSource->AcquireSoundById(RaceRoster::c_soundProximity);
	m_roster.m_proximitySound = sound;
	if (sound) {
		LegoFloat maxDistance = g_proximitySoundMaxDistance;
		sound->m_minDistanceSquared = g_proximitySoundMinDistance * g_proximitySoundMinDistance;
		sound->m_maxDistanceSquared = maxDistance * maxDistance;
		m_roster.m_proximitySound->SetVolume(0.8f);
	}
}

// FUNCTION: LEGORACERS 0x0043cd30
void RaceState::DrawRacerEntities(GolRenderDevice* p_renderer, Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		if (p_racer != &m_roster.m_racers[i] || p_racer->m_cameraViewIndex != 3 ||
			(p_racer->m_flags & Racer::c_flagFinished) || !(p_racer->m_flags & Racer::c_flagEngineSounds)) {
			m_roster.m_racers[i].m_visuals.m_entityGroup.Draw(*p_renderer);
		}
	}
}

// STUB: LEGORACERS 0x0043cda0
LegoU32 RaceState::GetTimeBehind(Racer* p_racer)
{
	TimeRaceManager* timeRaceManager = m_roster.m_timeRaceManager;
	LegoU32 lapsCompleted = p_racer->m_lapsCompleted;

	if (timeRaceManager) {
		LegoU32 racerLapTime = 0;
		LegoU32 recordLapTime = 0;
		LegoU32 bestLapTime = 0;

		for (LegoU32 i = 0; i < lapsCompleted; i++) {
			racerLapTime += p_racer->m_lapTimes[i];
		}

		if (timeRaceManager->HasRecordRunLapTimes()) {
			const LegoU32* lapTimes = timeRaceManager->GetRecordLapTimes();
			for (LegoU32 i = 0; i < lapsCompleted; i++) {
				recordLapTime += lapTimes[i];
			}
		}

		if (timeRaceManager->HasBestRunLapTimes()) {
			const LegoU32* lapTimes = timeRaceManager->GetBestLapTimes();
			for (LegoU32 i = 0; i < lapsCompleted; i++) {
				bestLapTime += lapTimes[i];
			}

			if (bestLapTime != 0 && (recordLapTime == 0 || recordLapTime > bestLapTime)) {
				recordLapTime = bestLapTime;
			}
		}

		if (recordLapTime != 0 && recordLapTime < racerLapTime) {
			return racerLapTime - recordLapTime;
		}

		return 0;
	}

	if (p_racer->m_lapTimes[5] == 1) {
		return 0;
	}

	LegoS32 result = 0;
	LegoU32 lapCount = m_setup.m_lapCount;
	if (lapsCompleted > lapCount) {
		lapsCompleted = lapCount;
	}

	for (LegoU32 racerIndex = 0; racerIndex < m_roster.m_racerCount; racerIndex++) {
		Racer* otherRacer = &m_roster.m_racers[racerIndex];
		if (otherRacer == p_racer) {
			continue;
		}

		LegoU32 otherLapsCompleted = otherRacer->m_lapsCompleted;
		if (otherLapsCompleted > lapCount) {
			otherLapsCompleted = lapCount;
		}

		if (lapsCompleted <= otherLapsCompleted) {
			LegoS32 delta = 0;
			for (LegoU32 completedLapIndex = 0; completedLapIndex < lapsCompleted; completedLapIndex++) {
				delta += static_cast<LegoS32>(p_racer->m_lapTimes[completedLapIndex]) -
						 static_cast<LegoS32>(otherRacer->m_lapTimes[completedLapIndex]);
			}

			for (LegoU32 remainingLapIndex = lapsCompleted; remainingLapIndex < otherLapsCompleted;
				 remainingLapIndex++) {
				delta += static_cast<LegoS32>(otherRacer->m_lapTimes[remainingLapIndex]);
			}

			if (delta > result) {
				result = delta;
			}
		}
	}

	return result;
}

// STUB: LEGORACERS 0x0043cf30
void RaceState::ComputeStandingsDeltas(Racer* p_racer, Racer::StandingsDeltaEntry* p_entries)
{
	LegoU32 lapCount = m_setup.m_lapCount;
	LegoS32 racerTime = 0;

	if (lapCount > p_racer->m_lapsCompleted) {
		if (m_roster.m_racerCount > 0) {
			LegoU32 racerIndex = 0;
			Racer::StandingsDeltaEntry* entry = p_entries;

			do {
				entry->m_racer = NULL;
				entry->m_delta = 0;
				entry->m_isValid = FALSE;
				racerIndex++;
				entry++;
			} while (racerIndex < m_roster.m_racerCount);
		}

		return;
	}

	if (lapCount > 0) {
		LegoU32 remaining = lapCount;
		LegoU32* lapTime = p_racer->m_lapTimes;

		do {
			racerTime += *lapTime++;
		} while (--remaining);
	}

	if (m_roster.m_racerCount > 0) {
		LegoU32 racerIndex = 0;
		Racer::StandingsDeltaEntry* entry = p_entries;

		do {
			entry->m_racer = &m_roster.m_racers[racerIndex];
			entry->m_isValid = TRUE;

			Racer* racers = m_roster.m_racers;
			Racer* otherRacer = &racers[racerIndex];
			if (otherRacer == p_racer) {
				entry->m_delta = 0;
			}
			else if (otherRacer->m_lapsCompleted >= m_setup.m_lapCount) {
				LegoS32 otherTime = 0;
				LegoU32 remaining = m_setup.m_lapCount;

				if (remaining) {
					LegoU32* lapTime = otherRacer->m_lapTimes;

					do {
						otherTime += *lapTime++;
					} while (--remaining);
				}

				entry->m_delta = otherTime - racerTime;
			}
			else {
				entry->m_delta = otherRacer->m_lapTimes[5] + 2147483641;
			}

			racerIndex++;
			entry++;
		} while (racerIndex < m_roster.m_racerCount);
	}

	if (m_roster.m_racerCount < 6) {
		Racer::StandingsDeltaEntry* entry = &p_entries[m_roster.m_racerCount];
		LegoU32 remaining = 6 - m_roster.m_racerCount;

		do {
			entry->m_isValid = FALSE;
			entry++;
		} while (--remaining);
	}
}

// FUNCTION: LEGORACERS 0x0043d070
RaceRouteRecord* RaceState::FindNearestRouteRecord(Racer* p_racer)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	RaceRouteRecord* result = NULL;

	GolVec3 racerPosition;
	p_racer->m_visuals.m_carEntity->GetPosition(&racerPosition);

	RaceRouteRecord* entry = m_roster.m_routeRecords;
	for (LegoS32 i = 6; i; i--) {
		if (entry->m_pathPoints) {
			GolVec3 position = entry->m_loopPosition;
			LegoFloat deltaX = position.m_x - racerPosition.m_x;
			LegoFloat deltaY = position.m_y - racerPosition.m_y;
			LegoFloat deltaZ = position.m_z - racerPosition.m_z;
			LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;

			if (distanceSquared < nearestDistanceSquared) {
				nearestDistanceSquared = distanceSquared;
				result = entry;
			}
		}

		entry++;
	}

	return result;
}
// FUNCTION: LEGORACERS 0x0043d120
void RaceState::StopProximitySound()
{
	SpatialSoundInstance* resource = m_roster.m_proximitySound;
	if (resource) {
		m_roster.m_soundSource->ReleaseSound(resource);
		m_roster.m_proximitySound = NULL;
	}
}

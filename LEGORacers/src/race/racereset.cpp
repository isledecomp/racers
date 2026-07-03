#include "race/racesession.h"
#include "race/timeracemanager.h"

DECOMP_SIZE_ASSERT(RaceReset, 0x2c)

// FUNCTION: LEGORACERS 0x0043a640
RaceReset::RaceReset()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a650
RaceReset::~RaceReset()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a660
void RaceReset::Reset()
{
	m_context = NULL;
	m_raceState = NULL;
	m_powerupManager = NULL;
	m_hazardManager = NULL;
	m_particleAnimation = NULL;
	m_sharedParticleAnimation = NULL;
	m_timeRaceManager = NULL;
	m_racerTriggers = NULL;
	m_triggers = NULL;
	m_collisionWorlds = NULL;
	m_eventTable = NULL;
}

// FUNCTION: LEGORACERS 0x0043a690
void RaceReset::Initialize(const Params* p_source)
{
	m_context = p_source->m_context;
	m_raceState = p_source->m_raceState;
	m_powerupManager = p_source->m_powerupManager;
	m_hazardManager = p_source->m_hazardManager;
	m_particleAnimation = p_source->m_particleAnimation;
	m_sharedParticleAnimation = p_source->m_sharedParticleAnimation;
	m_timeRaceManager = p_source->m_timeRaceManager;
	m_racerTriggers = p_source->m_racerTriggers;
	m_triggers = p_source->m_triggers;
	m_collisionWorlds = p_source->m_collisionWorlds;
	m_eventTable = p_source->m_eventTable;
}

// FUNCTION: LEGORACERS 0x0043a6e0
void RaceReset::FinishRace()
{
	m_raceState->RecordBestTimes(m_context);
	m_eventTable->ForceAllEvents();

	for (LegoU32 racerIndex = 0; racerIndex < m_raceState->GetRacerCount(); racerIndex++) {
		m_eventTable->EndAllForRacer(&m_raceState->GetRacers()[racerIndex]);
	}

	m_triggers->Reset();
	m_racerTriggers->Reset();
	m_collisionWorlds->Reset();
	m_hazardManager->ResetAll();
	m_powerupManager->ResetEffects();

	if (m_timeRaceManager) {
		m_timeRaceManager->ResetRun();
	}

	ResetRacers();
	m_particleAnimation->StopAllParticles();
	m_sharedParticleAnimation->StopAllParticles();
}

// FUNCTION: LEGORACERS 0x0043a780
void RaceReset::ResetRacers()
{
	m_raceState->StopProximitySound();

	for (LegoU32 racerIndex = 0; racerIndex < m_raceState->GetRacerCount(); racerIndex++) {
		Racer* racer = &m_raceState->GetRacers()[racerIndex];

		for (LegoU32 lapIndex = 0; lapIndex < racer->m_lapCount; lapIndex++) {
			racer->m_lapTimes[lapIndex] = 0;
		}

		racer->CollectColorBrick(0);
		racer->ReturnAllWhiteBricks();
		racer->EndShield();
		racer->Resume();
		racer->LeaveGhostMode();
		racer->ClearActiveAction();
		racer->EndSpinOut();
		racer->RemoveCurse();
		racer->EndMagnetHold();
		racer->EndDrift();
		racer->SetStandingsPosition(racerIndex + 1);

		if (racer->m_flags & Racer::c_flagWarping) {
			racer->m_flags &= ~Racer::c_flagWarping;
		}

		CarVisuals* field = &racer->m_visuals;
		field->StopSlideSkid();
		field->ShowModels();
		field->StopSkidEffects();
		field->UseNormalSkidMaterial();
		field->RefreshCarMaterial();
		field->m_flags |= CarVisuals::c_flagShadowEnabled;
		field->EndFlash();
		field->ClearColorTransform();
		field->SetScale(1.0f);

		field->m_carEntity->SetMsPerFrame(0.0f);
		if (field->m_secondaryEntity) {
			field->m_secondaryEntity->SetMsPerFrame(0.0f);
		}

		field->ResetDriverAnimation();

		for (LegoU32 particleIndex = 0; particleIndex < 4; particleIndex++) {
			field->ClearWheelParticle(particleIndex);
		}

		LegoU32 startIndex = m_raceState->GetPlacementSlot(racerIndex);
		GolVec3 position = m_raceState->GetStartPosition(startIndex);
		GolVec3 up;
		GolVec3 direction = m_raceState->GetStartDirection(startIndex);
		up = m_raceState->GetStartUp(startIndex);
		racer->m_visuals.m_carEntity->SetPosition(position);
		racer->m_visuals.m_carEntity->SetDirectionUp(direction, up);
		field->SnapVisuals();
		racer->InvalidateCamera();

		if (!m_context->m_playerSetupSlots[racerIndex].m_slotState) {
			racer->m_controlMode = Racer::c_controlNone;
			racer->m_routeRecord = NULL;
		}

		racer->InitializePhysics(NULL, NULL);
		racer->m_driveController.m_previewCursor = m_raceState->GetSharedRouteCursor();
		racer->ResetRaceProgress();
		racer->StopEngineSounds();
	}
}

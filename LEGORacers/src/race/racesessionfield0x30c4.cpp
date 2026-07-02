#include "race/racesession.h"
#include "race/timeracemanager.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x30c4, 0x2c)

// FUNCTION: LEGORACERS 0x0043a640
RaceSession::Field0x30c4::Field0x30c4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a650
RaceSession::Field0x30c4::~Field0x30c4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a660
void RaceSession::Field0x30c4::Reset()
{
	m_context = NULL;
	m_raceState = NULL;
	m_unk0x08 = NULL;
	m_unk0x0c = NULL;
	m_unk0x10 = NULL;
	m_unk0x14 = NULL;
	m_timeRaceManager = NULL;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = NULL;
}

// FUNCTION: LEGORACERS 0x0043a690
void RaceSession::Field0x30c4::FUN_0043a690(const Params* p_source)
{
	m_context = p_source->m_context;
	m_raceState = p_source->m_raceState;
	m_unk0x08 = p_source->m_unk0x08;
	m_unk0x0c = p_source->m_unk0x0c;
	m_unk0x10 = p_source->m_unk0x10;
	m_unk0x14 = p_source->m_unk0x14;
	m_timeRaceManager = p_source->m_timeRaceManager;
	m_unk0x1c = p_source->m_unk0x1c;
	m_unk0x20 = p_source->m_unk0x20;
	m_unk0x24 = p_source->m_unk0x24;
	m_unk0x28 = p_source->m_unk0x28;
}

// FUNCTION: LEGORACERS 0x0043a6e0
void RaceSession::Field0x30c4::FUN_0043a6e0()
{
	m_raceState->RecordBestTimes(m_context);
	m_unk0x28->FUN_00462c60();

	for (LegoU32 racerIndex = 0; racerIndex < m_raceState->GetRacerCount(); racerIndex++) {
		m_unk0x28->FUN_00462da0(&m_raceState->GetRacers()[racerIndex]);
	}

	m_unk0x20->VTable0x0c();
	m_unk0x1c->VTable0x0c();
	m_unk0x24->FUN_0045e5b0();
	m_unk0x0c->FUN_0048ae60();
	m_unk0x08->ResetEffects();

	if (m_timeRaceManager) {
		m_timeRaceManager->FUN_004234f0();
	}

	FUN_0043a780();
	m_unk0x10->FUN_00489f60();
	m_unk0x14->FUN_00489f60();
}

// FUNCTION: LEGORACERS 0x0043a780
void RaceSession::Field0x30c4::FUN_0043a780()
{
	m_raceState->StopProximitySound();

	for (LegoU32 racerIndex = 0; racerIndex < m_raceState->GetRacerCount(); racerIndex++) {
		RaceState::Racer* racer = &m_raceState->GetRacers()[racerIndex];

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

		if (racer->m_flags & RaceState::Racer::c_flagBit21) {
			racer->m_flags &= ~RaceState::Racer::c_flagBit21;
		}

		RaceState::Racer::CarVisuals* field = &racer->m_visuals;
		field->StopSlideSkid();
		field->ShowModels();
		field->StopSkidEffects();
		field->UseNormalSkidMaterial();
		field->RefreshCarMaterial();
		field->m_flags |= RaceState::Racer::CarVisuals::c_flagShadowEnabled;
		field->EndFlash();
		field->ClearColorTransform();
		field->SetScale(1.0f);

		field->m_carEntity->SetUnk0xb8(0.0f);
		if (field->m_unk0x040) {
			field->m_unk0x040->SetUnk0xb8(0.0f);
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
		racer->m_visuals.m_carEntity->VTable0x08(position);
		racer->m_visuals.m_carEntity->VTable0x40(direction, up);
		field->SnapVisuals();
		racer->InvalidateCamera();

		if (!m_context->m_playerSetupSlots[racerIndex].m_unk0x10) {
			racer->m_controlMode = 0;
			racer->m_routeRecord = NULL;
		}

		racer->InitializePhysics(NULL, NULL);
		racer->m_driveController.m_previewCursor = m_raceState->GetSharedRouteCursor();
		racer->ResetRaceProgress();
		racer->StopEngineSounds();
	}
}

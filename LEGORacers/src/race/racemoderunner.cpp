#include "race/racemoderunner.h"

#include "app/win32golapp.h"
#include "golhashtable.h"
#include "menu/menuscreenid.h"

#include <golerror.h>
#include <golstream.h>
#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(RaceModeRunner, 0x37b8)

// GLOBAL: LEGORACERS 0x004c4914
RaceModeRunner* g_raceModeRunner = NULL;

// GLOBAL: LEGORACERS 0x004c491c
LegoChar g_raceNameBuffer[9];

// FUNCTION: LEGORACERS 0x0042b130
void RaceModeRunner::Run(LegoRacers::Context* p_context)
{
	g_raceModeRunner = new RaceModeRunner();
	if (!g_raceModeRunner) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_raceModeRunner->Initialize(p_context);
	g_raceModeRunner->Run();
	g_raceModeRunner->Shutdown();

	if (g_raceModeRunner) {
		delete g_raceModeRunner;
	}
}

// FUNCTION: LEGORACERS 0x0042c1b0
RaceModeRunner::RaceModeRunner()
{
	m_context = NULL;
}

// FUNCTION: LEGORACERS 0x0042c210
RaceModeRunner::~RaceModeRunner()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0042c280
LegoS32 RaceModeRunner::Initialize(LegoRacers::Context* p_context)
{
	m_context = p_context;
	m_context->m_unk0x1e &= ~LegoRacers::Context::c_flagAbortRace;

	if (p_context->m_raceMode == LegoRacers::Context::c_raceModeTimeRace) {
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("GAMEDATA\\COMMON");
		}
		m_timeRaceManager.Initialize(
			p_context->m_golApp->GetRenderer(),
			p_context->m_golApp->GetGolExport(),
			p_context->m_unk0x18,
			p_context->m_raceSlots[0].m_mirror
		);
	}

	if (p_context->m_unk0x1e & LegoRacers::Context::c_flagReturnToGarage) {
		p_context->m_nextMenuId = c_menuGarage;
	}
	else {
		p_context->m_nextMenuId = c_menuMainMenu;
	}

	p_context->m_currentRaceIndex = 0;
	p_context->m_golApp->ClearFileSourceDirectoryCaches();

	if (!p_context->m_raceMode) {
		return m_circuitRunner.Initialize(m_context, &m_session);
	}

	return InitializeRaceScene();
}

// FUNCTION: LEGORACERS 0x0042c330
void RaceModeRunner::Run()
{
	if (!m_context->m_raceMode) {
		m_circuitRunner.Run();
		m_context->m_unk0x1e &= ~LegoRacers::Context::c_flagBit7;
		return;
	}

	m_session.Run();
	m_timeRaceManager.Shutdown();
	m_context->m_unk0x1e &= ~LegoRacers::Context::c_flagBit7;
}

// FUNCTION: LEGORACERS 0x0042c380
void RaceModeRunner::Shutdown()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(NULL);
	}

	m_timeRaceManager.Shutdown();
	m_circuitRunner.Shutdown();
	m_session.Shutdown();
	ReleaseContextAssets();
	m_context = NULL;
}

// FUNCTION: LEGORACERS 0x0042c3d0
void RaceModeRunner::ReleaseContextAssets()
{
	if (!m_context) {
		return;
	}

	GolExport* golExport = m_context->m_golApp->GetGolExport();

	for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
		LegoRacers::Context::PlayerSetupSlot& slot = m_context->m_playerSetupSlots[i];

		if (slot.m_chassisName[0]) {
			if (slot.m_model) {
				golExport->VTable0x48(slot.m_model);
				slot.m_model = NULL;
			}
			if (slot.m_materials) {
				golExport->DestroyMaterialList(slot.m_materials);
				slot.m_materials = NULL;
			}
			if (slot.m_textures) {
				golExport->DestroyTextureList(slot.m_textures);
				slot.m_textures = NULL;
			}
			if (slot.m_altModel) {
				golExport->VTable0x48(slot.m_altModel);
				slot.m_altModel = NULL;
			}
			if (slot.m_altMaterials) {
				golExport->DestroyMaterialList(slot.m_altMaterials);
				slot.m_altMaterials = NULL;
			}
			if (slot.m_altTextures) {
				golExport->DestroyTextureList(slot.m_altTextures);
				slot.m_altTextures = NULL;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0042c4e0
LegoS32 RaceModeRunner::InitializeRaceScene()
{
	sprintf(m_context->m_commonDataDirectory, "GAMEDATA\\COMMON");
	strcpy(m_context->m_gameDataDirectory, "GAMEDATA\\");
	memcpy(g_raceNameBuffer, m_context->m_raceSlots[0].m_folderName, sizeof(m_context->m_raceSlots[0].m_folderName));
	g_raceNameBuffer[sizeof(m_context->m_raceSlots[0].m_folderName)] = '\0';
	strcat(m_context->m_gameDataDirectory, g_raceNameBuffer);

	LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(gameDataDirectory);
	}

	if (m_timeRaceManager.GetScratchLapTimes()) {
		return m_session
			.Initialize(m_context, g_raceNameBuffer, m_context->m_raceSlots[0].m_mirror, &m_timeRaceManager);
	}

	return m_session.Initialize(m_context, g_raceNameBuffer, m_context->m_raceSlots[0].m_mirror, NULL);
}

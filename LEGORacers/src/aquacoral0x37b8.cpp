#include "aquacoral0x37b8.h"

#include "golhashtable.h"
#include "win32golapp.h"

#include <golerror.h>
#include <golstream.h>
#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(AquaCoral0x37b8, 0x37b8)

// GLOBAL: LEGORACERS 0x004c4914
AquaCoral0x37b8* g_unk0x4c4914 = NULL;

// GLOBAL: LEGORACERS 0x004c491c
LegoChar g_raceNameBuffer[9];

// FUNCTION: LEGORACERS 0x0042b130
void AquaCoral0x37b8::FUN_0042b130(LegoRacers::Context* p_context)
{
	g_unk0x4c4914 = new AquaCoral0x37b8();
	if (!g_unk0x4c4914) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_unk0x4c4914->Initialize(p_context);
	g_unk0x4c4914->Run();
	g_unk0x4c4914->Shutdown();

	if (g_unk0x4c4914) {
		delete g_unk0x4c4914;
	}
}

// FUNCTION: LEGORACERS 0x0042c1b0
AquaCoral0x37b8::AquaCoral0x37b8()
{
	m_context = NULL;
}

// FUNCTION: LEGORACERS 0x0042c210
AquaCoral0x37b8::~AquaCoral0x37b8()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0042c280
LegoS32 AquaCoral0x37b8::Initialize(LegoRacers::Context* p_context)
{
	m_context = p_context;
	m_context->m_unk0x1e &= ~LegoRacers::Context::c_flagBit3;

	if (p_context->m_unk0x24 == 2) {
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("GAMEDATA\\COMMON");
		}
		m_unk0x3400.FUN_00422420(
			p_context->m_golApp->GetRenderer(),
			p_context->m_golApp->GetGolExport(),
			p_context->m_unk0x18,
			p_context->m_raceSlots[0].m_unk0x04
		);
	}

	if (p_context->m_unk0x1e & LegoRacers::Context::c_flagBit1) {
		p_context->m_unk0x1c = 3;
	}
	else {
		p_context->m_unk0x1c = 2;
	}

	p_context->m_unk0xd8 = 0;
	p_context->m_golApp->ClearFileSourceDirectoryCaches();

	if (!p_context->m_unk0x24) {
		return m_unk0x04.Initialize(m_context, &m_unk0x98);
	}

	return InitializeRaceScene();
}

// FUNCTION: LEGORACERS 0x0042c330
void AquaCoral0x37b8::Run()
{
	if (!m_context->m_unk0x24) {
		m_unk0x04.Run();
		m_context->m_unk0x1e &= ~LegoRacers::Context::c_flagBit7;
		return;
	}

	m_unk0x98.Run();
	m_unk0x3400.FUN_00422670();
	m_context->m_unk0x1e &= ~LegoRacers::Context::c_flagBit7;
}

// FUNCTION: LEGORACERS 0x0042c380
void AquaCoral0x37b8::Shutdown()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(NULL);
	}

	m_unk0x3400.FUN_00422670();
	m_unk0x04.Shutdown();
	m_unk0x98.Shutdown();
	ReleaseContextAssets();
	m_context = NULL;
}

// FUNCTION: LEGORACERS 0x0042c3d0
void AquaCoral0x37b8::ReleaseContextAssets()
{
	if (!m_context) {
		return;
	}

	GolExport* golExport = m_context->m_golApp->GetGolExport();

	for (LegoU32 i = 0; i < m_context->m_unk0x32c; i++) {
		ScarletNova0x5c& slot = m_context->m_unk0x108[i];

		if (slot.m_flag) {
			if (slot.m_unk0x20) {
				golExport->VTable0x48(slot.m_unk0x20);
				slot.m_unk0x20 = NULL;
			}
			if (slot.m_unk0x24) {
				golExport->DestroyMaterialList(slot.m_unk0x24);
				slot.m_unk0x24 = NULL;
			}
			if (slot.m_unk0x28) {
				golExport->DestroyTextureList(slot.m_unk0x28);
				slot.m_unk0x28 = NULL;
			}
			if (slot.m_unk0x44) {
				golExport->VTable0x48(slot.m_unk0x44);
				slot.m_unk0x44 = NULL;
			}
			if (slot.m_unk0x48) {
				golExport->DestroyMaterialList(slot.m_unk0x48);
				slot.m_unk0x48 = NULL;
			}
			if (slot.m_unk0x4c) {
				golExport->DestroyTextureList(slot.m_unk0x4c);
				slot.m_unk0x4c = NULL;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0042c4e0
LegoS32 AquaCoral0x37b8::InitializeRaceScene()
{
	sprintf(m_context->m_commonDataDirectory, "GAMEDATA\\COMMON");
	strcpy(m_context->m_gameDataDirectory, "GAMEDATA\\");
	memcpy(g_raceNameBuffer, m_context->m_raceSlots[0].m_raceName, sizeof(m_context->m_raceSlots[0].m_raceName));
	g_raceNameBuffer[sizeof(m_context->m_raceSlots[0].m_raceName)] = '\0';
	strcat(m_context->m_gameDataDirectory, g_raceNameBuffer);

	LegoChar* gameDataDirectory = m_context->m_gameDataDirectory;
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(gameDataDirectory);
	}

	if (m_unk0x3400.GetUnk0x14()) {
		return m_unk0x98.Initialize(m_context, g_raceNameBuffer, m_context->m_raceSlots[0].m_unk0x04, &m_unk0x3400);
	}

	return m_unk0x98.Initialize(m_context, g_raceNameBuffer, m_context->m_raceSlots[0].m_unk0x04, NULL);
}

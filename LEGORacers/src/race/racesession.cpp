#include "race/racesession.h"

#include "app/golapp.h"
#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "audio/soundmanager.h"
#include "audio/soundnode.h"
#include "camera/golcamera.h"
#include "camera/goltransform.h"
#include "core/gol.h"
#include "golbmpwriterfile.h"
#include "golerror.h"
#include "golfontbase.h"
#include "golhashtable.h"
#include "golstream.h"
#include "race/circuitstandings.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/slatepeak0x58.h"
#include "world/golworlddatabase.h"

#include <memory.h>
#include <mmsystem.h>
#include <stdio.h>

DECOMP_SIZE_ASSERT(RaceSession, 0x3368)

// GLOBAL: LEGORACERS 0x004b07ec
LegoFloat g_unk0x004b07ec = 1.2f;

// GLOBAL: LEGORACERS 0x004b08bc
extern const LegoFloat g_unk0x004b08bc = 25.0f;

// GLOBAL: LEGORACERS 0x004bee74
const LegoU16 g_unk0x004bee74[16] =
	{0x0e, 0x0f, 0x11, 0x14, 0x0e, 0x10, 0x11, 0x00, 0x12, 0x13, 0x15, 0x16, 0x17, 0x18, 0x2c, 0x00};

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

// FUNCTION: LEGORACERS 0x004316e0
RaceSession::RaceSession()
{
	FUN_00431bd0();
}

// FUNCTION: LEGORACERS 0x00431990
RaceSession::~RaceSession()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00431bd0
void RaceSession::FUN_00431bd0()
{
	m_context = NULL;
	m_golApp = NULL;
	m_soundManager = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_unk0x21c = NULL;
	m_standings = NULL;
	m_unk0x1c = 0;
	m_unk0x5c = 0;
	m_unk0x69 = 0;
	m_unk0x76 = 0;
	m_unk0x83 = 0;
	m_unk0x90 = 0;
	m_unk0x9d = 0;
	m_unk0xaa = 0;
	m_unk0xb7 = 0;
	m_unk0xc4 = 0;
	m_unk0xde = 0;
	m_unk0xd1 = 0;
	m_unk0xeb = 0;
	m_unk0xf8 = 0;
	m_unk0x105 = 0;
	m_unk0x112 = 0;
	m_unk0x11f = 0;
	m_unk0x12c = 0;
	m_unk0x146 = 0;
	m_unk0x153 = 0;
	m_unk0x160 = 0;
	m_unk0x16d = 0;
	m_unk0x17a = 0;
	m_unk0x187 = 0;
	m_unk0x194 = 0;
	m_unk0x1a1 = 0;
	m_unk0x1ae = 0;
	m_unk0x1bb = 0;
	m_unk0x1c8 = 0;
	m_unk0x1d5 = 0;
	m_unk0x1ef = 0;
	m_unk0x1e2 = 0;
	m_unk0x3ac = 0;
	m_unk0x1f8.m_x = 0.0f;
	m_unk0x1f8.m_y = 0.0f;
	m_unk0x1f8.m_z = 0.0f;
	m_unk0x204.m_x = 1.0f;
	m_unk0x204.m_y = 0.0f;
	m_unk0x204.m_z = 0.0f;
	m_unk0x210.m_x = 0.0f;
	m_unk0x210.m_y = 0.0f;
	m_unk0x210.m_z = -1.0f;
	m_unk0x2abc = 1023.0f;
	m_unk0x2ac0 = -1023.0f;
	m_unk0x2ac4 = 1023.0f;
	m_unk0x2ac8 = -1023.0f;
	m_unk0x390 = NULL;
	m_unk0x394 = 0;
	m_unk0x39c = NULL;
	m_unk0x398 = NULL;
	m_unk0x3a0 = NULL;
	m_unk0x3b0 = 0;
	m_unk0x3b4 = 0;
	m_unk0x3b8 = 0;
	m_unk0x2d74 = 0;
	m_unk0x2d78 = 0;
	m_unk0x2d7c = 0;
	m_unk0x2f8c = 0;
	m_unk0x3314 = NULL;
	m_unk0x3320 = NULL;
	m_unk0x3324 = g_unk0x004b07ec;
	m_unk0x3a4 = NULL;
	m_unk0x3a8 = 0;
	m_unk0x3330 = 0;
	m_unk0x3358 = 0;

	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x2acc); i++) {
		m_unk0x3318[i] = NULL;
		m_unk0x2acc[i] = NULL;
		m_raceState.m_unk0x318[i] = NULL;
	}

	m_elapsedMs = 0;
	m_state = 0;
	memset(m_unk0x2d8c, 0, sizeof(m_unk0x2d8c));
	m_unk0x334c = 0;
	m_running = 0;
	m_unk0x3338 = 0;
	m_unk0x3350 = 0;
	m_unk0x3354 = 0;
	m_unk0x30c0 = 0;
	m_unk0x335c = 0;
	m_unk0x3360 = 0;
	m_unk0x3348 = 0;
	m_timeRaceManager = NULL;
}

// STUB: LEGORACERS 0x00431e00
LegoS32 RaceSession::Initialize(LegoRacers::Context* p_context, const LegoChar*, undefined4, TimeRaceManager*)
{
#if 0
	if (p_context->m_unk0x18) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	} else {
		parser = new RabTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
#endif
	// TODO
	STUB(0x431e00);
	return 0;
}

// FUNCTION: LEGORACERS 0x00432520
void RaceSession::VTable0x00()
{
	m_running = 0;
	m_context->m_running = FALSE;
}

// FUNCTION: LEGORACERS 0x00432540
void RaceSession::Run()
{
	m_running = 1;
	m_frameCount = 0;
	m_unk0x3340 = 0;

	LegoS32 previousTime = timeGetTime();

	m_fps = 0.0f;
	m_elapsedMs = 0;

	LegoU32 frameSampleCount = 0;
	LegoU32 frameSampleElapsedMs = 0;

	m_state = 1;
	m_renderer->VTable0x44();

	while (m_running) {
		if (!m_golApp->Tick(this)) {
			break;
		}

		if (m_golApp->GetFlags() & GolApp::c_flagBit14) {
			m_unk0x30c0 = 1;
			FUN_00436010();
			m_golApp->ClearFlags(GolApp::c_flagBit14);
		}

		while (m_inputEvents.GetSize()) {
			InputEventQueue::Event* event = m_inputEvents.Dequeue();
			if (event->m_isPressed) {
				VTable0x44(event->m_keyCode);
			}
			else {
				VTable0x48(event->m_keyCode);
			}
		}

		if (!m_golApp->IsDisabled()) {
			if (!m_unk0x30c0) {
				m_elapsedMs += m_golApp->GetFrameDeltaMs();
			}

			switch (m_state) {
			case 1:
				FUN_004349a0();
				break;
			case 2:
				FUN_00434b00();
				break;
			case 3:
				FUN_00434c80();
				break;
			case 4:
				FUN_00434eb0();
				break;
			case 5:
				FUN_00435180();
				break;
			}

			VTable0x30();
			FUN_004354d0();
			m_golApp->PresentFrame();

			if (m_frameCount) {
				LegoS32 currentTime = timeGetTime();
				m_unk0x3340 += currentTime - previousTime;
				frameSampleElapsedMs += currentTime - previousTime;
				frameSampleCount++;
				previousTime = currentTime;

				if (frameSampleCount >= 64) {
					frameSampleElapsedMs >>= 6;
					frameSampleCount = 0;
					m_fps = 1.0f / (static_cast<LegoFloat>((LegoS32) frameSampleElapsedMs) * 0.001f);
					frameSampleElapsedMs = 0;
				}
			}

			m_frameCount++;
		}
	}

	m_renderer->VTable0xf4();
	m_renderer->VTable0x38();
	m_renderer->VTable0x48();
	m_raceState.RecordBestTimes(m_context);

	RaceState::Racer* field = m_raceState.GetUnk0x318();
	if (field) {
		m_context->m_unk0x398 = field->m_unk0xdb8;
	}

	if (m_context->m_running && m_timeRaceManager) {
		m_context->m_unk0x1e |= LegoRacers::Context::c_flagBestTimesPending;

		if (m_timeRaceManager->HasBeatenRecord()) {
			m_context->m_unk0x1e |= LegoRacers::Context::c_flagRecordBeaten;
		}
	}
}

// FUNCTION: LEGORACERS 0x00432790
void RaceSession::Shutdown()
{
	FUN_00433460();
	FUN_004348a0();
	FUN_00434000();
	FUN_004330e0();
	FUN_00432df0();
	FUN_00432d70();
	m_unk0x280c.FUN_0042f430();
	FUN_00434300();
	FUN_00432b30();
	FUN_004328d0();
	FUN_00431bd0();
}

// FUNCTION: LEGORACERS 0x004328d0
void RaceSession::FUN_004328d0()
{
	m_context = NULL;
	m_golApp = NULL;
	m_soundManager = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_unk0x21c = NULL;
}

// FUNCTION: LEGORACERS 0x00432b30
void RaceSession::FUN_00432b30()
{
	if (m_soundManager) {
		for (LegoS32 i = 0; i < sizeOfArray(m_unk0x3318); i++) {
			if (m_unk0x3318[i]) {
				m_soundManager->DestroySoundNode(m_unk0x3318[i]);
				m_unk0x3318[i] = NULL;
			}
		}

		m_unk0x3300.FUN_00443a80();

		if (m_unk0x3320) {
			m_unk0x3320->Stop();
			m_unk0x3314->DestroyMusicInstance(m_unk0x3320);
			m_unk0x3320 = NULL;
		}

		MusicGroup* musicGroup = m_unk0x3314;
		if (musicGroup) {
			m_soundManager->DestroyMusicGroup(musicGroup);
			m_unk0x3314 = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00432d70
void RaceSession::FUN_00432d70()
{
	if (m_golExport && m_unk0x2d74) {
		m_golExport->DestroyFontTable(m_unk0x2d74);
		m_unk0x2d74 = NULL;
	}

	m_unk0x2d80.Reset();

	GolStringTable* stringTable = &m_unk0x30f0;
	stringTable->ReleaseOwnedBuffers();
}

// FUNCTION: LEGORACERS 0x00432df0
void RaceSession::FUN_00432df0()
{
	if (m_golExport) {
		if (m_unk0x2f8c) {
			m_golExport->VTable0x68(m_unk0x2f8c);
			m_unk0x2f8c = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x004330e0
void RaceSession::FUN_004330e0()
{
	if (m_golExport) {
		if (m_unk0x3a0) {
			m_golExport->VTable0x3c(m_unk0x3a0);
		}
		if (m_unk0x3a4) {
			m_golExport->VTable0x3c(m_unk0x3a4);
		}
		if (m_unk0x398) {
			m_golExport->VTable0x3c(m_unk0x398);
		}
		if (m_unk0x390) {
			m_golExport->VTable0x3c(m_unk0x390);
		}
		if (m_unk0x39c) {
			m_golExport->VTable0x3c(m_unk0x39c);
		}
	}

	GolNameTable* field0x27e0 = &m_unk0x27e0;
	field0x27e0->Clear();

	m_unk0x39c = NULL;
	m_unk0x398 = NULL;
	m_unk0x3a0 = NULL;
	m_unk0x390 = NULL;
	m_unk0x3b0 = 0;
	m_unk0x3b4 = 0;
	m_unk0x3b8 = 0;
	m_unk0x3ac = 0;
}

// FUNCTION: LEGORACERS 0x00433460
void RaceSession::FUN_00433460()
{
	Field0x3104* current = m_unk0x3104;
	LegoS32 remaining = sizeOfArray(m_unk0x3104);
	do {
		current->FUN_004a50a0();
		current++;
	} while (--remaining);
}

// FUNCTION: LEGORACERS 0x00434000
void RaceSession::FUN_00434000()
{
	if (m_context) {
		LegoU32 playerCount = m_context->m_playerCount;
		LegoU32 i = 0;

		if (playerCount > 0) {
			RaceState::Racer** racer = m_raceState.m_unk0x318;
			do {
				if (*racer) {
					(*racer)->m_unk0x018.FUN_00440130();
					(*racer)->m_unk0x018.FUN_004400e0();
				}

				i++;
				racer++;
			} while (i < m_context->m_playerCount);
		}
	}

	m_unk0x3058.Destroy();
	m_unk0x6dc.FUN_00459e20();

	if (m_golExport) {
		if (m_unk0x3a8) {
			m_golExport->VTable0x3c(m_unk0x3a8);
			m_unk0x3a8 = NULL;
		}
	}

	m_unk0x213c.Destroy();
	m_unk0x2128.Destroy();
	m_unk0x2080.Destroy();
	m_unk0x32c4.Destroy();
	m_unk0x2148.Destroy();
	m_unk0x2098.Destroy();
	m_unk0x2804.Reset();
	m_unk0x2f90.Clear();
	m_raceState.Destroy();
	m_unk0x27f4.Reset();
	m_unk0x27d4.Destroy();
	m_unk0x27c8.Destroy();
	m_unk0x27fc.Reset();
	m_unk0x248c.Clear();
	m_unk0x2150.Clear();

	Field0x2ad4* field0x2ad4 = m_unk0x2ad4;
	RaceState::Racer** racer = m_raceState.m_unk0x318;
	LegoS32 remaining = sizeOfArray(m_unk0x2ad4);
	do {
		*racer = NULL;
		field0x2ad4->Reset();
		racer++;
		field0x2ad4++;
	} while (--remaining);
}

// STUB: LEGORACERS 0x00434170
void RaceSession::FUN_00434170()
{
	const SlatePeak0x58* renderTargetInfo = m_renderer->GetRenderTargetInfo();
	LegoU32 width = renderTargetInfo->GetWidth();
	LegoU32 height = renderTargetInfo->GetHeight();
	LegoU32 i = 0;

	if (m_context->m_playerCount > 0) {
		do {
			GolCamera* camera = m_golExport->VTable0x20();
			m_unk0x2acc[i] = camera;

			if (m_unk0x3354) {
				camera->FUN_00404710(
					m_context->m_unk0x0c - g_unk0x004b08bc,
					m_context->m_unk0x10,
					m_context->m_unk0x14,
					2.6666667f
				);
			}
			else {
				camera->FUN_00404710(m_context->m_unk0x0c, m_context->m_unk0x10, m_context->m_unk0x14, 1.3333334f);
			}

			GolCamera* currentCamera = m_unk0x2acc[i];
			currentCamera->GetTransform()->SetPosition(&m_unk0x1f8);
			currentCamera->m_flags |= GolCamera::c_flagBit0;

			currentCamera = m_unk0x2acc[i];
			currentCamera->GetTransform()->VTable0x24(&m_unk0x204, &m_unk0x210);
			currentCamera->m_flags |= GolCamera::c_flagBit0;

			Rect viewport;
			if (!m_unk0x3354) {
				viewport.m_left = 0;
				viewport.m_top = 0;
				viewport.m_right = width;
				viewport.m_bottom = height;
			}
			else {
				if (i != 0) {
					if (i == 1) {
						viewport.m_left = 0;
						viewport.m_top = height >> 1;
						viewport.m_right = width;
						viewport.m_bottom = height;
					}
				}
				else {
					viewport.m_left = 0;
					viewport.m_top = 0;
					viewport.m_right = width;
					viewport.m_bottom = height >> 1;
				}
			}

			m_unk0x2acc[i]->VTable0x0c(&viewport);

			Field0x2ad4* field0x2ad4 = &m_unk0x2ad4[i];
			field0x2ad4->FUN_00428210(m_unk0x2acc[i], m_renderer);
			field0x2ad4->m_unk0x000 = TRUE;

			i++;
		} while (i < m_context->m_playerCount);
	}

	m_renderer->VTable0x20(m_unk0x2acc[0]);
}

// FUNCTION: LEGORACERS 0x00434300
void RaceSession::FUN_00434300()
{
	if (m_golExport) {
		for (LegoS32 i = 0; i < sizeOfArray(m_unk0x2acc); i++) {
			if (m_unk0x2acc[i]) {
				m_golExport->VTable0x54(m_unk0x2acc[i]);
			}
			m_unk0x2acc[i] = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00434340
void RaceSession::FUN_00434340()
{
	if (m_unk0x3ac) {
		m_unk0x3ac->m_unk0x28->FUN_0040dad0(0);
		m_unk0x3ac->m_unk0x28->SetFlags(m_unk0x3ac->m_unk0x28->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);

		GolAnimatedEntity* entity = m_unk0x3ac->m_unk0x28;
		entity->FUN_0040d650();
		entity->SetActiveValue(0.0f);

		LegoU32 i = 0;
		m_unk0x3ac->m_unk0x28->SetFlags(m_unk0x3ac->m_unk0x28->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);

		LegoU32 playerCount = m_context->m_playerCount;
		if (playerCount > 0) {
			GolCamera** camera = m_unk0x2acc;
			do {
				(*camera)->SetTrackedEntity(m_unk0x3ac->m_unk0x28, m_unk0x3ac->m_unk0x2c);
				i++;
				camera++;
			} while (i < m_context->m_playerCount);
		}
	}
}

// FUNCTION: LEGORACERS 0x004348a0
void RaceSession::FUN_004348a0()
{
	Field0x21c* field0x21c = m_unk0x21c;
	if (!field0x21c) {
		m_inputEvents.Reset();
		return;
	}

	InputDispatchSource* source = field0x21c->m_unk0x0a0;
	if (source) {
		source->m_unk0x98 = NULL;
		source->VTable0x54();
	}

	Field0x258* field0x258 = m_unk0x258;
	Field0x340* field0x340 = m_unk0x340;
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x258); i++) {
		field0x340->FUN_00421de0();
		field0x258->FUN_004300a0();
		field0x340++;
		field0x258++;
	}

	m_inputEvents.Reset();
	m_unk0x23c.FUN_004279f0();
	m_unk0x23c.FUN_00427960();
}

// FUNCTION: LEGORACERS 0x00434930
void RaceSession::FUN_00434930()
{
	if (m_unk0x3320) {
		m_unk0x3320->Stop();
		m_unk0x3314->DestroyMusicInstance(m_unk0x3320);
		m_unk0x3320 = NULL;
	}

	m_unk0x3320 = m_unk0x3314->CreateMusicInstance(0);

	if (m_unk0x3320) {
		m_unk0x3320->SetVolume(m_unk0x3324);
		m_unk0x3320->Play(FALSE);
	}
}

// FUNCTION: LEGORACERS 0x004349a0
void RaceSession::FUN_004349a0()
{
	if (m_unk0x3ac && m_unk0x2acc[0] && m_unk0x2acc[0]->m_trackedEntity &&
		m_unk0x2acc[0]->m_trackedEntity->FUN_0040e360()) {
		GolVec3 position;
		GolVec3 forward;
		GolVec3 right;
		GolCamera** camera = m_unk0x2acc;

		GolCamera* currentCamera = *camera;
		GolVec3* positionPtr = &position;
		currentCamera->m_transform->GetPosition(positionPtr);

		currentCamera = *camera;
		GolVec3* rightPtr = &right;
		GolVec3* forwardPtr = &forward;
		currentCamera->m_transform->VTable0x1c(forwardPtr, rightPtr);

		Field0x2ad4* field0x2ad4 = m_unk0x2ad4;
		LegoS32 remaining = sizeOfArray(m_unk0x2ad4);
		do {
			if (*camera) {
				(*camera)->ClearTrackedEntity();
				positionPtr = &position;
				field0x2ad4->FUN_00428390(positionPtr);

				rightPtr = &right;
				forwardPtr = &forward;
				field0x2ad4->FUN_004282a0(forwardPtr, rightPtr);
			}

			camera++;
			field0x2ad4++;
		} while (--remaining);

		m_elapsedMs = 0;
	}

	if (m_elapsedMs >= 2000) {
		GolCamera* camera = m_unk0x2acc[0];
		if (!camera || !camera->m_trackedEntity) {
			m_elapsedMs = 0;
			m_state = 2;

			LegoU32 i = 0;
			if (m_context->m_playerCount > 0) {
				CobaltTrail0x140* cobaltTrail = m_unk0x283c;
				Field0x340* field0x340 = m_unk0x340;
				RaceState::Racer** racer = m_raceState.m_unk0x318;
				do {
					(*racer)->FUN_0043a360();
					if (!m_unk0x335c) {
						cobaltTrail->FUN_00426360();
					}
					(*racer)->FUN_004393d0();
					field0x340->FUN_00422130();

					CobaltTrail0x140* nextCobaltTrail = cobaltTrail + 1;
					i++;
					racer++;
					cobaltTrail = nextCobaltTrail;
					field0x340++;
				} while (i < m_context->m_playerCount);
			}

			if (m_standings) {
				m_standings->FUN_004402b0();
			}

			FUN_00434b00();
		}
	}
}

// FUNCTION: LEGORACERS 0x00434b00
void RaceSession::FUN_00434b00()
{
	if (m_elapsedMs < 3000 && !m_unk0x335c) {
		return;
	}

	m_elapsedMs = 0;
	m_state = 3;
	m_raceState.FUN_0043ccb0();

	LegoU32 i = 0;
	if (m_context->m_playerCount > 0) {
		Field0x258* field0x258 = m_unk0x258;
		do {
			if (field0x258->m_unk0x000) {
				field0x258->FUN_00430710();
			}

			i++;
			field0x258++;
		} while (i < m_context->m_playerCount);
	}

	m_unk0x6dc.FUN_0045b900();

	if (m_timeRaceManager) {
		m_timeRaceManager->FUN_00422eb0(m_raceState.m_unk0x318[0]);
	}

	if (m_unk0x3320) {
		m_unk0x3320->Stop();
		m_unk0x3314->DestroyMusicInstance(m_unk0x3320);

		LegoU32 musicIndex = 1;
		MusicGroup* musicGroup = m_unk0x3314;
		if (musicGroup->GetMusicCount() > 4 && !m_standings) {
			LegoU32 randomValue = 0;
			LegoU32 randomState = g_unk0x004c6ee4;
			g_unk0x004c6ee4 = (randomState + 1) & 0x3ff;
			musicGroup = m_unk0x3314;
			randomValue = g_unk0x004befec[g_unk0x004c6ee4];
			LegoU32 randomIndex = randomValue % (musicGroup->GetMusicCount() - 3);
			switch (randomIndex) {
			case 0:
				musicIndex = 1;
				break;
			case 1:
				musicIndex = 4;
				break;
			case 2:
				musicIndex = 5;
				break;
			case 3:
				musicIndex = 6;
				break;
			default:
				musicIndex = 1;
				break;
			}
		}

		m_unk0x3320 = m_unk0x3314->CreateMusicInstance(musicIndex);
		if (m_unk0x3320) {
			m_unk0x3320->SetVolume(m_unk0x3324);
			m_unk0x3320->Play(TRUE);
		}
	}

	m_unk0x3330 = 0;
	FUN_00434c80();
}

// FUNCTION: LEGORACERS 0x00434c80
void RaceSession::FUN_00434c80()
{
	LegoU32 racerIndex = 0;
	if (m_context->m_racerCount > 0) {
		RaceState::Racer* racer = m_raceState.GetRacers();
		do {
			if (racer->m_lapsCompleted >= m_unk0x3348 && !(racer->m_unk0xd04 & 0x1000)) {
				racer->m_unk0xd04 |= 0x1000;

				if (m_standings) {
					m_standings->FUN_004402c0(racer->m_unk0xe04, m_unk0x3330);
				}

				m_unk0x3330++;
				racer->FUN_0043a210(m_unk0x3330);

				if (racer->m_unk0xd08 != 2 || !m_unk0x3350 || racerIndex == 0) {
					LegoU32 playerIndex = 0;
					RaceState::Racer** playerRacer = m_raceState.m_unk0x318;
					while (*playerRacer != racer && playerIndex < m_context->m_playerCount) {
						playerRacer++;
						playerIndex++;
					}

					m_unk0x283c[playerIndex].FUN_00426370();
					m_elapsedMs = 0;
					m_state = 4;
					if (m_unk0x335c) {
						m_elapsedMs = 9000;
					}

					if (m_unk0x258[playerIndex].m_unk0x000) {
						m_unk0x258[playerIndex].FUN_00430760();
					}

					m_unk0x6dc.FUN_0045b740(racer);

					if (!(racer->m_unk0xd04 & c_racerFlags0xd04Bit4) && !(racer->m_unk0xd04 & 0x200000) &&
						!m_unk0x335c) {
						m_unk0x2ad4[playerIndex].FUN_004283f0(4, m_unk0x3354);
					}

					if (m_timeRaceManager) {
						m_timeRaceManager->UpdateBestRun();
					}

					if (m_unk0x3320) {
						m_unk0x3320->Stop();
						m_unk0x3314->DestroyMusicInstance(m_unk0x3320);

						if (racer->m_lapTimes[5] == 1) {
							m_unk0x3320 = m_unk0x3314->CreateMusicInstance(3);
						}
						else {
							m_unk0x3320 = m_unk0x3314->CreateMusicInstance(2);
						}

						if (m_unk0x3320) {
							m_unk0x3320->SetVolume(m_unk0x3324);
							m_unk0x3320->Play(FALSE);
						}
					}

					if (m_standings) {
						m_standings->m_unk0x00 = m_unk0x2d7c;
						m_standings->m_unk0x08 = &m_raceState;
						m_standings->m_unk0x0c = &m_unk0x30f0;
					}

					FUN_00434eb0();
					return;
				}
			}

			racerIndex++;
			racer++;
		} while (racerIndex < m_context->m_racerCount);
	}
}

// FUNCTION: LEGORACERS 0x00434eb0
void RaceSession::FUN_00434eb0()
{
	if (m_elapsedMs > 9000) {
		if (!m_unk0x27fc.HasActive() && !m_standings) {
			m_unk0x27fc.Activate(1000, FALSE, NULL, NULL);
		}
	}

	if (m_timeRaceManager && m_elapsedMs > 9500) {
		if (m_unk0x30c0 != 2) {
			m_unk0x30c0 = 2;
			FUN_00436010();
		}
		return;
	}

	if (m_elapsedMs >= 10000) {
		m_elapsedMs = 0;
		m_state = 5;

		LegoU32 i = 0;
		if (m_context->m_racerCount > 0) {
			RaceState::Racer* racer = m_raceState.GetRacers();
			do {
				if (!(racer->m_unk0xd04 & 0x1000)) {
					if (m_standings) {
						m_standings->FUN_004402c0(racer->m_unk0xe04, m_unk0x3330);
					}

					m_unk0x3330++;
					racer->FUN_0043a210(m_unk0x3330);
				}

				m_context->m_playerSetupSlots[i].m_unk0x5a[0] = (LegoU8) racer->m_lapTimes[5];
				i++;
				racer++;
			} while (i < m_context->m_racerCount);
		}

		FUN_00435180();
		return;
	}

	LegoU32 racerIndex = 0;
	if (m_context->m_racerCount > 0) {
		RaceState::Racer* racer = m_raceState.GetRacers();
		do {
			if (racer->m_lapsCompleted >= m_unk0x3348 && !(racer->m_unk0xd04 & 0x1000)) {
				racer->m_unk0xd04 |= 0x1000;

				if (m_standings) {
					m_standings->FUN_004402c0(racer->m_unk0xe04, m_unk0x3330);
				}

				m_unk0x3330++;
				racer->FUN_0043a210(m_unk0x3330);

				if (racer->m_unk0xd08 != 2) {
					LegoU32 playerIndex = 0;
					RaceState::Racer** playerRacer = m_raceState.m_unk0x318;
					while (*playerRacer != racer && playerIndex < m_context->m_playerCount) {
						playerRacer++;
						playerIndex++;
					}

					if (m_unk0x258[playerIndex].m_unk0x000) {
						m_unk0x258[playerIndex].FUN_00430760();
					}

					m_unk0x6dc.FUN_0045b740(racer);

					if (!(racer->m_unk0xd04 & c_racerFlags0xd04Bit4) && !(racer->m_unk0xd04 & 0x200000)) {
						m_unk0x2ad4[playerIndex].FUN_004283f0(4, m_unk0x3354);
					}
				}
			}

			if ((racer->m_unk0xd04 & 0x1000) && racer->m_unk0xdb4 && !(racer->m_unk0xd04 & c_racerFlags0xd04Bit4) &&
				!(racer->m_unk0xd04 & 0x200000) && racer->m_unk0xdb8 != 4 && !m_unk0x335c) {
				racer->m_unk0xdb4->FUN_004283f0(4, m_unk0x3354);
			}

			racerIndex++;
			racer++;
		} while (racerIndex < m_context->m_racerCount);
	}

	if (m_standings && m_elapsedMs > 5000) {
		m_standings->FUN_00440330(m_golApp->GetFrameDeltaMs());
	}
}

// FUNCTION: LEGORACERS 0x00435180
void RaceSession::FUN_00435180()
{
	if (m_elapsedMs > 4000) {
		if (!m_unk0x27fc.HasActive()) {
			m_unk0x27fc.Activate(1000, FALSE, NULL, NULL);
		}
	}

	if (m_elapsedMs < 5000 && m_standings) {
		m_standings->FUN_00440330(m_golApp->GetFrameDeltaMs());
		return;
	}

	m_elapsedMs = 0;
	m_running = 0;
}

// FUNCTION: LEGORACERS 0x004351f0
void RaceSession::FUN_004351f0()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x283c); i++) {
		m_unk0x283c[i].FUN_00426390(m_golApp->GetFrameDeltaMs());
	}
}

// FUNCTION: LEGORACERS 0x00435220
void RaceSession::VTable0x30()
{
	LegoU32 elapsedMs = m_golApp->GetFrameDeltaMs();
	if (m_context->m_unk0x20 & c_contextFlag0x20Bit8) {
		elapsedMs =
			static_cast<LegoU32>(static_cast<LegoFloat>(static_cast<LegoS32>(m_golApp->GetFrameDeltaMs())) * 1.75f);
	}

	if (!m_unk0x30c0 ||
		(m_unk0x3058.FUN_00427420(elapsedMs), m_unk0x3058.GetUnk0x48() == 2) && (FUN_00436160(), m_unk0x30c0 != 3)) {
		if (elapsedMs > m_unk0x334c) {
			m_unk0x334c = c_unk0x334cResetMs;
		}
		else {
			m_unk0x334c -= elapsedMs;
		}

		m_unk0x390->FUN_00416090(elapsedMs);
		m_unk0x3a4->FUN_00416090(elapsedMs);
		m_unk0x398->FUN_00416090(elapsedMs);
		m_unk0x6dc.FUN_0045a490(elapsedMs);
		m_unk0x32c4.FUN_0045e470(elapsedMs);
		m_unk0x2128.VTable0x08(elapsedMs);
		m_unk0x2080.VTable0x08(elapsedMs);
		m_unk0x2150.FUN_00489fa0(elapsedMs);
		m_unk0x248c.FUN_00489fa0(elapsedMs);
		m_unk0x27c8.FUN_00493a20(elapsedMs);
		m_unk0x2098.FUN_00461cc0(elapsedMs);
		m_unk0x2148.FUN_0048add0(elapsedMs);
		m_unk0x213c.FUN_00464dd0(elapsedMs);
		m_unk0x27fc.Update(elapsedMs);
		m_soundManager->Update(elapsedMs);

		LegoU32 i;
		if (!m_unk0x3350) {
			for (i = 0; i < m_context->m_playerCount; i++) {
				LegoFloat unk0xa00 = m_raceState.m_unk0x318[i]->m_unk0xa00;
				m_unk0x340[i].FUN_00421e30(elapsedMs, unk0xa00);
				m_unk0x258[i].FUN_00430530(elapsedMs);
			}
		}

		LegoU32 remainingMs = elapsedMs;
		while (remainingMs > 0) {
			LegoS32 stepMs;
			LegoU32 remainingAfterStep;

			if (remainingMs > c_updateStepMs) {
				remainingMs -= c_updateStepMs;
				stepMs = c_updateStepMs;
				remainingAfterStep = remainingMs;
			}
			else {
				remainingAfterStep = 0;
				stepMs = static_cast<LegoS32>(remainingMs);
				remainingMs = 0;
			}

			m_raceState.FUN_0043c030(stepMs);

			for (i = 0; i < m_context->m_playerCount; i++) {
				m_unk0x2ad4[i].FUN_00428540(static_cast<LegoFloat>(stepMs));
			}

			remainingMs = remainingAfterStep;
			if (m_timeRaceManager) {
				m_timeRaceManager->FUN_00422710(stepMs);
			}
		}

		m_unk0x27d4.FUN_00492870(elapsedMs);
		m_unk0x2148.FUN_0048ae00(m_unk0x2acc[0], m_unk0x2ad4[0].m_unk0x0d4);
		m_unk0x2f90.FUN_0041ccb0(elapsedMs);

		if (m_state == 2 || m_state == 3 || m_state == 4) {
			FUN_004351f0();
		}
	}
}

// STUB: LEGORACERS 0x004354d0
void RaceSession::FUN_004354d0()
{
	if (m_unk0x6dc.GetUnk0x19a0()) {
		m_unk0x6dc.FUN_0045a7b0(FALSE);
		return;
	}

	GolAppEventHandler::VTable0x00();
	m_renderer->VTable0x20(m_unk0x2acc[0]);
	VTable0x34();

	if (m_unk0x3354) {
		m_raceState.m_unk0x318[0]->m_unk0x018.FUN_0043fa50(m_unk0x2acc[0]);
		m_raceState.m_unk0x318[1]->m_unk0x018.FUN_0043fa50(m_unk0x2acc[1]);
	}
	else {
		m_raceState.FUN_0043c6a0(m_unk0x2acc[0]);
	}

	LegoU32 viewportIndex = 1;
	if (m_unk0x3354) {
		m_renderer->VTable0xec(TRUE);
	}
	else {
		m_renderer->VTable0xec(FALSE);
	}

	if (m_raceState.m_unk0x318[0]->m_unk0xd04 & c_racerFlags0xd04Bit4) {
		m_unk0x6dc.FUN_0045a7b0(TRUE);
	}
	else {
		GolVec3 cameraPosition;
		m_unk0x2acc[0]->GetTransform()->GetPosition(&cameraPosition);
		m_unk0x2f90.FUN_0041d040(&cameraPosition);

		switch (m_state) {
		case 1:
			FUN_004357b0(m_raceState.m_unk0x318[0]);
			break;
		case 2:
			FUN_004357b0(m_raceState.m_unk0x318[0]);
			break;
		case 3:
			FUN_004357b0(m_raceState.m_unk0x318[0]);
			break;
		case 4:
			FUN_004357b0(m_raceState.m_unk0x318[0]);
			break;
		case 5:
			FUN_004357b0(m_raceState.m_unk0x318[0]);
			break;
		}
	}

	if (m_context->m_playerCount > 1) {
		do {
			m_renderer->VTable0x20(m_unk0x2acc[viewportIndex]);
			m_renderer->VTable0x5c();
			m_renderer->VTable0xec(++viewportIndex);

			if (m_raceState.m_unk0x318[viewportIndex - 1]->m_unk0xd04 & c_racerFlags0xd04Bit4) {
				m_unk0x6dc.FUN_0045a7b0(FALSE);
			}
			else {
				GolVec3 cameraPosition;
				m_unk0x2acc[viewportIndex - 1]->GetTransform()->GetPosition(&cameraPosition);
				m_unk0x2f90.FUN_0041d040(&cameraPosition);

				switch (m_state) {
				case 1:
					FUN_004357b0(m_raceState.m_unk0x318[viewportIndex - 1]);
					break;
				case 2:
					FUN_004357b0(m_raceState.m_unk0x318[viewportIndex - 1]);
					break;
				case 3:
					FUN_004357b0(m_raceState.m_unk0x318[viewportIndex - 1]);
					break;
				case 4:
					FUN_004357b0(m_raceState.m_unk0x318[viewportIndex - 1]);
					break;
				case 5:
					FUN_004357b0(m_raceState.m_unk0x318[viewportIndex - 1]);
					break;
				}
			}
		} while (viewportIndex < m_context->m_playerCount);
	}

	if (m_unk0x3354) {
		m_renderer->VTable0xec(FALSE);
	}

	m_renderer->VTable0xe8(FALSE);

	switch (m_state) {
	case 1:
		FUN_004357e0();
		break;
	case 2:
		FUN_00435800();
		break;
	case 3:
		FUN_00435830();
		break;
	case 4:
		FUN_00435860();
		break;
	case 5:
		FUN_004358e0();
		break;
	}

	m_renderer->VTable0xe4();
	FUN_00435bf0();
}

// FUNCTION: LEGORACERS 0x004357b0
void RaceSession::FUN_004357b0(RaceState::Racer* p_racer)
{
	m_unk0x2f90.FUN_0041d0f0(m_renderer);
	VTable0x38(p_racer);
	VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004357e0
void RaceSession::FUN_004357e0()
{
	FUN_00435ab0();
	m_unk0x27fc.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435800
void RaceSession::FUN_00435800()
{
	VTable0x40();
	FUN_00435ab0();
	m_unk0x27fc.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435830
void RaceSession::FUN_00435830()
{
	VTable0x40();
	FUN_00435ab0();
	GolAppEventHandler::VTable0x00();
	m_unk0x27fc.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435860
void RaceSession::FUN_00435860()
{
	VTable0x40();
	if (m_standings && m_running && m_elapsedMs > 5000) {
		for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
			m_unk0x283c[i].m_unk0x070 = 0;
		}

		m_standings->FUN_00440350(FALSE);
	}

	FUN_00435ab0();
	m_unk0x27fc.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x004358e0
void RaceSession::FUN_004358e0()
{
	if (m_standings && m_running) {
		m_standings->FUN_00440350(TRUE);
	}

	FUN_00435ab0();
	m_unk0x27fc.Draw(m_renderer);
	FUN_00435920();
}

// FUNCTION: LEGORACERS 0x00435920
void RaceSession::FUN_00435920()
{
	if (m_unk0x30c0) {
		m_unk0x3058.FUN_00427440();
	}
}

// FUNCTION: LEGORACERS 0x00435940
void RaceSession::VTable0x34()
{
	if (m_unk0x3358) {
		m_renderer->VTable0x54(2);
	}
	else {
		m_renderer->VTable0x54(6);
	}
}

// FUNCTION: LEGORACERS 0x00435960
void RaceSession::VTable0x38(RaceState::Racer* p_racer)
{
	m_raceState.FUN_0043cd30(m_renderer, p_racer);
	m_unk0x6dc.FUN_0045a7b0(FALSE);
	m_unk0x2150.FUN_00489ff0(m_renderer);
	m_unk0x248c.FUN_00489ff0(m_renderer);
	m_unk0x27c8.FUN_00493a60(m_renderer);

	m_unk0x390->VTable0x24(m_renderer);
	m_unk0x390->VTable0x20(m_renderer);
	m_unk0x390->VTable0x28(m_renderer);
	m_unk0x390->VTable0x1c(m_renderer);

	m_unk0x27d4.FUN_004928b0(m_renderer);
}

// FUNCTION: LEGORACERS 0x00435a00
void RaceSession::VTable0x3c()
{
	m_unk0x398->FUN_00416040();
	m_raceState.FUN_0043bff0(m_renderer);
	m_unk0x2148.FUN_0048ae30(m_renderer);
	m_unk0x6dc.FUN_0045a8a0();
	m_unk0x2150.FUN_0048a040(m_renderer);
	m_unk0x248c.FUN_0048a040(m_renderer);
	m_unk0x27c8.FUN_00493aa0(m_renderer);
	m_unk0x27d4.FUN_004928f0(m_renderer);

	if (m_timeRaceManager) {
		m_timeRaceManager->FUN_00422960(m_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00435a90
void RaceSession::VTable0x40()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x283c); i++) {
		m_unk0x283c[i].FUN_004263a0();
	}
}

// FUNCTION: LEGORACERS 0x00435ab0
void RaceSession::FUN_00435ab0()
{
	if (m_unk0x3350 && m_unk0x334c > c_overlayDrawDelayMs) {
		GolString string;
		const SlatePeak0x58* renderTargetInfo = m_renderer->GetRenderTargetInfo();
		string.CopyFromBufSelection(m_unk0x30f0.GetStringBuffer(c_overlayStringId), 0);

		LegoS32 textWidth;
		LegoS32 textHeight;
		m_unk0x2d7c->MeasureString(&string, &textWidth, &textHeight);

		m_renderer->VTable0x64(
			&string,
			m_unk0x2d7c,
			(renderTargetInfo->GetWidthU32() >> 1) - (static_cast<LegoU32>(textWidth) >> 1),
			renderTargetInfo->GetHeightU32() - textHeight - c_overlayBottomPadding,
			1.0f,
			1.0f,
			NULL,
			0
		);
	}
}

// FUNCTION: LEGORACERS 0x00435bf0
void RaceSession::FUN_00435bf0()
{
	m_renderer->VTable0xf0();
}

// FUNCTION: LEGORACERS 0x00435c00
void RaceSession::VTable0x44(LegoU32 p_keyCode)
{
	if (m_unk0x3350 && (p_keyCode & c_keySourceAbortMask)) {
		m_running = 0;
		m_context->m_unk0x1e |= LegoRacers::Context::c_flagBit7;
		return;
	}

	switch (p_keyCode) {
	case c_keyboardKey0x01:
	case c_keyboardKey0xc5:
		if (!m_unk0x30c0) {
			m_unk0x30c0 = 1;
			FUN_00436010();
		}
		break;
	case c_keyboardKey0xb7:
		FUN_00435f20();
		break;
	}

	if (m_unk0x3338 == 3) {
		m_running = 0;
	}

	if (m_unk0x3338 == 7) {
		m_running = 0;
		m_context->m_running = FALSE;
	}

	if (m_unk0x30c0) {
		m_unk0x3058.FUN_00427810(p_keyCode);
	}
}

// FUNCTION: LEGORACERS 0x00435cc0
void RaceSession::VTable0x48(LegoU32 p_keyCode)
{
	switch (p_keyCode) {
	case c_keyboardKey0x10:
		m_unk0x3338 &= ~c_unk0x3338Bit0;
		break;
	case c_keyboardKey0x1d:
		m_unk0x3338 &= ~c_unk0x3338Bit1;
		break;
	case c_keyboardKey0x2a:
		m_unk0x3338 &= ~c_unk0x3338Bit2;
		break;
	}

	if (m_unk0x30c0) {
		m_unk0x3058.FUN_004278c0(p_keyCode);
	}
}

// FUNCTION: LEGORACERS 0x00435f20
void RaceSession::FUN_00435f20()
{
	GolHashTable::Entry* currentEntry;
	GolBmpWriterFile bmpWriter;
	LegoChar fileName[32];
	LegoU32 screenshotIndex;

	if (g_hashTable) {
		currentEntry = g_hashTable->GetCurrentEntry();
		g_hashTable->SetCurrentEntryFromString(NULL);
	}
	else {
		currentEntry = NULL;
	}

	for (screenshotIndex = 0; screenshotIndex <= c_maxScreenshotIndex; screenshotIndex++) {
		sprintf(fileName, "LEGO%d.bmp", screenshotIndex);
		if (GolStream::FindFile(fileName) != GolStream::e_ioSuccess) {
			break;
		}
	}

	if (screenshotIndex <= c_maxScreenshotIndex) {
		bmpWriter.VTable0x08(fileName);
		bmpWriter.WriteSurface(m_renderer->GetRenderTargetInfo());
		bmpWriter.Destroy();

		if (g_hashTable) {
			g_hashTable->SetCurrentEntry(currentEntry);
		}
	}
}

// FUNCTION: LEGORACERS 0x00436010
void RaceSession::FUN_00436010()
{
	LegoU32 playerIndex = 0;
	if (m_context->m_playerCount > 0) {
		Field0x258* field0x258 = m_unk0x258;
		Field0x340* field0x340 = m_unk0x340;

		do {
			field0x258->m_unk0x004.m_unk0x054 = 0;
			field0x258->m_unk0x004.FUN_00430c20();
			field0x340->FUN_00422170();

			playerIndex++;
			field0x258++;
			field0x340++;
		} while (playerIndex < m_context->m_playerCount);
	}

	m_unk0x23c.m_unk0x18 = 0;
	m_unk0x23c.FUN_00427b40();

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x283c); i++) {
		m_unk0x283c[i].m_unk0x13c = 0;
	}

	if (m_standings) {
		m_standings->m_unk0x44 = 0;
	}

	switch (m_unk0x30c0) {
	case 1:
		if (m_standings) {
			m_unk0x3058.FUN_00427310(3, &g_unk0x004bee74[4], g_unk0x004bee74[3], 0xffff, 0);
		}
		else {
			m_unk0x3058.FUN_00427310(3, &g_unk0x004bee74[0], g_unk0x004bee74[3], 0xffff, 0);
		}
		break;
	case 2:
		if (m_timeRaceManager->HasBeatenRecord()) {
			m_unk0x3058.FUN_00427310(2, &g_unk0x004bee74[8], g_unk0x004bee74[12], g_unk0x004bee74[13], 0);
		}
		else {
			m_unk0x3058.FUN_00427310(2, &g_unk0x004bee74[8], g_unk0x004bee74[10], g_unk0x004bee74[11], 0);
		}
		break;
	case 3:
		m_unk0x3058.FUN_00427310(2, &g_unk0x004bee74[8], g_unk0x004bee74[14], 0xffff, 1);
		break;
	}

	MusicInstance* musicInstance = m_unk0x3320;
	if (musicInstance) {
		musicInstance->Pause();
	}

	m_soundManager->Pause();
}

// FUNCTION: LEGORACERS 0x00436160
void RaceSession::FUN_00436160()
{
	LegoU32 selectionIndex = m_unk0x3058.GetUnk0x50();
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x283c); i++) {
		m_unk0x283c[i].m_unk0x13c = 1;
	}

	if (m_standings) {
		m_standings->m_unk0x44 = 1;
	}

	switch (m_unk0x30c0) {
	case 3:
		if (!selectionIndex) {
			if (m_unk0x3360 == 1) {
				if (!m_standings || (m_context->m_unk0x1e & LegoRacers::Context::c_flagFirstRace)) {
					if (m_standings) {
						m_standings->ClearPoints();
					}
					FUN_004362e0();
				}
				else {
					m_running = 0;
					m_context->m_unk0x1e |= LegoRacers::Context::c_flagRestartCircuit;
				}
			}
			else if (m_unk0x3360 == 2) {
				m_running = 0;
				m_context->m_unk0x1e |= LegoRacers::Context::c_flagAbortRace;
			}
		}

		m_unk0x3360 = 0;
		break;
	case 2:
		if (!selectionIndex) {
			if (m_timeRaceManager) {
				m_timeRaceManager->FUN_00422de0();
			}
			FUN_004362e0();
		}
		else {
			m_running = 0;
		}
		break;
	case 1:
		if (selectionIndex == 1) {
			m_unk0x3360 = 1;
		}
		else if (selectionIndex == 2) {
			m_unk0x3360 = 2;
		}
		break;
	}

	if (m_unk0x3360) {
		m_unk0x30c0 = 3;
		FUN_00436010();
	}
	else {
		m_unk0x30c0 = 0;

		for (LegoU32 i = 0; i < m_context->m_playerCount; i++) {
			m_unk0x258[i].m_unk0x004.m_unk0x054 = 1;
			m_unk0x340[i].FUN_004221a0();
		}

		m_unk0x23c.m_unk0x18 = 1;
		m_soundManager->Resume();

		if (m_unk0x3320) {
			m_unk0x3320->Resume();
		}
	}
}

// FUNCTION: LEGORACERS 0x004362e0
void RaceSession::FUN_004362e0()
{
	RaceState::Racer* racer = m_raceState.GetUnk0x318();
	if (racer) {
		m_context->m_unk0x398 = racer->m_unk0xdb8;
	}

	m_unk0x30c4.FUN_0043a6e0();
	m_unk0x27d4.FUN_00492840();

	m_elapsedMs = 0;
	m_state = 1;

	LegoU32 playerIndex = 0;
	if (m_context->m_playerCount > 0) {
		do {
			Field0x2ad4* field0x2ad4 = &m_unk0x2ad4[playerIndex];

			m_unk0x258[playerIndex].FUN_00430100();
			m_unk0x340[playerIndex].FUN_00422150();
			m_raceState.m_unk0x318[playerIndex]->FUN_0043a300(m_context->m_unk0x398, m_unk0x3354);
			field0x2ad4->FUN_00428540(1.0f);
			field0x2ad4->FUN_004283d0(0);
			field0x2ad4->FUN_00428390(&m_unk0x1f8);
			field0x2ad4->FUN_004282a0(&m_unk0x204, &m_unk0x210);

			LegoFloat fov;
			if (m_unk0x3354) {
				GolCamera* currentCamera = m_unk0x2acc[playerIndex];
				LegoU32 cameraFlags = currentCamera->m_flags | GolCamera::c_flagBit1;
				currentCamera->m_fov = m_context->m_unk0x0c - g_unk0x004b08bc;
				currentCamera->m_flags = cameraFlags;
				fov = m_context->m_unk0x0c - g_unk0x004b08bc;
			}
			else {
				GolCamera* currentCamera = m_unk0x2acc[playerIndex];
				LegoU32 cameraFlags = currentCamera->m_flags | GolCamera::c_flagBit1;
				LegoFloat cameraFov = m_context->m_unk0x0c;
				currentCamera->m_fov = cameraFov;
				currentCamera->m_flags = cameraFlags;
				fov = m_context->m_unk0x0c;
			}

			field0x2ad4->m_unk0x134 = fov;
			field0x2ad4->m_unk0x140 = 0;
			MenuAnimationList* animationList = &m_unk0x27fc;
			field0x2ad4->m_unk0x000 = TRUE;

			animationList->FUN_00494fe0();

			playerIndex++;
		} while (playerIndex < m_context->m_playerCount);
	}

	m_unk0x283c[0].FUN_004262d0(0xffffffff);

	if (m_unk0x3354) {
		m_unk0x283c[1].FUN_004262d0(0xffffffff);
	}

	FUN_00434340();
	FUN_00434930();
}

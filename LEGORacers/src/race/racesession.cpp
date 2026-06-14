#include "race/racesession.h"

#include "app/golapp.h"
#include "golerror.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"

#include <mmsystem.h>

DECOMP_SIZE_ASSERT(RaceSession, 0x3368)

// STUB: LEGORACERS 0x004316e0
RaceSession::RaceSession()
{
	// TODO
	STUB(0x4316e0);
}

// STUB: LEGORACERS 0x00431990
RaceSession::~RaceSession()
{
	// TODO
	STUB(0x431990);
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

	RaceState::Field0x318* field = m_raceState.GetUnk0x318();
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

// STUB: LEGORACERS 0x00432790
void RaceSession::Shutdown()
{
	// TODO
	STUB(0x432790);
}

// STUB: LEGORACERS 0x004349a0
void RaceSession::FUN_004349a0()
{
	// TODO
	STUB(0x004349a0);
}

// STUB: LEGORACERS 0x00434b00
void RaceSession::FUN_00434b00()
{
	// TODO
	STUB(0x00434b00);
}

// STUB: LEGORACERS 0x00434c80
void RaceSession::FUN_00434c80()
{
	// TODO
	STUB(0x00434c80);
}

// STUB: LEGORACERS 0x00434eb0
void RaceSession::FUN_00434eb0()
{
	// TODO
	STUB(0x00434eb0);
}

// STUB: LEGORACERS 0x00435180
void RaceSession::FUN_00435180()
{
	// TODO
	STUB(0x00435180);
}

// STUB: LEGORACERS 0x00435220
void RaceSession::VTable0x30()
{
	// TODO
	STUB(0x435220);
}

// STUB: LEGORACERS 0x004354d0
void RaceSession::FUN_004354d0()
{
	// TODO
	STUB(0x004354d0);
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

// STUB: LEGORACERS 0x00435960
void RaceSession::VTable0x38()
{
	// TODO
	STUB(0x00435960);
}

// STUB: LEGORACERS 0x00435a00
void RaceSession::VTable0x3c()
{
	// TODO
	STUB(0x00435a00);
}

// STUB: LEGORACERS 0x00435a90
void RaceSession::VTable0x40()
{
	// TODO
	STUB(0x00435a90);
}

// STUB: LEGORACERS 0x00435c00
void RaceSession::VTable0x44(undefined4)
{
	// TODO
	STUB(0x00435c00);
}

// STUB: LEGORACERS 0x00435cc0
void RaceSession::VTable0x48(undefined4)
{
	// TODO
	STUB(0x00435cc0);
}

// STUB: LEGORACERS 0x00436010
void RaceSession::FUN_00436010()
{
	// TODO
	STUB(0x00436010);
}

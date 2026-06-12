#include "race/glassblock0x3368.h"

#include "app/golapp.h"
#include "golerror.h"
#include "race/glassshard0x3b8.h"

#include <mmsystem.h>

DECOMP_SIZE_ASSERT(GlassBlock0x3368, 0x3368)

// STUB: LEGORACERS 0x004316e0
GlassBlock0x3368::GlassBlock0x3368()
{
	// TODO
	STUB(0x4316e0);
}

// STUB: LEGORACERS 0x00431990
GlassBlock0x3368::~GlassBlock0x3368()
{
	// TODO
	STUB(0x431990);
}

// STUB: LEGORACERS 0x00431e00
LegoS32 GlassBlock0x3368::Initialize(LegoRacers::Context* p_context, const LegoChar*, undefined4, GlassShard0x3b8*)
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
void GlassBlock0x3368::VTable0x00()
{
	m_unk0x3334 = 0;
	m_context->m_unk0x00 = 0;
}

// FUNCTION: LEGORACERS 0x00432540
void GlassBlock0x3368::Run()
{
	m_unk0x3334 = 1;
	m_unk0x333c = 0;
	m_unk0x3340 = 0;

	LegoS32 previousTime = timeGetTime();

	m_unk0x3344 = 0.0f;
	m_unk0x332c = 0;

	LegoU32 frameSampleCount = 0;
	LegoU32 frameSampleElapsedMs = 0;

	m_unk0x3328 = 1;
	m_renderer->VTable0x44();

	while (m_unk0x3334) {
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
				m_unk0x332c += m_golApp->GetFrameDeltaMs();
			}

			switch (m_unk0x3328) {
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

			if (m_unk0x333c) {
				LegoS32 currentTime = timeGetTime();
				m_unk0x3340 += currentTime - previousTime;
				frameSampleElapsedMs += currentTime - previousTime;
				frameSampleCount++;
				previousTime = currentTime;

				if (frameSampleCount >= 64) {
					frameSampleElapsedMs >>= 6;
					frameSampleCount = 0;
					m_unk0x3344 = 1.0f / (static_cast<LegoFloat>((LegoS32) frameSampleElapsedMs) * 0.001f);
					frameSampleElapsedMs = 0;
				}
			}

			m_unk0x333c++;
		}
	}

	m_renderer->VTable0xf4();
	m_renderer->VTable0x38();
	m_renderer->VTable0x48();
	m_unk0x3bc.FUN_0043beb0(m_context);

	AzureCircuit0x320::Field0x318* field = m_unk0x3bc.GetUnk0x318();
	if (field) {
		m_context->m_unk0x398 = field->m_unk0xdb8;
	}

	if (m_context->m_unk0x00 && m_unk0x3364) {
		m_context->m_unk0x1e |= LegoRacers::Context::c_flagBit4;

		if (m_unk0x3364->FUN_004234b0()) {
			m_context->m_unk0x1e |= LegoRacers::Context::c_flagBit0;
		}
	}
}

// STUB: LEGORACERS 0x00432790
void GlassBlock0x3368::Shutdown()
{
	// TODO
	STUB(0x432790);
}

// STUB: LEGORACERS 0x004349a0
void GlassBlock0x3368::FUN_004349a0()
{
	// TODO
	STUB(0x004349a0);
}

// STUB: LEGORACERS 0x00434b00
void GlassBlock0x3368::FUN_00434b00()
{
	// TODO
	STUB(0x00434b00);
}

// STUB: LEGORACERS 0x00434c80
void GlassBlock0x3368::FUN_00434c80()
{
	// TODO
	STUB(0x00434c80);
}

// STUB: LEGORACERS 0x00434eb0
void GlassBlock0x3368::FUN_00434eb0()
{
	// TODO
	STUB(0x00434eb0);
}

// STUB: LEGORACERS 0x00435180
void GlassBlock0x3368::FUN_00435180()
{
	// TODO
	STUB(0x00435180);
}

// STUB: LEGORACERS 0x00435220
void GlassBlock0x3368::VTable0x30()
{
	// TODO
	STUB(0x435220);
}

// STUB: LEGORACERS 0x004354d0
void GlassBlock0x3368::FUN_004354d0()
{
	// TODO
	STUB(0x004354d0);
}

// STUB: LEGORACERS 0x00435940
void GlassBlock0x3368::VTable0x34()
{
	// TODO
	STUB(0x00435940);
}

// STUB: LEGORACERS 0x00435960
void GlassBlock0x3368::VTable0x38()
{
	// TODO
	STUB(0x00435960);
}

// STUB: LEGORACERS 0x00435a00
void GlassBlock0x3368::VTable0x3c()
{
	// TODO
	STUB(0x00435a00);
}

// STUB: LEGORACERS 0x00435a90
void GlassBlock0x3368::VTable0x40()
{
	// TODO
	STUB(0x00435a90);
}

// STUB: LEGORACERS 0x00435c00
void GlassBlock0x3368::VTable0x44(undefined4)
{
	// TODO
	STUB(0x00435c00);
}

// STUB: LEGORACERS 0x00435cc0
void GlassBlock0x3368::VTable0x48(undefined4)
{
	// TODO
	STUB(0x00435cc0);
}

// STUB: LEGORACERS 0x00436010
void GlassBlock0x3368::FUN_00436010()
{
	// TODO
	STUB(0x00436010);
}

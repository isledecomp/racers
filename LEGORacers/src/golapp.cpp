#include "golapp.h"

#include "../../GolDP/include/goldrawstate.h"
#include "cactusinterface0x4.h"

DECOMP_SIZE_ASSERT(GolApp, 0x830)

// FUNCTION: LEGORACERS 0x004162c0
void GolApp::ResetRuntimeState()
{
	m_maxFrameDeltaMs = 100;
	m_golExport = NULL;
	m_golDrawState = NULL;
	m_unk0x808 = 0;
	m_renderer = NULL;
	m_flags = 0;
	m_width = 0;
	m_height = 0;
	m_bpp = 0;
	m_lastFrameTimeMs = 0;
	m_frameDeltaMs = 0;
	m_fileSourceCount = 0;
	m_disabled = FALSE;
	m_eventHandler = NULL;
}

// FUNCTION: LEGORACERS 0x00416320
GolApp::GolApp()
{
	ResetRuntimeState();
}

// FUNCTION: LEGORACERS 0x004163d0
GolApp::~GolApp()
{
	ResetRuntimeState();
}

// FUNCTION: LEGORACERS 0x00416450
void GolApp::PresentFrame()
{
	m_golDrawState->VTable0x4c();
}

// FUNCTION: LEGORACERS 0x00416460
void GolApp::NotifyCloseRequested()
{
	if (m_eventHandler) {
		m_eventHandler->VTable0x00();
	}
}

// FUNCTION: LEGORACERS 0x00416470
void GolApp::InitializeDisplayWithDevice(
	LegoU32 p_width,
	LegoU32 p_height,
	LegoU32 p_bpp,
	LegoU32 p_flags,
	const LegoChar*,
	const LegoChar*
)
{
	InitializeDisplay(p_width, p_height, p_bpp, p_flags);
}

// FUNCTION: LEGORACERS 0x00416490
void GolApp::ClearFileSourceDirectoryCaches()
{
	for (LegoU32 i = 0; i < m_fileSourceCount; i++) {
		m_fileSources[i].ClearDirectoryTree();
	}
}

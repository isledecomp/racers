#include "videoplayer.h"

#include "decomp.h"
#include "golerror.h"

#include <control.h>
#include <stdio.h>
#include <string.h>
#include <uuids.h>
#include <windows.h>

DECOMP_SIZE_ASSERT(VideoPlayer::Graph, 0x18)

// GLOBAL: LEGORACERS 0x004cebd0
DEVMODEA g_devModeApply;

// GLOBAL: LEGORACERS 0x004cec68
DEVMODEA g_devModeCurrent;

// GLOBAL: LEGORACERS 0x004cecfc
LegoU32 g_savedWindowMode;

// GLOBAL: LEGORACERS 0x004ced00
LegoBool g_displayChanged;

// GLOBAL: LEGORACERS 0x004ced04
LegoChar g_buffer[256];

// GLOBAL: LEGORACERS 0x004cee04
WCHAR g_wideCharStr[256];

// STUB: LEGORACERS 0x004a5fe0
LegoS32 VideoPlayer::PlayImpl(IronFlame0x944*, LPCSTR, LegoBool32, LegoBool32)
{
	STUB(0x4a5fe0);
	return 0;
}

// STUB: LEGORACERS 0x004a60c0
int VideoPlayer::FUN_004a60c0(IronFlame0x944*, DWORD, DWORD)
{
	STUB(0x4a60c0);
	return 1;
}

// STUB: LEGORACERS 0x004a6190
void VideoPlayer::RevertDisplay()
{
	STUB(0x4a6190);
}

// STUB: LEGORACERS 0x004a61c0
int VideoPlayer::FUN_004a61c0(IronFlame0x944*, LPCSTR, int, int)
{
	STUB(0x4a61c0);
	return 0;
}

// STUB: LEGORACERS 0x004a61e0
int VideoPlayer::FUN_004a61e0(IronFlame0x944*)
{
	STUB(0x4a61e0);
	return 1;
}

// FUNCTION: LEGORACERS 0x004a6260
VideoPlayer::Graph::Graph()
{
	m_graph = NULL;
	m_eventHandle = NULL;
	m_hwnd = NULL;
	m_running = FALSE;
	m_hasVideoWindow = FALSE;
	m_autoRewind = FALSE;
}

// FUNCTION: LEGORACERS 0x004a6280 FOLDED
VideoPlayer::Graph::~Graph()
{
	Release();
}

// FUNCTION: LEGORACERS 0x004a6280 FOLDED
void VideoPlayer::Graph::Destroy()
{
	Release();
}

// FUNCTION: LEGORACERS 0x004a6290
LegoBool32 VideoPlayer::Graph::CreateGraph()
{
	if (m_graph) {
		Release();
	}

	m_running = FALSE;
	m_hasVideoWindow = FALSE;
	m_hwnd = NULL;

	if (FAILED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**) &m_graph))) {
		return 0;
	}

	GetMediaEvent();
	return 1;
}

// FUNCTION: LEGORACERS 0x004a62e0
HANDLE VideoPlayer::Graph::GetMediaEvent()
{
	m_eventHandle = NULL;
	if (!m_graph) {
		return NULL;
	}

	IMediaEvent* mediaEvent;
	if (FAILED(m_graph->QueryInterface(IID_IMediaEvent, (void**) &mediaEvent))) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to initialize ActiveMovie media event interface");
	}

	HRESULT hr = mediaEvent->GetEventHandle((OAEVENT*) &m_eventHandle);
	mediaEvent->Release();

	if (FAILED(hr)) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to get ActiveMovie notify event handle");
	}

	return m_eventHandle;
}

// FUNCTION: LEGORACERS 0x004a6360
void VideoPlayer::Graph::Release()
{
	if (m_graph) {
		m_graph->Release();
		m_graph = NULL;
	}

	m_running = FALSE;
	m_hasVideoWindow = FALSE;
}

// FUNCTION: LEGORACERS 0x004a6380
LegoBool32 VideoPlayer::Graph::LoadFile(LPCSTR p_filename)
{
	if (!CreateGraph()) {
		return 0;
	}

	MultiByteToWideChar(CP_ACP, 0, p_filename, -1, g_wideCharStr, sizeOfArray(g_wideCharStr) - 1);
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	HRESULT hr = m_graph->RenderFile(g_wideCharStr, NULL);
	SetCursor(LoadCursor(NULL, IDC_ARROW));

	if (FAILED(hr)) {
		sprintf(g_buffer, "Unable to open the video file:\n%s", p_filename);
		Release();
		GOL_FATALERROR_MESSAGE(g_buffer);
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x004a6430
void VideoPlayer::Graph::StartPlayback(LegoBool32 p_fullscreen, LegoBool32)
{
	if (!m_graph) {
		return;
	}

	m_hasVideoWindow = p_fullscreen;

	if (m_hwnd && p_fullscreen) {
		SetWindowPos(m_hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}

	IVideoWindow* videoWindow;
	if (FAILED(m_graph->QueryInterface(IID_IVideoWindow, (void**) &videoWindow))) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to get ActiveMovie video window control");
	}

	if (m_hwnd && FAILED(videoWindow->put_MessageDrain((OAHWND) m_hwnd))) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to set message drain");
	}

	long style = 0;
	videoWindow->get_WindowStyle(&style);
	style &= 0xFF33FFFF;
	videoWindow->put_WindowStyle(style);
	videoWindow->SetWindowPosition(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	videoWindow->HideCursor(-1);
	videoWindow->Release();

	IMediaControl* mediaControl;
	if (FAILED(m_graph->QueryInterface(IID_IMediaControl, (void**) &mediaControl))) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to get ActiveMovie media control");
	}

	HRESULT hr = mediaControl->Run();
	mediaControl->Release();

	if (FAILED(hr)) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to run ActiveMovie");
	}

	m_running = TRUE;
}

// STUB: LEGORACERS 0x004a65a0
void VideoPlayer::Graph::StopPlayback()
{
	STUB(0x4a65a0);
}

// STUB: LEGORACERS 0x004a6720
void VideoPlayer::Graph::ResetPosition()
{
	STUB(0x4a6720);
}

// STUB: LEGORACERS 0x004a67f0
void VideoPlayer::Graph::RunMessageLoop(LegoBool32)
{
	STUB(0x4a67f0);
}

// STUB: LEGORACERS 0x004a68c0
void VideoPlayer::Graph::ProcessEvent()
{
	STUB(0x4a68c0);
}

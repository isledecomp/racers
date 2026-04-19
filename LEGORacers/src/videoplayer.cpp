#include "videoplayer.h"

#include "compat.h"
#include "decomp.h"
#include "golerror.h"

#include <control.h>
#include <evcode.h>
#include <stdio.h>
#include <string.h>
#include <uuids.h>
#include <windows.h>

#ifndef COMPAT_MODE
typedef long LONG_PTR;
#endif

DECOMP_SIZE_ASSERT(VideoPlayer::Graph, 0x18)

// GLOBAL: LEGORACERS 0x004cebd0
DEVMODE g_devModeApply;

// GLOBAL: LEGORACERS 0x004cec68
DEVMODE g_devModeCurrent;

// GLOBAL: LEGORACERS 0x004cecfc
LegoU32 g_savedWindowMode;

// GLOBAL: LEGORACERS 0x004ced00
LegoBool g_displayChanged;

// GLOBAL: LEGORACERS 0x004ced04
LegoChar g_buffer[256];

// GLOBAL: LEGORACERS 0x004cee04
WCHAR g_wideCharStr[256];

// FUNCTION: LEGORACERS 0x004a5fe0
LegoS32 VideoPlayer::Play(
	IronFlame0x944* p_unk0x04,
	LPCSTR p_filename,
	LegoBool32 p_abortableOnKey,
	LegoBool32 p_autoRewind
)
{
	Graph g;
	LegoS32 result = 0;

	if (GetDeviceCaps(GetDC(p_unk0x04->GetHwnd()), BITSPIXEL) == 4) {
		return 0;
	}

	if (g.LoadFile(p_filename)) {
		g.m_hwnd = p_unk0x04->GetHwnd();
		g.StartPlayback(TRUE, p_autoRewind);
		g.RunMessageLoop(p_abortableOnKey);
		g.m_hwnd = NULL;
		g.Destroy();
		result = 1;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004a60c0
int VideoPlayer::Begin(IronFlame0x944* p_unk0x04, DWORD p_width, DWORD p_height)
{
	RevertDisplay();
	ShowCursor(FALSE);

	g_savedWindowMode = p_unk0x04->GetWindowMode();
	HWND hWnd = p_unk0x04->GetHwnd();
	ShowWindow(hWnd, SW_MAXIMIZE);
	BringWindowToTop(hWnd);

	g_devModeCurrent.dmSize = sizeof(DEVMODE);
	g_devModeCurrent.dmDriverExtra = 0;

	if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &g_devModeCurrent)) {
		memcpy(&g_devModeApply, &g_devModeCurrent, sizeof(DEVMODE));
		g_devModeApply.dmBitsPerPel = 16;
		g_devModeApply.dmPelsWidth = p_width;
		g_devModeApply.dmPelsHeight = p_height;
		g_devModeApply.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&g_devModeApply, CDS_FULLSCREEN | CDS_RESET) == DISP_CHANGE_SUCCESSFUL) {
			g_displayChanged = TRUE;
		}
	}

	ShowWindow(hWnd, SW_MAXIMIZE);
	BringWindowToTop(hWnd);
	return 1;
}

// FUNCTION: LEGORACERS 0x004a6190
void VideoPlayer::RevertDisplay()
{
	if (g_displayChanged) {
		g_displayChanged = FALSE;
		g_devModeCurrent.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&g_devModeCurrent, CDS_RESET);
	}
}

// FUNCTION: LEGORACERS 0x004a61c0
int VideoPlayer::Play(IronFlame0x944* p_unk0x04, LPCSTR p_filename, int p_abortableOnKey, int p_autoRewind)
{
	return Play(p_unk0x04, p_filename, (LegoBool32) p_abortableOnKey, (LegoBool32) p_autoRewind);
}

// FUNCTION: LEGORACERS 0x004a61e0
int VideoPlayer::End(IronFlame0x944* p_unk0x04)
{
	RevertDisplay();

	if (p_unk0x04->IsDisabled()) {
		p_unk0x04->ChangeWindowState(g_savedWindowMode);

		if (p_unk0x04->GetFlags() & IronFlame0x944::c_flagBit3) {
			ShowWindow(p_unk0x04->GetHwnd(), SW_MAXIMIZE);
		}
		else {
			ShowWindow(p_unk0x04->GetHwnd(), SW_RESTORE);
		}
	}
	else {
		ShowWindow(p_unk0x04->GetHwnd(), SW_MAXIMIZE);
	}

	return ShowCursor(TRUE);
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
	style &= ~(WS_CAPTION | WS_SYSMENU | WS_THICKFRAME);
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

// FUNCTION: LEGORACERS 0x004a65a0
void VideoPlayer::Graph::StopPlayback()
{
	if (!m_graph) {
		return;
	}

	IMediaControl* mediaControl;
	if (FAILED(m_graph->QueryInterface(IID_IMediaControl, (void**) &mediaControl))) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to get ActiveMovie media control");
	}

	HRESULT stopHr = mediaControl->Stop();
	mediaControl->Release();

	if (FAILED(stopHr)) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to stop ActiveMovie");
	}

	if (m_hasVideoWindow) {
		IVideoWindow* videoWindow;
		if (FAILED(m_graph->QueryInterface(IID_IVideoWindow, (void**) &videoWindow))) {
			Release();
			GOL_FATALERROR_MESSAGE("Unable to get ActiveMovie video window control");
		}
		videoWindow->put_FullScreenMode(0);
		videoWindow->Release();
	}

	if (m_hwnd && m_hasVideoWindow) {
		HBRUSH brush = CreateSolidBrush(0);
		SetWindowPos(m_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

		HDC hdc = GetDC(m_hwnd);
		RECT rect;
		GetClientRect(m_hwnd, &rect);
		FillRect(hdc, &rect, brush);
		ReleaseDC(m_hwnd, hdc);

		HDC screenDc = GetDC(NULL);
		rect.left = 0;
		rect.right = GetSystemMetrics(SM_CXSCREEN);
		rect.top = 0;
		rect.bottom = GetSystemMetrics(SM_CXSCREEN);
		FillRect(screenDc, &rect, brush);
		ReleaseDC(NULL, screenDc);
		DeleteObject(brush);
	}

	m_running = FALSE;
}

// FUNCTION: LEGORACERS 0x004a6720
void VideoPlayer::Graph::ResetPosition()
{
	if (!m_graph) {
		return;
	}

	IMediaPosition* mediaPosition;
	if (FAILED(m_graph->QueryInterface(IID_IMediaPosition, (void**) &mediaPosition))) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to get ActiveMovie media position control");
	}

	REFTIME duration;
	if (FAILED(mediaPosition->get_Duration(&duration))) {
		mediaPosition->Release();
		Release();
		GOL_FATALERROR_MESSAGE("Unable to get ActiveMovie media length");
	}

	REFTIME position;
	if (FAILED(mediaPosition->get_CurrentPosition(&position))) {
		mediaPosition->Release();
		Release();
		GOL_FATALERROR_MESSAGE("Unable to get ActiveMovie media current position");
	}

	mediaPosition->put_CurrentPosition(0.0);
	mediaPosition->Release();
}

// FUNCTION: LEGORACERS 0x004a67f0
void VideoPlayer::Graph::RunMessageLoop(LegoBool32 p_abortableOnKey)
{
	if (!m_graph || !m_running) {
		return;
	}

	MSG msg;
	while (m_running) {
		HANDLE pHandles = m_eventHandle;
		if (!pHandles) {
			WaitMessage();
		}
		else if (MsgWaitForMultipleObjects(1, &pHandles, FALSE, INFINITE, QS_ALLINPUT) == 0) {
			ProcessEvent();
			continue;
		}

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return;
			}
			if (p_abortableOnKey && msg.message == WM_KEYUP) {
				StopPlayback();
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a68c0
void VideoPlayer::Graph::ProcessEvent()
{
	if (!m_graph) {
		return;
	}

	IMediaEvent* mediaEvent;
	if (FAILED(m_graph->QueryInterface(IID_IMediaEvent, (void**) &mediaEvent))) {
		Release();
		GOL_FATALERROR_MESSAGE("Unable to initialize ActiveMovie media event interface");
	}

	long code;
	LONG_PTR lParam1;
	LONG_PTR lParam2;
	if (FAILED(mediaEvent->GetEvent(&code, &lParam1, &lParam2, 0))) {
		mediaEvent->Release();
		return;
	}

	switch (code) {
	case EC_COMPLETE:
		if (m_autoRewind) {
			ResetPosition();
			mediaEvent->Release();
			return;
		}
		break;
	case EC_USERABORT:
	case EC_ERRORABORT:
		break;
	default:
		mediaEvent->Release();
		return;
	}

	StopPlayback();
	mediaEvent->Release();
}

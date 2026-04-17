#include "ironflame0x944.h"

#include "../../GolDP/include/gol.h"
#include "gol.h"
#include "golerror.h"
#include "golfsutil.h"
#include "golstream.h"

#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

extern HINSTANCE g_hInstance;
extern HINSTANCE g_hPrevInstance;

DECOMP_SIZE_ASSERT(IronFlame0x944, 0x944)

// FUNCTION: LEGORACERS 0x004164d0
IronFlame0x944::IronFlame0x944()
{
	m_golLibrary = NULL;
	m_golExport = NULL;
	m_hWnd = 0;
	m_golBackendType = c_golBackendDP;
	m_unk0x92c = 0;
	m_unk0x934 = 0;
	m_unk0x93c = 0;
	m_unk0x940 = 0;
	m_unk0x930 = 0;
	m_unk0x938 = 1;
}

// FUNCTION: LEGORACERS 0x00416580
IronFlame0x944::~IronFlame0x944()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004165e0
void IronFlame0x944::Init(const LegoChar* p_windowName, const LegoChar* p_fileName)
{
	LegoChar buffer[64];

	if (m_unk0x04 & c_flagInitialized) {
		Destroy();
	}

	if (!g_hPrevInstance) {
		WNDCLASS wndClass;
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = AppWndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 4;
		wndClass.hInstance = g_hInstance;
		wndClass.hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(ICON_RACERS));

		if (!wndClass.hIcon) {
			::sprintf(buffer, "Unable to load app icon\nError = 0x%x", GetLastError());
			GOL_FATALERROR_MESSAGE(buffer);
		}

		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = "AolAppWinClass";

		if (!RegisterClass(&wndClass)) {
			::sprintf(buffer, "Unable to register app window class\nError = 0x%x", GetLastError());
			GOL_FATALERROR_MESSAGE(buffer);
		}

		g_hPrevInstance = g_hInstance;
	}

	g_unk0x4c73a0 = (undefined4*) &m_hashTable;

	if (p_fileName) {
		FUN_00416860(p_fileName);
	}

	m_unk0x93c = WS_POPUP | WS_CLIPCHILDREN;
	m_unk0x940 = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
	m_hWnd = CreateWindowEx(
		0,
		"AolAppWinClass",
		p_windowName,
		WS_POPUP | WS_CLIPCHILDREN,
		0,
		0,
		0,
		0,
		NULL,
		NULL,
		g_hInstance,
		NULL
	);

	if (!m_hWnd) {
		GOL_FATALERROR_MESSAGE("Unable to create application window");
	}

	LoadGolLibrary();
	InitInput();
	m_golDrawState->VTable0x08(m_hWnd);
	SetWindowLong(m_hWnd, 0, (LONG) this);
	ShowWindow(m_hWnd, SW_SHOW);
	m_unk0x820 = timeGetTime();
	m_unk0x92c = 0;
	m_unk0x04 |= c_flagInitialized;
}

// STUB: LEGORACERS 0x004167b0
void IronFlame0x944::VTable0x2c()
{
	// TODO
	STUB(0x4167b0);
}

// FUNCTION: LEGORACERS 0x004167e0
void IronFlame0x944::Destroy()
{
	m_golBackendType = c_golBackendDP;
	VTable0x2c();

	if (m_hWnd) {
		DestroyWindow(m_hWnd);
		m_hWnd = 0;
	}

	for (LegoU32 i = 0; i < sizeOfArray(m_fileSources); i++) {
		if (m_fileSources[i].GetStream()) {
			m_fileSources[i].Reset();
			m_files[i].Dispose();
		}
	}

	m_unk0x834.Shutdown();
	UnloadGolLibrary();

	m_unk0x92c = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00416860
void IronFlame0x944::FUN_00416860(const LegoChar* p_fileList)
{
	if (!p_fileList) {
		return;
	}

	LegoChar* buffer = new LegoChar[strlen(p_fileList) + 1];
	LegoChar* saved = buffer;

	if (buffer) {
		strcpy(buffer, p_fileList);

		while (buffer) {
			if (m_fileSourceCount >= sizeOfArray(m_fileSources)) {
				break;
			}

			LegoChar* newline = strchr(buffer, '\n');
			if (newline) {
				*newline = '\0';
			}

			if (!m_files[m_fileSourceCount].BufferedOpen(buffer, GolStream::c_modeRead, 0x8000)) {
				m_fileSources[m_fileSourceCount].FUN_0044d870(&m_files[m_fileSourceCount]);
				m_fileSourceCount++;
			}

			if (!newline) {
				break;
			}
			buffer = newline + 1;
		}

		if (m_fileSourceCount > 0) {
			g_fileSourceCount = m_fileSourceCount;
			g_fileSources = m_fileSources;
		}

		delete[] saved;
	}
}

// FUNCTION: LEGORACERS 0x00416960
void IronFlame0x944::LoadGolLibrary()
{
	LegoChar buffer[100];
	GolImport golImport;

	if (m_golBackendType & c_golBackendGlide) {
		m_golLibrary = LoadLibraryA("GolGlide.DLL");
	}
	else if (m_golBackendType & c_golBackendSoft) {
		m_golLibrary = LoadLibraryA("GolSoft.DLL");
	}
	else if (m_golBackendType & c_golBackendD3D) {
		m_golLibrary = LoadLibraryA("GolD3D.DLL");
	}
	else {
		m_golLibrary = LoadLibraryA("GolDP.DLL");
	}
	if (m_golLibrary == NULL) {
		::sprintf(buffer, "Unable to find a valid Gol DLL\nError Code = %d", GetLastError());
		GOL_FATALERROR_MESSAGE(buffer);
	}
	GolEntryCBFN* golEntry = (GolEntryCBFN*) GetProcAddress(m_golLibrary, "GolEntry");
	if (golEntry == NULL) {
		GOL_FATALERROR_MESSAGE("Invalid Gol DLL - cannot call entry procedure");
	}
	CreateGolImport(&golImport);
	golImport.m_fatalErrorMessage = GolFatalErrorMessage;
	m_golExport = golEntry(&golImport);
	m_golDrawState = m_golExport->VTable0x04();
}

// FUNCTION: LEGORACERS 0x00416a30
void IronFlame0x944::UnloadGolLibrary()
{
	m_golDrawState = NULL;

	if (m_golLibrary) {
		GolExitCBFN* golExit = (GolExitCBFN*) GetProcAddress(m_golLibrary, "GolExit");

		if (golExit == NULL) {
			GOL_FATALERROR_MESSAGE("Invalid Gol DLL - cannot call exit procedure");
		}

		golExit();
		FreeLibrary(m_golLibrary);
		m_golLibrary = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00416a90
void IronFlame0x944::InitInput()
{
	m_unk0x834.FUN_004503e0(g_hInstance, m_hWnd);
}

// STUB: LEGORACERS 0x00416ab0
void IronFlame0x944::VTable0x20()
{
	// TODO
	STUB(0x416ab0);
}

// STUB: LEGORACERS 0x00416ac0
void IronFlame0x944::VTable0x28()
{
	// TODO
	STUB(0x416ac0);
}

// STUB: LEGORACERS 0x00416b00
void IronFlame0x944::VTable0x24()
{
	// TODO
	STUB(0x416b00);
}

// STUB: LEGORACERS 0x00416cd0
void IronFlame0x944::VTable0x30()
{
	// TODO
	STUB(0x416cd0);
}

// STUB: LEGORACERS 0x00416ef0
void IronFlame0x944::VTable0x34()
{
	// TODO
	STUB(0x416ef0);
}

// STUB: LEGORACERS 0x00417330
LRESULT CALLBACK AppWndProc(HWND, UINT, WPARAM, LPARAM)
{
	// TODO
	STUB(0x417330);
	return 0;
}

// STUB: LEGORACERS 0x00417900
void IronFlame0x944::VTable0x00()
{
	// TODO
	STUB(0x417900);
}

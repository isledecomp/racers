#include "goldevicelist.h"

#include "goldrawstate.h"
#include "golerror.h"

#include <d3d.h>
#include <ddraw.h>
#include <string.h>

enum {
	IDC_DRIVERS_COMBOBOX = 1000,
	IDC_DEVICES_COMBOBOX = 1001,
};

#define TEMPLATE_SIZE 900

DECOMP_SIZE_ASSERT(GolDeviceList, 0x10)
DECOMP_SIZE_ASSERT(GolDeviceList::GolD3DDriverInfo, 0x2c)
DECOMP_SIZE_ASSERT(GolDeviceList::GolD3DDeviceInfo, 0x120)

#if defined(_MSC_VER) && _MSC_VER < 1400
typedef unsigned int uintptr_t;
#define GetWindowLongPtrA_COMPAT GetWindowLongA
#define GWLP_HINSTANCE_COMPAT GWL_HINSTANCE
#else
#define GetWindowLongPtrA_COMPAT GetWindowLongPtrA
#define GWLP_HINSTANCE_COMPAT GWLP_HINSTANCE
#endif

#define ALIGN(PTR, A) ((uintptr_t) (reinterpret_cast<char*>(PTR) + ((A) - 1)) & ~((A) - 1))

// GLOBAL: GOLDP 0x10063550
GolDeviceList* GolDeviceList::g_dialogDeviceList;

// GLOBAL: GOLDP 0x10063554
LegoChar g_unk0x10063554[] = "";

// FUNCTION: GOLDP 0x10013810
GolDeviceList::~GolDeviceList()
{
	Clear();
}

// FUNCTION: GOLDP 0x10013820
void GolDeviceList::DetectDevices()
{
	if (m_countDrivers > 0) {
		Clear();
	}

	LegoU32 countDrivers = 0;
	DirectDrawEnumerate(CountDirectDrawDriversCallback, &countDrivers);

	if (countDrivers >= 1) {
		m_drivers = new GolD3DDriverInfo[countDrivers];

		if (m_drivers == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_countDrivers = 0;
		DirectDrawEnumerate(EnumerateDirectDrawDriversCallback, this);
	}
}

// FUNCTION: GOLDP 0x10013890
void GolDeviceList::Clear()
{
	LegoU32 driverIndex;
	LegoU32 deviceIndex;
	GolD3DDriverInfo* driver;
	GolD3DDeviceInfo* device;

	if (m_drivers != NULL) {
		for (driverIndex = 0; driverIndex < m_countDrivers; driverIndex++) {
			driver = &m_drivers[driverIndex];

			if (driver->m_devices != NULL) {
				for (deviceIndex = 0; deviceIndex < driver->m_countDevices; deviceIndex++) {
					device = &driver->m_devices[deviceIndex];
					if (device->m_name != NULL) {
						delete[] device->m_name;
					}
					if (device->m_description != NULL) {
						delete[] device->m_description;
					}
				}
				delete[] driver->m_devices;
			}

			if (driver->m_description) {
				delete[] driver->m_description;
			}

			if (driver->m_name) {
				delete[] driver->m_name;
			}
		}

		delete[] m_drivers;
		m_drivers = NULL;
	}
}

#define STORE_DIALOG_ITEM_TEXT(WRITE_PTR, TEXT)                                                                        \
	do {                                                                                                               \
		int lenText = lstrlen(TEXT);                                                                                   \
		wchar_t* wideText = reinterpret_cast<wchar_t*>(*(WRITE_PTR));                                                  \
		int lenWideText = MultiByteToWideChar(0, 0, TEXT, lenText, wideText, lenText);                                 \
		wideText[lenWideText] = L'\0';                                                                                 \
		*(WRITE_PTR) += sizeof(wchar_t) * lenWideText;                                                                 \
		*(WRITE_PTR) += sizeof(wchar_t);                                                                               \
	} while (0)

#define STORE_DIALOG_ITEM(WRITE_PTR, STYLE, X, Y, CX, CY, ID, TYPE, TEXT)                                              \
	do {                                                                                                               \
		LPDLGITEMTEMPLATE itemTemplate = reinterpret_cast<LPDLGITEMTEMPLATE>(ALIGN(*(WRITE_PTR), 4));                  \
		itemTemplate->style = STYLE | WS_CHILD | WS_VISIBLE;                                                           \
		itemTemplate->dwExtendedStyle = 0;                                                                             \
		itemTemplate->x = X;                                                                                           \
		itemTemplate->y = Y;                                                                                           \
		itemTemplate->cx = CX;                                                                                         \
		itemTemplate->cy = CY;                                                                                         \
		itemTemplate->id = ID;                                                                                         \
		*(WRITE_PTR) = reinterpret_cast<LegoU8*>(itemTemplate + 1);                                                    \
		StoreDialogItemText(WRITE_PTR, TYPE);                                                                          \
		StoreDialogItemText(WRITE_PTR, TEXT);                                                                          \
		*(WRITE_PTR) += 2;                                                                                             \
	} while (0)

// FUNCTION: GOLDP 0x10013980
GolDeviceList::GolD3DDeviceInfo* GolDeviceList::SelectDevice(
	HWND p_hWnd,
	LegoU32 p_flags,
	const LegoChar* p_driverDescription,
	const LegoChar* p_deviceName
)
{
	GolDeviceList::GolD3DDeviceInfo* device;
	device = FindMatchingDevice(p_flags, p_driverDescription, p_deviceName);

	if (p_flags & GolDrawState::c_flagBit15) {
		HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(GetWindowLongPtrA_COMPAT(p_hWnd, GWLP_HINSTANCE_COMPAT));
		LPDLGTEMPLATE dialogTemplate = reinterpret_cast<LPDLGTEMPLATE>(new LegoChar[TEMPLATE_SIZE]);
		if (dialogTemplate != NULL) {
			::memset(dialogTemplate, 0, TEMPLATE_SIZE);
			dialogTemplate->style = WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | DS_CENTER | DS_SETFOREGROUND |
									DS_NOIDLEMSG | DS_MODALFRAME | DS_SETFONT | DS_3DLOOK;
			dialogTemplate->dwExtendedStyle = 0x0;
			dialogTemplate->cdit = 6;
			dialogTemplate->x = 0;
			dialogTemplate->y = 0;
			dialogTemplate->cx = 179;
			dialogTemplate->cy = 84;

			LegoU8* writePtr = reinterpret_cast<LegoU8*>(dialogTemplate + 1);
			// No menu
			*reinterpret_cast<wchar_t*>(writePtr) = L'\0';
			writePtr += 2;
			// Default window class
			*reinterpret_cast<wchar_t*>(writePtr) = L'\0';
			writePtr += 2;
			// Title
			STORE_DIALOG_ITEM_TEXT(&writePtr, "Select Direct3D Device");

			*reinterpret_cast<LegoU16*>(writePtr) = 8;
			writePtr += 2;

			STORE_DIALOG_ITEM_TEXT(&writePtr, "Arial");
			STORE_DIALOG_ITEM(&writePtr, WS_TABSTOP, 65, 65, 51, 14, IDOK, "BUTTON", "OK");
			STORE_DIALOG_ITEM(&writePtr, WS_TABSTOP, 123, 65, 51, 14, IDCANCEL, "BUTTON", "Cancel");
			STORE_DIALOG_ITEM(
				&writePtr,
				WS_VSCROLL | WS_TABSTOP | CBS_DROPDOWNLIST,
				36,
				5,
				138,
				45,
				IDC_DRIVERS_COMBOBOX,
				"COMBOBOX",
				g_unk0x10063554
			);
			STORE_DIALOG_ITEM(
				&writePtr,
				WS_VSCROLL | WS_TABSTOP | CBS_DROPDOWNLIST,
				36,
				24,
				138,
				45,
				IDC_DEVICES_COMBOBOX,
				"COMBOBOX",
				g_unk0x10063554
			);

			StoreDialogItem(&writePtr, SS_LEFT, 5, 5, 22, 13, -1, "STATIC", "Driver:");
			StoreDialogItem(&writePtr, SS_LEFT, 5, 24, 25, 13, -1, "STATIC", "Device:");
			int result = DialogBoxIndirectParam(
				hInstance,
				dialogTemplate,
				p_hWnd,
				SelectDeviceDlgProc,
				reinterpret_cast<LPARAM>(this)
			);

			delete[] dialogTemplate;

			if (result == IDOK) {
				device = &m_drivers[m_driverIndex].m_devices[m_deviceIndex];
			}
		}
	}

	return device;
}

// FUNCTION: GOLDP 0x10013ca0
GolDeviceList::GolD3DDeviceInfo* GolDeviceList::FindMatchingDevice(
	LegoU32 p_flags,
	const LegoChar* p_driverDescription,
	const LegoChar* p_deviceName
)
{
	GolD3DDriverInfo* driver;
	GolD3DDeviceInfo* device;

	if (p_flags & GolDrawState::c_flagBit14) {
		for (m_driverIndex = 0; m_driverIndex < m_countDrivers; m_driverIndex++) {
			driver = &m_drivers[m_driverIndex];
			if (::strcmp(driver->m_description, p_driverDescription) == 0) {
				for (m_deviceIndex = 0; m_deviceIndex < driver->m_countDevices; m_deviceIndex++) {
					device = &driver->m_devices[m_deviceIndex];
					if (::strcmp(device->m_name, p_deviceName) == 0) {
						return device;
					}
				}
			}
		}

		return NULL;
	}
	else if (
		(p_flags & GolDrawState::c_flagBit9) && !(p_flags & (GolDrawState::c_flagBit13 | GolDrawState::c_flagBit11))
	) {
		for (m_driverIndex = 0; m_driverIndex < m_countDrivers; m_driverIndex++) {
			driver = &m_drivers[m_driverIndex];
			if (!driver->m_unk0x00 && driver->m_accelerated) {
				for (m_deviceIndex = 0; m_deviceIndex < driver->m_countDevices; m_deviceIndex++) {
					device = &driver->m_devices[m_deviceIndex];
					if (device->m_deviceDesc.dcmColorModel == D3DCOLOR_RGB &&
						(device->m_deviceDesc.dwFlags & D3DDD_TRICAPS) &&
						(device->m_deviceDesc.dpcTriCaps.dwTextureAddressCaps & D3DPTADDRESSCAPS_WRAP) &&
						device->m_hwAccelerated) {
						return device;
					}
				}
			}
		}

		for (m_driverIndex = 0; m_driverIndex < m_countDrivers; m_driverIndex++) {
			driver = &m_drivers[m_driverIndex];
			if (driver->m_accelerated) {
				for (m_deviceIndex = 0; m_deviceIndex < driver->m_countDevices; m_deviceIndex++) {
					device = &driver->m_devices[m_deviceIndex];
					if (device->m_deviceDesc.dcmColorModel == D3DCOLOR_RGB &&
						(device->m_deviceDesc.dwFlags & D3DDD_TRICAPS) &&
						(device->m_deviceDesc.dpcTriCaps.dwTextureAddressCaps & D3DPTADDRESSCAPS_WRAP) &&
						device->m_hwAccelerated) {
						return device;
					}
				}
			}
		}
	}
	else if (!(p_flags & GolDrawState::c_flagBit11)) {
		for (m_driverIndex = 0; m_driverIndex < m_countDrivers; m_driverIndex++) {
			driver = &m_drivers[m_driverIndex];
			if (driver->m_unk0x00 && driver->m_accelerated) {
				for (m_deviceIndex = 0; m_deviceIndex < driver->m_countDevices; m_deviceIndex++) {
					device = &driver->m_devices[m_deviceIndex];
					if (device->m_deviceDesc.dcmColorModel == D3DCOLOR_RGB &&
						(device->m_deviceDesc.dwFlags & D3DDD_TRICAPS) &&
						(device->m_deviceDesc.dpcTriCaps.dwTextureAddressCaps & D3DPTADDRESSCAPS_WRAP) &&
						device->m_hwAccelerated) {
						return device;
					}
				}
			}
		}
	}
	else {
		for (m_driverIndex = 0; m_driverIndex < m_countDrivers; m_driverIndex++) {
			driver = &m_drivers[m_driverIndex];
			if (driver->m_unk0x00) {
				for (m_deviceIndex = 0; m_deviceIndex < driver->m_countDevices; m_deviceIndex++) {
					device = &driver->m_devices[m_deviceIndex];
					if (device->m_deviceDesc.dcmColorModel == D3DCOLOR_RGB &&
						(device->m_deviceDesc.dwFlags & D3DDD_TRICAPS) &&
						(device->m_deviceDesc.dpcTriCaps.dwTextureAddressCaps & D3DPTADDRESSCAPS_WRAP) &&
						!device->m_hwAccelerated) {
						return device;
					}
				}
			}
		}
	}

	for (m_driverIndex = 0; m_driverIndex < m_countDrivers; m_driverIndex++) {
		driver = &m_drivers[m_driverIndex];
		for (m_deviceIndex = 0; m_deviceIndex < driver->m_countDevices; m_deviceIndex++) {
			device = &driver->m_devices[m_deviceIndex];
			if (device->m_deviceDesc.dcmColorModel == D3DCOLOR_RGB && (device->m_deviceDesc.dwFlags & D3DDD_TRICAPS) &&
				(device->m_deviceDesc.dpcTriCaps.dwTextureAddressCaps & D3DPTADDRESSCAPS_WRAP)) {
				return device;
			}
		}
	}

	m_driverIndex = 0;
	m_deviceIndex = 0;
	return NULL;
}

// FUNCTION: GOLDP 0x10013ff0
void GolDeviceList::UpdateDialog(HWND p_hWnd)
{
	SendDlgItemMessage(p_hWnd, IDC_DRIVERS_COMBOBOX, CB_RESETCONTENT, 0, 0);
	SendDlgItemMessage(p_hWnd, IDC_DEVICES_COMBOBOX, CB_RESETCONTENT, 0, 0);

	for (LegoU32 driverIndex = 0; driverIndex < m_countDrivers; driverIndex++) {
		LegoU32 comboBoxIndex = SendDlgItemMessage(
			p_hWnd,
			IDC_DRIVERS_COMBOBOX,
			CB_ADDSTRING,
			0,
			reinterpret_cast<LPARAM>(m_drivers[driverIndex].m_name)
		);

		SendDlgItemMessage(
			p_hWnd,
			IDC_DRIVERS_COMBOBOX,
			CB_SETITEMDATA,
			comboBoxIndex,
			reinterpret_cast<LPARAM>(&m_drivers[driverIndex])
		);

		if (driverIndex == m_driverIndex) {
			SendDlgItemMessage(p_hWnd, IDC_DRIVERS_COMBOBOX, CB_SETCURSEL, comboBoxIndex, 0);
		}
	}

	GolD3DDeviceInfo* device = m_drivers[m_driverIndex].m_devices;
	for (LegoU32 deviceIndex = 0; deviceIndex < m_drivers[m_driverIndex].m_countDevices; deviceIndex++, device++) {
		LegoU32 comboBoxIndex = SendDlgItemMessage(
			p_hWnd,
			IDC_DEVICES_COMBOBOX,
			CB_ADDSTRING,
			0,
			reinterpret_cast<LPARAM>(device->m_description)
		);

		if (deviceIndex == m_driverIndex) {
			SendDlgItemMessage(p_hWnd, IDC_DEVICES_COMBOBOX, CB_SETCURSEL, comboBoxIndex, 0);
		}
	}
}

// FUNCTION: GOLDP 0x10014110
BOOL GolDeviceList::CountDirectDrawDriversCallback(GUID* p_guid, LPSTR p_name, LPSTR p_description, LPVOID p_context)
{
	*static_cast<LegoU32*>(p_context) += 1;
	return TRUE;
}

// FUNCTION: GOLDP 0x10014130
BOOL GolDeviceList::EnumerateDirectDrawDriversCallback(
	GUID* p_guid,
	LPSTR p_name,
	LPSTR p_description,
	LPVOID p_context
)
{
	GolD3DDriverInfo* const driver =
		&static_cast<GolDeviceList*>(p_context)->m_drivers[static_cast<GolDeviceList*>(p_context)->m_countDrivers++];

	if (p_guid == NULL) {
		driver->m_unk0x00 = TRUE;
		driver->m_unk0x08 = FALSE;
		::memset(&driver->m_guid, 0, sizeof(driver->m_guid));
	}
	else {
		driver->m_unk0x00 = FALSE;
		driver->m_unk0x08 = TRUE;
		::memcpy(&driver->m_guid, p_guid, sizeof(*p_guid));
	}

	driver->m_description = new LegoChar[strlen(p_description) + 1];

	if (driver->m_description == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(driver->m_description, p_description);
	driver->m_name = new LegoChar[strlen(p_name) + 1];

	if (driver->m_name == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(driver->m_name, p_name);

	LPDIRECTDRAW ddraw;
	if (DirectDrawCreate(p_guid, &ddraw, NULL) == DD_OK) {
		DDCAPS hwCaps;
		::memset(&hwCaps, 0, sizeof(hwCaps));
		hwCaps.dwSize = sizeof(hwCaps);

		DDCAPS helCaps;
		::memset(&helCaps, 0, sizeof(helCaps));
		helCaps.dwSize = sizeof(hwCaps);

		if (ddraw->GetCaps(&hwCaps, &helCaps) != DD_OK) {
			ddraw->Release();
			return TRUE;
		}

		if (hwCaps.dwCaps & DDCAPS_3D) {
			driver->m_accelerated = TRUE;
		}
		else {
			driver->m_accelerated = FALSE;
		}

		LPDIRECT3D3 d3d;
		if (ddraw->QueryInterface(IID_IDirect3D3, reinterpret_cast<LPVOID*>(&d3d)) == DD_OK) {
			LegoU32 countDevices = 0;

			if (d3d->EnumDevices(CountDirect3DDevicesCallback, &countDevices) == D3D_OK) {
				driver->m_devices = new GolD3DDeviceInfo[countDevices];
				if (driver->m_devices == NULL) {
					d3d->Release();
					ddraw->Release();
					GOL_FATALERROR(c_golErrorOutOfMemory);
				}
				driver->m_countDevices = 0;
				d3d->EnumDevices(EnumerateDirect3DDevicesCallback, driver);
			}

			d3d->Release();
		}

		ddraw->Release();
	}

	return TRUE;
}

// FUNCTION: GOLDP 0x10014370
HRESULT GolDeviceList::CountDirect3DDevicesCallback(
	GUID* p_guid,
	LPSTR p_description,
	LPSTR p_name,
	LPD3DDEVICEDESC p_halDesc,
	LPD3DDEVICEDESC p_helDesc,
	LPVOID p_context
)
{
	*static_cast<LegoU32*>(p_context) += 1;
	return TRUE;
}

// FUNCTION: GOLDP 0x10014390
HRESULT GolDeviceList::EnumerateDirect3DDevicesCallback(
	GUID* p_guid,
	LPSTR p_description,
	LPSTR p_name,
	LPD3DDEVICEDESC p_halDesc,
	LPD3DDEVICEDESC p_helDesc,
	LPVOID p_context
)
{
	GolD3DDriverInfo* const driver = static_cast<GolD3DDriverInfo*>(p_context);
	GolD3DDeviceInfo* const device = &driver->m_devices[driver->m_countDevices++];
	device->m_driver = driver;
	device->m_name = new LegoChar[strlen(p_name) + 1];

	if (device->m_name == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(device->m_name, p_name);
	device->m_description = new LegoChar[strlen(p_description) + 1];

	if (device->m_description == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(device->m_description, p_description);
	if (p_guid != NULL) {
		device->m_validGuid = TRUE;
		device->m_guid = *p_guid;
	}
	else {
		device->m_validGuid = FALSE;
	}
	if (p_halDesc->dwFlags != 0) {
		device->m_deviceDesc = *p_halDesc;
		device->m_hwAccelerated = TRUE;
	}
	else {
		device->m_deviceDesc = *p_helDesc;
		device->m_hwAccelerated = FALSE;
	}

	return TRUE;
}

void GolDeviceList::StoreDialogWord(LegoU8** p_ptrStorage, LegoU16 p_word)
{
	LegoU16* ptrWord = reinterpret_cast<LegoU16*>(*p_ptrStorage);
	*ptrWord = p_word;
	*p_ptrStorage = reinterpret_cast<LegoU8*>(ptrWord + 1);
}

// FUNCTION: GOLDP 0x100144b0
void GolDeviceList::StoreDialogItemText(LegoU8** p_ptrStorage, const char* p_text)
{
	int lenText = lstrlen(p_text);
	wchar_t* wideText = reinterpret_cast<wchar_t*>(*p_ptrStorage);
	int lenWideText = MultiByteToWideChar(0, 0, p_text, lenText, wideText, lenText);
	wideText[lenWideText] = L'\0';
	*p_ptrStorage += sizeof(wchar_t) * lenWideText;
	*p_ptrStorage += sizeof(wchar_t);
}

// FUNCTION: GOLDP 0x100144f0
void GolDeviceList::StoreDialogItem(
	LegoU8** p_ptrStorage,
	LegoU32 p_style,
	LegoS16 p_x,
	LegoS16 p_y,
	LegoS16 p_cx,
	LegoS16 p_cy,
	LegoU16 p_id,
	const char* p_type,
	const char* p_text
)
{
	LPDLGITEMTEMPLATE itemTemplate = reinterpret_cast<LPDLGITEMTEMPLATE>(ALIGN(*p_ptrStorage, 4));
	itemTemplate->style = p_style | WS_CHILD | WS_VISIBLE;
	itemTemplate->dwExtendedStyle = 0;
	itemTemplate->x = p_x;
	itemTemplate->y = p_y;
	itemTemplate->cx = p_cx;
	itemTemplate->cy = p_cy;
	itemTemplate->id = p_id;
	*p_ptrStorage = reinterpret_cast<LegoU8*>(itemTemplate + 1);

	int lenText = lstrlen(p_type);
	wchar_t* wideText = reinterpret_cast<wchar_t*>(*p_ptrStorage);
	int lenWideText = MultiByteToWideChar(0, 0, p_type, lenText, wideText, lenText);
	wideText[lenWideText] = L'\0';
	*p_ptrStorage += sizeof(wchar_t) * (lenWideText + 1);

	lenText = lstrlen(p_text);
	wideText = reinterpret_cast<wchar_t*>(*p_ptrStorage);
	lenWideText = MultiByteToWideChar(0, 0, p_text, lenText, wideText, lenText);
	wideText[lenWideText] = L'\0';
	*p_ptrStorage += sizeof(wchar_t) * (lenWideText + 1);
	*p_ptrStorage += sizeof(wchar_t) * (1);
}

// FUNCTION: GOLDP 0x100145a0
INT_PTR_COMPAT GolDeviceList::SelectDeviceDlgProc(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam)
{
	if (p_uMsg == WM_INITDIALOG) {
		g_dialogDeviceList = reinterpret_cast<GolDeviceList*>(p_lParam);
		g_dialogDeviceList->UpdateDialog(p_hWnd);
		return 1;
	}

	if (g_dialogDeviceList != NULL) {
		if (p_uMsg == WM_COMMAND) {
			if (LOWORD(p_wParam) == IDOK) {
				EndDialog(p_hWnd, IDOK);
				return 1;
			}

			if (LOWORD(p_wParam) == IDCANCEL) {
				EndDialog(p_hWnd, IDCANCEL);
				return 1;
			}

			LegoS16 notificationCode = HIWORD(p_wParam);
			if (notificationCode == CBN_SELENDOK) {
				int index = SendMessage(reinterpret_cast<HWND>(p_lParam), CB_GETCURSEL, 0, 0);

				if (index == -1) {
					return 1;
				}

				switch (LOWORD(p_wParam)) {
				case IDC_DRIVERS_COMBOBOX:
					g_dialogDeviceList->m_driverIndex = index;
					break;
				case IDC_DEVICES_COMBOBOX:
					g_dialogDeviceList->m_deviceIndex = index;
					break;
				}

				g_dialogDeviceList->UpdateDialog(p_hWnd);
				return 1;
			}
		}
	}

	return 0;
}

// FUNCTION: GOLDP 0x10026100
GolDeviceList::GolDeviceList()
{
	m_countDrivers = 0;
	m_drivers = NULL;
}

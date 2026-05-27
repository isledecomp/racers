#ifndef GOL_DEVICELIST_H
#define GOL_DEVICELIST_H

#include "types.h"

#include <d3d.h>
#include <windows.h>

#if defined(_MSC_VER) && _MSC_VER < 1300
#define INT_PTR_COMPAT int
#else
#define INT_PTR_COMPAT INT_PTR
#endif

// SIZE 0x10
class GolDeviceList {
public:
	struct GolD3DDeviceInfo;
	struct GolD3DDriverInfo;

	struct GolD3DDeviceInfo {
		GolD3DDriverInfo* m_driver; // 0x00
		BOOL m_validGuid;           // 0x04
		BOOL m_hwAccelerated;       // 0x08
		GUID m_guid;                // 0x0c
		char* m_name;               // 0x1c
		char* m_description;        // 0x20
		D3DDEVICEDESC m_deviceDesc; // 0x24
	};

	struct GolD3DDriverInfo {
		LegoBool32 m_unk0x00;        // 0x00
		LegoBool32 m_accelerated;    // 0x04
		LegoBool32 m_unk0x08;        // 0x08
		GUID m_guid;                 // 0x0c
		LegoChar* m_description;     // 0x1c
		LegoChar* m_name;            // 0x20
		LegoU32 m_countDevices;      // 0x24
		GolD3DDeviceInfo* m_devices; // 0x28

		const GolD3DDeviceInfo* GetDevices() const { return m_devices; }
	};

	GolDeviceList();
	~GolDeviceList();

	void Clear();
	GolD3DDeviceInfo* SelectDevice(
		HWND p_hWnd,
		LegoU32 p_flags,
		const LegoChar* p_driverDescription,
		const LegoChar* p_deviceName
	);
	void DetectDevices();
	void UpdateDialog(HWND p_hWnd);
	GolD3DDeviceInfo* FindMatchingDevice(
		LegoU32 p_flags,
		const LegoChar* p_driverDescription,
		const LegoChar* p_deviceName
	);

private:
	static BOOL CALLBACK
	CountDirectDrawDriversCallback(GUID* p_guid, LPSTR p_name, LPSTR p_description, LPVOID Context);
	static BOOL CALLBACK
	EnumerateDirectDrawDriversCallback(GUID* p_guid, LPSTR p_name, LPSTR p_description, LPVOID Context);
	static HRESULT CALLBACK CountDirect3DDevicesCallback(
		GUID* p_guid,
		LPSTR p_description,
		LPSTR p_name,
		LPD3DDEVICEDESC p_halDesc,
		LPD3DDEVICEDESC p_helDesc,
		LPVOID p_context
	);
	static HRESULT CALLBACK EnumerateDirect3DDevicesCallback(
		GUID* p_guid,
		LPSTR p_description,
		LPSTR p_name,
		LPD3DDEVICEDESC p_halDesc,
		LPD3DDEVICEDESC p_helDesc,
		LPVOID p_context
	);
	static void StoreDialogWord(LegoU8** p_ptrStorage, LegoU16 p_word);
	static void StoreDialogItemText(LegoU8** p_ptrStorage, const char* p_text);
	static void StoreDialogItem(
		LegoU8** p_ptrStorage,
		LegoU32 p_style,
		LegoS16 p_x,
		LegoS16 p_y,
		LegoS16 p_cx,
		LegoS16 p_cy,
		LegoU16 p_id,
		const char* p_type,
		const char* p_text
	);
	static INT_PTR_COMPAT CALLBACK SelectDeviceDlgProc(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam);

public:
	LegoU32 m_countDrivers;
	GolD3DDriverInfo* m_drivers;
	LegoU32 m_driverIndex;
	LegoU32 m_deviceIndex;

	static GolDeviceList* g_dialogDeviceList;
};

#endif // GOL_DEVICELIST_H

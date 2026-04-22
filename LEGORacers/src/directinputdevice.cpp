#include "directinputdevice.h"

#include "golerror.h"

DECOMP_SIZE_ASSERT(DirectInputDevice, 0xcc)

// FUNCTION: LEGORACERS 0x0044f990
DirectInputDevice::DirectInputDevice()
{
	Init();
}

// FUNCTION: LEGORACERS 0x0044fa00
DirectInputDevice::~DirectInputDevice()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0044fa50
void DirectInputDevice::Init()
{
	m_unk0x9c = 0;
	m_device = NULL;
	m_hWnd = NULL;
	m_effect = NULL;
	m_unk0xac = 0;
	m_nameIndices = NULL;
	m_unk0xc8 = NULL;
	m_cooperativeLevel = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
	::memset(&m_deviceGuid, 0, sizeof(m_deviceGuid));
	InputDevice::Init();
}

// FUNCTION: LEGORACERS 0x0044faa0
void DirectInputDevice::FUN_0044faa0()
{
	DIDEVICEINSTANCE deviceInfo;
	deviceInfo.dwSize = sizeof(deviceInfo);
	FUN_00450170(m_device->GetDeviceInfo(&deviceInfo));
	FUN_0044bad0(deviceInfo.tszProductName);
	m_devType = deviceInfo.dwDevType & 0xff;
	m_devSubType = (deviceInfo.dwDevType >> 8) & 0xff;

	DIDEVCAPS caps;
	caps.dwSize = sizeof(caps);
	FUN_00450170(m_device->GetCapabilities(&caps));
	m_buttonCount = caps.dwButtons;
	m_axisCount = caps.dwAxes;
}

// FUNCTION: LEGORACERS 0x0044fb30
void DirectInputDevice::FUN_0044fb30()
{
	LegoS32 count = VTable0x1c() + 4 * VTable0x20();

	m_unk0x5c = 4 * count;
	m_stringBuffer = new wchar_t[m_unk0x5c];

	if (m_stringBuffer == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_stringBuffer, 0, m_unk0x5c * sizeof(wchar_t));

	m_nameIndices = new LegoU16[VTable0x1c()];

	if (m_nameIndices == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_nameIndices, 0, sizeof(LegoU16) * VTable0x1c());

	if (VTable0x20() != 0) {
		m_unk0xc8 = new undefined2[VTable0x20()];

		if (m_unk0xc8 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		::memset(m_unk0xc8, 0, sizeof(undefined2) * VTable0x20());
	}
}

// FUNCTION: LEGORACERS 0x0044fc30
LegoBool32 DirectInputDevice::CreateDevice(CreateDirectInputDeviceParams* p_params)
{
	Destroy();
	m_hWnd = p_params->m_hWnd;
	m_unk0x90 = p_params->m_unk0x10;
	m_opalVault = p_params->m_opalVault;
	m_deviceGuid = *p_params->m_guid;

	LPDIRECTINPUTDEVICE device;
	HRESULT hResult = p_params->m_dinput->CreateDevice(m_deviceGuid, &device, NULL);

	if (hResult != DI_OK) {
		return FALSE;
	}

	hResult = device->QueryInterface(IID_IDirectInputDevice2A, reinterpret_cast<LPVOID*>(&m_device));
	device->Release();

	if (hResult != DI_OK) {
		return FALSE;
	}

	hResult = m_device->SetDataFormat(p_params->m_dataFormat);

	if (hResult != DI_OK) {
		m_device->Release();
		return FALSE;
	}

	FUN_0044fef0();
	FUN_0044faa0();
	FUN_0044fb30();

	m_unk0x18 = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044fd10
LegoBool32 DirectInputDevice::Destroy()
{
	if (!m_unk0x18) {
		return TRUE;
	}

	if (m_stringBuffer != NULL) {
		delete[] m_stringBuffer;
	}

	if (m_nameIndices != NULL) {
		delete[] m_nameIndices;
	}

	if (m_unk0xc8 != NULL) {
		delete[] m_unk0xc8;
	}

	if (m_device != NULL) {
		if (VTable0x18()) {
			VTable0x54();
		}

		FUN_00450170(m_device->Release());
	}

	return InputDevice::Destroy();
}

// FUNCTION: LEGORACERS 0x0044fda0
undefined4 DirectInputDevice::FUN_0044fda0(const GUID& p_guid) const
{
	if (p_guid == GUID_XAxis) {
		return c_axisX;
	}
	else if (p_guid == GUID_YAxis) {
		return c_axisY;
	}
	else if (p_guid == GUID_ZAxis) {
		return c_axisZ;
	}
	else if (p_guid == GUID_RxAxis) {
		return c_axisRx;
	}
	else if (p_guid == GUID_RyAxis) {
		return c_axisRy;
	}
	else if (p_guid == GUID_RzAxis) {
		return c_axisRz;
	}
	else if (p_guid == GUID_Slider) {
		return c_axisSlider;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044fe70
undefined4 DirectInputDevice::VTable0x50()
{
	if (!m_unk0x18) {
		return 0;
	}

	if (m_device->Acquire() == DI_OK) {
		FUN_0044b9f0();
		InputDevice::VTable0x50();
	}

	return VTable0x18();
}

// FUNCTION: LEGORACERS 0x0044feb0
undefined4 DirectInputDevice::VTable0x54()
{
	if (!m_unk0x18) {
		return 0;
	}

	if (VTable0x18() == 0) {
		return 1;
	}

	if (m_device->Unacquire() == DI_OK) {
		InputDevice::VTable0x54();
	}

	return VTable0x18();
}

// FUNCTION: LEGORACERS 0x0044fef0
LegoBool32 DirectInputDevice::FUN_0044fef0()
{
	undefined4 result = VTable0x18();
	if (!m_unk0x18) {
		return FALSE;
	}

	if (result) {
		VTable0x54();
	}

	FUN_00450170(m_device->SetCooperativeLevel(m_hWnd, m_cooperativeLevel));

	if (result) {
		VTable0x50();
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044ff50
void DirectInputDevice::FUN_0044ff50(undefined4 p_arg)
{
	undefined4 r = VTable0x18();
	if (r) {
		VTable0x54();
	}

	DIPROPDWORD prop;
	prop.dwData = p_arg;
	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	FUN_00450170(m_device->SetProperty(DIPROP_BUFFERSIZE, &prop.diph));

	if (r) {
		VTable0x50();
	}
}

// FUNCTION: LEGORACERS 0x0044ffc0
const wchar_t* DirectInputDevice::VTable0x24(undefined4 p_arg)
{
	switch (GetKeySource(p_arg)) {
	case c_sourceKeyboard:
	case c_sourceMouse:
	case c_sourceJoystick1:
		return &m_stringBuffer[m_nameIndices[LOWORD(p_arg)]];
	case c_sourceJoystick2:
		return &m_stringBuffer[m_unk0xc8[p_arg & 0xfffe]];
	default:
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x00450030
undefined4 DirectInputDevice::VTable0x14(undefined4 p_arg)
{
	undefined4 result = FUN_00450170(m_device->Poll());

	if (result != 0) {
		return result;
	}

	DIDEVICEOBJECTDATA deviceData;
	DWORD count = 1;
	result = FUN_00450170(m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &deviceData, &count, 0));

	if (result == 0) {
		while (result == 0 && count != 0) {
			VTable0x68(deviceData);

			if (count == 0) {
				break;
			}

			count = 1;
			result = FUN_00450170(m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &deviceData, &count, 0));

			if (result != 0) {
				return result;
			}
		}

		InputDevice::VTable0x14(p_arg);
		return 0;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0044f2c0 FOLDED
LegoFloat DirectInputDevice::VTable0x2c(undefined4)
{
	return 0.0f;
}

// FUNCTION: LEGORACERS 0x004500f0
undefined4 DirectInputDevice::VTable0x38()
{
	if (m_cooperativeLevel & DISCL_BACKGROUND) {
		return TRUE;
	}

	m_cooperativeLevel &= ~DISCL_FOREGROUND;
	m_cooperativeLevel |= DISCL_BACKGROUND;
	return FUN_0044fef0();
}

// FUNCTION: LEGORACERS 0x00450110
undefined4 DirectInputDevice::VTable0x3c()
{
	if (m_cooperativeLevel & DISCL_FOREGROUND) {
		return TRUE;
	}

	m_cooperativeLevel &= ~DISCL_BACKGROUND;
	m_cooperativeLevel |= DISCL_FOREGROUND;
	return FUN_0044fef0();
}

// FUNCTION: LEGORACERS 0x00450130
undefined4 DirectInputDevice::VTable0x40()
{
	if (m_cooperativeLevel & DISCL_EXCLUSIVE) {
		return TRUE;
	}

	m_cooperativeLevel &= ~DISCL_NONEXCLUSIVE;
	m_cooperativeLevel |= DISCL_EXCLUSIVE;
	return FUN_0044fef0();
}

// FUNCTION: LEGORACERS 0x00450150
undefined4 DirectInputDevice::VTable0x44()
{
	if (m_cooperativeLevel & DISCL_NONEXCLUSIVE) {
		return TRUE;
	}

	m_cooperativeLevel &= ~DISCL_EXCLUSIVE;
	m_cooperativeLevel |= DISCL_NONEXCLUSIVE;
	return FUN_0044fef0();
}

// FUNCTION: LEGORACERS 0x00450170
undefined4 DirectInputDevice::FUN_00450170(HRESULT p_hResult)
{
	if (SUCCEEDED(p_hResult)) {
		return 0;
	}

	switch (p_hResult) {
	case DIERR_NOTACQUIRED:
		return VTable0x18() ? 1 : 2;
	case DIERR_INPUTLOST:
		if (VTable0x18()) {
			VTable0x50();
		}
		return 1;
	default:
		return 0;
	}
}

// FUNCTION: LEGORACERS 0x004501d0
LegoBool32 DirectInputDevice::VTable0x58()
{
	if (!m_unk0x28) {
		return TRUE;
	}

	LONG direction[2] = {0, 0};
	DWORD axes[2] = {DIJOFS_X, DIJOFS_Y};

	VTable0x40();

	DIPERIODIC periodicParams;
	DIEFFECT effectParams;

	effectParams.dwDuration = INFINITE;
	effectParams.dwTriggerButton = DIEB_NOTRIGGER;
	effectParams.rgdwAxes = axes;

	periodicParams.dwMagnitude = 3000;
	periodicParams.lOffset = 0;
	periodicParams.dwPhase = 0;
	periodicParams.dwPeriod = 50000;

	effectParams.dwSize = sizeof(effectParams);
	effectParams.dwFlags = DIEFF_POLAR | DIEFF_OBJECTOFFSETS;
	effectParams.dwSamplePeriod = 0;
	effectParams.dwGain = 10000;
	effectParams.dwTriggerRepeatInterval = 0;
	effectParams.cAxes = sizeOfArray(axes);
	effectParams.rglDirection = direction;
	effectParams.lpEnvelope = NULL;
	effectParams.cbTypeSpecificParams = sizeof(periodicParams);
	effectParams.lpvTypeSpecificParams = &periodicParams;

	HRESULT hr = m_device->CreateEffect(GUID_Sine, &effectParams, &m_effect, NULL);
	if (FAILED(hr)) {
		m_effect = NULL;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004502b0
LegoS32 DirectInputDevice::VTable0x5c()
{
	if (m_unk0x28 && m_effect != NULL) {
		m_effect->Start(1, 0);
		return 0;
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x004502e0
LegoBool32 DirectInputDevice::VTable0x60()
{
	if (m_unk0x28 && m_effect != NULL) {
		m_effect->Stop();
		return 0;
	}

	return 1;
}

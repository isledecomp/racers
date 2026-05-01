#include "input/directinputdevice.h"

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
	m_buttonNameIndices = NULL;
	m_axisNameIndices = NULL;
	m_cooperativeLevel = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
	::memset(&m_deviceGuid, 0, sizeof(m_deviceGuid));
	InputDevice::Init();
}

// FUNCTION: LEGORACERS 0x0044faa0
void DirectInputDevice::ReadDeviceInfo()
{
	DIDEVICEINSTANCE deviceInfo;
	deviceInfo.dwSize = sizeof(deviceInfo);
	TranslateDirectInputResult(m_device->GetDeviceInfo(&deviceInfo));
	SetDeviceName(deviceInfo.tszProductName);
	m_deviceType = deviceInfo.dwDevType & 0xff;
	m_deviceSubType = (deviceInfo.dwDevType >> 8) & 0xff;

	DIDEVCAPS caps;
	caps.dwSize = sizeof(caps);
	TranslateDirectInputResult(m_device->GetCapabilities(&caps));
	m_buttonCount = caps.dwButtons;
	m_axisCount = caps.dwAxes;
}

// FUNCTION: LEGORACERS 0x0044fb30
void DirectInputDevice::AllocateControlNameBuffers()
{
	LegoS32 count = GetButtonCount() + 4 * GetAxisCount();

	m_stringBufferLength = 4 * count;
	m_stringBuffer = new wchar_t[m_stringBufferLength];

	if (m_stringBuffer == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_stringBuffer, 0, m_stringBufferLength * sizeof(wchar_t));

	m_buttonNameIndices = new LegoU16[GetButtonCount()];

	if (m_buttonNameIndices == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_buttonNameIndices, 0, sizeof(LegoU16) * GetButtonCount());

	if (GetAxisCount() != 0) {
		m_axisNameIndices = new undefined2[GetAxisCount()];

		if (m_axisNameIndices == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		::memset(m_axisNameIndices, 0, sizeof(undefined2) * GetAxisCount());
	}
}

// FUNCTION: LEGORACERS 0x0044fc30
LegoBool32 DirectInputDevice::CreateDevice(CreateDirectInputDeviceParams* p_params)
{
	Destroy();
	m_hWnd = p_params->m_hWnd;
	m_deviceId = p_params->m_deviceId;
	m_inputManager = p_params->m_inputManager;
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

	ApplyCooperativeLevel();
	ReadDeviceInfo();
	AllocateControlNameBuffers();

	m_created = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044fd10
LegoBool32 DirectInputDevice::Destroy()
{
	if (!m_created) {
		return TRUE;
	}

	if (m_stringBuffer != NULL) {
		delete[] m_stringBuffer;
	}

	if (m_buttonNameIndices != NULL) {
		delete[] m_buttonNameIndices;
	}

	if (m_axisNameIndices != NULL) {
		delete[] m_axisNameIndices;
	}

	if (m_device != NULL) {
		if (IsAcquired()) {
			Unacquire();
		}

		TranslateDirectInputResult(m_device->Release());
	}

	return InputDevice::Destroy();
}

// FUNCTION: LEGORACERS 0x0044fda0
undefined4 DirectInputDevice::GetAxisMask(const GUID& p_guid) const
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
undefined4 DirectInputDevice::Acquire()
{
	if (!m_created) {
		return 0;
	}

	if (m_device->Acquire() == DI_OK) {
		ReleasePressedButtons();
		InputDevice::Acquire();
	}

	return IsAcquired();
}

// FUNCTION: LEGORACERS 0x0044feb0
undefined4 DirectInputDevice::Unacquire()
{
	if (!m_created) {
		return 0;
	}

	if (IsAcquired() == 0) {
		return 1;
	}

	if (m_device->Unacquire() == DI_OK) {
		InputDevice::Unacquire();
	}

	return IsAcquired();
}

// FUNCTION: LEGORACERS 0x0044fef0
LegoBool32 DirectInputDevice::ApplyCooperativeLevel()
{
	undefined4 result = IsAcquired();
	if (!m_created) {
		return FALSE;
	}

	if (result) {
		Unacquire();
	}

	TranslateDirectInputResult(m_device->SetCooperativeLevel(m_hWnd, m_cooperativeLevel));

	if (result) {
		Acquire();
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044ff50
void DirectInputDevice::SetBufferSize(undefined4 p_bufferSize)
{
	undefined4 wasAcquired = IsAcquired();
	if (wasAcquired) {
		Unacquire();
	}

	DIPROPDWORD prop;
	prop.dwData = p_bufferSize;
	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	TranslateDirectInputResult(m_device->SetProperty(DIPROP_BUFFERSIZE, &prop.diph));

	if (wasAcquired) {
		Acquire();
	}
}

// FUNCTION: LEGORACERS 0x0044ffc0
const wchar_t* DirectInputDevice::GetControlName(undefined4 p_arg)
{
	switch (GetKeySource(p_arg)) {
	case c_sourceKeyboard:
	case c_sourceMouse:
	case c_sourceJoystick1:
		return &m_stringBuffer[m_buttonNameIndices[LOWORD(p_arg)]];
	case c_sourceJoystick2:
		return &m_stringBuffer[m_axisNameIndices[p_arg & 0xfffe]];
	default:
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x00450030
undefined4 DirectInputDevice::Poll(LegoS32 p_elapsedMs)
{
	undefined4 result = TranslateDirectInputResult(m_device->Poll());

	if (result != 0) {
		return result;
	}

	DIDEVICEOBJECTDATA deviceData;
	DWORD count = 1;
	result = TranslateDirectInputResult(m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &deviceData, &count, 0));

	if (result == 0) {
		while (result == 0 && count != 0) {
			ProcessDeviceData(deviceData);

			if (count == 0) {
				break;
			}

			count = 1;
			result =
				TranslateDirectInputResult(m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &deviceData, &count, 0));

			if (result != 0) {
				return result;
			}
		}

		InputDevice::Poll(p_elapsedMs);
		return 0;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0044f2c0 FOLDED
LegoFloat DirectInputDevice::GetAxisValueByIndex(undefined4)
{
	return 0.0f;
}

// FUNCTION: LEGORACERS 0x004500f0
undefined4 DirectInputDevice::SetBackgroundMode()
{
	if (m_cooperativeLevel & DISCL_BACKGROUND) {
		return TRUE;
	}

	m_cooperativeLevel &= ~DISCL_FOREGROUND;
	m_cooperativeLevel |= DISCL_BACKGROUND;
	return ApplyCooperativeLevel();
}

// FUNCTION: LEGORACERS 0x00450110
undefined4 DirectInputDevice::SetForegroundMode()
{
	if (m_cooperativeLevel & DISCL_FOREGROUND) {
		return TRUE;
	}

	m_cooperativeLevel &= ~DISCL_BACKGROUND;
	m_cooperativeLevel |= DISCL_FOREGROUND;
	return ApplyCooperativeLevel();
}

// FUNCTION: LEGORACERS 0x00450130
undefined4 DirectInputDevice::SetExclusiveMode()
{
	if (m_cooperativeLevel & DISCL_EXCLUSIVE) {
		return TRUE;
	}

	m_cooperativeLevel &= ~DISCL_NONEXCLUSIVE;
	m_cooperativeLevel |= DISCL_EXCLUSIVE;
	return ApplyCooperativeLevel();
}

// FUNCTION: LEGORACERS 0x00450150
undefined4 DirectInputDevice::SetNonExclusiveMode()
{
	if (m_cooperativeLevel & DISCL_NONEXCLUSIVE) {
		return TRUE;
	}

	m_cooperativeLevel &= ~DISCL_EXCLUSIVE;
	m_cooperativeLevel |= DISCL_NONEXCLUSIVE;
	return ApplyCooperativeLevel();
}

// FUNCTION: LEGORACERS 0x00450170
undefined4 DirectInputDevice::TranslateDirectInputResult(HRESULT p_hResult)
{
	if (SUCCEEDED(p_hResult)) {
		return 0;
	}

	switch (p_hResult) {
	case DIERR_NOTACQUIRED:
		return IsAcquired() ? 1 : 2;
	case DIERR_INPUTLOST:
		if (IsAcquired()) {
			Acquire();
		}

		return 1;
	default:
		return 0;
	}
}

// FUNCTION: LEGORACERS 0x004501d0
LegoBool32 DirectInputDevice::CreateForceFeedbackEffect()
{
	if (!m_forceFeedbackAvailable) {
		return TRUE;
	}

	DWORD axes[2] = {DIJOFS_X, DIJOFS_Y};
	LONG direction[2] = {0, 0};

	SetExclusiveMode();

	DIPERIODIC periodicParams;
	DIEFFECT effectParams;

	effectParams.dwDuration = INFINITE;
	effectParams.dwTriggerButton = DIEB_NOTRIGGER;

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
	effectParams.rgdwAxes = axes;
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
LegoS32 DirectInputDevice::StartForceFeedbackEffect()
{
	if (m_forceFeedbackAvailable && m_effect != NULL) {
		m_effect->Start(1, 0);
		return 0;
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x004502e0
LegoBool32 DirectInputDevice::StopForceFeedbackEffect()
{
	if (m_forceFeedbackAvailable && m_effect != NULL) {
		m_effect->Stop();
		return 0;
	}

	return 1;
}

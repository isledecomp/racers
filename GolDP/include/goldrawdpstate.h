#ifndef GOLDP_GOLDPSTATE_H
#define GOLDP_GOLDPSTATE_H

#include "golcommondrawstate.h"
#include "goldevicelist.h"
#include "slatepeak0x58.h"

#include <ddraw.h>

// VTABLE: GOLDP 0x10056140
// SIZE 0xc8ac4
class GolDrawDPState : public GolCommonDrawState {
public:
	GolDrawDPState();
	~GolDrawDPState() override; // vtable+0x04

	LegoS32 VTable0x00() override;                                                               // vtable+0x00
	void SetWindowHandle(HWND p_hWnd) override;                                                  // vtable+0x08
	void VTable0x0c(const char* p_driverName, const char* p_deviceName) override;                // vtable+0x0c
	LegoU32 GetDriverCount() override;                                                           // vtable+0x10
	const LegoChar* GetDriverDescription(LegoU32 p_index) override;                              // vtable+0x14
	const LegoChar* GetDriverName(LegoU32 p_index) override;                                     // vtable+0x18
	LegoU32 GetDeviceCount(LegoU32 p_driverIndex) override;                                      // vtable+0x1c
	const LegoChar* GetDeviceName(LegoU32 p_driverIndex, LegoU32 p_deviceIndex) override;        // vtable+0x20
	const LegoChar* GetDeviceDescription(LegoU32 p_driverIndex, LegoU32 p_deviceIndex) override; // vtable+0x24
	LegoBool32 IsDeviceHwAccelerated(LegoU32 p_driverIndex, LegoU32 p_deviceIndex) override;     // vtable+0x28
	void VTable0x2c(LegoU32 p_flags, LegoU32* p_driverIndex, LegoU32* p_deviceIndex) override;   // vtable+0x2c
	void GetDriverGuid(LegoU32 p_driverIndex, GUID* p_guid) override;                            // vtable+0x30
	void GetDeviceGuid(LegoU32 p_driverIndex, LegoU32 p_deviceIndex, GUID* p_guid) override;     // vtable+0x34
	GUID* GetCurrentDriverGuid() const override;                                                 // vtable+0x38

	void VTable0x48() override;                                // vtable+0x48
	void VTable0x50() override;                                // vtable+0x50
	undefined4 VTable0x58() override;                          // vtable+0x58
	LegoU32 GetZBufferBitDepth() const override;               // vtable+0x5c
	LegoBool32 IsHwAccelerated() override;                     // vtable+0x60
	LegoBool32 SupportsCulling() const override;               // vtable+0x64
	LegoBool32 SupportsPerspectiveCorrection() const override; // vtable+0x68
	LegoBool32 SupportsTextureWrap() const override;           // vtable+0x6c
	LegoBool32 SupportsCullCW() const override;                // vtable+0x70
	LegoBool32 SupportsCullCCW() const override;               // vtable+0x74
	LegoBool32 SupportsDither() const override;                // vtable+0x78
	LegoBool32 SupportsSubpixel() const override;              // vtable+0x7c
	LegoBool32 SupportsLinearFilter() const override;          // vtable+0x80
	LegoBool32 SupportsMipmap() const override;                // vtable+0x84
	LegoBool32 SupportsFogTable() const override;              // vtable+0x88
	LegoBool32 SupportsTextureAlpha() const override;          // vtable+0x8c
	LegoBool32 SupportsAdditiveBlend() const override;         // vtable+0x90
	undefined4 VTable0x94() override;                          // vtable+0x94
	LegoBool32 SupportsZBufferlessHsr() const override;        // vtable+0x98
	LegoBool32 SupportsPaletteAlpha() const override;          // vtable+0x9c
	LegoBool32 SupportsTextureSystemMemory() const override;   // vtable+0xa0
	LegoBool32 SupportsTextureVideoMemory() const override;    // vtable+0xa4
	LegoBool32 SupportsRenderingInWindow() const override;     // vtable+0xa8
	LPDIRECTDRAW GetDirectDraw() override;                     // vtable+0xac
	LPDIRECTDRAWSURFACE GetDisplaySurface() override;          // vtable+0xb0
	LPDIRECTDRAWSURFACE GetRenderSurface() override;           // vtable+0xb4

	// SYNTHETIC: GOLDP 0x100010e0
	// GolDrawDPState::`scalar deleting destructor'

	friend class DepthBuffer0x38;
	friend class SlatePeak0x58;
	friend class BronzeFalcon0xc8770;

private:
	void ReleaseDDraw();
	static HRESULT CALLBACK FindmatchingDepthPixelformat(LPDDPIXELFORMAT p_pixelformat, LPVOID p_context);

	LPDIRECTDRAW m_ddraw;                      // 0x20
	LPDIRECTDRAW4 m_ddraw4;                    // 0x24
	LPDIRECT3D3 m_d3d3;                        // 0x28
	HWND m_hWnd;                               // 0x2c
	DDCAPS m_ddrawCaps;                        // 0x30
	D3DDEVICEDESC m_deviceDesc;                // 0x1ac
	GolDeviceList::GolD3DDeviceInfo* m_device; // 0x2a8
	GUID m_deviceGuid;                         // 0x2ac
	LegoBool32 m_validGuid;                    // 0x2bc
	LegoBool32 m_hwAccelerated;                // 0x2c0
	DDPIXELFORMAT m_depthBufferPixelformat;    // 0x2c4
	GolDeviceList m_deviceList;                // 0x2e4
	LegoChar* m_driverName;                    // 0x2f4
	LegoChar* m_deviceName;                    // 0x2f8
	SlatePeak0x58 m_unk0x2fc;                  // 0x2fc
	BronzeFalcon0xc8770 m_unk0x354;            // 0x354
};

#endif // GOLDP_GOLDPSTATE_H

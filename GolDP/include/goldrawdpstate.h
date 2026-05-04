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

	LegoS32 VTable0x00() override;                                                             // vtable+0x00
	void VTable0x08(HWND p_hWnd) override;                                                     // vtable+0x08
	void VTable0x0c(const char* p_driverName, const char* p_deviceName) override;              // vtable+0x0c
	LegoU32 VTable0x10() override;                                                             // vtable+0x10
	const LegoChar* VTable0x14(LegoU32 p_index) override;                                      // vtable+0x14
	const LegoChar* VTable0x18(LegoU32 p_index) override;                                      // vtable+0x18
	LegoU32 VTable0x1c(LegoU32 p_index) override;                                              // vtable+0x1c
	const LegoChar* VTable0x20(LegoU32 p_driverIndex, LegoU32 p_deviceIndex) override;         // vtable+0x20
	const LegoChar* VTable0x24(LegoU32 p_driverIndex, LegoU32 p_deviceIndex) override;         // vtable+0x24
	LegoBool32 VTable0x28(LegoU32 p_driverIndex, LegoU32 p_deviceIndex) override;              // vtable+0x28
	void VTable0x2c(LegoU32 p_flags, LegoU32* p_driverIndex, LegoU32* p_deviceIndex) override; // vtable+0x2c
	void VTable0x30(LegoU32 p_driverIndex, GUID* p_guid) override;                             // vtable+0x30
	void VTable0x34(LegoU32 p_driverIndex, LegoU32 p_deviceIndex, GUID* p_guid) override;      // vtable+0x34
	GUID* VTable0x38() const override;                                                         // vtable+0x38

	void VTable0x48() override;                       // vtable+0x48
	void VTable0x50() override;                       // vtable+0x50
	undefined4 VTable0x58() override;                 // vtable+0x58
	undefined4 VTable0x5c() const override;           // vtable+0x5c
	undefined4 VTable0x60() override;                 // vtable+0x60
	LegoBool32 VTable0x64() const override;           // vtable+0x64
	LegoBool32 VTable0x68() const override;           // vtable+0x68
	LegoBool32 VTable0x6c() const override;           // vtable+0x6c
	LegoBool32 VTable0x70() const override;           // vtable+0x70
	LegoBool32 VTable0x74() const override;           // vtable+0x74
	LegoBool32 VTable0x78() const override;           // vtable+0x78
	LegoBool32 VTable0x7c() const override;           // vtable+0x7c
	LegoBool32 VTable0x80() const override;           // vtable+0x80
	LegoBool32 VTable0x84() const override;           // vtable+0x84
	LegoBool32 VTable0x88() const override;           // vtable+0x88
	LegoBool32 VTable0x8c() const override;           // vtable+0x8c
	LegoBool32 VTable0x90() const override;           // vtable+0x90
	undefined4 VTable0x94() override;                 // vtable+0x94
	LegoBool32 VTable0x98() const override;           // vtable+0x98
	LegoBool32 VTable0x9c() const override;           // vtable+0x9c
	LegoBool32 VTable0xa0() const override;           // vtable+0xa0
	LegoBool32 VTable0xa4() const override;           // vtable+0xa4
	LegoBool32 VTable0xa8() const override;           // vtable+0xa8
	LPDIRECTDRAW GetDirectDraw() override;            // vtable+0xac
	LPDIRECTDRAWSURFACE GetDisplaySurface() override; // vtable+0xb0
	LPDIRECTDRAWSURFACE GetRenderSurface() override;  // vtable+0xb4

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
	undefined4 m_unk0x2c0;                     // 0x2c0
	DDPIXELFORMAT m_depthBufferPixelformat;    // 0x2c4
	GolDeviceList m_deviceList;                // 0x2e4
	LegoChar* m_driverName;                    // 0x2f4
	LegoChar* m_deviceName;                    // 0x2f8
	SlatePeak0x58 m_unk0x2fc;                  // 0x2fc
	BronzeFalcon0xc8770 m_unk0x354;            // 0x354
};

#endif // GOLDP_GOLDPSTATE_H

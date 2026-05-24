#ifndef IMAGINARYGIZMO0X1908
#define IMAGINARYGIZMO0X1908

#include "golstringtable.h"
#include "imaginarychisel0x658.h"
#include "obscurebanner0x5ec.h"
#include "obscurecarousel0x78.h"
#include "obscuretome0x3dc.h"
#include "opalhaven0xf4.h"

// VTABLE: LEGORACERS 0x004b3f00
// SIZE 0x1908
class ImaginaryGizmo0x1908 : public ImaginaryChisel0x658 {
public:
	ImaginaryGizmo0x1908();

	void VTable0x4c() override;                                                        // vtable+0x4c
	~ImaginaryGizmo0x1908() override;                                                  // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00488820
	// ImaginaryGizmo0x1908::`scalar deleting destructor'

protected:
	LegoChar m_unk0x658[8];                  // 0x0658
	OpalHaven0xf4 m_unk0x660;                // 0x0660
	undefined4 m_unk0x754;                   // 0x0754
	ObscureTome0x3fc m_unk0x758;             // 0x0758
	ObscureCarouselNavigator0x94 m_unk0xb54; // 0x0b54
	ObscureBanner0x9f4 m_unk0xbe8;           // 0x0be8
	ObscureAnchor0x5c m_unk0x15dc[7];        // 0x15dc
	ObscureZebra0xa4 m_unk0x1860;            // 0x1860
	undefined4 m_unk0x1904;                  // 0x1904
};

#endif // IMAGINARYGIZMO0X1908

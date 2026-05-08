#ifndef IMAGINARYGIZMO0X1908
#define IMAGINARYGIZMO0X1908

#include "golstringtable.h"
#include "imaginarychisel0x658.h"
#include "opalhaven0xf4.h"

// VTABLE: LEGORACERS 0x004b3f00
// SIZE 0x1908
class ImaginaryGizmo0x1908 : public ImaginaryChisel0x658 {
public:
	ImaginaryGizmo0x1908();

	void VTable0x4c() override;                                                        // vtable+0x4c
	~ImaginaryGizmo0x1908() override;                                                  // vtable+0x68
	LegoBool32 VTable0x74() override;                                                  // vtable+0x74
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00488820
	// ImaginaryGizmo0x1908::`scalar deleting destructor'

protected:
	undefined4 m_unk0x658;                // 0x0658
	undefined4 m_unk0x65c;                // 0x065c
	OpalHaven0xf4 m_unk0x660;             // 0x0660
	undefined m_unk0x754[0x1908 - 0x754]; // 0x0754
};

#endif // IMAGINARYGIZMO0X1908

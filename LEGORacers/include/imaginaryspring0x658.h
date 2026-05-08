#ifndef IMAGINARYSPRING0X658
#define IMAGINARYSPRING0X658

#include "compat.h"
#include "decomp.h"
#include "imaginarychisel0x658.h"

// VTABLE: LEGORACERS 0x004b3030
// SIZE 0x658
class ImaginarySpring0x658 : public ImaginaryChisel0x658 {
public:
	ImaginarySpring0x658();

	void VTable0x4c() override;                                                        // vtable+0x4c
	~ImaginarySpring0x658() override;                                                  // vtable+0x68
	LegoBool32 VTable0x74() override;                                                  // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00479aa0
	// ImaginarySpring0x658::`scalar deleting destructor'
};

#endif // IMAGINARYSPRING0X658

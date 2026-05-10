#ifndef OBSCUREANCHOR0X5C
#define OBSCUREANCHOR0X5C

#include "compat.h"
#include "decomp.h"
#include "obscureanthem0x58.h"

// VTABLE: LEGORACERS 0x004b26bc
// SIZE 0x5c
class ObscureAnchor0x5c : public ObscureAnthem0x58 {
public:
	ObscureAnchor0x5c();

	void Reset() override;                        // vtable+0x00
	~ObscureAnchor0x5c() override;                // vtable+0x04
	undefined4 VTable0x38(Rect*, Rect*) override; // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x0046f0d0
	// ObscureAnchor0x5c::`scalar deleting destructor'

protected:
	undefined4 m_unk0x58; // 0x58
};

#endif // OBSCUREANCHOR0X5C

#ifndef OBSCUREANCHOR0X7C_H
#define OBSCUREANCHOR0X7C_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "render/rectangle.h"

// VTABLE: LEGORACERS 0x004b26fc
// SIZE 0x7c
class ObscureAnchor0x7c : public ObscureAnchor0x5c {
public:
	ObscureAnchor0x7c();

	~ObscureAnchor0x7c() override;                         // vtable+0x04
	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override; // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x0046f250
	// ObscureAnchor0x7c::`scalar deleting destructor'

protected:
	void FUN_0046f2c0(Rect* p_rect);

	Rect m_unk0x5c; // 0x5c
	Rect m_unk0x6c; // 0x6c
};

#endif // OBSCUREANCHOR0X7C_H

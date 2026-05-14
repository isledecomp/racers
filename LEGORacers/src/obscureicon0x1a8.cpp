#include "obscureicon0x1a8.h"

#include "audio/soundgroupbinding.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ObscureIcon0x1a8, 0x1a8)
DECOMP_SIZE_ASSERT(ObscureIcon0x1a8::CreateParams0x84, 0x84)
DECOMP_SIZE_ASSERT(ObscureIcon0x1a8::CreateState0x90, 0x90)

// FUNCTION: LEGORACERS 0x004664f0
LegoBool32 ObscureIcon0x1a8::VTable0x5c()
{
	if (m_flags & 2) {
		LegoBool32 result = TRUE;
		if (result & m_unk0x12c) {
			return result;
		}
	}

	return FALSE;
}

// STUB: LEGORACERS 0x004676c0
undefined4 ObscureIcon0x1a8::VTable0x38(Rect*, Rect*)
{
	// TODO
	STUB(0x004676c0);
	return 0;
}

// FUNCTION: LEGORACERS 0x00471c30
ObscureIcon0x1a8::ObscureIcon0x1a8()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00471ca0
ObscureIcon0x1a8::~ObscureIcon0x1a8()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00471cf0
void ObscureIcon0x1a8::Reset()
{
	m_soundGroupBinding = NULL;
	m_unk0x170 = NULL;
	m_unk0x198 = NULL;
	m_unk0x12c = 0;
	m_unk0x19c = 0;
	m_unk0x12d = FALSE;
	m_lastIcon = NULL;
	m_firstIcon = NULL;
	m_nextIcon = NULL;
	m_prevIcon = NULL;
	m_parentIcon = NULL;
	m_unk0x134 = 0;
	m_unk0x1a4 = 0;
	m_unk0x1a0 = 0;
	m_unk0x168 = 0;

	::memset(m_unk0x158, 0, sizeof(m_unk0x158));
	::memset(m_unk0x174, 0xff, sizeof(m_unk0x174));
	::memset(m_soundIds, 0, sizeof(m_soundIds));
	::memset(m_unk0x6c, 0, sizeof(m_unk0x6c));

	ObscureVantage0x58::Reset();
}

// STUB: LEGORACERS 0x00471d90
void ObscureIcon0x1a8::FUN_00471d90(CreateParams0x84* p_createParams, const CreateState0x90* p_createState)
{
	const undefined* defaultRects = p_createParams->m_unk0x52;
	if (!p_createParams->m_unk0x78) {
		defaultRects = p_createState->m_unk0x00;
	}

	::memcpy(m_unk0x174, defaultRects, sizeof(m_unk0x174));

	const undefined* soundIds = p_createParams->m_unk0x6a;
	if (!p_createParams->m_unk0x7c) {
		soundIds = p_createState->m_unk0x18;
	}

	::memcpy(m_soundIds, soundIds, sizeof(m_soundIds));
	::memcpy(m_unk0x6c, p_createState->m_unk0x24, sizeof(m_unk0x6c));

	m_unk0x170 = p_createParams->m_unk0x80;
	m_soundGroupBinding = p_createParams->m_soundGroupBinding;
	m_unk0x168 = p_createParams->m_unk0x40;
	m_unk0x130 = p_createState->m_unk0x84;
	VTable0x40(p_createParams->m_unk0x80);
}

// FUNCTION: LEGORACERS 0x00471e30
LegoBool32 ObscureIcon0x1a8::FUN_00471e30(CreateParams0x84* p_createParams, const CreateState0x90* p_createState)
{
	VTable0x08();
	FUN_00471d90(p_createParams, p_createState);

	if (FUN_00472a60(p_createParams)) {
		if (p_createParams->m_unk0x74 && p_createParams->m_parentIcon && (m_flags & 4)) {
			FUN_00471ec0(p_createParams->m_parentIcon);
		}

		if (p_createParams->m_unk0x38) {
			VTable0x44(0);
		}

		FUN_00472080();
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00471ea0
undefined4 ObscureIcon0x1a8::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		FUN_00471f00();
		result = ObscureVantage0x58::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00471ec0
void ObscureIcon0x1a8::FUN_00471ec0(ObscureIcon0x1a8* p_parentIcon)
{
	FUN_00471f00();
	m_parentIcon = p_parentIcon;

	if (m_parentIcon) {
		if (!m_parentIcon->m_lastIcon) {
			m_parentIcon->m_firstIcon = this;
			m_parentIcon->m_lastIcon = this;
			return;
		}

		m_prevIcon = m_parentIcon->m_lastIcon;
		m_prevIcon->m_nextIcon = this;
		m_parentIcon->m_lastIcon = this;
	}

	m_unk0x12d = TRUE;
}

// FUNCTION: LEGORACERS 0x00471f00
void ObscureIcon0x1a8::FUN_00471f00()
{
	if (!(m_flags & 4)) {
		return;
	}

	if (m_prevIcon) {
		m_prevIcon->m_nextIcon = m_nextIcon;
	}
	else if (m_parentIcon) {
		m_parentIcon->m_firstIcon = m_nextIcon;
	}

	if (m_nextIcon) {
		m_nextIcon->m_prevIcon = m_prevIcon;
		m_nextIcon = NULL;
		m_prevIcon = NULL;
		m_parentIcon = NULL;
		m_unk0x12d = FALSE;
		return;
	}

	if (m_parentIcon) {
		m_parentIcon->m_lastIcon = m_prevIcon;
	}

	m_nextIcon = NULL;
	m_prevIcon = NULL;
	m_parentIcon = NULL;
	m_unk0x12d = FALSE;
}

// FUNCTION: LEGORACERS 0x00471f70
ObscureIcon0x1a8* ObscureIcon0x1a8::FUN_00471f70()
{
	ObscureIcon0x1a8* result = this;

	while (result->m_parentIcon) {
		result = result->m_parentIcon;
	}

	return result;
}

// STUB: LEGORACERS 0x00471f90
ObscureIcon0x1a8* ObscureIcon0x1a8::FUN_00471f90()
{
	ObscureIcon0x1a8* result = FUN_00471f70();
	ObscureIcon0x1a8* child = result->m_unk0x198;

	if (!child) {
		return NULL;
	}

	do {
		result = child;
		child = result->m_unk0x198;
	} while (child);

	return result;
}

// STUB: LEGORACERS 0x00471fb0
void ObscureIcon0x1a8::FUN_00471fb0(undefined4 p_flags)
{
	LegoU8 skipParentLink = (LegoU8) p_flags & 2;
	ObscureIcon0x1a8* icon = this;

	if (icon) {
		do {
			icon->m_unk0x12c |= 2;
			FUN_00472080();

			ImaginaryInterface* eventHandler = icon->m_unk0x170;
			if (eventHandler) {
				if (!(p_flags & 1)) {
					eventHandler->VTable0x3c(this);
				}
			}

			if (!skipParentLink && icon->m_parentIcon) {
				icon->m_parentIcon->m_unk0x198 = icon;
			}

			icon = icon->m_parentIcon;
		} while (icon);
	}
}

// STUB: LEGORACERS 0x00472010
void ObscureIcon0x1a8::FUN_00472010(undefined4 p_flags)
{
	LegoU8 skipParentLink = (LegoU8) p_flags & 2;
	ObscureIcon0x1a8* icon = this;

	if (icon) {
		do {
			icon->m_unk0x12c &= 0xfd;
			FUN_00472080();

			ImaginaryInterface* eventHandler = icon->m_unk0x170;
			if (eventHandler) {
				if (!(p_flags & 1)) {
					eventHandler->VTable0x40(this);
				}
			}

			if (!skipParentLink && icon->m_parentIcon) {
				icon->m_parentIcon->m_unk0x198 = NULL;
			}

			icon = icon->m_parentIcon;
		} while (icon);
	}
}

// STUB: LEGORACERS 0x00472080
void ObscureIcon0x1a8::FUN_00472080()
{
	LegoU8 flags = m_unk0x12c;
	LegoU32 oldState = 0;
	oldState = m_unk0x19c;

	if (flags & 1) {
		if (flags & 2) {
			m_unk0x19c = 4;
		}
		else {
			m_unk0x19c = 2;
		}
	}
	else {
		m_unk0x19c = 0;
	}

	if (flags & 4) {
		m_unk0x19c++;
	}

	LegoU32 state = 0;
	state = m_unk0x19c;
	if (oldState != state) {
		FUN_00472540();
	}

	VTable0x14((Rect*) &m_unk0x174[state]);
}

// FUNCTION: LEGORACERS 0x004720f0
void ObscureIcon0x1a8::VTable0x44(undefined4 p_flags)
{
	if (!(m_unk0x12c & 1)) {
		m_unk0x12c |= 1;
		FUN_00472080();

		if (m_unk0x170 && !(p_flags & 1)) {
			m_unk0x170->VTable0x2c(this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00472130
void ObscureIcon0x1a8::VTable0x48(undefined4 p_flags)
{
	if (m_unk0x12c & 1) {
		LegoU8 flags = (LegoU8) p_flags;

		if (m_unk0x12c & 2) {
			ObscureIcon0x1a8* root = FUN_00471f70();
			if (!root->VTable0x60() && !root->VTable0x68()) {
				VTable0x50(0);
			}
		}

		m_unk0x12c &= 0xfe;
		FUN_00472080();

		if (m_unk0x170 && !flags) {
			m_unk0x170->VTable0x30(this);
		}
	}
}

// FUNCTION: LEGORACERS 0x004721a0
void ObscureIcon0x1a8::VTable0x4c(undefined4 p_flags)
{
	if (m_unk0x12c & 1) {
		if ((m_unk0x12c & 2) && !m_unk0x198) {
			return;
		}

		if (!(p_flags & 2)) {
			ObscureIcon0x1a8* icon = FUN_00471f90();
			if (icon) {
				icon->VTable0x50(0);
			}
		}

		FUN_00471fb0(p_flags);

		if (!(p_flags & 4)) {
			m_soundGroupBinding->FUN_0046e970(m_soundIds[0]);
		}
	}
}

// FUNCTION: LEGORACERS 0x00472200
void ObscureIcon0x1a8::VTable0x50(undefined4 p_flags)
{
	if ((m_unk0x12c & 1) && (m_unk0x12c & 2)) {
		if (m_unk0x12c & 4) {
			VTable0x58(1);
		}

		if (m_parentIcon && !(p_flags & 2)) {
			ObscureIcon0x1a8* icon = FUN_00471f90();
			if (!icon) {
				return;
			}

			icon->FUN_00472010(p_flags);

			if (!(p_flags & 4)) {
				icon->m_soundGroupBinding->FUN_0046e970(icon->m_soundIds[1]);
			}

			return;
		}

		FUN_00472010(p_flags);

		if (!(p_flags & 4)) {
			m_soundGroupBinding->FUN_0046e970(m_soundIds[1]);
		}
	}
}

// FUNCTION: LEGORACERS 0x00472290
void ObscureIcon0x1a8::VTable0x54(undefined4 p_flags)
{
	if (m_unk0x12c & 4) {
		return;
	}

	LegoU8 flags = (LegoU8) p_flags;

	if (m_parentIcon && !(flags & 2)) {
		m_parentIcon->VTable0x54(0);
	}

	FUN_00472bc0();
	m_unk0x12c |= 4;
	FUN_00472080();

	if (m_unk0x170 && !flags) {
		m_unk0x170->VTable0x34(this);
	}

	if (!(flags & 4)) {
		m_soundGroupBinding->FUN_0046e970(m_soundIds[2]);
	}
}

// FUNCTION: LEGORACERS 0x00472310
void ObscureIcon0x1a8::VTable0x58(undefined4 p_flags)
{
	LegoU8 stateFlags = m_unk0x12c;
	m_unk0x1a0 = 0;

	if (stateFlags & 4) {
		if (m_flags & 8) {
			FUN_00472c10();
		}

		LegoU8 flags = (LegoU8) p_flags;

		if (m_parentIcon && !(flags & 2)) {
			m_parentIcon->VTable0x58(0);
		}

		m_unk0x12c &= 0xfb;
		FUN_00472080();

		if (m_unk0x170 && !flags) {
			m_unk0x170->VTable0x38(this);
		}

		if (!(flags & 4)) {
			m_soundGroupBinding->FUN_0046e970(m_soundIds[3]);
		}
	}
}

// FUNCTION: LEGORACERS 0x004723a0
ObscureIcon0x1a8* ObscureIcon0x1a8::VTable0x68()
{
	if (VTable0x5c()) {
		ObscureIcon0x1a8* child = m_firstIcon;

		while (child) {
			ObscureIcon0x1a8* result = child->VTable0x68();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_nextIcon;
		}

		VTable0x4c(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004723f0
ObscureIcon0x1a8* ObscureIcon0x1a8::VTable0x6c()
{
	if (VTable0x5c()) {
		ObscureIcon0x1a8* child = m_lastIcon;

		while (child) {
			ObscureIcon0x1a8* result = child->VTable0x68();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_prevIcon;
		}

		VTable0x4c(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00472440
ObscureIcon0x1a8* ObscureIcon0x1a8::VTable0x60()
{
	if (m_unk0x12c & 2) {
		ObscureIcon0x1a8* child = m_unk0x198;

		while (child) {
			ObscureIcon0x1a8* result = child->VTable0x60();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_nextIcon;
		}

		VTable0x50(0);
		return NULL;
	}

	if (VTable0x5c()) {
		ObscureIcon0x1a8* child = m_firstIcon;

		while (child) {
			ObscureIcon0x1a8* result = child->VTable0x60();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_nextIcon;
		}

		VTable0x4c(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004724c0
ObscureIcon0x1a8* ObscureIcon0x1a8::VTable0x64()
{
	if (m_unk0x12c & 2) {
		ObscureIcon0x1a8* child = m_unk0x198;

		while (child) {
			ObscureIcon0x1a8* result = child->VTable0x64();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_prevIcon;
		}

		VTable0x50(0);
		return NULL;
	}

	if (VTable0x5c()) {
		ObscureIcon0x1a8* child = m_lastIcon;

		while (child) {
			ObscureIcon0x1a8* result = child->VTable0x64();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_prevIcon;
		}

		VTable0x4c(0);
		return this;
	}

	return NULL;
}

// STUB: LEGORACERS 0x00472540
void ObscureIcon0x1a8::FUN_00472540()
{
	STUB(0x00472540);
}

// STUB: LEGORACERS 0x00472680
undefined4 ObscureIcon0x1a8::VTable0x3c(undefined4)
{
	// TODO
	STUB(0x00472680);
	return 0;
}

// STUB: LEGORACERS 0x00472790
undefined4 ObscureIcon0x1a8::VTable0x2c(void*, undefined4, undefined4)
{
	// TODO
	STUB(0x00472790);
	return 0;
}

// STUB: LEGORACERS 0x00472820
undefined4 ObscureIcon0x1a8::VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	// TODO
	STUB(0x00472820);
	return 0;
}

// STUB: LEGORACERS 0x004728e0
undefined4 ObscureIcon0x1a8::VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	// TODO
	STUB(0x004728e0);
	return 0;
}

// STUB: LEGORACERS 0x00472950
void ObscureIcon0x1a8::VTable0x10(Rect*)
{
	STUB(0x00472950);
}

// STUB: LEGORACERS 0x004729a0
void ObscureIcon0x1a8::VTable0x40(ImaginaryInterface*)
{
	STUB(0x004729a0);
}

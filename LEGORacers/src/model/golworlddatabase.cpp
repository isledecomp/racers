#include "world/golworlddatabase.h"

#include "camera/golcamerabase.h"
#include "golanimatedentity.h"
#include "golmodelentity.h"
#include "mabmaterialanimation0x14.h"

// FUNCTION: LEGORACERS 0x00416040
void GolWorldDatabase::FUN_00416040()
{
	if (m_unk0x5c) {
		VTable0x1c(m_unk0x04);
	}

	if (m_unk0x54) {
		VTable0x24(m_unk0x04);
	}

	if (m_unk0x4c) {
		VTable0x20(m_unk0x04);
	}

	if (m_unk0x6c) {
		VTable0x28(m_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x00416090
void GolWorldDatabase::FUN_00416090(LegoS32 p_elapsedMs)
{
	LegoU32 i;

	for (i = 0; i < m_unk0x74; i++) {
		VTable0x4c(i)->FUN_00410300(p_elapsedMs);
	}

	for (i = 0; i < m_unk0x4c; i++) {
		m_unk0x9c[i].VTable0x10(p_elapsedMs);
	}

	for (i = 0; i < m_unk0x54; i++) {
		m_unk0xa0[i].VTable0x10(p_elapsedMs);
	}

	for (i = 0; i < m_unk0x7c; i++) {
		VTable0x50(i)->UpdateFromTrackedEntity();
	}
}

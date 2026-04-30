#include "citrinegrove0x1f4c.h"

#include "golerror.h"
#include "golfile.h"
#include "golstream.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CitrineGrove0x1f4c, 0x1f4c)
DECOMP_SIZE_ASSERT(MarigoldTrail0x108, 0x108)

// GLOBAL: LEGORACERS 0x004bef80
const LegoChar* g_defaultSaveFileName = "default.lrs";

// GLOBAL: LEGORACERS 0x004bef84
const LegoChar* g_quickBuildSaveFileName = "qbuild.lrs";

// FUNCTION: LEGORACERS 0x00443120
CitrineGrove0x1f4c::CitrineGrove0x1f4c()
{
	FUN_004432d0();
}

// FUNCTION: LEGORACERS 0x00443210
CitrineGrove0x1f4c::~CitrineGrove0x1f4c()
{
	FUN_004436e0();
}

// FUNCTION: LEGORACERS 0x004432d0
void CitrineGrove0x1f4c::FUN_004432d0()
{
	m_unk0x18c0 = 0;
}

// FUNCTION: LEGORACERS 0x004432e0
void CitrineGrove0x1f4c::FUN_004432e0(undefined4* p_arg1, undefined4 p_arg2)
{
	char path[128];

	m_unk0x18c4.FUN_0042e920(p_arg1);
	if (g_searchPaths[0] != NULL) {
		::strcpy(path, g_searchPaths[0]);
		size_t len = strlen(path);
		if ((LegoS32) len > 0 && path[len - 1] != '\\') {
			path[len] = '\\';
			path[len + 1] = '\0';
		}
	}
	else {
		path[0] = '\0';
	}

	::strcat(path, "Save\\");
	FUN_00450fc0(path);
	m_unk0x108.FUN_004426d0(5, 1, 0);
	m_unk0x18c4.FUN_0042ef80(&m_unk0x108);
	FUN_00443520(p_arg2);
	m_unk0x5b0.FUN_004426d0(4, 3, 0);
	FUN_00443620(g_defaultSaveFileName, &m_unk0x5b0);
	m_unk0x1418.FUN_004426d0(36, 3, 0);
	FUN_00443620(g_quickBuildSaveFileName, &m_unk0x1418);
	m_unk0x1cfc.FUN_0042b2f0(4, 0, 0, 0);
}

// FUNCTION: LEGORACERS 0x00443420
undefined4 CitrineGrove0x1f4c::FUN_00443420(LegoU32 p_index, undefined4 p_arg2)
{
	PeridotTrace0x4e0* entry = &m_unk0xa58[p_index];
	undefined4 status = entry->FUN_00443910();

	if (status == 0) {
		undefined4 result = entry->FUN_00443980();

		if (result == 0 && m_unk0x18c4.GetUnk0x04() == -1) {
			m_unk0x18c4.FUN_0042eb60(entry, p_index);
		}

		return result;
	}
	else if (status == 8) {
		if (p_arg2 != 0) {
			undefined4 result = entry->FUN_00443940();

			if (m_unk0x18c4.GetUnk0x04() == -1) {
				m_unk0x18c4.FUN_0042eb60(entry, p_index);
			}

			return result;
		}
	}

	return status;
}

// FUNCTION: LEGORACERS 0x004434a0
undefined4 CitrineGrove0x1f4c::FUN_004434a0(undefined4 p_index)
{
	if (m_unk0x18c4.GetUnk0x00() && m_unk0x18c4.GetUnk0x04() == p_index) {
		m_unk0x18c4.FUN_0042ef80(&m_unk0xa58[p_index]);
		m_unk0x18c4.SetUnk0x00(0);
		return m_unk0xa58[p_index].FUN_004439b0();
	}

	if (m_unk0xa58[p_index].GetUnk0x20()) {
		return m_unk0xa58[p_index].FUN_004439b0();
	}

	return 0;
}

// STUB: LEGORACERS 0x00443520
void CitrineGrove0x1f4c::FUN_00443520(undefined4)
{
	// TODO
	STUB(0x00443520);
}

// STUB: LEGORACERS 0x004435c0
void CitrineGrove0x1f4c::FUN_004435c0()
{
	// TODO
	STUB(0x004435c0);
}

// FUNCTION: LEGORACERS 0x00443620
void CitrineGrove0x1f4c::FUN_00443620(const LegoChar* p_fileName, PeridotTrace0x4a8* p_arg2)
{
	GolFile* file = new GolFile;
	if (file == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	if (file->BufferedOpen(p_fileName, GolFile::c_modeRead, 1024)) {
		if (file != NULL) {
			delete file;
		}
		return;
	}

	if (p_arg2->FUN_00442770(*file)) {
		GOL_FATALERROR_MESSAGE("Corrupt install - invalid default save file");
	}

	file->Dispose();
	if (file != NULL) {
		delete file;
	}
}

// STUB: LEGORACERS 0x004436e0
void CitrineGrove0x1f4c::FUN_004436e0()
{
	// TODO
	STUB(0x4436e0);
}

// STUB: LEGORACERS 0x00450fc0
void CitrineGrove0x1f4c::FUN_00450fc0(const LegoChar* p_path)
{
	// TODO
	STUB(0x00450fc0);
}

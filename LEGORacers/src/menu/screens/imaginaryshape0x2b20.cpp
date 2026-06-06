#include "menu/screens/imaginaryshape0x2b20.h"

#include "audio/soundgroupbinding.h"
#include "decomp.h"
#include "golstream.h"
#include "menu/crimsonsun0xa4.h"
#include "menu/menutoolcontext0x4bc8.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryShape0x2b20, 0x2b20)

// FUNCTION: LEGORACERS 0x00476d50
ImaginaryShape0x2b20::ImaginaryShape0x2b20()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00476ef0
ImaginaryShape0x2b20::~ImaginaryShape0x2b20()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00476ff0
void ImaginaryShape0x2b20::Reset()
{
	m_unk0x2ae0 = 1;
	m_unk0x2ae4 = 1;

	m_unk0x2adc = 0;
	m_unk0x2ad8 = 0;
	m_unk0x28d0 = 0;
	m_unk0x28cc = 0;
	m_unk0x28c8 = 0;
	m_unk0x2b1c = 0;
	m_partCategoryUnlockFlags = 0;

	memset(m_partCategoryAvailable, 0, sizeof(m_partCategoryAvailable));

	ObsidianMantle0x3b4::Reset();
}

// FUNCTION: LEGORACERS 0x00477050
void ImaginaryShape0x2b20::FUN_00477050()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\GARAGE");
	}

	FUN_0046c510(&m_unk0x1e30, 0, 3);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	FieldAt0x2308::CreateParams0x30 params;
	::memset(&params, 0, sizeof(params));
	params.m_golExport = m_golExport;
	params.m_renderer = m_renderer;
	params.m_unk0x08 = &m_unk0x1e30;
	params.m_soundGroupBinding = m_soundGroupBinding;
	params.m_context = m_context;
	params.m_screen = this;
	params.m_unk0x1c.m_x = 0.0f;
	params.m_unk0x1c.m_y = 0.0f;
	params.m_unk0x1c.m_z = 1.0f;
	params.m_unk0x28 = 0.001f;
	params.m_unk0x2c = m_context->m_context->m_unk0x18;
	m_unk0x2308.FUN_00477ae0(&params);

	m_unk0x1e30.FUN_00465b40(&m_unk0x2308);
	m_unk0x2308.FUN_00478180(0.0f);
}

// FUNCTION: LEGORACERS 0x00477130
void ImaginaryShape0x2b20::FUN_00477130()
{
	FUN_0046c240(&m_unk0x410, 0x3e, 0xaf);
	FUN_0046c2b0(&m_unk0x4a4, &m_unk0x410, 0xaa, 0x4d);

	for (LegoU32 i = 0; i < 12; i++) {
		FUN_0046bef0(&m_unk0x19e0[i], 0x9d, static_cast<undefined2>(i + 0x9e));
	}
}

// FUNCTION: LEGORACERS 0x00477190
void ImaginaryShape0x2b20::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x3b4, 0x49, 0x49);
	FUN_00477050();
	FUN_00477130();
	FUN_0047fcf0(&m_unk0xe98, 0xae, 0x3b);
	FUN_0046c2b0(&m_unk0xfec, &m_unk0xe98, 0xac, 0xcc);

	m_unk0xe98.FUN_00485440(m_context->m_unk0x21a4.GetEntries()[m_partCategoryAvailable[0]].GetUnk0x08());
}

// FUNCTION: LEGORACERS 0x00477210
void ImaginaryShape0x2b20::VTable0x80()
{
	ColorRGBA lightColor;
	ColorRGBA materialColor;

	materialColor.m_blu = 0x78;
	materialColor.m_grn = 0x78;
	materialColor.m_red = 0x78;
	materialColor.m_alp = 0x78;
	lightColor.m_blu = 0xff;
	lightColor.m_grn = 0xff;
	lightColor.m_red = 0xff;
	lightColor.m_alp = 0xff;

	FUN_0047fec0(&materialColor, &lightColor);
}

// FUNCTION: LEGORACERS 0x00477250
LegoBool32 ImaginaryShape0x2b20::VTable0x8c(MenuToolContext0x4bc8* p_unk0x04, MenuToolCreateParams0x30* p_unk0x08)
{
	if (!ImaginaryTool0x368::VTable0x8c(p_unk0x04, p_unk0x08)) {
		return FALSE;
	}

	FUN_00477290();
	VTable0x44(&m_unk0xfec);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00477290
void ImaginaryShape0x2b20::FUN_00477290()
{
	SaveSystem* saveSystem = &m_context->m_unk0x258;
	m_partCategoryUnlockFlags = saveSystem->GetUnk0x18c4().FUN_0042f1e0();

	LegoS32 i;
	for (i = 0; i < c_alwaysAvailablePartCategoryCount; i++) {
		m_partCategoryAvailable[i] = TRUE;
	}

	LegoS32 mask = 1;
	for (i = 0; i < c_saveUnlockedPartCategoryCount; i++) {
		if (m_partCategoryUnlockFlags & mask) {
			m_partCategoryAvailable[i + c_alwaysAvailablePartCategoryCount] = TRUE;
		}
		mask <<= 1;
	}

	for (i = 0; i < m_context->m_unk0x21f4.GetUnk0xd4(); i++) {
		LegoS32 index = m_context->m_unk0x21a4.FindEntryIndex(m_context->m_unk0x21f4.FUN_0049bd50(i));
		m_partCategoryAvailable[index] = TRUE;
	}

	for (i = 0; i < c_partCategoryCount; i++) {
		if (m_partCategoryAvailable[i]) {
			m_unk0x410.FUN_0046d9c0(&m_unk0x19e0[i]);
		}
	}

	m_unk0x410.VTable0x50(0);
}

// FUNCTION: LEGORACERS 0x00477380
void ImaginaryShape0x2b20::VTable0x84()
{
	FUN_004773a0();
	m_context->m_menuStack.Pop();
}

// FUNCTION: LEGORACERS 0x004773a0
void ImaginaryShape0x2b20::FUN_004773a0()
{
	memset(m_carBuildSaveBuffer, 0, c_carBuildSaveBufferSize);
	m_context->m_unk0x21f4.FUN_0049c820(m_carBuildSaveBuffer);
	m_context->m_unk0x258.GetUnk0x1cfc().FUN_0042b4f0(m_carBuildSaveBuffer);
}

// STUB: LEGORACERS 0x004773e0
LegoBool32 ImaginaryShape0x2b20::FUN_004773e0(LegoS32 p_deltaX, LegoS32 p_deltaY, LegoU16 p_sound, LegoBool32 p_unk0x10)
{
	LegoU32 fallbackSound = p_sound ? 8 : 0;

	if (m_unk0x2ae0 == 6) {
		return FALSE;
	}

	if (p_deltaX && p_deltaY && !p_unk0x10) {
		if (m_unk0x2308.FUN_004785b0(p_deltaX) && m_unk0x2308.FUN_00478670(p_deltaY)) {
			m_soundGroupBinding->FUN_0046e970(p_sound & 0xffff);
			return TRUE;
		}

		m_unk0x2308.FUN_004785b0(-p_deltaX);
		m_soundGroupBinding->FUN_0046e970(fallbackSound & 0xffff);
		return FALSE;
	}

	LegoBool32 result = m_unk0x2308.FUN_004785b0(p_deltaX);
	result |= m_unk0x2308.FUN_00478670(p_deltaY);
	if (result) {
		m_soundGroupBinding->FUN_0046e970(p_sound & 0xffff);
		return result;
	}

	m_soundGroupBinding->FUN_0046e970(fallbackSound & 0xffff);
	return result;
}

// FUNCTION: LEGORACERS 0x00477600
void ImaginaryShape0x2b20::VTable0xc4()
{
	FUN_0047fdc0(&m_unk0x25d8, 0x99, 0x42, 0x72);
	FUN_0046c730(&m_unk0x25d8, 0xba);
}

// FUNCTION: LEGORACERS 0x00477630
void ImaginaryShape0x2b20::VTable0x38(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x25d8) {
		m_unk0x284->FUN_00468cf0();
	}
}

// FUNCTION: LEGORACERS 0x00477650
void ImaginaryShape0x2b20::VTable0x44(ObscureVantage0x58* p_source)
{
	if (m_unk0x2ae0 == 6) {
		return;
	}

	if (p_source == &m_unk0xfec) {
		m_unk0x2308.FUN_00477e40(m_unk0xe98.GetUnk0xd4(m_unk0xe98.GetUnk0x6c()));
		return;
	}

	if (p_source == &m_unk0x4a4) {
		ObscureVantage0x58* child = m_unk0x410.GetUnk0x78();
		LegoU32 i;
		for (i = 0; i < c_partCategoryCount; i++) {
			if (child == &m_unk0x19e0[i]) {
				SiennaCircuit0x154* circuit = &m_unk0xe98;
				circuit->FUN_00485440(m_context->m_unk0x21a4.GetEntries()[i].GetUnk0x08());
				m_unk0x2308.FUN_00477e40(circuit->GetUnk0xd4(circuit->GetUnk0x6c()));
				return;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00477700
void ImaginaryShape0x2b20::VTable0x10(ObscureVantage0x58* p_source)
{
	if (p_source == &m_unk0x1e30) {
		switch (m_unk0x2adc) {
		case 4: {
			SiennaCircuit0x154* circuit = &m_unk0xe98;
			circuit->FUN_004853f0();
			circuit->VTable0x50(circuit->FUN_0046c9a0(m_unk0xe98.GetUnk0x6c()));
			m_unk0x2308.FUN_00477e40(circuit->GetUnk0xd4(circuit->GetUnk0x6c()));
		}
		case 5:
			m_unk0x2ae4 = 1;
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00477770
void ImaginaryShape0x2b20::FUN_00477770()
{
	switch (m_unk0x2ae0) {
	case 1:
		VTable0xa8();
		break;
	case 2:
		VTable0xb0();
		break;
	case 3:
		VTable0xb8();
		break;
	case 6:
		VTable0xc0();
		break;
	}

	switch (m_unk0x2ae4) {
	case 1:
		VTable0xa4();
		if (m_unk0xd8.GetFlags() & 8) {
			m_unk0xd8.FUN_00472c10();
		}
		break;
	case 2:
		VTable0xac();
		break;
	case 3:
		VTable0xb4();
		break;
	case 5:
		m_unk0x2ae4 = 6;
		m_unk0x2adc = 5;
		m_unk0x2308.FUN_004792d0();
		break;
	case 6:
		VTable0xbc();
		break;
	}

	m_unk0x35c = NULL;
	m_unk0x2ae0 = m_unk0x2ae4;
}

// FUNCTION: LEGORACERS 0x00477880
LegoBool32 ImaginaryShape0x2b20::VTable0x78(undefined4 p_unk0x04)
{
	if (m_unk0x2ae0 != m_unk0x2ae4) {
		if (m_unk0x35c == NULL || !(m_unk0x35c->GetUnk0x54() & 1)) {
			FUN_00477770();
		}
	}

	return ObsidianMantle0x3b4::VTable0x78(p_unk0x04);
}

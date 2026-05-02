#include "falcondunebag0x10.h"

// GLOBAL: GOLDP 0x10063558
FalconTextureFormat FalconDuneBag0x10::g_textureFormat;

// FUNCTION: GOLDP 0x100146c0
FalconDuneBag0x10::FalconDuneBag0x10()
{
	m_unk0x0c = NULL;
}

// FUNCTION: GOLDP 0x10014700
FalconDuneBag0x10::~FalconDuneBag0x10()
{
	Destroy();
}

// STUB: GOLDP 0x10014770
void FalconDuneBag0x10::FUN_10014770(undefined4*)
{
	// TODO
	STUB(0x10014770);
}

// FUNCTION: GOLDP 0x100147f0
void FalconDuneBag0x10::Destroy()
{
	if (m_unk0x0c != NULL) {
		delete m_unk0x0c;
		m_unk0x0c = NULL;
	}
	FUN_1002a1b0();
}

// FUNCTION: GOLDP 0x10014820
void FalconDuneBag0x10::SetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	BronzeDuneBag0xc::SetEntries(p_entries, p_start, p_count);

	while (p_count > 0) {
		m_unk0x0c[p_start] = g_textureFormat.MapRGBA(*p_entries);
		p_start++;
		p_entries++;
		p_count--;
	}
}

// FUNCTION: GOLDP 0x10014870
void FalconDuneBag0x10::CopyEntriesFrom(IPalette0x4* p_source)
{
	LegoU32 i;
	ColorRGBA entry;
	BronzeDuneBag0xc::CopyEntriesFrom(p_source);
	for (i = 0; i < m_size; i++) {
		p_source->GetEntry(&entry, i);
		m_unk0x0c[i] = g_textureFormat.MapRGBA(entry);
	}
}

// FUNCTION: GOLDP 0x100148c0
void FalconDuneBag0x10::SetTextureFormat(const FalconTextureFormat& p_format)
{
	g_textureFormat = p_format;
}

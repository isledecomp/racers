#include "imaginarytool0x368.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golstring.h"
#include "menutoolcontext0x4bc8.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryTool0x368, 0x368)
DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x2e0, 0x60)
DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x2e0::Entry0xe0, 0xe0)
DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x2e0::MidTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x340, 0x10)
DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x350, 0x4)

void __stdcall FUN_00469b20(ImaginaryTool0x368::FieldAt0x2e0::Entry0xe0* p_entry);
LegoBool32 __stdcall FUN_00480440(MenuToolContext0x4bc8* p_context);
void __stdcall FUN_004804c0(MenuToolContext0x4bc8* p_context);

// FUNCTION: LEGORACERS 0x00408460
ImaginaryTool0x368::FieldAt0x340::FieldAt0x340()
{
	m_unk0x0c = -1.0f;
	m_unk0x04 = 0.0f;
	m_unk0x08 = 0.0f;
}

// FUNCTION: LEGORACERS 0x0040eac0
ImaginaryTool0x368::FieldAt0x350::FieldAt0x350()
{
	m_unk0x00 = 0xff;
	m_unk0x01 = 0xff;
	m_unk0x02 = 0xff;
	m_unk0x03 = 0xff;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void ImaginaryTool0x368::VTable0x80()
{
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
undefined4 ImaginaryTool0x368::VTable0x18(ObscureIcon0x1a8*, OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return m_unk0x364;
}

// FUNCTION: LEGORACERS 0x004804f0 FOLDED
undefined4 ImaginaryTool0x368::VTable0x1c(ObscureIcon0x1a8*, OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return m_unk0x364;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void ImaginaryTool0x368::VTable0x90(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void ImaginaryTool0x368::VTable0x94(undefined4)
{
}

// FUNCTION: LEGORACERS 0x00469b20
void __stdcall FUN_00469b20(ImaginaryTool0x368::FieldAt0x2e0::Entry0xe0* p_entry)
{
	p_entry->m_unk0x38 = TRUE;
	p_entry->m_unk0x74 = TRUE;
	::memset(p_entry->m_unk0x52, 0xff, sizeof(p_entry->m_unk0x52));
}

// STUB: LEGORACERS 0x00469b50
void ImaginaryTool0x368::FieldAt0x2e0::FUN_00469b50(Entry0xe0*)
{
	// TODO
	STUB(0x00469b50);
}

// FUNCTION: LEGORACERS 0x00474bf0 FOLDED
CeruleanEmperor0x4c* ImaginaryTool0x368::GetMenuStyles()
{
	return &m_unk0x290;
}

// FUNCTION: LEGORACERS 0x00474c00
CeruleanQueen0x58* ImaginaryTool0x368::GetMenuInputBindings()
{
	return &m_unk0x2e0;
}

// FUNCTION: LEGORACERS 0x0047f0a0
ImaginaryTool0x368::FieldAt0x2e0::FieldAt0x2e0()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x0047f110
ImaginaryTool0x368::FieldAt0x2e0::~FieldAt0x2e0()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0047f160
void ImaginaryTool0x368::FieldAt0x2e0::VTable0x0c()
{
	m_unk0x5c = NULL;
	CeruleanQueen0x58::Clear();
}

// FUNCTION: LEGORACERS 0x0047f170
void ImaginaryTool0x368::FieldAt0x2e0::Clear()
{
	if (m_nameEntries) {
		if (m_unk0x5c) {
			delete[] m_unk0x5c;
		}

		CeruleanQueen0x58::Clear();
	}
}

// FUNCTION: LEGORACERS 0x0047f1a0
void ImaginaryTool0x368::FieldAt0x2e0::VTable0x10(undefined4 p_param)
{
	if (p_param) {
		m_unk0x10 = new GolBinParser();
		if (m_unk0x10 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_unk0x10->SetSuffix(".mib");
		return;
	}

	m_unk0x10 = new MidTxtParser();
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: LEGORACERS 0x0047f290
void ImaginaryTool0x368::FieldAt0x2e0::VTable0x14(undefined4 p_arg1)
{
	if (p_arg1 != 0x46) {
		CeruleanQueen0x58::VTable0x14(p_arg1);
		return;
	}

	FUN_0047f410();
}

// FUNCTION: LEGORACERS 0x0047f2b0
void ImaginaryTool0x368::FieldAt0x2e0::FUN_0047f2b0(Entry0xe0* p_entry)
{
	FUN_00469b20(p_entry);
	::memset(p_entry->m_unk0xb4, 0xff, sizeof(p_entry->m_unk0xb4));

	if (m_unk0x10->GetNextToken() != GolFileParser::e_leftCurly) {
		m_unk0x10->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_unk0x10->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_unk0x10->GetCurrentToken()) {
		case GolFileParser::e_unknown0x29: {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_unk0x84[i] = m_unk0x14->FindFontByName(m_unk0x10->ReadString());
			}
			break;
		}
		case GolFileParser::e_unknown0x28: {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_unk0x9c[i] = m_unk0x14->FindImageByName(m_unk0x10->ReadString());
			}
			break;
		}
		case GolFileParser::e_unknown0x2a: {
			FUN_0046b210(p_entry->m_unk0xd0);

			LegoS32 i;
			for (i = 0; i < 6; i++) {
				FUN_0046b210(p_entry->m_unk0xb4[i]);
			}

			for (i = 0; i < 6; i++) {
				FUN_0046b210(p_entry->m_unk0x52[i]);
			}

			p_entry->m_unk0x78 = TRUE;
			break;
		}
		case GolFileParser::e_unknown0x33:
			p_entry->m_unk0xd8 = m_unk0x10->ReadInteger();
			p_entry->m_unk0xdc = TRUE;
			break;
		default:
			FUN_00469b50(p_entry);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0047f410
void ImaginaryTool0x368::FieldAt0x2e0::FUN_0047f410()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x5c = new Entry0xe0[entryCount];
	::memset(m_unk0x5c, 0, sizeof(Entry0xe0) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_unk0x10->GetNextToken() != GolFileParser::e_unknown0x46) {
			m_unk0x10->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		LegoChar name[8];
		::strncpy(name, m_unk0x10->ReadString(), sizeof(name));
		AddName(name, &m_unk0x5c[i]);
		FUN_0047f2b0(&m_unk0x5c[i]);
	}
}

// FUNCTION: LEGORACERS 0x0047fae0
ImaginaryTool0x368::ImaginaryTool0x368()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047fb80
ImaginaryTool0x368::~ImaginaryTool0x368()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047fbf0
void ImaginaryTool0x368::Reset()
{
	m_unk0x360 = 0xffff;
	m_menuId = 0;
	m_unk0x354 = NULL;
	m_unk0x35c = NULL;
	m_unk0x358 = 0;
	m_unk0x364 = FALSE;
	ImaginaryNotion0x290::Reset();
}

// FUNCTION: LEGORACERS 0x0047fc20
LegoBool32 ImaginaryTool0x368::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	GolString string;

	m_unk0x354 = p_context;
	LegoBool32 result = ImaginaryNotion0x290::VTable0x70(p_createParams);
	VTable0x80();

	return result;
}

// FUNCTION: LEGORACERS 0x0047fca0
LegoBool32 ImaginaryTool0x368::Destroy()
{
	if (!m_unk0x04) {
		return TRUE;
	}

	if (m_unk0x354->m_unk0x4b40.HasMenuResources()) {
		m_unk0x354->m_unk0x4b40.RefreshMenuResources();
	}

	m_unk0xb8->VTable0x28();
	m_unk0xb8->VTable0x60();
	return ImaginaryNotion0x290::Destroy();
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg prevents this trivial body from folding with identical functions elsewhere.

// FUNCTION: LEGORACERS 0x004803c0
#pragma code_seg(".text$imaginarytool_vt6c")
LegoFloat ImaginaryTool0x368::VTable0x6c()
{
	return 1.0f;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x00480420 FOLDED
LegoBool32 ImaginaryTool0x368::VTable0x88()
{
	if (m_unk0x35c) {
		return !(m_unk0x35c->GetUnk0x54() & TRUE);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00480440
LegoBool32 __stdcall FUN_00480440(MenuToolContext0x4bc8* p_context)
{
	MusicInstance* musicInstance = p_context->m_unk0x4b40.GetMusicInstance();
	return musicInstance && musicInstance->IsPlaying();
}

// FUNCTION: LEGORACERS 0x00480470
void ImaginaryTool0x368::FUN_00480470(MenuToolContext0x4bc8* p_context, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	FUN_004804c0(p_context);

	MusicInstance* musicInstance = p_context->m_unk0x4b40.GetMusicGroup()->CreateMusicInstance(p_unk0x08);
	p_context->m_unk0x4b40.SetMusicInstance(musicInstance);

	if (!musicInstance) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	p_context->m_unk0x4b40.GetMusicInstance()->Play(p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x004804c0
void __stdcall FUN_004804c0(MenuToolContext0x4bc8* p_context)
{
	if (FUN_00480440(p_context)) {
		p_context->m_unk0x4b40.GetMusicGroup()->DestroyMusicInstance(p_context->m_unk0x4b40.GetMusicInstance());
		p_context->m_unk0x4b40.SetMusicInstance(NULL);
	}
}

// FUNCTION: LEGORACERS 0x00480500 FOLDED
void ImaginaryTool0x368::VTable0x34(undefined4)
{
	m_unk0x364 = FALSE;
}

// FUNCTION: LEGORACERS 0x00480510 FOLDED
void ImaginaryTool0x368::VTable0x3c(undefined4 p_unk0x04)
{
	m_unk0x358 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00480520
LegoBool32 ImaginaryTool0x368::VTable0x78(undefined4)
{
	if (m_unk0x364 && VTable0x88()) {
		VTable0x84();
	}

	return FALSE;
}

// STUB: LEGORACERS 0x00487d30 FOLDED
void ImaginaryTool0x368::VTable0x40(undefined4)
{
	// TODO
	STUB(0x00487d30);
}

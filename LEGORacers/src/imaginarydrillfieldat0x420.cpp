#include "imaginarydrillfieldat0x420.h"

#include "golfont0xa0.h"
#include "golstringtable.h"

DECOMP_SIZE_ASSERT(ImaginaryDrillFieldAt0x420, 0x78)
DECOMP_SIZE_ASSERT(ImaginaryDrillFieldAt0x420::CreateParams0x48, 0x48)

// FUNCTION: LEGORACERS 0x0046f410
ImaginaryDrillFieldAt0x420::ImaginaryDrillFieldAt0x420()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046f490
ImaginaryDrillFieldAt0x420::~ImaginaryDrillFieldAt0x420()
{
	ObscureVantage0x58::VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046f4f0
void ImaginaryDrillFieldAt0x420::Reset()
{
	m_unk0x64.Reset();
	m_unk0x5c = 0;
	m_unk0x60 = NULL;
	m_unk0x58 = 0;
	m_unk0x70 = 0;
	m_unk0x74 = 0;
	ObscureVantage0x58::Reset();
}

// FUNCTION: LEGORACERS 0x0046f520
LegoBool32 ImaginaryDrillFieldAt0x420::FUN_0046f520(
	CreateParams0x48* p_createParams,
	CeruleanEmperor0x4c::Entry0x14* p_unk0x08
)
{
	VTable0x08();

	m_unk0x60 = p_createParams->m_unk0x3c;
	m_unk0x5c = p_createParams->m_unk0x38;
	m_unk0x58 = p_unk0x08;
	LegoS32 unk0x44 = p_createParams->m_unk0x44;
	m_unk0x70 = unk0x44;
	if (unk0x44) {
		m_unk0x74 = TRUE;
	}

	if (FUN_00472a60(p_createParams)) {
		VTable0x44(p_createParams->m_unk0x40, 0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046f580
void ImaginaryDrillFieldAt0x420::VTable0x44(undefined2, undefined4)
{
	GolString string;

	m_unk0x5c->CopyStringByIndex(&string, 0);
	VTable0x40(&string, 0);
}

// FUNCTION: LEGORACERS 0x0046f600
void ImaginaryDrillFieldAt0x420::VTable0x40(GolString* p_string, undefined4 p_unk0x08)
{
	m_unk0x64.CopyFromGolString(p_string);
	m_unk0x64.ToUpperCase();

	if (!m_unk0x34.m_right || !m_unk0x34.m_bottom || p_unk0x08) {
		m_unk0x64.FirstLine();
		m_unk0x34.m_bottom = m_unk0x34.m_top;
		m_unk0x34.m_right = m_unk0x34.m_left;

		for (LegoS32 i = 0; i < m_unk0x64.CountLines(); i++) {
			LegoS32 width;
			LegoS32 height;
			m_unk0x60->FUN_00408be0(&m_unk0x64, &width, &height);

			LegoU32 right = m_unk0x34.m_left + width;
			LegoU32 currentRight = m_unk0x34.m_right;
			if (right > currentRight) {
				m_unk0x34.m_right = right;
			}

			m_unk0x34.m_bottom += height;
			m_unk0x64.NextLine();
		}

		m_unk0x64.FirstLine();
	}
}

// FUNCTION: LEGORACERS 0x0046f6f0
undefined4 ImaginaryDrillFieldAt0x420::VTable0x38(Rect* p_rect, Rect* p_arg)
{
	LegoS32 lineCount = m_unk0x64.CountLines();
	LegoFloat lineCountFloat = static_cast<LegoFloat>(lineCount);
	LegoFloat lineHeight = static_cast<LegoFloat>(m_unk0x34.m_bottom - m_unk0x34.m_top) / lineCountFloat;
	LegoS32 xOffset = p_arg->m_left - p_rect->m_left;
	LegoS32 yOffset = p_arg->m_top - p_rect->m_top;
	LegoFloat lineBottom = 0.0f;

	m_unk0x64.FirstLine();
	if (lineCount > 0) {
		LegoS32 lineTop = 0;
		for (; lineCount > 0; lineCount--) {
			Rect source;
			source.m_left = 0;
			source.m_top = lineTop;

			lineBottom += lineHeight;
			lineTop = (LegoS32) lineBottom;
			source.m_bottom = lineTop;
			source.m_right = m_unk0x34.m_right - m_unk0x34.m_left;

			Rect dest;
			FUN_00472d00(m_unk0x60, &m_unk0x64, &source, &dest, 0);
			dest.m_left += xOffset;
			dest.m_top += yOffset;
			dest.m_right += xOffset;
			dest.m_bottom += yOffset;
			FUN_00472da0(&dest, p_arg, m_unk0x60, &m_unk0x64, 0, 0);
			m_unk0x64.NextLine();
		}
	}

	return 0;
}

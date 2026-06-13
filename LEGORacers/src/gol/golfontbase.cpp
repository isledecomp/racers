#include "font/golfontbase.h"

#include "decomp.h"
#include "golstring.h"

#include <math.h>
#include <string.h>

// FUNCTION: LEGORACERS 0x00408be0
void GolFontBase::MeasureString(GolString* p_string, LegoS32* p_width, LegoS32* p_height)
{
	GolFontBase* font = this;

	if (p_string == NULL) {
		if (p_width != NULL) {
			*p_width = 0;
		}

		if (p_height != NULL) {
			*p_height = 0;
		}

		return;
	}

	if (p_height != NULL) {
		*p_height = font->m_fontHeight;
	}

	if (p_width != NULL) {
		LegoS32 width = 0;
		LegoU32 length = p_string->SelectionLength();

		for (LegoU32 i = 0; i < length; i++) {
			if (*p_string->FromCursor(i) == ' ') {
				width += font->m_charSpacing + font->m_spaceWidth;
			}
			else {
				LegoU16 textChar = *p_string->FromCursor(i);
				LegoU32 glyphIndex = FindGlyphIndex(textChar);
				width += font->m_glyphs[glyphIndex].m_width + font->m_charSpacing;
			}
		}

		width -= font->m_charSpacing;

		*p_width = width < 0 ? 0 : width;
	}
}

// FUNCTION: LEGORACERS 0x00408ca0
void GolFontBase::MeasureString(const LegoChar* p_string, LegoS32* p_width, LegoS32* p_height)
{
	GolFontBase* font = this;

	if (p_string == NULL) {
		if (p_width != NULL) {
			*p_width = 0;
		}

		if (p_height != NULL) {
			*p_height = 0;
		}

		return;
	}

	if (p_height != NULL) {
		*p_height = font->m_fontHeight;
	}

	if (p_width != NULL) {
		LegoS32 width = 0;
		LegoU32 length = ::strlen(p_string);

		for (LegoU32 i = 0; i < length; i++) {
			if (p_string[i] == ' ') {
				width += font->m_charSpacing + font->m_spaceWidth;
			}
			else {
				LegoS16 textChar = p_string[i];
				LegoU32 glyphIndex = FindGlyphIndex(textChar);
				width += font->m_glyphs[glyphIndex].m_width + font->m_charSpacing;
			}
		}

		width -= font->m_charSpacing;

		*p_width = width < 0 ? 0 : width;
	}
}

// STUB: LEGORACERS 0x00408d50
void GolFontBase::FUN_00408d50(
	GolString* p_string,
	LegoS32 p_wrapWidth,
	LegoS32 p_unk0x10,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	LegoS32* p_width,
	LegoS32* p_height
)
{
	GolFontBase* font = this;

	*p_height = 0;
	*p_width = 0;

	LegoU8 lineBreak = TRUE;

	if (p_string == NULL) {
		return;
	}

	LegoU32 length = p_string->SelectionLength();
	if (length == 0) {
		return;
	}

	if (p_unk0x10 < 0) {
		*p_height = static_cast<LegoS32>(::ceil(static_cast<LegoFloat>(-p_unk0x10) * p_scaleY));
	}

	LegoU32 wrapWidth = static_cast<LegoU32>(::floor(static_cast<LegoFloat>(p_wrapWidth) / p_scaleX));
	LegoS32 lineHeight =
		static_cast<LegoS32>(::ceil(static_cast<LegoFloat>(font->m_fontHeight + p_unk0x10) * p_scaleY));
	*p_height += lineHeight;

	LegoU32 i = 0;
	while (i < length) {
		if (!lineBreak) {
			while (*p_string->FromCursor(i) == ' ') {
				i++;
			}
		}

		lineBreak = FALSE;
		LegoU32 lineStart = i;
		LegoU32 lastIndex = i - 1;
		LegoU32 wordWidth = 0;
		LegoU32 lineWidth = 0;

		while (i < length) {
			LegoU16 textChar = *p_string->FromCursor(i);
			if (textChar == '\n' || textChar == '\r') {
				break;
			}

			LegoU32 charWidth;
			if (textChar == ' ') {
				if (wordWidth != 0 && *p_string->FromCursor(lastIndex) != ' ') {
					lineStart = i;
					wordWidth = 0;
				}

				charWidth = font->m_charSpacing + font->m_spaceWidth;
			}
			else {
				LegoU32 glyphIndex = font->FindGlyphIndex(textChar);
				charWidth = font->m_glyphs[glyphIndex].m_width + font->m_charSpacing;
			}

			wordWidth += charWidth;
			lineWidth += charWidth;
			i++;
			lastIndex++;

			if (lineWidth > wrapWidth) {
				break;
			}
		}

		if (lineWidth > wrapWidth) {
			if (wordWidth == lineWidth) {
				lineStart++;

				while (lineWidth > wrapWidth && i > lineStart) {
					i--;
					LegoU16 textChar = *p_string->FromCursor(i);
					LegoU32 charWidth;

					if (textChar == ' ') {
						charWidth = font->m_charSpacing + font->m_spaceWidth;
					}
					else {
						LegoU32 glyphIndex = font->FindGlyphIndex(textChar);
						charWidth = font->m_glyphs[glyphIndex].m_width + font->m_charSpacing;
					}

					lineWidth -= charWidth;
				}
			}
			else {
				i = lineStart;
				lineWidth -= wordWidth;
			}
		}

		lineWidth -= font->m_charSpacing;
		if (static_cast<LegoU32>(*p_width) < lineWidth) {
			*p_width = lineWidth;
		}

		if (*p_string->FromCursor(i) == '\r') {
			i++;
			lineBreak = TRUE;
		}

		if (*p_string->FromCursor(i) == '\n') {
			i++;
			lineBreak = TRUE;
		}

		if (i < length) {
			*p_height += lineHeight;
		}
	}

	if (font->m_charSpacing < 0) {
		*p_width -= font->m_charSpacing;
	}

	*p_width = static_cast<LegoS32>(::ceil(static_cast<LegoFloat>(*p_width) * p_scaleX));
}

// STUB: LEGORACERS 0x00408fe0
undefined2 GolFontBase::FUN_00408fe0(
	GolString*,
	GolRenderDevice*,
	LegoS32,
	LegoS32,
	LegoS32,
	LegoS32,
	LegoFloat,
	LegoFloat,
	Rect*,
	ColorRGBA*,
	LegoS32
)
{
	STUB(0x00408fe0);
	return 0;
}

// FUNCTION: LEGORACERS 0x004092b0
LegoU32 GolFontBase::FindGlyphIndex(LegoU16 p_char)
{
	LegoS32 low = 0;
	LegoS32 high = m_glyphCount - 1;
	LegoS32 mid = static_cast<LegoU32>(m_glyphCount) >> 1;

	while (low <= high) {
		LegoU16 glyphChar = m_glyphs[mid].m_char;
		if (glyphChar == p_char) {
			break;
		}

		if (glyphChar > p_char) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}

		mid = (high + low) >> 1;
	}

	if (low > high) {
		mid = 0;
	}

	return mid;
}

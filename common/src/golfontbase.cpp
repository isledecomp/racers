#include "golfontbase.h"

#include "decomp.h"
#include "golerror.h"
#include "golstring.h"
#include "render/gold3drenderdevice.h"
#include "render/golrenderdevice.h"
#include "render/rectangle.h"
#include "surface/silverdune0x30.h"
#include "surface/slatepeak0x58.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolFontBase, 0x40)

// GLOBAL: GOLDP 0x10063bd0
// GLOBAL: LEGORACERS 0x004c2860
static LegoU8 g_glyphIndexBuffer[0x80];

// GLOBAL: GOLDP 0x10063c9c
SilverDune0x30* g_fontSourceImage;

// FUNCTION: GOLDP 0x1001dea0
GolFontBase::GolFontBase()
{
	m_surfaceCount = 0;
	m_fontHeight = 0;
	m_glyphCount = 0;
	m_glyphs = NULL;
	m_spaceWidth = 0;
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
	m_name[0] = '\0';
	m_flags = 0;
	m_charSpacing = 0;
}

// FUNCTION: GOLDP 0x1001df40
GolFontBase::~GolFontBase()
{
	Clear();
}

// FUNCTION: GOLDP 0x1001df80
void GolFontBase::CreateGlyphs(GolD3DRenderDevice* p_renderer, GolString* p_string, LegoU32 p_count)
{
	if (m_glyphs) {
		Clear();
	}

	m_glyphCount = p_count + 1;
	m_glyphs = new Glyph[m_glyphCount];

	if (!m_glyphs) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_glyphs[0].m_char = ' ';
	for (LegoU32 i = 1; i < m_glyphCount; i++) {
		m_glyphs[i].m_char = *p_string->FromCursor(i - 1);
	}

	LegoChar name[sizeof(m_name) + 1];
	::memcpy(name, m_name, sizeof(m_name));
	name[sizeof(m_name)] = '\0';

	Load(name, p_renderer);
}

// FUNCTION: GOLDP 0x1001e030
void GolFontBase::Clear()
{
	if (m_glyphs != NULL) {
		delete m_glyphs;
		m_glyphs = NULL;
	}

	m_surfaceCount = 0;
	m_fontHeight = 0;
	m_glyphCount = 0;
	m_glyphs = NULL;
	m_spaceWidth = 0;
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
}

// STUB: GOLDP 0x1001e070
void GolFontBase::Load(const LegoChar*, GolD3DRenderDevice*)
{
	// TODO
	STUB(0x1001e070);
}

// FUNCTION: GOLDP 0x1001e190
void GolFontBase::ScanGlyphs(const LegoChar* p_name)
{
	LegoU32* rowSignature = new LegoU32[m_fontHeight];
	if (rowSignature == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU8* pixels;
	LegoU32 pitch;
	g_fontSourceImage->LockPixels(&pixels, &pitch, SilverDune0x30::c_lockRequestRead);
	ReadSeparatorSignature(rowSignature, pixels, pitch);

	LegoU32 step = g_fontSourceImage->GetTextureFormat().m_bitsPerPixel >> 2;
	LegoU32 sourcePitch = pitch;
	LegoU8* sourcePixels = pixels;
	LegoU32 x = 0;
	LegoU32 pixelOffset = 0;
	LegoU8* column = sourcePixels;
	while (x < g_fontSourceImage->GetWidth()) {
		if (!IsSeparatorColumn(rowSignature, column, sourcePitch, pixelOffset & 1)) {
			break;
		}

		pixelOffset += step;
		column = sourcePixels + (pixelOffset >> 1);
		x++;
	}

	m_spaceWidth = x;
	m_glyphs[0].m_sourceX = 0;
	m_glyphs[0].m_width = static_cast<LegoU16>(m_spaceWidth);

	x++;
	for (LegoU32 i = 1; i < m_glyphCount; i++) {
		if (i != 1) {
			LegoU32 sourcePitch = pitch;
			LegoU8* sourcePixels = pixels;
			LegoU32 step = g_fontSourceImage->GetTextureFormat().m_bitsPerPixel >> 2;
			LegoU32 pixelOffset = x * step;
			LegoU8* column = sourcePixels + (pixelOffset >> 1);
			while (x < g_fontSourceImage->GetWidth()) {
				if (!IsSeparatorColumn(rowSignature, column, sourcePitch, pixelOffset & 1)) {
					break;
				}

				pixelOffset += step;
				column = sourcePixels + (pixelOffset >> 1);
				x++;
			}
		}

		LegoU32 start = x;
		m_glyphs[i].m_sourceX = static_cast<undefined2>(start);

		LegoU32 end = start;
		{
			LegoU32 sourcePitch = pitch;
			LegoU8* sourcePixels = pixels;
			LegoU32 step = g_fontSourceImage->GetTextureFormat().m_bitsPerPixel >> 2;
			LegoU32 pixelOffset = end * step;
			LegoU8* column = sourcePixels + (pixelOffset >> 1);
			while (end < g_fontSourceImage->GetWidth()) {
				if (IsSeparatorColumn(rowSignature, column, sourcePitch, pixelOffset & 1)) {
					break;
				}

				pixelOffset += step;
				column = sourcePixels + (pixelOffset >> 1);
				end++;
			}
		}

		LegoU32 glyphWidth = end - start;
		m_glyphs[i].m_width = static_cast<LegoU16>(glyphWidth);
		if (!m_glyphs[i].m_width) {
			LegoChar message[256];
			::sprintf(message, "Incomplete font image: %s\nmissing character %x\n", p_name, m_glyphs[i].m_char);
			GOL_FATALERROR_MESSAGE(message);
		}

		x += m_glyphs[i].m_width;
	}

	g_fontSourceImage->UnlockPixels();
	delete[] rowSignature;
}

// FUNCTION: GOLDP 0x1001e420
void GolFontBase::ReadSeparatorSignature(LegoU32* p_rowSignature, LegoU8* p_pixels, LegoU32 p_pitch)
{
	GolFontBase* font = this;
	LegoU16 bitsPerPixel = g_fontSourceImage->GetTextureFormat().m_bitsPerPixel;

	if (bitsPerPixel == 4) {
		LegoU32 i = 0;
		while (i < font->m_fontHeight) {
			p_rowSignature[i++] = *p_pixels & 0x0f;
			p_pixels += p_pitch;
		}
	}
	else {
		LegoU32 mask = (1 << bitsPerPixel) - 1;
		LegoU32 i = 0;
		while (i < font->m_fontHeight) {
			LegoU32 pixel = p_pixels[0] | (p_pixels[1] << 8) | (p_pixels[2] << 16) | (p_pixels[3] << 24);
			p_rowSignature[i++] = mask & pixel;
			p_pixels += p_pitch;
		}
	}
}

// FUNCTION: GOLDP 0x1001e4c0
LegoBool32 GolFontBase::IsSeparatorColumn(
	LegoU32* p_rowSignature,
	LegoU8* p_pixels,
	LegoU32 p_pitch,
	LegoBool32 p_highNibble
)
{
	GolFontBase* font = this;
	LegoU16 bitsPerPixel = g_fontSourceImage->GetTextureFormat().m_bitsPerPixel;

	if (bitsPerPixel == 4) {
		if (!p_highNibble) {
			LegoU32 i = 0;
			while (i < font->m_fontHeight) {
				LegoU32 pixel = *p_pixels & 0x0f;
				if (pixel != *p_rowSignature) {
					return FALSE;
				}

				p_pixels += p_pitch;
				i++;
				p_rowSignature++;
			}

			return TRUE;
		}

		LegoU32 i = 0;
		while (i < font->m_fontHeight) {
			LegoU32 pixel = *p_pixels >> 4;
			if (pixel != *p_rowSignature) {
				return FALSE;
			}

			p_pixels += p_pitch;
			i++;
			p_rowSignature++;
		}

		return TRUE;
	}

	LegoU32 bytesPerPixel = bitsPerPixel >> 3;
	for (LegoU32 i = 0; i < font->m_fontHeight; i++) {
		LegoU32 shift = 0;
		LegoU32 j = 0;
		while (j < bytesPerPixel) {
			if (p_pixels[j] != static_cast<LegoU8>(*p_rowSignature >> shift)) {
				return FALSE;
			}

			shift += 8;
			j++;
		}

		p_pixels += p_pitch;
		p_rowSignature++;
	}

	return TRUE;
}

// FUNCTION: GOLDP 0x1001e5e0
LegoU32 GolFontBase::PackGlyphTextures(GolD3DRenderDevice* p_renderer, GolSurfaceFormat* p_textureFormat)
{
	LegoU32 bitsPerPixel = p_textureFormat->m_bitsPerPixel;

	m_maxTextureHeight = p_renderer->GetMaximumTextureHeight(bitsPerPixel);
	if (m_maxTextureHeight > 0x100) {
		m_maxTextureHeight = 0x100;
	}

	if (p_renderer->TexturesMustBeSquare()) {
		m_maxTextureWidth = p_renderer->GetMaximumTextureWidth(bitsPerPixel);
		if (m_maxTextureWidth > 0x100) {
			m_maxTextureWidth = 0x100;
		}
	}
	else {
		m_maxTextureWidth = m_maxTextureHeight;
	}

	if (m_fontHeight > m_maxTextureHeight) {
		GOL_FATALERROR_MESSAGE("Font too tall for tallest texture height");
	}

	LegoU32 texture = 0;
	LegoU32 x = 0;
	LegoU32 y = 0;
	LegoU32 lastTextureCount = 0;
	m_surfaceCount = 0;

	for (LegoU32 i = 0; i < m_glyphCount; i++) {
		if (m_glyphs[i].m_width > m_maxTextureWidth) {
			GOL_FATALERROR_MESSAGE("Font char too wide for widest texture width");
		}

		if (x + m_glyphs[i].m_width > m_maxTextureWidth) {
			y += m_fontHeight;
			x = 0;

			if (y + m_fontHeight > m_maxTextureHeight) {
				lastTextureCount = 0;
				y = 0;
				m_surfaceCount++;
			}
		}

		m_glyphs[i].m_textureX = static_cast<undefined2>(x);
		m_glyphs[i].m_textureY = static_cast<undefined2>(y);
		x += m_glyphs[i].m_width;
		m_glyphs[i].m_surfaceIndex = static_cast<undefined2>(m_surfaceCount);
		lastTextureCount++;
	}

	m_surfaceCount++;

	LegoU32 power = 0;
	LegoU32 hasRemainder = 0;
	m_textureHeight = m_fontHeight;
	while (m_textureHeight > 1) {
		power++;
		hasRemainder |= m_textureHeight & 1;
		m_textureHeight >>= 1;
	}

	m_textureHeight = 1 << (power + hasRemainder);

	if (m_textureHeight < p_renderer->GetMinimumTextureHeight(bitsPerPixel)) {
		m_textureHeight = p_renderer->GetMinimumTextureHeight(bitsPerPixel);
	}

	m_textureWidth = m_textureHeight;
	LegoU32 packedCount = 0;
	for (;;) {
		x = 0;
		y = 0;
		packedCount = 0;

		LegoU32 startIndex = m_glyphCount - lastTextureCount;
		for (LegoU32 i = startIndex; i < m_glyphCount; i++) {
			if (m_glyphs[i].m_width > m_textureWidth) {
				break;
			}

			if (x + m_glyphs[i].m_width > m_textureWidth) {
				x = 0;
				y += m_fontHeight;

				if (y + m_fontHeight > m_textureHeight) {
					break;
				}
			}

			m_glyphs[i].m_textureX = static_cast<undefined2>(x);
			m_glyphs[i].m_textureY = static_cast<undefined2>(y);
			x += m_glyphs[i].m_width;
			packedCount++;
		}

		if (packedCount >= lastTextureCount) {
			return lastTextureCount;
		}

		m_textureHeight *= 2;
		if (m_textureHeight > p_renderer->GetMaximumTextureHeight(bitsPerPixel)) {
			m_textureHeight = p_renderer->GetMaximumTextureHeight(bitsPerPixel);
		}

		m_textureWidth *= 2;
		if (m_textureWidth > p_renderer->GetMaximumTextureWidth(bitsPerPixel)) {
			m_textureWidth = p_renderer->GetMaximumTextureWidth(bitsPerPixel);
		}
	}
}

// FUNCTION: GOLDP 0x1001e970
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
	STUB(0x00408d50);

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

// FUNCTION: LEGORACERS 0x00408fe0
undefined2 GolFontBase::FUN_00408fe0(
	GolString* p_string,
	GolRenderDevice* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_wrapWidth,
	LegoS32 p_unk0x18,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	Rect* p_rect,
	ColorRGBA* p_color,
	LegoS32 p_unk0x2c
)
{
	GolFontBase* font = this;
	LegoU8 lineBreak = TRUE;

	if (p_string->SelectionLength()) {
		p_wrapWidth = static_cast<LegoS32>(::floor(static_cast<LegoFloat>(p_wrapWidth) / p_scaleX));
		p_unk0x18 += font->m_fontHeight;
		p_unk0x18 = static_cast<LegoS32>(::ceil(static_cast<LegoFloat>(p_unk0x18) * p_scaleY));
		LegoU32 length = p_string->SelectionLength();

		if (length) {
			LegoU32 i = 0;
			while (i < length) {
				if (!lineBreak) {
					while (*p_string->FromCursor(i) == ' ') {
						i++;
					}
				}

				lineBreak = FALSE;
				LegoU32 lineStart = i;
				LegoU32 breakIndex = i;
				LegoU32 wordWidth = 0;
				LegoU32 lineWidth = 0;
				LegoU32 lastIndex = i - 1;

				while (lineWidth <= static_cast<LegoU32>(p_wrapWidth)) {
					if (i >= length) {
						break;
					}

					if (*p_string->FromCursor(i) == '\n') {
						break;
					}

					if (*p_string->FromCursor(i) == '\r') {
						break;
					}

					LegoU16 textChar = *p_string->FromCursor(i);
					LegoU32 charWidth;
					if (textChar == ' ') {
						if (wordWidth != 0 && *p_string->FromCursor(lastIndex) != ' ') {
							breakIndex = i;
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
				}

				if (lineWidth > static_cast<LegoU32>(p_wrapWidth)) {
					if (wordWidth == lineWidth) {
						breakIndex++;

						while (lineWidth > static_cast<LegoU32>(p_wrapWidth) && i > breakIndex) {
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
						i = breakIndex;
						lineWidth -= wordWidth;
					}
				}

				LegoS32 drawX = p_x;
				if (p_unk0x2c == 1 && static_cast<LegoU32>(p_wrapWidth) > lineWidth) {
					drawX += (p_wrapWidth - lineWidth) >> 1;
				}

				while (lineStart < i) {
					LegoU32 count = i - lineStart;
					if (count > sizeOfArray(g_glyphIndexBuffer)) {
						count = sizeOfArray(g_glyphIndexBuffer);
					}

					for (LegoU32 j = 0; j < count; j++) {
						LegoU16 textChar = *p_string->FromCursor(lineStart);
						g_glyphIndexBuffer[j] = static_cast<LegoU8>(font->FindGlyphIndex(textChar));
						lineStart++;
					}

					drawX = font->DrawGlyphRun(
						count,
						p_renderer,
						drawX,
						p_y,
						p_scaleX,
						p_scaleY,
						p_rect,
						reinterpret_cast<undefined4>(p_color)
					);
				}

				p_y += p_unk0x18;

				if (*p_string->FromCursor(i) == '\r') {
					i++;
					lineBreak = TRUE;
				}

				if (*p_string->FromCursor(i) == '\n') {
					i++;
					lineBreak = TRUE;
				}
			}
		}
	}

	if (FALSE) {
		return 0;
	}
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

// FUNCTION: GOLDP 0x1001eaa0
void GolFontBase::DrawString(
	const LegoChar* p_string,
	GolRenderDevice* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	Rect* p_rect,
	undefined4 p_unk0x20
)
{
	GolFontBase* font = this;
	const LegoChar* cursor = p_string;

	if (*cursor) {
		for (; *cursor;) {
			LegoU32 count = 0;
			LegoChar c = *cursor;

			for (; c && count < sizeOfArray(g_glyphIndexBuffer); count++) {
				LegoS16 textChar = c;
				LegoS32 low = 0;
				LegoS32 high = font->m_glyphCount - 1;
				LegoS32 mid = static_cast<LegoU32>(font->m_glyphCount) >> 1;

				while (low <= high) {
					LegoU16 glyphChar = font->m_glyphs[mid].m_char;
					if (glyphChar == static_cast<LegoU16>(textChar)) {
						break;
					}

					if (glyphChar > static_cast<LegoU16>(textChar)) {
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

				g_glyphIndexBuffer[count] = static_cast<LegoU8>(mid);
				cursor++;
				c = *cursor;
			}

			p_x = font->DrawGlyphRun(count, p_renderer, p_x, p_y, p_scaleX, p_scaleY, p_rect, p_unk0x20);

			if (!*cursor) {
				return;
			}
		}
	}
}

// FUNCTION: GOLDP 0x1001eb70
LegoS32 GolFontBase::DrawString(
	GolString* p_string,
	GolRenderDevice* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	Rect* p_rect,
	undefined4 p_unk0x20
)
{
	GolFontBase* font = this;
	GolString* string = p_string;
	if (string->SelectionLength()) {
		LegoU32 length = string->SelectionLength();
		LegoU32 offset = 0;

		while (length > 0) {
			LegoU32 count;
			if (length > sizeOfArray(g_glyphIndexBuffer)) {
				count = sizeOfArray(g_glyphIndexBuffer);
				length -= count;
			}
			else {
				count = length;
				length = 0;
			}

			for (LegoU32 i = 0; i < count; i++) {
				LegoU16 textChar = *string->FromCursor(offset + i);
				LegoS32 low = 0;
				LegoS32 high = font->m_glyphCount - 1;
				LegoS32 mid = static_cast<LegoU32>(font->m_glyphCount) >> 1;

				while (low <= high) {
					LegoU16 glyphChar = font->m_glyphs[mid].m_char;
					if (glyphChar == textChar) {
						break;
					}

					if (glyphChar > textChar) {
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

				g_glyphIndexBuffer[i] = static_cast<LegoU8>(mid);
			}

			p_x = font->DrawGlyphRun(count, p_renderer, p_x, p_y, p_scaleX, p_scaleY, p_rect, p_unk0x20);
			offset += count;

			if (length > 0) {
				continue;
			}

			return p_x;
		}
	}
}

// FUNCTION: GOLDP 0x1001eca0
LegoS32 GolFontBase::DrawStringFitted(
	GolString* p_string,
	GolRenderDevice* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	Rect* p_rect,
	undefined4 p_unk0x20
)
{
	if (p_string->SelectionLength()) {
		LegoS32 width;
		MeasureString(p_string, &width, NULL);

		return DrawString(
			p_string,
			p_renderer,
			p_x,
			p_y,
			p_scaleX / static_cast<LegoFloat>(width),
			p_scaleY / static_cast<LegoFloat>(m_fontHeight),
			p_rect,
			p_unk0x20
		);
	}
}

// FUNCTION: GOLDP 0x1001ed00
// FUNCTION: LEGORACERS 0x00409300
LegoS32 GolFontBase::DrawGlyphRun(
	LegoU32 p_count,
	GolRenderDevice* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	Rect* p_rect,
	undefined4 p_unk0x20
)
{
	LegoS32 result = 0;
	GolFontBase* font = this;

	if (p_scaleX <= 0.0f) {
		return p_x;
	}

	if (p_scaleY <= 0.0f) {
		return p_x;
	}

	Rect clipRect;
	if (!font->ComputeClipRect(p_renderer, p_rect, &clipRect)) {
		return p_x;
	}

	if (p_x > clipRect.m_right) {
		return p_x;
	}

	if (p_y > clipRect.m_bottom) {
		return p_x;
	}

	LegoS32 bottom = p_y + static_cast<LegoS32>(static_cast<LegoFloat>(font->m_fontHeight) * p_scaleY);
	if (bottom < clipRect.m_top) {
		return p_x;
	}

	LegoFloat spacing = static_cast<LegoFloat>(font->m_charSpacing) * p_scaleX;
	LegoFloat inverseScaleX = 1.0f / p_scaleX;
	LegoFloat inverseScaleY = 1.0f / p_scaleY;

	font->VTable0x0c(p_renderer, p_count);

	for (LegoU32 surface = 0; surface < font->m_surfaceCount; surface++) {
		LegoFloat currentFloatX = static_cast<LegoFloat>(p_x);
		LegoBool32 selectedSurface = FALSE;
		result = p_x;

		for (LegoU32 i = 0; i < p_count; i++) {
			LegoU8 glyphIndex = g_glyphIndexBuffer[i];
			Rect destRect;
			destRect.m_left = result;

			if (result >= clipRect.m_right) {
				break;
			}

			Glyph* glyph = &font->m_glyphs[glyphIndex];
			LegoS32 glyphWidth = glyph->m_width;
			LegoFloat scaledWidth = static_cast<LegoFloat>(glyphWidth) * p_scaleX;
			LegoS32 right = result + static_cast<LegoS32>(scaledWidth);
			destRect.m_right = right;

			currentFloatX += scaledWidth;
			currentFloatX += spacing;
			result = static_cast<LegoS32>(currentFloatX);

			if (glyph->m_surfaceIndex == surface && right >= clipRect.m_left) {
				destRect.m_top = p_y;
				destRect.m_bottom = bottom;

				Rect sourceRect;
				sourceRect.m_left = glyph->m_textureX;
				sourceRect.m_top = glyph->m_textureY;
				sourceRect.m_right = glyph->m_textureX + glyph->m_width;
				sourceRect.m_bottom = glyph->m_textureY + font->m_fontHeight;

				font->ClipRects(&clipRect, &sourceRect, &destRect, inverseScaleX, inverseScaleY);

				if (!selectedSurface) {
					font->SelectSurface(surface);
					selectedSurface = TRUE;
				}

				font->VTable0x14(&sourceRect, &destRect);
			}
		}
	}

	font->VTable0x18();
	return result;
}

// FUNCTION: GOLDP 0x1001ef60
// FUNCTION: LEGORACERS 0x00409560
LegoBool32 GolFontBase::ComputeClipRect(GolRenderDevice* p_renderer, Rect* p_rect, Rect* p_result)
{
	Rect* result = p_result;

	if (p_rect == NULL) {
		result->m_left = 0;
		result->m_right = p_renderer->GetRenderTargetInfo()->GetWidth();
		result->m_top = 0;
		result->m_bottom = p_renderer->GetRenderTargetInfo()->GetHeight();
		return TRUE;
	}

	if (p_rect->m_right <= 0) {
		return FALSE;
	}

	if (p_rect->m_left >= p_renderer->GetRenderTargetInfo()->GetWidth()) {
		return FALSE;
	}

	if (p_rect->m_bottom <= 0) {
		return FALSE;
	}

	if (p_rect->m_top >= p_renderer->GetRenderTargetInfo()->GetHeight()) {
		return FALSE;
	}

	LegoS32 left = p_rect->m_left;
	result->m_left = left < 0 ? 0 : left;

	if (p_rect->m_top < 0) {
		result->m_top = 0;
	}
	else {
		result->m_top = p_rect->m_top;
	}

	if (p_rect->m_right > p_renderer->GetRenderTargetInfo()->GetWidth()) {
		result->m_right = p_renderer->GetRenderTargetInfo()->GetWidth();
	}
	else {
		result->m_right = p_rect->m_right;
	}

	if (p_rect->m_bottom > p_renderer->GetRenderTargetInfo()->GetHeight()) {
		result->m_bottom = p_renderer->GetRenderTargetInfo()->GetHeight();
	}
	else {
		result->m_bottom = p_rect->m_bottom;
	}

	return TRUE;
}

// FUNCTION: GOLDP 0x1001f090
// FUNCTION: LEGORACERS 0x00409690
void GolFontBase::ClipRects(
	Rect* p_clipRect,
	Rect* p_sourceRect,
	Rect* p_destRect,
	LegoFloat p_inverseScaleX,
	LegoFloat p_inverseScaleY
)
{
	LegoS32 delta;

	if (p_clipRect->m_bottom < p_destRect->m_bottom) {
		delta = p_destRect->m_bottom - p_clipRect->m_bottom;
		p_destRect->m_bottom -= delta;
		p_sourceRect->m_bottom -= static_cast<LegoS32>(static_cast<LegoFloat>(delta) * p_inverseScaleY);
	}

	if (p_clipRect->m_top > p_destRect->m_top) {
		delta = p_clipRect->m_top - p_destRect->m_top;
		p_destRect->m_top += delta;
		p_sourceRect->m_top += static_cast<LegoS32>(static_cast<LegoFloat>(delta) * p_inverseScaleY);
	}

	if (p_clipRect->m_right < p_destRect->m_right) {
		delta = p_destRect->m_right - p_clipRect->m_right;
		p_destRect->m_right -= delta;
		p_sourceRect->m_right -= static_cast<LegoS32>(static_cast<LegoFloat>(delta) * p_inverseScaleX);
	}

	if (p_clipRect->m_left > p_destRect->m_left) {
		delta = p_clipRect->m_left - p_destRect->m_left;
		p_destRect->m_left += delta;
		p_sourceRect->m_left += static_cast<LegoS32>(static_cast<LegoFloat>(delta) * p_inverseScaleX);
	}
}

// FUNCTION: GOLDP 0x1001f140
LegoS32 __cdecl GolFontBase::CompareGlyphChars(const void* p_left, const void* p_right)
{
	LegoU16 left = *static_cast<const LegoU16*>(p_left);
	LegoU16 right = *static_cast<const LegoU16*>(p_right);

	if (left > right) {
		return 1;
	}

	LegoS16 difference = left;
	difference -= right;
	return difference ? -1 : 0;
}

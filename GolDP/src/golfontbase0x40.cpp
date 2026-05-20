#include "golfontbase0x40.h"

#include "bronzefalcon0xc8770.h"
#include "decomp.h"
#include "golerror.h"
#include "golstring.h"
#include "rectangle.h"
#include "slatepeak0x58.h"
#include "whitefalcon0x140.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolFontBase0x40, 0x40)

// GLOBAL: GOLDP 0x10063bd0
static LegoU8 g_unk0x10063bd0[0x80];

// FUNCTION: GOLDP 0x1001dea0
GolFontBase0x40::GolFontBase0x40()
{
	m_unk0x04 = 0;
	m_unk0x1c = 0;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_unk0x18 = 0;
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
	m_name[0] = '\0';
	m_unk0x2c = 0;
	m_unk0x20 = 0;
}

// FUNCTION: GOLDP 0x1001df40
GolFontBase0x40::~GolFontBase0x40()
{
	Clear();
}

// FUNCTION: GOLDP 0x1001df80
void GolFontBase0x40::FUN_1001df80(BronzeFalcon0xc8770* p_renderer, GolString* p_string, LegoU32 p_count)
{
	if (m_unk0x28) {
		Clear();
	}

	m_unk0x24 = p_count + 1;
	m_unk0x28 = new Glyph0x0c[m_unk0x24];

	if (!m_unk0x28) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x28[0].m_char = ' ';
	for (LegoU32 i = 1; i < m_unk0x24; i++) {
		m_unk0x28[i].m_char = *p_string->FromCursor(i - 1);
	}

	LegoChar name[sizeof(m_name) + 1];
	::memcpy(name, m_name, sizeof(m_name));
	name[sizeof(m_name)] = '\0';

	VTable0x00(name, p_renderer);
}

// FUNCTION: GOLDP 0x1001e030
void GolFontBase0x40::Clear()
{
	if (m_unk0x28 != NULL) {
		delete m_unk0x28;
		m_unk0x28 = NULL;
	}

	m_unk0x04 = 0;
	m_unk0x1c = 0;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_unk0x18 = 0;
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
}

// STUB: GOLDP 0x1001e070
void GolFontBase0x40::VTable0x00(const LegoChar*, BronzeFalcon0xc8770*)
{
	// TODO
	STUB(0x1001e070);
}

// FUNCTION: GOLDP 0x1001e970
void GolFontBase0x40::FUN_1001e970(GolString* p_string, LegoS32* p_width, LegoS32* p_height)
{
	GolFontBase0x40* font = this;

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
		*p_height = font->m_unk0x1c;
	}

	if (p_width != NULL) {
		LegoS32 width = 0;
		LegoU32 length = p_string->SelectionLength();

		for (LegoU32 i = 0; i < length; i++) {
			if (*p_string->FromCursor(i) == ' ') {
				width += font->m_unk0x20 + font->m_unk0x18;
			}
			else {
				LegoU16 textChar = *p_string->FromCursor(i);
				LegoS32 low = 0;
				LegoS32 high = font->m_unk0x24 - 1;
				LegoS32 mid = static_cast<LegoU32>(font->m_unk0x24) >> 1;

				while (low <= high) {
					LegoU16 glyphChar = font->m_unk0x28[mid].m_char;
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

				width += font->m_unk0x28[mid].m_width + font->m_unk0x20;
			}
		}

		width -= font->m_unk0x20;

		*p_width = width < 0 ? 0 : width;
	}
}

// FUNCTION: GOLDP 0x1001eaa0
void GolFontBase0x40::FUN_1001eaa0(
	const LegoChar* p_string,
	WhiteFalcon0x140* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	Rect* p_rect,
	undefined4 p_unk0x20
)
{
	GolFontBase0x40* font = this;
	const LegoChar* cursor = p_string;

	if (*cursor) {
		for (; *cursor;) {
			LegoU32 count = 0;
			LegoChar c = *cursor;

			for (; c && count < sizeOfArray(g_unk0x10063bd0); count++) {
				LegoS16 textChar = c;
				LegoS32 low = 0;
				LegoS32 high = font->m_unk0x24 - 1;
				LegoS32 mid = static_cast<LegoU32>(font->m_unk0x24) >> 1;

				while (low <= high) {
					LegoU16 glyphChar = font->m_unk0x28[mid].m_char;
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

				g_unk0x10063bd0[count] = static_cast<LegoU8>(mid);
				cursor++;
				c = *cursor;
			}

			p_x = font->FUN_1001ed00(count, p_renderer, p_x, p_y, p_scaleX, p_scaleY, p_rect, p_unk0x20);

			if (!*cursor) {
				return;
			}
		}
	}
}

// FUNCTION: GOLDP 0x1001eb70
LegoS32 GolFontBase0x40::FUN_1001eb70(
	GolString* p_string,
	WhiteFalcon0x140* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	Rect* p_rect,
	undefined4 p_unk0x20
)
{
	GolFontBase0x40* font = this;
	GolString* string = p_string;
	if (string->SelectionLength()) {
		LegoU32 length = string->SelectionLength();
		LegoU32 offset = 0;

		while (length > 0) {
			LegoU32 count;
			if (length > sizeOfArray(g_unk0x10063bd0)) {
				count = sizeOfArray(g_unk0x10063bd0);
				length -= count;
			}
			else {
				count = length;
				length = 0;
			}

			for (LegoU32 i = 0; i < count; i++) {
				LegoU16 textChar = *string->FromCursor(offset + i);
				LegoS32 low = 0;
				LegoS32 high = font->m_unk0x24 - 1;
				LegoS32 mid = static_cast<LegoU32>(font->m_unk0x24) >> 1;

				while (low <= high) {
					LegoU16 glyphChar = font->m_unk0x28[mid].m_char;
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

				g_unk0x10063bd0[i] = static_cast<LegoU8>(mid);
			}

			p_x = font->FUN_1001ed00(count, p_renderer, p_x, p_y, p_scaleX, p_scaleY, p_rect, p_unk0x20);
			offset += count;

			if (length > 0) {
				continue;
			}

			return p_x;
		}
	}
}

// FUNCTION: GOLDP 0x1001eca0
LegoS32 GolFontBase0x40::FUN_1001eca0(
	GolString* p_string,
	WhiteFalcon0x140* p_renderer,
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
		FUN_1001e970(p_string, &width, NULL);

		return FUN_1001eb70(
			p_string,
			p_renderer,
			p_x,
			p_y,
			p_scaleX / static_cast<LegoFloat>(width),
			p_scaleY / static_cast<LegoFloat>(m_unk0x1c),
			p_rect,
			p_unk0x20
		);
	}
}

// FUNCTION: GOLDP 0x1001ed00
LegoS32 GolFontBase0x40::FUN_1001ed00(
	LegoU32 p_count,
	WhiteFalcon0x140* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	Rect* p_rect,
	undefined4 p_unk0x20
)
{
	LegoS32 result = 0;
	GolFontBase0x40* font = this;

	if (p_scaleX <= 0.0f) {
		return p_x;
	}

	if (p_scaleY <= 0.0f) {
		return p_x;
	}

	Rect clipRect;
	if (!font->FUN_1001ef60(p_renderer, p_rect, &clipRect)) {
		return p_x;
	}

	if (p_x > clipRect.m_right) {
		return p_x;
	}

	if (p_y > clipRect.m_bottom) {
		return p_x;
	}

	LegoS32 bottom = p_y + static_cast<LegoS32>(static_cast<LegoFloat>(font->m_unk0x1c) * p_scaleY);
	if (bottom < clipRect.m_top) {
		return p_x;
	}

	LegoFloat spacing = static_cast<LegoFloat>(font->m_unk0x20) * p_scaleX;
	LegoFloat inverseScaleX = 1.0f / p_scaleX;
	LegoFloat inverseScaleY = 1.0f / p_scaleY;

	font->VTable0x0c(p_renderer, p_count);

	for (LegoU32 surface = 0; surface < font->m_unk0x04; surface++) {
		LegoFloat currentFloatX = static_cast<LegoFloat>(p_x);
		LegoBool32 selectedSurface = FALSE;
		result = p_x;

		for (LegoU32 i = 0; i < p_count; i++) {
			LegoU8 glyphIndex = g_unk0x10063bd0[i];
			Rect destRect;
			destRect.m_left = result;

			if (result >= clipRect.m_right) {
				break;
			}

			Glyph0x0c* glyph = &font->m_unk0x28[glyphIndex];
			LegoS32 glyphWidth = glyph->m_width;
			LegoFloat scaledWidth = static_cast<LegoFloat>(glyphWidth) * p_scaleX;
			LegoS32 right = result + static_cast<LegoS32>(scaledWidth);
			destRect.m_right = right;

			currentFloatX += scaledWidth;
			currentFloatX += spacing;
			result = static_cast<LegoS32>(currentFloatX);

			if (glyph->m_unk0x04 == surface && right >= clipRect.m_left) {
				destRect.m_top = p_y;
				destRect.m_bottom = bottom;

				Rect sourceRect;
				sourceRect.m_left = glyph->m_unk0x06;
				sourceRect.m_top = glyph->m_unk0x08;
				sourceRect.m_right = glyph->m_unk0x06 + glyph->m_width;
				sourceRect.m_bottom = glyph->m_unk0x08 + font->m_unk0x1c;

				font->FUN_1001f090(&clipRect, &sourceRect, &destRect, inverseScaleX, inverseScaleY);

				if (!selectedSurface) {
					font->VTable0x10(surface);
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
LegoBool32 GolFontBase0x40::FUN_1001ef60(WhiteFalcon0x140* p_renderer, Rect* p_rect, Rect* p_result)
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
void GolFontBase0x40::FUN_1001f090(
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

#include "race/racedialog.h"

#include "golfontbase.h"
#include "golstringtable.h"
#include "render/gold3drenderdevice.h"
#include "surface/golrendertarget.h"

DECOMP_SIZE_ASSERT(RaceDialog, 0x68)

extern LegoFloat g_cosineTable[1024];
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_twoPi;

// FUNCTION: LEGORACERS 0x00427160
RaceDialog::RaceDialog()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004271d0
RaceDialog::~RaceDialog()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00427240
void RaceDialog::Destroy()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_options); i++) {
		m_options[i].Reset();
	}

	m_prompt.Reset();
	m_extra.Reset();
	Reset();
}

// FUNCTION: LEGORACERS 0x00427290
void RaceDialog::Reset()
{
	m_selecting = 1;
	m_font = NULL;
	m_renderer = NULL;
	m_stringTable = NULL;
	m_state = 0;
	m_selectionIndex = 0;
	m_blinkMs = 0;
	m_optionsTop = 0;
	m_lineHeight = 0;
	m_acceptKey = 0;
}

// FUNCTION: LEGORACERS 0x004272c0
void RaceDialog::Initialize(
	GolFontBase* p_font,
	GolD3DRenderDevice* p_renderer,
	GolStringTable* p_stringTable,
	LegoU32 p_keyCode
)
{
	if (m_font) {
		Destroy();
	}

	m_renderer = p_renderer;
	m_font = p_font;
	m_stringTable = p_stringTable;
	m_acceptKey = p_keyCode;

	if (p_keyCode == c_keyboardPrevious || p_keyCode == c_keyboardNext) {
		m_acceptKey = c_keyboardEnter;
	}
}

// FUNCTION: LEGORACERS 0x00427310
void RaceDialog::Open(
	LegoU32 p_optionCount,
	const LegoU16* p_optionStringIds,
	LegoU16 p_promptStringId,
	LegoU16 p_extraStringId,
	LegoU32 p_selectionIndex
)
{
	LegoS32 textHeight;
	const GolRenderTarget* renderTargetInfo = m_renderer->GetRenderTargetInfo();
	LegoS32 textWidth;
	LegoU32 i;

	for (i = 0; i < p_optionCount; i++) {
		m_options[i].CopyFromBufSelection(m_stringTable->GetStringBuffer(p_optionStringIds[i]), 0);
	}

	m_prompt.CopyFromBufSelection(m_stringTable->GetStringBuffer(p_promptStringId), 0);

	if (p_extraStringId != 0xffff) {
		m_extra.CopyFromBufSelection(m_stringTable->GetStringBuffer(p_extraStringId), 0);
	}
	else {
		m_extra.Reset();
	}

	m_optionCount = p_optionCount;
	m_state = 1;
	m_selectionIndex = p_selectionIndex;
	m_selecting = 1;
	m_lineHeight = 0;

	i = 0;
	if (p_optionCount > i) {
		GolString* option = m_options;
		do {
			m_font->MeasureString(option, &textWidth, &textHeight);

			if (static_cast<LegoU32>(textHeight) > static_cast<LegoU32>(m_lineHeight)) {
				m_lineHeight = textHeight;
			}

			i++;
			option++;
		} while (i < m_optionCount);
	}

	m_lineHeight += 2;
	m_optionsTop = renderTargetInfo->GetHeight() / 2 - (m_optionCount * m_lineHeight) / 2;
}

// FUNCTION: LEGORACERS 0x00427420
void RaceDialog::Update(LegoU32 p_elapsedMs)
{
	m_blinkMs += p_elapsedMs;
	if (m_blinkMs >= 500) {
		m_blinkMs = 0;
	}
}

// STUB: LEGORACERS 0x00427440
void RaceDialog::Draw()
{
	if (m_state != 1) {
		return;
	}

	const GolRenderTarget* renderTargetInfo = m_renderer->GetRenderTargetInfo();
	DrawBackdrop();

	LegoS32 selectedAlpha = c_selectedAlpha;
	if (m_selecting) {
		LegoS32 index =
			0xffffff00 -
			static_cast<LegoS32>(static_cast<LegoFloat>(m_blinkMs) * 0.002f * g_twoPi * g_negativeRadiansToTableIndex);
		index &= c_cosineTableMask;
		selectedAlpha = c_selectedPulseAlphaCenter -
						static_cast<LegoS32>(g_cosineTable[index] * (int) c_selectedPulseAlphaAmplitude);
	}

	m_font->SetColor(c_promptColor);

	LegoS32 y = m_optionsTop - m_lineHeight;
	if (m_extra.HasChars()) {
		y -= m_lineHeight >> 1;
	}

	LegoS32 textWidth;
	LegoS32 textHeight;
	m_font->MeasureString(&m_prompt, &textWidth, &textHeight);
	m_renderer->DrawString(
		&m_prompt,
		m_font,
		(renderTargetInfo->GetWidth() >> 1) - (static_cast<LegoU32>(textWidth) >> 1),
		y,
		1.0f,
		1.0f,
		NULL,
		0
	);

	y += m_lineHeight;
	if (m_extra.HasChars()) {
		m_font->MeasureString(&m_extra, &textWidth, &textHeight);
		m_renderer->DrawString(
			&m_extra,
			m_font,
			(renderTargetInfo->GetWidth() >> 1) - (static_cast<LegoU32>(textWidth) >> 1),
			y,
			1.0f,
			1.0f,
			NULL,
			0
		);
		y += m_lineHeight;
	}

	for (LegoU32 i = 0; i < m_optionCount; i++) {
		GolString* option = &m_options[i];
		m_font->MeasureString(option, &textWidth, &textHeight);

		LegoS32 x = (renderTargetInfo->GetWidth() >> 1) - (static_cast<LegoU32>(textWidth) >> 1);
		if (m_selecting && m_selectionIndex == i) {
			m_font->SetColor(c_selectedColor);
			m_renderer->SetAlphaOverride(selectedAlpha, c_selectedAlphaFlag);

			if (m_blinkMs < c_selectedBlinkThresholdMs) {
				m_renderer->DrawString(option, m_font, x, y, 1.0f, 1.0f, NULL, 0);
			}

			m_renderer->ClearAlphaOverride();
		}
		else {
			m_font->SetColor(c_optionColor);
			m_renderer->DrawString(option, m_font, x, y, 1.0f, 1.0f, NULL, 0);
		}

		y += m_lineHeight;
	}

	m_font->SetColor(c_promptColor);
}

// FUNCTION: LEGORACERS 0x004276c0
void RaceDialog::DrawBackdrop()
{
	m_renderer->SetAlphaOverride(c_backdropAlpha, c_backdropAlphaFlag);

	Rect renderTargetRect;
	GolRenderDevice::TexturedVertex topLeft;
	GolRenderDevice::TexturedVertex bottomRight;
	GolRenderDevice::TexturedVertex bottomLeft;
	GolRenderDevice::TexturedVertex topRight;

	renderTargetRect.m_bottom = m_renderer->GetRenderTargetInfo()->GetHeight();
	renderTargetRect.m_right = m_renderer->GetRenderTargetInfo()->GetWidth();

	LegoFloat bottom = static_cast<LegoFloat>(renderTargetRect.m_bottom);
	bottomLeft.m_y = bottom;

	LegoFloat right = static_cast<LegoFloat>(renderTargetRect.m_right);
	topRight.m_x = right;
	bottomRight.m_x = right;
	bottomRight.m_y = bottom;

	topLeft.m_x = 0.0f;
	topLeft.m_y = 0.0f;
	topLeft.m_z = 0.0f;
	topLeft.m_u = 0.0f;
	topLeft.m_v = 0.0f;
	topLeft.m_color.m_red = 0;
	topLeft.m_color.m_grn = 0;
	topLeft.m_color.m_blu = 0;
	topLeft.m_color.m_alp = c_backdropAlpha;

	bottomLeft.m_x = 0.0f;
	bottomLeft.m_z = 0.0f;
	bottomLeft.m_u = 0.0f;
	bottomLeft.m_v = 0.0f;
	bottomLeft.m_color.m_red = 0;
	bottomLeft.m_color.m_grn = 0;
	bottomLeft.m_color.m_blu = 0;
	bottomLeft.m_color.m_alp = c_backdropAlpha;

	topRight.m_y = 0.0f;
	topRight.m_z = 0.0f;
	topRight.m_u = 0.0f;
	topRight.m_v = 0.0f;
	topRight.m_color.m_red = 0;
	topRight.m_color.m_grn = 0;
	topRight.m_color.m_blu = 0;
	topRight.m_color.m_alp = c_backdropAlpha;

	bottomRight.m_z = 0.0f;
	bottomRight.m_u = 0.0f;
	bottomRight.m_v = 0.0f;
	bottomRight.m_color.m_red = 0;
	bottomRight.m_color.m_grn = 0;
	bottomRight.m_color.m_blu = 0;
	bottomRight.m_color.m_alp = c_backdropAlpha;

	m_renderer->DrawTriangle(&bottomLeft, &topLeft, &bottomRight, NULL, 0);
	m_renderer->DrawTriangle(&bottomRight, &topLeft, &topRight, NULL, 0);
	m_renderer->ClearAlphaOverride();
}

// FUNCTION: LEGORACERS 0x00427810
void RaceDialog::OnKeyDown(LegoU32 p_keyCode)
{
	LegoU32 keyCode;
	LegoU32 selectionIndex;

	if (m_state != 1) {
		return;
	}

	if (!m_selecting) {
		return;
	}

	keyCode = p_keyCode;

	switch (keyCode) {
	case c_keyboardEnter:
	case c_keyboardSpace:
	case c_joystickButton13:
	case c_joystickButton14:
	case c_joystickButton15:
		m_selecting = 0;
		break;
	case c_keyboardPrevious:
	case c_joystickButton4:
	case c_joystickButton11:
	case c_joystickAxisNegative:
		selectionIndex = m_selectionIndex;
		if (!selectionIndex) {
			selectionIndex = m_optionCount;
		}
		selectionIndex--;
		m_selectionIndex = selectionIndex;
		break;
	case c_keyboardNext:
	case c_joystickButton6:
	case c_joystickButton10:
	case c_joystickAxisPositive:
		selectionIndex = m_selectionIndex;
		selectionIndex++;
		if (selectionIndex == m_optionCount) {
			selectionIndex = 0;
		}
		m_selectionIndex = selectionIndex;
		break;
	}

	if (keyCode == m_acceptKey) {
		m_selecting = 0;
	}
}

// FUNCTION: LEGORACERS 0x004278c0
void RaceDialog::OnKeyUp(LegoU32 p_keyCode)
{
	if (p_keyCode == c_keyboardEnter || p_keyCode == c_keyboardSpace || p_keyCode == c_joystickButton13 ||
		p_keyCode == c_joystickButton15 || p_keyCode == c_joystickButton14 || p_keyCode == m_acceptKey) {
		if (!m_selecting) {
			m_state = 2;
		}
	}
}

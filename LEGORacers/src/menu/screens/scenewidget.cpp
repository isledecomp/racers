#include "audio/soundgroupbinding.h"
#include "golerror.h"
#include "input/inputdevice.h"
#include "menu/screens/menuscenescreen.h"
#include "render/gold3drenderdevice.h"
#include "surface/golrendertarget.h"

DECOMP_SIZE_ASSERT(MenuSceneScreen::SceneWidget, 0x2d0)

// Keep this fold pair out of the unrelated MenuWidget null-return fold group.
#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
MenuWidget* MenuSceneScreen::SceneWidget::OnCursorEvent(void*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x00466a10
MenuSceneScreen::SceneWidget::SceneWidget()
{
	ResetState();
}

// FUNCTION: LEGORACERS 0x00466aa0
MenuSceneScreen::SceneWidget::~SceneWidget()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00466b10
void MenuSceneScreen::SceneWidget::ResetState()
{
	m_skippable = TRUE;
	m_frameIndex = 0;
	m_frame = NULL;
	m_autoAdvance = 0;
	m_finished = FALSE;
	m_viewportRect.m_top = 0;
	m_viewportRect.m_bottom = 0;
	m_viewportRect.m_left = 0;
	m_viewportRect.m_right = 0;
}

// FUNCTION: LEGORACERS 0x00466b50
undefined4 MenuSceneScreen::SceneWidget::Create(SceneRefBinding* p_createParams, undefined4 p_binary)
{
	if (m_flags & 1) {
		Destroy();
	}

	if (CreateWidget(p_createParams)) {
		LoadCutscene(p_createParams, p_binary);
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00466b90
void MenuSceneScreen::SceneWidget::ComputeViewportRect()
{
	const GolRenderTarget* renderTarget = m_renderer->GetRenderTargetInfo();
	Rect rect = *GetGlobalRect();

	if (rect.m_left < 0) {
		rect.m_left = 0;
	}

	if (rect.m_right > renderTarget->GetWidth()) {
		rect.m_right = renderTarget->GetWidth();
	}

	if (rect.m_top < 0) {
		rect.m_top = 0;
	}

	if (rect.m_bottom > renderTarget->GetHeight()) {
		rect.m_bottom = renderTarget->GetHeight();
	}

	m_viewportRect = rect;
}

// FUNCTION: LEGORACERS 0x00466bf0
void MenuSceneScreen::SceneWidget::LoadCutscene(SceneRefBinding* p_createParams, undefined4 p_binary)
{
	ComputeViewportRect();
	m_definition.Load(m_golExport, m_renderer, p_createParams->m_cutsceneName, p_binary);

	if (!m_definition.GetFrameCount()) {
		GOL_FATALERROR_MESSAGE("Invalid cinema file, at least 1 cinema is required");
	}

	m_player.Load(
		m_golExport,
		m_renderer,
		p_createParams->m_soundGroupBinding->GetSoundManager(),
		&m_definition,
		p_createParams->m_cutsceneName,
		p_binary
	);
	m_definition.SetEventSink(&m_player);

	LegoFloat scale =
		(LegoFloat) ((double) (m_viewportRect.m_right - m_viewportRect.m_left) /
					 (double) (m_viewportRect.m_bottom - m_viewportRect.m_top) * p_createParams->m_aspectScale);
	m_definition.SetCameraAspectRatios(scale);

	m_autoAdvance = p_createParams->m_autoAdvance;
	m_frameIndex = p_createParams->m_startFrameIndex;
	if (m_frameIndex >= m_definition.GetFrameCount()) {
		m_finished = TRUE;
		return;
	}

	m_frame = &m_definition.GetFrames()[m_frameIndex];
	m_frame->Play();
	m_frame->SetViewportRect(&m_viewportRect);
}

// FUNCTION: LEGORACERS 0x00466d00
void MenuSceneScreen::SceneWidget::SetFrame(CutsceneDefinition::Frame* p_frame)
{
	m_frame->Rewind();
	m_frame->Stop();
	m_frame = p_frame;
	m_frame->Rewind();
	m_frame->Play();
	m_frame->SetViewportRect(&m_viewportRect);
	m_player.StopAll();
}

// FUNCTION: LEGORACERS 0x00466d60
LegoBool32 MenuSceneScreen::SceneWidget::Destroy()
{
	m_definition.Clear();
	m_player.Clear();
	ResetState();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00466d90
undefined4 MenuSceneScreen::SceneWidget::OnEvent(undefined4 p_elapsedMs)
{
	if (m_finished) {
		return FALSE;
	}

	if (m_frame->GetFlags() & CutsceneDefinition::Frame::c_flagComplete) {
		if (m_autoAdvance && ++m_frameIndex < m_definition.GetFrameCount()) {
			m_frame = &m_definition.GetFrames()[m_frameIndex];
			m_frame->Rewind();
			m_frame->Play();
			m_player.StopAll();
		}
		else {
			m_finished = TRUE;
		}
	}

	m_frame->Update(p_elapsedMs);
	m_player.Update(p_elapsedMs);

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00466e40
MenuWidget* MenuSceneScreen::SceneWidget::DrawSelf(Rect*, Rect*)
{
	if (m_finished) {
		return NULL;
	}

	m_renderer->EnableZBuffer();
	m_frame->Draw(m_renderer, 0);
	m_player.Draw(m_renderer);
	m_player.DrawTransparent(m_renderer);
	m_player.DrawOverlay(m_renderer);
	m_renderer->SelectViewport(0);
	m_renderer->DisableZBuffer(0);

	return NULL;
}

// FUNCTION: LEGORACERS 0x00466ec0
MenuWidget* MenuSceneScreen::SceneWidget::OnKeyDown(InputEventQueue::Event* p_item, undefined4, undefined4)
{
	MenuWidget* result = this;

	if (!m_frame || m_frame->GetCurrentFrame() >= m_frame->GetPlaybackRate()) {
		if (m_skippable) {
			if (!p_item->m_isRepeat) {
				LegoU32 keySource = p_item->m_keyCode & InputDevice::c_sourceMask;
				if (keySource == InputDevice::c_sourceKeyboard || keySource == InputDevice::c_sourceMouse ||
					keySource == InputDevice::c_sourceJoystickButton) {
					m_finished = TRUE;
					return result;
				}
			}
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00466f20
MenuWidget* MenuSceneScreen::SceneWidget::OnKeyUp(InputEventQueue::Event*, undefined4, undefined4)
{
	MenuWidget* result = this;

	if ((!m_frame || m_frame->GetCurrentFrame() >= m_frame->GetPlaybackRate()) && m_skippable) {
		m_finished = TRUE;
		return result;
	}

	return NULL;
}

#include "race/powerups/colorbrick.h"

#include "audio/soundnode.h"
#include "camera/golcamera.h"
#include "golmodelbase.h"
#include "material/materialtable.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racesoundsource.h"

#include <float.h>
#include <math.h>

// GLOBAL: LEGORACERS 0x004b170c
const LegoFloat g_brickSoundMinDistance = 30.0f;

// FUNCTION: LEGORACERS 0x00457640
ColorBrick::ColorBrick()
{
	m_brickMaterial = NULL;
	m_trailMaterial = NULL;
	m_assignedColor = 3;
	m_currentColor = 3;
	m_nextColor = 3;
}

// FUNCTION: LEGORACERS 0x00457670
ColorBrick::~ColorBrick()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004576c0
void ColorBrick::SetColor(LegoU32 p_brickColor)
{
	m_assignedColor = p_brickColor;
	m_currentColor = p_brickColor;
}

// FUNCTION: LEGORACERS 0x004576d0
void ColorBrick::Respawn()
{
	PickupBrick::Respawn();
	m_nextColor = m_assignedColor;
	m_currentColor = m_assignedColor;
	m_brickMaterial = m_manager->GetBrickMaterial(&m_currentColor);
	m_trailMaterial = m_manager->GetTrailMaterial(&m_currentColor);
}

// FUNCTION: LEGORACERS 0x00457700
void ColorBrick::Destroy()
{
	PickupBrick::Destroy();
}

// FUNCTION: LEGORACERS 0x00457710
void ColorBrick::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateInactive) {
		return;
	}

	PickupBrick::Update(p_elapsedMs);

	LegoBool playSound = FALSE;
	switch (m_state) {
	case c_stateTransition:
		if (m_stateTimerMs > 250) {
			m_state = m_nextState;
			m_currentColor = m_nextColor;
			m_stateTimerMs = 0;
			m_brickMaterial = m_manager->GetBrickMaterial(&m_currentColor);
			m_trailMaterial = m_manager->GetTrailMaterial(&m_currentColor);
			SetTouchable(FALSE);

			if (m_state == c_stateActive && (m_flags & c_flagAudible)) {
				playSound = TRUE;
			}
		}
		break;
	case c_stateActive:
		if (m_stateTimerMs > 500) {
			m_state = c_stateIdle;
			m_stateTimerMs = 0;
			SetTouchable(TRUE);
		}
		break;
	case c_stateWait: {
		LegoU32 elapsedMs = m_stateTimerMs;
		if (m_respawnMs <= elapsedMs) {
			LegoU8 flags = m_flags;
			m_stateTimerMs = 0;
			m_state = c_stateActive;
			if (flags & c_flagAudible) {
				playSound = TRUE;
			}
		}
		break;
	}
	}

	if (playSound) {
		SoundVector position;
		m_worldEntity.GetPosition(&position);
		m_soundSource->PlaySpatialSoundById(c_soundRespawn, &position, g_brickSoundMinDistance, 150.0f, 1.0f, 1.0f);
	}
}

// FUNCTION: LEGORACERS 0x00457820
void ColorBrick::OnTouched(Racer* p_racer)
{
	if (m_state == c_stateIdle) {
		LegoU32 racerState = p_racer->GetHeldPowerupColor();
		p_racer->CollectColorBrick(m_currentColor);

		SoundVector position;
		m_worldEntity.GetPosition(&position);

		if (!racerState) {
			m_nextColor = m_assignedColor;
			m_nextState = c_stateWait;
			if (m_flags & c_flagAudible) {
				m_soundSource
					->PlaySpatialSoundById(c_soundCollect, &position, g_brickSoundMinDistance, 150.0f, 1.0f, 1.0f);
			}
		}
		else {
			m_nextColor = racerState;
			m_nextState = c_stateActive;
			if (m_flags & c_flagAudible) {
				m_soundSource
					->PlaySpatialSoundById(c_soundSwap, &position, g_brickSoundMinDistance, 150.0f, 1.0f, 1.0f);
			}
		}

		m_state = c_stateTransition;
		m_stateTimerMs = 0;
	}
}

// FUNCTION: LEGORACERS 0x004578e0
void ColorBrick::SetMaterials(GolMaterial* p_brickMaterial, GolMaterial* p_trailMaterial)
{
	m_brickMaterial = p_brickMaterial;
	m_trailMaterial = p_trailMaterial;
}

// FUNCTION: LEGORACERS 0x00457900
void ColorBrick::Draw(GolD3DRenderDevice* p_renderer)
{
	MaterialTable* materialTable = m_model->GetPrimaryMaterialTable();
	if (materialTable == NULL) {
		materialTable = m_model->GetModel(0)->GetMaterialTable();
	}
	materialTable->SetEntry(0, m_brickMaterial);
	PickupBrick::Draw(p_renderer);
}

// FUNCTION: LEGORACERS 0x00457930
void ColorBrick::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	MaterialTable* materialTable = m_blendModel->GetPrimaryMaterialTable();
	if (materialTable == NULL) {
		materialTable = m_blendModel->GetModel(0)->GetMaterialTable();
	}
	materialTable->SetEntry(0, m_trailMaterial);
	PickupBrick::DrawTransparent(p_renderer);
}

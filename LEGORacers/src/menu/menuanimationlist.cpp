#include "menu/menuanimationlist.h"

#include "golcamerabase.h"
#include "golerror.h"
#include "render/gold3drenderdevice.h"
#include "surface/golrendertarget.h"

DECOMP_SIZE_ASSERT(MenuAnimationList, 0x8)

// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
MenuAnimationList::MenuAnimationList()
{
	m_entries = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00494d90
MenuAnimationList::~MenuAnimationList()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00494da0
void MenuAnimationList::Reset()
{
	if (m_entries) {
		for (LegoU32 i = 0; i < m_count; i++) {
			m_entries[i].Reset();
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00494e10
void MenuAnimationList::Allocate(LegoU32 p_count)
{
	if (m_entries) {
		Reset();
	}

	if (p_count) {
		m_entries = new Entry[p_count];
		if (!m_entries) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_count = p_count;
	}
}

// FUNCTION: LEGORACERS 0x00494eb0
MenuAnimationList::Entry* MenuAnimationList::Activate(
	LegoU32 p_durationMs,
	LegoBool32 p_fadeOut,
	GolMaterial* p_material,
	const GolCameraBase* p_rectSource
)
{
	LegoU32 i = 0;
	while (i < m_count && m_entries[i].IsActive()) {
		i++;
	}

	if (i == m_count) {
		return NULL;
	}

	m_entries[i].Activate(p_durationMs, p_fadeOut, p_material, p_rectSource);
	return &m_entries[i];
}

// FUNCTION: LEGORACERS 0x00494f10
void MenuAnimationList::Deactivate(Entry* p_entry)
{
	if (p_entry->IsActive()) {
		p_entry->Deactivate();
	}
}

// FUNCTION: LEGORACERS 0x00494f30
LegoBool32 MenuAnimationList::HasActive() const
{
	for (LegoU32 i = 0; i < m_count; i++) {
		if (m_entries[i].IsActive()) {
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00494f60
void MenuAnimationList::Update(LegoU32 p_elapsedMs)
{
	for (LegoU32 i = 0; i < m_count; i++) {
		if (m_entries[i].IsActive()) {
			m_entries[i].Update(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x00494fa0
void MenuAnimationList::Draw(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_count; i++) {
		if (m_entries[i].IsActive()) {
			m_entries[i].Draw(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x00494fe0
void MenuAnimationList::DeactivateAll()
{
	LegoU32 result = m_count;

	for (LegoU32 i = 0; i < result; i++) {
		if (m_entries[i].IsActive()) {
			m_entries[i].Deactivate();
		}

		result = m_count;
	}
}

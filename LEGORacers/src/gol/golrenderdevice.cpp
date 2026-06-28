#include "render/golrenderdevice.h"

#include "font/golfont.h"
#include "font/golfontlibrary.h"
#include "golmateriallibrary.h"
#include "image/utopianpan0xa4.h"
#include "material/golimagelist.h"
#include "material/goltexturelist.h"
#include "scene/golbillboard.h"

// FUNCTION: LEGORACERS 0x00413170
GolFont* GolRenderDevice::FindFontByName(const LegoChar* p_name)
{
	GolFontLibrary* node = m_fontLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			GolFont* value = static_cast<GolFont*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004131a0
UtopianPan0xa4* GolRenderDevice::FindImageByName(const LegoChar* p_name)
{
	GolImageList* node = m_imageLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			UtopianPan0xa4* value = static_cast<UtopianPan0xa4*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004131d0
GoldDune0x38* GolRenderDevice::FindTextureByName(const LegoChar* p_name)
{
	GolTextureList* node = m_textureLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			GoldDune0x38* value = static_cast<GoldDune0x38*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00413200
DuskwindBananaRelic0x24* GolRenderDevice::FindMaterialByName(const LegoChar* p_name)
{
	GolMaterialLibrary* node = m_materialLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			DuskwindBananaRelic0x24* value = static_cast<DuskwindBananaRelic0x24*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// STUB: LEGORACERS 0x004133a0
LegoU32 GolBillboard::FUN_10029e90(
	MaterialTable0x0c* p_container,
	LegoS32 p_index,
	LegoFloat p_width,
	LegoFloat p_height,
	LegoFloat p_maxDistanceSquared
)
{
	m_positionContainer = p_container;
	m_positionIndex = static_cast<LegoU16>(p_index);
	LegoU32 result = VTable0x4c(
		static_cast<DuskwindBananaRelic0x24*>(p_container->GetPosition(p_index)),
		p_width,
		p_height,
		p_maxDistanceSquared
	);
	m_flags |= c_flagBit2;

	return result;
}

// FUNCTION: LEGORACERS 0x00415d60
LegoS32 GolViewFrustum::ClassifySphere(const GolVec3& p_center, LegoFloat p_radius) const
{
	LegoS32 insideCount = 0;
	const Plane* plane = m_planes;
	const Plane* end = m_planes + sizeOfArray(m_planes);

	for (; plane < end; plane++) {
		LegoFloat distance = plane->m_normal.m_z * p_center.m_z;
		distance += plane->m_normal.m_y * p_center.m_y;
		distance += plane->m_normal.m_x * p_center.m_x;
		distance += plane->m_distance;
		if (distance > p_radius) {
			insideCount++;
		}
		else if (distance < -p_radius) {
			return 0;
		}
	}

	if (insideCount == 6) {
		return 2;
	}
	return 1;
}

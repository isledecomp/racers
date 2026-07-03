#include "render/golrenderdevice.h"

#include "font/golfont.h"
#include "font/golfontlibrary.h"
#include "golmateriallibrary.h"
#include "image/golimage.h"
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
GolImage* GolRenderDevice::FindImageByName(const LegoChar* p_name)
{
	GolImageList* node = m_imageLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			GolImage* value = static_cast<GolImage*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004131d0
GolTexture* GolRenderDevice::FindTextureByName(const LegoChar* p_name)
{
	GolTextureList* node = m_textureLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			GolTexture* value = static_cast<GolTexture*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00413200
GolMaterial* GolRenderDevice::FindMaterialByName(const LegoChar* p_name)
{
	GolMaterialLibrary* node = m_materialLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			GolMaterial* value = static_cast<GolMaterial*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004133a0
LegoU32 GolBillboard::ConfigureFromMaterialTable(
	MaterialTable* p_container,
	LegoS32 p_index,
	LegoFloat p_width,
	LegoFloat p_height,
	LegoFloat p_maxDistanceSquared
)
{
	m_materialTable = p_container;
	m_materialIndex = static_cast<LegoU16>(p_index);
	LegoU32 result =
		Configure(static_cast<GolMaterial*>(p_container->m_entries[p_index]), p_width, p_height, p_maxDistanceSquared);
	m_flags |= c_flagMaterialAssignment;

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

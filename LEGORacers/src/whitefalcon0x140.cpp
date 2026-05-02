#include "whitefalcon0x140.h"

#include "amberhaze0x1c.h"
#include "cinderbasin0x28.h"
#include "golfont0xa0.h"
#include "hypnoticnoise0x1c.h"
#include "magentaribbon0x20.h"
#include "utopianpan0xa4.h"

// FUNCTION: LEGORACERS 0x00413170
GolFont0xa0* WhiteFalcon0x140::FindFontByName(const LegoChar* p_name)
{
	CinderBasin0x28* node = m_fontLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			GolFont0xa0* value = static_cast<GolFont0xa0*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004131a0
UtopianPan0xa4* WhiteFalcon0x140::FindImageByName(const LegoChar* p_name)
{
	HypnoticNoise0x1c* node = m_imageLists;

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
undefined4* WhiteFalcon0x140::FindTextureByName(const LegoChar* p_name)
{
	MagentaRibbon0x20* node = m_textureLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			undefined4* value = static_cast<undefined4*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00413200
undefined4* WhiteFalcon0x140::FindMaterialByName(const LegoChar* p_name)
{
	AmberHaze0x1c* node = m_materialLists;

	while (node != NULL) {
		if (node->GetNameEntries() != NULL) {
			undefined4* value = static_cast<undefined4*>(node->GetName(p_name));
			if (value != NULL) {
				return value;
			}
		}

		node = node->GetNext();
	}

	return NULL;
}

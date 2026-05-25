#ifndef SHADOWWOLF0xC_H
#define SHADOWWOLF0xC_H

#include "decomp.h"
#include "duskwindbananarelic0x24.h"
#include "golerror.h"
#include "golname.h"
#include "materialtable0x0c.h"
#include "types.h"
#include "whitefalcon0x140.h"

#include <string.h>

class GolFileParser;

class ShadowWolf0xc : public MaterialTable0x0c {
public:
	ShadowWolf0xc();
	~ShadowWolf0xc();

	void Destroy();

	void FUN_10025df0(WhiteFalcon0x140* p_renderer, undefined4);
	void FUN_10025e60(WhiteFalcon0x140* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary);
	void FUN_10025f90(WhiteFalcon0x140* p_renderer, GolFileParser& p_parser);
	LegoS32 FindEntryIndexByName(const LegoChar* p_name) const
	{
		if (m_count == 0) {
			return -1;
		}

		for (LegoU32 i = 0; i < m_count; i++) {
			DuskwindBananaRelic0x24* material = static_cast<DuskwindBananaRelic0x24*>(m_entries[i]);
			if (material != NULL && ::strncmp(p_name, material->GetName(), sizeof(GolName)) == 0) {
				return i;
			}
		}

		return -1;
	}
	void* AssignEntryByName(LegoS32 p_index, const LegoChar* p_name)
	{
		void* result = m_renderer->FindMaterialByName(p_name);
		m_entries[p_index] = result;
		if (m_entries[p_index] == NULL) {
			LegoChar message[64];
			::strncpy(message, p_name, sizeof(GolName));
			message[sizeof(GolName) - 1] = '\0';
			::strcat(message, ": Material assignment failed");
			GOL_FATALERROR_MESSAGE(message);
		}

		return result;
	}

	WhiteFalcon0x140* GetRenderer() const { return m_renderer; }
	LegoU32 GetCount() const { return m_count; }
	DuskwindBananaRelic0x24* GetMaterial(LegoU32 p_index) const
	{
		return static_cast<DuskwindBananaRelic0x24*>(m_entries[p_index]);
	}
};

#endif // SHADOWWOLF0xC_H

#ifndef DUSKWINDBANANARELIC0x24_H
#define DUSKWINDBANANARELIC0x24_H

#include "decomp.h"
#include "golname.h"
#include "types.h"

#include <string.h>

class GolRenderDevice;
class GolTexture;

// SIZE 0x04
struct GolMaterialColor {
	GolMaterialColor() {}
	GolMaterialColor(undefined4 p_arg0, undefined4 p_arg1, undefined4 p_arg2, undefined4 p_arg3)
	{
		m_red = p_arg0;
		m_grn = p_arg1;
		m_blu = p_arg2;
		m_alp = p_arg3;
	}
	undefined m_red; // 0x0
	undefined m_grn; // 0x1
	undefined m_blu; // 0x2
	undefined m_alp; // 0x3
};

// SIZE 0x14
struct GolMaterialParams {
	GolMaterialParams() {}
	GolMaterialParams(LegoU8 p_fullIntensity);

	LegoU32 m_unk0x00;
	GolTexture* m_unk0x04;
	GolMaterialColor m_ambient;
	GolMaterialColor m_diffuse;
	undefined m_unk0x10;
	undefined m_unk0x11;
	undefined m_unk0x12;
	undefined m_unk0x13;
};

// VTABLE: GOLDP 0x10057030
// SIZE 0x24
class GolMaterial {
public:
	// SIZE 0x8
	struct NameRecord {
		GolName m_name; // 0x0
	};

	enum {
		c_flagBit0 = 1 << 0,
		c_flagBit7 = 1 << 7,
		c_flagBit8 = 1 << 8,
		c_flagBit9 = 1 << 9,
		c_flagBit11 = 1 << 11,
		c_flagBit12 = 1 << 12,
		c_flagBit14 = 1 << 14,
	};

	enum {
		c_flag0x08Bit1 = 1 << 1,
		c_flag0x08Bit2 = 1 << 2,
		c_flag0x08Bit3 = 1 << 3,
		c_flag0x08Bit4 = 1 << 4,
		c_flag0x08Bit5 = 1 << 5,
		c_flag0x08Bit6 = 1 << 6,
		c_flag0x08Bit7 = 1 << 7,
		c_flag0x08Bit8 = 1 << 8,
		c_flag0x08Bit9 = 1 << 9,
		c_flag0x08Bit10 = 1 << 10,
		c_flag0x08Bit11 = 1 << 11,
		c_flag0x08Bit12 = 1 << 12,
		c_flag0x08Bit13 = 1 << 13,
		c_flag0x08Bit14 = 1 << 14,
		c_flag0x08Bit15 = 1 << 15,
		c_flag0x08Bit16 = 1 << 16,
		c_flag0x08Bit17 = 1 << 17,
		c_flag0x08Bit18 = 1 << 18,
		c_flag0x08Bit19 = 1 << 19,
		c_flag0x08Bit20 = 1 << 20,
		c_flag0x08Bit21 = 1 << 21,
		c_flag0x08Bit22 = 1 << 22,
	};

	GolMaterial();
	virtual ~GolMaterial(); // vtable+0x00

	GolTexture* GetUnk0x04() const { return m_unk0x04; }
	LegoU32 GetUnk0x08() const { return m_unk0x08; }
	const GolMaterialColor& GetDiffuse() const { return m_diffuse; }
	const GolMaterialColor& GetAmbient() const { return m_ambient; }
	undefined GetAlphaFunc() const { return m_unk0x20; }
	undefined GetAlphaRef() const { return m_unk0x21; }
	undefined GetSrcBlend() const { return m_unk0x22; }
	undefined GetDestBlend() const { return m_unk0x23; }
	const LegoChar* GetName() const { return m_unk0x18.m_name; }
	const GolMaterial::NameRecord& GetNameRecord() const { return m_unk0x18; }
	void SetName(const LegoChar* p_name) { ::memcpy(m_unk0x18.m_name, p_name, sizeof(GolName)); }
	void SetUnk0x14(void* p_unk0x14) { m_unk0x14 = p_unk0x14; }
	void EnableFlag0x08Bit18() { m_unk0x08 |= c_flag0x08Bit18; }

	// SYNTHETIC: GOLDP 0x100257b0
	// GolMaterial::`scalar deleting destructor'

	void CopyParamsTo(GolMaterialParams* p_params) const;
	void SetParams(GolRenderDevice*, const GolMaterialParams&);

	friend class GolMaterialLibrary;
	friend class GolSoftwareRenderer;

protected:
	GolTexture* m_unk0x04;
	LegoU32 m_unk0x08;
	GolMaterialColor m_diffuse;
	GolMaterialColor m_ambient;
	void* m_unk0x14;
	GolMaterial::NameRecord m_unk0x18;
	undefined m_unk0x20;
	undefined m_unk0x21;
	undefined m_unk0x22;
	undefined m_unk0x23;
};

inline GolMaterialParams::GolMaterialParams(LegoU8 p_fullIntensity)
{
	m_diffuse.m_red = p_fullIntensity;
	m_diffuse.m_grn = p_fullIntensity;
	m_diffuse.m_blu = p_fullIntensity;
	m_diffuse.m_alp = p_fullIntensity;
	m_ambient.m_red = p_fullIntensity;
	m_ambient.m_grn = p_fullIntensity;
	m_ambient.m_blu = p_fullIntensity;
	m_ambient.m_alp = p_fullIntensity;
	m_unk0x00 = GolMaterial::c_flag0x08Bit2 | GolMaterial::c_flag0x08Bit4 | GolMaterial::c_flag0x08Bit7 |
				GolMaterial::c_flag0x08Bit9 | GolMaterial::c_flag0x08Bit10 | GolMaterial::c_flag0x08Bit13 |
				GolMaterial::c_flag0x08Bit15 | GolMaterial::c_flag0x08Bit20 | GolMaterial::c_flag0x08Bit22;
	m_unk0x04 = NULL;
	m_unk0x10 = 2;
	m_unk0x11 = 0;
	m_unk0x12 = 1;
	m_unk0x13 = 0;
}

#endif // DUSKWINDBANANARELIC0x24_H

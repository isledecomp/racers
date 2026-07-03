#ifndef GOLMATERIAL_H
#define GOLMATERIAL_H

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

	LegoU32 m_flags;            // 0x00
	GolTexture* m_texture;      // 0x04
	GolMaterialColor m_ambient; // 0x08
	GolMaterialColor m_diffuse; // 0x0c
	undefined m_alphaFunc;      // 0x10
	undefined m_alphaRef;       // 0x11
	undefined m_srcBlend;       // 0x12
	undefined m_destBlend;      // 0x13
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
		c_flagCreated = 1 << 0,
		c_flagFlatShading = 1 << 1,
		c_flagGouraudShading = 1 << 2,
		c_flagTextured = 1 << 3,
		c_flagDecal = 1 << 4,
		c_flagModulate = 1 << 5,
		c_flagAlphaTest = 1 << 6,
		c_flagNoAlphaTest = 1 << 7,
		c_flagAlphaBlend = 1 << 8,
		c_flagNoAlphaBlend = 1 << 9,
		c_flagLinearFilter = 1 << 10,
		c_flagPointFilter = 1 << 11,
		c_flagTransparent = 1 << 12,
		c_flagNoTransparency = 1 << 13,
		c_flagRotateVertices = 1 << 14,
		c_flagWrap = 1 << 15,
		c_flagClamp = 1 << 16,
		c_flagBit17 = 1 << 17,
		c_flagBit18 = 1 << 18,
		c_flagBit19 = 1 << 19,
		c_flagBit20 = 1 << 20,
		c_flagBit21 = 1 << 21,
		c_flagBit22 = 1 << 22,
	};

	GolMaterial();
	virtual ~GolMaterial(); // vtable+0x00

	GolTexture* GetTexture() const { return m_texture; }
	LegoU32 GetFlags() const { return m_flags; }
	const GolMaterialColor& GetDiffuse() const { return m_diffuse; }
	const GolMaterialColor& GetAmbient() const { return m_ambient; }
	undefined GetAlphaFunc() const { return m_alphaFunc; }
	undefined GetAlphaRef() const { return m_alphaRef; }
	undefined GetSrcBlend() const { return m_srcBlend; }
	undefined GetDestBlend() const { return m_destBlend; }
	const LegoChar* GetName() const { return m_nameRecord.m_name; }
	const GolMaterial::NameRecord& GetNameRecord() const { return m_nameRecord; }
	void SetName(const LegoChar* p_name) { ::memcpy(m_nameRecord.m_name, p_name, sizeof(GolName)); }
	void SetUserData(void* p_userData) { m_userData = p_userData; }
	void EnableFlagBit18() { m_flags |= c_flagBit18; }

	// SYNTHETIC: GOLDP 0x100257b0
	// GolMaterial::`scalar deleting destructor'

	void CopyParamsTo(GolMaterialParams* p_params) const;
	void SetParams(GolRenderDevice*, const GolMaterialParams&);

	friend class GolMaterialLibrary;
	friend class GolSoftwareRenderer;

protected:
	GolTexture* m_texture;                // 0x04
	LegoU32 m_flags;                      // 0x08
	GolMaterialColor m_diffuse;           // 0x0c
	GolMaterialColor m_ambient;           // 0x10
	void* m_userData;                     // 0x14
	GolMaterial::NameRecord m_nameRecord; // 0x18
	undefined m_alphaFunc;                // 0x20
	undefined m_alphaRef;                 // 0x21
	undefined m_srcBlend;                 // 0x22
	undefined m_destBlend;                // 0x23
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
	m_flags = GolMaterial::c_flagGouraudShading | GolMaterial::c_flagDecal | GolMaterial::c_flagNoAlphaTest |
			  GolMaterial::c_flagNoAlphaBlend | GolMaterial::c_flagLinearFilter | GolMaterial::c_flagNoTransparency |
			  GolMaterial::c_flagWrap | GolMaterial::c_flagBit20 | GolMaterial::c_flagBit22;
	m_texture = NULL;
	m_alphaFunc = 2;
	m_alphaRef = 0;
	m_srcBlend = 1;
	m_destBlend = 0;
}

#endif // GOLMATERIAL_H

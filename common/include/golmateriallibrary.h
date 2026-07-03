#ifndef GOLMATERIALLIBRARY_H
#define GOLMATERIALLIBRARY_H

#include "golmaterial.h"
#include "golnametable.h"
#include "goltxtparser.h"

class GolRenderDevice;
class RaceState;

class GolMaterialSource {
public:
	virtual void GetMaterialParams(LegoU32 p_index, GolMaterialParams* p_params) = 0; // vtable+0x00
};

// VTABLE: GOLDP 0x10057134
// SIZE 0x1c
class GolMaterialLibrary : public GolNameTable {
public:
	// VTABLE: GOLDP 0x10057160
	// SIZE 0x1fc
	class MdbTxtParser : public GolTxtParser {
	public:
		// .mdf tokens (alpha funcs index g_d3dCmpFuncLookup, blend factors g_d3dBlendOps)
		enum {
			e_material = 0x27,
			e_ambient = 0x28,
			e_diffuse = 0x29,
			e_flatShading = 0x2a,
			e_gouraudShading = 0x2b,
			e_texture = 0x2c,
			e_modulate = 0x2d,
			e_decal = 0x2e,
			e_alphaTest = 0x2f,
			e_alphaAlways = 0x30,
			e_alphaEqual = 0x31,
			e_alphaGreater = 0x32,
			e_alphaGreaterEqual = 0x33,
			e_alphaLess = 0x34,
			e_alphaLessEqual = 0x35,
			e_alphaNever = 0x36,
			e_alphaNotEqual = 0x37,
			e_blend = 0x38,
			e_blendZero = 0x39,
			e_blendOne = 0x3a,
			e_blendSrcColor = 0x3b,
			e_blendDestColor = 0x3c,
			e_blendInvSrcColor = 0x3d,
			e_blendInvDestColor = 0x3e,
			e_blendSrcAlpha = 0x3f,
			e_blendDestAlpha = 0x40,
			e_blendInvSrcAlpha = 0x41,
			e_blendInvDestAlpha = 0x42,
			e_blendSrcAlphaSat = 0x43,
			e_linearFilter = 0x44,
			e_pointFilter = 0x45,
			e_transparency = 0x46,
			e_rotateVertices = 0x47,
			e_wrap = 0x48,
			e_clamp = 0x49,
			e_transparency2 = 0x4d,
			e_transparency3 = 0x4e,
			e_transparency4 = 0x4f,
			e_transparency5 = 0x50,
			e_unknown0x4a = 0x4a,
			e_unknown0x4b = 0x4b,
			e_unknown0x4c = 0x4c,
		};

		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// GolMaterialLibrary::MdbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolMaterialLibrary::MdbTxtParser::~MdbTxtParser
	};

	GolMaterialLibrary();
	~GolMaterialLibrary() override; // vtable+0x00
	void Clear() override;          // vtable+0x08

	virtual void ReleaseMaterials();                                          // vtable+0x0c
	virtual void RestoreMaterials();                                          // vtable+0x10
	virtual void AllocateItems() = 0;                                         // vtable+0x14
	virtual void CreateMaterial(LegoU32 p_index) = 0;                         // vtable+0x18
	virtual void Initialize(GolRenderDevice* p_renderer, LegoU32 p_capacity); // vtable+0x1c
	virtual void InitializeFromSource(
		GolRenderDevice* p_renderer,
		GolMaterialSource* p_source,
		LegoU32 p_capacity
	); // vtable+0x20
	virtual void Load(GolRenderDevice* p_renderer, const LegoChar* p_fileName,
					  LegoBool32 p_binary);                  // vtable+0x24
	virtual GolMaterial* GetItem(LegoU32 p_index) const = 0; // vtable+0x28

	// SYNTHETIC: GOLDP 0x100261d0
	// GolMaterialLibrary::`scalar deleting destructor'

	GolMaterialLibrary* GetNext() const { return m_next; }
	void SetNext(GolMaterialLibrary* p_next) { m_next = p_next; }

	LegoU32 GetItemCount() const { return m_itemCount; }

protected:
	friend class RaceState;

	void CreateMaterials();

	GolRenderDevice* m_renderer;         // 0x0c
	GolMaterialLibrary* m_next;          // 0x10
	GolMaterialSource* m_materialSource; // 0x14
	LegoU32 m_itemCount;                 // 0x18
};

#endif // GOLMATERIALLIBRARY_H

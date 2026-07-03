#ifndef GOLRENDERDEVICE_H
#define GOLRENDERDEVICE_H

#include "decomp.h"
#include "golmath.h"
#include "golsurface.h"
#include "golsurfaceformat.h"
#include "golviewfrustum.h"
#include "render/gold3drenderstate.h"
#include "surface/color.h"
#include "types.h"

class GolMaterialLibrary;
class GolCamera;
class GolD3DRenderDevice;
class GolFontLibrary;
class GolMaterial;
class GolModelEntity;
class GolWorldEntity;
class GolSurfaceFormat;
class GolFont;
class GolFontBase;
class GolString;
class GolCommonDrawState;
class GolNameTable;
class GolImageList;
class GolBillboard;
struct Rect;
class GolTextureList;
class GolRenderTarget;
class GolImage;
class GolTexture;

// VTABLE: GOLDP 0x10057338
// SIZE 0x140
class GolRenderDevice {
public:
	// SIZE 0x18
	struct TexturedVertex {
		LegoFloat m_x;     // 0x00
		LegoFloat m_y;     // 0x04
		LegoFloat m_z;     // 0x08
		LegoFloat m_u;     // 0x0c
		LegoFloat m_v;     // 0x10
		ColorRGBA m_color; // 0x14
	};

	// SIZE 0x04
	class MaterialColor {
	public:
		MaterialColor();
		void SetColor(ColorRGBA p_color);
		const ColorRGBA& GetColor() const { return m_color; }

		ColorRGBA m_color; // 0x00
	};

	// SIZE 0x10
	class Light : public MaterialColor {
	public:
		Light();
		void SetDirection(const GolVec3& p_direction);

		GolVec3 m_direction; // 0x04
	};

	enum Flags {
		c_flagCreated = 1 << 0,
		c_flagZBuffer = 1 << 1,
		c_flagZBufferActive = 1 << 5,
		c_flagColorKeyAlphaBlend = 1 << 7,
		c_flagColorKeyAlphaTest = 1 << 8,
		c_flagBlackColorKey = 1 << 9,
		c_flagBit11 = 1 << 11,
		c_flagBit12 = 1 << 12,
		c_flagBit13 = 1 << 13,
		c_flagAlphaOverride = 1 << 14,
		c_flagLightingEnabled = 1 << 15,
		c_flagSoftwareRenderer = 1 << 16,
		c_flagMipmapsEnabled = 1 << 17,
		c_flagBit18 = 1 << 18,
		c_flagColorOverride = 1 << 19,
		c_flagBit20 = 1 << 20,
		c_flagBit24 = 1 << 24,
	};

	GolRenderDevice();

	virtual LegoS32 RestoreResources(); // vtable+0x00
	virtual void ReleaseResources();    // vtable+0x04
	virtual ~GolRenderDevice();         // vtable+0x08
	virtual void SelectTextureFormat(
		const GolSurfaceFormat& p_requestedTextureFormat,
		GolSurfaceFormat* p_actualTextureFormat,
		LegoBool32
	);                                                                            // vtable+0x0c
	virtual GolCommonDrawState* GetDrawState() = 0;                               // vtable+0x10
	virtual GolRenderTarget* GetRenderTargetInfo() = 0;                           // vtable+0x14
	virtual void Shutdown() = 0;                                                  // vtable+0x18
	virtual void SetClearColor(const ColorRGBA&) = 0;                             // vtable+0x1c
	virtual void SetCamera(GolCamera*) = 0;                                       // vtable+0x20
	virtual void DetachCamera();                                                  // vtable+0x24
	virtual void ClearLights();                                                   // vtable+0x28
	virtual void SetAmbient(const MaterialColor* p_param);                        // vtable+0x2c
	virtual void AddLight(const Light* p_param);                                  // vtable+0x30
	virtual void SetViewportRect(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08);  // vtable+0x34
	virtual void VTable0x38();                                                    // vtable+0x38
	virtual void EnableMipmaps(LegoU32);                                          // vtable+0x3c
	virtual void DisableMipmaps();                                                // vtable+0x40
	virtual void VTable0x44();                                                    // vtable+0x44
	virtual void VTable0x48();                                                    // vtable+0x48
	virtual GolRenderTarget* CreateRenderTarget(undefined2, undefined2);          // vtable+0x4c
	virtual void DestroyRenderTarget(GolRenderTarget*);                           // vtable+0x50
	virtual void BeginFrame(undefined4) = 0;                                      // vtable+0x54
	virtual void SetRenderTarget(GolRenderTarget* p_param1, undefined4 p_param2); // vtable+0x58
	virtual void ApplyCamera() = 0;                                               // vtable+0x5c
	virtual void ApplyLights();                                                   // vtable+0x60
	virtual void DrawString(
		GolString*,
		GolFontBase*,
		LegoS32,
		LegoS32,
		LegoFloat,
		LegoFloat,
		Rect*,
		undefined4
	) = 0; // vtable+0x64
	virtual void DrawCString(
		const LegoChar*,
		GolFontBase*,
		LegoS32,
		LegoS32,
		LegoFloat,
		LegoFloat,
		Rect*,
		undefined4
	) = 0; // vtable+0x68
	virtual void DrawStringFitted(
		GolString*,
		GolFontBase*,
		LegoS32,
		LegoS32,
		LegoFloat,
		LegoFloat,
		Rect*,
		undefined4
	) = 0; // vtable+0x6c
	virtual void DrawImage(GolImage*, undefined4, LegoS32, LegoS32, LegoS32,
						   LegoS32) = 0; // vtable+0x70
	virtual void DrawImageStretched(
		GolImage*,
		undefined4,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32
	) = 0;                                                               // vtable+0x74
	virtual void DrawImageRect(GolImage*, undefined4, Rect*, Rect*) = 0; // vtable+0x78
	virtual void DrawImageClipped(
		GolImage* p_image,
		undefined4 p_unk0x08,
		Rect* p_destRect,
		Rect* p_sourceRect,
		Rect* p_clipRect
	) = 0; // vtable+0x7c
	virtual void DrawRectangle(
		const Rect& p_rect,
		LegoFloat p_z,
		const ColorRGBA& p_color1,
		const ColorRGBA& p_color2,
		const ColorRGBA& p_color3,
		const ColorRGBA& p_color4,
		undefined4 p_arg7
	) = 0; // vtable+0x80
	virtual void DrawTriangle(
		const TexturedVertex* p_vertex0,
		const TexturedVertex* p_vertex1,
		const TexturedVertex* p_vertex2,
		GolMaterial* p_material,
		undefined4 p_flags
	) = 0;                                                                                             // vtable+0x84
	virtual void DrawCollidableEntityWithState(GolModelEntity*, GolD3DRenderState*, undefined4);       // vtable+0x88
	virtual void DrawModelEntityWithState(GolModelEntity*, GolD3DRenderState*, undefined4);            // vtable+0x8c
	virtual void DrawCollidableEntity(GolWorldEntity*) = 0;                                            // vtable+0x90
	virtual void DrawModelEntity(GolWorldEntity*) = 0;                                                 // vtable+0x94
	virtual void DrawCollidableEntityWithScopedState(GolModelEntity*, GolD3DRenderState*, undefined4); // vtable+0x98
	virtual void DrawModelEntityWithScopedState(GolModelEntity*, GolD3DRenderState*, undefined4);      // vtable+0x9c
	virtual void DrawModelEntityWithUvAxes(
		GolWorldEntity*,
		const GolVec3*,
		const GolVec3*,
		const GolVec3*
	);                                                              // vtable+0xa0
	virtual void DrawModelEntityEnvironmentMapped(GolWorldEntity*); // vtable+0xa4
	virtual void DrawModelEntityWithUvOffset(
		GolWorldEntity* p_param1,
		LegoFloat p_param2,
		LegoFloat p_param3
	);                                                                     // vtable+0xa8
	virtual void DrawModelEntityLodMirrored(GolModelEntity*, undefined4);  // vtable+0xac
	virtual void DrawModelEntityLod(GolModelEntity*, undefined4);          // vtable+0xb0
	virtual void DrawBillboard(GolBillboard&) = 0;                         // vtable+0xb4
	virtual void SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags); // vtable+0xb8
	virtual void ClearAlphaOverride();                                     // vtable+0xbc
	virtual void SetColorOverride(const ColorRGBA& p_param);               // vtable+0xc0
	virtual void ClearColorOverride();                                     // vtable+0xc4
	virtual void EnableWireframe();                                        // vtable+0xc8
	virtual void DisableWireframe();                                       // vtable+0xcc
	virtual void VTable0xd0() = 0;                                         // vtable+0xd0
	virtual void DisablePerspectiveCorrection() = 0;                       // vtable+0xd4
	virtual void EnablePerspectiveCorrection() = 0;                        // vtable+0xd8
	virtual void EnableDither() = 0;                                       // vtable+0xdc
	virtual void DisableDither() = 0;                                      // vtable+0xe0
	virtual void EnableZBuffer() = 0;                                      // vtable+0xe4
	virtual void DisableZBuffer(LegoBool32 p_arg) = 0;                     // vtable+0xe8
	virtual void SelectViewport(undefined4);                               // vtable+0xec
	virtual void EndFrame() = 0;                                           // vtable+0xf0
	virtual void VTable0xf4();                                             // vtable+0xf4
	virtual LegoU32 GetMinimumTextureWidth(undefined4) const = 0;          // vtable+0xf8
	virtual LegoU32 GetMaximumTextureWidth(undefined4) const = 0;          // vtable+0xfc
	virtual LegoU32 GetMinimumTextureHeight(undefined4) const = 0;         // vtable+0x100
	virtual LegoU32 GetMaximumTextureHeight(undefined4) const = 0;         // vtable+0x104
	virtual LegoBool32 TexturesMustBeSquare() const = 0;                   // vtable+0x108
	virtual LegoBool32 TextureSizesMustBePowersOfTwo() const = 0;          // vtable+0x10c
	virtual LegoBool32 VTable0x110() const;

	void Destroy();
	void AddFontList(GolFontLibrary* p_param);
	void RemoveFontList(GolFontLibrary* p_param);
	void AddImageList(GolImageList* p_param);
	void RemoveImageList(GolImageList* p_param);
	void AddTextureList(GolTextureList* p_param);
	void RemoveTextureList(GolTextureList* p_param);
	GolTexture* FindTextureByName(const LegoChar* p_name);
	void AddMaterialList(GolMaterialLibrary* p_param);
	void RemoveMaterialList(GolMaterialLibrary* p_param);
	GolMaterial* FindMaterialByName(const LegoChar* p_name);

#ifdef BUILDING_LEGORACERS
	GolFont* FindFontByName(const LegoChar* p_name);
	GolImage* FindImageByName(const LegoChar* p_name);
#endif

	// SYNTHETIC: GOLDP 0x100288b0
	// GolRenderDevice::`scalar deleting destructor'

	undefined4 GetFlags() { return m_flags; }
	GolCamera* GetCurrentCamera() { return m_currentCamera; }
	MaterialColor* GetCurrentMaterialColor() { return const_cast<MaterialColor*>(m_ambientColor); }
	Light* GetCurrentLight(LegoU32 p_index) { return const_cast<Light*>(m_lights[p_index]); }

protected:
	friend class GolCommonDrawState;

	undefined4 m_flags;                          // 0x04
	undefined2 m_alphaOverrideFlags;             // 0x08
	undefined2 m_alphaOverride;                  // 0x0a
	GolCamera* m_currentCamera;                  // 0x0c
	LegoU32 m_textureFormatIndex;                // 0x10
	undefined4 m_requestedRedBitCount;           // 0x14
	undefined4 m_requestedGrnBitCount;           // 0x18
	undefined4 m_requestedBluBitCount;           // 0x1c
	undefined4 m_requestedAlpBitCount;           // 0x20
	undefined4 m_requestedIntensityBitCount;     // 0x24
	undefined4 m_requestedPaletteBitCount;       // 0x28
	undefined4 m_unk0x2c;                        // 0x2c
	LegoU32 m_countTextureFormats;               // 0x30
	GolSurfaceFormat* m_textureFormats;          // 0x34
	GolTextureList* m_textureLists;              // 0x38
	GolMaterialLibrary* m_materialLists;         // 0x3c
	GolImageList* m_imageLists;                  // 0x40
	GolFontLibrary* m_fontLists;                 // 0x44
	GolD3DRenderDevice* m_nextDrawStateRenderer; // 0x48
	GolViewFrustum m_viewFrustum;                // 0x4c
	ColorRGBA m_colorOverride;                   // 0x118
	undefined4 m_lightCount;                     // 0x11c
	const MaterialColor* m_ambientColor;         // 0x120
	const Light* m_lights[7];                    // 0x124
};

#endif // GOLRENDERDEVICE_H

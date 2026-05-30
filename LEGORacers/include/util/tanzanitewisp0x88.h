#ifndef TANZANITEWISP0X88_H
#define TANZANITEWISP0X88_H

#include "decomp.h"
#include "material/duskwindbananarelic0x24.h"
#include "types.h"

class GolExport;
class GolBmpFile;
class GolMaterialLibrary;
class GolD3DRenderDevice;
class GolTextureList;
class MusicInstance;
class MenuManager;
class MusicGroup;
class GarnetFlare0x60;
class GolModelBase;
class GolSceneNode;
struct TurquoiseGlowColor;

// SIZE 0x88
class TanzaniteWisp0x88 {
public:
	// SIZE 0x14
	struct ModelSummary0x14 {
		LegoS32 m_unk0x00;     // 0x00
		LegoS32 m_unk0x04;     // 0x04
		LegoS32 m_unk0x08;     // 0x08
		LegoS32 m_unk0x0c;     // 0x0c
		GolModelBase* m_model; // 0x10
	};

	// SIZE 0x10
	struct LoadParams {
		GolExport* m_golExport;         // 0x00
		GolD3DRenderDevice* m_renderer; // 0x04
		undefined4 m_menuId;            // 0x08
		GarnetFlare0x60* m_unk0x0c;     // 0x0c
	};

	TanzaniteWisp0x88();
	~TanzaniteWisp0x88();

	void ResetMenuState();
	undefined4 FUN_0049d1d0(const LoadParams* p_params);
	LegoBool32 ReleaseMenuResources();
	void RefreshMenuResources();
	GolModelBase* FUN_0049db90(TurquoiseGlowColor* p_color, GolModelBase* p_model, undefined4 p_unk0x0c);
	GolSceneNode* FUN_0049dc10(TurquoiseGlowColor* p_color);
	void FUN_0049dc90(undefined4* p_dest);
	void FUN_0049dce0(GolModelBase* p_model, TurquoiseGlowColor* p_color);

	void Reset()
	{
		m_unk0x78 = 0;
		m_musicInstance = NULL;
	}

	MusicGroup* GetMusicGroup() { return m_musicGroup; }
	void SetMusicGroup(MusicGroup* p_musicGroup) { m_musicGroup = p_musicGroup; }
	MusicInstance* GetMusicInstance() { return m_musicInstance; }
	void SetMusicInstance(MusicInstance* p_musicInstance) { m_musicInstance = p_musicInstance; }
	LegoBool32 HasMenuResources() const { return m_menuId != 0; }
	void SetUnk0x10(undefined4 p_unk0x10) { m_unk0x10 = p_unk0x10; }
	undefined4 GetUnk0x78() const { return m_unk0x78; }
	void SetUnk0x78(undefined4 p_unk0x78) { m_unk0x78 = p_unk0x78; }
	LegoS32 GetUnk0x84() const { return m_unk0x84; }
	void SetUnk0x84(LegoS32 p_unk0x84) { m_unk0x84 = p_unk0x84; }

private:
	friend class MenuManager;

	void CreateMenuResources();
	void InitializeDefaultMaterialParams();
	void FUN_0049d2e0(const LegoChar* p_name, GolBmpFile* p_imageFile);
	void FUN_0049d3a0(const LegoChar* p_name);
	void FUN_0049d420(LegoS32 p_faceIndex);
	void FUN_0049d570(GolModelBase* p_model, ModelSummary0x14* p_summary);
	LegoBool32 FUN_0049d5c0() const;
	void FUN_0049d600();
	LegoBool32 FUN_0049d670(GolModelBase* p_model) const;
	GolModelBase* FUN_0049d6e0(undefined2 p_vertexType);
	void CopyModelVertices(GolModelBase* p_sourceModel, GolModelBase* p_destModel, LegoU32 p_vertexOffset);
	void FUN_0049d880(GolModelBase* p_sourceModel, GolModelBase* p_destModel, LegoU32 p_indexOffset);
	void FUN_0049d920();
	void FUN_0049d970();
	void FUN_0049d9b0(DuskwindBananaRelic0x24* p_material, const LegoChar* p_name);
	GolModelBase* FUN_0049dab0(TurquoiseGlowColor* p_color, GolModelBase* p_model, undefined4 p_unk0x0c);
	void FUN_0049dd50();

	undefined4 m_menuId;                 // 0x00
	undefined4 m_unk0x04;                // 0x04
	undefined4 m_unk0x08;                // 0x08
	undefined4 m_unk0x0c;                // 0x0c
	undefined4 m_unk0x10;                // 0x10
	GolExport* m_golExport;              // 0x14
	GolD3DRenderDevice* m_renderer;      // 0x18
	GolTextureList* m_menuResource0;     // 0x1c
	GolMaterialLibrary* m_menuResource1; // 0x20
	DuskWindBananaRelicParams m_unk0x24; // 0x24
	GarnetFlare0x60* m_unk0x38;          // 0x38
	ModelSummary0x14 m_unk0x3c;          // 0x3c
	ModelSummary0x14 m_unk0x50;          // 0x50
	ModelSummary0x14 m_unk0x64;          // 0x64
	undefined4 m_unk0x78;                // 0x78
	MusicGroup* m_musicGroup;            // 0x7c
	MusicInstance* m_musicInstance;      // 0x80
	LegoS32 m_unk0x84;                   // 0x84
};

#endif // TANZANITEWISP0X88_H

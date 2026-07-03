#ifndef GOLWORLDDATABASE_H
#define GOLWORLDDATABASE_H

#include "golmath.h"
#include "golname.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "render/golrenderdevice.h"
#include "surface/color.h"
#include "world/wdbbillboardsprite.h"
#include "world/wdbcamera.h"
#include "world/wdblight.h"
#include "world/wdbmodel.h"

class GolCameraBase;
class GolCamera;
class GolMaterialLibrary;
class GolBoundingShape;
class GolBoundingVolume;
class CmbModelPart;
class GolFileParser;
class GolWorldEntity;
class GolModelEntity;
class GolBoundedEntity;
class GolAnimatedEntity;
class GolCollidableEntity;
class GolBillboard;
class GolModelBase;
class MabMaterialAnimation;
class GolTextureList;
class GolModelMaterialTable;
class GolRenderDevice;
class GolSceneNode;
struct Rect;

// VTABLE: GOLDP 0x100576ec
// SIZE 0xf0
class GolWorldDatabase {
	friend class DriverHeadBuilder;

public:
	// VTABLE: GOLDP 0x10057744
	// SIZE 0x1fc
	class WdbTxtParser : public GolTxtParser {
	public:
		// .wdb tokens; ids are section-scoped, so several carry one name per context
		enum {
			e_textureLists = 0x27,
			e_materialLibraries = 0x28,
			e_modelParts = 0x29,
			e_models = 0x2a,
			e_materialTables = 0x2b,
			e_materialAssignment = 0x2b,
			e_sceneNodes = 0x2c,
			e_nodeLod = 0x2c,
			e_boundingShapes = 0x2d,
			e_modelEntities = 0x2e,
			e_animatedEntities = 0x2f,
			e_trackedEntity = 0x2f,
			e_collidableEntities = 0x30,
			e_position = 0x31,
			e_orientation = 0x32,
			e_jointedModel = 0x33,
			e_collidableModel = 0x34,
			e_node = 0x35,
			e_scale = 0x36,
			e_sprites = 0x37,
			e_axis = 0x38,
			e_materialName = 0x39,
			e_width = 0x3a,
			e_height = 0x3b,
			e_maxDistance = 0x3c,
			e_materialAnimations = 0x3d,
			e_materialAnimation = 0x3e,
			e_lod = 0x3f,
			e_textureScroll = 0x3f,
			e_boundingVolumes = 0x40,
			e_boundingVolumeRef = 0x40,
			e_boundedEntities = 0x41,
			e_modelFlag1 = 0x42,
			e_cameras = 0x43,
			e_target = 0x44,
			e_nearClip = 0x45,
			e_farClip = 0x46,
			e_fov = 0x47,
			e_ambientLights = 0x48,
			e_lights = 0x49,
			e_color = 0x4a,
			e_direction = 0x4b,
			e_modelFlag2 = 0x4c,
		};

		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// GolWorldDatabase::WdbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolWorldDatabase::WdbTxtParser::~WdbTxtParser
	};

	GolWorldDatabase();
	virtual void DestroyRecords();           // vtable+0x00
	virtual void AllocateEntities();         // vtable+0x04
	virtual void AllocateResources() = 0;    // vtable+0x08
	virtual undefined4* LoadResources() = 0; // vtable+0x0c
	virtual ~GolWorldDatabase();             // vtable+0x10
	virtual void Load(
		GolRenderDevice* p_renderer,
		const LegoChar* p_name,
		LegoBool32 p_binary,
		LegoFloat p_worldScale
	);                                                                             // vtable+0x14
	virtual void Destroy();                                                        // vtable+0x18
	virtual void DrawCollidableEntities(GolRenderDevice*) = 0;                     // vtable+0x1c
	virtual void DrawModelEntities(GolRenderDevice*) = 0;                          // vtable+0x20
	virtual void DrawAnimatedEntities(GolRenderDevice*) = 0;                       // vtable+0x24
	virtual void DrawSprites(GolRenderDevice*) = 0;                                // vtable+0x28
	virtual GolTextureList* GetTextureList(LegoU32 p_index) const = 0;             // vtable+0x2c
	virtual GolMaterialLibrary* GetMaterialLibrary(LegoU32 p_index) const = 0;     // vtable+0x30
	virtual CmbModelPart* GetModelPart(LegoU32 p_index) const = 0;                 // vtable+0x34
	virtual GolModelBase* GetModel(LegoU32 p_index) const = 0;                     // vtable+0x38
	virtual GolModelMaterialTable* GetMaterialTable(LegoU32 p_index) const = 0;    // vtable+0x3c
	virtual GolSceneNode* GetSceneNode(LegoU32 p_index) const = 0;                 // vtable+0x40
	virtual GolBoundingShape* GetBoundingShape(LegoU32 p_index) const = 0;         // vtable+0x44
	virtual GolWorldEntity* GetWorldEntity(LegoU32 p_index) const = 0;             // vtable+0x48
	virtual MabMaterialAnimation* GetMaterialAnimation(LegoU32 p_index) const = 0; // vtable+0x4c
	virtual GolCameraBase* GetCamera(LegoU32 p_index) const = 0;                   // vtable+0x50
	virtual void SetLoadTexturesImmediately(undefined4 p_immediate);               // vtable+0x54

	// SYNTHETIC: GOLDP 0x1002c0c0
	// GolWorldDatabase::`scalar deleting destructor'

	LegoU32 GetTextureListCount() const { return m_textureListCount; }
	LegoU32 GetMaterialLibraryCount() const { return m_materialLibraryCount; }
	LegoU32 GetModelPartCount() const { return m_modelPartCount; }
	LegoU32 GetModelEventCount() const { return m_modelCount; }
	LegoU32 GetMaterialTableCount() const { return m_materialTableCount; }
	LegoU32 GetSceneNodeCount() const { return m_sceneNodeCount; }
	LegoU32 GetBoundingShapeCount() const { return m_boundingShapeCount; }
	LegoU32 GetModelEntityCount() const { return m_modelEntityCount; }
	LegoU32 GetAnimatedEntityCount() const { return m_animatedEntityCount; }
	LegoU32 GetCollidableEntityCount() const { return m_collidableEntityCount; }
	LegoU32 GetBoundedEntityCount() const { return m_boundedEntityCount; }
	LegoU32 GetSpriteCount() const { return m_spriteCount; }
	LegoU32 GetMaterialAnimationCount() const { return m_materialAnimationCount; }
	GolName* GetMaterialAnimationNames() const { return m_materialAnimationNames; }
	LegoU32 GetCameraCount() const { return m_cameraCount; }
	LegoU32 GetAmbientLightCount() const { return m_ambientLightCount; }
	LegoU32 GetLightCount() const { return m_lightCount; }
	GolModelEntity* GetModelEntities() const { return m_modelEntities; }
	GolAnimatedEntity* GetAnimatedEntities() const { return m_animatedEntities; }
	GolCollidableEntity* GetCollidableEntities() const { return m_collidableEntities; }
	GolBoundedEntity* GetBoundedEntities() const { return m_boundedEntities; }
	GolRenderDevice::MaterialColor* GetAmbientMaterial() { return m_ambientMaterial; }
	const GolRenderDevice::MaterialColor* GetAmbientMaterial() const { return m_ambientMaterial; }
	GolRenderDevice::Light* GetLight() { return m_light; }
	const GolRenderDevice::Light* GetLight() const { return m_light; }
	void DrawWorld();
	void Update(LegoS32 p_elapsedMs);
	void ResetEntities();
	LegoU32 SetCameraAspectRatios(LegoFloat p_aspectRatio);
	GolNameTable::Entry* GetModelEntityEntries() const { return m_modelEntityNames.GetNameEntries(); }
	GolModelEntity* GetModelEntityByName(const LegoChar* p_name) const
	{
		return static_cast<GolModelEntity*>(m_modelEntityNames.GetName(p_name));
	}
	GolNameTable::Entry* GetAnimatedEntityEntries() const { return m_animatedEntityNames.GetNameEntries(); }
	GolAnimatedEntity* GetAnimatedEntityByName(const LegoChar* p_name) const
	{
		return static_cast<GolAnimatedEntity*>(m_animatedEntityNames.GetName(p_name));
	}
	GolNameTable::Entry* GetCollidableEntityEntries() const { return m_collidableEntityNames.GetNameEntries(); }
	GolCollidableEntity* GetCollidableEntityByName(const LegoChar* p_name) const
	{
		return static_cast<GolCollidableEntity*>(m_collidableEntityNames.GetName(p_name));
	}
	GolModelEntity* FindModelEntity(const LegoChar* p_name) const
	{
		if (m_modelEntityNames.GetNameEntries() == NULL) {
			return NULL;
		}

		return static_cast<GolModelEntity*>(m_modelEntityNames.GetName(p_name));
	}
	GolAnimatedEntity* FindAnimatedEntity(const LegoChar* p_name) const
	{
		if (m_animatedEntityNames.GetNameEntries() == NULL) {
			return NULL;
		}
		return static_cast<GolAnimatedEntity*>(m_animatedEntityNames.GetName(p_name));
	}
	GolCollidableEntity* FindCollidableEntity(const LegoChar* p_name) const
	{
		return m_collidableEntityNames.GetNameEntries()
				   ? static_cast<GolCollidableEntity*>(m_collidableEntityNames.GetName(p_name))
				   : NULL;
	}
	GolBoundedEntity* FindBoundedEntity(const LegoChar* p_name) const
	{
		if (m_boundedEntityNames.GetNameEntries() == NULL) {
			return NULL;
		}

		return static_cast<GolBoundedEntity*>(m_boundedEntityNames.GetName(p_name));
	}
	GolCamera* FindCamera(const LegoChar* p_name) const
	{
		if (m_cameraNames.GetNameEntries() == NULL) {
			return NULL;
		}

		return static_cast<GolCamera*>(m_cameraNames.GetName(p_name));
	}

protected:
	void Reset();
	void ParseTextureListNames(GolFileParser&);
	void ParseMaterialLibraryNames(GolFileParser&);
	void ParseModelPartNames(GolFileParser&);
	void ParseModelNames(GolFileParser&);
	void ParseMaterialTableNames(GolFileParser&);
	void ParseSceneNodeNames(GolFileParser&);
	void ParseBoundingShapeNames(GolFileParser&);
	void ParseBoundingVolumeNames(GolFileParser&);
	void ParseModelEntities(GolFileParser&);
	void ParseAnimatedEntities(GolFileParser&);
	void ParseCollidableEntities(GolFileParser&);
	void ParseBoundedEntities(GolFileParser&);
	void ParseSprites(GolFileParser&);
	void ParseMaterialAnimationNames(GolFileParser&);
	void ParseAnimationBindings(GolFileParser&, Rect**, LegoU32* p_count);
	void ParseCameras(GolFileParser&);
	void ParseAmbientLights(GolFileParser&);
	void ParseLights(GolFileParser&);
	void BindSpriteMaterialAnimation(GolBillboard* p_billboard, WdbBillboardSprite* p_sprite);
	void InitializeEntities();
	void SetupCamera(LegoU32 p_cameraIndex, GolCameraBase* p_lens);

	GolRenderDevice* m_renderer;                       // 0x04
	LegoBool32 m_binary;                               // 0x08
	LegoU32 m_textureListCount;                        // 0x0c
	GolName* m_textureListNames;                       // 0x10
	LegoU32 m_materialLibraryCount;                    // 0x14
	GolName* m_materialLibraryNames;                   // 0x18
	LegoU32 m_modelPartCount;                          // 0x1c
	GolName* m_modelPartNames;                         // 0x20
	LegoU32 m_modelCount;                              // 0x24
	GolName* m_modelNames;                             // 0x28
	LegoU32 m_materialTableCount;                      // 0x2c
	GolName* m_materialTableNames;                     // 0x30
	LegoU32 m_sceneNodeCount;                          // 0x34
	GolName* m_sceneNodeNames;                         // 0x38
	LegoU32 m_boundingShapeCount;                      // 0x3c
	GolName* m_boundingShapeNames;                     // 0x40
	LegoU32 m_boundingVolumeCount;                     // 0x44
	GolName* m_boundingVolumeNames;                    // 0x48
	LegoU32 m_modelEntityCount;                        // 0x4c
	WdbModel* m_modelEntityRecords;                    // 0x50
	LegoU32 m_animatedEntityCount;                     // 0x54
	WdbModel* m_animatedEntityRecords;                 // 0x58
	LegoU32 m_collidableEntityCount;                   // 0x5c
	WdbModel* m_collidableEntityRecords;               // 0x60
	LegoU32 m_boundedEntityCount;                      // 0x64
	WdbModel* m_boundedEntityRecords;                  // 0x68
	LegoU32 m_spriteCount;                             // 0x6c
	WdbBillboardSprite* m_spriteRecords;               // 0x70
	LegoU32 m_materialAnimationCount;                  // 0x74
	GolName* m_materialAnimationNames;                 // 0x78
	LegoU32 m_cameraCount;                             // 0x7c
	WdbCamera* m_cameraRecords;                        // 0x80
	LegoU32 m_ambientLightCount;                       // 0x84
	WdbLight* m_ambientLightRecords;                   // 0x88
	LegoU32 m_lightCount;                              // 0x8c
	WdbLight* m_lightRecords;                          // 0x90
	LegoFloat m_worldScale;                            // 0x94
	GolBoundingVolume* m_boundingVolumes;              // 0x98
	GolModelEntity* m_modelEntities;                   // 0x9c
	GolAnimatedEntity* m_animatedEntities;             // 0xa0
	GolCollidableEntity* m_collidableEntities;         // 0xa4
	GolBoundedEntity* m_boundedEntities;               // 0xa8
	GolRenderDevice::MaterialColor* m_ambientMaterial; // 0xac
	GolRenderDevice::Light* m_light;                   // 0xb0
	GolNameTable m_modelEntityNames;                   // 0xb4
	GolNameTable m_animatedEntityNames;                // 0xc0
	GolNameTable m_collidableEntityNames;              // 0xcc
	GolNameTable m_boundedEntityNames;                 // 0xd8
	GolNameTable m_cameraNames;                        // 0xe4
};

#endif // GOLWORLDDATABASE_H

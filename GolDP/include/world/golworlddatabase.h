#ifndef GOLWORLDDATABASE_H
#define GOLWORLDDATABASE_H

#include "golmath.h"
#include "golname.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "render/golrenderdevice.h"
#include "surface/color.h"

class GolCameraBase;
class GolCamera;
class GolMaterialLibrary;
class GolBoundingShape;
class GolBoundingVolume;
class CmbModelPart0x34;
class GolFileParser;
class GolWorldEntity;
class GolModelEntity;
class GolBoundedEntity;
class GolAnimatedEntity;
class GolCollidableEntity;
class GolBillboard;
class GolModelBase;
class MabMaterialAnimation0x14;
class GolTextureList;
class GolModelMaterialTable;
class GolRenderDevice;
class GolSceneNode;
struct Rect;

// SIZE 0x8c
struct WdbModel0x8c {
	enum {
		e_flagBit1 = 0x1 << 1,
		e_flagBit2 = 0x1 << 2,
		e_flagBit3 = 0x1 << 3,
	};

	GolName m_unk0x00;      // 0x00
	LegoS32 m_unk0x08[3];   // 0x08
	LegoS32 m_unk0x14[3];   // 0x14
	LegoS32 m_unk0x20[3];   // 0x14
	LegoS32 m_unk0x2c[3];   // 0x2c
	LegoFloat m_unk0x38[3]; // 0x38
	LegoS32 m_unk0x44;      // 0x44
	GolName m_unk0x48;      // 0x48
	GolVec3 m_unk0x50;      // 0x50
	GolVec3 m_unk0x5c;      // 0x5c
	GolVec3 m_unk0x68;      // 0x68
	LegoFloat m_unk0x74;    // 0x74
	Rect* m_unk0x78;        // 0x78
	LegoU32 m_unk0x7c;      // 0x7c
	LegoFloat m_unk0x80;    // 0x80
	LegoFloat m_unk0x84;    // 0x84
	LegoU32 m_flags;        // 0x88
};

// SIZE 0x38
struct WdbBillboardSprite0x38 {
	enum {
		c_flagBit1 = 0x1 << 1,
		c_flagBit2 = 0x1 << 2,
	};

	GolName m_unk0x00;                // 0x00
	GolVec3 m_unk0x08;                // 0x08
	GolVec3 m_unk0x14;                // 0x14
	LegoFloat m_unk0x20;              // 0x20
	LegoFloat m_unk0x24;              // 0x24
	LegoFloat m_unk0x28;              // 0x28
	LegoU8 m_flags;                   // 0x2c
	undefined m_unk0x2d[0x2e - 0x2d]; // 0x2d
	undefined2 m_unk0x2e;             // 0x2e
	undefined2 m_unk0x30;             // 0x30
	undefined2 m_unk0x32;             // 0x32
	undefined2 m_unk0x34;             // 0x34
	undefined2 m_unk0x36;             // 0x36
};

// SIZE 0x4c
struct WdbCamera0x4c {
	LegoFloat GetUnk0x40() const { return m_unk0x40; }
	LegoFloat GetUnk0x44() const { return m_unk0x44; }
	LegoFloat GetUnk0x48() const { return m_unk0x48; }

	GolName m_unk0x00;    // 0x00
	LegoS32 m_unk0x08;    // 0x08
	undefined4 m_unk0x0c; // 0x0c
	LegoS32 m_unk0x10;    // 0x10
	GolName m_unk0x14;    // 0x14
	GolVec3 m_unk0x1c;    // 0x1c
	GolVec3 m_unk0x28;    // 0x28
	GolVec3 m_unk0x34;    // 0x34
	LegoFloat m_unk0x40;  // 0x40
	LegoFloat m_unk0x44;  // 0x44
	LegoFloat m_unk0x48;  // 0x48
};

// SIZE 0x10
struct WdbLight0x10 {
	ColorRGBA m_color; // 0x00
	GolVec3 m_unk0x04; // 0x04
};

// VTABLE: GOLDP 0x100576ec
// SIZE 0xf0
class GolWorldDatabase {
	friend class DriverHeadBuilder;

public:
	// VTABLE: GOLDP 0x10057744
	// SIZE 0x1fc
	class WdbTxtParser : public GolTxtParser {
		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// GolWorldDatabase::WdbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolWorldDatabase::WdbTxtParser::~WdbTxtParser
	};

	GolWorldDatabase();
	virtual void VTable0x00();                                                                         // vtable+0x00
	virtual void VTable0x04();                                                                         // vtable+0x04
	virtual void VTable0x08() = 0;                                                                     // vtable+0x08
	virtual undefined4* VTable0x0c() = 0;                                                              // vtable+0x0c
	virtual ~GolWorldDatabase();                                                                       // vtable+0x10
	virtual void VTable0x14(GolRenderDevice*, const LegoChar* p_name, LegoBool32 p_binary, LegoFloat); // vtable+0x14
	virtual void VTable0x18();                                                                         // vtable+0x18
	virtual void VTable0x1c(GolRenderDevice*) = 0;                                                     // vtable+0x1c
	virtual void VTable0x20(GolRenderDevice*) = 0;                                                     // vtable+0x20
	virtual void VTable0x24(GolRenderDevice*) = 0;                                                     // vtable+0x24
	virtual void VTable0x28(GolRenderDevice*) = 0;                                                     // vtable+0x28
	virtual GolTextureList* VTable0x2c(LegoU32 p_index) const = 0;                                     // vtable+0x2c
	virtual GolMaterialLibrary* VTable0x30(LegoU32 p_index) const = 0;                                 // vtable+0x30
	virtual CmbModelPart0x34* VTable0x34(LegoU32 p_index) const = 0;                                   // vtable+0x34
	virtual GolModelBase* VTable0x38(LegoU32 p_index) const = 0;                                       // vtable+0x38
	virtual GolModelMaterialTable* VTable0x3c(LegoU32 p_index) const = 0;                              // vtable+0x3c
	virtual GolSceneNode* VTable0x40(LegoU32 p_index) const = 0;                                       // vtable+0x40
	virtual GolBoundingShape* VTable0x44(LegoU32 p_index) const = 0;                                   // vtable+0x44
	virtual GolWorldEntity* VTable0x48(LegoU32 p_index) const = 0;                                     // vtable+0x48
	virtual MabMaterialAnimation0x14* VTable0x4c(LegoU32 p_index) const = 0;                           // vtable+0x4c
	virtual GolCameraBase* VTable0x50(LegoU32 p_index) const = 0;                                      // vtable+0x50
	virtual void VTable0x54(undefined4);                                                               // vtable+0x54

	// SYNTHETIC: GOLDP 0x1002c0c0
	// GolWorldDatabase::`scalar deleting destructor'

	LegoU32 GetUnk0x0c() const { return m_unk0x0c; }
	LegoU32 GetUnk0x14() const { return m_unk0x14; }
	LegoU32 GetUnk0x1c() const { return m_unk0x1c; }
	LegoU32 GetUnk0x24() const { return m_unk0x24; }
	LegoU32 GetUnk0x2c() const { return m_unk0x2c; }
	LegoU32 GetUnk0x34() const { return m_unk0x34; }
	LegoU32 GetUnk0x3c() const { return m_unk0x3c; }
	LegoU32 GetUnk0x54() const { return m_unk0x54; }
	LegoU32 GetUnk0x5c() const { return m_unk0x5c; }
	LegoU32 GetUnk0x6c() const { return m_unk0x6c; }
	LegoU32 GetUnk0x74() const { return m_unk0x74; }
	LegoU32 GetUnk0x7c() const { return m_unk0x7c; }
	LegoU32 GetUnk0x84() const { return m_unk0x84; }
	LegoU32 GetUnk0x8c() const { return m_unk0x8c; }
	GolModelEntity* GetUnk0x9c() const { return m_unk0x9c; }
	GolAnimatedEntity* GetUnk0xa0() const { return m_unk0xa0; }
	GolRenderDevice::MaterialColor* GetUnk0xac() { return m_unk0xac; }
	const GolRenderDevice::MaterialColor* GetUnk0xac() const { return m_unk0xac; }
	GolRenderDevice::Light* GetUnk0xb0() { return m_unk0xb0; }
	const GolRenderDevice::Light* GetUnk0xb0() const { return m_unk0xb0; }
	void FUN_00416040();
	void FUN_00416090(LegoS32 p_elapsedMs);
	LegoU32 FUN_00416290(LegoFloat p_scale);
	GolNameTable::Entry* GetUnk0xc0NameEntries() const { return m_unk0xc0.GetNameEntries(); }
	GolAnimatedEntity* GetUnk0xc0Name(const LegoChar* p_name) const
	{
		return static_cast<GolAnimatedEntity*>(m_unk0xc0.GetName(p_name));
	}
	GolModelEntity* FindUnk0xb4(const LegoChar* p_name) const
	{
		return m_unk0xb4.GetNameEntries() ? static_cast<GolModelEntity*>(m_unk0xb4.GetName(p_name)) : NULL;
	}
	GolAnimatedEntity* FindUnk0xc0(const LegoChar* p_name) const
	{
		if (m_unk0xc0.GetNameEntries() == NULL) {
			return NULL;
		}
		return static_cast<GolAnimatedEntity*>(m_unk0xc0.GetName(p_name));
	}
	GolCollidableEntity* FindUnk0xcc(const LegoChar* p_name) const
	{
		return m_unk0xcc.GetNameEntries() ? static_cast<GolCollidableEntity*>(m_unk0xcc.GetName(p_name)) : NULL;
	}
	GolCamera* FindUnk0xe4(const LegoChar* p_name) const
	{
		return m_unk0xe4.GetNameEntries() ? static_cast<GolCamera*>(m_unk0xe4.GetName(p_name)) : NULL;
	}

protected:
	void Reset();
	void FUN_1002c7b0(GolFileParser&);
	void FUN_1002c840(GolFileParser&);
	void FUN_1002c8d0(GolFileParser&);
	void FUN_1002c960(GolFileParser&);
	void FUN_1002c9f0(GolFileParser&);
	void FUN_1002ca80(GolFileParser&);
	void FUN_1002cb10(GolFileParser&);
	void FUN_1002cba0(GolFileParser&);
	void FUN_1002cc30(GolFileParser&);
	void FUN_1002cfa0(GolFileParser&);
	void FUN_1002d400(GolFileParser&);
	void FUN_1002d720(GolFileParser&);
	void FUN_1002d950(GolFileParser&);
	void FUN_1002db50(GolFileParser&);
	void FUN_1002dbe0(GolFileParser&, Rect**, LegoU32* p_count);
	void FUN_1002dc80(GolFileParser&);
	void FUN_1002df90(GolFileParser&);
	void FUN_1002e0d0(GolFileParser&);
	void FUN_1002e250(GolBillboard* p_billboard, WdbBillboardSprite0x38* p_sprite);
	void FUN_1002e640();
	void FUN_1002f210(LegoU32 p_cameraIndex, GolCameraBase* p_lens);

	GolRenderDevice* m_unk0x04;                // 0x04
	LegoBool32 m_binary;                       // 0x08
	LegoU32 m_unk0x0c;                         // 0x0c
	GolName* m_unk0x10;                        // 0x10
	LegoU32 m_unk0x14;                         // 0x14
	GolName* m_unk0x18;                        // 0x18
	LegoU32 m_unk0x1c;                         // 0x1c
	GolName* m_unk0x20;                        // 0x20
	LegoU32 m_unk0x24;                         // 0x24
	GolName* m_unk0x28;                        // 0x28
	LegoU32 m_unk0x2c;                         // 0x2c
	GolName* m_unk0x30;                        // 0x30
	LegoU32 m_unk0x34;                         // 0x34
	GolName* m_unk0x38;                        // 0x38
	LegoU32 m_unk0x3c;                         // 0x3c
	GolName* m_unk0x40;                        // 0x40
	LegoU32 m_unk0x44;                         // 0x44
	GolName* m_unk0x48;                        // 0x48
	LegoU32 m_unk0x4c;                         // 0x4c
	WdbModel0x8c* m_unk0x50;                   // 0x50
	LegoU32 m_unk0x54;                         // 0x54
	WdbModel0x8c* m_unk0x58;                   // 0x58
	LegoU32 m_unk0x5c;                         // 0x5c
	WdbModel0x8c* m_unk0x60;                   // 0x60
	LegoU32 m_unk0x64;                         // 0x64
	WdbModel0x8c* m_unk0x68;                   // 0x68
	LegoU32 m_unk0x6c;                         // 0x6c
	WdbBillboardSprite0x38* m_unk0x70;         // 0x70
	LegoU32 m_unk0x74;                         // 0x74
	GolName* m_unk0x78;                        // 0x78
	LegoU32 m_unk0x7c;                         // 0x7c
	WdbCamera0x4c* m_unk0x80;                  // 0x80
	LegoU32 m_unk0x84;                         // 0x84
	WdbLight0x10* m_unk0x88;                   // 0x88
	LegoU32 m_unk0x8c;                         // 0x8c
	WdbLight0x10* m_unk0x90;                   // 0x90
	LegoFloat m_unk0x94;                       // 0x94
	GolBoundingVolume* m_unk0x98;              // 0x98
	GolModelEntity* m_unk0x9c;                 // 0x9c
	GolAnimatedEntity* m_unk0xa0;              // 0xa0
	GolCollidableEntity* m_unk0xa4;            // 0xa4
	GolBoundedEntity* m_unk0xa8;               // 0xa8
	GolRenderDevice::MaterialColor* m_unk0xac; // 0xac
	GolRenderDevice::Light* m_unk0xb0;         // 0xb0
	GolNameTable m_unk0xb4;                    // 0xb4
	GolNameTable m_unk0xc0;                    // 0xc0
	GolNameTable m_unk0xcc;                    // 0xcc
	GolNameTable m_unk0xd8;                    // 0xd8
	GolNameTable m_unk0xe4;                    // 0xe4
};

#endif // GOLWORLDDATABASE_H

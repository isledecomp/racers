#ifndef GOLMATERIALLIBRARY_H
#define GOLMATERIALLIBRARY_H

#include "duskwindbananarelic0x24.h"
#include "golnametable.h"
#include "goltxtparser.h"

class GolRenderDevice;

class DuskwindBananaRelicProvider0x4 {
public:
	virtual void VTable0x00(LegoU32 p_index, DuskWindBananaRelicParams* p_params) = 0;
};

// VTABLE: GOLDP 0x10057134
// SIZE 0x1c
class GolMaterialLibrary : public GolNameTable {
public:
	// VTABLE: GOLDP 0x10057160
	// SIZE 0x1fc
	class MdbTxtParser : public GolTxtParser {
		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// GolMaterialLibrary::MdbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolMaterialLibrary::MdbTxtParser::~MdbTxtParser
	};

	GolMaterialLibrary();
	~GolMaterialLibrary() override; // vtable+0x00
	void Clear() override;          // vtable+0x08

	virtual void VTable0x0c();                                                // vtable+0x0c
	virtual void VTable0x10();                                                // vtable+0x10
	virtual void AllocateItems() = 0;                                         // vtable+0x14
	virtual void VTable0x18(LegoU32 p_index) = 0;                             // vtable+0x18
	virtual void VTable0x1c(GolRenderDevice* p_renderer, LegoU32 p_capacity); // vtable+0x1c
	virtual void VTable0x20(
		GolRenderDevice* p_renderer,
		DuskwindBananaRelicProvider0x4* p_source,
		LegoU32 p_capacity
	); // vtable+0x20
	virtual void VTable0x24(
		GolRenderDevice* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                                                   // vtable+0x24
	virtual DuskwindBananaRelic0x24* GetItem(LegoU32 p_index) const = 0; // vtable+0x28

	// SYNTHETIC: GOLDP 0x100261d0
	// GolMaterialLibrary::`scalar deleting destructor'

	GolMaterialLibrary* GetNext() const { return m_next; }
	void SetNext(GolMaterialLibrary* p_next) { m_next = p_next; }

	LegoU32 GetItemCount() const { return m_numItems; }

protected:
	void FUN_10026970();

	GolRenderDevice* m_renderer;               // 0x0c
	GolMaterialLibrary* m_next;                // 0x10
	DuskwindBananaRelicProvider0x4* m_unk0x14; // 0x14
	LegoU32 m_numItems;                        // 0x18
};

#endif // GOLMATERIALLIBRARY_H

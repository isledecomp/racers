#ifndef RACEEVENTDISPATCHER0X08_H
#define RACEEVENTDISPATCHER0X08_H

#include "decomp.h"
#include "types.h"

class GolCamera;
class GolD3DRenderDevice;
class RaceSession;

// SIZE 0x08
class RaceEventDispatcher0x08 {
public:
	// VTABLE: LEGORACERS 0x004b40c4
	// SIZE 0x10
	class Item {
	public:
		Item();
		virtual void VTable0x00(undefined4);             // vtable+0x00
		virtual void VTable0x04(void*) = 0;              // vtable+0x04
		virtual void VTable0x08(void*) = 0;              // vtable+0x08
		virtual ~Item();                                 // vtable+0x0c
		virtual void VTable0x10() = 0;                   // vtable+0x10
		virtual void VTable0x14(undefined4);             // vtable+0x14
		virtual void VTable0x18(GolCamera*, undefined4); // vtable+0x18
		virtual void VTable0x1c(GolD3DRenderDevice*);    // vtable+0x1c
		virtual LegoBool32 VTable0x20();                 // vtable+0x20
		virtual void VTable0x24();                       // vtable+0x24
		virtual void VTable0x28(LegoS32, void*);         // vtable+0x28
		virtual void VTable0x2c(LegoS32, void*);         // vtable+0x2c

		LegoS32 Reset();
		void FUN_0048a470(void* p_unk0x04);
		void FUN_0048a490(void* p_unk0x04);

		// SYNTHETIC: LEGORACERS 0x0048a420
		// RaceEventDispatcher0x08::Item::`scalar deleting destructor'

	private:
		friend class RaceEventDispatcher0x08;

		undefined4 m_unk0x04; // 0x04
		LegoS32 m_unk0x08;    // 0x08
		LegoS32 m_unk0x0c;    // 0x0c
	};

	class Context {
	public:
		class Field0x5c {
		public:
			virtual void VTable0x00() = 0;           // vtable+0x00
			virtual void VTable0x04(undefined*) = 0; // vtable+0x04
		};

	private:
		friend class RaceEventDispatcher0x08;

		undefined m_unk0x00[0x5c]; // 0x00
		Field0x5c* m_unk0x5c;      // 0x5c
	};

	RaceEventDispatcher0x08();
	~RaceEventDispatcher0x08();

	void FUN_0048aad0(LegoS32 p_unk0x04, void* p_unk0x08);
	void FUN_0048ab20(LegoS32 p_unk0x04, void* p_unk0x08);
	void FUN_0048ab70(LegoS32 p_unk0x04);
	void FUN_0048abb0(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_unk0x0c);
	void FUN_0048ac30(LegoS32 p_unk0x04, Context* p_context);
	void FUN_0048aca0(LegoS32 p_unk0x04, Context* p_context);
	void FUN_0048ad10(LegoS32 p_unk0x04, LegoS32 p_unk0x08, Context* p_context);
	void FUN_0048add0(undefined4 p_unk0x04);
	void FUN_0048ae00(GolCamera* p_unk0x04, undefined4 p_unk0x08);
	void FUN_0048ae30(GolD3DRenderDevice* p_renderer);
	void FUN_0048ae60();

private:
	friend class RaceSession;

	void Destroy();

	LegoU32 m_count;  // 0x00
	Item** m_entries; // 0x04
};

#endif

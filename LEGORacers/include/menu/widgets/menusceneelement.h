#ifndef MENUSCENEELEMENT_H
#define MENUSCENEELEMENT_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

class GolD3DRenderDevice;
class GolExport;
class MenuSceneView;

// VTABLE: LEGORACERS 0x004b2228
// SIZE 0x1c
class MenuSceneElement {
public:
	// SIZE 0x0c
	struct CreateParams {
		GolExport* m_golExport;         // 0x00
		GolD3DRenderDevice* m_renderer; // 0x04
		MenuSceneView* m_sceneView;     // 0x08
	};

	MenuSceneElement();
	virtual void Reset();                      // vtable+0x00
	virtual ~MenuSceneElement();               // vtable+0x04
	virtual LegoBool32 Destroy();              // vtable+0x08
	virtual LegoBool32 Draw() = 0;             // vtable+0x0c
	virtual LegoBool32 Update(undefined4) = 0; // vtable+0x10

	LegoBool32 Create(CreateParams* p_createParams);
	MenuSceneElement* Append(MenuSceneElement* p_parent);
	MenuSceneElement* GetNext() const { return m_next; }

	// SYNTHETIC: LEGORACERS 0x0046b2b0
	// MenuSceneElement::`scalar deleting destructor'

protected:
	MenuSceneElement* m_prev;       // 0x04
	MenuSceneElement* m_next;       // 0x08
	GolExport* m_golExport;         // 0x0c
	GolD3DRenderDevice* m_renderer; // 0x10
	MenuSceneView* m_sceneView;     // 0x14
	LegoBool32 m_created;           // 0x18
};

#endif // MENUSCENEELEMENT_H

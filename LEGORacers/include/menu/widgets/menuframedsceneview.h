#ifndef MENUFRAMEDSCENEVIEW_H
#define MENUFRAMEDSCENEVIEW_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuframe.h"
#include "menu/widgets/menusceneview.h"

// VTABLE: LEGORACERS 0x004b1e40
// SIZE 0x4d8
class MenuFramedSceneView : public MenuSceneView {
public:
	// SIZE 0x88
	class CreateParams : public MenuSceneView::CreateParams {
	public:
		MenuFrame::CreateParams* m_unk0x84; // 0x84
	};

	MenuFramedSceneView();
	~MenuFramedSceneView() override; // vtable+0x04

	LegoBool32 Create(CreateParams* p_createParams, undefined4 p_binary);

	// SYNTHETIC: LEGORACERS 0x00466100
	// MenuFramedSceneView::`scalar deleting destructor'

protected:
	LegoBool32 CreateFrame(CreateParams* p_createParams);

	MenuFrame m_frame; // 0x0dc
};

#endif // MENUFRAMEDSCENEVIEW_H

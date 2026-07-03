#ifndef SCENEREFBINDING_H
#define SCENEREFBINDING_H

#include "menu/widgets/menuwidget.h"
#include "types.h"

// SIZE 0x54
class SceneRefBinding : public MenuWidget::CreateParams {
public:
	LegoChar m_cutsceneName[0x48 - 0x38]; // 0x38
	undefined4 m_autoAdvance;             // 0x48
	LegoU32 m_startFrameIndex;            // 0x4c
	LegoFloat m_aspectScale;              // 0x50
};

#endif // SCENEREFBINDING_H

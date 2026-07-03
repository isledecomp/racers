#ifndef CARMODELSCREENBASE_H
#define CARMODELSCREENBASE_H

#include "compat.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "menu/screens/awardcinematicscreen.h"
#include "menu/screens/carbuildscreenbase.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menucarouselnavigator.h"
#include "menu/widgets/menuframedsceneview.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menusceneelement.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "model/carbuildmodel.h"
#include "racer/carpartcarousel.h"
#include "render/golrenderdevice.h"

class MenuGameContext;
class MenuScreenCreateParams;
class SoundGroupBinding;
class CmbModelPart;
class GolModelBase;
class GolSceneNode;
class GolWorldEntity;

// VTABLE: LEGORACERS 0x004b2cf8
// SIZE 0x2b20
class CarModelScreenBase : public CarBuildScreenBase {
public:
	enum {
		c_modeBrowse = 1,
		c_modeCarView = 2,
		c_modePieceView = 3,
		c_modeResetView = 5,
		c_modeBusy = 6,
	};

	enum {
		c_carBuildSaveBufferSize = 0x202,
		c_partCategoryCount = 12,
		c_alwaysAvailablePartCategoryCount = 4,
		c_saveUnlockedPartCategoryCount = c_partCategoryCount - c_alwaysAvailablePartCategoryCount
	};

	// VTABLE: LEGORACERS 0x004b2edc
	// SIZE 0x2d0
	class CarPartPlacement : public MenuSceneElement {
	public:
		enum {
			c_flagRotatingAroundCar = 1 << 0,
			c_flagPitchChanging = 1 << 1,
			c_flagCommittingPart = 1 << 2,
			c_flagResettingView = 1 << 3,
			c_placementFeedbackLowering = 1 << 0,
			c_placementFeedbackHold = 1 << 1,
			c_placementFeedbackRaising = 1 << 2,
			c_placementFeedbackMask =
				c_placementFeedbackLowering | c_placementFeedbackHold | c_placementFeedbackRaising,
		};

		// SIZE 0x30
		struct CreateParams : public MenuSceneElement::CreateParams {
			undefined4 m_unk0x0c;                   // 0x0c
			SoundGroupBinding* m_soundGroupBinding; // 0x10
			MenuGameContext* m_context;             // 0x14
			CarModelScreenBase* m_screen;           // 0x18
			GolVec3 m_piecePosition;                // 0x1c
			LegoFloat m_unk0x28;                    // 0x28
			undefined4 m_useBinaryFiles;            // 0x2c
		};

		CarPartPlacement();
		void Reset() override;                  // vtable+0x00
		~CarPartPlacement() override;           // vtable+0x04
		LegoBool32 Destroy() override;          // vtable+0x08
		LegoBool32 Draw() override;             // vtable+0x0c
		LegoBool32 Update(undefined4) override; // vtable+0x10
		LegoBool32 Create(CreateParams* p_createParams);
		void SelectPieceChoice(LegoS32 p_choice);
		LegoBool32 RotateViewAnalog(LegoFloat p_delta);
		LegoBool32 RotateViewStep(LegoS32 p_delta, LegoBool32 p_setCurrentAngle);
		void SnapViewRotation();
		LegoBool32 PitchViewAnalog(LegoFloat p_delta);
		LegoBool32 PitchViewStep(LegoS32 p_delta, LegoBool32 p_setCurrentPosition);
		void SnapViewPitch();
		LegoBool32 BeginViewReset(LegoBool32 p_rotateFirst);
		void RotatePiece();
		LegoBool32 MovePieceX(LegoS32 p_delta);
		LegoBool32 MovePieceY(LegoS32 p_delta);
		LegoBool32 CommitPiece();
		LegoBool32 UndoLastPiece(LegoS32* p_partType, LegoS32* p_pieceType, LegoS32* p_colorRecordIndex);
		void BeginResetAnimation();
		void FocusCar();
		void FocusPiece();
		void ClearFocusPane();
		GolWorldEntity* GetCarGroup() { return &m_carGroup; }
		GolWorldEntity* GetPieceEntity() { return &m_pieceEntity; }
		LegoS32 GetFocusedPane() const { return m_focusedPane; }
		LegoS8 GetViewSlot() const { return m_viewSlot; }

		// SYNTHETIC: LEGORACERS 0x004779b0
		// CarModelScreenBase::CarPartPlacement::`scalar deleting destructor'

	private:
		void ResetCamera();
		void CreatePieceModel();
		void CreateDriverModel(undefined4 p_useBinaryFiles);
		void CreateCarGroup();
		void SetViewSlot(LegoS32 p_slot);
		void ApplyViewAngle(LegoFloat p_angle);
		void UpdatePieceBob(LegoS32 p_elapsed);
		void StartPieceRaise(LegoS32 p_elapsed);
		void StartPieceLower(LegoS32 p_elapsed);
		void UpdateViewRotation(LegoU32 p_elapsed);
		void UpdateViewPitch(LegoU32 p_elapsed);
		void UpdateCommitFeedback(LegoS32 p_elapsed);
		void UpdateResetAnimation(LegoS32 p_elapsed);
		void GetViewPosition(GolVec3* p_dest, LegoS32 p_index);

		CarModelScreenBase* m_screen;                      // 0x1c
		SoundGroupBinding* m_soundGroupBinding;            // 0x20
		MenuGameContext* m_context;                        // 0x24
		CarBuildModel::Placement m_placement;              // 0x28
		AwardCinematicScreen::SceneEntityGroup m_carGroup; // 0x58
		GolAnimatedEntity m_driverEntity;                  // 0xa8
		GolSceneNode* m_bodySceneNode;                     // 0x19c
		CmbModelPart* m_bodyModelPart;                     // 0x1a0
		GolModelEntity m_pieceEntity;                      // 0x1a4
		GolModelBase* m_pieceModel;                        // 0x234
		GolModelBase* m_driverModel;                       // 0x238
		GolRenderDevice::MaterialColor m_pieceMaterial;    // 0x23c
		undefined4 m_previewDirty;                         // 0x240
		undefined4 m_overlayVisible;                       // 0x244
		LegoU32 m_animFlags;                               // 0x248
		LegoU32 m_feedbackMs;                              // 0x24c
		GolVec3 m_piecePosition;                           // 0x250
		undefined4 m_selectedChoice;                       // 0x25c
		undefined4 m_unk0x260;                             // 0x260
		LegoU32 m_pieceAnimMs;                             // 0x264
		LegoU32 m_bobMs;                                   // 0x268
		LegoFloat m_pieceHeight;                           // 0x26c
		LegoFloat m_pieceRestHeight;                       // 0x270
		LegoFloat m_commitHeight;                          // 0x274
		LegoU8 m_pieceAnimPhase;                           // 0x278
		undefined m_unk0x279[0x27c - 0x279];               // 0x279
		GolVec3 m_cameraEye;                               // 0x27c
		LegoFloat m_viewPitch;                             // 0x288
		LegoS32 m_viewResetDelayMs;                        // 0x28c
		LegoU8 m_pitchTarget;                              // 0x290
		undefined m_unk0x291[0x294 - 0x291];               // 0x291
		LegoS32 m_focusedPane;                             // 0x294
		LegoS8 m_viewSlot;                                 // 0x298
		undefined m_unk0x299[0x29c - 0x299];               // 0x299
		LegoFloat m_viewAngle;                             // 0x29c
		LegoS32 m_viewAnimMs;                              // 0x2a0
		LegoS32 m_viewAnimRemainingMs;                     // 0x2a4
		LegoFloat m_viewAngles[8];                         // 0x2a8
		LegoFloat m_viewAngleF;                            // 0x2c8
		LegoFloat m_carSizeBlend;                          // 0x2cc
	};

	CarModelScreenBase();

	void OnCarouselSettled(MenuWidget*) override;    // vtable+0x10
	void OnIconUnfocused(MenuWidget*) override;      // vtable+0x38
	void OnWidgetValueChanged(MenuWidget*) override; // vtable+0x44
	void CreateWidgets() override;                   // vtable+0x4c
	void Reset() override;                           // vtable+0x54
	~CarModelScreenBase() override;                  // vtable+0x68
	LegoBool32 Update(undefined4) override;          // vtable+0x78
	void SetupLighting() override;                   // vtable+0x80
	void Navigate() override;                        // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*,
						  MenuScreenCreateParams*) override;                    // vtable+0x8c
	GolString* GetHelpString(undefined4) override = 0;                          // vtable+0x98
	GolFont* GetHelpFont(undefined4) override = 0;                              // vtable+0x9c
	void GetTooltipLayout(LegoS32*, LegoS32*, LegoS32*, LegoS32*) override = 0; // vtable+0xa0
	virtual void EnterBrowseMode() = 0;                                         // vtable+0xa4
	virtual void ExitBrowseMode() = 0;                                          // vtable+0xa8
	virtual void EnterCarViewMode() = 0;                                        // vtable+0xac
	virtual void ExitCarViewMode() = 0;                                         // vtable+0xb0
	virtual void EnterPieceViewMode() = 0;                                      // vtable+0xb4
	virtual void ExitPieceViewMode() = 0;                                       // vtable+0xb8
	virtual void EnterBusyMode() = 0;                                           // vtable+0xbc
	virtual void ExitBusyMode() = 0;                                            // vtable+0xc0
	virtual void ShowPlacementError();                                          // vtable+0xc4

	// SYNTHETIC: LEGORACERS 0x00476e60
	// CarModelScreenBase::`scalar deleting destructor'

protected:
	void CreatePlacementScene();
	void CreateCategoryCarousel();
	void PopulateCategoryCarousel();
	void SaveCarData();
	LegoBool32 MovePieceByDrag(LegoS32 p_deltaX, LegoS32 p_deltaY, LegoU16 p_sound, LegoBool32 p_independentAxes);
	void ApplyModeChange();

	MenuImage m_photoImage;                   // 0x3b4
	MenuCarouselNavigator m_categoryCarousel; // 0x410
	MenuSelector m_categorySelector;          // 0x4a4
	CarPartCarousel m_partCarousel;           // 0xe98
	MenuSelector m_pieceSelector;             // 0xfec
	MenuImage m_categoryIcons[12];            // 0x19e0
	MenuFramedSceneView m_sceneView;          // 0x1e30
	CarPartPlacement m_partPlacement;         // 0x2308
	MenuTextButton m_errorPopup;              // 0x25d8
	undefined4 m_unk0x28c8;                   // 0x28c8
	undefined4 m_unk0x28cc;                   // 0x28cc
	undefined4 m_unk0x28d0;                   // 0x28d0
	LegoU8 m_carBuildSaveBuffer[0x202];       // 0x28d4
	undefined m_unk0x2ad6[0x2ad8 - 0x2ad6];   // 0x2ad6
	undefined4 m_unk0x2ad8;                   // 0x2ad8
	undefined4 m_carouselAction;              // 0x2adc
	undefined4 m_mode;                        // 0x2ae0
	LegoU32 m_nextMode;                       // 0x2ae4
	LegoU8 m_partCategoryUnlockFlags;         // 0x2ae8
	undefined m_unk0x2ae9[0x2aec - 0x2ae9];   // 0x2ae9
	LegoBool32 m_partCategoryAvailable[12];   // 0x2aec
	undefined4 m_unk0x2b1c;                   // 0x2b1c
};

#endif // CARMODELSCREENBASE_H

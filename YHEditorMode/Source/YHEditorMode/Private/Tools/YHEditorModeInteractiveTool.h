// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolBuilder.h"
#include "BaseTools/ClickDragTool.h"
#include "YHEditorModeInteractiveTool.generated.h"


/**
 * Builder for UYHEditorModeInteractiveTool
 */
UCLASS()
class YHEDITORMODE_API UYHEditorModeInteractiveToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override { return true; }
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};
//----YHEM----
UCLASS()
class YHEDITORMODE_API UYHEditorModeYHITlBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override { return true; }
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};


/**
 * Property set for the UYHEditorModeInteractiveTool
 */
UCLASS(Transient)
class YHEDITORMODE_API UYHEditorModeInteractiveToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()

public:
	UYHEditorModeInteractiveToolProperties();

	/** First point of measurement */
	UPROPERTY(EditAnywhere, Category = Options)
	FVector StartPoint;

	/** Second point of measurement */
	UPROPERTY(EditAnywhere, Category = Options)
	FVector EndPoint;
	
	/** Current distance measurement */
	UPROPERTY(EditAnywhere, Category = Options)
	double Distance;
};

/** ----YHEM----
 * Property set for the UYHEditorModeInteractiveTool
 */
UCLASS(Transient)
class YHEDITORMODE_API UYHEditorModeInteractiveToolYHProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()

public:
	UYHEditorModeInteractiveToolYHProperties();

	/** First point of measurement */
	UPROPERTY(EditAnywhere, Category = Options)
	FVector StartPoint;

	/** Second point of measurement */
	UPROPERTY(EditAnywhere, Category = Options)
	FVector EndPoint;
	
	/** Current distance measurement */
	UPROPERTY(EditAnywhere, Category = Options)
	double Distance;

	UPROPERTY(EditAnywhere, Category = Options)
	FString MyTestString;
};



/**
 * UYHEditorModeInteractiveTool是一个示例工具，允许用户测量
 *两点之间的距离。通过单击拖动鼠标来设置第一个点，并且
 *第二点是通过shift-click-拖动鼠标来设置的。
 */
UCLASS()
class YHEDITORMODE_API UYHEditorModeInteractiveTool : public UInteractiveTool, public IClickDragBehaviorTarget
{
	GENERATED_BODY()

public:
	virtual void SetWorld(UWorld* World);

	/** UInteractiveTool overrides */
	virtual void Setup() override;
	virtual void Render(IToolsContextRenderAPI* RenderAPI) override;
	virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;

	/** IClickDragBehaviorTarget implementation */
	virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;
	virtual void OnClickPress(const FInputDeviceRay& PressPos) override;
	virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;
	// these are not used in this Tool
	virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override {}
	virtual void OnTerminateDragSequence() override {}

	/** IModifierToggleBehaviorTarget implementation (inherited via IClickDragBehaviorTarget) */
	virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;


protected:
	/** Properties of the tool are stored here */
	UPROPERTY()
	TObjectPtr<UYHEditorModeInteractiveToolProperties> Properties;
	
protected:
	UWorld* TargetWorld = nullptr;		// target World we will raycast into

	static const int MoveSecondPointModifierID = 1;		// identifier we associate with the shift key
	bool bSecondPointModifierDown = false;				// flag we use to keep track of modifier state
	bool bMoveSecondPoint = false;						// flag we use to keep track of which point we are moving during a press-drag

	FInputRayHit FindRayHit(const FRay& WorldRay, FVector& HitPos);		// raycasts into World
	void UpdatePosition(const FRay& WorldRay);					// updates first or second point based on raycast
	void UpdateDistance();										// updates distance
};

//----YHRP---- My Editor Properties Copy from UYHEditorModeInteractiveTool
UCLASS()
class YHEDITORMODE_API UYHEditorModeYHInteractiveTool : public UInteractiveTool, public IClickDragBehaviorTarget
{
	GENERATED_BODY()

public:
	virtual void SetWorld(UWorld* World);

	/** UInteractiveTool overrides */
	virtual void Setup() override;
	virtual void Render(IToolsContextRenderAPI* RenderAPI) override;
	virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;

	/** IClickDragBehaviorTarget implementation */
	virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;
	virtual void OnClickPress(const FInputDeviceRay& PressPos) override;
	virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;
	// these are not used in this Tool
	virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override {}
	virtual void OnTerminateDragSequence() override {}

	/** IModifierToggleBehaviorTarget implementation (inherited via IClickDragBehaviorTarget) */
	virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;

protected:
	UPROPERTY()
	TObjectPtr<UYHEditorModeInteractiveToolYHProperties> Properties;
	UPROPERTY()
	TObjectPtr<UYHEditorModeInteractiveToolProperties> Properties_1;

protected:
	UWorld* TargetWorld = nullptr;		// target World we will raycast into

	static const int MoveSecondPointModifierID = 1;		// identifier we associate with the shift key
	bool bSecondPointModifierDown = false;				// flag we use to keep track of modifier state
	bool bMoveSecondPoint = false;						// flag we use to keep track of which point we are moving during a press-drag

	FInputRayHit FindRayHit(const FRay& WorldRay, FVector& HitPos);		// raycasts into World
	void UpdatePosition(const FRay& WorldRay);					// updates first or second point based on raycast
	void UpdateDistance();										// updates distance
};

// Copyright Epic Games, Inc. All Rights Reserved.

#include "YHEditorModeInteractiveTool.h"
#include "InteractiveToolManager.h"
#include "ToolBuilderUtil.h"
#include "BaseBehaviors/ClickDragBehavior.h"

// for raycast into World
#include "CollisionQueryParams.h"
#include "Engine/World.h"

#include "SceneManagement.h"

// localization namespace
#define LOCTEXT_NAMESPACE "UYHEditorModeInteractiveTool"

/*
 * ToolBuilder
 */

UInteractiveTool* UYHEditorModeInteractiveToolBuilder::BuildTool(const FToolBuilderState & SceneState) const
{
	UYHEditorModeInteractiveTool* NewTool = NewObject<UYHEditorModeInteractiveTool>(SceneState.ToolManager);
	NewTool->SetWorld(SceneState.World);
	return NewTool;
}


// JAH TODO: update comments
/*
 * Tool
 */

//----YHEM----
UInteractiveTool* UYHEditorModeYHITlBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	UYHEditorModeYHInteractiveTool* NewTool = NewObject<UYHEditorModeYHInteractiveTool>(SceneState.ToolManager);
	NewTool->SetWorld(SceneState.World);
	return NewTool;
}

UYHEditorModeInteractiveToolProperties::UYHEditorModeInteractiveToolProperties()
{
	// initialize the points and distance to reasonable values
	StartPoint = FVector(0,0,0);
	EndPoint = FVector(0,0,100);
	Distance = 100;
}

//----YHEM---- UYHEditorModeInteractiveToolYHProperties Init
UYHEditorModeInteractiveToolYHProperties::UYHEditorModeInteractiveToolYHProperties()
{
	// initialize the points and distance to reasonable values
	StartPoint = FVector(0, 0, 0);
	EndPoint = FVector(0, 0, 100);
	Distance = 100;
	MyTestString = "Hello World";
}
//----YHEM---- UYHEditorModeInteractiveToolYHProperties Init

void UYHEditorModeInteractiveTool::SetWorld(UWorld* World)
{
	check(World);
	this->TargetWorld = World;
}


void UYHEditorModeInteractiveTool::Setup()
{
	UInteractiveTool::Setup();

	// Add default mouse input behavior
	UClickDragInputBehavior* MouseBehavior = NewObject<UClickDragInputBehavior>();
	// We will use the shift key to indicate that we should move the second point. 
	// This call tells the Behavior to call our OnUpdateModifierState() function on mouse-down and mouse-move
	MouseBehavior->Modifiers.RegisterModifier(MoveSecondPointModifierID, FInputDeviceState::IsShiftKeyDown);
	MouseBehavior->Initialize(this);
	AddInputBehavior(MouseBehavior);

	// Create the property set and register it with the Tool
	Properties = NewObject<UYHEditorModeInteractiveToolProperties>(this, "Measurement");
	AddToolPropertySource(Properties);
	
	
	bSecondPointModifierDown = false;
	bMoveSecondPoint = false;
}


void UYHEditorModeInteractiveTool::OnUpdateModifierState(int ModifierID, bool bIsOn)
{
	// keep track of the "second point" modifier (shift key for mouse input)
	if (ModifierID == MoveSecondPointModifierID)
	{
		bSecondPointModifierDown = bIsOn;
	}
}


FInputRayHit UYHEditorModeInteractiveTool::CanBeginClickDragSequence(const FInputDeviceRay& PressPos)
{
	// we only start drag if press-down is on top of something we can raycast
	FVector Temp;
	FInputRayHit Result = FindRayHit(PressPos.WorldRay, Temp);
	return Result;
}


void UYHEditorModeInteractiveTool::OnClickPress(const FInputDeviceRay& PressPos)
{
	// determine whether we are moving first or second point for the drag sequence
	bMoveSecondPoint = bSecondPointModifierDown;
	UpdatePosition(PressPos.WorldRay);
}


void UYHEditorModeInteractiveTool::OnClickDrag(const FInputDeviceRay& DragPos)
{
	UpdatePosition(DragPos.WorldRay);
}


FInputRayHit UYHEditorModeInteractiveTool::FindRayHit(const FRay& WorldRay, FVector& HitPos)
{
	// trace a ray into the World
	FCollisionObjectQueryParams QueryParams(FCollisionObjectQueryParams::AllObjects);
	FHitResult Result;
	bool bHitWorld = TargetWorld->LineTraceSingleByObjectType(Result, WorldRay.Origin, WorldRay.PointAt(999999), QueryParams);
	if (bHitWorld)
	{
		HitPos = Result.ImpactPoint;
		return FInputRayHit(Result.Distance);
	}
	return FInputRayHit();
}


void UYHEditorModeInteractiveTool::UpdatePosition(const FRay& WorldRay)
{
	FInputRayHit HitResult = FindRayHit(WorldRay, (bMoveSecondPoint) ? Properties->EndPoint : Properties->StartPoint);
	if (HitResult.bHit)
	{
		UpdateDistance();
	}
}


void UYHEditorModeInteractiveTool::UpdateDistance()
{
	Properties->Distance = FVector::Distance(Properties->StartPoint, Properties->EndPoint);
}

/*
 *	Begin ------YHEM------ Tool Properties
 *
 *----YHEM---- My Editor Tool Properties
*/
void UYHEditorModeYHInteractiveTool::SetWorld(UWorld* World)
{
	check(World);
	this->TargetWorld = World;
}
void UYHEditorModeYHInteractiveTool::UpdateDistance()
{
	Properties->Distance = FVector::Distance(Properties->StartPoint, Properties->EndPoint);
}
FInputRayHit UYHEditorModeYHInteractiveTool::FindRayHit(const FRay& WorldRay, FVector& HitPos)
{
	// trace a ray into the World
	FCollisionObjectQueryParams QueryParams(FCollisionObjectQueryParams::AllObjects);
	FHitResult Result;
	bool bHitWorld = TargetWorld->LineTraceSingleByObjectType(Result, WorldRay.Origin, WorldRay.PointAt(999999), QueryParams);
	if (bHitWorld)
	{
		HitPos = Result.ImpactPoint;
		return FInputRayHit(Result.Distance);
	}
	return FInputRayHit();
}
void UYHEditorModeYHInteractiveTool::UpdatePosition(const FRay& WorldRay)
{
	FInputRayHit HitResult = FindRayHit(WorldRay, (bMoveSecondPoint) ? Properties->EndPoint : Properties->StartPoint);
	if (HitResult.bHit)
	{
		UpdateDistance();
	}
}
void UYHEditorModeYHInteractiveTool::Setup()
{
	Super::Setup();

	// Add default mouse input behavior
	UClickDragInputBehavior* MouseBehavior = NewObject<UClickDragInputBehavior>();
	// This call tells the Behavior to call our OnUpdateModifierState() function on mouse-down and mouse-move
	MouseBehavior->Modifiers.RegisterModifier(MoveSecondPointModifierID, FInputDeviceState::IsShiftKeyDown);
	MouseBehavior->Initialize(this);
	AddInputBehavior(MouseBehavior);

	// Create the property set and register it with the Tool	//----YHEM----这里 创建EditorMode下的Detail
	Properties = NewObject<UYHEditorModeInteractiveToolYHProperties>(this , "TestTool");
	Properties_1 = NewObject<UYHEditorModeInteractiveToolProperties>(this , "TestTool_1");
	AddToolPropertySource(Properties);
	AddToolPropertySource(Properties_1);

	bSecondPointModifierDown = false;
	bMoveSecondPoint = false;
}
void UYHEditorModeYHInteractiveTool::Render(IToolsContextRenderAPI* RenderAPI)
{
	Super::Render(RenderAPI);
	FPrimitiveDrawInterface* PDI = RenderAPI->GetPrimitiveDrawInterface();
	// draw a thin line that shows through objects
	PDI->DrawLine(Properties->StartPoint, Properties->EndPoint,
		FColor(240, 16, 16), SDPG_Foreground, 2.0f, 0.0f, true);
	// draw a thicker line that is depth-tested
	PDI->DrawLine(Properties->StartPoint, Properties->EndPoint,
		FColor(240, 16, 16), SDPG_World, 4.0f, 0.0f, true);
}
void UYHEditorModeYHInteractiveTool::OnPropertyModified(UObject* PropertySet, FProperty* Property)
{
	Super::OnPropertyModified(PropertySet, Property);
	UpdateDistance();
}
FInputRayHit UYHEditorModeYHInteractiveTool::CanBeginClickDragSequence(const FInputDeviceRay& PressPos)
{
	// we only start drag if press-down is on top of something we can raycast
	// 只有当按下按钮位于我们可以光线投射的物体上时，我们才会开始拖动
	FVector Temp;
	FInputRayHit Result = FindRayHit(PressPos.WorldRay, Temp);
	return Result;
}
void UYHEditorModeYHInteractiveTool::OnClickPress(const FInputDeviceRay& PressPos)
{
	// 确定我们是移动拖动序列的第一个点还是第二个点
	bMoveSecondPoint = bSecondPointModifierDown;
	UpdatePosition(PressPos.WorldRay);
}
void UYHEditorModeYHInteractiveTool::OnClickDrag(const FInputDeviceRay& DragPos)
{
	UpdatePosition(DragPos.WorldRay);
}
void UYHEditorModeYHInteractiveTool::OnUpdateModifierState(int ModifierID, bool bIsOn)
{
	IClickDragBehaviorTarget::OnUpdateModifierState(ModifierID, bIsOn);

	// keep track of the "second point" modifier (shift key for mouse input)
	if (ModifierID == MoveSecondPointModifierID)
	{
		bSecondPointModifierDown = bIsOn;
	}
}
/*	End ------YHEM------ Tool Properties
 *----YHEM---- My Editor Tool Properties
*/

void UYHEditorModeInteractiveTool::OnPropertyModified(UObject* PropertySet, FProperty* Property)
{
	// if the user updated any of the property fields, update the distance
	UpdateDistance();
}


void UYHEditorModeInteractiveTool::Render(IToolsContextRenderAPI* RenderAPI)
{
	FPrimitiveDrawInterface* PDI = RenderAPI->GetPrimitiveDrawInterface();
	// draw a thin line that shows through objects
	PDI->DrawLine(Properties->StartPoint, Properties->EndPoint,
		FColor(240, 16, 16), SDPG_Foreground, 2.0f, 0.0f, true);
	// draw a thicker line that is depth-tested
	PDI->DrawLine(Properties->StartPoint, Properties->EndPoint,
		FColor(240, 16, 16), SDPG_World, 4.0f, 0.0f, true);
}


#undef LOCTEXT_NAMESPACE

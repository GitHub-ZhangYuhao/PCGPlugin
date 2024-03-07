// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPCGSettings.h"

#include "PCGContext.h"
#include "Data/PCGPointData.h"
#include "Data/PCGSpatialData.h"

namespace MyPCGSettings
{
	const FName InputLable = TEXT("MyInputPin");
}

#define LOCTEXT_NAMESPACE "UMyPCGSettings"
TArray<FPCGPinProperties> UMyPCGSettings::InputPinProperties() const
{
	TArray<FPCGPinProperties> PinPropertieses;
	PinPropertieses.Emplace(
		MyPCGSettings::InputLable,
		EPCGDataType::Point ,
		true ,
		true,
		LOCTEXT("MyInputPinToolTip" , "My Input Pin Tooltip") );
	
	return PinPropertieses;
}
#undef LOCTEXT_NAMESPACE

FPCGElementPtr UMyPCGSettings::CreateElement() const
{
	return MakeShared<FMyPCGElemnt>();
}


FPCGContext* FMyPCGElemnt::Initialize(const FPCGDataCollection& InputData, TWeakObjectPtr<UPCGComponent> SourceComponent, const UPCGNode* Node)
{
	FPCGContext* Context = new FPCGContext();
	Context->InputData = InputData;
	Context->SourceComponent = SourceComponent;
	Context->Node = Node;
	return Context;
}

bool FMyPCGElemnt::ExecuteInternal(FPCGContext* Context) const
{
	TRACE_CPUPROFILER_EVENT_SCOPE(FMyPCGElemnt::ExecuteInternal);
	check(Context);

	//读取MyInputPin
	TArray<FPCGTaggedData> Inputs = Context->InputData.GetInputsByPin(MyPCGSettings::InputLable);
	for(const FPCGTaggedData Input : Inputs)
	{
		//获取InputPin中的Points
		const UPCGSpatialData* InputData = Cast<UPCGSpatialData>(Input.Data);
		const UPCGPointData* PointData = InputData->ToPointData(Context);
		const TArray<FPCGPoint>& Points = PointData->GetPoints();

		//打印每个Point的Transfrom信息
		for(const FPCGPoint Point : Points)
		{
			const FTransform PointTransform = Point.Transform;
			const FString TransformString = PointTransform.ToString();
			GEngine->AddOnScreenDebugMessage(-1 , 5.0f , FColor::White , TransformString);
		}
	}
	
	Context->OutputData.TaggedData = MoveTemp(Inputs);
	return true;
}

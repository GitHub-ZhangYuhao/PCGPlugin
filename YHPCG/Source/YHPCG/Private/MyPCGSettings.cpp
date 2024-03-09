// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPCGSettings.h"

#include "PCGContext.h"
#include "Data/PCGPointData.h"
#include "Data/PCGSpatialData.h"

#include "Metadata/Accessors/IPCGAttributeAccessor.h"
#include "Metadata/Accessors/PCGAttributeAccessorHelpers.h"
#include "PCGContext.h"
#include "Elements/Metadata/PCGMetadataElementCommon.h"

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

UMyPCGSettings::UMyPCGSettings()
{
	// 在创建节点时设置 AttributeSelector 读取的属性，读取 Point 上的 Seed 属性
	// 我们在随后的 FMyPCGElement::ExecuteInternal() 中没有对可能读取到的其他类型的属性做处理
	// 由于此原因，不要在编辑器中修改 AttributeSelector 的“$Seed”值，否则会引起程序崩溃
	AttributeSelector.SetPointProperty(EPCGPointProperties::Seed);
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

	/*// PCG 获取PointData的基础属性
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
	return true;*/


	// 通过变量访问特定于Attribute的第 0 号点的 Int 值
	const UMyPCGSettings* Settings = Context->GetInputSettings<UMyPCGSettings>();
	TArray<FPCGTaggedData> SourceInputs = Context->InputData.GetInputsByPin(MyPCGSettings::InputLable);

	// 防止 InputPin 为空时，后续的 InputAccessor 读取数组时发生越界
	if(SourceInputs.IsEmpty())
	{
		return true;
	}

	// 直接读取 MyInputPin 中的第一组数据
	const UPCGSpatialData* SpatialData = Cast<const UPCGSpatialData>(SourceInputs[0].Data);
	const UPCGPointData* PointData = SpatialData->ToPointData(Context);
	// 得到 MyPCGSettings 中的 AttributeSelector
	const FPCGAttributePropertyInputSelector InputAttributeSelector = Settings->AttributeSelector.CopyAndFixLast(PointData);

	// 创建 Accessor 和 Keys
	TUniquePtr<const IPCGAttributeAccessor> InputAccessor = PCGAttributeAccessorHelpers::CreateConstAccessor(PointData, InputAttributeSelector);
	TUniquePtr<const IPCGAttributeAccessorKeys> InputKeys = PCGAttributeAccessorHelpers::CreateConstKeys(PointData, InputAttributeSelector);

	int64 MyInt;
	// 通过访问器获取第一个 Point 上 AttributeSelector 指定的值
	InputAccessor->Get<int64>(MyInt, 0, *InputKeys);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("%lld"), MyInt));
	return true;
}

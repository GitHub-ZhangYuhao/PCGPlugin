// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPCGSettings.h"

#include "PCGContext.h"


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

	const UMyPCGSettings* Settings = Context->GetInputSettings<UMyPCGSettings>();

	FString ComponentName = Context->GetComponentName();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, /*FString::Printf(TEXT("FloatValue: %f"), Settings->FloatValue)*/ComponentName);
	return true;
}

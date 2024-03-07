// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PCGSettings.h"
#include "MyPCGSettings.generated.h"

/**
 * 
 */
UCLASS()
class YHPCG_API UMyPCGSettings : public UPCGSettings
{
	GENERATED_BODY()
	
public:
	// ~ Begin UPCGSettings Interface
#if WITH_EDITOR
	virtual FName GetDefaultNodeName() const override { return FName(TEXT("MyNode")); }
	virtual FText GetDefaultNodeTitle() const override { return NSLOCTEXT("MyNode" , "NodeTitle" ,"MyNode");}
	virtual EPCGSettingsType GetType() const override { return EPCGSettingsType::Metadata; }
#endif
	// ~ End UPCGSettings Interface

protected:
	virtual TArray<FPCGPinProperties> InputPinProperties() const override;
	virtual TArray<FPCGPinProperties> OutputPinProperties() const override { return Super::DefaultPointOutputPinProperties(); }
	virtual FPCGElementPtr CreateElement() const override;
	
public:
	UPROPERTY(BlueprintReadWrite , EditAnywhere , Category = Settings , meta = (PCG_Overridable))
	float FloatValue = 0.f;
};

// PCGElement
class FMyPCGElemnt : public IPCGElement
{
public:
	virtual FPCGContext* Initialize(const FPCGDataCollection& InputData, TWeakObjectPtr<UPCGComponent> SourceComponent, const UPCGNode* Node) override;
protected:
	virtual bool ExecuteInternal(FPCGContext* Context) const override;
};
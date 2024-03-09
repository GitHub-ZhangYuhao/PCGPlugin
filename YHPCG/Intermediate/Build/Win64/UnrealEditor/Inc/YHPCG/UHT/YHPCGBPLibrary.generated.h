// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "YHPCGBPLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef YHPCG_YHPCGBPLibrary_generated_h
#error "YHPCGBPLibrary.generated.h already included, missing '#pragma once' in YHPCGBPLibrary.h"
#endif
#define YHPCG_YHPCGBPLibrary_generated_h

#define FID_PCGDev_Plugins_PCGPlugin_YHPCG_Source_YHPCG_Public_YHPCGBPLibrary_h_28_RPC_WRAPPERS \
	DECLARE_FUNCTION(execYHPCGSampleFunction);


#define FID_PCGDev_Plugins_PCGPlugin_YHPCG_Source_YHPCG_Public_YHPCGBPLibrary_h_28_INCLASS \
private: \
	static void StaticRegisterNativesUYHPCGBPLibrary(); \
	friend struct Z_Construct_UClass_UYHPCGBPLibrary_Statics; \
public: \
	DECLARE_CLASS(UYHPCGBPLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/YHPCG"), NO_API) \
	DECLARE_SERIALIZER(UYHPCGBPLibrary)


#define FID_PCGDev_Plugins_PCGPlugin_YHPCG_Source_YHPCG_Public_YHPCGBPLibrary_h_28_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UYHPCGBPLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UYHPCGBPLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UYHPCGBPLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UYHPCGBPLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UYHPCGBPLibrary(UYHPCGBPLibrary&&); \
	UYHPCGBPLibrary(const UYHPCGBPLibrary&); \
public: \
	NO_API virtual ~UYHPCGBPLibrary();


#define FID_PCGDev_Plugins_PCGPlugin_YHPCG_Source_YHPCG_Public_YHPCGBPLibrary_h_25_PROLOG
#define FID_PCGDev_Plugins_PCGPlugin_YHPCG_Source_YHPCG_Public_YHPCGBPLibrary_h_28_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PCGDev_Plugins_PCGPlugin_YHPCG_Source_YHPCG_Public_YHPCGBPLibrary_h_28_RPC_WRAPPERS \
	FID_PCGDev_Plugins_PCGPlugin_YHPCG_Source_YHPCG_Public_YHPCGBPLibrary_h_28_INCLASS \
	FID_PCGDev_Plugins_PCGPlugin_YHPCG_Source_YHPCG_Public_YHPCGBPLibrary_h_28_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> YHPCG_API UClass* StaticClass<class UYHPCGBPLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_PCGDev_Plugins_PCGPlugin_YHPCG_Source_YHPCG_Public_YHPCGBPLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

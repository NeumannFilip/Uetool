// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PowerLineToolLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class APowerLineActor;
class UObject;
#ifdef ENERGY_PowerLineToolLibrary_generated_h
#error "PowerLineToolLibrary.generated.h already included, missing '#pragma once' in PowerLineToolLibrary.h"
#endif
#define ENERGY_PowerLineToolLibrary_generated_h

#define FID_Energy_Source_Energy_PowerLineToolLibrary_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execCreatePowerLineFromSelectedActors);


#define FID_Energy_Source_Energy_PowerLineToolLibrary_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPowerLineToolLibrary(); \
	friend struct Z_Construct_UClass_UPowerLineToolLibrary_Statics; \
public: \
	DECLARE_CLASS(UPowerLineToolLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Energy"), NO_API) \
	DECLARE_SERIALIZER(UPowerLineToolLibrary)


#define FID_Energy_Source_Energy_PowerLineToolLibrary_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPowerLineToolLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPowerLineToolLibrary(UPowerLineToolLibrary&&); \
	UPowerLineToolLibrary(const UPowerLineToolLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPowerLineToolLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPowerLineToolLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPowerLineToolLibrary) \
	NO_API virtual ~UPowerLineToolLibrary();


#define FID_Energy_Source_Energy_PowerLineToolLibrary_h_13_PROLOG
#define FID_Energy_Source_Energy_PowerLineToolLibrary_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Energy_Source_Energy_PowerLineToolLibrary_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Energy_Source_Energy_PowerLineToolLibrary_h_16_INCLASS_NO_PURE_DECLS \
	FID_Energy_Source_Energy_PowerLineToolLibrary_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ENERGY_API UClass* StaticClass<class UPowerLineToolLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Energy_Source_Energy_PowerLineToolLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

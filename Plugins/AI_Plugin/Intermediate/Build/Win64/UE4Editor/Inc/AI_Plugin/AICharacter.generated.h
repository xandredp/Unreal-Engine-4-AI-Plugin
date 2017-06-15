// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class APawn;
class ASoundBlockingActor;
struct FVector;
#ifdef AI_PLUGIN_AICharacter_generated_h
#error "AICharacter.generated.h already included, missing '#pragma once' in AICharacter.h"
#endif
#define AI_PLUGIN_AICharacter_generated_h

#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execYellForHelp) \
	{ \
		P_GET_OBJECT(APawn,Z_Param_SensedPawn); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->YellForHelp(Z_Param_SensedPawn); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSoundBlockingActorInView) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(ASoundBlockingActor**)Z_Param__Result=this->GetSoundBlockingActorInView(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnHearNoise) \
	{ \
		P_GET_OBJECT(APawn,Z_Param_PawnInstigator); \
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Location); \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Volume); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnHearNoise(Z_Param_PawnInstigator,Z_Param_Out_Location,Z_Param_Volume); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnSeePlayer) \
	{ \
		P_GET_OBJECT(APawn,Z_Param_Pawn); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnSeePlayer(Z_Param_Pawn); \
		P_NATIVE_END; \
	}


#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execYellForHelp) \
	{ \
		P_GET_OBJECT(APawn,Z_Param_SensedPawn); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->YellForHelp(Z_Param_SensedPawn); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSoundBlockingActorInView) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(ASoundBlockingActor**)Z_Param__Result=this->GetSoundBlockingActorInView(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnHearNoise) \
	{ \
		P_GET_OBJECT(APawn,Z_Param_PawnInstigator); \
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Location); \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Volume); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnHearNoise(Z_Param_PawnInstigator,Z_Param_Out_Location,Z_Param_Volume); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnSeePlayer) \
	{ \
		P_GET_OBJECT(APawn,Z_Param_Pawn); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnSeePlayer(Z_Param_Pawn); \
		P_NATIVE_END; \
	}


#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAAICharacter(); \
	friend AI_PLUGIN_API class UClass* Z_Construct_UClass_AAICharacter(); \
	public: \
	DECLARE_CLASS(AAICharacter, ABaseCharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/AI_Plugin"), NO_API) \
	DECLARE_SERIALIZER(AAICharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_INCLASS \
	private: \
	static void StaticRegisterNativesAAICharacter(); \
	friend AI_PLUGIN_API class UClass* Z_Construct_UClass_AAICharacter(); \
	public: \
	DECLARE_CLASS(AAICharacter, ABaseCharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/AI_Plugin"), NO_API) \
	DECLARE_SERIALIZER(AAICharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAICharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAICharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAICharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAICharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAICharacter(AAICharacter&&); \
	NO_API AAICharacter(const AAICharacter&); \
public:


#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAICharacter(AAICharacter&&); \
	NO_API AAICharacter(const AAICharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAICharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAICharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAICharacter)


#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_PRIVATE_PROPERTY_OFFSET
#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_17_PROLOG
#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_PRIVATE_PROPERTY_OFFSET \
	AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_RPC_WRAPPERS \
	AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_INCLASS \
	AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_PRIVATE_PROPERTY_OFFSET \
	AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_INCLASS_NO_PURE_DECLS \
	AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID AI_Plugin_Plugins_AI_Plugin_Source_AI_Plugin_Public_AICharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

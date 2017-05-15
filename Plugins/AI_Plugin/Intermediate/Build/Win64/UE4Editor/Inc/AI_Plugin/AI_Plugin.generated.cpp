// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Boilerplate C++ definitions for a single module.
	This is automatically generated by UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "Private/AI_PluginPrivatePCH.h"
#include "GeneratedCppIncludes.h"
#include "AI_Plugin.generated.dep.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1AI_Plugin() {}
	void UAIComponent::StaticRegisterNativesUAIComponent()
	{
	}
	IMPLEMENT_CLASS(UAIComponent, 2569586676);
	void AMyPluginComponent::StaticRegisterNativesAMyPluginComponent()
	{
	}
	IMPLEMENT_CLASS(AMyPluginComponent, 1766499449);
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	ENGINE_API class UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API class UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API class UClass* Z_Construct_UClass_AActor();

	AI_PLUGIN_API class UClass* Z_Construct_UClass_UAIComponent_NoRegister();
	AI_PLUGIN_API class UClass* Z_Construct_UClass_UAIComponent();
	AI_PLUGIN_API class UClass* Z_Construct_UClass_AMyPluginComponent_NoRegister();
	AI_PLUGIN_API class UClass* Z_Construct_UClass_AMyPluginComponent();
	AI_PLUGIN_API class UPackage* Z_Construct_UPackage__Script_AI_Plugin();
	UClass* Z_Construct_UClass_UAIComponent_NoRegister()
	{
		return UAIComponent::StaticClass();
	}
	UClass* Z_Construct_UClass_UAIComponent()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UActorComponent();
			Z_Construct_UPackage__Script_AI_Plugin();
			OuterClass = UAIComponent::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20B00080;


PRAGMA_DISABLE_DEPRECATION_WARNINGS
				CPP_BOOL_PROPERTY_BITMASK_STRUCT(Sight, UAIComponent, bool);
				UProperty* NewProp_Sight = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Sight"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(Sight, UAIComponent), 0x0010000000000005, CPP_BOOL_PROPERTY_BITMASK(Sight, UAIComponent), sizeof(bool), true);
				CPP_BOOL_PROPERTY_BITMASK_STRUCT(Hearing, UAIComponent, bool);
				UProperty* NewProp_Hearing = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Hearing"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(Hearing, UAIComponent), 0x0010000000000005, CPP_BOOL_PROPERTY_BITMASK(Hearing, UAIComponent), sizeof(bool), true);
				UProperty* NewProp_PatrollingPoints = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("PatrollingPoints"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(PatrollingPoints, UAIComponent), 0x0010000000000005);
				UProperty* NewProp_PatrollingPoints_Inner = new(EC_InternalUseOnlyConstructor, NewProp_PatrollingPoints, TEXT("PatrollingPoints"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000, Z_Construct_UClass_AActor_NoRegister());
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintSpawnableComponent"), TEXT(""));
				MetaData->SetValue(OuterClass, TEXT("ClassGroupNames"), TEXT("Custom"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("AIComponent.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Public/AIComponent.h"));
				MetaData->SetValue(NewProp_Sight, TEXT("Category"), TEXT("AI Component|AI unit properties"));
				MetaData->SetValue(NewProp_Sight, TEXT("ModuleRelativePath"), TEXT("Public/AIComponent.h"));
				MetaData->SetValue(NewProp_Hearing, TEXT("Category"), TEXT("AI Component|AI unit properties"));
				MetaData->SetValue(NewProp_Hearing, TEXT("ModuleRelativePath"), TEXT("Public/AIComponent.h"));
				MetaData->SetValue(NewProp_Hearing, TEXT("ToolTip"), TEXT("AI properties"));
				MetaData->SetValue(NewProp_PatrollingPoints, TEXT("Category"), TEXT("AI Component|Patrolling points"));
				MetaData->SetValue(NewProp_PatrollingPoints, TEXT("ModuleRelativePath"), TEXT("Public/AIComponent.h"));
				MetaData->SetValue(NewProp_PatrollingPoints, TEXT("ToolTip"), TEXT("Array of target points for patrolling"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAIComponent(Z_Construct_UClass_UAIComponent, &UAIComponent::StaticClass, TEXT("UAIComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAIComponent);
	UClass* Z_Construct_UClass_AMyPluginComponent_NoRegister()
	{
		return AMyPluginComponent::StaticClass();
	}
	UClass* Z_Construct_UClass_AMyPluginComponent()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_AI_Plugin();
			OuterClass = AMyPluginComponent::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900080;


				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("ClassGroupNames"), TEXT("Custom"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("MyPluginComponent.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Public/MyPluginComponent.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMyPluginComponent(Z_Construct_UClass_AMyPluginComponent, &AMyPluginComponent::StaticClass, TEXT("AMyPluginComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMyPluginComponent);
	UPackage* Z_Construct_UPackage__Script_AI_Plugin()
	{
		static UPackage* ReturnPackage = NULL;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/AI_Plugin")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0xF76DD770;
			Guid.B = 0x6563B047;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

		}
		return ReturnPackage;
	}
#endif

PRAGMA_ENABLE_DEPRECATION_WARNINGS

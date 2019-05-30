// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/UnrealOpenMeshLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealOpenMeshLibrary() {}
// Cross Module References
	UNREALOPENMESH_API UClass* Z_Construct_UClass_UUnrealOpenMeshLibrary_NoRegister();
	UNREALOPENMESH_API UClass* Z_Construct_UClass_UUnrealOpenMeshLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_UnrealOpenMesh();
	UNREALOPENMESH_API UFunction* Z_Construct_UFunction_UUnrealOpenMeshLibrary_GetCube();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
// End Cross Module References
	void UUnrealOpenMeshLibrary::StaticRegisterNativesUUnrealOpenMeshLibrary()
	{
		UClass* Class = UUnrealOpenMeshLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetCube", &UUnrealOpenMeshLibrary::execGetCube },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_UUnrealOpenMeshLibrary_GetCube()
	{
		struct UnrealOpenMeshLibrary_eventGetCube_Parms
		{
			bool bFlatShaded;
			TArray<FVector> vertices;
			TArray<int32> triangles;
			TArray<FVector> normals;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_normals = { UE4CodeGen_Private::EPropertyClass::Array, "normals", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(UnrealOpenMeshLibrary_eventGetCube_Parms, normals), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_normals_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "normals", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_triangles = { UE4CodeGen_Private::EPropertyClass::Array, "triangles", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(UnrealOpenMeshLibrary_eventGetCube_Parms, triangles), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_triangles_Inner = { UE4CodeGen_Private::EPropertyClass::Int, "triangles", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_vertices = { UE4CodeGen_Private::EPropertyClass::Array, "vertices", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(UnrealOpenMeshLibrary_eventGetCube_Parms, vertices), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_vertices_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "vertices", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bFlatShaded_MetaData[] = {
				{ "NativeConst", "" },
			};
#endif
			auto NewProp_bFlatShaded_SetBit = [](void* Obj){ ((UnrealOpenMeshLibrary_eventGetCube_Parms*)Obj)->bFlatShaded = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bFlatShaded = { UE4CodeGen_Private::EPropertyClass::Bool, "bFlatShaded", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000082, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(UnrealOpenMeshLibrary_eventGetCube_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_bFlatShaded_SetBit)>::SetBit, METADATA_PARAMS(NewProp_bFlatShaded_MetaData, ARRAY_COUNT(NewProp_bFlatShaded_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_normals,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_normals_Inner,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_triangles,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_triangles_Inner,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_vertices,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_vertices_Inner,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_bFlatShaded,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "OpenMesh" },
				{ "ModuleRelativePath", "Public/UnrealOpenMeshLibrary.h" },
				{ "ToolTip", "@param bFlatShaded              returns the cube in a flat shaded version" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UUnrealOpenMeshLibrary, "GetCube", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04442401, sizeof(UnrealOpenMeshLibrary_eventGetCube_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UUnrealOpenMeshLibrary_NoRegister()
	{
		return UUnrealOpenMeshLibrary::StaticClass();
	}
	UClass* Z_Construct_UClass_UUnrealOpenMeshLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
				(UObject* (*)())Z_Construct_UPackage__Script_UnrealOpenMesh,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_UUnrealOpenMeshLibrary_GetCube, "GetCube" }, // 1340682566
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "UnrealOpenMeshLibrary.h" },
				{ "ModuleRelativePath", "Public/UnrealOpenMeshLibrary.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<UUnrealOpenMeshLibrary>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&UUnrealOpenMeshLibrary::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00100080u,
				FuncInfo, ARRAY_COUNT(FuncInfo),
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UUnrealOpenMeshLibrary, 3714303242);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UUnrealOpenMeshLibrary(Z_Construct_UClass_UUnrealOpenMeshLibrary, &UUnrealOpenMeshLibrary::StaticClass, TEXT("/Script/UnrealOpenMesh"), TEXT("UUnrealOpenMeshLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UUnrealOpenMeshLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

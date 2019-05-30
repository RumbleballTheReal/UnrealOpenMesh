// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FVector;
#ifdef UNREALOPENMESH_UnrealOpenMeshLibrary_generated_h
#error "UnrealOpenMeshLibrary.generated.h already included, missing '#pragma once' in UnrealOpenMeshLibrary.h"
#endif
#define UNREALOPENMESH_UnrealOpenMeshLibrary_generated_h

#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetCube) \
	{ \
		P_GET_UBOOL(Z_Param_bFlatShaded); \
		P_GET_TARRAY_REF(FVector,Z_Param_Out_vertices); \
		P_GET_TARRAY_REF(int32,Z_Param_Out_triangles); \
		P_GET_TARRAY_REF(FVector,Z_Param_Out_normals); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UUnrealOpenMeshLibrary::GetCube(Z_Param_bFlatShaded,Z_Param_Out_vertices,Z_Param_Out_triangles,Z_Param_Out_normals); \
		P_NATIVE_END; \
	}


#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetCube) \
	{ \
		P_GET_UBOOL(Z_Param_bFlatShaded); \
		P_GET_TARRAY_REF(FVector,Z_Param_Out_vertices); \
		P_GET_TARRAY_REF(int32,Z_Param_Out_triangles); \
		P_GET_TARRAY_REF(FVector,Z_Param_Out_normals); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UUnrealOpenMeshLibrary::GetCube(Z_Param_bFlatShaded,Z_Param_Out_vertices,Z_Param_Out_triangles,Z_Param_Out_normals); \
		P_NATIVE_END; \
	}


#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUUnrealOpenMeshLibrary(); \
	friend UNREALOPENMESH_API class UClass* Z_Construct_UClass_UUnrealOpenMeshLibrary(); \
public: \
	DECLARE_CLASS(UUnrealOpenMeshLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UnrealOpenMesh"), NO_API) \
	DECLARE_SERIALIZER(UUnrealOpenMeshLibrary) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUUnrealOpenMeshLibrary(); \
	friend UNREALOPENMESH_API class UClass* Z_Construct_UClass_UUnrealOpenMeshLibrary(); \
public: \
	DECLARE_CLASS(UUnrealOpenMeshLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UnrealOpenMesh"), NO_API) \
	DECLARE_SERIALIZER(UUnrealOpenMeshLibrary) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UUnrealOpenMeshLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UUnrealOpenMeshLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UUnrealOpenMeshLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UUnrealOpenMeshLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UUnrealOpenMeshLibrary(UUnrealOpenMeshLibrary&&); \
	NO_API UUnrealOpenMeshLibrary(const UUnrealOpenMeshLibrary&); \
public:


#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UUnrealOpenMeshLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UUnrealOpenMeshLibrary(UUnrealOpenMeshLibrary&&); \
	NO_API UUnrealOpenMeshLibrary(const UUnrealOpenMeshLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UUnrealOpenMeshLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UUnrealOpenMeshLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UUnrealOpenMeshLibrary)


#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_PRIVATE_PROPERTY_OFFSET
#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_12_PROLOG
#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_PRIVATE_PROPERTY_OFFSET \
	ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_RPC_WRAPPERS \
	ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_INCLASS \
	ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_PRIVATE_PROPERTY_OFFSET \
	ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_INCLASS_NO_PURE_DECLS \
	ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ThePaintProject_Plugins_UnrealOpenMesh_Source_UnrealOpenMesh_Public_UnrealOpenMeshLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

// Copyright by Schwarzlicht Fabrik 2019

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealOpenMeshLibrary.generated.h"

/**
 *
 */
UCLASS()
class UNREALOPENMESH_API UUnrealOpenMeshLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    /**
     *	@param bFlatShaded		returns the cube in a flat shaded version
     */
    UFUNCTION(BlueprintCallable, Category = "OpenMesh")
    static void GetCube(const float size, const bool bFlatShaded, TArray<FVector>& vertices, TArray<int32>& triangles, TArray<FVector>& normals);
};

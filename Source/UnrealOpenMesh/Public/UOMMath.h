// Copyright by Schwarzlicht Fabrik 2019

#pragma once

#include "CoreMinimal.h"
#include "Compatibility/Compatibility.h"


/**
 * 
 */
class UNREALOPENMESH_API FUnrealOpenMeshMath
{
public:
	/**
	 *	If the returned value is > 0 -> the point is above the plane
	 *	If the returned value is == 0 -> the point is one the plane
	 *	If the returned value is < 0 -> the point is below the plane
	 */
	inline static float ComparePlanePoint(const OpenMesh::FVector& planeNormal, const OpenMesh::FVector& planeLocation, const OpenMesh::FVector& point)
	{
		const OpenMesh::FVector directionPlanePoint = point - planeLocation;
		return static_cast<float>(dot(planeNormal,directionPlanePoint)); // dot product
	}
	
};

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
	inline static float ComparePlanePoint(const FVector& planeNormal, const FVector& planeLocation, const FVector& point)
	{
		FVector directionPlanePoint = (point - planeLocation);
		directionPlanePoint *= 100.f; // scale the vector to prevent it to small results
		return planeNormal | directionPlanePoint; // dot product
	}
	
};

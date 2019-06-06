// Copyright by Schwarzlicht Fabrik 2019

#pragma once

#include "CoreMinimal.h"
#include "OpenMesh/Core/Mesh/TriMeshT.hh"
#include "UOMMath.h"


class FUnrealOpenMeshAlgorithm
{
public:
    /**
     *	Checks if a point is inside a CONVEX mesh.
     *	For successful evaluation the faces of the mesh must be planar -> Only take in TriMeshT.
     */
    template <typename Kernel, typename PointType>
    static bool IsPointInsideMesh_Convex(const OpenMesh::TriMeshT<Kernel>& mesh, const PointType& point);

    /**
     *	Checks if the 1-ring neighborhood of a vertex is convex.
     *	For successful evaluation the faces of the mesh must be planar -> Only take in TriMeshT.
     */
    template <typename Kernel>
    static bool IsVertexNeighborhoodConvex(const OpenMesh::TriMeshT<Kernel>& mesh, const typename Kernel::VertexHandle vHandle);

    /**
     *  Checks a TriMeshT if it is convex.
     *	For successful evaluation the faces of the mesh must be planar -> Only take in TriMeshT.
     */
    template <typename Kernel>
    static bool IsMeshConvex(const OpenMesh::TriMeshT<Kernel>& mesh);

    template <typename Kernel>
    static typename Kernel::VertexHandle GetVertexClosestToPoint(const OpenMesh::PolyMeshT<Kernel>& mesh, const typename Kernel::Point& point);

    /**
     *	Returns the handle to a face around the specified vertex (vHandle) that matches
     *	the location of the specified point the most.
     *
     *  @param vHandle		Most appropriate is the vertex closest to point
     *  @param point		The location to find the matching face for
     */
    template <typename Kernel>
    static typename Kernel::FaceHandle GetEvidentFaceAtVertexByPoint(const OpenMesh::PolyMeshT<Kernel>& mesh, const typename Kernel::VertexHandle vHandle, const typename Kernel::Point& point);

};

template <typename Kernel, typename PointType>
static bool FUnrealOpenMeshAlgorithm::IsPointInsideMesh_Convex(const OpenMesh::TriMeshT<Kernel>& mesh, const PointType& point)
{
    // A point is inside a convex mesh, when it is below every plane defined by a planar face of the mesh.
    for (Kernel::ConstFaceIter faceIter = mesh.faces_begin(); faceIter != mesh.faces_end(); ++faceIter)
    {
        Kernel::Normal faceNormal = mesh.calc_face_normal(*faceIter);
        Kernel::Point faceVertex = mesh.point(*mesh.cfv_iter(*faceIter));
        if (FUnrealOpenMeshMath::ComparePlanePoint(faceNormal, faceVertex, point) > 0.f) return false;
    }

    return true;
}

template <typename Kernel>
bool FUnrealOpenMeshAlgorithm::IsVertexNeighborhoodConvex(const OpenMesh::TriMeshT<Kernel>& mesh, const typename Kernel::VertexHandle vHandle)
{
    // A vertex and its neighborhood is convex if all vertices in a 1-ring neighborhood of the specified vertex are on or below all planes
    // defined by the faces incident to the vertex.

    if (!vHandle.is_valid()) return false;

    for (Kernel::ConstVertexFaceIter vertexFaceIter = mesh.cvf_iter(vHandle); vertexFaceIter.is_valid(); ++vertexFaceIter)
    {
        Kernel::FaceHandle fHandle = *vertexFaceIter;
        if (!fHandle.is_valid())
        {
            ensure(0);
			continue;
        }

        Kernel::Normal faceNormal = mesh.calc_face_normal(fHandle);
        Kernel::Point faceVertex = mesh.point(vHandle);

        for (Kernel::ConstVertexVertexIter vertexVertexIter = mesh.cvv_iter(vHandle); vertexVertexIter.is_valid(); ++vertexVertexIter)
        {
            float result = FUnrealOpenMeshMath::ComparePlanePoint(faceNormal, faceVertex, mesh.point(*vertexVertexIter));
            if(FMath::IsNearlyZero(result, 0.000001f)) continue;
			if (result > 0)
			{
				UKismetSystemLibrary::PrintString(GWorld, FString::Printf(TEXT("result: %f"), result), true, true, FLinearColor::Red, 5.f);
				return false;
			}
        }
    }

    return true;
}

template <typename Kernel>
bool FUnrealOpenMeshAlgorithm::IsMeshConvex(const OpenMesh::TriMeshT<Kernel>& mesh)
{
    for (Kernel::ConstVertexIter vertexIter = mesh.vertices_begin(); vertexIter != mesh.vertices_end(); ++vertexIter)
    {
        if (!IsVertexNeighborhoodConvex()) return false;
    }

    return true;
}

template <typename Kernel>
typename Kernel::VertexHandle FUnrealOpenMeshAlgorithm::GetVertexClosestToPoint(const OpenMesh::PolyMeshT<Kernel>& mesh, const typename Kernel::Point& point)
{
    Kernel::VertexHandle vHandle;
    float lenLowestValue = BIG_NUMBER;
    for (Kernel::ConstVertexIter vertexIter = mesh.vertices_begin(); vertexIter != mesh.vertices_end(); ++vertexIter)
    {
        float lenSqr = OpenMesh::sqrnorm(point - mesh.point(*vertexIter)); // norm == length (!=normalize)
        if (lenSqr < lenLowestValue)
        {
            vHandle = *vertexIter;
            lenLowestValue = lenSqr;
        }
    }
    return vHandle;
}

template <typename Kernel>
typename Kernel::FaceHandle FUnrealOpenMeshAlgorithm::GetEvidentFaceAtVertexByPoint(const OpenMesh::PolyMeshT<Kernel>& mesh, const typename Kernel::VertexHandle vHandle, const typename Kernel::Point& point)
{
    // To get the most evident face, we take the face normal and dot product it with the directions from the faces vertices to the point.
    // The face with the highest dot product sum wins.

    if (!vHandle.is_valid()) return Kernel::FaceHandle();

    Kernel::Point vertexLocation = mesh.point(vHandle);
    Kernel::Normal directionPointVertex = (vertexLocation - point).normalize();

    float highestValue = SMALL_NUMBER;
    Kernel::FaceHandle incidentFaceHandle;

    // Loop over all faces that are incident to the vertex
    for (Kernel::ConstVertexFaceIter vertexFaceIter = mesh.cvf_iter(vHandle); vertexFaceIter.is_valid(); ++vertexFaceIter)
    {
        float dotSum = 0.f;
        Kernel::Normal faceNormal = mesh.calc_face_normal(*vertexFaceIter);
        // Loop over all vertices of the face
        for (Kernel::ConstFaceVertexIter faceVertexIter = mesh.cfv_iter(*vertexFaceIter); faceVertexIter.is_valid(); ++faceVertexIter)
        {
            Kernel::Normal direction = (point - mesh.point(*faceVertexIter)).normalize();
            dotSum += dot(faceNormal, direction);
        }

        if (dotSum > highestValue)
        {
            highestValue = dotSum;
            incidentFaceHandle = *vertexFaceIter;
        }
    }

    return incidentFaceHandle;
}

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

    template <typename Kernel>
    static bool IsEdgeConvex(const OpenMesh::TriMeshT<Kernel>& mesh, const typename Kernel::EdgeHandle eHandle);

    /**
     *  Checks a TriMeshT if it is convex.
     *	For successful evaluation the faces of the mesh must be planar -> Only take in TriMeshT.
     */
    template <typename Kernel>
    static bool IsMeshConvex(const OpenMesh::TriMeshT<Kernel>& mesh);

    template <typename Kernel>
    static typename Kernel::VertexHandle GetVertexClosestToPoint(const OpenMesh::PolyMeshT<Kernel>& mesh, const typename Kernel::Point& point);

    /**
     *	Get the vertex of a face that is closest to the specified point
     */
    template <typename Kernel>
    static typename Kernel::VertexHandle GetFaceVertexClosestToPoint(const OpenMesh::PolyMeshT<Kernel>& mesh, const typename Kernel::FaceHandle fHandle, const typename Kernel::Point& point);


    /**
     *	Returns the handle to a face which is the most evident face at point.
     *	Only works properly for a convex mesh.
     *
     *  @param point		The location to find the matching face for
     */
    template <typename Kernel>
    static typename Kernel::FaceHandle GetEvidentFaceByPoint(const OpenMesh::PolyMeshT<Kernel>& mesh, const typename Kernel::Point& point);

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
    // defined by the faces incident with the vertex.

    if (!vHandle.is_valid()) return false;

    TArray<Kernel::VertexHandle> faceVertexHandles;
    for (Kernel::ConstVertexFaceIter vertexFaceIter = mesh.cvf_iter(vHandle); vertexFaceIter.is_valid(); ++vertexFaceIter)
    {
        Kernel::FaceHandle fHandle = *vertexFaceIter;
        Kernel::Normal faceNormal = mesh.calc_face_normal(fHandle);
        Kernel::Point faceVertex = mesh.point(vHandle);

		faceVertexHandles.Reset();
        for (Kernel::ConstFaceVertexIter faceVertexIter = mesh.cfv_iter(fHandle); faceVertexIter.is_valid(); ++faceVertexIter)
        {
            faceVertexHandles.Add(*faceVertexIter);
        }

        for (Kernel::ConstVertexVertexIter vertexVertexIter = mesh.cvv_iter(vHandle); vertexVertexIter.is_valid(); ++vertexVertexIter)
        {
            // Skip vertices that are also part of the face
            if (faceVertexHandles.Contains(*vertexVertexIter)) continue;

            float result = FUnrealOpenMeshMath::ComparePlanePoint(faceNormal, faceVertex, mesh.point(*vertexVertexIter));
            //if(FMath::IsNearlyZero(result, 0.000001f)) continue;
            if (result > 0)
            {
                //UKismetSystemLibrary::PrintString(GWorld, FString::Printf(TEXT("vertex result: %f"), result), true, true, FLinearColor::Red, 5.f);
                return false;
            }
        }
    }

    return true;
}

template <typename Kernel>
bool FUnrealOpenMeshAlgorithm::IsEdgeConvex(const OpenMesh::TriMeshT<Kernel>& mesh, const typename Kernel::EdgeHandle eHandle)
{
    if (!eHandle.is_valid()) return false;
    Kernel::HalfedgeHandle hHandle1 = mesh.halfedge_handle(eHandle, 0);
    Kernel::HalfedgeHandle hHandle2 = mesh.halfedge_handle(eHandle, 1);
    if (mesh.is_boundary(hHandle1) || mesh.is_boundary(hHandle2)) return true;

    Kernel::FaceHandle fHandle1 = mesh.face_handle(hHandle1);
    Kernel::FaceHandle fHandle2 = mesh.face_handle(hHandle2);

    Kernel::Normal face1Normal = mesh.calc_face_normal(fHandle1);
    Kernel::Point face1Location = mesh.point(*mesh.cfv_iter(fHandle1));

    TArray<Kernel::VertexHandle> face1VertexHandles;
    for (Kernel::ConstFaceVertexIter face1VertexIter = mesh.cfv_iter(fHandle1); face1VertexIter.is_valid(); ++face1VertexIter)
    {
        face1VertexHandles.Add(*face1VertexIter);
    }

    for (Kernel::ConstFaceVertexIter face2VertexIter = mesh.cfv_iter(fHandle2); face2VertexIter.is_valid(); ++face2VertexIter)
    {
        // Skip vertices that are also part of face 1
        if (face1VertexHandles.Contains(*face2VertexIter)) continue;

        float result = FUnrealOpenMeshMath::ComparePlanePoint(face1Normal, face1Location, mesh.point(*face2VertexIter));
        //if (FMath::IsNearlyZero(result, 0.000001f)) continue;
        if (result > 0)
        {
            //UKismetSystemLibrary::PrintString(GWorld, FString::Printf(TEXT("edge result: %f"), result), true, true, FLinearColor::Red, 5.f);
            return false;
        }
    }

    return true;
}

template <typename Kernel>
bool FUnrealOpenMeshAlgorithm::IsMeshConvex(const OpenMesh::TriMeshT<Kernel>& mesh)
{
    for (Kernel::ConstEdgeIter edgeIter = mesh.edges_begin(); edgeIter != mesh.edges_end(); ++edgeIter)
    {
        if (!IsEdgeConvex(mesh, *edgeIter)) return false;
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
typename Kernel::VertexHandle FUnrealOpenMeshAlgorithm::GetFaceVertexClosestToPoint(const OpenMesh::PolyMeshT<Kernel>& mesh, const typename Kernel::FaceHandle fHandle, const typename Kernel::Point& point)
{
    Kernel::VertexHandle vHandle;
    float closestDistance = BIG_NUMBER;
    for (Kernel::ConstFaceVertexIter faceVertexIter = mesh.cfv_iter(fHandle); faceVertexIter.is_valid(); ++faceVertexIter)
    {
        float distance = (point - mesh.point(*faceVertexIter)).sqrnorm();
        if (distance < closestDistance)
        {
            closestDistance = distance;
            vHandle = *faceVertexIter;
        }
    }
    return vHandle;
}

template <typename Kernel>
typename Kernel::FaceHandle FUnrealOpenMeshAlgorithm::GetEvidentFaceByPoint(const OpenMesh::PolyMeshT<Kernel>& mesh, const typename Kernel::Point& point)
{
    // To get the most evident face, we take the face normal and dot product it with the directions from the faces vertices to the point.
    // The face with the highest dot product sum wins.

    float highestValue = -BIG_NUMBER;
    Kernel::FaceHandle incidentFaceHandle;

    // Loop over all faces
    for (Kernel::ConstFaceIter faceIter = mesh.faces_begin(); faceIter != mesh.faces_end(); ++faceIter)
    {
        float dotSum = 0.f;
        Kernel::Normal faceNormal = mesh.calc_face_normal(*faceIter);
        // Loop over all vertices of the face
        for (Kernel::ConstFaceVertexIter faceVertexIter = mesh.cfv_iter(*faceIter); faceVertexIter.is_valid(); ++faceVertexIter)
        {
            Kernel::Normal direction = (point - mesh.point(*faceVertexIter)).normalize();
            dotSum += dot(faceNormal, direction);
        }

        if (dotSum > highestValue)
        {
            highestValue = dotSum;
            incidentFaceHandle = *faceIter;
        }
    }

    return incidentFaceHandle;
}

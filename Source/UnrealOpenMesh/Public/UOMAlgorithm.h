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
    // A vertex and its neighborhood is convex if all vertices in a 1-ring neighborhood of the specified vertex are on or below a plane
    // defined by one of the faces that are incident to the specified vertex.
    
	if (!vHandle.is_valid()) return false;

    Kernel::Normal faceNormal = mesh.calc_face_normal(*mesh.cvf_iter(vHandle));
    Kernel::Point faceVertex = mesh.point(vHandle);

    for (Kernel::ConstVertexVertexIter vertexVertexIter = mesh.cvv_iter(vHandle); vertexVertexIter.is_valid(); ++vertexVertexIter)
    {
        if (FUnrealOpenMeshMath::ComparePlanePoint(faceNormal, faceVertex, mesh.point(*vertexVertexIter)) > 0) return false;
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
    // The most evident face is evaluated by calculating the dot product of the face and
    // vertex incident edges and the direction of the vertex to the point.
    //
    //		# _
    //          - _
    //              - _ Halfedge2 (outgoing) (points to Face)
    // 	                - _
    //          Point *- _  - _
    //                     --  # vertex     ( clock wise edge iteration)
    //		Face           _ -
    // 	               _ / Halfedge1 (outgoing)
    //             _ /
    //            #
    //

	if (!vHandle.is_valid()) return Kernel::FaceHandle();

    Kernel::Point vertexLocation = mesh.point(vHandle);
    Kernel::Normal directionVertexPoint = (point - vertexLocation).normalize();
    Kernel::ConstVertexOHalfedgeCWIter vertexOutgoingHalfedgeCWIter = mesh.cvoh_cwiter(vHandle); // clockwise
    Kernel::HalfedgeHandle heHandle;

    heHandle = *vertexOutgoingHalfedgeCWIter;
    Kernel::Normal directionEdge1 = (mesh.point(mesh.to_vertex_handle(heHandle)) - vertexLocation).normalize();
	
	++vertexOutgoingHalfedgeCWIter; // Next halve edge
    Kernel::HalfedgeHandle heHandleHighestValue = *vertexOutgoingHalfedgeCWIter; // Init with second edge of first face
    float highestValue = SMALL_NUMBER;
    for (; vertexOutgoingHalfedgeCWIter.is_valid(); ++vertexOutgoingHalfedgeCWIter)
    {
        heHandle = *vertexOutgoingHalfedgeCWIter;
        Kernel::Normal directionEdge2 = (mesh.point(mesh.to_vertex_handle(heHandle)) - vertexLocation).normalize();

		float value = 0.f;
        value += dot(directionVertexPoint, directionEdge1);
        value += dot(directionVertexPoint, directionEdge2);

        if (value > highestValue)
        {
            highestValue = value;
            // To return the face, get the face from the second halfedge handle (assumes clock wise iteration)
            heHandleHighestValue = heHandle;
        }

        directionEdge1 = directionEdge2;
    }

    return mesh.face_handle(heHandleHighestValue);
}

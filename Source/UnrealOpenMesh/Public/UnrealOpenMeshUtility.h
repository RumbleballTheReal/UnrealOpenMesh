// Copyright by Schwarzlicht Fabrik 2019

#pragma once

#include "CoreMinimal.h"
#include "OpenMesh/Core/Mesh/TriMeshT.hh"
#include "Templates/EnableIf.h"

/**
 *
 */
class UNREALOPENMESH_API FUnrealOpenMeshUtility
{
public:
    FUnrealOpenMeshUtility() {}
    ~FUnrealOpenMeshUtility() {}

    /**
     *	Takes in any PolyMeshT and returns a flat shaded version.
     *	If the mesh was already flat shaded, nothing changes.
     *
     *	Will create duplicated vertices.
     *	Normals for the output mesh are only calculated when the input mesh has face normals
     *	and the output mesh has vertex normals set via the traits.
     */
    template <typename InKernel, typename OutKernel>
    static void ConvertToFlatShaded(const OpenMesh::PolyMeshT<InKernel>& inMesh, OpenMesh::PolyMeshT<OutKernel>& outMesh);

    /**
     *	Converts a TriMeshT to Unreals internal types. Unreal can only work with triangles meshes, so don't bother with PolyMeshT.
     *	
     *	This function will only compile when the point and normal type of the mesh kernel is OpenMesh::Vec3f (or derived).
     *	The mesh should not have any garbage laying around at this point: OpenMesh::ArrayKernel::garbage_collection
     *	
     *	@param bUpdateNormals    Set to true to update the normal information in the mesh. Only possible when normal are set via traits.
     *	@param bFlipNormals		 For some reason the normal calculated by OpenMesh is the wrong way round. If you didn't flip it already, this is the place to do it.
     */
    template <typename Kernel>
    static typename TEnableIf<
    __is_base_of(OpenMesh::Vec3f, typename Kernel::Point)
    && __is_base_of(OpenMesh::Vec3f, typename Kernel::Normal)
    , void>::Type
    PolyMeshToUnrealTypes(OpenMesh::TriMeshT<Kernel>& mesh, const bool bUpdateNormals, TArray<FVector>& outVertices, TArray<int32>& outIndices, TArray<FVector>* outNormals = nullptr);
};

template <typename InKernel, typename OutKernel>
void FUnrealOpenMeshUtility::ConvertToFlatShaded(const OpenMesh::PolyMeshT<InKernel>& inMesh, OpenMesh::PolyMeshT<OutKernel>& outMesh)
{
	// Flat Shaded is only useful when the out mesh has vertex normals.
	if (!outMesh.has_vertex_normals()) return;

	outMesh.clean();
	TArray<OutKernel::VertexHandle> vHandles;

	// Reserve some space. Usually we need more space for vertices and edges, but can't know how much.
	// Try to prevent as much reallocations as possible.
	outMesh.reserve(inMesh.n_vertices(), inMesh.n_edges(), inMesh.n_faces()); // vertices, edges, faces

	for (InKernel::ConstFaceIter faceIter = inMesh.faces_begin(); faceIter != inMesh.faces_end(); ++faceIter)
	{
		InKernel::Normal normal = inMesh.calc_face_normal(*faceIter);
		vHandles.Reset();

		for (InKernel::ConstFaceVertexIter faceVertexIter = inMesh.cfv_iter(*faceIter); faceVertexIter.is_valid(); ++faceVertexIter)
		{
			OutKernel::VertexHandle vhandle = outMesh.add_vertex(inMesh.point(*faceVertexIter));
			vHandles.Add(vhandle);
			outMesh.set_normal(vhandle, normal);
		}

		outMesh.add_face(vHandles.GetData(), vHandles.Num());
	}
}

template <typename Kernel>
typename TEnableIf<
	__is_base_of(OpenMesh::Vec3f, typename Kernel::Point)
	&& __is_base_of(OpenMesh::Vec3f, typename Kernel::Normal)
	, void>::Type
	FUnrealOpenMeshUtility::PolyMeshToUnrealTypes(OpenMesh::TriMeshT<Kernel>& mesh, const bool bUpdateNormals, TArray<FVector>& outVertices, TArray<int32>& outIndices, TArray<FVector>* outNormals /*= nullptr*/)
{
	if (mesh.n_vertices() == 0 || mesh.n_faces() == 0) return;
	outVertices.Reset();
	outIndices.Reset();

	// Positions
	{
		// We can do a simple copy of the binary data here, as the memory layout is the same.
		// check type size
		check(outVertices.GetTypeSize() == sizeof(mesh.property(mesh.points_pph()).data_vector()[0]));

		outVertices.SetNumUninitialized(mesh.n_vertices());
		// check array length
		check(outVertices.Num() >= mesh.property(mesh.points_pph()).data_vector().size());

		FMemory::Memcpy(outVertices.GetData(), mesh.points(), outVertices.GetAllocatedSize());
	}

	// Faces
	{
		outIndices.Reserve(mesh.n_faces() * 3); // Function assumes triangles
		// Faces itself do not exist es memory object. Faces are only a handle to a halve edge that would be part of the face
		// if it would exist. So we can only iterate.
		for (Kernel::ConstFaceIter faceIter = mesh.faces_begin(); faceIter != mesh.faces_end(); ++faceIter)
		{
			for (Kernel::ConstFaceVertexIter vertexIter = mesh.cfv_iter(*faceIter); vertexIter.is_valid(); ++vertexIter)
			{
				outIndices.Add((*vertexIter).idx());
			}
		}
	}

	// Normals
	if (outNormals)
	{
		outNormals->Reset();

		if (mesh.has_vertex_normals())
		{
			if (bUpdateNormals && mesh.has_face_normals())
			{
				// Vertex normals get updated from face normals
				mesh.update_face_normals();
				mesh.update_vertex_normals();
			}

			// We can do a simple copy of the binary data here, as the memory layout is the same.
			// check type size
			check(outNormals->GetTypeSize() == sizeof(mesh.property(mesh.vertex_normals_pph()).data_vector()[0]));

			outNormals->SetNumUninitialized(mesh.n_vertices());
			// check array length
			check(outNormals->Num() >= mesh.property(mesh.vertex_normals_pph()).data_vector().size());

			FMemory::Memcpy(outNormals->GetData(), mesh.vertex_normals(), outVertices.GetAllocatedSize());
		}
	}
}

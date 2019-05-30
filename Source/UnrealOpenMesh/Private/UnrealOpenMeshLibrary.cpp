// Copyright by Schwarzlicht Fabrik 2019

#include "UnrealOpenMeshLibrary.h"
#include "Compatibility/Compatibility.h"
#include "UnrealOpenMeshCreation.h"
#include "UnrealOpenMeshUtility.h"

#include "OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh"


void UUnrealOpenMeshLibrary::GetCube(const bool bFlatShaded, TArray<FVector>& vertices, TArray<int32>& triangles, TArray<FVector>& normals)
{
	vertices.Empty();
	normals.Empty();
	triangles.Empty();

	struct CustomTraits : public OpenMesh::DefaultTraits
	{
		typedef OpenMesh::LeftHandedType CoordinateSystemType;
		typedef OpenMesh::FVector  Point;
		typedef OpenMesh::FVector  Normal;
		typedef OpenMesh::FVector2D  TexCoord;
		typedef FColor Color;
		typedef float Scalar;

		VertexAttributes(OpenMesh::Attributes::Normal);
		FaceAttributes(OpenMesh::Attributes::Normal);
	};

	typedef OpenMesh::TriMesh_ArrayKernelT<CustomTraits> MyMesh;
	MyMesh mesh;

	FUnrealOpenMeshCreation::CreateCube(mesh);
	if (bFlatShaded)
	{
		MyMesh meshFlatShaded;
		FUnrealOpenMeshUtility::ConvertToFlatShaded(mesh, meshFlatShaded);
		mesh = MoveTemp(meshFlatShaded);
	}

	FUnrealOpenMeshUtility::PolyMeshToUnrealTypes(mesh, false, vertices, triangles, &normals);
}

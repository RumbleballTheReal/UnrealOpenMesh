// Copyright by Schwarzlicht Fabrik 2019

#pragma once

#include "CoreMinimal.h"
#include "OpenMesh/Core/Mesh/PolyMeshT.hh"

/**
 *
 */
class UNREALOPENMESH_API FUnrealOpenMeshCreation
{
public:
    FUnrealOpenMeshCreation();
    ~FUnrealOpenMeshCreation();

    /**
     *	Test function that uses OpenMesh to create a cube (smooth shading).
     *	It is also meant to be a reference and lookup of how things can be accomplished.
     */
    template <typename Kernel>
    static void CreateCube(OpenMesh::PolyMeshT<Kernel>& mesh, const float size);

};

template <typename Kernel>
void FUnrealOpenMeshCreation::CreateCube(OpenMesh::PolyMeshT<Kernel>& mesh, const float size)
{
    //typedef OpenMesh::TriMesh_ArrayKernelT<myTraits> MyMesh;

    mesh.clean(); // Emptys the mesh arrays but keeps the properties (see also clear(), which kills the properties)
    typedef Kernel MyMesh;

	float halfsize = size / 2.f;
    MyMesh::VertexHandle vhandle[8];
    vhandle[0] = mesh.add_vertex(MyMesh::Point(-halfsize, -halfsize, halfsize));
    vhandle[1] = mesh.add_vertex(MyMesh::Point(halfsize, -halfsize, halfsize));
    vhandle[2] = mesh.add_vertex(MyMesh::Point(halfsize, halfsize, halfsize));
    vhandle[3] = mesh.add_vertex(MyMesh::Point(-halfsize, halfsize, halfsize));
    vhandle[4] = mesh.add_vertex(MyMesh::Point(-halfsize, -halfsize, -halfsize));
    vhandle[5] = mesh.add_vertex(MyMesh::Point(halfsize, -halfsize, -halfsize));
    vhandle[6] = mesh.add_vertex(MyMesh::Point(halfsize, halfsize, -halfsize));
    vhandle[7] = mesh.add_vertex(MyMesh::Point(-halfsize, halfsize, -halfsize));
    // generate (quadrilateral) faces with counter clockwise order (CCW)
    std::vector<MyMesh::VertexHandle>  face_vhandles;
    // Top Face
    face_vhandles.clear();
    face_vhandles.push_back(vhandle[0]);
    face_vhandles.push_back(vhandle[3]);
    face_vhandles.push_back(vhandle[2]);
    face_vhandles.push_back(vhandle[1]);
    mesh.add_face(face_vhandles);
    // Bottom Face
    face_vhandles.clear();
    face_vhandles.push_back(vhandle[7]);
    face_vhandles.push_back(vhandle[4]);
    face_vhandles.push_back(vhandle[5]);
    face_vhandles.push_back(vhandle[6]);
    mesh.add_face(face_vhandles);
    // Left Face
    face_vhandles.clear();
    face_vhandles.push_back(vhandle[0]);
    face_vhandles.push_back(vhandle[1]);
    face_vhandles.push_back(vhandle[5]);
    face_vhandles.push_back(vhandle[4]);
    mesh.add_face(face_vhandles);
    // Front Face
    face_vhandles.clear();
    face_vhandles.push_back(vhandle[1]);
    face_vhandles.push_back(vhandle[2]);
    face_vhandles.push_back(vhandle[6]);
    face_vhandles.push_back(vhandle[5]);
    mesh.add_face(face_vhandles);
    // Right Face
    face_vhandles.clear();
    face_vhandles.push_back(vhandle[2]);
    face_vhandles.push_back(vhandle[3]);
    face_vhandles.push_back(vhandle[7]);
    face_vhandles.push_back(vhandle[6]);
    mesh.add_face(face_vhandles);
    // Back Face
    face_vhandles.clear();
    face_vhandles.push_back(vhandle[3]);
    face_vhandles.push_back(vhandle[0]);
    face_vhandles.push_back(vhandle[4]);
    face_vhandles.push_back(vhandle[7]);
    mesh.add_face(face_vhandles);

	// Normals
    {
        // Calculate the normal for each face and store it in a normal property for each face.
        // This is only possible when faces were given normals within the traits of the mesh.
        // !! The function itself does not check if the faces have normals. -> Crash if not
        //if(mesh.has_face_normals()) mesh.update_face_normals();
   

        // Calculate the normal for each vertex and store it in the normal property for each vertex.
        // This is only possible when vertices were given normals within the traits of the mesh.
        // This also requires the faces to have normals, as the vertex normals are calculated from the
        // normals of the connected faces.
        // !! The function itself does not check if faces/vertices have normals. -> Crash if not
        //if(mesh.has_face_normals() && mesh.has_vertex_normals()) mesh.update_vertex_normals();
   

        // Update all normals (Face/Edge/Vertex).
        // Checks if the properties have normals.
		mesh.update_normals();
    }

    // Mesh data num
    //int32 numVertices = mesh.n_vertices();
    //int32 numHalfedges = mesh.n_halfedges();
    //int32 numEdges = mesh.n_edges();
    //int32 numFaces = mesh.n_faces();
}

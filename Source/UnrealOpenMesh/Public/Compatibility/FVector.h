#pragma once

#include "CoreMinimal.h"
#include "OpenMesh/Core/Geometry/VectorT.hh"

//inline FVector normalize(const FVector& vec)
//{
//	return vec.GetSafeNormal();
//}
//
//inline float dot(const FVector& v1, const FVector& v2)
//{
//	return v1 | v2;
//}
//
////OpenMesh::vec3f
//template <>
//struct OpenMesh::vector_traits<FVector>
//{
//	/// Type of the vector class
//	typedef FVector vector_type;
//
//	/// Type of the scalar value
//	typedef float  value_type;
//
//	/// size/dimension of the vector
//	static const size_t size_ = 3; // Number of elements of the type
//
//	/// size/dimension of the vector
//	static size_t size() { return size_; }
//};

namespace OpenMesh
{
	struct FVector : public Vec3f
	{
		// Construct from Initialization-List
		template <typename ...Ts> 
		FVector(Ts ... vs) : Vec3f(vs...)
		{

		}

		// Implicit conversion to Unreals FVector
		operator ::FVector() const 
		{
			return ::FVector((*this)[0], (*this)[1], (*this)[2]);
		}
	/*	operator ::FVector&&()
		{
			return (::FVector&&)MoveTemp(*this);
		}*/
	};
}
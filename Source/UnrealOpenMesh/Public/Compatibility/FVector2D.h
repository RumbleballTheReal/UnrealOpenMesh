#pragma once

#include "CoreMinimal.h"

namespace OpenMesh
{
	struct FVector2D : public Vec3f
	{
		// Construct from Initialization-List
		template <typename ...Ts>
		FVector2D(Ts ... vs) : Vec2f(vs...)
		{

		}
	};
}
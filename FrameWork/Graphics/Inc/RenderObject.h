#pragma once

#include "MeshBuffer.h"
#include "Material.h"
#include "TextureManager.h"
#include "Transform.h"


namespace KTEngine::Graphics
{
	struct RenderObject
	{
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;

		Material material;

		TextureId diffuseMapId;
		TextureId normalMapId;
		TextureId specMapId;
		TextureId bumpMapId;
	};
}
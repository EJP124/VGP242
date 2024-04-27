#include "Precompiled.h"
#include "RenderObject.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
}
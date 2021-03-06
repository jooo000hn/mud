
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
        
#include <gfx/Generated/Forward.h>
#include <gfx/Generated/Types.h>

#include <gfx/Animated.h>
#include <gfx/Animation.h>
#include <gfx/Asset.h>
#include <gfx/Asset.impl.h>
#include <gfx/Camera.h>
#include <gfx/Draw.h>
#include <gfx/Effects.h>
#include <gfx/Filter.h>
#include <gfx/Frustum.h>
#include <gfx/Generator.h>
#include <gfx/Gfx.h>
#include <gfx/GfxSystem.h>
#include <gfx/Graph.h>
#include <gfx/Item.h>
#include <gfx/Light.h>
#include <gfx/ManualRender.h>
#include <gfx/Material.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Node3.h>
#include <gfx/Particles.h>
#include <gfx/Picker.h>
#include <gfx/Pipeline.h>
#include <gfx/Prefab.h>
#include <gfx/Program.h>
#include <gfx/Renderer.h>
#include <gfx/RenderTarget.h>
#include <gfx/Scene.h>
#include <gfx/Shader.h>
#include <gfx/Shot.h>
#include <gfx/Skeleton.h>
#include <gfx/Texture.h>
#include <gfx/Uniform.h>
#include <gfx/Viewport.h>
#include <gfx/Blocks/Sky.h>

namespace mud
{
	export_ class MUD_GFX_EXPORT mudgfx : public Module
	{
	private:
		mudgfx();

	public:
		static mudgfx& m() { static mudgfx instance; return instance; }
	};
}

#ifdef MUD_GFX_MODULE
extern "C"
MUD_GFX_EXPORT Module& getModule();
#endif

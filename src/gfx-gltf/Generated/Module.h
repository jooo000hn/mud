
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <gfx/Generated/Module.h>
        
#include <gfx-gltf/Generated/Forward.h>
#include <gfx-gltf/Generated/Types.h>

#include <gfx-gltf/ImporterGltf.h>

namespace mud
{
	export_ class MUD_GFX_GLTF_EXPORT mudgfxgltf : public Module
	{
	private:
		mudgfxgltf();

	public:
		static mudgfxgltf& m() { static mudgfxgltf instance; return instance; }
	};
}

#ifdef MUD_GFXGLTF_MODULE
extern "C"
MUD_GFX_GLTF_EXPORT Module& getModule();
#endif

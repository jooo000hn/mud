#pragma once

#include <00_tutorial/Generated/Forward.h>

#ifndef MUD_MODULES
#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <ui/Generated/Types.h>
#include <uio/Generated/Types.h>
#include <gfx/Generated/Types.h>
#include <edit/Generated/Types.h>
#include <gen/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> _00_TUTORIAL_EXPORT Type& type<ShapeType>();
    
    export_ template <> _00_TUTORIAL_EXPORT Type& type<MyObject>();
}

#pragma once

#include <lang/Generated/Forward.h>

#ifndef MUD_MODULES
#include <obj/Generated/Types.h>

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
    export_ template <> MUD_LANG_EXPORT Type& type<mud::StreamModifier>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ValveKind>();
    
    export_ template <> MUD_LANG_EXPORT Type& type<mud::LuaInterpreter>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Pipe>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Process>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::StreamBranch>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Valve>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessFunction>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessMethod>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessScript>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessCallable>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessCreate>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessDisplay>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessGetMember>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessSetMember>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessValue>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessInput>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessOutput>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Script>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::VisualScript>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Stream>();
}

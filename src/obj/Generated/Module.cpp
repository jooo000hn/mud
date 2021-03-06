#ifdef MUD_CPP_20
#include <cassert>
#include <cstdint>
#include <climits>
#include <cfloat>
import std.core;
import std.memory;
import std.threading;
import std.regex;
#endif

#include <obj/Generated/Module.h>

#ifdef MUD_OBJ_REFLECT
#include <obj/Generated/Convert.h>

#define MUD_OBJ_REFLECTION_IMPL
#include <obj/Generated/Meta.h>
#endif

namespace mud
{
	mudobj::mudobj()
		: Module("mud::obj")
	{
        // ensure dependencies are instantiated

#ifdef MUD_OBJ_REFLECT
        // setup reflection meta data
		obj_meta(*this);
#endif
	}
}

#ifdef MUD_OBJ_MODULE
extern "C"
MUD_OBJ_EXPORT Module& getModule()
{
	return mudobj::m();
}
#endif

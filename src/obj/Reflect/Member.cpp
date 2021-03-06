//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Config.h>
#include <obj/Reflect/Member.h>
#include <obj/Reflect/Meta.h>
#include <obj/System/System.h>
#endif

namespace mud
{
	Static::Static(Type& parent_type, cstring name, Ref value)
		: m_parent_type(&parent_type)
		, m_name(name)
		, m_value(value)
	{}

	Member::Member(Type& object_type, Address address, Type& type, cstring name, Var default_value, Flags flags)
		: m_index(0)
		, m_object_type(&object_type)
		, m_address(address)
		, m_type(&type)
		, m_name(name)
		, m_default_value(default_value)
		, m_flags(flags)
	{
		m_offset = *reinterpret_cast<size_t*>(m_address.value);
	}

	Member::~Member()
	{}
}

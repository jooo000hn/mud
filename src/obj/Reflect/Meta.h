//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Var.h>
#include <obj/Type.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	using cstring = const char*;

	export_ enum class _refl_ TypeClass : unsigned int
	{
		None = 0,
		Object = 1,
		Struct = 2,
		Complex = 3,
		Sequence = 4,
		BaseType = 5,
		Enum = 6
	};

	export_ template<typename T, typename U> constexpr uintptr_t member_offset(U T::*member)
	{
		return (char*)&((T*)nullptr->*member) - (char*)nullptr;
	}

	export_ template<typename T_Object, typename T_Base> uintptr_t base_offset()
	{
		void* mem = malloc(sizeof(T_Object));
		uintptr_t offset = (char*)static_cast<T_Base*>((T_Object*)mem) - (char*)(T_Object*)mem;
		free(mem);
		return offset;
	}

	export_ class _refl_ MUD_OBJ_EXPORT Meta
	{
	public:
		Meta(Type& type, Namespace* location, cstring name, size_t size, TypeClass type_class);

		Type* m_type;
		Namespace* m_namespace = nullptr;
		cstring m_name;
		size_t m_size;
		TypeClass m_type_class;

		std::function<Ref(void)> m_empty_ref;
		std::function<Var(void)> m_empty_var;
		std::function<Var(Ref)> m_copy_construct;
		std::function<void(Ref, Ref)> m_copy_assign;
	};

	export_ inline bool is_none(Type& ty) { return &ty == &type<None>(); }
	export_ inline bool is_base_type(Type& ty) { return ty.m_meta->m_type_class == TypeClass::BaseType; }
	export_ inline bool is_enum(Type& ty) { return ty.m_meta->m_type_class == TypeClass::Enum; }
	export_ inline bool is_basic(Type& ty) { return ty.m_meta->m_type_class == TypeClass::BaseType || ty.m_meta->m_type_class == TypeClass::Enum; }
	export_ inline bool is_struct(Type& ty) { return ty.m_meta->m_type_class == TypeClass::Struct; }
	export_ inline bool is_object(Type& ty) { return ty.m_meta->m_type_class == TypeClass::Object; }
	export_ inline bool is_sequence(Type& ty) { return ty.m_meta->m_type_class == TypeClass::Sequence; }
	export_ inline bool is_class(Type& ty) { return ty.m_meta->m_type_class < TypeClass::BaseType; }
	
	export_ inline Meta& meta(const Ref& ref) { return *ref.type().m_meta; }
	export_ inline Meta& meta(const Var& var) { return *var.m_ref.m_type->m_meta; }

	export_ inline Class& cls(const Ref& ref) { return *ref.type().m_class; }
	export_ inline Class& cls(const Var& var) { return *var.m_ref.m_type->m_class; }

	export_ inline Enum& enu(const Ref& ref) { return *ref.type().m_enum; }
	export_ inline Enum& enu(const Var& var) { return *var.m_ref.m_type->m_enum; }

	export_ void copy_construct(Ref dest, Ref source);

	export_ inline Var construct(Type& type)
	{
		return type.m_meta->m_empty_var();
	}

	export_ void assign(Ref first, Ref second);
	export_ void assign_pointer(Ref first, Ref second);
	export_ bool compare(Ref first, Ref second);

	export_ bool is_related(Type& input, Type& output);

	export_ bool convert(Var& input, Type& output, Var& result, bool ref = false);
	export_ Var convert(Ref input, Type& output);
	export_ void convert(Ref input, Type& output, Var& result);

	export_ bool can_convert(Type& input, Type& output);
	export_ bool can_convert(Ref input, Type& output);
}

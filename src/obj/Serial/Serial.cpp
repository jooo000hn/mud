//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h>
#include <string.h>
import std.core;
import std.memory;
#else
#include <fstream>
#endif

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Config.h>
#include <obj/Types.h>
#include <obj/Serial/Serial.h>
#include <obj/System/System.h>
#include <obj/Reflect/Convert.h>
#include <obj/Reflect/Sequence.h>
#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Injector.h>
#include <obj/Reflect/Member.h>
#include <obj/Reflect/Method.h>
#endif

#include <json11.hpp>

//#define MUD_DEBUG_SERIAL

namespace mud
{
	std::vector<uint8_t> read_binary_file(const string& path)
	{
		std::vector<uint8_t> buffer;
		std::ifstream file = std::ifstream(path, std::ios::binary);
		//buffer.resize(file.gcount());
		buffer.insert(buffer.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
		return buffer;
	}

	string read_text_file(const string& path)
	{
		std::ifstream file = std::ifstream(path);
		std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		return result;
	}

	void parse_json_file(const string& path, json& data)
	{
		if(!std::ifstream(path).good())
		{
			printf("ERROR: couldn't open file %s\n", path.c_str());
			return;
		}

		string text = read_text_file(path);
#ifdef MUD_JSON_NLOHMANN
		data = json::parse(text);
#else
		string errors;
		data = json::parse(text, errors);
#endif
	}

	json parse_json_file(const string& path)
	{
		json data;
		parse_json_file(path, data);
		return data;
	}

#ifndef MUD_CPP_20
	void dump_json_file(const string& path, const json& value)
	{
		std::ofstream file = std::ofstream(path);
		if(!file.good())
			printf("ERROR: couldn't open file %s\n", path.c_str());
		string content = value.dump();
		file << content;
	}
#endif

	void visit_json(json& json_value, const JsonVisitor& visitor)
	{
		visitor(json_value);

		if(json_value.is_object())
			for(auto& key_value : json_value.object_items())
				visit_json(const_cast<json&>(key_value.second), visitor);
		else if(json_value.is_array())
			for(const json& value : json_value.array_items())
				visit_json(const_cast<json&>(value), visitor);
	}

	FromJson::FromJson()
	{
		dispatch_branch<int>(*this, [](int& value, Ref&, const json& json_value) { value = json_value.int_value(); });
		dispatch_branch<float>(*this, [](float& value, Ref&, const json& json_value) { value = float(json_value.number_value()); });
		// cstring can't be deserialized I believe, or we need to memoize them ?
		dispatch_branch<string>(*this, [](string& value, Ref&, const json& json_value) { value = json_value.string_value(); });
		dispatch_branch<strung>(*this, [](strung& value, Ref&, const json& json_value) { value = json_value.string_value().c_str(); });
		dispatch_branch<Id>(*this, [](Id& value, Ref&, const json& json_value) { value = Id(json_value.int_value()); });
		dispatch_branch<bool>(*this, [](bool& value, Ref&, const json& json_value) { value = json_value.bool_value(); });

		dispatch_branch<std::vector<Var>>(*this, [](std::vector<Var>& values, Ref&, const json& json_value)
		{
			for(const json& value : json_value.array_items())
				values.push_back(unpack_typed(value));
		});

		dispatch_branch<Call>(*this, [](Call& call, Ref&, const json& json_value)
		{
			call.m_callable = System::instance().find_function(json_value["callable"].string_value().c_str());
			call.m_arguments = unpackt<std::vector<Var>>(json_value["arguments"]);
		});
	}

	ToJson::ToJson()
	{
		dispatch_branch<int>(*this, [](int& value, json& json_value) { json_value = json(value); });
		dispatch_branch<float>(*this, [](float& value, json& json_value) { json_value = value; });
		dispatch_branch<cstring>(*this, [](cstring value, json& json_value) { json_value = string(value); });
		dispatch_branch<string>(*this, [](string& value, json& json_value) { json_value = value; });
		dispatch_branch<strung>(*this, [](strung& value, json& json_value) { json_value = string(value); });
		dispatch_branch<Id>(*this, [](Id& value, json& json_value) { json_value = json(int(value)); });
		dispatch_branch<bool>(*this, [](bool& value, json& json_value) { json_value = value; });

		dispatch_branch<Type>(*this, [](Type& type, json& json_value) { json_value = type.m_name; });

		dispatch_branch<std::vector<Var>>(*this, [](std::vector<Var>& values, json& json_value)
		{
			std::vector<json> json_values = std::vector<json>(values.size());
			for (size_t i = 0; i < values.size(); ++i)
				pack_typed(values[i], json_values[i]);
			json_value = json_values;
		});

		dispatch_branch<Call>(*this, [](Call& call, json& json_value)
		{
			std::map<std::string, json> json_values;
			json_values["callable"] = string(call.m_callable->m_name);
			pack(Ref(&call.m_arguments), json_values["arguments"]);
			json_value = json_values;
		});
	}

	inline void enum_set_value(Ref value, size_t enum_value)
	{
		memcpy(value.m_value, &enum_value, meta(value).m_size);
	}

	inline void enum_manual_value(Ref result, size_t value)
	{
		enum_set_value(result, value);
	}

	Var unpack(Type& type, const json& json_value)
	{
		static FromJson unpacker;
		return unpack(unpacker, type, json_value);
	}

	void unpack(Var& value, const json& json_value)
	{
		static FromJson unpacker;
		unpack(unpacker, value, json_value);
	}

	void unpack(Ref object, const json& json_value)
	{
		static FromJson unpacker;
		Var value = object;
		unpack(unpacker, value, json_value);
	}
	
	Var unpack(FromJson& unpacker, Type& type, const json& json_value, bool typed)
	{
		Var result = type.m_meta->m_empty_var();
		unpack(unpacker, result, json_value, typed);
		return result;
	}

	void unpack(FromJson& unpacker, Var& value, const json& json_value, bool typed)
	{
		if(json_value.is_null())
			return;

		// @note: we MUST take a Var& as parameter of this function for this specific case
		// -> polymorphic objects must be created by value since we don't know in advance the actual type we are loading
		if(value.type().m_class && cls(value).m_type_member && !typed) // @kludge this parameter is only there to tell us we were called from the typed variant of this function, couldn't think of a better design at this time of the day
		{
			value = unpack_typed(unpacker, json_value);
			return;
		}

		if(unpacker.check(value))
		{
			unpacker.dispatch(value, value.m_ref, json_value);
			return;
		}
		else if(is_enum(value.type()) && json_value.is_number()) // is_number_integer
		{
			enum_manual_value(value, json_value.int_value());
			return;
		}
		else if(value.type().m_convert && json_value.is_string())
		{
			value.type().m_convert->m_from_string(json_value.string_value(), value);
			return;
		}
		else if(is_sequence(value.type()))
		{
			for(const json& json_element : json_value.array_items())
			{
				Var element = unpack(unpacker, *cls(value).m_content, json_element);
				add_sequence(value, element);
			}
			return;
		}

		size_t size = json_value.is_array() ? json_value.array_items().size() : json_value.object_items().size();

		const Class& cls = mud::cls(value);
		const Constructor* constructor = cls.constructor(size);

		if(!constructor)
		{
			auto unpack_member = [&](const Member& member, const json& member_value)
			{
#ifdef MUD_DEBUG_SERIAL
				printf("DEBUG: unpacking member %s :: %s\n", value.type().m_name, member.m_name);
#endif
				member.set(value, unpack(unpacker, *member.m_type, member_value));
			};

			if(json_value.is_object())
				for(const Member& member : cls.m_members)
					if(!json_value[member.m_name].is_null())
					{
						unpack_member(member, json_value[member.m_name]);
					}

			if(json_value.is_array())
				for(size_t index = 0; index < size; ++index)
				{
					unpack_member(cls.m_members[index], json_value[index]);
				}
		}
		else
		{
			Call construct = { *constructor };

			for(size_t index = 0; index < size; ++index)
			{
#ifdef MUD_DEBUG_SERIAL
				printf("DEBUG: unpacking member %s :: %s\n", value.type().m_name, construct.m_callable->m_params[index + 1].m_name);
#endif
				const json& json_field = json_value.is_array() ? json_value[index]
															   : json_value[construct.m_callable->m_params[index + 1].m_name];

				unpack(unpacker, construct.m_arguments[index + 1], json_field);
			}

			construct(value);
		}
	}

	Var unpack_typed(FromJson& unpacker, const json& json_typed_value)
	{
		string type_name = json_typed_value["type"].string_value();
		json json_value = json_typed_value["value"];
		return unpack(unpacker, *System::instance().find_type(type_name.c_str()), json_value, true);
	}

	Var unpack_typed(const json& json_value)
	{
		static FromJson unpacker;
		return unpack_typed(unpacker, json_value);
	}

	void pack(ToJson& packer, const Var& value, json& json_value, bool typed)
	{
		if(packer.check(value.m_ref))
		{
			packer.dispatch(value.m_ref, json_value);
		}
		else if(is_basic(value.type()))
		{
			json_value = to_string(value);
		}
		else if(is_sequence(value.type()))
		{
			size_t i = 0;
			std::vector<json> json_values = std::vector<json>(sequence_size(value.m_ref));
			iterate_sequence(value.m_ref, [&](Ref element) {
				pack(element, json_values[i++]);
			});
			json_value = json_values;
		}
		else if(is_object(value.type()))
		{
			if(value.null())
				json_value = nullptr;
			else if(cls(value).m_type_member && !typed)
				pack_typed(value, json_value);
			else
			{
				for(Member& member : cls(value).m_members)
					if(&member != cls(value).m_type_member)
					{
						Var member_val = member.get(value.m_ref);
						json member_json = json_value[member.m_name];
						pack(packer, member_val, member_json);
					}
			}
		}
	}

	void pack(const Var& value, json& json_value)
	{
		static ToJson packer;
		pack(packer, value, json_value);
	}

	json pack(const Var& value)
	{
		json json_value;
		pack(value, json_value);
		return json_value;
	}

	void pack_typed(ToJson& packer, const Var& value, json& json_value)
	{
		std::map<std::string, json> json_values;
		json_values["type"] = value.type().m_name;
		pack(packer, value, json_values["value"], true);
		json_value = json_values;
	}

	void pack_typed(const Var& value, json& json_value)
	{
		static ToJson packer;
		pack_typed(packer, value, json_value);
	}

	string pack_json(const Var& value)
	{
		json json_value;
		pack(value, json_value);
		return json_value.dump();
	}
}

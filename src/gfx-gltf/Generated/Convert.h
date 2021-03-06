
#pragma once

#include <gfx-gltf/Generated/Types.h>

#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Enum.h>
#include <obj/String/StringConvert.h>

namespace mud
{
    template <> inline void from_string(const string& str, glTFAlphaMode& val) { val = static_cast<glTFAlphaMode>(enu<glTFAlphaMode>().value(str.c_str())); };
    template <> inline void to_string(const glTFAlphaMode& val, string& str) { str = enu<glTFAlphaMode>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, glTFComponentType& val) { val = static_cast<glTFComponentType>(enu<glTFComponentType>().value(str.c_str())); };
    template <> inline void to_string(const glTFComponentType& val, string& str) { str = enu<glTFComponentType>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, glTFInterpolation& val) { val = static_cast<glTFInterpolation>(enu<glTFInterpolation>().value(str.c_str())); };
    template <> inline void to_string(const glTFInterpolation& val, string& str) { str = enu<glTFInterpolation>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, glTFPrimitiveType& val) { val = static_cast<glTFPrimitiveType>(enu<glTFPrimitiveType>().value(str.c_str())); };
    template <> inline void to_string(const glTFPrimitiveType& val, string& str) { str = enu<glTFPrimitiveType>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, glTFType& val) { val = static_cast<glTFType>(enu<glTFType>().value(str.c_str())); };
    template <> inline void to_string(const glTFType& val, string& str) { str = enu<glTFType>().m_map[size_t(val)]; };
    
    
}

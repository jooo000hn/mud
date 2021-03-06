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

#include <${ module.subdir }/Generated/Module.h>

#ifdef ${ module.preproc_name }_REFLECT
#include <${ module.subdir }/Generated/Convert.h>

#define ${ module.preproc_name }_REFLECTION_IMPL
#include <${ module.subdir }/Generated/Meta.h>
#endif

% if module.namespace != '' :
namespace ${ module.namespace }
{
% endif
	${ module.namespace }${ module.name }::${ module.namespace }${ module.name }()
		: Module("${ module.namespace + '::' if module.namespace != '' else '' }${ module.name }")
	{
        // ensure dependencies are instantiated
% for m in module.dependencies :
        ${ m.namespace }${ m.name }::m();
% endfor

#ifdef ${ module.preproc_name }_REFLECT
        // setup reflection meta data
		${ module.name }_meta(*this);
#endif
	}
% if module.namespace != '' :
}
% endif

#ifdef ${ module.namespace.upper() }_${ module.name.upper() }_MODULE
extern "C"
${ module.export } Module& getModule()
{
	return ${ module.namespace }${ module.name }::m();
}
#endif

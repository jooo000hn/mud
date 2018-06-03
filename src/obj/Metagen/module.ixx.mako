#include <assert.h>
#include <stdint.h>
#include <float.h>

export module ${ module.namespace }.${ module.name };
export import std.core;
export import std.memory;
export import std.threading;

% for header in module.headers :
#include <${ module.subdir }/${ header }>
% endfor

#include <assert.h>
#include <stdint.h>
#include <float.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>
#include <sstream>

export module ${ module.namespace }.${ module.name };

% for header in module.headers :
#include <${ module.subdir }/${ header }>
% endfor

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
module mud.gfx;
#else
#include <obj/Indexer.h>
#include <geom/Geom.h>
#include <gfx/Generated/Types.h>
#include <gfx/Model.h>
#include <gfx/Mesh.h>
#include <gfx/Skeleton.h>
#endif

namespace mud
{
	//static uint16_t s_model_index = 0;

	Model::Model(cstring id)
		: m_name(id)
		, m_index(index(type<Model>(), this))//++s_model_index)
	{}

	Model::~Model()
	{}

	Mesh& Model::add_mesh(cstring name, bool readback)
	{
		m_meshes.emplace_back(name, readback);
		return m_meshes.back();
	}

	void Model::prepare()
	{
		m_aabb = { Zero3, Zero3 };
		m_radius = 0.f;

		for(ModelItem& item: m_items) //Mesh& mesh : m_meshes)
		{
			m_geometry[item.m_mesh->m_draw_mode] = true;
			m_aabb.merge(transform_aabb(item.m_mesh->m_aabb, item.m_transform));
			//m_radius = max(item.m_mesh->m_radius, m_radius);
		}

		m_radius = sqrt(2.f) * max(m_aabb.m_extents.x, max(m_aabb.m_extents.y, m_aabb.m_extents.z));

		m_origin = m_aabb.m_center;
	}
}

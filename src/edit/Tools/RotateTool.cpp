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
module mud.edit;
#else
#include <math/Axes.h>
#include <geom/Shapes.h>
#include <geom/Intersect.h>
#include <gfx/Gfx.h>
#include <gfx/Item.h>
#include <edit/Generated/Types.h>
#include <edit/Tools/RotateTool.h>
#include <edit/Viewer/Viewer.h>
#endif

namespace mud
{
	RotateAction::RotateAction(const std::vector<Transform*>& targets, const vec3& axis)
		: TransformAction(targets)
		, m_axis(axis)
		, m_angle(0.f)
	{}

	void RotateAction::apply(Transform& transform)
	{
		transform.m_rotation = transform.m_rotation * angle_axis(m_angle, m_axis);
	}

	void RotateAction::undo(Transform& transform)
	{
		transform.m_rotation = transform.m_rotation * angle_axis(-m_angle, m_axis);
	}

	void RotateAction::update(const vec3& start, const vec3& end)
	{
		// @kludge : why negative axis ?
		m_angle = oriented_angle(normalize(start), normalize(end), m_axis); 
	}

	RotateTool::RotateTool(ToolContext& context)
		: TransformTool(context, "Rotate", type<RotateTool>())
	{
		m_gizmos.push_back(rotation_gizmo(Axis::X, 0.f));
		m_gizmos.push_back(rotation_gizmo(Axis::Y, 1.f / 3.f));
		m_gizmos.push_back(rotation_gizmo(Axis::Z, 2.f / 3.f));
		m_current = &m_gizmos.front();
	}

	Item& rotate_gizmo(Gnode& parent, Axis axis, Colour colour, float ring_radius, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, Zero3, ZeroQuat);
		return gfx::shape(node, Torus(1.f, ring_radius, axis), Symbol(Colour::None, colour, true, true), flags);
	}

	Gizmo RotateTool::rotation_gizmo(Axis axis, float hue)
	{
		auto grab_point = [this, axis](Viewer& viewer, const vec2& pos) { UNUSED(pos); return gizmo_grab_planar(viewer, m_transform, axis) - m_transform.m_position; };

		auto draw_handle = [=](Gnode& parent) { return &rotate_gizmo(parent, axis, Colour::Invisible, 0.05f, ITEM_UI); };
		auto draw_gizmo = [=](Gnode& parent, bool active) { rotate_gizmo(parent, axis, gizmo_colour(hue, active), 0.01f); };

		return { draw_handle, draw_gizmo, nullptr, false, grab_point };
	}

	object_ptr<TransformAction> RotateTool::create_action(const std::vector<Transform*>& targets)
	{
		vec3 axis = m_current == &m_gizmos[0] ? -X3
				  : m_current == &m_gizmos[1] ?  Y3
											  : -Z3;
		return make_object<RotateAction>(targets, axis);
	}

}


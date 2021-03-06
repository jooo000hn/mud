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
module mud.ui;
#else
#include <obj/Vector.h>
#include <ui/Sequence.h>
#include <ui/Structs/Widget.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Structs/Container.h>
#include <ui/ScrollSheet.h>
#endif

namespace mud
{
namespace ui
{
	Sequence& sequence(Widget& parent)
	{
		Sequence& self = twidget<Sequence>(parent, styles().sequence);
		self.m_body = scroll_sheet(self).m_body;
		return self;
	}

	bool select_logic(Widget& element, Ref object, std::vector<Ref>& selection)
	{
		bool changed = false;
		if(MouseEvent mouse_event = element.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputModifier::Shift))
		{
			vector_swap(selection, object);
			changed = true;
		}
		if(MouseEvent mouse_event = element.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			vector_select(selection, object);
			changed = true;
		}
		if(MouseEvent mouse_event = element.mouse_event(DeviceType::MouseRight, EventType::Stroked))
		{
			vector_select(selection, object);
			changed = true;
		}

		element.setState(SELECTED, vector_has(selection, object));
		return changed;
	}

	bool select_logic(Widget& element, Ref object, Ref& selection)
	{
		bool changed = false;
		if(MouseEvent mouse_event = element.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			selection = object;
			changed = true;
		}

		element.setState(SELECTED, object == selection);
		return changed;
	}

	Widget& element(Widget& parent, Ref object)
	{
		Widget& self = widget(parent, styles().element, object.m_value);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			parent.root_sheet().m_drop = { static_cast<Widget*>(mouse_event.m_target), object, DropState::Preview };

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
			parent.root_sheet().m_drop = { static_cast<Widget*>(mouse_event.m_target), object, DropState::Done };

		return self;
	}

	Widget& element(Widget& parent, Ref object, std::vector<Ref>& selection)
	{
		Widget& self = element(parent, object);
		select_logic(self, object, selection);
		return self;
	}

	Widget& element(Sequence& sequence, Ref object)
	{
		return element(*sequence.m_body, object, *sequence.m_selection);
	}
}
}

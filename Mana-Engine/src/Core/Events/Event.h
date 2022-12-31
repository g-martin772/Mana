#pragma once

#include "Core/Core.h"

#include <functional>

namespace Mana {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowFocusLost, WindowMoved, FileDropped, WindowMinimized, WindowRestored, WindowMaximized,
		KeyPressed, KeyReleased,
		ButtonPressed, ButtonReleased, MouseMoved, MouseScrolled, MouseEntered, MouseLeft
	};

	#define EventClassType(type)\
		static constexpr EventType GetStaticType() { return EventType::##type; }\
		virtual EventType GetEventType() const { return GetStaticType(); }\
		virtual const char* GetName() const override { return #type; }

	class MANA_API Event {
		friend class EventDispather;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	protected:
		bool m_Handled = false;
	};

	class MANA_API EventDispather {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispather(Event& event) : m_Event(event) { }

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream & os, const Event& e) {
		return os << e.ToString();
	}
}

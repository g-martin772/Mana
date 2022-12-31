#pragma once

#include "Event.h"

#include <sstream>

namespace Mana {
	class MANA_API KeyPressedEvent : public Event {
	public: EventClassType(KeyPressed)
		KeyPressedEvent(int keycode, bool repeat) : m_KeyCode(keycode), m_Repeat(repeat) {}

		int GetKeyCode() const { return m_KeyCode; }
		bool IsRepeat() const { return m_KeyCode; }
		
		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << m_KeyCode;
			ss << (m_Repeat ? " - repeat" : "");
			return ss.str();
		}

	private:
		int m_KeyCode;
		bool m_Repeat;
	};

	class MANA_API KeyReleasedEvent : public Event {
	public: EventClassType(KeyReleased)
		KeyReleasedEvent(int keycode) : m_KeyCode(keycode) {}

		int GetKeyCode() const { return m_KeyCode; }

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << m_KeyCode;
			return ss.str();
		}

	private:
		int m_KeyCode;
	};
}

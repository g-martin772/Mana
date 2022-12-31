#pragma once

#include "Event.h"
#include <sstream>

namespace Mana {
	class MANA_API MouseButtonPressedEvent : public Event {
	public: EventClassType(ButtonPressed)
		MouseButtonPressedEvent(int keycode) : m_KeyCode(keycode) {}

		  int GetKeyCode() const { return m_KeyCode; }
		  bool IsRepeat() const { return m_KeyCode; }

		  virtual std::string ToString() const override {
			  std::stringstream ss;
			  ss << GetName() << ": " << m_KeyCode;
			  return ss.str();
		  }

	private:
		int m_KeyCode;
	};

	class MANA_API MouseButtonReleasedEvent : public Event {
	public: EventClassType(ButtonReleased)
		MouseButtonReleasedEvent(int keycode) : m_KeyCode(keycode) {}

		  int GetKeyCode() const { return m_KeyCode; }

		  virtual std::string ToString() const override {
			  std::stringstream ss;
			  ss << GetName() << ": " << m_KeyCode;
			  return ss.str();
		  }

	private:
		int m_KeyCode;
	};

	class MANA_API MouseMovedEvent : public Event {
	public: EventClassType(MouseMoved)
		MouseMovedEvent(float x, float y) : m_X(x), m_Y(y) {}

		  float GetPosX() const { return m_X; }
		  float GetPosY() const { return m_Y; }
		  std::pair<float, float> GetPosition() const { return { m_X, m_Y }; }

		  virtual std::string ToString() const override {
			  std::stringstream ss;
			  ss << GetName() << ": x=" << m_X << " y=" << m_Y;
			  return ss.str();
		  }

	private:
		float m_X, m_Y;
	};

	class MANA_API MouseScrolledEvent : public Event {
	public: EventClassType(MouseScrolled)
		MouseScrolledEvent(float x, float y) : m_X(x), m_Y(y) {}

		  float GetOffsetX() const { return m_X; }
		  float GetOffsetY() const { return m_Y; }
		  std::pair<float, float> GetOffset() const { return { m_X, m_Y }; }

		  virtual std::string ToString() const override {
			  std::stringstream ss;
			  ss << GetName() << ": x=" << m_X << " y=" << m_Y;
			  return ss.str();
		  }

	private:
		float m_X, m_Y;
	};

	class MANA_API MouseEnteredEvent : public Event {
	public: EventClassType(MouseEntered)
		MouseEnteredEvent() {}
	};

	class MANA_API MouseLeftEvent : public Event {
	public: EventClassType(MouseLeft)
		MouseLeftEvent() {}
	};
}
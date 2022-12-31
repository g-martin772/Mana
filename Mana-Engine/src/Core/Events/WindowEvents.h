#pragma once

#include "Event.h"
#include <sstream>

namespace Mana {
	class MANA_API WindowCloseEvent : public Event {
	public: EventClassType(WindowClose)
		WindowCloseEvent() {}
	};

	class MANA_API WindowMinimizedEvent : public Event {
	public: EventClassType(WindowMinimized)
		WindowMinimizedEvent() {}
	};

	class MANA_API WindowRestoredEvent : public Event {
	public: EventClassType(WindowRestored)
		WindowRestoredEvent() {}
	};

	class MANA_API WindowMaximizedEvent : public Event {
	public: EventClassType(WindowMaximized)
		WindowMaximizedEvent() {}
	};

	class MANA_API WindowFocusdEvent : public Event {
	public: EventClassType(WindowFocus)
		WindowFocusdEvent() {}
	};

	class MANA_API WindowFocusLostEvent : public Event {
	public: EventClassType(WindowFocusLost)
		WindowFocusLostEvent() {}
	};


	class MANA_API WindowResizeEvent : public Event {
	public: EventClassType(WindowResize)
		WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}

		  int GetWidht() const { return m_Width; }
		  int GetHeight() const { return m_Height; }
		  std::pair<int, int> GetWindowSize() const { return { m_Width, m_Height }; }

		  virtual std::string ToString() const override {
			  std::stringstream ss;
			  ss << GetName() << ": width=" << m_Width << " height=" << m_Height;
			  return ss.str();
		  }

	private:
		int m_Width, m_Height;
	};

	class MANA_API WindowMovedEvent : public Event {
	public: EventClassType(WindowMoved)
		WindowMovedEvent(int x, int y) : m_X(x), m_Y(y) {}

		  int GetPosX() const { return m_X; }
		  int GetPosY() const { return m_Y; }
		  std::pair<int, int> GetPosition() const { return { m_X, m_Y }; }

		  virtual std::string ToString() const override {
			  std::stringstream ss;
			  ss << GetName() << ": x=" << m_X << " y=" << m_Y;
			  return ss.str();
		  }

	private:
		int m_X, m_Y;
	};

	class MANA_API FileDroppedEvent : public Event {
	public: EventClassType(FileDropped)
		FileDroppedEvent(std::vector<const char*> paths) : m_Paths(paths) {}

		  std::vector<const char*> GetPaths() const { return m_Paths; }

		  virtual std::string ToString() const override {
			  std::stringstream ss;
			  for (const char* s : m_Paths)
				  ss << s << ";";
			  return ss.str();
		  }

	private:
		std::vector<const char*> m_Paths;
	};
}

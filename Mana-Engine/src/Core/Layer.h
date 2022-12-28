#pragma once

#include "Core/Core.h"

#include <vector>

namespace Mana {
	class MANA_API Layer {
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent() = 0;
	};

	class MANA_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void AddLayer(Layer* layer);
		void AddGUI(Layer* gui);
		void PopLayer();
		void PopGUI();

		void OnUpdate();
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*> m_GUI;
	};
}

#include "manapch.h"
#include "Layer.h"

namespace Mana {
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		if (m_Layers.size() > 0)
			for (auto& layer : m_Layers) {
				layer->OnDetach();
				delete layer;
			}
		if (m_GUI.size() > 0)
			for (auto iterator = m_GUI.end(); iterator-- != m_GUI.begin(); ) {
				(*iterator)->OnDetach();
				delete *iterator;
			}
	}

	void LayerStack::AddLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		layer->OnAttach();
	}

	void LayerStack::AddGUI(Layer* gui)
	{
		m_GUI.push_back(gui);
		gui->OnAttach();
	}

	void LayerStack::PopLayer()
	{
		m_Layers.front()->OnDetach();
		m_Layers.pop_back();
	}

	void LayerStack::PopGUI()
	{
		m_GUI.front()->OnDetach();
		m_GUI.pop_back();
	}

	void LayerStack::OnUpdate()
	{
		if (m_Layers.size() > 0)
			for (auto& layer : m_Layers) {
				layer->OnUpdate();
			}
		if(m_GUI.size() > 0)
			for (auto iterator = m_GUI.end(); iterator-- != m_GUI.begin(); ) {
				(*iterator)->OnUpdate();
			}
	}
}

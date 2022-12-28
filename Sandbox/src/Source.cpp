#include "Mana.h"

class AppLayer : public Mana::Layer {
	void OnAttach() override {
		MANA_TRACE("Attached");
		m_Scene = std::make_shared<Mana::Scene>();
	}
	void OnDetach() override {
		MANA_TRACE("Detached");
	}
	void OnUpdate() override {
		MANA_TRACE("Updated");
		m_Scene->OnUpdate();
	}
	void OnEvent() override {
		MANA_TRACE("Event");
	}
private:
	Mana::Ref<Mana::Scene>m_Scene;
};

class Sandbox : public Mana::ManaApplication {
public:
	Sandbox() {
		m_LayerStack->AddLayer(new AppLayer());
	}

	~Sandbox() {

	}
};

Mana::ManaApplication* Mana::CreateApplication(char** argv, int argc) {
	return new Sandbox();
}
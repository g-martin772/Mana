#include "Mana.h"

class AppLayer : public Mana::Layer {
	void OnAttach() override {
		m_Scene = std::make_shared<Mana::Scene>();
	}
	void OnDetach() override {
	}
	void OnUpdate() override {
		m_Scene->OnUpdate();
		Mana::RenderCommand::SetClearColor({ 0.0f, 1.0f, 1.0f, 1.0f });
		Mana::RenderCommand::Clear();
	}
	void OnEvent() override {
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
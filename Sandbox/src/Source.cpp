#include "Mana.h"

class AppLayer : public Mana::Layer {
	void OnAttach() override {
		

		/*m_Scene = std::make_shared<Mana::Scene>();
		
		Mana::Entity e = m_Scene->CreateEntity();
		e.AddComponent<Mana::SpriteRendererComponent>(Mana::vec4{ 1.0f, 1.0f, 0.0f, 1.0f });
		auto& tc = e.GetComponent<Mana::TransformComponent>();
		tc.Scale = Mana::vec3{1.0f, 1.0f, 1.0f};
		tc.Position = Mana::vec3{ 10.0f, 10.0f, 10.0f };*/
	}
	void OnDetach() override {
	}
	void OnUpdate() override {
		//m_Scene->OnUpdate();
		//Mana::RenderCommand::SetClearColor({ 0.0f, 1.0f, 1.0f, 1.0f });
		//Mana::RenderCommand::Clear();
	}
	bool OnEvent(Mana::Event& e) override {
		//MANA_TRACE(e);

		return true;
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
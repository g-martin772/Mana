#include "Mana.h"

class Sandbox : public Mana::ManaApplication {
public:
	Sandbox() {
		MANA_TRACE("Some Client Text");
	}

	~Sandbox() {

	}
};

Mana::ManaApplication* Mana::CreateApplication(char** argv, int argc) {
	return new Sandbox();
}
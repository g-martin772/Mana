#include "Mana.h"

#include <iostream>

class Sandbox : public Mana::ManaApplication {
public:
	Sandbox() {
		std::cout << "Hello from the sandbox" << std::endl;
	}

	~Sandbox() {

	}
};

Mana::ManaApplication* Mana::CreateApplication(char** argv, int argc) {
	return new Sandbox();
}
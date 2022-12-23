#pragma once

#include "Application.h"

extern Mana::ManaApplication* Mana::CreateApplication(char** argv, int argc);

int main(char** argv, int argc) {
	auto app = Mana::CreateApplication(argv, argc);
	app->Run();
	delete app;
}

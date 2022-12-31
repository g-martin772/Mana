#pragma once

#include "Application.h"
#include "Log.h"

extern Mana::ManaApplication* Mana::CreateApplication(char** argv, int argc);

int main(char** argv, int argc) {
	Mana::Log::Init();
	auto app = Mana::CreateApplication(argv, argc);
	app->Run();
	delete app;
}

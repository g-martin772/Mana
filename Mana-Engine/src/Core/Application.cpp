#include "manapch.h"
#include "Application.h"

#include <iostream>

namespace Mana {
	ManaApplication::ManaApplication()
	{
	}

	ManaApplication::~ManaApplication()
	{
	}

	void ManaApplication::Run()
	{
		std::cout << "Hello from the engine" << std::endl;
	}
}
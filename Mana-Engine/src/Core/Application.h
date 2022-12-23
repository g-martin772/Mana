#pragma once

#include "Core/Core.h"

namespace Mana {
	class MANA_API ManaApplication {
	public:
		ManaApplication();
		~ManaApplication();
		void Run();
	private:
	};

	ManaApplication* CreateApplication(char** argv, int argc);
}

#pragma once

#include <memory>

#ifdef MANA_PLATFORM_WINDOWS
	#if MANA_DLL_EXPORT
		#define MANA_API __declspec(dllexport)
	#elif MANA_DLL_IMPORT
		#define MANA_API __declspec(dllimport)
	#else
		#define MANA_API
	#endif
#else
	#error Mana only supports windows right now
#endif

namespace Mana {
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}
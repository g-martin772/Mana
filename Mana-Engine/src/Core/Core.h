#pragma once

#include <memory>
#include <ostream>

#ifdef MANA_PLATFORM_WINDOWS
	#if MANA_DLL_EXPORT
		#define MANA_API __declspec(dllexport)
	#elif MANA_DLL_IMPORT
		#define MANA_API __declspec(dllimport)
	#else
		#define MANA_API
	#endif
#else
	static_assert Mana only supports windows right now
#endif

namespace glm {}

namespace Mana {
	using namespace glm;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}

#define MANA_ASSERT(expression, message) \
    if (!(expression)) { \
        std::cerr << "Assertion failed: " << message << std::endl; \
        __debugbreak(); \
    }

#define MANA_CORE_ASSERT(expression, message) \
    if (!(expression)) { \
        std::cerr << "Assertion failed: " << message << std::endl; \
        __debugbreak(); \
    }

#ifdef MANA_DEBUG
	const constexpr bool enableValidationLayers = true;
#else
	const constexpr bool enableValidationLayers = false;
#endif

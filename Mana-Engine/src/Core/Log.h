#pragma once

#include "Core/Core.h"

#include "spdlog/spdlog.h"

namespace Mana {
	class MANA_API Log {
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

#define MANA_CORE_TRACE(...)   ::Mana::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MANA_CORE_INFO(...)	   ::Mana::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MANA_CORE_WARN(...)    ::Mana::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MANA_CORE_ERROR(...)   ::Mana::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MANA_CORE_FATAL(...)   ::Mana::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define MANA_TRACE(...)	       ::Mana::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MANA_INFO(...)	       ::Mana::Log::GetClientLogger()->info(__VA_ARGS__)
#define MANA_WARN(...)         ::Mana::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MANA_ERROR(...)        ::Mana::Log::GetClientLogger()->error(__VA_ARGS__)
#define MANA_FATAL(...)        ::Mana::Log::GetClientLogger()->fatal(__VA_ARGS__)
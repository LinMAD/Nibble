#pragma once

#include <spdlog/spdlog.h>
#include "Core/MacroCore.h"

namespace Nibble {
	class NIBBLE_API Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		Logger();
		~Logger();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}

		static void Init();
	};
}

#define LOGGER_CORE_ERROR(...)::Nibble::Logger::GetCoreLogger()->error(__VA_ARGS__);
#define LOGGER_CORE_WARNING(...)::Nibble::Logger::GetCoreLogger()->warn(__VA_ARGS__);
#define LOGGER_CORE_INFO(...)::Nibble::Logger::GetCoreLogger()->info(__VA_ARGS__);
#define LOGGER_CORE_DEBUG(...)::Nibble::Logger::GetCoreLogger()->debug(__VA_ARGS__);
#define LOGGER_CORE_TRACE(...)::Nibble::Logger::GetCoreLogger()->trace(__VA_ARGS__);

#define LOGGER_APP_ERROR(...)::Nibble::Logger::GetClientLogger()->error(__VA_ARGS__);
#define LOGGER_APP_WARNING(...)::Nibble::Logger::GetClientLogger()->warn(__VA_ARGS__);
#define LOGGER_APP_INFO(...)::Nibble::Logger::GetClientLogger()->info(__VA_ARGS__);
#define LOGGER_APP_DEBUG(...)::Nibble::Logger::GetClientLogger()->debug(__VA_ARGS__);
#define LOGGER_APP_TRACE(...)::Nibble::Logger::GetClientLogger()->trace(__VA_ARGS__);

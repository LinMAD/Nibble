#pragma once

#include <spdlog/spdlog.h>
#include "Core/MacroCore.h"

namespace Nibble {
	class NIBBLE_EXPORT_API Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		Logger();
		~Logger();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger()
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

// For engine usages
#define M_LOGGER_ENG_ERROR(...)::Nibble::Logger::GetEngineLogger()->error(__VA_ARGS__);
#define M_LOGGER_ENG_WARNING(...)::Nibble::Logger::GetEngineLogger()->warn(__VA_ARGS__);
#define M_LOGGER_ENG_INFO(...)::Nibble::Logger::GetEngineLogger()->info(__VA_ARGS__);
#define M_LOGGER_ENG_DEBUG(...)::Nibble::Logger::GetEngineLogger()->debug(__VA_ARGS__);
#define M_LOGGER_ENG_TRACE(...)::Nibble::Logger::GetEngineLogger()->trace(__VA_ARGS__);

// For external application usages
#define LOGGER_CLIENT_ERROR(...)::Nibble::Logger::GetClientLogger()->error(__VA_ARGS__);
#define LOGGER_CLIENT_WARNING(...)::Nibble::Logger::GetClientLogger()->warn(__VA_ARGS__);
#define LOGGER_CLIENT_INFO(...)::Nibble::Logger::GetClientLogger()->info(__VA_ARGS__);
#define LOGGER_CLIENT_DEBUG(...)::Nibble::Logger::GetClientLogger()->debug(__VA_ARGS__);
#define LOGGER_CLIENT_TRACE(...)::Nibble::Logger::GetClientLogger()->trace(__VA_ARGS__);

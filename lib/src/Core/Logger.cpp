#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Nibble {
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

	void Logger::Init()
	{
		// https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		// %^ - Start color range (can be used only once)
		// %$ - End color range (for example %^[+++]%$ %v) (can be used only once)
		// %T - ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S
		// %l - The log level of the message
		// %v - The actual text to log ("debug", "info", etc)
		spdlog::set_pattern("%^|%T| %l:%n -> %v");

		s_CoreLogger = spdlog::stdout_color_mt("Nibble");
		s_ClientLogger = spdlog::stdout_color_mt("Application");

		// TODO Add log level config loading
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}

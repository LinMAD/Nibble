#pragma once

#ifdef NIBBLE_PLATFORM_WINDOWS

extern Nibble::Engine* Nibble::InitilizeEngine();

// Main function where all components (singletons) must be initialized
int main(int argc, char** argv)
{
	Nibble::Logger::Init();
	LOGGER_CORE_DEBUG("Logger initialized...");

	auto app = Nibble::InitilizeEngine();

	app->Run();

	delete app;
}

#endif // NIBBLE_PLATFORM_WINDOWS

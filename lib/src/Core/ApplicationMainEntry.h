#pragma once

#ifdef NIBBLE_PLATFORM_WINDOWS

extern Nibble::Application* Nibble::CreateApplicaiton();

// Main function where all components (singletons) must be initialized
int main(int argc, char** argv)
{
	Nibble::Logger::Init();
	LOGGER_CORE_DEBUG("Logger initialized...");

	auto app = Nibble::CreateApplicaiton();

	app->Run();

	delete app;
}

#endif // NIBBLE_PLATFORM_WINDOWS

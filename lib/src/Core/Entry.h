#pragma once

#ifdef NIBBLE_PLATFORM_WINDOWS

extern Nibble::Application* Nibble::CreateApplicaiton();

int main(int argc, char** argv)
{
	auto app = Nibble::CreateApplicaiton();

	app->Run();

	delete app;
}

#endif // NIBBLE_PLATFORM_WINDOWS

#include "Application.h"
#include "Traceability/Logger.h"

Nibble::Application::Application()
{
}

Nibble::Application::~Application()
{
}

void Nibble::Application::Run()
{
	LOGGER_APP_DEBUG("Main loop log test");

	while (true)
	{
	}
}
#include "Application.h"
#include "Traceability/Logger.h"
#include "Events/EventBus.h"
#include "Events/Window/WindowEvent.h"

Nibble::Application::Application()
{
}

Nibble::Application::~Application()
{
}

void Nibble::Application::Run()
{
	LOGGER_APP_INFO("Initializing");
	EventBus eventBus;
	// TODO Add EventHandler for contrect events

	WindowResizeEvent eWinResize(1280, 720);
	if (eWinResize.IsInCategory(EventCategory::Window))
		LOGGER_APP_INFO(eWinResize.ToString());

	// Main loop for updates
	while (true)
	{
		// TODO Update EventHandler window, keyboard, mouse etc
		eventBus.Notify();
	}
}
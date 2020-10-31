#include "pch.h"
#include "WindowsCloseEvent.h"

void Nibble::WindowsCloseEvent::SetIsHandled()
{
	std::stringstream ss;
	ss << GetName() << ": Gracefully closing...";

	LOGGER_CORE_TRACE(ss.str());

	m_IsHandled = true;
}

const char* Nibble::WindowsCloseEvent::GetName()
{
	return m_name;
}

int Nibble::WindowsCloseEvent::GetCategoryFlags()
{
	return m_categoryFlags;
}

Nibble::Event::EventType Nibble::WindowsCloseEvent::GetEventType()
{
	return m_eventType;
}


#include "pch.h"
#include "WindowsCloseEvent.h"

void Nibble::WindowsCloseEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

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

std::string Nibble::WindowsCloseEvent::ToString()
{
	std::stringstream ss;
	ss << GetName() << ": Gracefully closing...";

	return ss.str();
}

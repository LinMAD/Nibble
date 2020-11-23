#include "pch.h"
#include "WindowCloseEvent.h"

void Nibble::WindowsCloseEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

	m_IsHandled = true;
}

const char* Nibble::WindowsCloseEvent::GetName()
{
	return m_Name;
}

int Nibble::WindowsCloseEvent::GetCategoryFlags()
{
	return m_CategoryFlags;
}

Nibble::Event::EventType Nibble::WindowsCloseEvent::GetEventType()
{
	return m_EventType;
}

std::string Nibble::WindowsCloseEvent::ToString()
{
	std::stringstream ss;
	ss << GetName() << ": Gracefully closing...";

	return ss.str();
}

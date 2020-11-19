#include "pch.h"
#include "MouseButtonPressedEvent.h"

void Nibble::MouseButtonPressedEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

	m_IsHandled = true;
}

const char* Nibble::MouseButtonPressedEvent::GetName()
{
	return m_Name;
}

int Nibble::MouseButtonPressedEvent::GetCategoryFlags()
{
	return m_CategoryFlags;
}

Nibble::Event::EventType Nibble::MouseButtonPressedEvent::GetEventType()
{
	return m_EventType;
}

std::string Nibble::MouseButtonPressedEvent::ToString()
{
	std::stringstream ss;
	ss << m_Name << ": Button code -> " << m_Button;

	return ss.str();
}

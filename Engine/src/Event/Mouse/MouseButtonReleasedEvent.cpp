#include "pch.h"
#include "MouseButtonReleasedEvent.h"

void Nibble::MouseButtonReleasedEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

	m_IsHandled = true;
}

const char* Nibble::MouseButtonReleasedEvent::GetName()
{
	return m_Name;
}

int Nibble::MouseButtonReleasedEvent::GetCategoryFlags()
{
	return m_CategoryFlags;
}

Nibble::Event::EventType Nibble::MouseButtonReleasedEvent::GetEventType()
{
	return m_EventType;
}

std::string Nibble::MouseButtonReleasedEvent::ToString()
{
	std::stringstream ss;
	ss << GetName() << ": Button code -> " << m_Button;

	return ss.str();
}

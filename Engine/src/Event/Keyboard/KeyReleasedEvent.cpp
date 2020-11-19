#include "pch.h"
#include "KeyReleasedEvent.h"

void Nibble::KeyReleasedEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

	m_IsHandled = true;
}

const char* Nibble::KeyReleasedEvent::GetName()
{
	return m_Name;
}

int Nibble::KeyReleasedEvent::GetCategoryFlags()
{
	return m_CategoryFlags;
}

Nibble::Event::EventType Nibble::KeyReleasedEvent::GetEventType()
{
	return m_EventType;
}

std::string Nibble::KeyReleasedEvent::ToString()
{
	std::stringstream ss;
	ss << m_Name << ": " << m_KeyCode;

	return ss.str();
}

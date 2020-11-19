#include "pch.h"
#include "KeyTypedEvent.h"

void Nibble::KeyTypedEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

	m_IsHandled = true;
}

const char* Nibble::KeyTypedEvent::GetName()
{
	return m_Name;
}

int Nibble::KeyTypedEvent::GetCategoryFlags()
{
	return m_CategoryFlags;
}

Nibble::Event::EventType Nibble::KeyTypedEvent::GetEventType()
{
	return m_EventType;
}

std::string Nibble::KeyTypedEvent::ToString()
{
	std::stringstream ss;
	ss << m_Name << ": " << m_KeyCode;

	return ss.str();
}

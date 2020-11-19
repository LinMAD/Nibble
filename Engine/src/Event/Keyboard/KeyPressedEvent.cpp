#include "pch.h"
#include "KeyPressedEvent.h"

void Nibble::KeyPressedEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

	m_IsHandled = true;
}

const char* Nibble::KeyPressedEvent::GetName()
{
	return m_Name;
}

int Nibble::KeyPressedEvent::GetCategoryFlags()
{
	return m_CategoryFlags;
}

Nibble::Event::EventType Nibble::KeyPressedEvent::GetEventType()
{
	return m_EventType;
}

std::string Nibble::KeyPressedEvent::ToString()
{
	std::stringstream ss;
	ss << m_Name << ": " << m_KeyCode << " (" << m_RepeatCount << " repeats)";

	return ss.str();
}

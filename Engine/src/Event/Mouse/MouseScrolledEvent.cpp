#include "pch.h"
#include "MouseScrolledEvent.h"

void Nibble::MouseScrolledEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

	m_IsHandled = true;
}

const char* Nibble::MouseScrolledEvent::GetName()
{
	return m_Name;
}

int Nibble::MouseScrolledEvent::GetCategoryFlags()
{
	return m_CategoryFlags;
}

Nibble::Event::EventType Nibble::MouseScrolledEvent::GetEventType()
{
	return m_EventType;
}

std::string Nibble::MouseScrolledEvent::ToString()
{
	std::stringstream ss;
	ss << GetName() << ": Offset X:" << m_XOffset << " Y: " << m_YOffset;

	return ss.str();
}

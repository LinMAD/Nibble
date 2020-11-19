#include "pch.h"
#include "MouseMovedEvent.h"

void Nibble::MouseMovedEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

	m_IsHandled = true;
}

const char* Nibble::MouseMovedEvent::GetName()
{
	return m_Name;
}

int Nibble::MouseMovedEvent::GetCategoryFlags()
{
	return m_CategoryFlags;
}

Nibble::Event::EventType Nibble::MouseMovedEvent::GetEventType()
{
	return m_EventType;
}

std::string Nibble::MouseMovedEvent::ToString()
{
	std::stringstream ss;
	ss << GetName() << ": X(" << m_MouseX << "), Y(" << m_MouseY << ")";

	return ss.str();
}

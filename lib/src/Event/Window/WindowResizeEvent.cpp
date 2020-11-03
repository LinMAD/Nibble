#include "pch.h"
#include "WindowResizeEvent.h"

void Nibble::WindowResizeEvent::SetIsHandled()
{
	M_LOGGER_ENG_DEBUG(ToString());

	m_IsHandled = true;
}

const char* Nibble::WindowResizeEvent::GetName()
{
	return m_name;
}

int Nibble::WindowResizeEvent::GetCategoryFlags()
{
	return m_categoryFlags;
}

Nibble::Event::EventType Nibble::WindowResizeEvent::GetEventType()
{
	return m_eventType;
}

std::string Nibble::WindowResizeEvent::ToString()
{
	std::stringstream ss;
	ss << GetName() << ": " << m_Width << ", " << m_Height;

	return ss.str();
}


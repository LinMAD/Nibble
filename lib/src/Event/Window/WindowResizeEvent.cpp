#include "pch.h"
#include "WindowResizeEvent.h"

const char* Nibble::WindowResizeEvent::GetName() const
{
	return "WindowResizeEvent";
}

int Nibble::WindowResizeEvent::GetCategoryFlags() const
{
	return EventCategory::Window;
}

Nibble::Event::EventType Nibble::WindowResizeEvent::GetEventType() const
{
	return EventType::WindowResize;
}

void Nibble::WindowResizeEvent::SetIsHandled()
{
	std::stringstream ss;
	ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;

	LOGGER_CORE_TRACE(ss.str());

	m_IsHandled = true;
}

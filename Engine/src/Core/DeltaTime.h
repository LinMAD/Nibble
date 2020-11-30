#pragma once

namespace Nibble {
	struct DeltaTime
	{
	public:
		DeltaTime(float time = 0.0f): m_TimeInSeconds(time){}

		float GetSeconds() const 
		{ 
			return m_TimeInSeconds;
		}
	public:
		operator float() const
		{
			return m_TimeInSeconds;
		}
	private:
		float m_TimeInSeconds = 0.0f;
	};
}

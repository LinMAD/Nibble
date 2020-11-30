#include "pch.h"
#include "OrthographicCameraController.h"

namespace Nibble {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: 
		m_AspectRatio(aspectRatio),
		m_Camera(-2.0f, 2.0f, -2.0f, 2.0f),
		m_Rotation(rotation)
	{
	}
}

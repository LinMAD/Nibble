#pragma once

#include "OrthographicCamera.h"

namespace Nibble {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(
			float aspectRatio, 
			bool rotation = false
		);

		OrthographicCamera& GetCamera()
		{
			return m_Camera; 
		}
		const OrthographicCamera& GetCamera() const 
		{
			return m_Camera;
		}
	private:
		OrthographicCamera m_Camera;

		bool m_Rotation;

		float m_AspectRatio;
	};
}

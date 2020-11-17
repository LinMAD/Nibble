#pragma once

#include "Nibble.h"

namespace Playground {
	class TestLayer : public Nibble::ILayer
	{
	public:
		TestLayer() : ILayer("Test Layer") {}

		void OnUpdate() override
		{
			LOGGER_CLIENT_INFO("TestLayer -> On update method called");
		}

		void OnEvent(Nibble::Event& e) override
		{
			LOGGER_CLIENT_INFO("TestLayer -> {0}", e.ToString());
		}
	};
}
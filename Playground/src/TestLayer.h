#pragma once

#include "Nibble.h"

namespace Playground {
	class TestLayer : public Nibble::ILayer
	{
	public:
		TestLayer() : ILayer("Test Layer") {}
	};
}

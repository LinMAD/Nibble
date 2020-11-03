#include "Nibble.h"
#include "TestLayer.h"

namespace Playground {
	class ClientApplication : public Nibble::Engine
	{
	public:
		ClientApplication()
		{
			PushLayer(std::make_shared<TestLayer>());
		}
		~ClientApplication()
		{
		}
	};
}

// Executing main entry
Nibble::Engine* Nibble::InitilizeEngine()
{
	return new Playground::ClientApplication();
}

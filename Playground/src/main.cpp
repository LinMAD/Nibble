#include "Nibble.h"
#include "TriangleLayer.h"

namespace Playground {
	class ClientApplication : public Nibble::Engine
	{
	public:
		ClientApplication()
		{
			LOGGER_CLIENT_DEBUG("Preparing to create triangle...");
			PushLayer(std::make_shared<TriangleLayer>());
		}
		~ClientApplication() {}
	};
}

// Executing main entry
Nibble::Engine* Nibble::InitilizeEngine()
{
	 return new Playground::ClientApplication();
}

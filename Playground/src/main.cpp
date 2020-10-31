#include "Nibble.h"

class Playground : public Nibble::Engine
{
public:
	Playground()
	{
	}
	~Playground()
	{
	}
};

Nibble::Engine* Nibble::InitilizeEngine()
{
	return new Playground();
}

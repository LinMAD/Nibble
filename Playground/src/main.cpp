#include "Nibble.h"

class Playground : public Nibble::Application
{
public:
	Playground()
	{
	}
	~Playground()
	{
	}
};

Nibble::Application* Nibble::CreateApplicaiton()
{
	return new Playground();
}

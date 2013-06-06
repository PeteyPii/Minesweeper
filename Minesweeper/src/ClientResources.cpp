#include "ClientResources.h"

ClientResources::ClientResources()
{

}
ClientResources::~ClientResources()
{

}
ClientResources& ClientResources::getInstance()
{
	static ClientResources instance;	// guaranteed to be destroyed
										// instantiated on first use
	return instance;
}
void ClientResources::loadResources()
{
	background.loadFromFile("resources/images/background.jpg");

	timesFont.loadFromFile("resources/fonts/times.ttf");
}


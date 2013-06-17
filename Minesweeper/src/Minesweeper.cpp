#include "Resources.h"
#include "MinesweeperApp.h"
#include "Settings.h"

using namespace std;

int main()
{
	Settings::loadSettings();
	Resources::getInstance().loadResources();

	MinesweeperApp::getInstance().begin();

	return 0;
}
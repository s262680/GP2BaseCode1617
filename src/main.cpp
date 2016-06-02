#include "MyGame.h"

int main(int argc, char * arg[])
{
	unique_ptr<MyGame> pGame(new MyGame);

	pGame->init();
	pGame->run();

	return 0;
}

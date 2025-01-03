#include <iostream>
#include "Engine/Engine.h"
#include "TestLevel.h"

int main()
{
	Engine* gameDemo = new Engine();

	gameDemo->LoadLevel(new TestLevel());
	gameDemo->Run();

	if (gameDemo->GetIsQuit())
	if (gameDemo->GetIsQuit())
	{
		delete gameDemo;
	}

	return 0;
}
#include "PreCompiledHeader.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine* gameDemo = new Engine();
	gameDemo->LoadLevel(new Level);
	gameDemo->Run();
	gameDemo->QuitGame();

	return 0;
}
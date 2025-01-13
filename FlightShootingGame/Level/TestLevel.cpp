#include "../FlightShootingGame/Level/TestLevel.h"
#include "Engine/Engine.h"
#include "Engine/InputManager.h"
#include "Actor/Player.h"

TestLevel::TestLevel()
{
	AddActor(new Player("<A>"));
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float _dTime)
{
	Super::Update(_dTime);

	if (InputManager::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}
}

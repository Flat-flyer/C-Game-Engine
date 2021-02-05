#include "Engine/Core/CoreEngine.h"
#include "Game/Game1.h"

CoreEngine* engine;

int main(int argc, char* argv[])
{
	CoreEngine::GetInstance()->SetGameInterface(new Game1);

	if (!CoreEngine::GetInstance()->OnCreate("Game Engine", 800, 600)) {
		Debug::FatalError("Engine failed to initialize", "Main.cpp", __LINE__);
		return 0;
	}
	CoreEngine::GetInstance()->Run();
	return 0;
}
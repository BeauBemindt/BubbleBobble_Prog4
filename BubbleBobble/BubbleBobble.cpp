#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Game.h"

int main(int, char* []) {
	dae::Game game;
	game.Run();
	return 0;
}
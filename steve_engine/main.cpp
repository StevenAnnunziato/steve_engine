#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Vector2D.h>
#include <Timer.h>

#include <cstdlib>

#include "Game.h"
#include "EventSystem.h"

using namespace std;


int main()
{

	Vector2D size(800, 600);

	// init
	EventSystem::initInstance();
	EventSystem* pEventSystem = EventSystem::getInstance();
	pEventSystem->init();
	Game::initInstance();
	Game::getInstance()->initializeGame(60, size, 25);

	// run the game
	Game::getInstance()->doLoop();

	// cleanup
	Game::getInstance()->cleanupGame();
	Game::cleanupInstance();
	EventSystem::cleanupInstance(); // cleanup listeners (game) first, then event system

	// finalize
	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");
	
}
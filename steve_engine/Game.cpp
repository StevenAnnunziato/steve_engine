#include <windows.h>
#include <vector>
#include <cassert>

#include <Timer.h>

#include "Game.h"
#include "Display.h"
#include "Sprite.h"
#include "Color.h"
#include "Animation.h"

Game* Game::mpsTheGame = nullptr;

Game::Game()
{
	mMSPerFrame = 0;
}
Game::~Game()
{
	cleanupGame();
}

// instance management
Game* Game::getInstance()
{
	assert(mpsTheGame);
	return mpsTheGame;
}
void Game::initInstance()
{
	if (mpsTheGame == nullptr)
		mpsTheGame = new Game;
}
void Game::cleanupInstance()
{
	delete mpsTheGame;
	mpsTheGame = nullptr;
}

void Game::initializeGame(const float& framesPerSecond, const Vector2D& size, const int& maxUnits)
{
	// convert frames per second to milliseconds per frame
	mMSPerFrame = 1 / framesPerSecond * 1000;

	mDisplay.init(size);
	mGraphicsBufferManager.init();
	mUnitManager.initUnitManager(maxUnits, &mGraphicsBufferManager);
	mInputSystem.initInputSystem();
}
void Game::cleanupGame()
{
	// cleanup member variables
	mDisplay.cleanup();
	mUnitManager.cleanupUnitManager();
	mInputSystem.cleanupInputSystem();
	mGraphicsBufferManager.cleanup();

	// make sure the game loops next time
	mGameLooping = true;

}

void Game::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EventType::QUIT_GAME)
	{
		mGameLooping = false;
	}
	else if (theEvent.getType() == EventType::ADD_UNIT)
	{
		const AddUnitEvent& addEvent = static_cast<const AddUnitEvent&>(theEvent);
		mUnitManager.addUnit(addEvent.getPos() - Vector2D(30, 30));
	}
	else if (theEvent.getType() == EventType::DELETE_UNIT)
	{
		const DeleteUnitEvent& deleteEvent = static_cast<const DeleteUnitEvent&>(theEvent);
		mUnitManager.removeAtPosition(deleteEvent.getPos());
	}
	else if (theEvent.getType() == EventType::TOGGLE_FREEZE_ANIMATIONS)
	{
		const AnimationFreezeEvent& pauseEvent = static_cast<const AnimationFreezeEvent&>(theEvent);
		mUnitManager.pauseAllAnimations(pauseEvent.getFrozen());
	}
}

void Game::doLoop()
{
	// called once in main
	while (mGameLooping)
	{
		// get current time
		double startTime = mTimer.getElapsedTime();

		processInput();
		updateGameState();
		render();

		// sleep until it's time to go to next frame
		mTimer.sleep(startTime + mMSPerFrame - mTimer.getElapsedTime());
	}
}

// Note: Check held down keys and buttons here
void Game::processInput()
{
	// update the InputSystem to check for key presses and releases
	mInputSystem.update();	
	
}
void Game::updateGameState()
{
	// update unit manager which updates all units
	mUnitManager.update(mDisplay, mMSPerFrame);
}
void Game::render()
{
	// draw background seperately
	GraphicsBuffer* woods = mGraphicsBufferManager.getGraphicsBuffer("background");
	Sprite bgSprite(woods, Vector2D(0, 0), woods->getWidth(), woods->getHeight());
	mDisplay.draw(Vector2D(0, 0), bgSprite, 0.5);

	// draw units from unitManager
	mUnitManager.draw(mDisplay);

	// update the display
	mDisplay.flip();
}
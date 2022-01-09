#include "InputSystem.h"
#include "Game.h"
#include "EventSystem.h"
#include "Event.h"

InputSystem::InputSystem()
{
	// initialize state arrays
	for (int i = 0; i < NUM_KEYS; i++)
	{
		mPreviousKeyboardStates[i] = false;
		mCurrentKeyboardStates[i] = false;
	}
	for (int i = 0; i < NUM_MOUSE_BUTTONS; i++)
	{
		mPreviousMouseStates[i] = false;
		mCurrentMouseStates[i] = false;
	}
}
InputSystem::~InputSystem()
{
	cleanupInputSystem();
}

void InputSystem::initInputSystem()
{
	// get a pointer to the game instance
	mpGameInstance = Game::getInstance();

	// Init keyboard and mouse
	if (!al_install_keyboard())
	{
		cout << "error - keyboard not installed\n";
	}
	if (!al_install_mouse())
	{
		cout << "error - mouse not installed\n";
	}
}
void InputSystem::cleanupInputSystem()
{
	// nothing
}

/*
* 
*	- Keep a running tab of each key every frame
*	- Store the key's state every frame
*	- Call the appropriate press or release function if the state changes
*   - do the same for mouse
* 
*/
void InputSystem::update()
{
	// for each key the game knows about
	for (int i = 0; i < NUM_KEYS; i++)
	{
		// get current state of this key
		mCurrentKeyboardStates[i] = isKeyPressed(mKeys[i]);

		// determine which keys were pressed (false -> true)
		if (mPreviousKeyboardStates[i] == false && mCurrentKeyboardStates[i] == true)
			onKeyDown(mKeys[i]);

		// determine which keys were released (true -> false)
		if (mPreviousKeyboardStates[i] == true && mCurrentKeyboardStates[i] == false)
			onKeyUp(mKeys[i]);

		// set previous states for next frame
		for (int i = 0; i < NUM_KEYS; i++)
		{
			mPreviousKeyboardStates[i] = mCurrentKeyboardStates[i];
		}
	}

	// for each mouse button the game knows about
	for (int i = 0; i < NUM_MOUSE_BUTTONS; i++)
	{
		// get current state of this key
		mCurrentMouseStates[i] = isMouseButtonPressed(mButtons[i]);

		// determine which keys were pressed (false -> true)
		if (mPreviousMouseStates[i] == false && mCurrentMouseStates[i] == true)
			onMouseDown(mButtons[i]);

		// determine which keys were released (true -> false)
		if (mPreviousMouseStates[i] == true && mCurrentMouseStates[i] == false)
			onMouseUp(mButtons[i]);

		// set previous states for next frame
		for (int i = 0; i < NUM_MOUSE_BUTTONS; i++)
		{
			mPreviousMouseStates[i] = mCurrentMouseStates[i];
		}
	}

}

Vector2D InputSystem::getCurrentMousePos()
{
	ALLEGRO_MOUSE_STATE state;

	al_get_mouse_state(&state);

	return Vector2D(state.x, state.y);
}

bool InputSystem::isMouseButtonPressed(MouseButton button)
{
	ALLEGRO_MOUSE_STATE state;

	al_get_mouse_state(&state);

	if (button == MouseButton::LEFT)
	{
		if (state.buttons & 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (button == MouseButton::RIGHT)
	{
		if (state.buttons & 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (button == MouseButton::CENTER)
	{
		if (state.buttons & 4)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool InputSystem::isKeyPressed(KeyCode theKey)
{
	ALLEGRO_KEYBOARD_STATE state;
	al_get_keyboard_state(&state);

	if (al_key_down(&state, (int)theKey))
	{
		return true;
	}

	return false;
}

void InputSystem::onKeyDown(KeyCode pressedKey)
{
	if (pressedKey == KeyCode::SPACE)
		mpGameInstance->handleEvent(AnimationFreezeEvent(mpGameInstance->getUnitManager().getPaused()));
}
void InputSystem::onKeyUp(KeyCode releasedKey)
{

	// exit game loop
	if (releasedKey == KeyCode::ESCAPE)
		mpGameInstance->handleEvent(Event(EventType::QUIT_GAME));
	

}
void InputSystem::onMouseDown(MouseButton pressedButton)
{
	// remove unit
	if (pressedButton == MouseButton::LEFT)
		mpGameInstance->handleEvent(AddUnitEvent(getCurrentMousePos()));

	// add unit
	if (pressedButton == MouseButton::RIGHT)
		mpGameInstance->handleEvent(DeleteUnitEvent(getCurrentMousePos()));
}
void InputSystem::onMouseUp(MouseButton releasedButton)
{

}
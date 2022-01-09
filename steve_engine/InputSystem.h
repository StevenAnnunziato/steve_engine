#pragma once

#include <allegro5/allegro.h>

#include <Vector2D.h>
#include <Trackable.h>

class Game;

enum class KeyCode
{
	F = ALLEGRO_KEY_F,
	S = ALLEGRO_KEY_S,
	ENTER = ALLEGRO_KEY_ENTER,
	SPACE = ALLEGRO_KEY_SPACE,
	ESCAPE = ALLEGRO_KEY_ESCAPE
};

enum class MouseButton
{
	LEFT,
	RIGHT,
	CENTER
};

class InputSystem :public Trackable
{

public:
	InputSystem();
	~InputSystem();

	void initInputSystem();
	void cleanupInputSystem();

	Vector2D getCurrentMousePos();
	bool isMouseButtonPressed(MouseButton button);
	bool isKeyPressed(KeyCode theKey);

	// key up and down functions for convenience
	void onKeyDown(KeyCode pressedKey);
	void onKeyUp(KeyCode releasedKey);
	void onMouseDown(MouseButton pressedButton);
	void onMouseUp(MouseButton releasedButton);

	void update();

private:
	Game* mpGameInstance;

	// keyboard
	static const int NUM_KEYS = 5;
	bool mPreviousKeyboardStates[NUM_KEYS];
	bool mCurrentKeyboardStates[NUM_KEYS];
	KeyCode mKeys[NUM_KEYS] = { KeyCode::ESCAPE, KeyCode::ENTER, KeyCode::SPACE, KeyCode::F, KeyCode::S };

	// mouse
	static const int NUM_MOUSE_BUTTONS = 3;
	bool mPreviousMouseStates[NUM_MOUSE_BUTTONS];
	bool mCurrentMouseStates[NUM_MOUSE_BUTTONS];
	MouseButton mButtons[NUM_MOUSE_BUTTONS] = { MouseButton::LEFT, MouseButton::RIGHT, MouseButton::CENTER };
};
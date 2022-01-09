#pragma once

#include <Trackable.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <Windows.h>
#include <Trackable.h>
#include <Vector2D.h>

#include "GraphicsBuffer.h"
#include "Font.h"

class Sprite;
class Color;

using namespace std;

class Display :public Trackable
{

	// public methods
	public:
		enum class Alignment
		{
			Left,
			Center,
			Right
		};

		// constructor / destructor
		Display();
		~Display();

		// init/cleanup
		void init(const Vector2D& size);
		void cleanup();

		// allegro draw functions
		void flip();
		void clearDisplay(const Sprite& sprite);
		void draw(const Vector2D& loc, Sprite& sprite, float scale = 1);
		void draw(const GraphicsBuffer& targetBuffer, const Vector2D& loc, Sprite& sprite, float scale = 1);
		void writeText(const Vector2D& loc, const Font& font, Color& color, const string& text);
		void writeText(const GraphicsBuffer& targetBuffer, const Vector2D& loc, const Font& font, Color& color, const string& text);
		void saveBuffer(const GraphicsBuffer& targetBuffer, const string& filename);

		// accessors
		Vector2D getWindowSize()
		{
			return mWindowSize;
		}
		int getWidth()
		{
			return al_get_display_width(mpDisplay);
		}
		int getHeight()
		{
			return al_get_display_height(mpDisplay);
		}
		GraphicsBuffer* getBackbuffer()
		{
			al_get_backbuffer(mpDisplay);
		}
	
	// private member variables
	private:
		Vector2D mWindowSize;

		ALLEGRO_DISPLAY* mpDisplay;
		GraphicsBuffer* mpBackBuffer;

};
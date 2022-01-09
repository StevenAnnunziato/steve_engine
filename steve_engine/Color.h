#pragma once

#include <allegro5/allegro.h>
#include "Trackable.h"
#include <Windows.h>

class Color :public Trackable
{
	friend class Display;

	public:
		Color(const int& r, const int& g, const int& b, const int& a);

		int getR()
		{
			return r;
		}
		int getG()
		{
			return g;
		}
		int getB()
		{
			return b;
		}
		int getA()
		{
			return a;
		}

	private:
		int r;
		int g;
		int b;
		int a;

		ALLEGRO_COLOR getAllegroColor()
		{
			return al_map_rgba(r, g, b, a);
		}

};
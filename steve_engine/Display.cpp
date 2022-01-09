#include "Display.h"
#include "Vector2D.h"
#include "Sprite.h"
#include "Color.h"
#include <cassert>
#include <sstream>

// constructor / destructor
Display::Display()
{
	mWindowSize = Vector2D(0, 0);
}
Display::~Display()
{
	cleanup();

	// only do this once when the game's display object is destroyed
	al_destroy_display(mpDisplay);
}

// draw functions
void Display::init(const Vector2D& size)
{

	// init allegro
	if (!al_init())
	{
		cout << "error initting Allegro\n";
		system("pause");
	}
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
		system("pause");
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
		system("pause");
	}
	if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
		system("pause");
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
		system("pause");
	}
	if (!al_install_audio())
	{
		cout << "error - Audio Add-on not initted\n";
		system("pause");
	}
	if (!al_init_acodec_addon())
	{
		cout << "error - Audio Codec Add-on not initted\n";
		system("pause");
	}
	if (!al_reserve_samples(1))
	{
		cout << "error - samples not reserved\n";
		system("pause");
	}

	mpDisplay = al_create_display(size.getX(), size.getY());
	assert(mpDisplay);

	mWindowSize = size;
}
void Display::cleanup()
{
	// nothing
}

void Display::flip()
{
	al_flip_display();
}
void Display::clearDisplay(const Sprite& sprite)
{
	al_clear_to_color(al_map_rgba(255, 255, 255, 255));
}
void Display::draw(const Vector2D& loc, Sprite& sprite, float scale)
{
	assert(!isnan(loc.getX()));
	al_draw_scaled_bitmap(sprite.getBuffer()->mpBitmap,
						  sprite.getSourceLoc().getX(), sprite.getSourceLoc().getY(),
						  sprite.getWidth(), sprite.getHeight(),
						  loc.getX(), loc.getY(),
						  sprite.getWidth() * scale, sprite.getHeight() * scale,
						  0);
}
void Display::draw(const GraphicsBuffer& targetBuffer, const Vector2D& loc, Sprite& sprite, float scale)
{
	// set the target bitmap
	ALLEGRO_BITMAP* oldBitmap = al_get_target_bitmap();
	al_set_target_bitmap(targetBuffer.mpBitmap);

	// draw
	draw(loc, sprite, scale);

	// set the target back
	al_set_target_bitmap(oldBitmap);
}
void Display::writeText(const Vector2D& loc, const Font& font, Color& color, const string& text)
{
	al_draw_text(font.mpFont,
				 color.getAllegroColor(),
				 loc.getX(), loc.getY(),
				 ALLEGRO_ALIGN_CENTER,
				 text.c_str());
}
void Display::writeText(const GraphicsBuffer& targetBuffer, const Vector2D& loc, const Font& font, Color& color, const string& text)
{
	// set the target bitmap
	ALLEGRO_BITMAP* oldBitmap = al_get_target_bitmap();
	al_set_target_bitmap(targetBuffer.mpBitmap);

	// draw
	writeText(loc, font, color, text);

	// set the target back
	al_set_target_bitmap(oldBitmap);
}
void Display::saveBuffer(const GraphicsBuffer& targetBuffer, const string& filename)
{
	al_save_bitmap(filename.c_str(), targetBuffer.mpBitmap);
}
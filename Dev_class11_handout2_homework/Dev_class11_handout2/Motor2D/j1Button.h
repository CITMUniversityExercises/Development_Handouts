#ifndef __j1Button_H__
#define __j1Button_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"

enum class Button_Type
{
	BUTTON,
	LABEL,

	NONE
};

enum class Text_Position
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	MIDDLE
};

struct Text
{
	const char* text;
	const char* text2;
	SDL_Color  color;
	iPoint position;
	SDL_Rect font_Rect;
	SDL_Texture* tex;
	Text_Position location;
};

struct ButtonInfo
{
	Button_Type type;
	SDL_Rect rect;
	Text label;
	iPoint position;
	SDL_Texture* tex;
	bool hovering = false;
};

class j1Button
{
public:
	friend class j1Scene;
	friend class j1Gui;

	j1Button(Button_Type type, iPoint position, Text label, SDL_Texture* tex, SDL_Rect rect);

	~j1Button();

	void FixedUpdate();

private:
	ButtonInfo Data;
};


#endif // __j1Button_H__

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
	//iPoint position;
	SDL_Rect font_Rect;
	SDL_Rect logic_rect;
	SDL_Texture* tex;
	Text_Position location;
	bool hovering = false;
	bool clicking = false;
};

struct Buttonrects
{
	SDL_Rect current_rect = { 0,0,0,0 };
	SDL_Rect rect_hover = { 0,0,0,0 };
	SDL_Rect rect_click = { 0,0,0,0 };
	SDL_Rect rect_normal = { 0,0,0,0 };
};

struct ButtonInfo
{
	Button_Type type;
	Buttonrects rects;
	SDL_Rect logic_rect;
	Text label;
	iPoint position;
	SDL_Texture* tex;
	bool hovering = false;
	bool clicking = false;
};

class j1Button
{
public:
	friend class j1Scene;
	friend class j1Gui;

	j1Button(Button_Type type, iPoint position, Text label, SDL_Texture* tex, Buttonrects rects);

	~j1Button();

	void FixedUpdate();

private:
	ButtonInfo Data;
};


#endif // __j1Button_H__

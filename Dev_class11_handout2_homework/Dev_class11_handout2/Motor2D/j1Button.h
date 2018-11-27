#ifndef __j1Button_H__
#define __j1Button_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"

enum class Button_Type
{
	BUTTON,

	NONE
};

struct Text
{
	const char* text;
	SDL_Color  color;
	iPoint pos;
};

struct ButtonInfo
{
	Button_Type type;
	//SDL_Texture* tex;
	SDL_Rect rect;
	Text label;
	iPoint position;
};

class j1Button
{
public:

	j1Button(Button_Type type, Text label, iPoint position, SDL_Rect rect = {0,0,0,0});

	~j1Button();

	void on_press();
	void on_hover();

	void FixedUpdate();

private:
	ButtonInfo Data;
};


#endif // __j1Button_H__

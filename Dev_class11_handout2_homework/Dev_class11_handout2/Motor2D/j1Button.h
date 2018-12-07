#ifndef __j1Button_H__
#define __j1Button_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1UI_Element.h"

struct Buttonrects
{
	SDL_Rect logic_rect = { 0,0,0,0 };
	SDL_Rect current_rect = { 0,0,0,0 };
	SDL_Rect rect_hover = { 0,0,0,0 };
	SDL_Rect rect_click = { 0,0,0,0 };
	SDL_Rect rect_normal = { 0,0,0,0 };
};

struct ButtonInfo
{
	Buttonrects rects;
	iPoint position;
	SDL_Texture* tex;
	Booleans bools;
	/*bool hovering = false;
	bool clicking = false;*/
	ELEMENTS type;

	int parent_id = -1;
};

class j1Button : public j1UI_Element
{
	friend class j1Gui;
public:

	j1Button(ButtonInfo Data) : Data(Data)
	{

	}

	~j1Button();

	void FixedUpdate();
	ELEMENTS GetType() override;
	Buttonrects* Getrects() override;
	Booleans * GetBooleans() override;

private:
	ButtonInfo Data;
};


#endif // __j1Button_H__

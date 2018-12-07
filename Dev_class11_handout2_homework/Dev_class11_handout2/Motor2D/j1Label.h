#ifndef __j1Label_H__
#define __j1Label_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1UI_Element.h"

enum class Text_Position
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	MIDDLE,

	NONE
};

struct Text
{
	const char* text;
	const char* text2;
	SDL_Color  color;
	SDL_Texture* tex;
	Text_Position Place;
	Booleans bools;
	ELEMENTS type;
	Buttonrects rects;
	iPoint position;

	int parent_id = -1;
};

class j1Label : public j1UI_Element
{
public:
	friend class j1Scene;
	friend class j1Gui;

	j1Label(Text Data) : Data(Data){}

	~j1Label(){}

	void FixedUpdate();

	ELEMENTS GetType() override;
	Booleans * GetBooleans() override;
    Buttonrects* Getrects() override;

	//--- Label placing functions ---
	inline void PlaceAtTop();
	inline void PlaceAtBottom();
	inline void PlaceAtLeft();
	inline void PlaceAtRight();
	inline void PlaceAtMiddle();

private:
	Text Data;
};


#endif // __j1Label_H__

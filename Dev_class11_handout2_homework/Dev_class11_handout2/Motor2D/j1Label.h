#ifndef __j1Label_H__
#define __j1Label_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"

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
	SDL_Rect font_Rect;
	SDL_Rect logic_rect;
	SDL_Texture* tex;
	Text_Position location;
	bool hovering = false;
	bool clicking = false;

};

class j1Label
{
public:
	friend class j1Scene;
	friend class j1Gui;

	j1Label(const char* text, SDL_Color  color, const char* text2 = "");

	~j1Label();

	void FixedUpdate();

	//--- Label placing functions ---
	//inline void PlaceAtTop(ButtonInfo &Data);
	//inline void PlaceAtBottom(ButtonInfo  &Data);
	//inline void PlaceAtLeft(ButtonInfo &Data);
	//inline void PlaceAtRight(ButtonInfo &Data);
	//inline void PlaceAtMiddle(ButtonInfo &Data);

private:
	Text Data;
};


#endif // __j1Label_H__

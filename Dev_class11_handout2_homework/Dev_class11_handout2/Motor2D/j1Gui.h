#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1Button.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes


// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	friend class j1Button;
	friend class j1Scene;

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	SDL_Texture* GetAtlas() const;

	SDL_Texture* CreateImage(const char* path);

	// --- Create/Destroy ---

	j1Button* CreateButton(Button_Type type, iPoint position, Text label, SDL_Texture* tex, Buttonrects rect);

	Text CreateLabel(const char* text, SDL_Color  color, Text_Position location = Text_Position::MIDDLE , const char* text2="");

	Buttonrects CreateRects(SDL_Rect normal, SDL_Rect hover, SDL_Rect click);

	j1Button* DestroyButton(Button_Type type);

	bool isInbound(SDL_Rect &rect);
	bool isClicked(SDL_Rect &rect);

	void DebugDraw();

private:

	p2List <j1Button*> button_list;
	//p2List <SDL_Texture*> images;

	SDL_Texture* atlas = nullptr;
	SDL_Texture* background = nullptr;
	SDL_Texture* wowlogo = nullptr;
	SDL_Texture* blizzardlogo = nullptr;
	SDL_Texture* esrb = nullptr;
	SDL_Texture* tickbox = nullptr;
	SDL_Texture* greyrect = nullptr;
	SDL_Texture* redrect = nullptr;

	p2SString atlas_file_name;

	iPoint mouse_pos = { 0,0 };
	iPoint click_pos = { 0,0 };

	bool debug = true;
};

#endif // __j1GUI_H__
#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1UI_Element.h"
#include "j1Button.h"

#define CURSOR_WIDTH 2


// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	//friend class j1Button;
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

	SDL_Texture* GetAtlas() const;

	SDL_Texture* CreateImage(const char* path);

	void DeployUI(pugi::xml_node &UIconfig);

	// --- Create/Destroy ---

	// --- UI ELEMENT ---


	//// --- BUTTON ---
	j1UI_Element* CreateButton(ButtonInfo &Data);
	ButtonInfo FillButton(pugi::xml_node &UIconfig);



	//Buttonrects CreateRects(SDL_Rect normal, SDL_Rect hover, SDL_Rect click);
	//// --- LABEL ---
	//Text* CreateLabel(const char* text, SDL_Color  color, const char* text2="");


	// --- Utilities ---
	bool isInbound(SDL_Rect &rect);
	bool isClicked(SDL_Rect &rect);

	void DebugDraw();

	//bool Colorize(SDL_Texture& tex, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
	//void DeColorize(SDL_Texture& tex) const;


private:

	p2List <j1UI_Element*> UIelements;;
	j1Button* focus = nullptr;
	int focus_index = 0;

	SDL_Texture* atlas = nullptr;
    p2SString atlas_file_name;

	iPoint mouse_pos = { 0,0 };
	iPoint click_pos = { 0,0 };

	bool debug = true;
};

#endif // __j1GUI_H__
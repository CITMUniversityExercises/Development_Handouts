#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class j1Button;


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// --- UI ---
	void ONhover_label(j1Button &button);
	void OFFhover_label(j1Button &button);
	void ONclick_label(j1Button &button);
	void OFFclick_label(j1Button &button);

	void ONhover(j1Button &button);
	void OFFhover(j1Button &button);
	void ONclick(j1Button &button);
	void OFFclick(j1Button &button);

private:
	SDL_Texture* debug_tex;
	GuiImage* banner;
	GuiText* text;
};

#endif // __j1SCENE_H__
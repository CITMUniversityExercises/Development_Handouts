#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = CreateImage(atlas_file_name.GetString());
	background = CreateImage("gui/login_background.png");
	wowlogo = CreateImage("gui/Glues-Logo.png");
	blizzardlogo = CreateImage("gui/Glues-BlizzardLogo.png");
	esrb = CreateImage("gui/Glues-ESRBRating.png");
	tickbox = CreateImage("gui/SquareButtonTextures.png");
	greyrect = CreateImage("gui/UI-Panel-Button-Disabled.png");
	redrect = CreateImage("gui/UI-Panel-Button-Up.png");
	
	if (atlas == nullptr)
		return false;

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item <j1Button*> * item = button_list.start;

	while (item)
	{
		item->data->FixedUpdate();
		item = item->next;
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item <j1Button*> * item = button_list.start;

	while (item)
	{
		RELEASE(item->data);
		item = item->next;
	}

	button_list.clear();

	//images.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

SDL_Texture * j1Gui::CreateImage(const char * path)
{
	SDL_Texture * tex = App->tex->Load(path);

	//images.add(tex);

	return tex;
}

j1Button * j1Gui::CreateButton(Button_Type type, iPoint position, Text label, SDL_Texture* tex, SDL_Rect rect)
{
	j1Button *button = new j1Button(type, position, label,tex,rect);

	button_list.add(button);

	return button;
}

Text j1Gui::CreateLabel(const char * text, SDL_Color color, Text_Position location)
{
	Text label;
	label.color = color;
	label.position = { 0,0 };
	label.text = text;
	label.font_Rect = { 0,0,0,0 };
	label.location = location;
	label.tex = App->font->Print(label.text, label.color, App->font->default);
	App->font->CalcSize(label.text, label.font_Rect.w, label.font_Rect.h, App->font->default);

	return label;
}

j1Button * j1Gui::DestroyButton(Button_Type type)
{
	return nullptr;
}

// class Gui ---------------------------------------------------


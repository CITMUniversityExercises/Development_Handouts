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
	atlas = App->tex->Load(atlas_file_name.GetString());

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

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

j1Button * j1Gui::CreateButton(Button_Type type, Text label, iPoint position)
{
	j1Button *button = new j1Button(type, label, position);

	button_list.add(button);

	return button;
}

j1Button * j1Gui::DestroyButton(Button_Type type)
{
	return nullptr;
}

// class Gui ---------------------------------------------------


#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Scene.h"

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
	App->input->GetMousePosition(mouse_pos.x,mouse_pos.y);

	p2List_item <j1Button*> * item = button_list.start;

	while (item)
	{
		// --- Handling label ---
		if (isInbound(item->data->Data.label.logic_rect))
		{
			if (!item->data->Data.label.hovering)
			{
				App->scene->ONhover_label(*item->data);
			}
		}
		else if (!isInbound(item->data->Data.label.logic_rect))
		{
			if (item->data->Data.label.hovering)
			{
				App->scene->OFFhover_label(*item->data);
			}
		}

		//// --- Handling button ---
		//if (isInbound(item->data->Data.logic_rect))
		//{
		//	if (!item->data->Data.hovering)
		//	{
		//		App->scene->ONhover(*item->data);
		//	}
		//}
		//else if (!isInbound(item->data->Data.logic_rect))
		//{
		//	if (item->data->Data.hovering)
		//	{
		//		App->scene->OFFhover(*item->data);
		//	}
		//}

		item = item->next;
	}

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

	DebugDraw();

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

Text j1Gui::CreateLabel(const char * text, SDL_Color color, Text_Position location, const char* text2)
{
	Text label;

	label.color = color;
	label.text = text;
	label.text2 = text2;
	label.location = location;

	label.font_Rect = { 0,0,0,0 };
	label.tex = App->font->Print(label.text, label.color, App->font->default);
	App->font->CalcSize(label.text, label.font_Rect.w, label.font_Rect.h, App->font->default);
	label.logic_rect = { 0,0,label.font_Rect.w,label.font_Rect.h };

	return label;
}

j1Button * j1Gui::DestroyButton(Button_Type type)
{
	return nullptr;
}

bool j1Gui::isInbound(SDL_Rect &rect)
{
	return (rect.x < mouse_pos.x &&
		rect.x + rect.w > mouse_pos.x &&
		rect.y < mouse_pos.y  &&
		rect.h + rect.y > mouse_pos.y);
}

void j1Gui::DebugDraw()
{

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) //collider draw
		debug = !debug;

	if (debug == false)
		return;

	p2List_item <j1Button*> *item;
	item = button_list.start;

	Uint8 alpha = 80;

	while (item != NULL)
	{

		switch (item->data->Data.type)
		{
		case Button_Type::LABEL: // white
			App->render->DrawQuad(item->data->Data.label.logic_rect, 255, 255, 255, alpha);
			break;
		case Button_Type::BUTTON: // white
			App->render->DrawQuad(item->data->Data.logic_rect, 255, 255, 255, alpha);
			break;

		}
		item = item->next;
	}

}

// class Gui ---------------------------------------------------


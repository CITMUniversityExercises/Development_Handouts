#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Window.h"

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

	// --- Button test textures ---
	//atlas2 = CreateImage(atlas_file_name.GetString());
	//atlas3 = CreateImage(atlas_file_name.GetString());
	//atlas4 = CreateImage(atlas_file_name.GetString());


	
	if (atlas == nullptr)
		return false;

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	App->input->GetMousePosition(mouse_pos.x,mouse_pos.y);

	if (App->input->GetMouseButtonDown(1) == KEY_REPEAT)
		click_pos = mouse_pos;
	else
		click_pos = { -1,-1 };

	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{
		/*App->scene->ONFocus();*/
	}

	p2List_item <j1UI_Element*> * item = UIelements.start;

	while (item)
	{
		if (isInbound(item->data->Getrects()->logic_rect))
		{
			if (!item->data->GetBooleans()->hovering)
			{
				App->scene->ONhover(*item->data);
			}

			if (isClicked(item->data->Getrects()->logic_rect))
			{
				if (!item->data->GetBooleans()->clicking)
				{
					App->scene->ONclick(*item->data);
				}
			}
			else
			{
				if (item->data->GetBooleans()->clicking)
				{
					App->scene->OFFclick(*item->data);
				}
			}
		}

		else if (!isInbound(item->data->Getrects()->logic_rect))
		{
			if (item->data->GetBooleans()->hovering)
			{
				App->scene->OFFhover(*item->data);
			}
			if (isClicked(item->data->Getrects()->logic_rect))
			{
				if (item->data->GetBooleans()->clicking)
				{
					App->scene->OFFclick(*item->data);
				}
			}
		}

		item = item->next;
	}


	
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item <j1UI_Element*> * item = UIelements.start;

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

	p2List_item <j1UI_Element*> * item = UIelements.start;

	while (item)
	{
		item->data->children.clear();

		RELEASE(item->data);
		item = item->next;
	}

	UIelements.clear();

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
	return tex;
}

void j1Gui::DeployUI(pugi::xml_node &UIconfig)
{
	UIconfig = UIconfig.child("Element");
	uint elem_type;

	while (UIconfig)
	{
		elem_type = UIconfig.child("type").attribute("id").as_uint();

		if (elem_type == static_cast <uint> (ELEMENTS::PANEL))
		{

		}

		if (elem_type == static_cast <uint> (ELEMENTS::BUTTON))
		{
			CreateButton(FillButton(UIconfig));
		}

		if (elem_type == static_cast <uint> (ELEMENTS::LABEL))
		{

		}

		UIconfig = UIconfig.next_sibling();
	}
}

ButtonInfo j1Gui::FillButton(pugi::xml_node & UIconfig)
{
	ButtonInfo Data;

	// --- Parent ID ---
	Data.parent_id= UIconfig.child("parent").attribute("id").as_int();

	Data.type = (ELEMENTS) UIconfig.child("type").attribute("id").as_int();

	// --- Position ---
	Data.position.x = UIconfig.child("position").attribute("x").as_int();
	Data.position.y = UIconfig.child("position").attribute("y").as_int();

	// --- Texture ---
	Data.tex = CreateImage(UIconfig.child("Texture").attribute("path").as_string());

	// --- Rectangles ---
	Data.rects.logic_rect.x = Data.position.x;
	Data.rects.logic_rect.y = Data.position.y;
	Data.rects.logic_rect.w = UIconfig.child("logic_rect").attribute("w").as_int();
	Data.rects.logic_rect.h = UIconfig.child("logic_rect").attribute("h").as_int();

	Data.rects.rect_normal.x = UIconfig.child("normal_rect").attribute("x").as_int();
	Data.rects.rect_normal.y = UIconfig.child("normal_rect").attribute("y").as_int();
	Data.rects.rect_normal.w = UIconfig.child("normal_rect").attribute("w").as_int();
	Data.rects.rect_normal.h = UIconfig.child("normal_rect").attribute("h").as_int();
	Data.rects.current_rect = Data.rects.rect_normal;

	Data.rects.rect_hover.x = UIconfig.child("hover_rect").attribute("x").as_int();
	Data.rects.rect_hover.y = UIconfig.child("hover_rect").attribute("y").as_int();
	Data.rects.rect_hover.w = UIconfig.child("hover_rect").attribute("w").as_int();
	Data.rects.rect_hover.h = UIconfig.child("hover_rect").attribute("h").as_int();

	Data.rects.rect_click.x = UIconfig.child("click_rect").attribute("x").as_int();
	Data.rects.rect_click.y = UIconfig.child("click_rect").attribute("y").as_int();
	Data.rects.rect_click.w = UIconfig.child("click_rect").attribute("w").as_int();
	Data.rects.rect_click.h = UIconfig.child("click_rect").attribute("h").as_int();

	return Data;
}

j1UI_Element * j1Gui::CreateButton(ButtonInfo &Data)
{
	j1UI_Element *button = (j1UI_Element*) new j1Button(Data);

	if (Data.parent_id != -1)
	{
		button->parent = UIelements.At(Data.parent_id)->data;
		UIelements.At(Data.parent_id)->data->children.add(button);
	}

	UIelements.add(button);


	// --- Positioning button ---
	button->position = Data.position;

	if (Data.parent_id != -1)
	{
		button->position.x = button->parent->position.x + Data.position.x;
		button->position.y = button->parent->position.y + Data.position.y;
	}

	return button;
}

//Text* j1Gui::CreateLabel(const char * text, SDL_Color color, const char* text2)
//{
//	Text label;
//
//	label.color = color;
//	label.text = text;
//	label.text2 = text2;
//
//	label.font_Rect = { 0,0,0,0 };
//	label.tex = App->font->Print(label.text, label.color, App->font->default);
//	App->font->CalcSize(label.text, label.font_Rect.w, label.font_Rect.h, App->font->default);
//	label.logic_rect = { 0,0,label.font_Rect.w,label.font_Rect.h };
//
//	j1Label *label = new j1Label(label.);
//
//	return &label;
//}
//
//Buttonrects j1Gui::CreateRects(SDL_Rect normal, SDL_Rect hover, SDL_Rect click)
//{
//	Buttonrects rects;
//
//	rects.rect_normal = normal;
//	rects.rect_hover = hover;
//	rects.rect_click = click;
//	rects.current_rect = normal;
//
//	return rects;
//}

//j1Button * j1Gui::DestroyButton(Button_Type type)
//{
//	return nullptr;
//}

bool j1Gui::isInbound(SDL_Rect &rect)
{
	return (rect.x < mouse_pos.x &&
		rect.x + rect.w > mouse_pos.x &&
		rect.y < mouse_pos.y  &&
		rect.h + rect.y > mouse_pos.y);
}

bool j1Gui::isClicked(SDL_Rect & rect)
{
	return (rect.x < click_pos.x &&
		rect.x + rect.w > click_pos.x &&
		rect.y < click_pos.y  &&
		rect.h + rect.y > click_pos.y);
}

void j1Gui::DebugDraw()
{

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) 
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;

	p2List_item <j1UI_Element*> * item = UIelements.start;

	while (item != NULL)
	{

		//switch (item->data->Data.type)
		//{
		//case Button_Type::LABEL: // white
		App->render->DrawQuad(item->data->Getrects()->logic_rect, 255, 255, 255, alpha);
		//	break;
		//case Button_Type::BUTTON: // white
		//	App->render->DrawQuad(item->data->Data.logic_rect, 255, 255, 255, alpha);
		//	break;

		//}
		item = item->next;
	}

}

//void j1Gui::DeColorize(SDL_Texture & tex) const
//{
//	SDL_SetTextureColorMod(&tex, 255, 255, 255);
//}
//
//bool j1Gui::Colorize(SDL_Texture& tex, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
//{
//	bool ret = true;
//
//	SDL_SetTextureBlendMode(&tex, SDL_BLENDMODE_BLEND);
//	SDL_SetTextureColorMod(&tex, r, g, b);
//
//	return ret;
//}

// class Gui ---------------------------------------------------


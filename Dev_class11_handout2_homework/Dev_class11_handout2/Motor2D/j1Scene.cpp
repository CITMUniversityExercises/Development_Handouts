#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Button.h"
#include "j1Fonts.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	// TODO 3: Create the banner (rect {485, 829, 328, 103}) and the text "Hello World"

	//Text label = App->gui->CreateLabel("Hello World", { 120,0,120,255 });
	//SDL_Rect temprect = { 485, 829, 328, 103 };

	//iPoint tempos = { App->render->camera.w / 2, 0 };
	//App->gui->CreateButton(Button_Type::BUTTON, label, tempos,temprect);

	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ 0,0 }, App->gui->CreateLabel("", { 0,0,0,255 }), App->gui->background, SDL_Rect{ 0,0,1920,1080 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ -50,25 }, App->gui->CreateLabel("", { 0,0,0,255 }), App->gui->wowlogo, SDL_Rect{ 0,0,512,256 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{App->render->camera.w/2-64,App->render->camera.h-150}, App->gui->CreateLabel("", { 0,0,0,255 }), App->gui->blizzardlogo, SDL_Rect{ 0,0,128,128 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ 25,App->render->camera.h-200}, App->gui->CreateLabel("", { 0,0,0,255 }), App->gui->esrb, SDL_Rect{ 0,0,128,128 });

	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ App->render->camera.w/2-64,App->render->camera.h/2 }, App->gui->CreateLabel("Account Name", { 255,219,142,255 }, Text_Position::TOP), App->gui->greyrect, SDL_Rect{ 0,0,128,32 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ App->render->camera.w / 2 - 64,App->render->camera.h / 2 +100 }, App->gui->CreateLabel("Account Password", { 255,219,142,255 }, Text_Position::TOP), App->gui->greyrect, SDL_Rect{ 0,0,128,32 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ App->render->camera.w / 2 - 64,App->render->camera.h / 2 +200 }, App->gui->CreateLabel("Login", { 255,219,142,255 }), App->gui->redrect, SDL_Rect{ 0,0,128,32 });

	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ App->render->camera.w - 150,App->render->camera.h / 2 + 180 }, App->gui->CreateLabel("Cinematics", { 255,219,142,255 }), App->gui->redrect, SDL_Rect{ 0,0,128,32 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ App->render->camera.w - 150,App->render->camera.h / 2 + 230 }, App->gui->CreateLabel("Credits", { 255,219,142,255 }), App->gui->redrect, SDL_Rect{ 0,0,128,32 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ App->render->camera.w - 150,App->render->camera.h / 2 + 280 }, App->gui->CreateLabel("Terms of Use", { 255,219,142,255 }), App->gui->redrect, SDL_Rect{ 0,0,128,32 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ App->render->camera.w - 150,App->render->camera.h - 75 }, App->gui->CreateLabel("Quit", { 255,219,142,255 }), App->gui->redrect, SDL_Rect{ 0,0,128,32 });

	App->gui->CreateButton(Button_Type::BUTTON, iPoint{25,App->render->camera.h / 2 + 275 }, App->gui->CreateLabel("Manage Account", { 255,219,142,255 }), App->gui->redrect, SDL_Rect{ 0,0,128,32 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{25,App->render->camera.h / 2 + 325 }, App->gui->CreateLabel("Community Site", { 255,219,142,255 }), App->gui->redrect, SDL_Rect{ 0,0,128,32 });

	App->gui->CreateButton(Button_Type::BUTTON, iPoint{25,App->render->camera.h / 2 + 375 }, App->gui->CreateLabel("Remember Account Name", { 255,219,142,255 },Text_Position::RIGHT), App->gui->tickbox, SDL_Rect{ 2,16,24,24 });

	App->gui->CreateButton(Button_Type::BUTTON, iPoint{0,App->render->camera.h / 2 + 475 }, App->gui->CreateLabel("Version 2.0.12 (6546) (Release)", { 255,219,142,255 }, Text_Position::RIGHT), App->gui->redrect, SDL_Rect{ 0,0,0,0 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ 0,App->render->camera.h / 2 + 500 }, App->gui->CreateLabel("Mar 30 2007", { 255,219,142,255 }, Text_Position::RIGHT), App->gui->redrect, SDL_Rect{ 0,0,0,0 });
	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ App->render->camera.w/2,App->render->camera.h / 2 + 500 }, App->gui->CreateLabel("Copyright 2004-2007 Blizzard Entertainment. All Rights Reserved.", { 255,219,142,255 }), App->gui->redrect, SDL_Rect{ 0,0,0,0 });

	App->gui->CreateButton(Button_Type::BUTTON, iPoint{ App->render->camera.w,App->render->camera.h / 2 + 325 }, App->gui->CreateLabel("WoWps.org TBC", { 0,0,0,255 }, Text_Position::LEFT), App->gui->redrect, SDL_Rect{ 0,0,0,0 });


	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---
	
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

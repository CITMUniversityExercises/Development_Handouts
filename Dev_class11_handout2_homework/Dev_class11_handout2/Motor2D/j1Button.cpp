#include "j1Button.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Gui.h"

j1Button::j1Button(Button_Type type , Text label, iPoint position, SDL_Rect rect)
{
	SDL_Rect temprect = { 485, 829, 328, 103 };

	Data.type = type;
	Data.rect = temprect;
	Data.label = label;
	Data.position = position;
}

j1Button::~j1Button()
{

}

void j1Button::on_press()
{
}

void j1Button::on_hover()
{
}

void j1Button::FixedUpdate()
{
	App->render->Blit(App->gui->GetAtlas(), Data.position.x, Data.position.y, &Data.rect);
}

#include "j1Button.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Fonts.h"

j1Button::j1Button(Button_Type type, iPoint position, Text label, SDL_Texture* tex, SDL_Rect rect)
{
	Data.type = type;
	Data.rect = rect;
	Data.label = label;
	Data.position = position;
	Data.tex = tex;
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
	//App->render->Blit(App->gui->GetAtlas(), Data.position.x, Data.position.y+25, &Data.rect);
	//App->render->Blit(Data.label.tex, Data.position.x+Data.rect.w/2-Data.label.font_Rect.w/2, Data.position.y, &Data.label.font_Rect);

	if(Data.tex)
	App->render->Blit(Data.tex, Data.position.x, Data.position.y, &Data.rect);

	switch (Data.label.location)
	{
		case Text_Position::MIDDLE:
			App->render->Blit(Data.label.tex, Data.position.x + Data.rect.w / 2 - Data.label.font_Rect.w / 2, Data.position.y + Data.label.font_Rect.h / 2, &Data.label.font_Rect);
			break;
		case Text_Position::TOP:
			App->render->Blit(Data.label.tex, Data.position.x + Data.rect.w / 2 - Data.label.font_Rect.w / 2, Data.position.y - Data.label.font_Rect.h, &Data.label.font_Rect);
			break;
		case Text_Position::RIGHT:
			App->render->Blit(Data.label.tex, Data.position.x + Data.rect.w +10 , Data.position.y + Data.label.font_Rect.h/4, &Data.label.font_Rect);
			break;
		case Text_Position::LEFT:
			App->render->Blit(Data.label.tex, Data.position.x - Data.label.font_Rect.w- 25, Data.position.y + Data.label.font_Rect.h / 4, &Data.label.font_Rect);
	}
}

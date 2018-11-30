#include "j1Button.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Fonts.h"

j1Button::j1Button(Button_Type type, iPoint position, Text label, SDL_Texture* tex, SDL_Rect rect)
{
	// --- Initializing variables ---
	Data.type = type;
	Data.rect = rect;
	Data.label = label;
	Data.position = position;
	Data.tex = tex;

	// --- Logic rect, handles interaction ---
	Data.logic_rect = rect;
	Data.logic_rect.x = Data.position.x;
	Data.logic_rect.y = Data.position.y;
	Data.label.logic_rect.x = Data.position.x;
	Data.label.logic_rect.y = Data.position.y;
	

	if (Data.type != Button_Type::LABEL)
	{
		switch (Data.label.location)
		{
		case Text_Position::TOP:
			Data.label.logic_rect.x = Data.position.x + Data.rect.w / 2 - Data.label.font_Rect.w / 2;
			Data.label.logic_rect.y = Data.position.y - Data.label.font_Rect.h;
		case Text_Position::MIDDLE:
			Data.label.logic_rect.x = Data.position.x + Data.rect.w / 2 - Data.label.font_Rect.w / 2;
			Data.label.logic_rect.y = Data.position.y + Data.label.font_Rect.h / 2;
			break;
		case Text_Position::RIGHT:
			Data.label.logic_rect.x = Data.position.x + Data.rect.w + 10;
			Data.label.logic_rect.y = Data.position.y + Data.label.font_Rect.h / 4;
			break;
		case Text_Position::LEFT:
			Data.label.logic_rect.x = Data.position.x - Data.label.font_Rect.w - 25;
			Data.label.logic_rect.y = Data.position.y + Data.label.font_Rect.h / 4;
			break;
		}
	}
}

j1Button::~j1Button()
{

}

void j1Button::FixedUpdate()
{

	if(Data.tex)
	App->render->Blit(Data.tex, Data.position.x, Data.position.y, &Data.rect);

	App->render->Blit(Data.label.tex,Data.label.logic_rect.x,Data.label.logic_rect.y, &Data.label.font_Rect);	
}

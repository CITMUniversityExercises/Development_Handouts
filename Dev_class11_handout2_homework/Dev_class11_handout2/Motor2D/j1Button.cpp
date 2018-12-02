#include "j1Button.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Fonts.h"

j1Button::j1Button(Button_Type type, iPoint position, Text label, SDL_Texture* tex, Buttonrects rect)
{
	// --- Initializing variables ---
	Data.type = type;
	Data.rects = rect;
	Data.label = label;
	Data.position = position;
	Data.tex = tex;

	// --- Logic rect, handles interaction ---
	Data.logic_rect = rect.rect_normal;
	Data.logic_rect.x = Data.position.x;
	Data.logic_rect.y = Data.position.y;
	Data.label.logic_rect.x = Data.position.x;
	Data.label.logic_rect.y = Data.position.y;
	

	if (Data.type != Button_Type::LABEL)
	{
		switch (Data.label.location)
		{
		case Text_Position::TOP:
			PlaceAtTop(Data);
			break;
		case Text_Position::BOTTOM:
			PlaceAtBottom(Data);
			break;
		case Text_Position::MIDDLE:
			PlaceAtMiddle(Data);
			break;
		case Text_Position::RIGHT:
			PlaceAtRight(Data);
			break;
		case Text_Position::LEFT:
			PlaceAtLeft(Data);
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
	App->render->Blit(Data.tex, Data.position.x, Data.position.y, &Data.rects.current_rect);

	App->render->Blit(Data.label.tex,Data.label.logic_rect.x,Data.label.logic_rect.y, &Data.label.font_Rect);	
}

inline void j1Button::PlaceAtTop(ButtonInfo &Data)
{
	Data.label.logic_rect.x = Data.position.x + Data.logic_rect.w / 2 - Data.label.font_Rect.w / 2;
	Data.label.logic_rect.y = Data.position.y - Data.label.font_Rect.h;
}

inline void j1Button::PlaceAtBottom(ButtonInfo &Data)
{
	Data.label.logic_rect.x = Data.position.x + Data.logic_rect.w / 2 - Data.label.font_Rect.w / 2;
	Data.label.logic_rect.y = Data.position.y +Data.logic_rect.h + 10;
}

inline void j1Button::PlaceAtLeft(ButtonInfo &Data)
{
	Data.label.logic_rect.x = Data.position.x - Data.label.font_Rect.w - 25;
	Data.label.logic_rect.y = Data.position.y + Data.label.font_Rect.h / 4;
}

inline void j1Button::PlaceAtRight(ButtonInfo &Data)
{
	Data.label.logic_rect.x = Data.position.x + Data.logic_rect.w + 10;
	Data.label.logic_rect.y = Data.position.y + Data.label.font_Rect.h / 4;
}

inline void j1Button::PlaceAtMiddle(ButtonInfo &Data)
{
	Data.label.logic_rect.x = Data.position.x + Data.logic_rect.w / 2 - Data.label.font_Rect.w / 2;
	Data.label.logic_rect.y = Data.position.y + Data.label.font_Rect.h / 2;
}

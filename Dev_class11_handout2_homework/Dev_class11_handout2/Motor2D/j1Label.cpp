#include "j1Label.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Map.h"

void j1Label::FixedUpdate()
{
	if (this->parent != nullptr)
	{
		switch (Data.Place)
		{
			case Text_Position::NONE:
				this->position.x = parent->position.x + Data.position.x;
				this->position.y = parent->position.y + Data.position.y;
			break;

			case Text_Position::MIDDLE:
				PlaceAtMiddle();
			break;

			case Text_Position::TOP:
				PlaceAtTop();
			break;

			case Text_Position::BOTTOM:
				PlaceAtBottom();
			break;

			case Text_Position::RIGHT:
				PlaceAtRight();
			break;

			case Text_Position::LEFT:
				PlaceAtLeft();
			break;
		}
	}

	this->Data.rects.logic_rect.x = position.x;
	this->Data.rects.logic_rect.y = position.y;

	App->render->Blit(Data.tex, this->position.x, this->position.y, &Data.rects.rect_normal,false);
}

ELEMENTS j1Label::GetType()
{
	return Data.type;
}

Booleans * j1Label::GetBooleans()
{
	return &Data.bools;
}

Buttonrects * j1Label::Getrects()
{
	return &Data.rects;
}

inline void j1Label::PlaceAtTop()
{
	position.x = parent->Getrects()->logic_rect.x + parent->Getrects()->current_rect.w / 2 - Data.rects.rect_normal.w / 2;
	position.y = parent->position.y - Data.rects.rect_normal.h;
}

inline void j1Label::PlaceAtBottom()
{
	position.x = parent->Getrects()->logic_rect.x + parent->Getrects()->current_rect.w / 2 - Data.rects.rect_normal.w / 2;
	position.y = parent->position.y + parent->Getrects()->current_rect.h;
}

inline void j1Label::PlaceAtLeft()
{
	position.x = parent->position.x - Data.rects.rect_normal.w;
	position.y = parent->position.y + parent->Getrects()->current_rect.h / 2 - Data.rects.rect_normal.h / 2;
}

inline void j1Label::PlaceAtRight()
{
	position.x = parent->position.x + parent->Getrects()->current_rect.w;
	position.y = parent->position.y + parent->Getrects()->current_rect.h / 2 - Data.rects.rect_normal.h / 2;
}

inline void j1Label::PlaceAtMiddle()
{
	position.x = parent->Getrects()->logic_rect.x + parent->Getrects()->current_rect.w / 2 - Data.rects.rect_normal.w / 2;
	position.y = parent->position.y + parent->Getrects()->current_rect.h / 2 - Data.rects.rect_normal.h / 2;
}

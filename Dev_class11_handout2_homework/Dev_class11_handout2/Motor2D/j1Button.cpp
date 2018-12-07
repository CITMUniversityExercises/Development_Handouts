#include "j1Button.h"
#include "j1Render.h"
#include "j1App.h"

void j1Button::FixedUpdate()
{
	if (this->parent != nullptr)
	{
		this->position.x = parent->position.x + Data.position.x;
		this->position.y = parent->position.y + Data.position.y;
	}

	this->Data.rects.logic_rect.x = position.x;
	this->Data.rects.logic_rect.y = position.y;

	App->render->Blit(Data.tex, this->position.x, this->position.y, &Data.rects.current_rect,false);
}

ELEMENTS j1Button::GetType()
{
	return Data.type;
}

Buttonrects * j1Button::Getrects()
{
	return &Data.rects;
}

Booleans * j1Button::GetBooleans()
{
	return &Data.bools;
}



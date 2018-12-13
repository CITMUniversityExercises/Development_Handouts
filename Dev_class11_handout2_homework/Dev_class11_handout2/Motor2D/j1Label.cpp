#include "j1Label.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Textures.h"

void j1Label::FixedUpdate()
{
	
		if (!this->GetBooleans()->dragging)
		{
			if (parent->GetType() != ELEMENTS::SLIDER || start==0)
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

			
		}
		else
		{
			if (parent->GetType() != ELEMENTS::SLIDER)
			{
				Data.position.x = this->position.x - parent->position.x;
				Data.position.y = this->position.y - parent->position.y;
			}
			
		}
	

	this->Data.rects.logic_rect.x = position.x;
	this->Data.rects.logic_rect.y = position.y;


	if (start == 0 && parent->GetType() == ELEMENTS::SLIDER)
	{
		blittext = this->Data.rects.logic_rect;
		start = 1;
	}

	/*iPoint blit_pos;
	int scale = App->win->GetScale();
	blit_pos.x = (Data.position.x - App->render->camera.x) / scale;
	blit_pos.y = (Data.position.y - App->render->camera.y) / scale;*/

	App->render->SetViewPort(blittext);

	//SDL_RenderSetClipRect(App->render->renderer, &Data.rects.logic_rect);

	App->render->Blit(Data.tex,blittext.x - Data.rects.logic_rect.x, blittext.y - Data.rects.logic_rect.y);

	//SDL_RenderSetClipRect(App->render->renderer, NULL);
	App->render->ResetViewPort();
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

textbox * j1Label::GetTexts()
{
	return &Data.texts;
}

SDL_Texture * j1Label::GetTexture()
{
	return Data.tex;
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

void j1Label::ShapeLabel(const char * text)
{
	App->tex->UnLoad((SDL_Texture*)this->Data.tex);
	this->Data.tex = App->font->Print(text, this->Data.color, App->font->default);
	App->font->CalcSize(text, this->Data.rects.rect_normal.w, this->Data.rects.rect_normal.h, App->font->default);
	this->Data.rects.logic_rect = { this->position.x , this->position.y , this->Data.rects.rect_normal.w , this->Data.rects.rect_normal.h };
	this->Data.texts.current_text = text;
}

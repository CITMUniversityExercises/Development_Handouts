#ifndef __j1UI_Element_H__
#define __j1UI_Element_H__

#include "SDL/include/SDL.h"
#include "p2List.h"
#include "p2Point.h"

enum class ELEMENTS
{
	PANEL,
	BUTTON,
	LABEL,

	NONE
};

struct Booleans
{
	bool hovering = false;
	bool clicking = false;
};

struct Buttonrects;

class j1UI_Element
{
friend class j1Gui;

public:
	j1UI_Element();

	~j1UI_Element();

	virtual void FixedUpdate(){}

	virtual ELEMENTS GetType();

	virtual Buttonrects* Getrects();

	virtual Booleans * GetBooleans();
	

public:
	iPoint position;

protected:
	p2List <j1UI_Element*> children;
	j1UI_Element* parent = nullptr;
};


#endif // __j1UI_Element_H__


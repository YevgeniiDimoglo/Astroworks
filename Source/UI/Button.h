#pragma once

#include "UI.h"
#include "../Graphics/Sprite.h"

class Button
{
public:
	Button() {}
	~Button() {}
private:
	Sprite buttonNormal;
	Sprite buttonHover;
	Sprite buttonClicked;
	Sprite buttonDisabled;
};
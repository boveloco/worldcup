#include "Keyboard.h"
#include "ofMain.h"

Keyboard *Keyboard::INSTANCE = new Keyboard();

Keyboard::Keyboard()
{}

Keyboard *Keyboard::GetInstance()
{
	return INSTANCE;
}

bool Keyboard::IsPressed(int key)
{
	return pressedKeys[key];
}

bool Keyboard::IsDown(int key)
{
	return downKeys[key];
}

bool Keyboard::IsRelease(int key)
{
	return releasedKeys[key];
}

void Keyboard::Set(int key, bool action)
{
	if (action)
	{
		downKeys[tolower(key)] = action;
		pressedKeys[tolower(key)] = action;
	}
	else
	{
		releasedKeys[tolower(key)] = true;
		downKeys.erase(tolower(key));
	}
}

void Keyboard::Update()
{
	pressedKeys.clear();
	releasedKeys.clear();
}
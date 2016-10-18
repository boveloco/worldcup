#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <unordered_map>

class Keyboard
{
private:
	std::unordered_map<int, bool> pressedKeys;
	std::unordered_map<int, bool> downKeys;
	std::unordered_map<int, bool> releasedKeys;
	
	static Keyboard *INSTANCE;

	Keyboard();
public:

	static Keyboard *GetInstance();
	bool IsPressed(int key);
	bool IsDown(int key);
	bool IsRelease(int key);

	void Set(int key, bool action);
	void Update();
};

#endif //__KEYBOARD_H__

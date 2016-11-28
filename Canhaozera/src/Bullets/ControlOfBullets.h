#ifndef	__CONTROL_OF_BULLETS_H__
#define	__CONTROL_OF_BULLETS_H__

#include <vector>

class Bullet;

class ControlOfBullets
{
private:
public:
	ControlOfBullets();
	static Bullet *bullet;

	~ControlOfBullets();

	static void Update();
	static void Draw();
};

#endif//__CONTROL_OF_BULLETS_H__

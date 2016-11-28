#include "ControlOfBullets.h"
#include "Bullet.h"

Bullet *ControlOfBullets::bullet = nullptr;

ControlOfBullets::ControlOfBullets()
{
}

ControlOfBullets::~ControlOfBullets()
{
	if (bullet)
	{
		delete bullet;
		bullet = nullptr;
	}
}

void ControlOfBullets::Update()
{
	if (bullet)
	{
		bullet->Update();
	}
}

void ControlOfBullets::Draw()
{
	if(bullet)
		bullet->Draw();
}

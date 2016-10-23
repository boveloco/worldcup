#pragma once
#include <vector>
#include "Bullet.h"

class Cannon
{
public:
	Cannon();
	
	//adiciona um no bullets
	void instantiate(Bullet* b);

	//desenha todos
	void Draw();

	//vetor bullets
	std::vector<Bullet*> _bullets;
private:
	
};
#include "Cannon.h"
#include "../MathVinicius/AffineTransform.h"

Cannon::Cannon(){
	this->_bullets = std::vector<Bullet*>();
}

void Cannon::instantiate(Bullet *b) {
	this->_bullets.push_back(b);
}

void Cannon::Draw() {
	if (_bullets.size() == NULL)
		return;

	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->Draw();
	}
}


#include "Bullet.h"
#include "../MathVinicius/ofDraw.h" 
Bullet::Bullet(math::Vector2D pos) {
	this->_sprite.load("img/circle.png");
	this->m_transform = new Transform(pos);
}

void Bullet::Draw() {
	if (&this->m_transform->position.x == nullptr || &this->m_transform->position.y == nullptr) {
		throw nullptr;
		return;
	}
	math::lh::draw(m_transform->tMatrix, _sprite);
}

void Bullet::Update() {

	// faz todas as multiplicações de matrix
	m_transform->Update();

	m_transform->tMatrix *= *world;
}
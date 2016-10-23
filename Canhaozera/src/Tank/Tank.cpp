#include "Tank.h"
#include "../MathVinicius/ofDraw.h"
#include "../Transform.h"

Tank::Tank(char* src, math::Matrix3 &world) {
	this->_cannon = new Cannon();
	this->_sprite.load(src);
	this->Setup(&world);
}
Tank::Tank(char* src, math::Vector2D &pos, math::Matrix3 &world) {
	this->_cannon = new Cannon();
	this->_sprite.load(src);
	this->Setup(&world, pos);
}

void Tank::setPos(math::Vector2D &pos) {

	m_transform->position = pos;

}
math::Vector2D Tank::getPos() {
	return m_transform->position;
}

void Tank::Draw() {
	math::lh::draw(m_transform->tMatrix, _sprite);
	if(_cannon != nullptr)
		this->_cannon->Draw();
}

void Tank::Update() {

	// faz todas as multiplicações de matrix
	m_transform->Update();

	m_transform->tMatrix *= *world;
}

Tank::~Tank() {
	delete _cannon;
	_cannon = nullptr;
}
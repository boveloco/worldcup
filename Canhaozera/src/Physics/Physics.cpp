#include "Physics.h"
#include "../Body.h"
#include "../ofMain.h"

Physics::Physics() {}

void Physics::update() {
	for each (Body b in _objects)
	{
		b.momentum += (_wind / b.getMass() + _gravity) * ofGetLastFrameTime();
	}
}

void Physics::setup() {
	this->_gravity = math::Vector2D(0,-10);
	this->_wind = math::Vector2D(0, 0);
}

math::Vector2D Physics::getGravity() const {
	return this->_gravity;
}

math::Vector2D Physics::getWind() const {
	return this->_wind;
}
void Physics::setGravity(math::Vector2D g) {
	_gravity = g;
}
void Physics::setWind(math::Vector2D w) {
	_wind = w;
}

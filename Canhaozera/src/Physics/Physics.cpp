#include "Physics.h"
#include "../Body.h"
#include "../ofMain.h"
#include "../Tank/Tank.h"

std::vector<Body *> Physics::_objects;

Physics::Physics() {}

Physics::~Physics() {}

void Physics::update() {
	for each (Body *b in _objects)
	{
		if (b->getStatic())
			continue;
		b->momentum += (_wind / b->GetMass() + _gravity) * ofGetLastFrameTime();
	}
}

void Physics::setup() {
	this->_gravity = math::Vector2D(0,10);
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

bool Physics::BoxCollisionCheck(math::AABB &p_rect1, math::AABB &p_rect2)
{
	return p_rect1.intersects(p_rect2);
}

bool Physics::CircleCollisionCheck(math::BoundingCircle &p_circle1, math::BoundingCircle &p_circle2)
{
	return p_circle1.intersects(p_circle2);
}

bool Physics::CircleBoxCollisionCheck(math::AABB &p_rect, math::BoundingCircle &p_circle)
{
	return p_rect.intersects(p_circle);
}

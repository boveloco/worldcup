#pragma once

#include "MathVinicius\AffineTransform.h"
#include "MathVinicius\collisions.h"

class Body;
class Missile;
class Asteroid;

class Steering
{
public:
	static math::Vector2D Flee(math::BoundingCircle &asteroid, math::BoundingCircle &ship, float speed);
	static math::Vector2D Pursuit(Missile &missile, Asteroid &asteroid);
	static math::Vector2D Seek(math::Vector2D &pos1, math::Vector2D &pos2, float speed);
};

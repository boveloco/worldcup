#pragma once

#include "Body.h"
#include "MathVinicius\AffineTransform.h"
#include "MathVinicius\collisions.h"
#include "ofMain.h"

class Asteroid;
class Ship;

class Rot : public Body
{
private:
	ofImage image;
	const float SPEED;
	math::BoundingCircle shape;
	float index;
	Asteroid *asteroid;

	bool getpos;
public:
	bool move;
	Rot(char *src, math::Matrix3 *world, math::Vector2D &pos);
	void Update();
	void Draw();

	math::BoundingCircle GetShape() const { return shape; }
	float GetSpeed() const { return SPEED; }
	void SetForce(math::Vector2D &force);
	void SetAsteroid(Asteroid *asteroid);
	void SetDirection(math::Vector2D &dir);
};

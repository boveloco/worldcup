#ifndef __BULLET_H__
#define __BULLET_H__

#include "Body.h"
#include "ofMain.h"
#include "MathVinicius\collisions.h"

class Bullet : public Body
{
private:
	ofImage image;
	math::Vector2D dir;
	float impactForce;
	const float SPEED;

	math::BoundingBox rect;

public:
	Bullet(char *src, math::Vector2D spawn, math::Vector2D dir, float angle);
	void Update();
	void Draw();

	math::BoundingBox GetShape() const;
};

#endif //__BULLET_H__

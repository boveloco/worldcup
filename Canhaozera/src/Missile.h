#ifndef	 __MISSILE_H__
#define	 __MISSILE_H__

#include "MathVinicius\AffineTransform.h"
#include "MathVinicius\collisions.h"
#include "ofMain.h"
#include "Body.h"

class Asteroid;

class Missile : public Body
{
private:
	ofImage image;
	const float SPEED;
	float angle;
	math::BoundingBox rect;
	Asteroid *asteroid;
public:
	math::Vector2D dir;
	Missile(char *src, math::Vector2D spawn, math::Vector2D &dir, float angle, Asteroid *asteroid);
	void Update();
	void Draw();

	math::BoundingBox GetShape() const;
	float GetSpeed() const { return SPEED; }
	void SetForce(math::Vector2D &force, float angle);
	void SetAsteroid(Asteroid *asteroid);
};

#endif //__MISSILE_H__

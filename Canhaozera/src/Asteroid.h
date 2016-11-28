#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "Body.h"
#include "MathVinicius/Vector2D.h"
#include "MathVinicius/collisions.h"
#include "ofMain.h"

class Asteroid : public Body
{
private:
	ofImage image;
	const float SPEED;


	math::BoundingCircle circle;

	bool alive = true;
public:
	math::Vector2D dir;
	Asteroid(char *src, math::Matrix3 *world, math::Vector2D &pos, math::Vector2D &dir, float mass, float speed);
	void Update();
	void Draw();
	void SetAlive(bool p_alive) { alive = p_alive; }
	math::BoundingCircle GetShape() const;
	bool GetAlive() const { return alive; }
	void SetForce(math::Vector2D force);
	float GetSpeed() const { return SPEED; }
};

#endif //__ASTEROID_H__

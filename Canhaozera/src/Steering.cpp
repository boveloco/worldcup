#include "Steering.h"
#include "Asteroid.h"
#include "Shield.h"
#include "Missile.h"
#include "Transform.h"

math::Vector2D Steering::Flee(math::BoundingCircle &asteroid, math::BoundingCircle &ship, float speed)
{
	if ((ship.position - asteroid.position).size() > ship.radius)
	{
		return math::Vector2D();
	}

	math::Vector2D desiredVelocity = asteroid.position - ship.position;
	desiredVelocity.normalize();
	desiredVelocity *= speed;

	return desiredVelocity;
}

math::Vector2D Steering::Pursuit(Missile &missile, Asteroid &asteroid)
{
	math::Vector2D toEvader = asteroid.GetShape().position - missile.GetShape().position;
	double relativeDir = missile.dir.dot(asteroid.dir);

	if (toEvader.dot(asteroid.dir) > 0 &&
		relativeDir < -0.95)
	{
		return Seek(missile.GetShape().position, asteroid.GetShape().position, missile.GetSpeed());
	}

	double lookAheadTime = toEvader.size() / (asteroid.GetSpeed() + missile.GetSpeed());
	return Seek(missile.GetShape().position,
				asteroid.GetShape().position + 
				(asteroid.dir * asteroid.GetSpeed() * ofGetLastFrameTime()),
				missile.GetSpeed());
}

math::Vector2D Steering::Seek(math::Vector2D &pos1, math::Vector2D &pos2, float speed)
{
	math::Vector2D desiredVelocity;
	desiredVelocity = pos2 - pos1;
	desiredVelocity.normalize();

	return desiredVelocity * speed;
}

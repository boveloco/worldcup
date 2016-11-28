#ifndef __SHIP_H__
#define __SHIP_H__

#include "Body.h"
#include "MathVinicius/Vector2D.h"
#include "MathVinicius/collisions.h"
#include "ofMain.h"
#include <vector>

class Star;
class Bullet;
class Shield;
class Missile;
class Asteroid;
class Rot;

class Ship : public Body
{
private:
	//math::Vector2D momentum;
	ofImage image;

	ofImage prop;
	math::Vector2D pos_prop;
	bool move;
	float index;

	math::Vector2D spawn;

	const float ANGULAR_SPEED = 30.0f;
	const float SPEED = 50.0f;

	Shield *shield;
	bool  isProtected;
	float ctrlShield;
	float ctrlrot;
	math::BoundingBox rect;

	bool alive;
	bool add;

	void Rotate();
	void Move();
	void ToShoot();
	math::Vector2D CalculateForces();
	void SetLimit();
	void Press();
public:
	std::vector<Bullet*> bullet;
	std::vector<Asteroid*> asteroids;
	std::vector<Missile*> missiles;
	std::vector<Rot*> r;

	bool toThrowMissile;

	Ship(char *src, math::Matrix3 *world, math::Vector2D &pos, float mass);
	~Ship();
	void CalculateForceField(Star &star, float attractionForce = 1.f);
	void Update();
	void Draw();

	math::BoundingBox GetShape() const;
	void SetAlive(bool p_alive);
	bool GetAlive() const;
	std::vector<Bullet*> GetBullets() const;

	Shield *GetShield() const { return shield; }
	bool IsProtected() const { return isProtected; }
};

#endif //__SHIP_H__

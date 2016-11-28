#ifndef __CANNON_H__
#define __CANNON_H__

#include "../MathVinicius/AffineTransform.h"
#include "ofMain.h"
#include "../Body.h"

class Cannon : public Body
{
public:
	Cannon(char* src, math::Vector2D &pos, math::Matrix3 &world);
	Cannon(char* src, math::Matrix3 &world);
	~Cannon();

	void Update();
	void Draw();

	void SetPos(math::Vector2D &pos);

	math::Vector2D GetPos() const;

	void Rotate(float angle);
	void ToShoot();
private:
	ofImage _sprite;
};

#endif __CANNON_H__//
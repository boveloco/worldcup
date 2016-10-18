#pragma once

#include "../Body.h"
#include "../ofMain.h"
#include "../MathVinicius/AffineTransform.h"
class Cannon;

class Tank : public Body
{
public:
	Tank(char* src, math::Matrix3 &world);
	Tank(char* src, math::Vector2D &pos, math::Matrix3 &world);
	~Tank();
	void Draw();
	void Update();
	
	void setPos(math::Vector2D &pos);

	math::Vector2D getPos();

private:
	int _life;
	Cannon* _cannon;
	ofImage _sprite;
};
#pragma once

#include "../Body.h"
#include "../ofMain.h"
#include "../MathVinicius/AffineTransform.h"
#include "../MathVinicius/AABB.h"
#include <string>
#include <vector>

class Cannon;
class Bullet;

struct LifeBar
{
	ofImage bar1;
	ofImage bar2;

	math::Matrix3 mBar1;
	math::Matrix3 mBar2;

	math::Vector2D vBar1;
	math::Vector2D vBar2;
};

class Tank : public Body
{
private:
	Cannon* m_cannon;
	ofImage m_sprite;
	std::string m_tag;
	float m_life;

	LifeBar m_lifeBar;

	math::AABB *m_rect;

public:
	bool shoot = false;
	Tank(char* src, math::Matrix3 &world, char *tag);
	Tank(char* src, math::Vector2D &pos, math::Matrix3 &world, char *tag);
	~Tank();
	void Draw();
	void Update();
	
	void ToShoot();
	void ToRotate();
	void setPos(math::Vector2D &pos);
	math::Vector2D getPos();

	std::string getTag() const;

	void SetLife(float life);
	float GetLife() const;

	math::AABB *GetShape() const;
};
#pragma once
#include "ofMain.h"
#include "../Body.h"
#include "../MathVinicius/AffineTransform.h"


class Bullet : public Body
{
public:
	

	Bullet(math::Vector2D pos);

	math::Vector2D getPosition() {
		return this->m_transform->position;
	}

	void setPosition(math::Vector2D pos) {
		this->m_transform->position = pos;
	}

	void Draw();
	void Update();
private:
	Body* body;
	ofImage _sprite;
};
#pragma once

#include <vector>
#include "../MathVinicius/AffineTransform.h"

class Body;

class Physics
{
public:
	Physics();
	~Physics();
	
	void setup();
	void update();

	math::Vector2D getGravity() const;
	math::Vector2D getWind() const;
	void setGravity(math::Vector2D g);
	void setWind(math::Vector2D w);
	std::vector<Body> _objects;

private:
	math::Vector2D _gravity;
	math::Vector2D _wind;
};

#pragma once

#include <vector>
#include "../MathVinicius/AffineTransform.h"
#include "../MathVinicius/AABB.h"
#include "../MathVinicius/BoundingCircle.h"

class Body;

class Physics
{
private:
	math::Vector2D _gravity;
	math::Vector2D _wind;

public:
	static std::vector<Body *> _objects;
	Physics();
	~Physics();
	
	void setup();
	void update();

	math::Vector2D getGravity() const;
	math::Vector2D getWind() const;
	void setGravity(math::Vector2D g); 
	void setWind(math::Vector2D w);

	static bool BoxCollisionCheck(math::AABB &p_rect1, math::AABB &p_rect2);
	static bool CircleCollisionCheck(math::BoundingCircle &p_circle1, math::BoundingCircle &p_circle2);
	static bool CircleBoxCollisionCheck(math::AABB &p_rect, math::BoundingCircle &p_circle);
};

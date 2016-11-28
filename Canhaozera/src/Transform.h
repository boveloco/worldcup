#ifndef __TRANSFORM_H__
#define  __TRANSFORM_H__

#include "MathVinicius/Vector2D.h"
#include "MathVinicius/Matrix3.h"

class Transform
{
public:
	math::Vector2D position;
	math::Vector2D scale;
	float angle;

	math::Matrix3 tMatrix;
	Transform(math::Vector2D pos = math::Vector2D(0,0));

	void Update();
};

#endif // __TRANSFORM_H__

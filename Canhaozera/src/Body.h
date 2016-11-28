#ifndef __BODY_H__
#define __BODY_H__

#include "MathVinicius/Matrix3.h"
#include "MathVinicius/Vector2D.h"
#include "MathVinicius\collisions.h"

class Transform;

class Body
{
protected:
	Transform *m_transform;
	math::Vector2D momentum;
	math::Matrix3 *world;
	float mass;
public:
	Body();
	~Body();
	float GatMass() const;
	Transform *GetTransform() const;
	void Setup(math::Matrix3 *world, math::Vector2D &pos, float mass = 1.f);
	void Setup(math::Matrix3 *world, float x, float y, float mass = 1.f);
	void SetMomentum(math::Vector2D _momentum);
};

#endif // __BODY_H__

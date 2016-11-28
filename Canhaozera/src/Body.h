#ifndef __BODY_H__
#define __BODY_H__

#include "MathVinicius/Matrix3.h"
#include "MathVinicius/Vector2D.h"

class Transform;

class Body
{
public:
	math::Vector2D momentum;
protected:
	Transform *m_transform;
	math::Matrix3 *world;
	float mass;
	bool _static;

public:
	Body();
	~Body();
	float GetMass() const;
	bool getStatic() const;
	Transform *GetTransform() const;
	void Setup(math::Matrix3 *world, math::Vector2D &pos, float mass = 1.f, bool _static = false);
	void Setup(math::Matrix3 *world, float x, float y, float mass = 1.f, bool _static = false);
	void Setup(math::Matrix3 *world);
	void AddForce(math::Vector2D &dir, float mulForce = 1.f);
};

#endif // __BODY_H__

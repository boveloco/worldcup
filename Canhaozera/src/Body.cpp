#include "Body.h"
#include "Transform.h"
#include "Physics/Physics.h"
#include "ofMain.h"

Body::Body() :
	m_transform(nullptr),
	world(nullptr),
	mass(0.f)
{}

Body::~Body()
{
	if (m_transform)
	{
		delete m_transform;
		m_transform = nullptr;
	}
}

float Body::GetMass() const
{
	return mass;
}

bool Body::getStatic() const
{
	return _static;
}

Transform *Body::GetTransform() const
{
	return m_transform;
}

void Body::Setup(math::Matrix3 *world, math::Vector2D &pos, float mass, bool _static)
{
	this->m_transform = new Transform(pos);
	this->world = world;

	this->mass = mass;

	this->_static = _static;

	Physics::_objects.push_back(this);
}

void Body::Setup(math::Matrix3 *world, float x, float y, float mass, bool _static)
{
	Setup(world, math::Vector2D(x, y), mass, _static);
}

void Body::Setup(math::Matrix3 *world) 
{
	this->Setup(world, math::Vector2D(0, 0));
}

void Body::AddForce(math::Vector2D &dir, float mulForce)
{
	momentum += (dir / mass) * mulForce * ofGetLastFrameTime();
}

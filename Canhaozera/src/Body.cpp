#include "Body.h"
#include "Transform.h"

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

float Body::getMass() const
{
	return mass;
}

Transform *Body::GetTransform() const
{
	return m_transform;
}

void Body::Setup(math::Matrix3 *world, math::Vector2D &pos, float mass)
{
	this->m_transform = new Transform(pos);
	this->world = world;

	this->mass = mass;
}

void Body::Setup(math::Matrix3 *world, float x, float y, float mass)
{
	Setup(world, math::Vector2D(x, y), mass);
}
void Body::Setup(math::Matrix3 *world) {
	this->Setup(world, math::Vector2D(0, 0));
}

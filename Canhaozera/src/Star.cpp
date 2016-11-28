#include "Star.h"
#include "MathVinicius\ofDraw.h"
#include "Transform.h"
#include "Camera.h"

Star::Star(char *src, float radius, float attractionForce) :
	  radius(radius), attractionForce(attractionForce)
{
	image.load(src);
	circle = math::BoundingCircle(0, 0, image.getHeight() / 2);
}

float Star::GetRadius() const
{
	return radius;
}

float Star::GetAttractionForce() const
{
	return attractionForce;
}

void Star::Update()
{
	m_transform->Update();
	m_transform->tMatrix *= inverse(Camera::GetTransform()->tMatrix) * *world;

	math::Vector2D pos = math::lh::transform(m_transform->tMatrix, math::Vector2D());
	circle.position.set(pos.x, pos.y);
}

void Star::Draw()
{
	math::lh::draw(m_transform->tMatrix, image);
	/*ofDrawLine(circle.position.x, circle.position.y, circle.position.x + circle.radius, circle.position.y);*/
}

math::BoundingCircle Star::GetShape() const
{
	return circle;
}

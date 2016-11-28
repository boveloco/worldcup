#include "Asteroid.h"
#include "Transform.h"
#include "MathVinicius\ofDraw.h"
#include "Camera.h"

using namespace math;

Asteroid::Asteroid(char *src, math::Matrix3 *world, math::Vector2D &pos, math::Vector2D &dir, float mass, float speed) :
		  dir(dir), SPEED(speed)
{
	image.load(src);
	Setup(world, pos, mass);

	momentum += dir.normalize() * SPEED;
	circle = math::BoundingCircle(0, 0, image.getHeight() / 2);
}

void Asteroid::Update()
{
	m_transform->position += momentum * ofGetLastFrameTime();

	m_transform->Update();
	m_transform->tMatrix *= inverse(Camera::GetTransform()->tMatrix) * *world;

	math::Vector2D pos = math::lh::transform(m_transform->tMatrix, math::Vector2D());
	circle.position.set(pos.x, pos.y);
}

void Asteroid::Draw()
{
	//ofDrawLine(circle.position.x, circle.position.y, circle.position.x + circle.radius, circle.position.y);
	lh::draw(m_transform->tMatrix, image);
}

math::BoundingCircle Asteroid::GetShape() const
{
	return circle;
}

void Asteroid::SetForce(math::Vector2D force)
{
	momentum += force;
}

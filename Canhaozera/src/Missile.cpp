#include "Missile.h"
#include "MathVinicius\ofDraw.h"
#include "Transform.h"
#include "Steering.h"
#include "Asteroid.h"

Missile::Missile(char *src, math::Vector2D spawn, math::Vector2D &dir, float angle, Asteroid *asteroid) :
		 SPEED(600), angle(angle), asteroid(asteroid), dir(dir)
{
	image.load(src);
	Setup(&math::Matrix3::newIdentity(), spawn);
	m_transform->angle = angle;

	rect.position.set(0, 0);
	rect.size.set(image.getWidth(), image.getHeight());
}

void Missile::Update()
{
	if (asteroid)
	{
		math::Vector2D aux = asteroid->GetShape().position - rect.position;
		float _angle = math::toDegrees(atan2(aux.y, aux.x)) + 90;
		SetForce(Steering::Pursuit(*this, *asteroid), _angle);
	}
	/*if (m_transform->angle < angle)
	{
		m_transform->angle += 45.f * ofGetLastFrameTime();
	}
	else
	{
		m_transform->angle -= 45.f * ofGetLastFrameTime();
	}*/

	m_transform->position += momentum * ofGetLastFrameTime();
	m_transform->Update();

	auto pos = math::lh::transform(m_transform->tMatrix, math::Vector2D());
	rect.position.set(pos - (rect.size / 2));
}

void Missile::Draw()
{
	math::lh::draw(m_transform->tMatrix, image);
}

math::BoundingBox Missile::GetShape() const
{
	return rect;
}

void Missile::SetForce(math::Vector2D &force, float angle)
{
	this->GetTransform()->angle = angle;
	momentum += force * ofGetLastFrameTime();
}

void Missile::SetAsteroid(Asteroid *asteroid)
{
	this->asteroid = asteroid;
}

#include "Rot.h"
#include "MathVinicius\ofDraw.h"
#include "Asteroid.h"
#include "Transform.h"
#include "Steering.h"
#include "Ship.h"
#include "Shield.h"

Rot::Rot(char *src, math::Matrix3 *world, math::Vector2D &pos) :
	asteroid(nullptr), SPEED(500), index(0.f), move(false), getpos(false)
{
	image.load(src);
	Setup(world, pos);

	shape = math::BoundingCircle(0, 0, 32);
}

void Rot::Update()
{
	if (!move)
	{
		m_transform->angle += 30 * ofGetLastFrameTime();

		m_transform->tMatrix = math::lh::newAffineTranslation(m_transform->position) *
							   math::lh::newAffineRotation(math::toRadians(m_transform->angle)) *
							   math::lh::newAffineScale(m_transform->scale.x, m_transform->scale.y);
		m_transform->tMatrix *= *world;
	}
	else
	{
		if (!getpos)
		{
			auto pos = math::lh::transform(m_transform->tMatrix, math::Vector2D());
			m_transform->position = pos;
			getpos = true;
		}
		m_transform->position += momentum * ofGetLastFrameTime();
		m_transform->Update();
	}

	auto pos = math::lh::transform(m_transform->tMatrix, math::Vector2D());
	shape.position.set(pos.x, pos.y);

	index = (index > 16.0f) ? 0.0f : index + 8.0f * ofGetLastFrameTime();
}

void Rot::Draw()
{
	math::lh::draw(m_transform->tMatrix, image, math::Vector2D(32, 32), index);
}

void Rot::SetForce(math::Vector2D &force)
{
	momentum += force;
}

void Rot::SetAsteroid(Asteroid *asteroid)
{
	this->asteroid = asteroid;
}

void Rot::SetDirection(math::Vector2D &asteroid)
{
	SetForce(Steering::Seek(shape.position, asteroid, SPEED));
}

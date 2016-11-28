#include "Cannon.h"
#include "../Transform.h"
#include "../MathVinicius/ofDraw.h"
#include "../Camera.h"

Cannon::Cannon(char *src, math::Vector2D &pos, math::Matrix3 &world)
{
	_sprite.load(src);
	_sprite.setAnchorPoint(-_sprite.getWidth() / 2, _sprite.getHeight()/2);
	/*math::Vector2D tmp = pos + math::Vector2D(_sprite.getWidth()/2 - 10, -_sprite.getHeight()/2);*/
	Setup(&world, pos, 1.f, true);
}

Cannon::Cannon(char *src, math::Matrix3 &world)
{
	_sprite.load(src);
	_sprite.setAnchorPoint(-_sprite.getWidth() / 2, 0);
	math::Vector2D pos = math::Vector2D(_sprite.getWidth() / 2 - 10, -_sprite.getHeight() / 2);
	Setup(&world, pos, 1.f, true);
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	m_transform->Update();
	m_transform->tMatrix *= *world;
}

void Cannon::Draw()
{
	auto mat = m_transform->tMatrix * math::inverse(Camera::GetTransform()->tMatrix);
	math::lh::draw(mat, _sprite);
}

void Cannon::SetPos(math::Vector2D &pos)
{
	m_transform->position = pos;
}

math::Vector2D Cannon::GetPos() const
{
	return m_transform->position;
}

void Cannon::Rotate(float angle)
{
	m_transform->angle += angle;

	m_transform->angle = (m_transform->angle > 45) ? 45 :
						 (m_transform->angle < -20) ? -20 :
						 m_transform->angle;
}

void Cannon::ToShoot()
{
}

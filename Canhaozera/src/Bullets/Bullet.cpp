#include "Bullet.h"
#include "../Transform.h"
#include "../MathVinicius/ofDraw.h"
#include "../Camera.h"


Bullet::Bullet(char *src, math::Vector2D &pos, math::Vector2D &dir,
			   float angle, float mass, float speed, Dir dirMove) : 
	alive(true), dir(dirMove)
{
	m_sprite.load(src);
	Setup(world, pos, mass, false);

	m_rect = new math::AABB(0, 0, m_sprite.getWidth(), m_sprite.getHeight());
	m_frame = 0;
	m_frames.push_back(1);
	function<bool(ofVec4f)> isColorKey = [](ofVec4f color) -> bool { return color.y == 255; };
	m_mask = new Bitmask(m_sprite, *m_rect, &m_rect->size, &m_frames, &m_frame, isColorKey);

	if (dirMove == LEFT)
	{
		m_sprite.rotate90(90);
	}
	AddForce(dir * speed, 2.f);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_transform->position += momentum * ofGetLastFrameTime();
	m_transform->Update();
	//m_transform->tMatrix *= math::inverse(Camera::GetTransform()->tMatrix);

	auto pos = math::lh::transform(m_transform->tMatrix * math::inverse(Camera::GetTransform()->tMatrix), math::Vector2D());
	m_rect->position.set(pos - (m_rect->size / 2));
}

void Bullet::Draw()
{
	auto mat =  math::inverse(Camera::GetTransform()->tMatrix) * m_transform->tMatrix ;
	math::lh::draw(mat, m_sprite);
}

math::Vector2D Bullet::GetPos() const
{
	return m_transform->position;
}

void Bullet::SetPos(math::Vector2D pos)
{
	m_transform->position = pos;
}

bool Bullet::GetAlive() const
{
	return alive;
}

void Bullet::SetAlive(bool alive)
{
	this->alive = alive;
}

Dir Bullet::GetDir() const
{
	return dir;
}

math::AABB *Bullet::GetShape() const
{
	return m_rect;
}

Bitmask *Bullet::GetMask() const
{
	return m_mask;
}

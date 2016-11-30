#include "Explosion.h"
#include "../Transform.h"
#include "../MathVinicius/ofDraw.h"
#include "../Camera.h"

Explosion::Explosion(char *p_src, math::Vector2D &p_position)
{
	m_sprite.load(p_src);

	m_transform = new Transform(p_position);

	m_rect = new math::AABB(0, 0, 128, 128);
	m_frame = 0;

	for (int i = 0; i < 40; i++)
		m_frames.push_back(i);

	function<bool(ofVec4f)> isColorKey = [](ofVec4f color)->bool { return color.y == 255; };
	m_mask = new Bitmask(m_sprite, *m_rect, &m_rect->size, &m_frames, &m_frame, isColorKey);
	m_time = 0;
	m_isLive = false;
}

Explosion::~Explosion()
{
	delete m_mask;
	m_mask = nullptr;
	delete m_rect;
	m_rect = nullptr;
}

math::AABB *Explosion::GetShape() const
{
	return m_rect;
}

Bitmask *Explosion::GetMask() const
{
	return m_mask;
}

bool Explosion::IsLive() const
{
	return m_isLive;
}

void Explosion::SetIslive(bool p_isLive)
{
	m_isLive = p_isLive;
}

unsigned int Explosion::GetFrame() const
{
	return m_frame;
}

void Explosion::Reset(math::Vector2D & p_position, bool p_isLive)
{
	m_transform->position = p_position;
	m_isLive = p_isLive;
}

void Explosion::Update()
{
	if (m_isLive)
	{
		m_time += 20.0f * ofGetLastFrameTime();

		if (m_time > 1.0f)
		{
			m_frame++;

			if (m_frame > 40)
			{
				m_frame = 0;
				m_isLive = false;
			}
			
			m_time = 0;
		}

		m_transform->Update();
		auto pos = math::lh::transform(m_transform->tMatrix * math::inverse(Camera::GetTransform()->tMatrix), math::Vector2D());
		m_rect->position.set(pos - (m_rect->size / 2));
	}
}

void Explosion::Draw()
{
	if (m_isLive)
	{
		auto mat = math::inverse(Camera::GetTransform()->tMatrix) * m_transform->tMatrix;
		math::lh::draw(mat, m_sprite, math::Vector2D(128, 128), m_frame);
	}
}

#include "Ground.h"
#include "../Transform.h"
#include "../MathVinicius/ofDraw.h"
#include "../Camera.h"

Ground::Ground(char *src, math::Vector2D &pos, math::Matrix3 *world) :
	m_transform(new Transform(pos)), m_world(world)
{
	m_sprite.load(src);
	m_rect = new math::AABB(0, 0, m_sprite.getWidth(), m_sprite.getHeight());
	m_frame = 0;
	m_frames.push_back(0);
	function<bool(ofVec4f)> isColorKey = [](ofVec4f color) -> bool { return color.x == 0 && color.y == 0 && color.z == 0; };
	m_mask = new Bitmask(m_sprite, *m_rect, &m_rect->size, &m_frames, &m_frame, isColorKey);
}

Ground::~Ground()
{
	delete m_transform;
	delete m_rect;
	delete m_mask;
}

Transform *Ground::GetTransform() const
{
	return m_transform;
}

math::AABB *Ground::GetShape() const
{
	return m_rect;
}

Bitmask *Ground::GetMask() const
{
	return m_mask;
}

void Ground::Update()
{
	m_transform->Update();
	m_transform->tMatrix *= *m_world;

	auto pos = math::lh::transform(m_transform->tMatrix * math::inverse(Camera::GetTransform()->tMatrix), math::Vector2D());
	m_rect->position.set(pos - (m_rect->size / 2));
}

void Ground::Draw()
{
	// ofDrawRectangle(m_rect->position.x, m_rect->position.y, m_rect->size.x, m_rect->size.x);
	auto mat = m_transform->tMatrix * math::inverse(Camera::GetTransform()->tMatrix);
	math::lh::draw(mat, m_sprite);

}

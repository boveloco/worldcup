#include "Bullet.h"
#include "MathVinicius\ofDraw.h"
#include "MathVinicius\Matrix3.h"
#include "Transform.h"
#include "Camera.h"

using namespace math;

Bullet::Bullet(char *src, math::Vector2D spawn, math::Vector2D dir, float angle) : 
		dir(dir), impactForce(10), SPEED(200.f)
{
	image.load(src);
	Setup(&Matrix3::newIdentity(), spawn);
	m_transform->angle = angle;

	momentum += dir.normalize() * SPEED;

	rect.position.set(0, 0);
	rect.size.set(image.getWidth(), image.getHeight());
}

void Bullet::Update()
{
	m_transform->position += momentum * ofGetLastFrameTime();
	m_transform->Update();
	//m_transform->tMatrix *= math::inverse(Camera::GetTransform()->tMatrix);

	auto pos = lh::transform(m_transform->tMatrix, Vector2D());
	rect.position.set(pos - (rect.size / 2));
}

void Bullet::Draw()
{
	/*auto pos = lh::transform(m_transform->tMatrix, Vector2D());
	rect.position.set(pos - (rect.size / 2));
	ofDrawLine(rect.position.x, rect.position.y, rect.position.x + rect.size.x, rect.position.y);*/
	lh::draw(m_transform->tMatrix, image);
}

math::BoundingBox Bullet::GetShape() const
{
	return rect;
}
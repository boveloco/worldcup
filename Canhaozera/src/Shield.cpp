#include "Shield.h"
#include "Transform.h"
#include "Camera.h"
#include "MathVinicius\AffineTransform.h"
#include "MathVinicius\ofDraw.h"

Shield::Shield(char *src)
{
	image.load(src);
	shape = math::BoundingCircle(0, 0, image.getHeight() / 2);
}

void Shield::Update()
{
	m_transform->Update();
	m_transform->tMatrix *= *world;

	math::Vector2D pos = math::lh::transform(m_transform->tMatrix, math::Vector2D());
	shape.position.set(pos.x, pos.y);
}

void Shield::Draw()
{
	math::lh::draw(m_transform->tMatrix, image);
}

math::BoundingCircle Shield::GetShape() const
{
	return shape;
}
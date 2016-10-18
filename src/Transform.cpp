#include "Transform.h"
#include "MathVinicius/AffineTransform.h"

Transform::Transform(math::Vector2D pos) : 
		   position(pos), scale(math::Vector2D(1, 1)),angle(0)
{}

void Transform::Update()
{
	tMatrix = math::lh::newAffineScale(scale.x, scale.y) *
			  math::lh::newAffineRotation(math::toRadians(angle)) *
		      math::lh::newAffineTranslation(position);
}
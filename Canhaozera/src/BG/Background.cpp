#include "Background.h"
#include "../Transform.h"
#include "../MathVinicius/ofDraw.h"
#include "../Camera.h"

Background::Background(char *src, math::Vector2D &pos, math::Matrix3 *world) :
			m_transform(new Transform(pos)), world(world)
{
	image.load(src);
}

Background::~Background()
{
	delete m_transform;
	m_transform = nullptr;
}

void Background::Update()
{
	m_transform->Update();
	m_transform->tMatrix *= *world;
}

void Background::Draw()
{
	auto mat = m_transform->tMatrix * math::inverse(Camera::GetTransform()->tMatrix);
	math::lh::draw(mat, image);
}

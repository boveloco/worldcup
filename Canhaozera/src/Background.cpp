#include "Background.h"
#include "MathVinicius\ofDraw.h"
#include "Transform.h"
#include "Camera.h"

Background::Background(char *src, math::Matrix3 *world, math::Vector2D &pos) :
			m_transform(nullptr)
{
	Setup(src, world, pos);
}

Background::Background(char *src, math::Matrix3 *world, float x, float y) :
			m_transform(nullptr)
{
	Setup(src, world, math::Vector2D(x, y));
}

Background::~Background()
{
	if (m_transform)
	{
		delete m_transform;
		m_transform = nullptr;
	}
}

void Background::Setup(char *src, math::Matrix3 *world, math::Vector2D &pos)
{
	image.load(src);
	this->world = world;
	m_transform = new Transform(pos);
}

void Background::Update()
{
	m_transform->Update();
	m_transform->tMatrix *= inverse(Camera::GetTransform()->tMatrix) * *world;
}

void Background::Draw()
{
	math::lh::draw(m_transform->tMatrix, image);
}
#include "Camera.h"
#include "Transform.h"
#include "MathVinicius\AffineTransform.h"

Transform *Camera::m_transform = new Transform(math::Vector2D(0, 0));

Camera::Camera() : 
		world(nullptr)
{}

Camera::~Camera()
{
	delete m_transform;
	m_transform = nullptr;
}

void Camera::Setup(math::Vector2D &p_pos, int p_width, int p_height, math::Matrix3 *p_world)
{
	m_transform->position = p_pos;
	width = (float)p_width/2;
	height = (float)p_height/2;

	world = p_world;

	m_transform->tMatrix = math::Matrix3(1, 0, 0,
										 0, 1, 0,
										 0, 0, 1);
}

void Camera::Setup(float p_x, float p_y, int p_width, int p_height, math::Matrix3 *p_world)
{
	Setup(math::Vector2D(p_x, p_y), p_width, p_height, p_world);
}

Transform *Camera::GetTransform()
{
	return m_transform;
}

int Camera::GetWidth() const
{
	return width * 2;
}

int Camera::GetHeight() const
{
	return height * 2;
}

void Camera::Update(float x, float y)
{
	Update(math::Vector2D(x, y));
}

void Camera::Update(math::Vector2D &pos)
{
	//m_transform->position = pos;
	m_transform->position =  math::lerp(m_transform->position, pos, 1.f);
	m_transform->tMatrix = math::lh::newAffineTranslation(m_transform->position);
}

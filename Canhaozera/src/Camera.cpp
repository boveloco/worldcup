#include "Camera.h"
#include "Transform.h"
#include "MathVinicius\AffineTransform.h"

Transform *Camera::m_transform = new Transform(math::Vector2D(0, 0));

Camera::Camera(math::Vector2D &pos, int width, int height, math::Matrix3 *p_world) :
		world(nullptr)
{
	Setup(pos, width, height, p_world);
}

Camera::Camera(float x, float y, int width, int height, math::Matrix3 *p_world) :
		world(nullptr)
{
	Setup(x, y, width, height, p_world);
}

Camera::~Camera()
{
	delete m_transform;
	m_transform = nullptr;
}

void Camera::Setup(math::Vector2D &p_pos, int p_width, int p_height, math::Matrix3 *p_world)
{
	m_transform->position = p_pos;
	width = p_width;
	height = p_height;

	world = p_world;

	m_transform->tMatrix = math::Matrix3(1, 0, 0,
										 0, 1, 0,
										 p_pos.x, p_pos.y, 1);
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
	return width;
}

int Camera::GetHeight() const
{
	return height;
}

math::Vector2D Camera::getPos()
{
	return m_transform->position;
}


void Camera::Update(float x, float y)
{
	Update(math::Vector2D(x, y));
}

void Camera::Update(math::Vector2D &pos)
{
	//m_transform->position = pos;
	m_transform->position =  math::lerp(m_transform->position, pos, 0.01f);
	m_transform->tMatrix = math::lh::newAffineTranslation(m_transform->position);
}

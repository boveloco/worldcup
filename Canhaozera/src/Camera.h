#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "MathVinicius\Vector2D.h"
#include "MathVinicius\Matrix3.h"

class Transform;

class Camera
{
private:
	static Transform *m_transform;
	math::Matrix3 *world;
	int width;
	int height;

public:
	Camera();
	~Camera();

	void Setup(math::Vector2D &pos, int width, int height, math::Matrix3 *p_world);
	void Setup(float x, float y, int width, int height, math::Matrix3 *p_world);

	static Transform *GetTransform();
	int GetWidth() const;
	int GetHeight() const;

	void Update(float x, float y);
	void Update(math::Vector2D &pos);
	void Update();

};

#endif//__CAMERA_H__
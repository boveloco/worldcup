#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "ofImage.h"
#include "MathVinicius\Vector2D.h"
#include "MathVinicius\Matrix3.h"

class Transform;

class Background
{
private:
	Transform *m_transform;
	ofImage image;
	math::Matrix3 *world;

public:
	Background(char *src, math::Matrix3 *world, math::Vector2D &pos);
	Background(char *src, math::Matrix3 *world, float x, float y);
	~Background();
	void Setup(char *src, math::Matrix3 *world, math::Vector2D &pos);
	void Update();
	void Draw();
};

#endif  //__BACKGROUND_H__

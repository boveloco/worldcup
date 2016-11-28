#ifndef	 __BACKGROUND_H__
#define	 __BACKGROUND_H__

#include "ofMain.h"
#include "../MathVinicius/AffineTransform.h"
#include "../MathVinicius/AABB.h"

class Transform;

class Background
{
private:
	ofImage image;
	Transform *m_transform;
	math::Matrix3 *world;

public:
	Background(char *src, math::Vector2D &pos, math::Matrix3 *world);
	~Background();

	void Update();
	void Draw();
};

#endif //__BACKGROUND_H__

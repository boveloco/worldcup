#pragma once


#include "../MathVinicius/AABB.h"
#include "../MathVinicius/AffineTransform.h"
#include "../Physics/Bitmask.h"
#include "ofMain.h"
#include <vector>

class Transform;

class Ground 
{
private:
	Transform *m_transform;
	math::AABB *m_rect;
	Bitmask *m_mask;
	math::Matrix3 *m_world;

	std::vector<unsigned int> m_frames;
	unsigned int m_frame;
public:
	ofImage m_sprite;
	Ground(char *src, math::Vector2D &pos, math::Matrix3 *world);
	~Ground();

	Transform *GetTransform() const;
	math::AABB *GetShape() const;
	Bitmask *GetMask() const;

	void Update();
	void Draw();

};

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "ofMain.h"
#include "../MathVinicius/MathIncluder.h"
#include "../Physics/Bitmask.h"
#include <vector>

class Transform;

class Explosion
{
private:
	Transform *m_transform;
	math::AABB *m_rect;
	Bitmask *m_mask;

	std::vector<unsigned int> m_frames;
	unsigned int m_frame;

	float m_time;
	bool m_isLive;

public:
	ofImage m_sprite;
	Explosion(char *p_src, math::Vector2D &p_position);
	~Explosion();

	math::AABB *GetShape() const;
	Bitmask *GetMask() const;
	bool IsLive() const;
	void SetIslive(bool p_isLive);
	unsigned int GetFrame() const;
	void Reset(math::Vector2D &p_position, bool p_isLive = true);

	void Update();
	void Draw();
};

#endif //__EXPLOSION_H__

#ifndef  __BULLET_H__
#define  __BULLET_H__

#include "../Body.h"
#include "ofMain.h"
#include "../MathVinicius/AffineTransform.h"
#include "../MathVinicius/AABB.h"
#include "../Physics/Bitmask.h"
#include <vector>

enum Dir {LEFT, RIGHT};

class Bullet : public Body
{
private:
	Dir dir;
	bool alive;

	math::AABB *m_rect;
	Bitmask *m_mask;

	std::vector<unsigned int> m_frames;
	unsigned int m_frame;
public:
	ofImage m_sprite;
	Bullet(char *src, math::Vector2D &pos, math::Vector2D &dir,
		   float angle, float mass, float speed, Dir dirMove);
	~Bullet();

	void Update();
	void Draw();

	math::Vector2D GetPos() const;
	void SetPos(math::Vector2D pos);
	bool GetAlive() const;
	void SetAlive(bool alive);
	Dir GetDir() const;
	math::AABB *GetShape() const;
	Bitmask *GetMask() const;
};

#endif //__BULLET_H__

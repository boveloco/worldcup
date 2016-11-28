#ifndef	 __SHIELD_H__
#define	 __SHIELD_H__

#include "Body.h"
#include "ofMain.h"
#include "MathVinicius\collisions.h"

class Ship;

class Shield : public Body
{
private:
	ofImage image;

	math::BoundingCircle shape;

public:
	Shield(char *src);
	void Update();
	void Draw();

	math::BoundingCircle GetShape() const;
};

#endif //__SHIELD_H__

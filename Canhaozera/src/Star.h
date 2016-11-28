#ifndef __STAR_H__
#define __STAR_H__

#include "Body.h"
#include "ofMain.h"
#include "MathVinicius\collisions.h"

class Star : public Body
{
private:
	ofImage image;
	float radius;
	float attractionForce;

	math::BoundingCircle circle;

public:
	Star(char *src, float radius, float attractionForce);
	float GetRadius() const;
	float GetAttractionForce() const;
	void Update();
	void Draw();

	math::BoundingCircle GetShape() const;
};

#endif // !__STAR_H__


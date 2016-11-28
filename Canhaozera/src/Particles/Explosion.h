#ifndef  __EXPLOSION_H__
#define	 __EXPLOSION_H__

#include "gamesteps.h"
#include "Emitter.h"

#include "ParticleObserver.h"
#include "ColoredBody.h"
#include "Range.h"
#include "../MathVinicius/AffineTransform.h"

class Explosion : public GameSteps
{
private:
	particle::Emitter* emitter;
	particle::body::ColoredBody* explosionBody;

public:
	Explosion();
	virtual void setup();

	virtual void update(float time, const MouseInfo& mouse) {}
	void update(float time);
	virtual void draw() const;

	virtual void teardown();

	void CreateExplosion(const math::Vector2D &pos);
};

#endif //__EXPLOSION_H__

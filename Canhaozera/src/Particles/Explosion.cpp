#include "Explosion.h"

#include "RingShape.h"
#include "DynamicManager.h"
#include "NewtonPhysics.h"
#include "ColoredBody.h"
#include "OFRenderer.h"

#include <iostream>

using namespace std;
using namespace math;
using namespace particle;
using namespace particle::physics;
using namespace particle::body;
using namespace particle::manager;
using namespace particle::shape;

Explosion::Explosion()
{
}

void Explosion::setup()
{
	NewtonPhysics* newton2 = new NewtonPhysics(
		Range<float>(1), //Mass
		Range<int>(1, 100),  //Force
		Range<float>(ofDegToRad(0), ofDegToRad(360)), //Direction
		Range<float>(ofDegToRad(0), ofDegToRad(180)), //Angle
		Range<float>(ofDegToRad(-60), ofDegToRad(60))); //Angular speed

	explosionBody = new ColoredBody(
		30, 0, 0, //Color 
		Range<int>(50, 0)); //Alpha variation

	ParticleRenderer* renderer = new OFRenderer("img/smoke.png", 2, true);
	emitter = new Emitter(ofVec2f(), //Center
		0, //Creations per second
		Range<float>(0.5f, 2.5f), //LifeTime
		new DynamicManager(), newton2, explosionBody,
		renderer); //Managers		
}

void Explosion::update(float time)
{
	emitter->process(time);
}

void Explosion::draw() const
{
	//explosionBody->setColor(200, 20, 0);
	emitter->draw();
}

void Explosion::teardown()
{
	delete emitter;
}

void Explosion::CreateExplosion(const math::Vector2D &pos)
{
	explosionBody->setColor(200, 20, 0);
	emitter->setParticlesPerCreation(3000);
	emitter->setPosition(ofVec2f(pos.x, pos.y));
	emitter->createParticles();
}

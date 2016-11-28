#include "Ship.h"
#include "MathVinicius/ofDraw.h"
#include "Transform.h"
#include "Camera.h"
#include "Keyboard.h"
#include "ofMain.h"
#include "Star.h"
#include "Bullet.h"
#include "Shield.h"
#include "Missile.h"
#include "Rot.h"
#include "Asteroid.h"

using namespace math;

Ship::Ship(char *src, math::Matrix3 *world, math::Vector2D &pos, float mass) :
	move(false), index(0), alive(true), toThrowMissile(false), add(false)
{
	Setup(world, pos, mass);
	image.load(src);
	prop.load("thrust_orange_big.png");
	pos_prop = Vector2D(0.0f, image.getHeight() - prop.getHeight()/4 + 10);

	rect.position.set(0, 0);
	rect.size.set(image.getWidth(), image.getHeight());

	shield = new Shield("escudo.png");
	shield->Setup(&m_transform->tMatrix, 0, 0);
	isProtected = false;
	ctrlShield = 0.0f;
	ctrlrot = 0.0f;
	
}

Ship::~Ship()
{
	for (Bullet *b : bullet)
	{
		delete b;
		b = nullptr;
	}

	bullet.clear();

	for (Missile *m : missiles)
	{
		delete m;
		m = nullptr;
	}

	missiles.clear();

	for (Rot *_r : r)
	{
		delete _r;
		_r = nullptr;
	}
}

void Ship::Update()
{
	if (GetAlive())
	{
		Move();
		Rotate();
		Press();
		ToShoot();
	}

	for (Bullet *b : bullet)
	{
		b->Update();
	}

	for (Missile *m : missiles)
	{
		m->Update();
	}
	
	for (Rot *_r : r)
	{
		_r->Update();
	}

	if (GetAlive())
	{
		m_transform->Update();
		m_transform->tMatrix *= inverse(Camera::GetTransform()->tMatrix) * *world;
	}

	if (isProtected)
	{
		ctrlShield += ofGetLastFrameTime();

		if (ctrlShield > 12.f || !GetAlive())
		{
			ctrlShield = 0.f;
			isProtected = false;
		}
	}

	shield->Update();

	if (asteroids.size() > 0)
	{
		if (r.size() > 0)
		{
			for (Rot *_r : r)
			{
				if (!_r->move)
				{
					_r->move = true;
					int i = rand() % asteroids.size();
					_r->SetDirection(asteroids[i]->GetShape().position);
				}
			}
		}
	}

	if (add)
	{
		ctrlrot += ofGetLastFrameTime();

		if (ctrlrot > 5.f || !GetAlive())
		{
			ctrlrot = 0.0f;
			add = false;
			for (Rot *_r : r)
			{
				delete _r;
				_r = nullptr;
			}
			r.clear();
		}
	}

	index = (index > 16.0f)? 0.0f : index + 8.0f * ofGetLastFrameTime();

	auto pos = lh::transform(m_transform->tMatrix, Vector2D());
	rect.position.set(pos - (rect.size/2));
}

void Ship::Draw()
{
	lh::draw(m_transform->tMatrix, image);

	if (move)
	{
		auto mat = lh::newAffineTranslation(pos_prop) * m_transform->tMatrix;
		lh::draw(mat, prop, Vector2D(64, 128), index);
	}

	if (isProtected)
		shield->Draw();

	for (Bullet *b : bullet)
	{
		b->Draw();
	}

	for (Missile *m : missiles)
	{
		m->Draw();
	}

	for (Rot *_r : r)
	{
		_r->Draw();
	}
}

void Ship::Rotate()
{
	if (Keyboard::GetInstance()->IsDown(OF_KEY_LEFT))
	{
		m_transform->angle += ANGULAR_SPEED * ofGetLastFrameTime();
	}
	if (Keyboard::GetInstance()->IsDown(OF_KEY_RIGHT))
	{
		m_transform->angle -= ANGULAR_SPEED * ofGetLastFrameTime();
	}
}

void Ship::Move()
{
	move = false;

	SetLimit();

	Vector2D acceleration = (CalculateForces() / mass);
	m_transform->position = m_transform->position + momentum * ofGetLastFrameTime() + acceleration * pow(ofGetLastFrameTime(), 2) / 2.f;
	momentum += acceleration * ofGetLastFrameTime();
}

void Ship::ToShoot()
{
	if (Keyboard::GetInstance()->IsPressed(' '))
	{
		spawn = lh::transform(m_transform->tMatrix, Vector2D(0.0f, -(image.getHeight() / 2) + 10));
		Vector2D pos = lh::transform(m_transform->tMatrix, Vector2D(0, 0));
		Vector2D dir = (spawn - pos).normalize();

		bullet.push_back(new Bullet("tiro1.png", spawn, dir, m_transform->angle));
	}
	if (Keyboard::GetInstance()->IsPressed('x'))
	{
		spawn = lh::transform(m_transform->tMatrix, Vector2D(0.0f, -(image.getHeight() / 2) + 10));
		Vector2D pos = lh::transform(m_transform->tMatrix, Vector2D(0, 0));
		Vector2D dir = (spawn - pos).normalize();

		if (asteroids.size() > 0)
		{
			int i = rand() % asteroids.size();
			Vector2D dir = (spawn - pos).normalize();
			missiles.push_back(new Missile("missel.png", spawn, dir, m_transform->angle, asteroids[i]));
			toThrowMissile = true;
		}
	}
	if (Keyboard::GetInstance()->IsPressed('c'))
	{
		if (r.size() == 0)
		{
			r.push_back(new Rot("projectile.png", &m_transform->tMatrix, Vector2D(shield->GetShape().radius, 0.f)));
			r.push_back(new Rot("projectile.png", &m_transform->tMatrix, Vector2D(-shield->GetShape().radius, 0.f)));
			add = true;
		}
	}
}

void Ship::CalculateForceField(Star &star, float attractionForce)
{
	float intensity = star.GatMass() * mass;
	Vector2D  forceField = star.GetTransform()->position - m_transform->position;
	float distSqr = forceField.size();
	forceField.normalize();
	forceField *= (intensity / distSqr) * attractionForce;

	Vector2D acceleration = (forceField / mass);
	momentum += acceleration * ofGetLastFrameTime();
}

Vector2D Ship::CalculateForces()
{
	if (Keyboard::GetInstance()->IsDown(OF_KEY_UP))
	{
		Vector2D aux = lh::transform(m_transform->tMatrix, Vector2D(0.0f, -(image.getHeight() / 2) + 10));
		Vector2D pos = lh::transform(m_transform->tMatrix, Vector2D(0, 0));
		move = true;
		return (aux - pos).normalize() * SPEED; //math::Vector2D::newBySizeAngle(50, math::toRadians(-m_transform->angle)) ;
	}
	if (Keyboard::GetInstance()->IsDown(OF_KEY_DOWN))
	{
		Vector2D aux = lh::transform(m_transform->tMatrix, Vector2D(0.0f, -(image.getHeight() / 2) + 10));
		Vector2D pos = lh::transform(m_transform->tMatrix, Vector2D(0, 0));
		return ((aux - pos)*-1).normalize() * SPEED;
	}

	return Vector2D();
}

void Ship::SetLimit()
{
	if (m_transform->position.x < -5120)
	{
		m_transform->position.x = -5120;
		momentum = math::Vector2D(0, 0);
	}
	else if (m_transform->position.x > 5120)
	{
		m_transform->position.x = 5120;
		momentum = math::Vector2D(0, 0);
	}
	if (m_transform->position.y < -2048)
	{
		m_transform->position.y = -2048;
		momentum = math::Vector2D(0, 0);
	}
	else if (m_transform->position.y > 2048)
	{
		m_transform->position.y = 2048;
		momentum = math::Vector2D(0, 0);
	}
}

void Ship::Press()
{
	if (!isProtected && Keyboard::GetInstance()->IsDown('z'))
	{
		isProtected = true;
	}
}

math::BoundingBox Ship::GetShape() const
{
	return rect;
}

void Ship::SetAlive(bool p_alive)
{
	alive = p_alive;
}

bool Ship::GetAlive() const
{
	return alive;
}

std::vector<Bullet*> Ship::GetBullets() const
{
	return bullet;
}

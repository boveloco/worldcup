#include "Tank.h"
#include "../MathVinicius/ofDraw.h"
#include "../Transform.h"
#include "Cannon.h"
#include "../Keyboard.h"
#include "../Camera.h"
#include "../Bullets/Bullet.h"
#include "../Bullets/ControlOfBullets.h"

Tank::Tank(char* src, math::Matrix3 &world, char *tag) :
	m_tag(tag), m_cannon(nullptr), m_life(1.0f)
{
	m_sprite.load(src);
	Setup(&world, math::Vector2D(), 1.f, true);

	if (m_tag.compare("Player2") == 0)
	{
		m_transform->scale.set(-1, 1);
	}

	m_cannon = new Cannon("cannon.png", math::Vector2D(), m_transform->tMatrix);

	m_rect = new math::AABB(0, 0, m_sprite.getWidth(), m_sprite.getHeight());

	m_lifeBar.bar1.load("barra_1.png");
	m_lifeBar.bar2.load("barra_2.png");

	m_lifeBar.vBar1 = math::Vector2D(m_transform->position.x, m_transform->position.y - m_sprite.getWidth()/2);
	m_lifeBar.vBar2 = math::Vector2D(0, 0);

	m_lifeBar.mBar1 = math::lh::newAffineTranslation(m_lifeBar.vBar1) * world;
	m_lifeBar.mBar2 = math::lh::newAffineTranslation(m_lifeBar.vBar2) * m_lifeBar.mBar1;
}

Tank::Tank(char* src, math::Vector2D &pos, math::Matrix3 &world, char *tag) :
	m_tag(tag), m_life(1.0f)
{
	m_sprite.load(src);
	Setup(&world, pos, 1.f, true);

	if (m_tag == "Player2")
	{
		m_transform->scale.set(-1, 1);
	}

	m_cannon = new Cannon("cannon.png", m_transform->tMatrix);

	m_rect = new math::AABB(0, 0, m_sprite.getWidth(), m_sprite.getHeight());

	m_lifeBar.bar1.load("barra_1.png");
	m_lifeBar.bar2.load("barra_2.png");

	m_lifeBar.vBar1 = math::Vector2D(m_transform->position.x, m_transform->position.y - m_sprite.getWidth() / 2 - 20);
	m_lifeBar.vBar2 = math::Vector2D(0, 0);

	m_lifeBar.mBar1 = math::lh::newAffineTranslation(m_lifeBar.vBar1) * world;
	m_lifeBar.mBar2 = math::lh::newAffineTranslation(m_lifeBar.vBar2) * m_lifeBar.mBar1;
}

void Tank::setPos(math::Vector2D &pos) {
	m_transform->position = pos;
}

math::Vector2D Tank::getPos() {
	return m_transform->position;
}

std::string Tank::getTag() const
{
	return m_tag;
}

void Tank::SetLife(float life)
{
	m_life = life;
	m_life = m_life <= 0.01? 0.0f : m_life;

	m_lifeBar.vBar2 = math::Vector2D(-m_lifeBar.bar2.getWidth() / 2 * (1.0f - life), m_lifeBar.vBar2.y);
}

float Tank::GetLife() const
{
	return m_life;
}

math::AABB *Tank::GetShape() const
{
	return m_rect;
}

void Tank::ToShoot()
{
	if (!ControlOfBullets::bullet)
	{
		if (m_tag == "Player2")
		{
			if (Keyboard::GetInstance()->IsPressed(OF_KEY_RIGHT_ALT))
			{
				math::Vector2D spawn = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D(10.f, 0.f));
				math::Vector2D pos = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D());
				math::Vector2D dir = (spawn - pos).normalize();
				Bullet *bullet = new Bullet("bala1.png", math::lh::transform(m_cannon->GetTransform()->tMatrix,
											m_cannon->GetPos()), dir, m_cannon->GetTransform()->angle, 3, 12000, LEFT);
				ControlOfBullets::bullet = bullet;
				shoot = true;
			}
			else if (Keyboard::GetInstance()->IsPressed(OF_KEY_RIGHT_CONTROL))
			{
				math::Vector2D spawn = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D(10.f, 0.f));
				math::Vector2D pos = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D());
				math::Vector2D dir = (spawn - pos).normalize();
				Bullet *bullet = new Bullet("bala2.png", math::lh::transform(m_cannon->GetTransform()->tMatrix,
											m_cannon->GetPos()), dir, m_cannon->GetTransform()->angle, 2, 9000, LEFT);
				ControlOfBullets::bullet = bullet;
				shoot = true;
			}
			else if (Keyboard::GetInstance()->IsPressed(OF_KEY_DEL))
			{
				math::Vector2D spawn = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D(10.f, 0.f));
				math::Vector2D pos = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D());
				math::Vector2D dir = (spawn - pos).normalize();
				Bullet *bullet = new Bullet("bala3.png", math::lh::transform(m_cannon->GetTransform()->tMatrix,
											m_cannon->GetPos()), dir, m_cannon->GetTransform()->angle, 1, 4000, LEFT);
				ControlOfBullets::bullet = bullet;
				shoot = true;
			}
		}
		else
		{
			if (Keyboard::GetInstance()->IsPressed('e'))
			{
				math::Vector2D spawn = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D(10.f, 0.f));
				math::Vector2D pos = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D());
				math::Vector2D dir = (spawn - pos).normalize();
				Bullet *bullet = new Bullet("bala1.png", math::lh::transform(m_cannon->GetTransform()->tMatrix,
											m_cannon->GetPos()), dir, m_cannon->GetTransform()->angle, 3, 12000, RIGHT);
				ControlOfBullets::bullet = bullet;
				shoot = true;
			}
			else if (Keyboard::GetInstance()->IsPressed('d'))
			{
				math::Vector2D spawn = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D(10.f, 0.f));
				math::Vector2D pos = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D());
				math::Vector2D dir = (spawn - pos).normalize();
				Bullet *bullet = new Bullet("bala2.png", math::lh::transform(m_cannon->GetTransform()->tMatrix,
											m_cannon->GetPos()), dir, -m_cannon->GetTransform()->angle, 2, 9000, RIGHT);
				ControlOfBullets::bullet = bullet;
				shoot = true;
			}
			else if (Keyboard::GetInstance()->IsPressed('c'))
			{
				math::Vector2D spawn = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D(10.f, 0.f));
				math::Vector2D pos = math::lh::transform(m_cannon->GetTransform()->tMatrix, math::Vector2D());
				math::Vector2D dir = (spawn - pos).normalize();
				Bullet *bullet = new Bullet("bala3.png", math::lh::transform(m_cannon->GetTransform()->tMatrix,
											m_cannon->GetPos()), dir, -m_cannon->GetTransform()->angle, 1, 4000, RIGHT);
				ControlOfBullets::bullet = bullet;
				shoot = true;
			}
		}
	}
}

void Tank::ToRotate()
{
	if (m_tag == "Player2")
	{
		if (Keyboard::GetInstance()->IsDown(OF_KEY_UP))
		{
			m_cannon->Rotate(45 * ofGetLastFrameTime());
		}
		if (Keyboard::GetInstance()->IsDown(OF_KEY_DOWN))
		{
			m_cannon->Rotate(-45 * ofGetLastFrameTime());
		}
	}
	else
	{
		if (Keyboard::GetInstance()->IsDown('w'))
		{
			m_cannon->Rotate(45 * ofGetLastFrameTime());
		}
		if (Keyboard::GetInstance()->IsDown('s'))
		{
			m_cannon->Rotate(-45 * ofGetLastFrameTime());
		}
	}
}

void Tank::Update() {
	ControlOfBullets::Update();

	m_cannon->Update();
	
	// faz todas as multiplicações de matrix
	m_transform->Update();
	m_transform->tMatrix *= *world;

	auto pos = math::lh::transform(m_transform->tMatrix * math::inverse(Camera::GetTransform()->tMatrix), math::Vector2D());
	m_rect->position.set(pos - (m_rect->size / 2));

	m_lifeBar.mBar1 = math::lh::newAffineTranslation(m_lifeBar.vBar1) * 
					  math::inverse(Camera::GetTransform()->tMatrix) * *world ;
	m_lifeBar.mBar2 = math::lh::newAffineScale(m_life, 1.0f) *
					  math::lh::newAffineTranslation(m_lifeBar.vBar2) * m_lifeBar.mBar1;

}

void Tank::Draw() {
	ofSetColor(255, 255, 255);
	ControlOfBullets::Draw();
	m_cannon->Draw();
	auto mat = m_transform->tMatrix * math::inverse(Camera::GetTransform()->tMatrix);
	math::lh::draw(mat, m_sprite);

	string text = "";
	text += ofToString(100 * m_life) + "%";
	math::Vector2D p = math::lh::transform(m_lifeBar.mBar1, math::Vector2D());
	ofSetColor(255, 0, 0);
	ofDrawBitmapString(text, p.x - 8, p.y - 12);

	ofSetColor(255, 255, 255);
	math::lh::draw(m_lifeBar.mBar1, m_lifeBar.bar1);
	math::lh::draw(m_lifeBar.mBar2, m_lifeBar.bar2);
}

Tank::~Tank() {
	delete m_cannon;
	m_cannon = nullptr;
	delete m_rect;
	m_rect = nullptr;
}
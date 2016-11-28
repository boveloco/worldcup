#include "ofApp.h"
#include "Ship.h"
#include "MathVinicius/AffineTransform.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Star.h"
#include "Transform.h"
#include "Background.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Shield.h"
#include "Steering.h"
#include "Missile.h"
#include "MathVinicius\collisions.h"
#include "Rot.h"
#include "MathVinicius\ofDraw.h"

math::Vector2D posC;

void ofApp::ResetPosition()
{
	if (time > 3.f)
	{
		ship->SetAlive(true);
		ship->GetTransform()->position = math::Vector2D();
		ship->GetTransform()->angle = 0;
		ship->SetMomentum(math::Vector2D());
		life = 1.f;
		vBar2 = math::Vector2D();
		Camera::GetTransform()->position = math::Vector2D();
		time = 0;
	}
}

//--------------------------------------------------------------
ofApp::~ofApp()
{
	if (ship)
	{
		delete ship;
		ship = nullptr;
	}
	for (Star *s : star)
	{
		delete s;
		s = nullptr;
	}

	star.clear();

	for (Background *b : backgrounds)
	{
		delete b;
		b = nullptr;
	}

	backgrounds.clear();

	for (Asteroid *a : asteroids)
	{
		delete a;
		a = nullptr;
	}

	asteroids.clear();
}

//--------------------------------------------------------------
void ofApp::CreateBackgrounds()
{
	int size = 1024;
	//Background
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(-size * 5, -size*2)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(-size * 4, -size*2 + 6)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(-size * 3, -size*2)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(-size * 2, -size*2 + 6)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(-size, -size*2)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(0, -size*2 + 6)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(size, -size*2)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(size * 2, -size*2 + 6)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(size * 3, -size*2)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(size * 4, -size*2 + 6)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(size * 5, -size*2)));
	/////
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(-size * 5, -size)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(-size * 4, -size + 3)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(-size * 3, -size)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(-size * 2, -size + 3)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(-size, -size)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(0, -size + 3)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(size, -size)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(size * 2, -size + 3)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(size * 3, -size)));
	backgrounds.push_back(new Background("Background2.png", &world, math::Vector2D(size * 4, -size + 3)));
	backgrounds.push_back(new Background("Background1.png", &world, math::Vector2D(size * 5, -size)));
	////
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 5, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 4, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 3, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 2, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(0, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 2, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 3, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 4, 0)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 5, 0)));
	/////
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 5, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 4, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 3, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 2, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(0, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 2, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 3, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 4, size)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 5, size)));
	/////
	backgrounds.push_back(new Background("Background4.png", &world, math::Vector2D(-size * 5, size*2)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 4, size * 2)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 3, size*2)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size * 2, size*2)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(-size, size*2)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(0, size*2)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size, size*2)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 2, size*2)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 3, size*2)));
	backgrounds.push_back(new Background("Background5.png", &world, math::Vector2D(size * 4, size * 2)));
	backgrounds.push_back(new Background("Background3.png", &world, math::Vector2D(size * 5, size*2)));
}

//--------------------------------------------------------------
void ofApp::CreateStars()
{
	Star *s = new Star("terra.png", 1080, 4.f);
	s->Setup(&world, -ofGetWidth() * 2, -ofGetHeight() / 2, 300.f);
	star.push_back(s);

	s = new Star("lua.png", 600, 2.f);
	s->Setup(&world, -ofGetWidth() / 2, -ofGetHeight() / 2, 100.f);
	star.push_back(s);

	s = new Star("sol.png", 1320, 6.f);
	s->Setup(&world, -ofGetWidth() * 4, 0, 2000.f);
	star.push_back(s);

	s = new Star("terra.png", 810, 2.f);
	s->Setup(&world, ofGetWidth() * 2, ofGetHeight() / 2, 200.f);
	star.push_back(s);

	s = new Star("sol.png", 1320, 4.f);
	s->Setup(&world, ofGetWidth() * 4, 0, 1000.f);
	star.push_back(s);

	s = new Star("sol.png", 990, 5.f);
	s->Setup(&world, 0, -ofGetWidth()*2, 1000.f);
	star.push_back(s);

	s = new Star("lua.png", 400, 1.f);
	s->Setup(&world, 0, ofGetWidth() * 1.5f, 100.f);
	star.push_back(s);

	s = new Star("terra.png", 740, 1.5f);
	s->Setup(&world, -ofGetWidth() * 3, ofGetWidth() * 1.5f, 200.f);
	star.push_back(s);
}

//--------------------------------------------------------------
void ofApp::GravitationalField(Star &star, Ship &s)
{
	if (!s.GetAlive())
		return;

	math::Vector2D aux = s.GetTransform()->position - star.GetTransform()->position;

	if (aux.size() < star.GetRadius())
	{
		s.CalculateForceField(star, star.GetAttractionForce());
	}
}

//--------------------------------------------------------------
void ofApp::AddAsteroid()
{
	if (controlAsteroids > 0.3f)
	{
		int y = rand() % 2560;
		y = y * 2 - 2560;
		int x = (y == -2560)? rand() % 5632 : 0;
		x = x * 2 - 5632;
		math::Vector2D pos = math::Vector2D(x, y);
		math::Vector2D dir = math::Vector2D(rand() % ofGetWidth(), rand() % ofGetHeight());
		float mass = (rand() % 10) + 1;
		float speed = (rand() % 150) + 50;

		Asteroid *a = new Asteroid("asteroide.png", &world, pos, dir.normalize(), mass, speed);
		asteroids.push_back(a);
		controlAsteroids = 0.f;
	}
}

//--------------------------------------------------------------
bool ofApp::AsteroidCollisionCheck(Ship *s, Asteroid *a)
{
	if (s->GetAlive() && math::circleBoxCollisionCheck(&s->GetShape(), &a->GetShape()))
	{
		//ship->SetAlive(false);
		life -= 0.2f;
		vBar2 = math::Vector2D(-bar2.getWidth()/2*(1.0f - life), vBar2.y);
		explosion.CreateExplosion(s->GetShape().position);
		posC = ship->GetTransform()->position;
		return true;
	}

	return false;
}

//--------------------------------------------------------------
void ofApp::AsteroidBulletCollisionCheck(Asteroid *a)
{
	if (!ship->GetAlive())
		return;

	std::vector<Bullet *> inGame;
	for (Bullet *b : ship->bullet)
	{
		if (a && math::circleBoxCollisionCheck(&b->GetShape(), &a->GetShape()))
		{
  			delete b;
			a->SetAlive(false);
			score += 50;
		}
		else if (b->GetTransform()->position.x > 5632 &&
				b->GetTransform()->position.y > 2560 &&
				b->GetTransform()->position.x <= -5632 &&
				b->GetTransform()->position.y <= -2560)
		{
			delete b;
		}
		else
			inGame.push_back(b);
	}

	std::swap(inGame, ship->bullet);

	std::vector<Missile*> miss;

	for (Missile *m : ship->missiles)
	{
		if (a && math::circleBoxCollisionCheck(&m->GetShape(), &a->GetShape()))
		{
			delete m;
			a->SetAlive(false);
			score += 50;
		}
		else if (m->GetTransform()->position.x > 5632 &&
				 m->GetTransform()->position.y > 2560 &&
				 m->GetTransform()->position.x <= -5632 &&
				 m->GetTransform()->position.y <= -2560)
		{
			delete m;
		}
		else
			miss.push_back(m);
	}
	std::swap(miss, ship->missiles);

	std::vector<Rot*> rot;

	for (Rot *r : ship->r)
	{
		if (a && math::circleCollisionCheck(&r->GetShape(), &a->GetShape()))
		{
			delete r;
			a->SetAlive(false);
			score += 50;
		}
		else if (r->GetTransform()->position.x > 5632 &&
				 r->GetTransform()->position.y > 2560 &&
				 r->GetTransform()->position.x <= -5632 &&
				 r->GetTransform()->position.y <= -2560)
		{
			delete r;
		}
		else
			rot.push_back(r);
	}
	std::swap(rot, ship->r);
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	world = math::Matrix3(1, 0, 0,
						  0, 1, 0,
						  ofGetWidth() / 2, ofGetHeight() / 2, 1);

	camera = new Camera;
	camera->Setup(math::Vector2D(-1024, 0), (float)ofGetWidth(), (float)ofGetHeight(), &world);
	
	CreateBackgrounds();
	CreateStars();
	
	ship = new Ship("player.png", &world, math::Vector2D(0, 0), 2.f);
	//math::Vector2D pos = math::Vector2D(0, 0);//math::lh::transform(world, math::Vector2D(0, 0));
	//ship->Setup(&world, pos, 2.f);

	bar1.load("barra_1.png");
	bar2.load("barra_2.png");
	
	vBar1 = math::Vector2D(-ofGetWidth()/2 + 100, -ofGetHeight()/2 + 50);

	mBar1 = math::lh::newAffineTranslation(vBar1) * world;
	mBar2 = math::lh::newAffineTranslation(vBar2) * mBar1;

	life = 1.0f;
	score = 0;
	explosion.setup();
	controlAsteroids = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	ResetPosition();
	AddAsteroid();
	ship->Update();
	

	for (Star *s : star)
	{
		s->Update();
		if (ship->GetAlive())
		{
			GravitationalField(*s, *ship);

			if (math::circleBoxCollisionCheck(&ship->GetShape(), &s->GetShape()))
			{
				ship->SetAlive(false);
				life = 0.f;
				explosion.CreateExplosion(ship->GetShape().position);
				posC = ship->GetTransform()->position;
				break;
			}
		}
	}

	if (ship->GetAlive())
		camera->Update(ship->GetTransform()->position);
	else
		camera->Update(posC);

	explosion.update(ofGetLastFrameTime());

	for (Background *b : backgrounds)
	{
		b->Update();
	}

	std::vector<Asteroid *> inGame;
	std::vector<Asteroid*> ast;

	for (Asteroid *a : asteroids)
	{
		a->Update();

		if (ship->GetAlive())
		{
			math::BoundingCircle aux = math::BoundingCircle(ship->GetShield()->GetShape().position,
															ship->GetShield()->GetShape().radius * 4);
			if (math::circleCollisionCheck(&a->GetShape(), &aux))
			{
				ast.push_back(a);
			}
		}
		if (a->GetTransform()->position.x < 5632 &&
			a->GetTransform()->position.y < 2560 &&
			a->GetTransform()->position.x >= -5632 &&
			a->GetTransform()->position.y >= -2560)
		{
			if (AsteroidCollisionCheck(ship, a))
			{
				a->SetAlive(false);
			}
			if (ship->GetAlive() && ship->IsProtected())
			{
				a->SetForce(Steering::Flee(a->GetShape(), ship->GetShield()->GetShape(), a->GetSpeed()));
			}
			AsteroidBulletCollisionCheck(a);

			if (a->GetAlive())
			{
				inGame.push_back(a);
			}
			else
			{
				delete a;
				a = nullptr;
			}
		}
		else
			delete a;
	}

	if(ship->GetAlive())
		ship->asteroids = ast;

	asteroids.clear();
	asteroids = inGame;

	controlAsteroids += 1.f * ofGetLastFrameTime();

	if (life <= 0.01)
	{
		life = 0;
		ship->SetAlive(false);
		time += ofGetLastFrameTime();
	}

	mBar1 = math::lh::newAffineTranslation(vBar1) * world;
	mBar2 = math::lh::newAffineScale(life, 1.0f) * 
			math::lh::newAffineTranslation(vBar2) * mBar1;

	Keyboard::GetInstance()->Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	for (Background *b : backgrounds)
	{
		b->Draw();
	}

	for (Star *s : star)
	{
		s->Draw();
	}

	if (ship->GetAlive())
		ship->Draw();

	for (Asteroid *a : asteroids)
	{
		a->Draw();
	}


	explosion.draw();

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255, 255, 255);
	math::lh::draw(mBar1, bar1);
	math::lh::draw(mBar2, bar2);

	string l = "";
	l += ofToString(100 * life) + "%";
	ofSetColor(255, 0, 0);
	ofDrawBitmapString(l, 90, 30);
	
	string s = "";
	s += "SCORE: " + ofToString(score);
	ofSetColor(0, 255, 0);
	ofDrawBitmapString(s, ofGetWidth() - 150, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	Keyboard::GetInstance()->Set(key, true);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	Keyboard::GetInstance()->Set(key, false);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

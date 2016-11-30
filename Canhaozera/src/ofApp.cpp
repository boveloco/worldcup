#include "ofApp.h"
#include <iostream>

#include "Tank\Tank.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Physics\Physics.h"
#include "Bullets\ControlOfBullets.h"
#include "Bullets\Bullet.h"
#include "Transform.h"
#include "BG\Background.h"
#include "BG\Ground.h"
#include "Bullets\Explosion.h"
#include "MathVinicius\MathIncluder.h"
#include "MathVinicius\ofDraw.h"

void ofApp::CollisionCheck()
{
	if (ControlOfBullets::bullet)
	{
		int index = control + 1 > 1 ? 0 : control + 1;

		if (Physics::BoxCollisionCheck(*m_tanks[index]->GetShape(), *ControlOfBullets::bullet->GetShape()))
		{
			m_tanks[index]->SetLife(m_tanks[index]->GetLife() - ControlOfBullets::bullet->GetMass() / 10.0f);
			explosion->Reset(ControlOfBullets::bullet->GetPos());
			delete ControlOfBullets::bullet;
			ControlOfBullets::bullet = nullptr;
			control++;
			control = (control > 1) ? 0 : control;
			physics->_objects.erase(physics->_objects.begin() + 4);
			posCam = (m_tanks[control]->getTag() == "Player") ? math::Vector2D() : math::Vector2D(ofGetWidth(), 0);

			int r = (rand() % 4 + 1);
			if (r % 2 == 0)
			{
				wDir *= -1.f;
			}
		}
		else if (Physics::BoxCollisionCheck(*ground->GetShape(), *ControlOfBullets::bullet->GetShape()))
		{
			if (ground->GetMask()->testCollision(*ControlOfBullets::bullet->GetMask()))
			{
				explosion->Reset(ControlOfBullets::bullet->GetPos());
				delete ControlOfBullets::bullet;
				ControlOfBullets::bullet = nullptr;
				control++;
				control = (control > 1) ? 0 : control;
				physics->_objects.erase(physics->_objects.begin() + 4);
				posCam = (m_tanks[control]->getTag() == "Player") ? math::Vector2D() : math::Vector2D(ofGetWidth(), 0);

				int r = (rand() % 4 + 1);
				if (r % 2 == 0)
				{
					wDir *= -1.f;
				}
			}
		}
	}

	if (explosion->IsLive())
	{
		math::Vector2D aux = ground->GetShape()->position + ground->GetMask()->GetPixel();
		math::BoundingCircle b = math::BoundingCircle(aux, explosion->m_sprite.getHeight() / 3);

		ground->GetMask()->removeArea(b);
	}
}

ofApp::~ofApp()
{
	delete camera;
	camera = nullptr;
	delete physics;
	physics = nullptr;
	delete bg;
	bg = nullptr;
	delete explosion;
	explosion = nullptr;

	for (Tank *t : m_tanks)
	{
		delete t;
		t = nullptr;
	}

	m_tanks.clear();
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackgroundHex(0x00ffff);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofDisableAntiAliasing();
	ofSetFrameRate(60);

	physics = new Physics();
	physics->setGravity(math::Vector2D(0, 20));
	physics->setWind(math::Vector2D(-3, 0));

	_world = math::Matrix3(1, 0, 0,
						   0, 1, 0,
						   ofGetWidth() / 2, ofGetHeight() / 2, 1);

	//bg = new Background("deserto.png", math::Vector2D(0, 0), &_world);

	ground = new Ground("ground.png", math::Vector2D(518, ofGetHeight()/2), &_world);

	m_tanks.push_back(new Tank("tank.png", math::Vector2D(-400, 260), _world, "Player"));
	m_tanks.push_back(new Tank("tank.png", math::Vector2D(ofGetWidth() + 400, 220), _world, "Player2"));

	explosion = new Explosion("Exp.png", math::Vector2D(512, 300));

	control = rand() % 2;

	posCam = (m_tanks[control]->getTag() == "Player") ? math::Vector2D() : math::Vector2D(ofGetWidth(), 0);
	camera = new Camera(posCam, (float)ofGetWidth(), (float)ofGetHeight(), &_world);

	wDirection.load("direção.png");
	wTransform = new Transform(math::Vector2D(ofGetWidth() / 2, 100));
	wDir = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
	physics->update();
	physics->setWind(physics->getWind() * wDir);
	//bg->Update();
	ground->Update();

	if (m_tanks[control]->shoot)
	{
		if (m_tanks[control]->getTag() == "Player2")
			dist.x = ControlOfBullets::bullet->GetPos().x - ofGetWidth();
		else
			dist.x = 0;
		m_tanks[control]->shoot = false;
	}
	if (ControlOfBullets::bullet)
	{
		posCam = ControlOfBullets::bullet->GetPos() - dist;
		if (ControlOfBullets::bullet->GetPos().y > ofGetHeight() || 
			ControlOfBullets::bullet->GetPos().x < 0 || 
			ControlOfBullets::bullet->GetPos().x > ofGetWidth()*3)
		{
			delete ControlOfBullets::bullet;
			ControlOfBullets::bullet = nullptr;
			physics->_objects.erase(physics->_objects.begin() + 4);
			control++;
			control = (control > 1) ? 0 : control;
			posCam = (m_tanks[control]->getTag() == "Player")? math::Vector2D() : math::Vector2D(ofGetWidth(), 0);
			int r = (rand() % 4 + 1);
			if (r % 2 == 0)
			{
				wDir *= -1.f;
			}
		}

	}

	camera->Update(posCam.x, 0.f);
	camera->GetTransform()->position.x = (camera->getPos().x < 1)? 0 : (camera->getPos().x > ofGetWidth() - 1) ? ofGetWidth() : camera->getPos().x;

	m_tanks[control]->ToRotate();
	m_tanks[control]->ToShoot();

	for each (Tank *t in m_tanks)
	{	
		t->Update();
	}

	CollisionCheck();

	explosion->Update();

	wTransform->scale.set(wDir, 1.f);
	wTransform->Update();

	Keyboard::GetInstance()->Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	//bg->Draw();
	ground->Draw();

	for each (Tank *t in m_tanks)
	{
		t->Draw();
	}

	string text = "";
	text += ofToString("WIND");
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(text, ofGetWidth() / 2 - 15, 70);

	ofSetColor(255, 255, 255);
	explosion->Draw();
	math::lh::draw(wTransform->tMatrix, wDirection);
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

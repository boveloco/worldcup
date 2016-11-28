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

void ofApp::CollisionCheck()
{
	int index = control + 1 > 1 ? 0 : control + 1;

	if (Physics::BoxCollisionCheck(*_tanks[index]->GetShape(), *ControlOfBullets::bullet->GetShape()))
	{
		_tanks[index]->SetLife(_tanks[index]->GetLife() - ControlOfBullets::bullet->GetMass()/10.0f);
		delete ControlOfBullets::bullet;
		ControlOfBullets::bullet = nullptr;
		control++;
		control = (control > 1) ? 0 : control;
		physics->_objects.erase(physics->_objects.begin() + 4);
		posCam = (_tanks[control]->getTag() == "Player") ? math::Vector2D() : math::Vector2D(ofGetWidth(), 0);
	}
	if(ControlOfBullets::bullet->GetMask()->testCollision(*ground->GetMask()))
	{
		delete ControlOfBullets::bullet;
		ControlOfBullets::bullet = nullptr;
		control++;
		control = (control > 1) ? 0 : control;
		physics->_objects.erase(physics->_objects.begin() + 4);
		posCam = (_tanks[control]->getTag() == "Player") ? math::Vector2D() : math::Vector2D(ofGetWidth(), 0);
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

	for (Tank *t : _tanks)
	{
		delete t;
		t = nullptr;
	}

	_tanks.clear();
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
	physics->setWind(math::Vector2D(-2, 0));

	_world = math::Matrix3(1, 0, 0,
						   0, 1, 0,
						   ofGetWidth() / 2, ofGetHeight() / 2, 1);

	bg = new Background("deserto.png", math::Vector2D(0, 0), &_world);

	ground = new Ground("Ground2.png", math::Vector2D(518, ofGetHeight()/2), &_world);

	_tanks.push_back(new Tank("tank.png", math::Vector2D(-400, 220), _world, "Player"));
	_tanks.push_back(new Tank("tank.png", math::Vector2D(ofGetWidth() + 400, 220), _world, "Player2"));

	control = rand() % 2;

	posCam = (_tanks[control]->getTag() == "Player") ? math::Vector2D() : math::Vector2D(ofGetWidth(), 0);
	camera = new Camera(posCam, (float)ofGetWidth(), (float)ofGetHeight(), &_world);
}

//--------------------------------------------------------------
void ofApp::update(){
	physics->update();
	bg->Update();
	ground->Update();

	if (_tanks[control]->shoot)
	{
		if (_tanks[control]->getTag() == "Player2")
			dist.x = ControlOfBullets::bullet->GetPos().x - ofGetWidth();
		else
			dist.x = 0;
		_tanks[control]->shoot = false;
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
			posCam = (_tanks[control]->getTag() == "Player")? math::Vector2D() : math::Vector2D(ofGetWidth(), 0); 
		}

	}

	camera->Update(posCam.x, 0.f);
	camera->GetTransform()->position.x = (camera->getPos().x < 1)? 0 : (camera->getPos().x > ofGetWidth() - 1) ? ofGetWidth() : camera->getPos().x;

	_tanks[control]->ToRotate();
	_tanks[control]->ToShoot();

	for each (Tank *t in _tanks)
	{	
		t->Update();
	}

	if (ControlOfBullets::bullet)
	{
		CollisionCheck();
	}

	Keyboard::GetInstance()->Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	bg->Draw();
	ground->Draw();

	for each (Tank *t in _tanks)
	{
		t->Draw();
	}
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

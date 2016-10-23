#include "ofApp.h"
#include <iostream>

#include "Tank\Tank.h"

//--------------------------------------------------------------
void ofApp::setup(){
	_world = math::Matrix3(1, 0, 0,
						   0, 1, 0,
						   ofGetWidth() / 2, ofGetHeight() / 2, 1);

	_tanks.push_back(new Tank("img/tank.png", _world));
	_tanks.push_back(new Tank("img/tank.png",math::Vector2D(200,0), _world));
}

//--------------------------------------------------------------
void ofApp::update(){
	for each (Tank *t in _tanks)
	{	
		t->Update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for each (Tank *t in _tanks)
	{
		t->Draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

#pragma once

#include "ofMain.h"
#include <vector>
#include "MathVinicius\AffineTransform.h"

class Tank;
class Camera;
class Physics;
class Background;
class Bullet;
class Ground;

class ofApp : public ofBaseApp{
	private:
		Camera *camera;
		Physics *physics;
		Background *bg;
		Ground *ground;

		math::Vector2D posCam;
		math::Vector2D dist;
		int control;

		void CollisionCheck();
	public:
		~ofApp();
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		std::vector<Tank*> _tanks;
		math::Matrix3 _world;
};

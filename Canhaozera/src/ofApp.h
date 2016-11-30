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
class Explosion;
class Transform;

class ofApp : public ofBaseApp{
	private:
		Camera *camera;
		Physics *physics;
		Background *bg;
		Ground *ground;
		Explosion *explosion;

		math::Vector2D posCam;
		math::Vector2D dist;
		int control;

		void CollisionCheck();

		ofImage wDirection;
		float wDir;
		Transform *wTransform;

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

		std::vector<Tank*> m_tanks;
		math::Matrix3 _world;
};

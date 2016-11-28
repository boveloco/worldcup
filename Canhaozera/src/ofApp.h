#pragma once

#include "ofMain.h"
#include "MathVinicius/Matrix3.h"
#include "Particles/Explosion.h"
#include <vector>

class Ship;
class Camera;
class Star;
class Background;
class Asteroid;
class Missile;

class ofApp : public ofBaseApp{
	private:
		Ship *ship;
		Camera *camera;
		math::Matrix3 world;

		std::vector<Star *> star;
		std::vector<Background *> backgrounds;
		std::vector<Asteroid *> asteroids;

		Explosion explosion;
		bool ex = false;

		float controlAsteroids;

		void CreateBackgrounds();
		void CreateStars();
		void GravitationalField(Star &star, Ship &s);
		void AddAsteroid();

		bool AsteroidCollisionCheck(Ship *s, Asteroid *a);
		void AsteroidBulletCollisionCheck(Asteroid *a);

		float life;
		int score;

		ofImage bar1;
		ofImage bar2;

		math::Matrix3 mBar1;
		math::Matrix3 mBar2;

		math::Vector2D vBar1;
		math::Vector2D vBar2;

		float time;

		void ResetPosition();
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
		
};

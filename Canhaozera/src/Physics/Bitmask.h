#pragma once

#include <ofImage.h>
#include "../MathVinicius/Vector2D.h"
#include "../MathVinicius/AABB.h"
#include "../MathVinicius/BoundingCircle.h"

class Bitmask
{
	ofImage* image;
	math::AABB* broadPhaseBox;
	math::Vector2D* dimensions;
	vector<unsigned int>* frames;
	unsigned int* frame;
	function<bool(ofVec4f)> isColorKey;

	static function<bool(ofVec4f)> defaultColorKey();
	ofVec4f pixelColor(int x, int y) const;
	unsigned int currentFrameRow() const;
	unsigned int currentFrameCol() const;

	math::Vector2D m_pixel;

public:
	explicit Bitmask();
	explicit Bitmask(
		ofImage& image, 
		math::AABB& broadPhaseBox, 
		math::Vector2D* dimensions = nullptr, 
		vector<unsigned int>* frames = nullptr, 
		unsigned int* frame = nullptr, 
		function<bool(ofVec4f)> isColorKey = nullptr);

	bool testCollision(Bitmask& other);
	void transform(math::Vector2D position, float angle, math::Vector2D size, bool centered);

	math::Vector2D GetPixel() const;

	void removeArea(const Bitmask& other);
	void removeArea(math::AABB& region);
	void removeArea(math::BoundingCircle& region);

	virtual ~Bitmask();
};

#pragma once
#include "BaseAnimation.h"
#include <string>
#include <array>

class SpriteAnimation : public BaseAnimation
{
public:
	SpriteAnimation(const std::string& animationName, const int timePerFrame, const ofPoint& position, const float rotation, bool loop = false);
	~SpriteAnimation();

	void setPosition(const ofPoint& position);
	void setRotation(const float rotation);

	void update(int deltaTime);
	void draw();

private:
	int passedTime;
	int currentFrame;
	int numberOfFrames;
	int timePerFrame;
	bool loop;
	ofPoint position;
	float rotation;

	// TODO use less memory consuming data structure
	std::vector<PizzaImage*> frames;
};


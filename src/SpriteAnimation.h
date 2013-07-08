#pragma once
#include "BaseAnimation.h"
#include <string>
#include <array>

class SpriteAnimation : public BaseAnimation
{
public:
	SpriteAnimation(const std::string& folderName, const int numberOfFrames, const int timePerFrame, const ofPoint& position, const float rotation);
	~SpriteAnimation();

	void update(int deltaTime);
	void draw();

private:
	int passedTime;
	int currentFrame;
	const int numberOfFrames;
	const int timePerFrame;

	// TODO use less memory consuming data structure
	std::vector<PizzaImage*> frames;
};


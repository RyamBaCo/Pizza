#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(const std::string& folderName, const int numberOfFrames, const int timePerFrame, const ofPoint& position, const float rotation)
	:	BaseAnimation(),
		numberOfFrames(numberOfFrames),
		timePerFrame(timePerFrame),
		currentFrame(0),
		passedTime(0)
{
	for(int i = 0; i < numberOfFrames; ++i)
	{
		frames.push_back(new PizzaImage("images/" + folderName + "/" + "s (" + ofToString(i + 1) + ").png", PizzaImage::CENTER, rotation));
		frames[i]->setDrawPosition(position);
	}
}

SpriteAnimation::~SpriteAnimation(void)
{
	for(int i = 0; i < frames.size(); ++i)
		if(frames[i] != 0)
		{
			delete frames[i];
			frames[i] = 0;
		}		

	frames.clear();
}

void SpriteAnimation::update(int deltaTime)
{
	passedTime += deltaTime;
	currentFrame = passedTime / timePerFrame;

	if(currentFrame >= numberOfFrames)
	{
		currentFrame = numberOfFrames - 1;
		readyForDelete = true;
	}
}

void SpriteAnimation::draw()
{
	frames[currentFrame]->draw();
}

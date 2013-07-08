#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(const std::string& folderName, const int numberOfFrames, const int timePerFrame, const ofPoint& position, const float rotation, bool loop)
	:	BaseAnimation(),
		numberOfFrames(numberOfFrames),
		timePerFrame(timePerFrame),
		currentFrame(0),
		passedTime(0),
		loop(loop)
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

void SpriteAnimation::setPosition(const ofPoint& position)
{
	for(int i = 0; i < numberOfFrames; ++i)
		frames[i]->setDrawPosition(position);
}

void SpriteAnimation::setRotation(const float rotation)
{
	for(int i = 0; i < numberOfFrames; ++i)
		frames[i]->setDrawRotation(rotation);
}

void SpriteAnimation::update(int deltaTime)
{
	passedTime += deltaTime;
	currentFrame = passedTime / timePerFrame;

	if(currentFrame >= numberOfFrames)
	{
		currentFrame = numberOfFrames - 1;
		loop ? passedTime = 0 : readyForDelete = true;
	}
}

void SpriteAnimation::draw()
{
	frames[currentFrame]->draw();
}
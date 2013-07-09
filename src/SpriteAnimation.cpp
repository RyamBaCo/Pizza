#include "SpriteAnimation.h"
#include "GlobalValues.h"

SpriteAnimation::SpriteAnimation(const std::string& animationName, const int timePerFrame, const ofPoint& position, const float rotation, bool loop)
	:	BaseAnimation(),
		timePerFrame(timePerFrame),
		currentFrame(0),
		passedTime(0),
		loop(loop),
		position(position),
		rotation(rotation)
{
	frames = GlobalValues::getInstance().getAnimationImages(animationName);
	numberOfFrames = frames.size();
}

SpriteAnimation::~SpriteAnimation(void)
{
}

void SpriteAnimation::setPosition(const ofPoint& position)
{
	this->position = position;
}

void SpriteAnimation::setRotation(const float rotation)
{
	this->rotation = rotation;
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
	frames[currentFrame]->draw(position, rotation);
}